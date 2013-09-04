#include <iostream>
using namespace std;

#include "core_cse502.h"

void CoreCSE502::do_reset() {
	Core::do_reset();
	fetch.RIP = RIP;
	fetch.RSP = RSP;
	regfile.rsp = RSP;
}

void CoreCSE502::work() {
	if (reset) return;
}