#ifndef _DECODER_H
#define _DECODER_H

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

class Decoder : public sc_module
{
  typedef Decoder SC_CURRENT_USER_MODULE;
	
  //Local flags

  void work();
  void do_reset();
  
  public:
  
  sc_in<bool>         clk;
  sc_in<bool>         reset;
  sc_in<bool>         clear;
  
  sc_in<bool>         in_ready;
  sc_out<bool>        out_ready;

  sc_in<sc_inst>      in_data;
  sc_in<sc_addr>      in_addr;
  sc_in<uint64_t>      in_alignedaddr;

  bool reset_flag;
  string rem_string;
  bool first_run;
  sc_addr last_good_addr;
  
 Decoder(const sc_module_name &name): sc_module(name)
  {
    SC_METHOD(do_reset); sensitive << reset.pos();
    SC_METHOD(work); sensitive << clk.pos();
    first_run = true;
  }

  void decode_opcodes(sc_inst);
  void crack_opcodes(queue<ud_t>);
  void clear_struct(struct uop *);
  uint64_t sign_extend(long long, int);
  string bin2hex(string);
  void build_byte_stack(string);
  void print_uops(queue<uop>);
  void push2q(int, int, int, int, uint64_t, int);
  
  static int byte_seek_ptr;
  static string byte_stream;
  static int stream_len;
  
  static int input_hook(ud_t *);
 
};
#endif
