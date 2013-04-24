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

	Top(const sc_module_name &name, const char* memfile);
};

#endif
