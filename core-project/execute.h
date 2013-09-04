#ifndef _EXECUTE_H
#define _EXECUTE_H

#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <utility>
#include <queue>
#include <sstream>

#include "systemc.h"
#include "core.h"
#include "common.h"

using namespace std;

class Execute : public sc_module
{
  typedef Execute SC_CURRENT_USER_MODULE;
  void work();
  void do_reset();
  void do_syscall();
  void do_jump();
  void do_shift();

  int prev_reg1;
  long long prev_value1;
  int prev_reg2;
  long long prev_value2;
  sc_addr expected_addr;
  sc_addr prev_addr;

  bool rip_changed;
  bool firstrun;

  uop Op;

  enum State 
  {
    STATE_NORMAL,
    STATE_READ,
    STATE_USESCRATCHREGVALUE,
    STATE_CLEAR
  };

  int state;
  int port;
  int cyclecount;

  long long stackpointer;



  public:
  
  sc_in<bool>         clk;
  sc_in<bool>         clear;
  sc_in<bool>         reset;

  sc_in<bool>         in_ready;
  sc_out<bool>        out_ready;
  sc_out<bool>        clear_out;
  // sc_out<bool>        stahp;
  
  sc_out<mem_op>      d_op[d_ports];
  sc_out<int>         d_tagin[d_ports];
  sc_out<sc_addr>     d_addr[d_ports];

  sc_out<sc_data>     d_dout[d_ports];
  sc_in<bool>         d_ready[d_ports];
  sc_in<int>	        d_tagout[d_ports];
  sc_in<sc_data>      d_data[d_ports];
	
  //Signals from Writeback for branches
  sc_out<bool>         change_RIP;
  sc_out<sc_addr>      new_RIP;
  
  // Execute(const sc_module_name &name, CoreCSE502 *coreaddr): sc_module(name)
  Execute(const sc_module_name &name): sc_module(name)
  {
	  SC_METHOD(do_reset); sensitive << reset.pos();
	  SC_METHOD(work); sensitive << clk.pos();
    // this->core = coreaddr;

    // sc_trace(wf, this.in_ready, "a");
    // sc_trace(wf, this.out_ready, "b");
    // sc_trace(wf, this.clear, "c");

    firstrun = true;
    state = STATE_NORMAL;
    port = 0;
    prev_reg1 = 0;
    prev_reg2 = 0;
    prev_value2 = 0;
    prev_value1 = 0;
    prev_addr = 0;
    cyclecount = 0;
  }

};

#endif
