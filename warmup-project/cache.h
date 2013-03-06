#ifndef _CACHE_H
#define _CACHE_H

#include "systemc"
#include "sram.h"

#include <iostream>
using namespace std;

extern ofstream mylogfile;
#define sysc_logfile if (1) mylogfile

using namespace sc_core;
using namespace sc_dt;

#define ENABLE_SYSTEMC_CACHE

class Cache : public sc_module
{
	typedef Cache SC_CURRENT_USER_MODULE;

	virtual void work() = 0;
public:
	static const int block_size = 64;
	static const int ports = 1;

	static const int depthLog2 = 4;
	static const int idx_mask = (1<<depthLog2)-1;

	sc_in<bool>          clk;
	sc_in<bool>          reset;

	sc_signal<bool>      port_available[ports];

	//general inputs
	sc_in<bool>          in_ena[ports];
	sc_in<sc_uint<64> >  in_addr[ports];
	
	
	//inserting data
	sc_in<bool>          in_is_insert[ports];
	sc_in<bool>          in_has_data[ports];
	sc_in<sc_bv<8*block_size> >  in_data[ports];
	
	//needs data
	sc_in<bool>          in_needs_data[ports];
	
	//status update
	sc_in<bool>          in_update_state[ports];
	sc_in<sc_uint<8> >   in_new_state[ports];

	//general outputs
	sc_out<bool>         out_ready[ports];
	
	sc_out<sc_uint<64> > out_addr[ports];
	sc_out<sc_bv<8*block_size> >   out_data[ports];
	sc_out<sc_uint<64> > out_token[ports];
	sc_out<sc_uint<8> >  out_state[ports];

	Cache(const sc_module_name &name)
	:	sc_module(name)
	{
		SC_METHOD(work); sensitive << clk.pos();
		for(int p=0; p<ports; ++p)
			port_available[p] = false;
	}
};
	/*
	sc_in<bool> ena[ports];
	sc_in<Addr> addr[ports];
	sc_in<Row>  din[ports];
	sc_in<bool> we[ports];
	sc_out<Row> dout[ports];
	
	A basic overview of the Cache interface that you must implement:

	in_ena[#]<bool> - New request is available.  Can only be true if the port_available output was set to true on the preceeding clock cycle.
	in_addr[#]<uint<64>> - The ful address that triggered this operation (corresponding to the accessed/inserted block).
	in_is_insert[#]<bool> - If true, must evict an entry to write a new one.
	in_has_data[#]<bool> - If true, must write value from in_data into the cache.
	in_needs_data[#]<bool> - If true, data must be fetched from the cache and output on out_data.
	in_data[#]<uint<64>> - The data in case in_has_data is true.
	in_update_state[#]<bool> - If update state is true, must update the state corresponding to the block with the value from in_new_state.
	in_new_state[#]<uint<8>> - The state in case in_update_state is true.

	out_ready[#]<bool> - If true, one of the operations sent to the cache has completed.
	out_token[#]<uint<64>> - When out_ready is true, out_token must be set to the value of in_addr from the original request.
	out_addr[#]<uint<64>> - This should always be set to what has been read out of the tag array.  This may be the accessed tag or the old tag (the victim being replaced).
	out_state[#]<uint<8>> - Always reads the state bits corresponding to the accessed cache line, EXCEPT on a miss, set 0xff.
	out_data[#]<bv<8*blocksz>> - If in_needs_data on the request was true, out_data must contain the block contents.
	*/
	
class CacheProject: public Cache
{
	SRAM<8*block_size,depthLog2,ports>	data_set1;
	SRAM<8,depthLog2,ports>			state_set1;
	SRAM<64,depthLog2,ports>			tag_set1;

	SRAM<8*block_size,depthLog2,ports>	data_set2;
	SRAM<8,depthLog2,ports>			state_set2;
	SRAM<64,depthLog2,ports>			tag_set2;
	
	sc_uint<64> servaddr[ports];
	sc_bv<8> newstate[ports];
	sc_bv<64> temptag[ports][2];
	sc_bv<8*block_size>	newdata[ports];
	
	sc_signal<bool> dataena[ports], stateena[ports], tagena[ports];
	sc_signal<bool> datawe[ports], statewe[ports], tagwe[ports];
	sc_signal<sc_uint<depthLog2> > tagaddr[ports], stateaddr[ports], dataaddr[ports];
	sc_signal<sc_bv<8> > statedin[ports];
	sc_signal<sc_bv<64> > tagdin[ports];
	sc_signal<sc_bv<8*block_size> > datadin[ports];
	
	sc_signal<sc_bv<8> > statedout1[ports];
	sc_signal<sc_bv<64> > tagdout1[ports];
	sc_signal<sc_bv<8*block_size> > datadout1[ports];

	sc_signal<sc_bv<8> > statedout2[ports];
	sc_signal<sc_bv<64> > tagdout2[ports];
	sc_signal<sc_bv<8*block_size> > datadout2[ports];
	
	int waitdelay[ports];
	bool deassertoutput[ports];
	int operation[ports];	//1 for insert 2 for read 3 for update 4 for write probe reset to 0 when not valid.
	int opstate[ports];	// only for write and update. 1 for reading 2 for updating. reset to 0 later.

	int set;
	
	void work(){
		for(int p=0; p<ports; ++p){
			if(deassertoutput[p] == true){
				//sysc_logfile <<"In deassertoutput!"<<endl;
				out_ready[p] = false;
				deassertoutput[p] = false;
			}
			if(waitdelay[p]>0) {
				waitdelay[p]--;
				port_available[p] = false;
				out_ready[p] = false;
				continue;
			}
			else if(waitdelay[p] == 0){
				port_available[p] = true; // available for next cycle
				if(operation[p] == 1){	//insert
					stateena[p] = false;
					statewe[p] = false;
					
					dataena[p] = false;
					datawe[p] = false;
					
					tagena[p] = false;
					tagwe[p] = false;
					
					out_ready[p] = true;
					deassertoutput[p] = true;

					if(!set)
					  out_state[p] = state_set1.dout[p].read();
					else 
					  out_state[p] = state_set2.dout[p].read();					  
					out_token[p] = servaddr[p];
					out_addr[p] = temptag[p][set];
					opstate[p] = 0;
					operation[p] = 0;
					waitdelay[p] = 0;
				}
				else if(operation[p] == 2){	//read
					temptag[p][0] = tag_set1.dout[p];
					temptag[p][1] = tag_set2.dout[p];
					//sysc_logfile <<"Tag for read:" << tag.dout[p] <<endl;
					if(temptag[p][0] == (servaddr[p]&~0x3FF)){	//present in cache
					        set = (set + 1) % 2;
						out_ready[p] = true;
						deassertoutput[p] = true;
						out_state[p] = state_set1.dout[p].read();
						out_token[p] = servaddr[p];
						out_addr[p] = temptag[p][0];
						out_data[p] = data_set1.dout[p].read();
						//sysc_logfile <<"Hit!" << state_set1.dout[p].read() << " " << data_set1.dout[p].read() << endl;
					}
					else if(temptag[p][1] == (servaddr[p]&~0x3FF)){	//present in cache
					        set = (set + 1) % 2;
						out_ready[p] = true;
						deassertoutput[p] = true;
						out_state[p] = state_set2.dout[p].read();
						out_token[p] = servaddr[p];
						out_addr[p] = temptag[p][1];
						out_data[p] = data_set2.dout[p].read();
						//sysc_logfile <<"Hit!" << state_set2.dout[p].read() << " " << data_set2.dout[p].read() << endl;
					}
					
					else{	//miss
						out_ready[p] = true;
						deassertoutput[p] = true;
						out_state[p].write(0xff);
						out_token[p] = servaddr[p];
						out_addr[p] = temptag[p][set];
						if (!set)
						  out_data[p] = data_set1.dout[p].read();
						else
						  out_data[p] = data_set2.dout[p].read();
						//sysc_logfile <<"Miss!" << state.dout[p].read() << " " << data.dout[p].read() << endl;
					}
					operation[p] = 0;
					opstate[p] = 0;
					dataena[p] = false;
					stateena[p] = false;
					tagena[p] = false;
					waitdelay[p] = 0;
					//sysc_logfile <<endl <<endl;
					
				}
				else if(operation[p] == 3){	//write probe whatever this is.
					if(opstate[p] == 0)
						cout <<"Help insert in invalid state 0";
				
					else if(opstate[p] == 1){
						tagena[p] = false;
						tagwe[p] = false;
						out_ready[p] = false;
						deassertoutput[p] = false;
						temptag[p][0] = tag_set1.dout[p];
						temptag[p][1] = tag_set2.dout[p];
						if(temptag[p][0] == (servaddr[p]&~0x3FF)){	//present in cache
						        set = (set + 1) % 2;
							stateena[p] = true;
							statewe[p] = true;
							stateaddr[p] = (servaddr[p]&0x3C0)>>6;
							statedin[p] = newstate[p];
							
							dataena[p] = true;
							datawe[p] =  true;
							dataaddr[p] = (servaddr[p]&0x3C0)>>6;
							datadin[p] = newdata[p];
							
							opstate[p] = 2;
							waitdelay[p] = data_set1.Delay;
							port_available[p] = false;
						}
						else if(temptag[p][1] == (servaddr[p]&~0x3FF)){	//present in cache
						        set = (set + 1) % 2;
							stateena[p] = true;
							statewe[p] = true;
							stateaddr[p] = (servaddr[p]&0x3C0)>>6;
							statedin[p] = newstate[p];
							
							dataena[p] = true;
							datawe[p] =  true;
							dataaddr[p] = (servaddr[p]&0x3C0)>>6;
							datadin[p] = newdata[p];
							
							opstate[p] = 2;
							waitdelay[p] = data_set2.Delay;
							port_available[p] = false;
						}

						else{	//miss
							out_ready[p] = true;
							deassertoutput[p] = true;
							out_state[p] = 0xff;
							out_token[p] = servaddr[p];
							out_addr[p] = temptag[p][set];
							waitdelay[p] = 0;
							operation[p] = 0;
							opstate[p] = 0;
						}
						
					}
					else if(opstate[p] == 2){
						stateena[p] = false;
						statewe[p] = false;
						
						dataena[p] = false;
						datawe[p] = false;
						
						out_ready[p] = true;
						deassertoutput[p] = true;

						if(!set)
						  out_state[p] = state_set1.dout[p].read();
						else
						  out_state[p] = state_set2.dout[p].read();						  
						out_token[p] = servaddr[p];
						out_addr[p] = temptag[p][set];
						opstate[p] = 0;
						operation[p] = 0;
						waitdelay[p] = 0;
					}
				}
				else if(operation[p] == 4 ){	//only update
					if(opstate[p] == 0)
						cout <<"Help update in invalid state 0";
					else if(opstate[p] == 1){
						tagena[p] = false;
						tagwe[p] = false;
						out_ready[p] = false;
						deassertoutput[p] = false;
						temptag[p][0] = tag_set1.dout[p].read();
						temptag[p][1] = tag_set2.dout[p].read();
						if(temptag[p][0] == (servaddr[p]&~0x3FF)){	//present in cache
							stateena[p] = true;
							statewe[p] = true;
							stateaddr[p] = (servaddr[p]&0x3C0)>>6;
							statedin[p] = newstate[p];
							opstate[p] = 2;
							waitdelay[p] = data_set1.Delay;
							port_available[p] = false;
						}
						else if(temptag[p][1] == (servaddr[p]&~0x3FF)){	//present in cache
							stateena[p] = true;
							statewe[p] = true;
							stateaddr[p] = (servaddr[p]&0x3C0)>>6;
							statedin[p] = newstate[p];
							opstate[p] = 2;
							waitdelay[p] = data_set2.Delay;
							port_available[p] = false;
						}
						else{	//miss
							out_ready[p] = true;
							deassertoutput[p] = true;
							out_state[p] = 0xff;
							out_token[p] = servaddr[p];
							out_addr[p] = temptag[p][set];
							waitdelay[p] = 0;
							operation[p] = 0;
							opstate[p] = 0;
						}
						
					}
					else if(opstate[p] == 2){
						stateena[p] = false;
						statewe[p] = false;
						out_ready[p] = true;
						deassertoutput[p] = true;
						if (!set)
						  out_state[p] = state_set1.dout[p].read();
						else
						  out_state[p] = state_set2.dout[p].read();					  
						out_token[p] = servaddr[p];
						out_addr[p] = temptag[p][set];
						opstate[p] = 0;
						waitdelay[p] = 0;
						operation[p] = 0;
					}
				}			
			}
			
			if(in_ena[p] && port_available[p]){
				if(in_is_insert[p] && in_has_data[p] && in_update_state[p]){
					operation[p] = 1;
					opstate[p] = 0;
					if (!set)
					  waitdelay[p] = data_set1.Delay;
					else
					  waitdelay[p] = data_set2.Delay;
					servaddr[p] = in_addr[p];
					newstate[p] = in_new_state[p];
					newdata[p] = in_data[p];
					
					dataena[p] = true;
					dataaddr[p] = (servaddr[p]&0x3C0)>>6;
					datawe[p] = true;
					datadin[p] = newdata[p];
					
					stateena[p] = true;
					stateaddr[p] = (servaddr[p]&0x3C0)>>6;
					statewe[p] = true;
					statedin[p] = newstate[p];
					
					tagena[p] = true;
					tagaddr[p] = (servaddr[p]&0x3C0)>>6;
					tagwe[p] = true;
					tagdin[p] = servaddr[p]&~0x3FF;
					
					port_available[p] = false;
					out_ready[p] = false;
				}
				else if(in_needs_data[p]){
					//sysc_logfile << endl << "Read:" << endl;
					servaddr[p] = in_addr[p];
					if (!set)
					  waitdelay[p] = data_set1.Delay;
					else
					  waitdelay[p] = data_set2.Delay;					  
					operation[p] = 2;
					opstate[p] = 0;
					
					//sysc_logfile <<"Address to serve" << servaddr[p] <<endl;
					
					dataena[p] = true;
					dataaddr[p] = (servaddr[p]&0x3C0)>>6;
					
					stateena[p] = true;
					stateaddr[p] = (servaddr[p]&0x3C0)>>6;
					
					tagena[p] = true;
					tagaddr[p] = (servaddr[p]&0x3C0)>>6;
					
					port_available[p] = false;
					out_ready[p] = false;
				}
				else if(in_has_data[p] && in_update_state[p]){
					operation[p] = 3;
					opstate[p] = 1;
					if (!set)
					  waitdelay[p] = data_set1.Delay;
					else
					  waitdelay[p] = data_set2.Delay;					  
					servaddr[p] = in_addr[p];
					newstate[p] = in_new_state[p];
					newdata[p] = in_data[p];
					
					tagena[p] = true;
					tagaddr[p] = (servaddr[p]&0x3C0)>>6;
					
					port_available[p] = false;
					out_ready[p] = false;
				}
				else if(in_update_state[p]){
					operation[p] = 4;
					opstate[p] = 1;
					if (!set)
					  waitdelay[p] = data_set1.Delay;
					else
					  waitdelay[p] = data_set2.Delay;
					servaddr[p] = in_addr[p];
					newstate[p] = in_new_state[p];
					
					tagena[p] = true;
					tagaddr[p] = (servaddr[p]&0x3C0)>>6;
					
					port_available[p] = false;
					out_ready[p] = false;
				}
			}
		}
	}
	
public:
 CacheProject(const sc_module_name &name): Cache(name), data_set1("Data1"), state_set1("State1"), tag_set1("Tag1"), data_set2("Data2"), state_set2("State2"), tag_set2("Tag2"){

		data_set1.clk(clk);
		state_set1.clk(clk);
		tag_set1.clk(clk);

		data_set2.clk(clk);
		state_set2.clk(clk);
		tag_set2.clk(clk);

		set = 0;

		for(int p=0; p<ports; ++p){
			port_available[p] = true;
			
			data_set1.ena[p](dataena[p]);
			data_set1.addr[p](dataaddr[p]);
			data_set1.we[p](datawe[p]);
			data_set1.din[p](datadin[p]);
			data_set1.dout[p](datadout1[p]);

			data_set2.ena[p](dataena[p]);
			data_set2.addr[p](dataaddr[p]);
			data_set2.we[p](datawe[p]);
			data_set2.din[p](datadin[p]);
			data_set2.dout[p](datadout2[p]);
			
			state_set1.ena[p](stateena[p]);
			state_set1.addr[p](stateaddr[p]);
			state_set1.din[p](statedin[p]);
			state_set1.we[p](statewe[p]);
			state_set1.dout[p](statedout1[p]);
			
			state_set2.ena[p](stateena[p]);
			state_set2.addr[p](stateaddr[p]);
			state_set2.din[p](statedin[p]);
			state_set2.we[p](statewe[p]);
			state_set2.dout[p](statedout2[p]);

			tag_set1.ena[p](tagena[p]);
			tag_set1.addr[p](tagaddr[p]);
			tag_set1.din[p](tagdin[p]);
			tag_set1.we[p](tagwe[p]);
			tag_set1.dout[p](tagdout1[p]);

			tag_set2.ena[p](tagena[p]);
			tag_set2.addr[p](tagaddr[p]);
			tag_set2.din[p](tagdin[p]);
			tag_set2.we[p](tagwe[p]);
			tag_set2.dout[p](tagdout2[p]);

		}
	}
};

#endif
