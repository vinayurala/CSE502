#include <iostream>

#include "core.h"
#include "syscall.h"

using namespace std;

void Core::do_reset() {
	if (reset) {
		RIP = entry;
		RSP = mem_size - addr_width/8;
		return;
	}
}

int Core::syscall(uint64_t rsp, uint64_t rip) {
	cerr << "SYSCALL RSP=" << hex << rsp << " RIP=" << rip << endl;
}

Core::Core(const sc_module_name &name)
	: sc_module(name)
{
	SC_METHOD(do_reset); sensitive << reset.pos();
	SC_METHOD(work); sensitive << clk.pos();

	/*int fd;
	fd = open("/dev/ptmx", O_RDWR);
	assetr(fd != -1);
	int xterm = fork();
	assert(xterm != -1);
	if (pid == 0) {
		close(f);
	} else {
	}
	*/
}
