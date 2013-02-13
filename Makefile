COMPILER = gcc
CCFLAGS1 = -g
CCFLAGS2 = -lrt
obj-m := hw1.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

mod:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clock:
	${COMPILER} ${CCFLAGS1} hw1_clock.c ${CCFLAGS2} -o hw1_clock

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf hw1_clock