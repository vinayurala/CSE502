#include "fetch.h"
// #define DEBUG
// #define DEBUG1

int Fetch::cyclecount = 0;

void Fetch::do_reset()
{
   if(reset)
     reset_flag = true;
   regfile.rsp = RSP;
}

void Fetch::work()
{
  cyclecount++;
  // cout<<"Fetch "<<cyclecount<<endl;
  if (reset)
    return;
  
  if (clear)      //line needs to be set hi for each cycle that the pipeline is stalled for
  {
    for(int port=0; port<i_ports; ++port) {
      i_op[port] = NONE;
      i_tagin[port] = 0;
      i_addr[port] = (sc_addr)0;
      
      out_data[port] =  (sc_inst)0;
      out_addr[port] =  (sc_addr)0;
      out_ready[port] =  false;
      prev_tag[port] = 0;
    }
    // return;
  } 
  
  sc_addr tempRIP = RIP;
  if(RIP % 16 != 0)
    tempRIP = RIP & ~15;  //Bottom 4 bits set to zero. Memory requires this.

  if(change_RIP) {        // sent from writeback/execute/decode to change the RIP value
    RIP = new_RIP;
    tempRIP = RIP;
    if(RIP % 16 != 0)
      tempRIP = RIP & ~15;
    for(int port=0; port<i_ports; ++port)
      prev_tag[port] = (sc_addr)0;
    i_op[0] = READ;        // requesting data from i_cache
    i_tagin[0] = tempRIP;
    i_addr[0] = tempRIP;
    prev_tag[0] = RIP;
    #ifdef DEBUG
      cout<<"got this RIP from execute: "<<hex<<RIP<<" cc: "<<cyclecount<<endl;
      cout<<"\nRIP sent to cache:"<<hex<<tempRIP<<endl;
    #endif
    RIP_jump = true;
    return;
  }

  #ifdef DEBUG
  cout<<"\ntempRIP = "<<hex<<tempRIP<<dec<<" prev_tag "<<hex<<prev_tag[0]<<dec<<endl;
  cout <<cyclecount<<endl;
  #endif

  for(int port=0; port<i_ports; ++port) {
    int bufferindex = 0;
    out_ready[port] = false;

    if(i_ready[port]){     //reply from i_cache
      for(int p=0; p<i_ports; ++p) {
        if(i_tagout[port] == (prev_tag[p] & ~15)) {
          out_data[bufferindex] = i_data[port];
          if(prev_tag[p] != i_tagout[port])            //1st run misalignment
            out_data[bufferindex] = i_data[port].read().range((127-(prev_tag[p] - i_tagout[port])*8),0);
          #ifdef DEBUG1
            cout <<cyclecount<<endl;
            cout<<"\nprev_tag "<<prev_tag[p]<<" itagout[port] "<<i_tagout[port]<<endl;
            cout<<hex<<"\ni_tagout[port] = "<<i_tagout[port]<<dec<<endl;
            cout<<"\nout_data = "<<i_data[port]<<endl;
          #endif
          out_addr[bufferindex] = i_tagout[port].read();
          out_ready[bufferindex] = true;
          out_alignedaddr[bufferindex] = prev_tag[p] - i_tagout[port];
          prev_tag[p] = 0;
          bufferindex++;
          RIP = tempRIP + 16;
          i_op[port] = READ;        // requesting data from i_cache
          i_tagin[port] = RIP;
          i_addr[port] = RIP;
          prev_tag[p] = RIP;
          #ifdef DEBUG
            cout<<"\nRIP sent to cache:"<<hex<<RIP<<endl;
          #endif
        } 
      }
    }
    if(firstRunFlag){
      i_op[port] = READ;        // requesting data from i_cache
      i_tagin[port] = tempRIP;
      i_addr[port] = tempRIP;
      prev_tag[port] = RIP;
      regfile.rsp = RSP;
      firstRunFlag = false;
    }
  }
  return;
}
