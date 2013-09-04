#ifndef _CORE_CSE502_H
#define _CORE_CSE502_H

#include "fetch.h"
#include "execute.h"
#include "core.h"
#include "decoder.h"
#include "dispatch.h"
#include "common.h"
#include "writeback.h"

using namespace std;

class CoreCSE502 : public Core {
	typedef CoreCSE502 SC_CURRENT_USER_MODULE;

	virtual void do_reset();
	virtual void work();
	
	friend class Fetch;
	friend class Decoder;
	friend class Execute;
	friend class Dispatch;
	friend class Writeback;
	
	Fetch fetch;
	Execute execute;
	Decoder decode;
	Dispatch dispatch;
	Writeback writeback;

	sc_signal<sc_inst>		fd_out_data_sig[i_ports];
	sc_signal<sc_addr>		fd_out_addr_sig[i_ports];
	sc_signal<uint64_t>		fd_out_align_sig[i_ports];
	sc_signal<bool> 		fd_out_ready_sig[i_ports];
	
	sc_signal<bool> 		dd_out_ready_sig;
	sc_signal<bool> 		de_out_ready_sig;
	sc_signal<bool> 		ew_out_ready_sig;
	// sc_signal<bool> 		ed_stahp_sig;


	sc_signal<bool>         change_RIP;
	sc_signal<sc_addr>      new_RIP;

public:
	sc_signal<bool> clear; // need to figure out a way to set this from inside the pipeline as appropriate 

	CoreCSE502(const sc_module_name& name)
		:	Core(name),fetch("Fetch"), execute("Execute"),decode("Decode"),
			dispatch("Dispatch"), writeback("Writeback")
	{ 


		fetch.clk(clk);
		fetch.reset(reset);
		fetch.clear(clear);
		fetch.RIP = RIP;
		fetch.RSP = RSP;
		regfile.rsp = RSP;
		
		decode.clk(clk);
		decode.reset(reset);
		decode.clear(clear);

		dispatch.clk(clk);
		dispatch.reset(reset);
		dispatch.clear(clear);
		// dispatch.stahp(ed_stahp_sig);
		
		execute.clk(clk);
		execute.reset(reset);
		execute.clear(clear);
		execute.clear_out(clear);
		// execute.stahp(ed_stahp_sig);

		writeback.clk(clk);
		writeback.reset(reset);
		writeback.clear(clear);		
		
		for(int port=0; port<i_ports; ++port) {
			fetch.i_op[port](this->i_op[port]);
			fetch.i_tagin[port](this->i_tagin[port]);
			fetch.i_addr[port](this->i_addr[port]);
			fetch.i_ready[port](this->i_ready[port]);
			fetch.i_tagout[port](this->i_tagout[port]);
			fetch.i_data[port](this->i_data[port]);
			fetch.out_data[port](fd_out_data_sig[port]);
			fetch.out_addr[port](fd_out_addr_sig[port]);
			fetch.out_ready[port](fd_out_ready_sig[port]);
			fetch.out_alignedaddr[port](fd_out_align_sig[port]);

			decode.in_alignedaddr(fd_out_align_sig[port]);
			decode.in_data(fd_out_data_sig[port]);
			decode.in_ready(fd_out_ready_sig[port]);
			decode.in_addr(fd_out_addr_sig[port]);

		}
               
		decode.out_ready(dd_out_ready_sig);
		dispatch.in_ready(dd_out_ready_sig);

		dispatch.out_ready(de_out_ready_sig);
		execute.in_ready(de_out_ready_sig);

		execute.out_ready(ew_out_ready_sig);
		writeback.in_ready(ew_out_ready_sig);

		execute.change_RIP(change_RIP);
		fetch.change_RIP(change_RIP);
		execute.new_RIP(new_RIP);
		fetch.new_RIP(new_RIP);

		for(int port=0; port<d_ports; ++port) {
			execute.d_op[port](this->d_op[port]);
			execute.d_tagin[port](this->d_tagin[port]);
			execute.d_addr[port](this->d_addr[port]);
			
			execute.d_ready[port](this->d_ready[port]);
			execute.d_tagout[port](this->d_tagout[port]);
			execute.d_data[port](this->d_data[port]);
			execute.d_dout[port](this->d_dout[port]);
		
		}		
	}
};

#endif
  /* sc_in<bool>         clk; */
  /* sc_in<bool>         reset; */
  /* sc_in<bool>         clear; */
  
  /* sc_out<mem_op>      i_op[i_ports]; */
  /* sc_out<int>         i_tagin[i_ports]; */
  /* sc_out<sc_addr>     i_addr[i_ports]; */
  /* sc_in<bool>         i_ready[i_ports]; */
  /* sc_in<int>          i_tagout[i_ports]; */
  /* sc_in<sc_inst>      i_data[i_ports]; */
  
  /* //For decode */
  /* sc_out<sc_inst>     out_data[i_ports]; */
  /* sc_out<sc_addr>     out_addr[i_ports]; */
  /* sc_out<bool>	      out_ready[i_ports]; */
  /* sc_out<bool>        out_RIP_jump; */
