#ifndef _WRITEBACK_H
#define _WRITEBACK_H

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

class Writeback : public sc_module
{
  typedef Writeback SC_CURRENT_USER_MODULE;
  
  void work();
  void do_reset();
  
  public:
  
  sc_in<bool>         clk;
  sc_in<bool>         reset;
  sc_in<bool>         clear;
  
  sc_in<bool>         in_ready;

  int                 cyclecount;

 Writeback(const sc_module_name &name): sc_module(name)
  {
    SC_METHOD(do_reset); sensitive << reset.pos();
    SC_METHOD(work); sensitive << clk.pos();
    cyclecount = 0;
  }

};

#endif