#ifndef _CONST_H
#define _CONST_H

#include <systemc>
#include <inttypes.h>
#include "sc_enum_trace.h"

static const int i_ports = 1;
static const int d_ports = 1;

const long mem_size = 64*1024*1024;
const unsigned long long mem_base = 0x4000000000;
const unsigned long long stack_base = mem_size - 1024;

static const sc_core::sc_time clockcycle(500, sc_core::SC_PS);
static const sc_core::sc_time ns(1, sc_core::SC_NS);

static const int addr_width = 64;

extern uint64_t entry;
extern uint64_t brk_val;

typedef sc_dt::sc_uint<addr_width> sc_addr;
typedef sc_dt::sc_bv<16*8> sc_inst;
typedef sc_dt::sc_uint< 8*8> sc_data;

enum mem_op {
	NONE
,	READ
,	WRITE
};

#endif
