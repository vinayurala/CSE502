#include <iostream>

#include "core.h"
#include "syscall.h"

using namespace std;

void Core::do_reset() {
	if (reset) {
		RIP = entry;
		RSP = stack_base;
		return;
	}
}


int Core::syscall(uint64_t rsp, uint64_t rip
	,	uint64_t n
	,	uint64_t a0
	,	uint64_t a1
	,	uint64_t a2
	,	uint64_t a3
	,	uint64_t a4
	,	uint64_t a5
) {
	switch(n) {
	case 1: // write
		return __syscall(n, a0, mem_base+a1, a2);
	case 12: // brk
		if (brk_val < a0) brk_val = a0;
		return brk_val;
	case 16: // ioctl
		// WARNING: ignored
		return 0;
	case 20: // writev
		assert(0);
		return 0;
	case 60: // exit
		cerr << endl << "[ target application called 'exit()', executed in " << std::dec << sc_time_stamp()/clockcycle << " cycles ]" << endl;
		sc_stop();
		return 0;
	case 228: // clock_gettime
		*(uint64_t*)(mem_base + a1+0) = sc_time_stamp().value();
		*(long long*)(mem_base + a1+8) = 0;
		return 0;
	default:
		cerr << "unsupported system call " << dec << n << endl;
		assert(0);
	}
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
