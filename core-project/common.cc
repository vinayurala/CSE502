#include "common.h"

using namespace std;

stack<long long> core_stack;

ARF regfile = { 0 };

queue<uop> dd_uop_queue;

deque<uop> de_uop_queue;

queue<uop> ew_uop_queue;

bool RIP_jump = false;

int scratchreg = 999;
int scratchregls = 888;
int load_store_reg = 666;
long long offsetreg_value = 0;
