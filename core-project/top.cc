#include "top.h"
#include "core_cse502.h"

Top::Top(const sc_module_name &name, const char* memfile)
	: sc_module(name)
	,	core(new CoreCSE502("core"))
	,	mem("mem", memfile)
{
	core->clk(clk);
	core->reset(reset);
	mem.clk(clk);
	mem.reset(reset);

	for(int port=0; port<i_ports; ++port) {
		mem.i_op[port](core->i_op[port]);
		mem.i_tagin[port](core->i_tagin[port]);
		mem.i_addr[port](core->i_addr[port]);
		core->i_ready[port](mem.i_ready[port]);
		core->i_tagout[port](mem.i_tagout[port]);
		core->i_data[port](mem.i_data[port]);
	}
	for(int port=0; port<d_ports; ++port) {
		mem.d_op[port](core->d_op[port]);
		mem.d_tagin[port](core->d_tagin[port]);
		mem.d_addr[port](core->d_addr[port]);
		core->d_ready[port](mem.d_ready[port]);
		core->d_tagout[port](mem.d_tagout[port]);
		core->d_data[port](mem.d_data[port]);
	}
}
