#ifndef _CORE_CSE502_H
#define _CORE_CSE502_H

#include "core.h"
#include <cstdlib>

class CoreCSE502 : public Core {
	typedef Core SC_CURRENT_USER_MODULE;

	virtual void do_reset();
	virtual void work();

public:
	CoreCSE502(const sc_module_name& name)
		:	Core(name)
	{ }
};

#define assert(x)				\
  do { if (!(x)) {cout<<"\nAssertion failure: %s\n"<<#x; exit(-1); }  } while (0)


#endif
