#ifndef _FETCH_H
#define _FETCH_H

#include <iostream>

#include "systemc.h"
#include "core.h"
#include "common.h"

using namespace std;

class Fetch : public sc_module
{
  typedef Fetch SC_CURRENT_USER_MODULE;
	
  //Local flags
  bool reset_flag;
  sc_addr prev_tag[i_ports];
  bool firstRunFlag;
  
  void work();
  void do_reset();
  static int cyclecount;

  public:
  sc_addr RIP, RSP;
  
  sc_in<bool>         clk;
  sc_in<bool>         reset;
  sc_in<bool>         clear;
  
  sc_out<mem_op>      i_op[i_ports];
  sc_out<int>         i_tagin[i_ports];
  sc_out<sc_addr>     i_addr[i_ports];
  sc_in<bool>         i_ready[i_ports];
  sc_in<int>          i_tagout[i_ports];
  sc_in<sc_inst>      i_data[i_ports];
  
  //For decode
  sc_out<sc_inst>     out_data[i_ports];
  sc_out<sc_addr>     out_addr[i_ports];
  sc_out<uint64_t>     out_alignedaddr[i_ports];
  sc_out<bool>	      out_ready[i_ports];
	
  //Signals from Writeback for branches
  sc_in<bool>         change_RIP;
  sc_in<sc_addr>      new_RIP;
	  
 Fetch(const sc_module_name &name): sc_module(name)
  {
    SC_METHOD(do_reset); sensitive << reset.pos();
    SC_METHOD(work); sensitive << clk.pos();
    firstRunFlag = true;
    regfile.rsp = RSP;
  }

};

#endif
