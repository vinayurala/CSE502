COMPILER = gcc
CCFLAGS1 = -g
CCFLAGS2 = -lrt
obj-m := hw1.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

mod:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf hw1_clock