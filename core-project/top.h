#ifndef _TOP_H
#define _TOP_H

#include <systemc>
#include <iostream>

#include "core.h"
#include "memory.h"

using namespace sc_core;
using namespace sc_dt;

class Top : public sc_module
{
	typedef Top SC_CURRENT_USER_MODULE;

	Core* core;
	Memory<i_ports, d_ports> mem;

	void work() {
		if (reset) return;
	}
public:
	sc_in<bool>				clk;
	sc_in<bool>				reset;

	sc_signal<mem_op>      i_op[i_ports];
	sc_signal<int>         i_tagin[i_ports];
	sc_signal<sc_addr>     i_addr[i_ports];
	sc_signal<bool>        i_ready[i_ports];
	sc_signal<int>         i_tagout[i_ports];
	sc_signal<sc_inst>     i_data[i_ports];
	
	sc_signal<mem_op>      d_op[d_ports];
	sc_signal<int>         d_tagin[d_ports];
	sc_signal<sc_addr>     d_addr[d_ports];
	sc_signal<bool>        d_ready[d_ports];
	sc_signal<int>         d_tagout[d_ports];
	sc_signal<sc_data>     d_data[d_ports];
	sc_signal<sc_data>     d_din[d_ports];

	Top(const sc_module_name &name, int argc, char* argv[]);
};

#endif
