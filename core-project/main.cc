#include <systemc>
#include "top.h"

using namespace sc_core;
using namespace sc_dt;

int sc_main(int argc, char* argv[]) {
	assert(argc>=2);
	sc_report_handler::set_actions(SC_ID_MORE_THAN_ONE_SIGNAL_DRIVER_, SC_DO_NOTHING);
	Top top("top", argc-1, &argv[1]);

	sc_signal<bool> reset;
	sc_clock clk("clk", clockcycle);
	top.clk(clk);
	top.reset(reset);

	reset = true;
	sc_start(clockcycle);
	reset = false;

	sc_start(clockcycle * 400000000);
	return 0;
}
