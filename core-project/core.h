#ifndef _CORE_H
#define _CORE_H

#include "const.h"

using namespace sc_core;
using namespace sc_dt;

class Core : public sc_module
{
	typedef Core SC_CURRENT_USER_MODULE;

protected:
	sc_addr RIP, RSP;

	virtual void do_reset();
	virtual void work() = 0;

	int syscall(uint64_t rsp, uint64_t rip);

public:
	sc_in<bool>        clk;
	sc_in<bool>        reset;

	sc_signal<mem_op>  i_op[i_ports];
	sc_signal<int>     i_tagin[i_ports];
	sc_signal<sc_addr> i_addr[i_ports];
	sc_in<bool>        i_ready[i_ports];
	sc_in<int>         i_tagout[i_ports];
	sc_in<sc_inst>     i_data[i_ports];
	sc_signal<mem_op>  d_op[d_ports];
	sc_signal<int>     d_tagin[d_ports];
	sc_signal<sc_addr> d_addr[d_ports];
	sc_in<bool>        d_ready[d_ports];
	sc_in<int>         d_tagout[d_ports];
	sc_inout<sc_data>  d_data[d_ports];

	Core(const sc_module_name &name);
};

#endif
