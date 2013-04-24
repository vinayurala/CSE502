#include <iostream>

#include "systemc.h"

using namespace std;

SC_MODULE (fetch) {
  sc_in_clk         clock;
  sc_in <bool>      ready;
  sc_out<sc_inst>   data_out;
  sc_in <sc_inst>   data_in;
  sc_signal<int>    tag_out;
  

  void fetch_next_line() {
    // Code to fetch i-cache line and update RIP
  }

  SC_CTOR(fetch) {
    SC_METHOD(fetch_next_line);
    // connect to ports of memory.cc module
    
  }

};


// int main()
//   {
    
//     cout<<endl;
//     return 0;
//   }
