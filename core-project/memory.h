#ifndef _MEMORY_H
#define _MEMORY_H

#include <systemc>
#include <iostream>

#include "delaybucket.h"
#include "lruset.h"

#include "const.h"

using namespace sc_core;
using namespace sc_dt;
using namespace std;

template<int i_ports, int d_ports>
class Memory : public sc_module
{
	typedef Memory SC_CURRENT_USER_MODULE;

	enum dirty { CLEAN, DIRTY };
	typedef lruset<sc_addr,dirty> Cache;
	Cache L1i, L1d, L2;

	char* mem;
	void mem_init(const char* filename);
	sc_inst mem_i_read(const sc_addr& addr);
	sc_data mem_d_read(const sc_addr& addr);
	sc_data mem_d_write(const sc_addr& addr, const sc_data& data);

	typedef delaybucket<pair<int, sc_addr> > cache_delaybucket;
	cache_delaybucket i_resp, d_resp;

	void work();

public:
	sc_in<bool>				 clk;
	sc_in<bool>				 reset;

	sc_in<mem_op>      i_op[i_ports];
	sc_in<int>         i_tagin[i_ports];
	sc_in<sc_addr>     i_addr[i_ports];
	sc_signal<bool>    i_ready[i_ports];
	sc_signal<int>     i_tagout[i_ports];
	sc_signal<sc_inst> i_data[i_ports];
	sc_in<mem_op>      d_op[d_ports];
	sc_in<int>         d_tagin[d_ports];
	sc_in<sc_addr>     d_addr[d_ports];
	sc_signal<bool>    d_ready[d_ports];
	sc_signal<int>     d_tagout[d_ports];
	sc_signal<sc_data> d_data[d_ports];

	Memory(const sc_module_name &name, const char* filename);
};

#endif
