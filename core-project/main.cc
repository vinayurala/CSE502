#include <systemc>
#include "top.h"

using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char *argv[]) {
	assert(argc==2);
	Top top("top", argv[1]);

	sc_signal<bool> reset;
	sc_clock clk("clk", clockcycle);
	top.clk(clk);
	top.reset(reset);

	reset = true;
	sc_start(clockcycle);
	reset = false;

	sc_start(clockcycle * 10000);
	return 0;
}
