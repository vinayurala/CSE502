#ifndef _COMMON_H
#define _COMMON_H

#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <utility>
#include <deque>
#include <queue>
#include <sstream>
#include <bitset>

//#include <stdint.h>

#include "udis86.h"
#include "const.h"

using namespace std;

enum src_type {
  NO_SRC,
  REG,
  IMMED,
  IMUL_1,
  IMUL_2R,
  IMUL_2I,
  IMUL_3,
  LOADMUL
};

extern int scratchreg;
extern int scratchregls;
extern int load_store_reg;
extern long long offsetreg_value;

struct uop
{
  enum src_type src;
  sc_addr address;
  int opcode;
  int reg1;
  long long value1;
  int reg2;
  long long value2;
  int reg3;
  long long value3;
  long long immed;
  int opsize;
};

extern stack<long long>	core_stack;

struct ARF{
	unsigned long long rax;
	unsigned long long rbx;
	unsigned long long rcx;
	unsigned long long rdx;
	unsigned long long rsp;
	unsigned long long rbp;
	unsigned long long rsi;
	unsigned long long rdi;
	unsigned long long r8;
	unsigned long long r9;
	unsigned long long r10;
	unsigned long long r11;
	unsigned long long r12;
	unsigned long long r13;
	unsigned long long r14;
	unsigned long long r15;
  unsigned long long rip;
};

extern ARF regfile;

extern queue<uop> dd_uop_queue;
extern deque<uop> de_uop_queue;
extern queue<uop> ew_uop_queue;
extern bool RIP_jump;

#endif
