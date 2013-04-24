#!/bin/bash -x

NAME=prog1

for i in *.s; do
	as -o ${i%.s}.o $i
done
ld -static -o $NAME *.o
objdump -D $NAME
