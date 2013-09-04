	.file	"prog2.bc"
	.text
	.globl	OutDig
	.type	OutDig,@function
OutDig:                                 # @OutDig
	.cfi_startproc
# BB#0:                                 # %entry
	addq	$48, %rdi
	jmp	putchar                 # TAILCALL
.Ltmp0:
	.size	OutDig, .Ltmp0-OutDig
	.cfi_endproc

	.globl	PrintVal
	.type	PrintVal,@function
PrintVal:                               # @PrintVal
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset %rbx, -16
	movq	%rdi, %rbx
	cmpq	$10, %rbx
	jl	.LBB1_2
# BB#1:                                 # %if.then
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	leaq	(%rdx,%rax), %rdi
	callq	PrintVal
.LBB1_2:                                # %if.end
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	negq	%rax
	leaq	48(%rbx,%rax), %rdi
	popq	%rbx
	jmp	putchar                 # TAILCALL
.Ltmp5:
	.size	PrintVal, .Ltmp5-PrintVal
	.cfi_endproc

	.globl	PrintShort
	.type	PrintShort,@function
PrintShort:                             # @PrintShort
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%r14
.Ltmp9:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp10:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp11:
	.cfi_def_cfa_offset 32
.Ltmp12:
	.cfi_offset %rbx, -24
.Ltmp13:
	.cfi_offset %r14, -16
	movq	%rdi, %r14
	movabsq	$7378697629483820647, %rsi # imm = 0x6666666666666667
	movq	%r14, %rax
	imulq	%rsi
	movq	%rdx, %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$2, %rbx
	addq	%rax, %rbx
	movq	%rbx, %rax
	imulq	%rsi
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	movq	%rbx, %rcx
	subq	%rax, %rcx
	leaq	48(%rcx), %rdi
	callq	putchar
	shlq	$1, %rbx
	leaq	(%rbx,%rbx,4), %rax
	negq	%rax
	leaq	48(%r14,%rax), %rdi
	callq	putchar
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	ret
.Ltmp14:
	.size	PrintShort, .Ltmp14-PrintShort
	.cfi_endproc

	.globl	Print
	.type	Print,@function
Print:                                  # @Print
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%r15
.Ltmp21:
	.cfi_def_cfa_offset 16
	pushq	%r14
.Ltmp22:
	.cfi_def_cfa_offset 24
	pushq	%r13
.Ltmp23:
	.cfi_def_cfa_offset 32
	pushq	%r12
.Ltmp24:
	.cfi_def_cfa_offset 40
	pushq	%rbx
.Ltmp25:
	.cfi_def_cfa_offset 48
.Ltmp26:
	.cfi_offset %rbx, -48
.Ltmp27:
	.cfi_offset %r12, -40
.Ltmp28:
	.cfi_offset %r13, -32
.Ltmp29:
	.cfi_offset %r14, -24
.Ltmp30:
	.cfi_offset %r15, -16
	movq	%rdi, %r14
	movabsq	$51, %rdi
	callq	putchar
	movabsq	$46, %rdi
	callq	putchar
	cmpq	$2, size(%rip)
	jl	.LBB3_3
# BB#1:
	movabsq	$1, %r12
	movabsq	$7378697629483820647, %r13 # imm = 0x6666666666666667
.LBB3_2:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	movq	(%r14,%r12,8), %r15
	movq	%r15, %rax
	imulq	%r13
	movq	%rdx, %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$2, %rbx
	addq	%rax, %rbx
	movq	%rbx, %rax
	imulq	%r13
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	movq	%rbx, %rcx
	subq	%rax, %rcx
	leaq	48(%rcx), %rdi
	callq	putchar
	shlq	$1, %rbx
	leaq	(%rbx,%rbx,4), %rax
	negq	%rax
	leaq	48(%r15,%rax), %rdi
	callq	putchar
	incq	%r12
	cmpq	size(%rip), %r12
	jl	.LBB3_2
.LBB3_3:                                # %for.end
	movabsq	$10, %rdi
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	jmp	putchar                 # TAILCALL
.Ltmp31:
	.size	Print, .Ltmp31-Print
	.cfi_endproc

	.globl	arctan
	.type	arctan,@function
arctan:                                 # @arctan
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%r14
.Ltmp35:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp36:
	.cfi_def_cfa_offset 24
.Ltmp37:
	.cfi_offset %rbx, -24
.Ltmp38:
	.cfi_offset %r14, -16
	movq	%rdx, %r8
	movq	%rdi, %rcx
	movq	powers(%rip), %r9
	movq	size(%rip), %rax
	testq	%rax, %rax
	jle	.LBB4_3
# BB#1:
	xorq	%rdx, %rdx
.LBB4_2:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	movq	$0, (%r9,%rdx,8)
	incq	%rdx
	movq	size(%rip), %rax
	cmpq	%rax, %rdx
	jl	.LBB4_2
.LBB4_3:                                # %for.end
	imulq	%rsi, %rcx
	xorq	%rbx, %rbx
	imulq	%rsi, %rsi
	movabsq	$1, %r10
	movq	term(%rip), %r11
	movq	pi(%rip), %r14
.LBB4_4:                                # %while.cond.outer
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB4_5 Depth 2
                                        #     Child Loop BB4_7 Depth 2
                                        #     Child Loop BB4_12 Depth 2
                                        #     Child Loop BB4_9 Depth 2
                                        #     Child Loop BB4_14 Depth 2
                                        #     Child Loop BB4_17 Depth 2
	cmpq	%rax, %rbx
	movq	%rbx, %rdi
	jge	.LBB4_6
.LBB4_5:                                # %for.body4
                                        #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	addq	(%r9,%rdi,8), %rcx
	movq	%rcx, %rax
	cqto
	idivq	%rsi
	movq	%rax, (%r9,%rdi,8)
	imulq	%rsi, %rax
	subq	%rax, %rcx
	imulq	$100, %rcx, %rcx
	incq	%rdi
	movq	size(%rip), %rax
	cmpq	%rax, %rdi
	jl	.LBB4_5
.LBB4_6:                                # %for.cond13.loopexit
                                        #   in Loop: Header=BB4_4 Depth=1
	xorq	%rcx, %rcx
	cmpq	%rax, %rbx
	movq	%rbx, %rdi
	jge	.LBB4_8
.LBB4_7:                                # %for.body15
                                        #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	addq	(%r9,%rdi,8), %rcx
	movq	%rcx, %rax
	cqto
	idivq	%r10
	movq	%rax, (%r11,%rdi,8)
	imulq	%r10, %rax
	subq	%rax, %rcx
	imulq	$100, %rcx, %rcx
	incq	%rdi
	movq	size(%rip), %rax
	cmpq	%rax, %rdi
	jl	.LBB4_7
.LBB4_8:                                # %for.end26
                                        #   in Loop: Header=BB4_4 Depth=1
	xorq	%rcx, %rcx
	testq	%r8, %r8
	jg	.LBB4_9
# BB#11:                                # %for.cond44.preheader
                                        #   in Loop: Header=BB4_4 Depth=1
	testq	%rax, %rax
	jle	.LBB4_13
.LBB4_12:                               # %for.body46
                                        #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	-8(%r14,%rax,8), %rdx
	subq	-8(%r11,%rax,8), %rdx
	movq	%rdx, %rdi
	subq	%rcx, %rdi
	addq	$100, %rdi
	subq	%rcx, %rdx
	cmovnsq	%rdx, %rdi
	movq	%rdi, -8(%r14,%rax,8)
	shrq	$63, %rdx
	decq	%rax
	testq	%rax, %rax
	movq	%rdx, %rcx
	jg	.LBB4_12
	jmp	.LBB4_13
.LBB4_10:                               # %for.body31
                                        #   in Loop: Header=BB4_9 Depth=2
	addq	-8(%r14,%rax,8), %rcx
	movq	-8(%r11,%rax,8), %rdi
	leaq	-100(%rdi,%rcx), %rdx
	addq	%rdi, %rcx
	cmpq	$99, %rcx
	cmovgq	%rdx, %rcx
	movq	%rcx, -8(%r14,%rax,8)
	jg GREATER
	movq $0, %rcx
	jmp NOTGREATER
GREATER:
	movq $1, %rcx
NOTGREATER:
	decq	%rax
.LBB4_9:                                # %for.cond29.preheader
                                        #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	testq	%rax, %rax
	jg	.LBB4_10
.LBB4_13:                               # %if.end59
                                        #   in Loop: Header=BB4_4 Depth=1
	addq	$2, %r10
	negq	%r8
	movq	size(%rip), %rax
	movq	%rbx, %rcx
.LBB4_14:                               # %for.cond62
                                        #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpq	%rax, %rcx
	jge	.LBB4_18
# BB#15:                                # %for.body64
                                        #   in Loop: Header=BB4_14 Depth=2
	cmpq	$0, (%r9,%rcx,8)
	leaq	1(%rcx), %rcx
	je	.LBB4_14
# BB#16:                                # %while.cond74.loopexit
                                        #   in Loop: Header=BB4_4 Depth=1
	decq	%rbx
.LBB4_17:                               # %while.cond74
                                        #   Parent Loop BB4_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	xorq	%rcx, %rcx
	cmpq	$0, 8(%r9,%rbx,8)
	leaq	1(%rbx), %rbx
	je	.LBB4_17
	jmp	.LBB4_4
.LBB4_18:                               # %while.cond.loopexit
	popq	%rbx
	popq	%r14
	ret
.Ltmp39:
	.size	arctan, .Ltmp39-arctan
	.cfi_endproc

	.globl	_main
	.type	_main,@function
_main:                                  # @_main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp47:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp48:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp49:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp50:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp51:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp52:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp53:
	.cfi_def_cfa_offset 64
.Ltmp54:
	.cfi_offset %rbx, -56
.Ltmp55:
	.cfi_offset %r12, -48
.Ltmp56:
	.cfi_offset %r13, -40
.Ltmp57:
	.cfi_offset %r14, -32
.Ltmp58:
	.cfi_offset %r15, -24
.Ltmp59:
	.cfi_offset %rbp, -16
	movq	%rsi, %rbx
	cmpq	$2, %rdi
	je	.LBB5_2
# BB#1:                                 # %if.then
	movabsq	$.L.str, %rdi
	callq	puts
	movabsq	$1, %rdi
	callq	llexit
.LBB5_2:                                # %if.end
	movq	8(%rbx), %rdi
	callq	atol
	movq	%rax, size(%rip)
	testq	%rax, %rax
	jg	.LBB5_4
# BB#3:                                 # %if.then3
	movabsq	$.L.str1, %rdi
	callq	puts
	movabsq	$1, %rdi
	callq	llexit
	movq	size(%rip), %rax
.LBB5_4:                                # %if.end5
	leaq	1(%rax), %rdx
	shrq	$63, %rdx
	leaq	1(%rax,%rdx), %rax
	sarq	%rax
	leaq	1(%rax), %rbp
	movq	%rbp, size(%rip)
	leaq	8(,%rax,8), %rbx
	movq	%rbx, %rdi
	callq	malloc
	movq	%rax, %r14
	movq	%r14, pi(%rip)
	movq	%rbx, %rdi
	callq	malloc
	movq	%rax, %r15
	movq	%r15, powers(%rip)
	movq	%rbx, %rdi
	callq	malloc
	movq	%rax, term(%rip)
	testq	%r14, %r14
	je	.LBB5_7
# BB#5:                                 # %if.end5
	testq	%r15, %r15
	je	.LBB5_7
# BB#6:                                 # %if.end5
	testq	%rax, %rax
	jne	.LBB5_8
.LBB5_7:                                # %if.then16
	movabsq	$.L.str2, %rdi
	callq	puts
	movabsq	$1, %rdi
	callq	llexit
	movq	size(%rip), %rbp
.LBB5_8:                                # %for.cond.preheader
	testq	%rbp, %rbp
	jle	.LBB5_11
# BB#9:                                 # %for.body.lr.ph
	xorq	%rax, %rax
	movq	pi(%rip), %rcx
.LBB5_10:                               # %for.body
                                        # =>This Inner Loop Header: Depth=1
	movq	$0, (%rcx,%rax,8)
	incq	%rax
	cmpq	size(%rip), %rax
	jl	.LBB5_10
.LBB5_11:                               # %for.end
	xorq	%rdi, %rdi
	callq	time
	movq	%rax, (%rsp)            # 8-byte Spill
	movabsq	$1, %r13
	movabsq	$16, %rdi
	movabsq	$5, %rsi
	movabsq	$1, %rdx
	callq	arctan
	movabsq	$4, %rdi
	movabsq	$239, %rsi
	movq	$-1, %rdx
	callq	arctan
	xorq	%rdi, %rdi
	callq	time
	movq	%rax, %r15
	movq	pi(%rip), %rbp
	movabsq	$51, %rdi
	callq	putchar
	movabsq	$46, %rdi
	callq	putchar
	cmpq	$2, size(%rip)
	jl	.LBB5_14
# BB#12:
	movabsq	$7378697629483820647, %r14 # imm = 0x6666666666666667
.LBB5_13:                               # %for.body.i
                                        # =>This Inner Loop Header: Depth=1
	movq	(%rbp,%r13,8), %r12
	movq	%r12, %rax
	imulq	%r14
	movq	%rdx, %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$2, %rbx
	addq	%rax, %rbx
	movq	%rbx, %rax
	imulq	%r14
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	movq	%rbx, %rcx
	subq	%rax, %rcx
	leaq	48(%rcx), %rdi
	callq	putchar
	shlq	$1, %rbx
	leaq	(%rbx,%rbx,4), %rax
	negq	%rax
	leaq	48(%r12,%rax), %rdi
	callq	putchar
	incq	%r13
	cmpq	size(%rip), %r13
	jl	.LBB5_13
.LBB5_14:                               # %Print.exit
	movabsq	$10, %rdi
	callq	putchar
	movabsq	$.L.str3, %rdi
	callq	puts
	subq	(%rsp), %r15            # 8-byte Folded Reload
	movq	%r15, %rdi
	callq	PrintVal
	movabsq	$.L.str4, %rdi
	callq	puts
	xorq	%rax, %rax
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	ret
.Ltmp60:
	.size	_main, .Ltmp60-_main
	.cfi_endproc

	.type	size,@object            # @size
	.comm	size,8,8
	.type	powers,@object          # @powers
	.comm	powers,8,8
	.type	term,@object            # @term
	.comm	term,8,8
	.type	pi,@object              # @pi
	.comm	pi,8,8
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "Syntax: ./prog2 <number>   - <number> indicates the number of digits to compute\n"
	.size	.L.str, 81

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "Invalid argument - need <number>\n"
	.size	.L.str1, 34

	.type	.L.str2,@object         # @.str2
.L.str2:
	.asciz	 "Unable to allocate enough memory.\n"
	.size	.L.str2, 35

	.type	.L.str3,@object         # @.str3
.L.str3:
	.asciz	 "Calculation time "
	.size	.L.str3, 18

	.type	.L.str4,@object         # @.str4
.L.str4:
	.asciz	 " cycles\n"
	.size	.L.str4, 9


	.section	".note.GNU-stack","",@progbits
