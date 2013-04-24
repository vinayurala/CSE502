.text
.global _start
_start:
        xor %rbp,%rbp
	mov %rdx, %r9
	mov %rsp,%rdx
	mov %rcx, 16(%rsi)
	mov %r10, %rsp
        andq $-16,%rsp
	mov %rax, %rdi
        mov $m,%rdi
        callq *%rdi
        mov $0x3c,%rax
        syscall
v:      rex64
        gs
        insb (%dx),%es:(%rdi)
        insb (%dx),%es:(%rdi)
        outsl %ds:(%rsi),(%dx)
        and %dh,0x6f(%rdi)
        jb v+0x76
        and %ecx,%fs:(%rdx)
m:      mov $0x1,%rax
        mov $0x1,%rdi
        mov $v,%rsi
        mov $0xd,%rdx
        syscall
        xor %rax,%rax
        retq
