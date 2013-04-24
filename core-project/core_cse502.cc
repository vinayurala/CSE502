#include <iostream>
using namespace std;

#include "core_cse502.h"

void CoreCSE502::do_reset() {
	Core::do_reset();
}

void CoreCSE502::work() {
	if (reset) return;
}


void fetch()
{
  cout<<"\nIn Fetch\n"<<endl;
  i_op = READ;
  
  
  
}
