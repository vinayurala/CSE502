#!/bin/bash -x

NAME=prog2
PATH=/scratch/aakshintala/llvm/build/Debug+Asserts/bin:$PATH

CPU=CSE502
#CPU=hammer

as -o crt1.o crt1.s
for c in *.c; do
	clang -g -Wno-main-return-type -emit-llvm -nobuiltininc -msoft-float -O3 -S -c -o ${c%.c}.bc $c
	#llc -march=x86-64 -mcpu=$CPU -O3 ${c%.c}.bc -o ${c%.c}.S
	sed -i'' -e '/align	16/d' ${c%.c}.S
	as -g -o ${c%.c}.o ${c%.c}.S
done
ld -static -o $NAME *.o
#objdump -D $NAME
