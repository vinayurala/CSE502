	.file	"prog2.bc"
	.file	1 "prog2.c"
	.text
	.globl	OutDig
	.type	OutDig,@function
OutDig:                                 # @OutDig
	.cfi_startproc
.Lfunc_begin0:
	.loc	1 91 0                  # prog2.c:91:0
# BB#0:                                 # %entry
	#DEBUG_VALUE: OutDig:dig <- RDI+0
	.loc	1 92 0 prologue_end     # prog2.c:92:0
	addq	$48, %rdi
.Ltmp0:
	jmp	putchar                 # TAILCALL
.Ltmp1:
.Ltmp2:
	.size	OutDig, .Ltmp2-OutDig
.Lfunc_end0:
	.cfi_endproc

	.globl	PrintVal
	.type	PrintVal,@function
PrintVal:                               # @PrintVal
	.cfi_startproc
.Lfunc_begin1:
	.loc	1 95 0                  # prog2.c:95:0
# BB#0:                                 # %entry
	pushq	%rbx
.Ltmp5:
	.cfi_def_cfa_offset 16
.Ltmp6:
	.cfi_offset %rbx, -16
	#DEBUG_VALUE: PrintVal:val <- RDI+0
	movq	%rdi, %rbx
.Ltmp7:
	#DEBUG_VALUE: PrintVal:val <- RBX+0
	.loc	1 96 0 prologue_end     # prog2.c:96:0
	cmpq	$10, %rbx
	jl	.LBB1_2
# BB#1:                                 # %if.then
	#DEBUG_VALUE: PrintVal:val <- RBX+0
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	leaq	(%rdx,%rax), %rdi
	callq	PrintVal
.LBB1_2:                                # %if.end
.Ltmp8:
	#DEBUG_VALUE: PrintVal:val <- RBX+0
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	.loc	1 97 0                  # prog2.c:97:0
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	negq	%rax
	.loc	1 92 0                  # prog2.c:92:0
.Ltmp9:
	leaq	48(%rbx,%rax), %rdi
	popq	%rbx
.Ltmp10:
	jmp	putchar                 # TAILCALL
.Ltmp11:
.Ltmp12:
	.size	PrintVal, .Ltmp12-PrintVal
.Lfunc_end1:
	.cfi_endproc

	.globl	PrintShort
	.type	PrintShort,@function
PrintShort:                             # @PrintShort
	.cfi_startproc
.Lfunc_begin2:
	.loc	1 102 0                 # prog2.c:102:0
# BB#0:                                 # %entry
	pushq	%r14
.Ltmp16:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp17:
	.cfi_def_cfa_offset 24
	pushq	%rax
.Ltmp18:
	.cfi_def_cfa_offset 32
.Ltmp19:
	.cfi_offset %rbx, -24
.Ltmp20:
	.cfi_offset %r14, -16
	#DEBUG_VALUE: PrintShort:num <- RDI+0
	movq	%rdi, %r14
.Ltmp21:
	#DEBUG_VALUE: x <- 0+0
	#DEBUG_VALUE: PrintShort:num <- R14+0
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	.loc	1 109 0 prologue_end    # prog2.c:109:0
.Ltmp22:
	movq	%r14, %rax
	imulq	%rcx
	movq	%rdx, %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$2, %rbx
	addq	%rax, %rbx
.Ltmp23:
	#DEBUG_VALUE: PrintShort:num <- RBX+0
	.loc	1 108 0                 # prog2.c:108:0
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	movq	%rbx, %rcx
	subq	%rax, %rcx
.Ltmp24:
	#DEBUG_VALUE: OutDig:dig <- RCX+0
	#DEBUG_VALUE: x <- 1+0
	.loc	1 92 0                  # prog2.c:92:0
	leaq	48(%rcx), %rdi
	callq	putchar
.Ltmp25:
	.loc	1 108 0                 # prog2.c:108:0
	shlq	$1, %rbx
.Ltmp26:
	leaq	(%rbx,%rbx,4), %rax
	negq	%rax
.Ltmp27:
	.loc	1 92 0                  # prog2.c:92:0
	leaq	48(%r14,%rax), %rdi
.Ltmp28:
	#DEBUG_VALUE: x <- 0+0
	callq	putchar
.Ltmp29:
	.loc	1 113 0                 # prog2.c:113:0
	addq	$8, %rsp
	popq	%rbx
	popq	%r14
	ret
.Ltmp30:
.Ltmp31:
	.size	PrintShort, .Ltmp31-PrintShort
.Lfunc_end2:
	.cfi_endproc

	.globl	Print
	.type	Print,@function
Print:                                  # @Print
	.cfi_startproc
.Lfunc_begin3:
	.loc	1 116 0                 # prog2.c:116:0
# BB#0:                                 # %entry
	pushq	%r15
.Ltmp37:
	.cfi_def_cfa_offset 16
	pushq	%r14
.Ltmp38:
	.cfi_def_cfa_offset 24
	pushq	%r12
.Ltmp39:
	.cfi_def_cfa_offset 32
	pushq	%rbx
.Ltmp40:
	.cfi_def_cfa_offset 40
	pushq	%rax
.Ltmp41:
	.cfi_def_cfa_offset 48
.Ltmp42:
	.cfi_offset %rbx, -40
.Ltmp43:
	.cfi_offset %r12, -32
.Ltmp44:
	.cfi_offset %r14, -24
.Ltmp45:
	.cfi_offset %r15, -16
	#DEBUG_VALUE: Print:num <- RDI+0
	movq	%rdi, %r14
.Ltmp46:
	#DEBUG_VALUE: Print:num <- R14+0
	movabsq	$51, %rdi
	.loc	1 119 0 prologue_end    # prog2.c:119:0
.Ltmp47:
	callq	putchar
	movabsq	$46, %rdi
	.loc	1 120 0                 # prog2.c:120:0
	callq	putchar
	movabsq	$1, %r12
.Ltmp48:
	#DEBUG_VALUE: x <- 1+0
	.loc	1 121 0                 # prog2.c:121:0
	cmpq	$2, size(%rip)
	jl	.LBB3_2
.LBB3_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
.Ltmp49:
	#DEBUG_VALUE: Print:num <- R14+0
	#DEBUG_VALUE: x <- 1+0
	.loc	1 122 0                 # prog2.c:122:0
	movq	(%r14,%r12,8), %r15
.Ltmp50:
	#DEBUG_VALUE: PrintShort:num <- R15+0
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	.loc	1 109 0                 # prog2.c:109:0
.Ltmp51:
	movq	%r15, %rax
	imulq	%rcx
	movq	%rdx, %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$2, %rbx
	addq	%rax, %rbx
.Ltmp52:
	#DEBUG_VALUE: x <- 0+0
	#DEBUG_VALUE: PrintShort:num <- RBX+0
	.loc	1 108 0                 # prog2.c:108:0
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	movq	%rbx, %rcx
	subq	%rax, %rcx
.Ltmp53:
	#DEBUG_VALUE: OutDig:dig <- RCX+0
	#DEBUG_VALUE: x <- 1+0
	.loc	1 92 0                  # prog2.c:92:0
	leaq	48(%rcx), %rdi
	callq	putchar
.Ltmp54:
	.loc	1 108 0                 # prog2.c:108:0
	shlq	$1, %rbx
.Ltmp55:
	leaq	(%rbx,%rbx,4), %rax
	negq	%rax
	.loc	1 92 0                  # prog2.c:92:0
.Ltmp56:
	leaq	48(%r15,%rax), %rdi
.Ltmp57:
	#DEBUG_VALUE: x <- 0+0
	callq	putchar
.Ltmp58:
	.loc	1 121 0                 # prog2.c:121:0
	incq	%r12
.Ltmp59:
	#DEBUG_VALUE: x <- R12+0
	cmpq	size(%rip), %r12
	jl	.LBB3_1
.Ltmp60:
.LBB3_2:                                # %for.end
	movabsq	$10, %rdi
	.loc	1 123 0                 # prog2.c:123:0
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	jmp	putchar                 # TAILCALL
.Ltmp61:
.Ltmp62:
	.size	Print, .Ltmp62-Print
.Lfunc_end3:
	.cfi_endproc

	.globl	arctan
	.type	arctan,@function
arctan:                                 # @arctan
	.cfi_startproc
.Lfunc_begin4:
	.loc	1 127 0                 # prog2.c:127:0
# BB#0:                                 # %entry
	pushq	%r14
.Ltmp66:
	.cfi_def_cfa_offset 16
	pushq	%rbx
.Ltmp67:
	.cfi_def_cfa_offset 24
.Ltmp68:
	.cfi_offset %rbx, -24
.Ltmp69:
	.cfi_offset %r14, -16
	#DEBUG_VALUE: arctan:multiplier <- RDI+0
	#DEBUG_VALUE: arctan:denom <- RSI+0
	#DEBUG_VALUE: arctan:sign <- RDX+0
.Ltmp70:
	#DEBUG_VALUE: denom2 <- RSI+0
	movq	%rdx, %r8
.Ltmp71:
	#DEBUG_VALUE: x <- 0+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: arctan:sign <- R8+0
	xorq	%rcx, %rcx
	.loc	1 134 0 prologue_end    # prog2.c:134:0
.Ltmp72:
	movq	powers(%rip), %r9
	.loc	1 133 0                 # prog2.c:133:0
	movq	size(%rip), %rax
	testq	%rax, %rax
	jle	.LBB4_2
.LBB4_1:                                # %for.body
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: arctan:multiplier <- RDI+0
	#DEBUG_VALUE: arctan:denom <- RSI+0
	#DEBUG_VALUE: arctan:sign <- R8+0
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: x <- 0+0
	.loc	1 134 0                 # prog2.c:134:0
	movq	$0, (%r9,%rcx,8)
	.loc	1 133 0                 # prog2.c:133:0
	incq	%rcx
.Ltmp73:
	#DEBUG_VALUE: x <- RCX+0
	movq	size(%rip), %rax
	cmpq	%rax, %rcx
	jl	.LBB4_1
.Ltmp74:
.LBB4_2:                                # %for.end
	#DEBUG_VALUE: arctan:multiplier <- RDI+0
	#DEBUG_VALUE: arctan:denom <- RSI+0
	#DEBUG_VALUE: arctan:sign <- R8+0
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	.loc	1 140 0                 # prog2.c:140:0
	imulq	%rsi, %rdi
.Ltmp75:
	#DEBUG_VALUE: adv <- 0+0
	#DEBUG_VALUE: remain <- RDI+0
	xorq	%rbx, %rbx
	.loc	1 137 0                 # prog2.c:137:0
	imulq	%rsi, %rsi
.Ltmp76:
	movabsq	$1, %r10
	.loc	1 183 0                 # prog2.c:183:0
.Ltmp77:
	movq	term(%rip), %r11
	movq	pi(%rip), %r14
.Ltmp78:
.LBB4_3:                                # %while.cond.outer
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB4_4 Depth 2
                                        #     Child Loop BB4_6 Depth 2
                                        #     Child Loop BB4_11 Depth 2
                                        #     Child Loop BB4_10 Depth 2
                                        #     Child Loop BB4_13 Depth 2
                                        #     Child Loop BB4_16 Depth 2
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: x <- RBX+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 143 0                 # prog2.c:143:0
	cmpq	%rax, %rbx
	movq	%rbx, %rcx
	jge	.LBB4_5
.Ltmp79:
.LBB4_4:                                # %for.body4
                                        #   Parent Loop BB4_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 145 0                 # prog2.c:145:0
	addq	(%r9,%rcx,8), %rdi
.Ltmp80:
	#DEBUG_VALUE: temp <- RDI+0
	.loc	1 146 0                 # prog2.c:146:0
	movq	%rdi, %rax
	cqto
	idivq	%rsi
	movq	%rax, (%r9,%rcx,8)
	.loc	1 147 0                 # prog2.c:147:0
	imulq	%rsi, %rax
	subq	%rax, %rdi
.Ltmp81:
	imulq	$100, %rdi, %rdi
.Ltmp82:
	#DEBUG_VALUE: remain <- RDI+0
	.loc	1 143 0                 # prog2.c:143:0
	incq	%rcx
.Ltmp83:
	#DEBUG_VALUE: x <- RCX+0
	movq	size(%rip), %rax
	cmpq	%rax, %rcx
	jl	.LBB4_4
.Ltmp84:
.LBB4_5:                                # %for.cond13.loopexit
                                        #   in Loop: Header=BB4_3 Depth=1
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: adv <- 0+0
	xorq	%rdi, %rdi
	.loc	1 151 0                 # prog2.c:151:0
.Ltmp85:
	cmpq	%rax, %rbx
	movq	%rbx, %rcx
	jge	.LBB4_7
.LBB4_6:                                # %for.body15
                                        #   Parent Loop BB4_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 153 0                 # prog2.c:153:0
.Ltmp86:
	addq	(%r9,%rcx,8), %rdi
.Ltmp87:
	#DEBUG_VALUE: temp <- RDI+0
	.loc	1 154 0                 # prog2.c:154:0
	movq	%rdi, %rax
	cqto
	idivq	%r10
	movq	%rax, (%r11,%rcx,8)
	.loc	1 155 0                 # prog2.c:155:0
	imulq	%r10, %rax
	subq	%rax, %rdi
.Ltmp88:
	imulq	$100, %rdi, %rdi
.Ltmp89:
	#DEBUG_VALUE: remain <- RDI+0
	.loc	1 151 0                 # prog2.c:151:0
	incq	%rcx
.Ltmp90:
	#DEBUG_VALUE: x <- RCX+0
	movq	size(%rip), %rax
	cmpq	%rax, %rcx
	jl	.LBB4_6
.Ltmp91:
.LBB4_7:                                # %for.end26
                                        #   in Loop: Header=BB4_3 Depth=1
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 159 0                 # prog2.c:159:0
	testq	%r8, %r8
.Ltmp92:
	#DEBUG_VALUE: remain <- 0+0
	jle	.LBB4_9
# BB#8:                                 # %for.cond29.preheader
                                        #   in Loop: Header=BB4_3 Depth=1
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	xorq	%rcx, %rcx
	testq	%rax, %rax
	.loc	1 164 0                 # prog2.c:164:0
.Ltmp93:
	jg	.LBB4_10
	jmp	.LBB4_12
.LBB4_10:                               # %for.body31
                                        #   Parent Loop BB4_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 166 0                 # prog2.c:166:0
.Ltmp94:
	addq	-8(%r14,%rax,8), %rcx
	movq	-8(%r11,%rax,8), %rdx
	.loc	1 171 0                 # prog2.c:171:0
.Ltmp95:
	leaq	-100(%rdx,%rcx), %rdi
.Ltmp96:
	#DEBUG_VALUE: sum <- RDI+0
	#DEBUG_VALUE: carry <- 0+0
	.loc	1 166 0                 # prog2.c:166:0
	addq	%rdx, %rcx
.Ltmp97:
	#DEBUG_VALUE: sum <- RCX+0
	.loc	1 168 0                 # prog2.c:168:0
	cmpq	$99, %rcx
	pushfq
	popq	%rdx
	testq	%rdx, %rdx
	cmovneq	%rdi, %rcx
.Ltmp98:
	.loc	1 173 0                 # prog2.c:173:0
	movq	%rcx, -8(%r14,%rax,8)
.Ltmp99:
	.loc	1 164 0                 # prog2.c:164:0
	decq	%rax
	testq	%rax, %rax
	movq	%rdx, %rcx
	jg	.LBB4_10
	jmp	.LBB4_12
.Ltmp100:
.LBB4_9:                                # %for.cond44.preheader
                                        #   in Loop: Header=BB4_3 Depth=1
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	xorq	%rdx, %rdx
	testq	%rax, %rax
	.loc	1 181 0                 # prog2.c:181:0
.Ltmp101:
	jg	.LBB4_11
	jmp	.LBB4_12
.LBB4_11:                               # %for.body46
                                        #   Parent Loop BB4_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 183 0                 # prog2.c:183:0
.Ltmp102:
	movq	-8(%r14,%rax,8), %rcx
	subq	-8(%r11,%rax,8), %rcx
	subq	%rdx, %rcx
.Ltmp103:
	#DEBUG_VALUE: sum <- RCX+0
	.loc	1 188 0                 # prog2.c:188:0
	leaq	100(%rcx), %rdx
.Ltmp104:
	#DEBUG_VALUE: borrow <- 0+0
	#DEBUG_VALUE: sum <- RDX+0
	.loc	1 185 0                 # prog2.c:185:0
	testq	%rcx, %rcx
	pushfq
	popq	%rdi
	testq	%rdi, %rdi
	cmoveq	%rcx, %rdx
.Ltmp105:
	.loc	1 190 0                 # prog2.c:190:0
	movq	%rdx, -8(%r14,%rax,8)
	.loc	1 185 0                 # prog2.c:185:0
	shrq	$63, %rcx
.Ltmp106:
	.loc	1 181 0                 # prog2.c:181:0
	decq	%rax
	testq	%rax, %rax
	movq	%rcx, %rdx
	jg	.LBB4_11
.Ltmp107:
.LBB4_12:                               # %if.end59
                                        #   in Loop: Header=BB4_3 Depth=1
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 1+0
	#DEBUG_VALUE: divisor <- 1+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 195 0                 # prog2.c:195:0
	addq	$2, %r10
.Ltmp108:
	#DEBUG_VALUE: divisor <- R10+0
	.loc	1 194 0                 # prog2.c:194:0
	negq	%r8
.Ltmp109:
	#DEBUG_VALUE: arctan:sign <- R8+0
	.loc	1 197 0                 # prog2.c:197:0
	movq	size(%rip), %rax
.Ltmp110:
	#DEBUG_VALUE: NotZero <- 0+0
	movq	%rbx, %rcx
.LBB4_13:                               # %for.cond62
                                        #   Parent Loop BB4_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	#DEBUG_VALUE: arctan:sign <- R8+0
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 0+0
	#DEBUG_VALUE: divisor <- R10+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	cmpq	%rax, %rcx
	jge	.LBB4_17
# BB#14:                                # %for.body64
                                        #   in Loop: Header=BB4_13 Depth=2
	#DEBUG_VALUE: arctan:sign <- R8+0
.Ltmp111:
	#DEBUG_VALUE: denom2 <- RSI+0
	#DEBUG_VALUE: NotZero <- 0+0
	#DEBUG_VALUE: x <- RCX+0
	#DEBUG_VALUE: divisor <- R10+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 199 0                 # prog2.c:199:0
	cmpq	$0, (%r9,%rcx,8)
.Ltmp112:
	.loc	1 197 0                 # prog2.c:197:0
	leaq	1(%rcx), %rcx
.Ltmp113:
	.loc	1 199 0                 # prog2.c:199:0
	je	.LBB4_13
.Ltmp114:
# BB#15:                                # %while.cond74.loopexit
                                        #   in Loop: Header=BB4_3 Depth=1
	#DEBUG_VALUE: arctan:sign <- R8+0
	decq	%rbx
.LBB4_16:                               # %while.cond74
                                        #   Parent Loop BB4_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
.Ltmp115:
	#DEBUG_VALUE: arctan:sign <- R8+0
	xorq	%rdi, %rdi
	.loc	1 208 0                 # prog2.c:208:0
.Ltmp116:
	cmpq	$0, 8(%r9,%rbx,8)
	leaq	1(%rbx), %rbx
	je	.LBB4_16
	jmp	.LBB4_3
.Ltmp117:
.LBB4_17:                               # %while.cond.loopexit
	#DEBUG_VALUE: NotZero <- 0+0
	#DEBUG_VALUE: remain <- 0+0
	#DEBUG_VALUE: adv <- 0+0
	.loc	1 213 0                 # prog2.c:213:0
	popq	%rbx
	popq	%r14
	ret
.Ltmp118:
.Ltmp119:
	.size	arctan, .Ltmp119-arctan
.Lfunc_end4:
	.cfi_endproc

	.globl	_main
	.type	_main,@function
_main:                                  # @_main
	.cfi_startproc
.Lfunc_begin5:
	.loc	1 216 0                 # prog2.c:216:0
# BB#0:                                 # %entry
	pushq	%rbp
.Ltmp127:
	.cfi_def_cfa_offset 16
	pushq	%r15
.Ltmp128:
	.cfi_def_cfa_offset 24
	pushq	%r14
.Ltmp129:
	.cfi_def_cfa_offset 32
	pushq	%r13
.Ltmp130:
	.cfi_def_cfa_offset 40
	pushq	%r12
.Ltmp131:
	.cfi_def_cfa_offset 48
	pushq	%rbx
.Ltmp132:
	.cfi_def_cfa_offset 56
	pushq	%rax
.Ltmp133:
	.cfi_def_cfa_offset 64
.Ltmp134:
	.cfi_offset %rbx, -56
.Ltmp135:
	.cfi_offset %r12, -48
.Ltmp136:
	.cfi_offset %r13, -40
.Ltmp137:
	.cfi_offset %r14, -32
.Ltmp138:
	.cfi_offset %r15, -24
.Ltmp139:
	.cfi_offset %rbp, -16
	#DEBUG_VALUE: _main:argc <- RDI+0
	#DEBUG_VALUE: _main:argv <- RSI+0
	movq	%rsi, %rbx
.Ltmp140:
	#DEBUG_VALUE: _main:argv <- RBX+0
	.loc	1 220 0 prologue_end    # prog2.c:220:0
	cmpq	$2, %rdi
	je	.LBB5_2
.Ltmp141:
# BB#1:                                 # %if.then
	#DEBUG_VALUE: _main:argv <- RBX+0
	.loc	1 222 0                 # prog2.c:222:0
	movabsq	$.L.str, %rdi
	callq	puts
	movabsq	$1, %rdi
	.loc	1 223 0                 # prog2.c:223:0
	callq	llexit
.Ltmp142:
.LBB5_2:                                # %if.end
	#DEBUG_VALUE: _main:argv <- RBX+0
	.loc	1 226 0                 # prog2.c:226:0
	movq	8(%rbx), %rdi
	callq	atol
	movq	%rax, size(%rip)
	.loc	1 228 0                 # prog2.c:228:0
	testq	%rax, %rax
	jg	.LBB5_4
.Ltmp143:
# BB#3:                                 # %if.then3
	.loc	1 230 0                 # prog2.c:230:0
	movabsq	$.L.str1, %rdi
	callq	puts
	movabsq	$1, %rdi
	.loc	1 231 0                 # prog2.c:231:0
	callq	llexit
.Ltmp144:
	.loc	1 234 0                 # prog2.c:234:0
	movq	size(%rip), %rax
.LBB5_4:                                # %if.end5
	leaq	1(%rax), %rcx
	shrq	$63, %rcx
	leaq	1(%rax,%rcx), %rax
	sarq	%rax
	leaq	1(%rax), %rbp
	movq	%rbp, size(%rip)
	.loc	1 236 0                 # prog2.c:236:0
	leaq	8(,%rax,8), %rbx
	movq	%rbx, %rdi
	callq	malloc
	movq	%rax, %r14
	movq	%r14, pi(%rip)
	.loc	1 237 0                 # prog2.c:237:0
	movq	%rbx, %rdi
	callq	malloc
	movq	%rax, %r15
	movq	%r15, powers(%rip)
	.loc	1 238 0                 # prog2.c:238:0
	movq	%rbx, %rdi
	callq	malloc
	movq	%rax, term(%rip)
	.loc	1 240 0                 # prog2.c:240:0
	testq	%r14, %r14
	je	.LBB5_7
# BB#5:                                 # %if.end5
	testq	%r15, %r15
	je	.LBB5_7
# BB#6:                                 # %if.end5
	testq	%rax, %rax
	jne	.LBB5_8
.LBB5_7:                                # %if.then16
	.loc	1 242 0                 # prog2.c:242:0
.Ltmp145:
	movabsq	$.L.str2, %rdi
	callq	puts
	movabsq	$1, %rdi
	.loc	1 243 0                 # prog2.c:243:0
	callq	llexit
.Ltmp146:
	.loc	1 246 0                 # prog2.c:246:0
	movq	size(%rip), %rbp
.LBB5_8:                                # %for.cond.preheader
	testq	%rbp, %rbp
	jle	.LBB5_11
# BB#9:                                 # %for.body.lr.ph
	xorq	%rax, %rax
	.loc	1 247 0                 # prog2.c:247:0
	movq	pi(%rip), %rcx
.LBB5_10:                               # %for.body
                                        # =>This Inner Loop Header: Depth=1
	movq	$0, (%rcx,%rax,8)
	.loc	1 246 0                 # prog2.c:246:0
	incq	%rax
.Ltmp147:
	#DEBUG_VALUE: x <- RAX+0
	cmpq	size(%rip), %rax
	jl	.LBB5_10
.Ltmp148:
.LBB5_11:                               # %for.end
	xorq	%rdi, %rdi
	.loc	1 249 0                 # prog2.c:249:0
	callq	time
	movq	%rax, %r14
.Ltmp149:
	#DEBUG_VALUE: T1 <- R14+0
	movabsq	$1, %r13
	movabsq	$16, %rdi
	movabsq	$5, %rsi
	movabsq	$1, %rdx
	.loc	1 268 0                 # prog2.c:268:0
	callq	arctan
	movabsq	$4, %rdi
	movabsq	$239, %rsi
	movq	$-1, %rdx
	.loc	1 269 0                 # prog2.c:269:0
	callq	arctan
	xorq	%rdi, %rdi
	.loc	1 272 0                 # prog2.c:272:0
	callq	time
	movq	%rax, %r15
.Ltmp150:
	#DEBUG_VALUE: T2 <- R15+0
	.loc	1 274 0                 # prog2.c:274:0
	movq	pi(%rip), %rbp
.Ltmp151:
	#DEBUG_VALUE: Print:num <- RBP+0
	movabsq	$51, %rdi
	.loc	1 119 0                 # prog2.c:119:0
.Ltmp152:
	callq	putchar
	movabsq	$46, %rdi
	.loc	1 120 0                 # prog2.c:120:0
	callq	putchar
	.loc	1 121 0                 # prog2.c:121:0
	cmpq	$2, size(%rip)
.Ltmp153:
	#DEBUG_VALUE: x <- 1+0
	jl	.LBB5_13
.LBB5_12:                               # %for.body.i
                                        # =>This Inner Loop Header: Depth=1
	#DEBUG_VALUE: T1 <- R14+0
	#DEBUG_VALUE: T2 <- R15+0
.Ltmp154:
	#DEBUG_VALUE: Print:num <- RBP+0
	#DEBUG_VALUE: x <- 1+0
	.loc	1 122 0                 # prog2.c:122:0
	movq	(%rbp,%r13,8), %r12
.Ltmp155:
	#DEBUG_VALUE: PrintShort:num <- R12+0
	movabsq	$7378697629483820647, %rcx # imm = 0x6666666666666667
	.loc	1 109 0                 # prog2.c:109:0
.Ltmp156:
	movq	%r12, %rax
	imulq	%rcx
	movq	%rdx, %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$2, %rbx
	addq	%rax, %rbx
.Ltmp157:
	#DEBUG_VALUE: x <- 0+0
	#DEBUG_VALUE: PrintShort:num <- RBX+0
	.loc	1 108 0                 # prog2.c:108:0
	movq	%rbx, %rax
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rdx
	addq	%rax, %rdx
	shlq	$1, %rdx
	leaq	(%rdx,%rdx,4), %rax
	movq	%rbx, %rcx
	subq	%rax, %rcx
.Ltmp158:
	#DEBUG_VALUE: OutDig:dig <- RCX+0
	#DEBUG_VALUE: x <- 1+0
	.loc	1 92 0                  # prog2.c:92:0
	leaq	48(%rcx), %rdi
	callq	putchar
.Ltmp159:
	.loc	1 108 0                 # prog2.c:108:0
	shlq	$1, %rbx
.Ltmp160:
	leaq	(%rbx,%rbx,4), %rax
	negq	%rax
	.loc	1 92 0                  # prog2.c:92:0
.Ltmp161:
	leaq	48(%r12,%rax), %rdi
.Ltmp162:
	#DEBUG_VALUE: x <- 0+0
	callq	putchar
.Ltmp163:
	.loc	1 121 0                 # prog2.c:121:0
	incq	%r13
.Ltmp164:
	#DEBUG_VALUE: x <- R13+0
	cmpq	size(%rip), %r13
	jl	.LBB5_12
.Ltmp165:
.LBB5_13:                               # %Print.exit
	#DEBUG_VALUE: T1 <- R14+0
	#DEBUG_VALUE: T2 <- R15+0
	#DEBUG_VALUE: x <- 1+0
	movabsq	$10, %rdi
	.loc	1 123 0                 # prog2.c:123:0
	callq	putchar
.Ltmp166:
	.loc	1 277 0                 # prog2.c:277:0
	movabsq	$.L.str3, %rdi
	callq	puts
	.loc	1 278 0                 # prog2.c:278:0
	subq	%r14, %r15
.Ltmp167:
	movq	%r15, %rdi
	callq	PrintVal
	.loc	1 279 0                 # prog2.c:279:0
	movabsq	$.L.str4, %rdi
	callq	puts
	xorq	%rax, %rax
	.loc	1 282 0                 # prog2.c:282:0
	addq	$8, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
.Ltmp168:
	popq	%r15
	popq	%rbp
	ret
.Ltmp169:
.Ltmp170:
	.size	_main, .Ltmp170-_main
.Lfunc_end5:
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

	.text
.Ltext_end:
	.data
.Ldata_end:
	.text
.Lsection_end1:
	.section	.debug_info,"",@progbits
.Lsection_info:
	.section	.debug_abbrev,"",@progbits
.Lsection_abbrev:
	.section	.debug_aranges,"",@progbits
	.section	.debug_macinfo,"",@progbits
	.section	.debug_line,"",@progbits
.Lsection_line:
	.section	.debug_loc,"",@progbits
	.section	.debug_pubtypes,"",@progbits
	.section	.debug_str,"MS",@progbits,1
.Linfo_string:
	.section	.debug_ranges,"",@progbits
.Ldebug_range:
	.section	.debug_loc,"",@progbits
.Lsection_debug_loc:
	.text
.Ltext_begin:
	.data
	.section	.debug_info,"",@progbits
.L.debug_info_begin0:
	.long	1209                    # Length of Compilation Unit Info
	.short	2                       # DWARF version number
	.long	.L.debug_abbrev_begin   # Offset Into Abbrev. Section
	.byte	8                       # Address Size (in bytes)
	.byte	1                       # Abbrev [1] 0xb:0x4b2 DW_TAG_compile_unit
	.long	.Linfo_string0          # DW_AT_producer
	.short	12                      # DW_AT_language
	.long	.Linfo_string1          # DW_AT_name
	.quad	0                       # DW_AT_low_pc
	.long	.Lsection_line          # DW_AT_stmt_list
	.long	.Linfo_string2          # DW_AT_comp_dir
                                        # DW_AT_APPLE_optimized
	.byte	2                       # Abbrev [2] 0x26:0x7 DW_TAG_base_type
	.long	.Linfo_string4          # DW_AT_name
	.byte	5                       # DW_AT_encoding
	.byte	8                       # DW_AT_byte_size
	.byte	3                       # Abbrev [3] 0x2d:0xb DW_TAG_typedef
	.long	38                      # DW_AT_type
	.long	.Linfo_string5          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	78                      # DW_AT_decl_line
	.byte	4                       # Abbrev [4] 0x38:0x5 DW_TAG_pointer_type
	.long	45                      # DW_AT_type
	.byte	5                       # Abbrev [5] 0x3d:0x15 DW_TAG_variable
	.long	.Linfo_string3          # DW_AT_name
	.long	56                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	pi
	.byte	5                       # Abbrev [5] 0x52:0x15 DW_TAG_variable
	.long	.Linfo_string6          # DW_AT_name
	.long	56                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	powers
	.byte	5                       # Abbrev [5] 0x67:0x15 DW_TAG_variable
	.long	.Linfo_string7          # DW_AT_name
	.long	56                      # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	86                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	term
	.byte	3                       # Abbrev [3] 0x7c:0xb DW_TAG_typedef
	.long	38                      # DW_AT_type
	.long	.Linfo_string9          # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	82                      # DW_AT_decl_line
	.byte	5                       # Abbrev [5] 0x87:0x15 DW_TAG_variable
	.long	.Linfo_string8          # DW_AT_name
	.long	124                     # DW_AT_type
                                        # DW_AT_external
	.byte	1                       # DW_AT_decl_file
	.byte	87                      # DW_AT_decl_line
	.byte	9                       # DW_AT_location
	.byte	3
	.quad	size
	.byte	6                       # Abbrev [6] 0x9c:0x2a DW_TAG_subprogram
	.long	.Linfo_string10         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin0           # DW_AT_low_pc
	.quad	.Lfunc_end0             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_APPLE_omit_frame_ptr
	.byte	1                       # DW_AT_inline
	.byte	7                       # Abbrev [7] 0xb6:0xf DW_TAG_formal_parameter
	.long	.Linfo_string16         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc0            # DW_AT_location
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0xc6:0x52 DW_TAG_subprogram
	.long	.Linfo_string11         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	95                      # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin1           # DW_AT_low_pc
	.quad	.Lfunc_end1             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_APPLE_omit_frame_ptr
	.byte	7                       # Abbrev [7] 0xdf:0xf DW_TAG_formal_parameter
	.long	.Linfo_string18         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	95                      # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc2            # DW_AT_location
	.byte	9                       # Abbrev [9] 0xee:0x29 DW_TAG_lexical_block
	.quad	.Ltmp7                  # DW_AT_low_pc
	.quad	.Ltmp11                 # DW_AT_high_pc
	.byte	10                      # Abbrev [10] 0xff:0x17 DW_TAG_inlined_subroutine
	.long	156                     # DW_AT_abstract_origin
	.quad	.Ltmp9                  # DW_AT_low_pc
	.quad	.Ltmp11                 # DW_AT_high_pc
	.byte	1                       # DW_AT_call_file
	.byte	97                      # DW_AT_call_line
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	6                       # Abbrev [6] 0x118:0x77 DW_TAG_subprogram
	.long	.Linfo_string12         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin2           # DW_AT_low_pc
	.quad	.Lfunc_end2             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_APPLE_omit_frame_ptr
	.byte	1                       # DW_AT_inline
	.byte	7                       # Abbrev [7] 0x132:0xf DW_TAG_formal_parameter
	.long	.Linfo_string19         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.long	45                      # DW_AT_type
	.long	.Ldebug_loc6            # DW_AT_location
	.byte	9                       # Abbrev [9] 0x141:0x4d DW_TAG_lexical_block
	.quad	.Ltmp22                 # DW_AT_low_pc
	.quad	.Ltmp30                 # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x152:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc10           # DW_AT_location
	.byte	12                      # Abbrev [12] 0x161:0xb DW_TAG_variable
	.long	.Linfo_string21         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	104                     # DW_AT_decl_line
	.long	1161                    # DW_AT_type
	.byte	13                      # Abbrev [13] 0x16c:0x21 DW_TAG_lexical_block
	.long	.Ldebug_range+48        # DW_AT_ranges
	.byte	14                      # Abbrev [14] 0x171:0x1b DW_TAG_inlined_subroutine
	.long	156                     # DW_AT_abstract_origin
	.long	.Ldebug_range           # DW_AT_ranges
	.byte	1                       # DW_AT_call_file
	.byte	112                     # DW_AT_call_line
	.byte	7                       # Abbrev [7] 0x17c:0xf DW_TAG_formal_parameter
	.long	.Linfo_string16         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc14           # DW_AT_location
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	6                       # Abbrev [6] 0x18f:0xae DW_TAG_subprogram
	.long	.Linfo_string13         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	115                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin3           # DW_AT_low_pc
	.quad	.Lfunc_end3             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_APPLE_omit_frame_ptr
	.byte	1                       # DW_AT_inline
	.byte	7                       # Abbrev [7] 0x1a9:0xf DW_TAG_formal_parameter
	.long	.Linfo_string19         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	115                     # DW_AT_decl_line
	.long	56                      # DW_AT_type
	.long	.Ldebug_loc16           # DW_AT_location
	.byte	9                       # Abbrev [9] 0x1b8:0x84 DW_TAG_lexical_block
	.quad	.Ltmp47                 # DW_AT_low_pc
	.quad	.Ltmp61                 # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x1c9:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	117                     # DW_AT_decl_line
	.long	124                     # DW_AT_type
	.long	.Ldebug_loc20           # DW_AT_location
	.byte	9                       # Abbrev [9] 0x1d8:0x63 DW_TAG_lexical_block
	.quad	.Ltmp48                 # DW_AT_low_pc
	.quad	.Ltmp60                 # DW_AT_high_pc
	.byte	15                      # Abbrev [15] 0x1e9:0x51 DW_TAG_inlined_subroutine
	.long	280                     # DW_AT_abstract_origin
	.quad	.Ltmp51                 # DW_AT_low_pc
	.quad	.Ltmp58                 # DW_AT_high_pc
	.byte	1                       # DW_AT_call_file
	.byte	122                     # DW_AT_call_line
	.byte	7                       # Abbrev [7] 0x200:0xf DW_TAG_formal_parameter
	.long	.Linfo_string19         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.long	45                      # DW_AT_type
	.long	.Ldebug_loc23           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x20f:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc26           # DW_AT_location
	.byte	14                      # Abbrev [14] 0x21e:0x1b DW_TAG_inlined_subroutine
	.long	156                     # DW_AT_abstract_origin
	.long	.Ldebug_range+96        # DW_AT_ranges
	.byte	1                       # DW_AT_call_file
	.byte	112                     # DW_AT_call_line
	.byte	7                       # Abbrev [7] 0x229:0xf DW_TAG_formal_parameter
	.long	.Linfo_string16         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc30           # DW_AT_location
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	8                       # Abbrev [8] 0x23d:0x137 DW_TAG_subprogram
	.long	.Linfo_string14         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	126                     # DW_AT_decl_line
                                        # DW_AT_prototyped
                                        # DW_AT_external
	.quad	.Lfunc_begin4           # DW_AT_low_pc
	.quad	.Lfunc_end4             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_APPLE_omit_frame_ptr
	.byte	7                       # Abbrev [7] 0x256:0xf DW_TAG_formal_parameter
	.long	.Linfo_string23         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	126                     # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc32           # DW_AT_location
	.byte	7                       # Abbrev [7] 0x265:0xf DW_TAG_formal_parameter
	.long	.Linfo_string24         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	126                     # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc35           # DW_AT_location
	.byte	7                       # Abbrev [7] 0x274:0xf DW_TAG_formal_parameter
	.long	.Linfo_string25         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	126                     # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc38           # DW_AT_location
	.byte	9                       # Abbrev [9] 0x283:0xf0 DW_TAG_lexical_block
	.quad	.Ltmp72                 # DW_AT_low_pc
	.quad	.Ltmp118                # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x294:0xf DW_TAG_variable
	.long	.Linfo_string26         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	129                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.long	.Ldebug_loc43           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x2a3:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	128                     # DW_AT_decl_line
	.long	124                     # DW_AT_type
	.long	.Ldebug_loc48           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x2b2:0xf DW_TAG_variable
	.long	.Linfo_string28         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	130                     # DW_AT_decl_line
	.long	45                      # DW_AT_type
	.long	.Ldebug_loc55           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x2c1:0xf DW_TAG_variable
	.long	.Linfo_string29         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	129                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.long	.Ldebug_loc59           # DW_AT_location
	.byte	16                      # Abbrev [16] 0x2d0:0x14 DW_TAG_variable
	.long	.Linfo_string30         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	131                     # DW_AT_decl_line
	.long	124                     # DW_AT_type
	.byte	8                       # DW_AT_const_value
	.quad	0
	.byte	11                      # Abbrev [11] 0x2e4:0xf DW_TAG_variable
	.long	.Linfo_string31         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	129                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.long	.Ldebug_loc63           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x2f3:0xf DW_TAG_variable
	.long	.Linfo_string32         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	129                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.long	.Ldebug_loc69           # DW_AT_location
	.byte	9                       # Abbrev [9] 0x302:0x70 DW_TAG_lexical_block
	.quad	.Ltmp77                 # DW_AT_low_pc
	.quad	.Ltmp117                # DW_AT_high_pc
	.byte	13                      # Abbrev [13] 0x313:0x29 DW_TAG_lexical_block
	.long	.Ldebug_range+144       # DW_AT_ranges
	.byte	11                      # Abbrev [11] 0x318:0xf DW_TAG_variable
	.long	.Linfo_string33         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	178                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.long	.Ldebug_loc75           # DW_AT_location
	.byte	16                      # Abbrev [16] 0x327:0x14 DW_TAG_variable
	.long	.Linfo_string34         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	178                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.byte	8                       # DW_AT_const_value
	.quad	0
	.byte	0                       # End Of Children Mark
	.byte	9                       # Abbrev [9] 0x33c:0x35 DW_TAG_lexical_block
	.quad	.Ltmp93                 # DW_AT_low_pc
	.quad	.Ltmp100                # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x34d:0xf DW_TAG_variable
	.long	.Linfo_string33         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.long	.Ldebug_loc72           # DW_AT_location
	.byte	16                      # Abbrev [16] 0x35c:0x14 DW_TAG_variable
	.long	.Linfo_string35         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	161                     # DW_AT_decl_line
	.long	1173                    # DW_AT_type
	.byte	8                       # DW_AT_const_value
	.quad	0
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	17                      # Abbrev [17] 0x374:0x103 DW_TAG_subprogram
	.long	.Linfo_string15         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	215                     # DW_AT_decl_line
                                        # DW_AT_prototyped
	.long	38                      # DW_AT_type
                                        # DW_AT_external
	.quad	.Lfunc_begin5           # DW_AT_low_pc
	.quad	.Lfunc_end5             # DW_AT_high_pc
	.byte	1                       # DW_AT_frame_base
	.byte	87
                                        # DW_AT_APPLE_omit_frame_ptr
	.byte	7                       # Abbrev [7] 0x391:0xf DW_TAG_formal_parameter
	.long	.Linfo_string36         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	215                     # DW_AT_decl_line
	.long	38                      # DW_AT_type
	.long	.Ldebug_loc78           # DW_AT_location
	.byte	7                       # Abbrev [7] 0x3a0:0xf DW_TAG_formal_parameter
	.long	.Linfo_string37         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	215                     # DW_AT_decl_line
	.long	1196                    # DW_AT_type
	.long	.Ldebug_loc80           # DW_AT_location
	.byte	9                       # Abbrev [9] 0x3af:0xc7 DW_TAG_lexical_block
	.quad	.Ltmp140                # DW_AT_low_pc
	.quad	.Ltmp169                # DW_AT_high_pc
	.byte	11                      # Abbrev [11] 0x3c0:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	217                     # DW_AT_decl_line
	.long	124                     # DW_AT_type
	.long	.Ldebug_loc84           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x3cf:0xf DW_TAG_variable
	.long	.Linfo_string39         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	218                     # DW_AT_decl_line
	.long	1201                    # DW_AT_type
	.long	.Ldebug_loc86           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x3de:0xf DW_TAG_variable
	.long	.Linfo_string41         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	218                     # DW_AT_decl_line
	.long	1201                    # DW_AT_type
	.long	.Ldebug_loc89           # DW_AT_location
	.byte	18                      # Abbrev [18] 0x3ed:0x88 DW_TAG_inlined_subroutine
	.long	399                     # DW_AT_abstract_origin
	.quad	.Ltmp152                # DW_AT_low_pc
	.quad	.Ltmp166                # DW_AT_high_pc
	.byte	1                       # DW_AT_call_file
	.short	274                     # DW_AT_call_line
	.byte	7                       # Abbrev [7] 0x405:0xf DW_TAG_formal_parameter
	.long	.Linfo_string19         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	115                     # DW_AT_decl_line
	.long	56                      # DW_AT_type
	.long	.Ldebug_loc92           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x414:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	117                     # DW_AT_decl_line
	.long	124                     # DW_AT_type
	.long	.Ldebug_loc95           # DW_AT_location
	.byte	15                      # Abbrev [15] 0x423:0x51 DW_TAG_inlined_subroutine
	.long	280                     # DW_AT_abstract_origin
	.quad	.Ltmp156                # DW_AT_low_pc
	.quad	.Ltmp163                # DW_AT_high_pc
	.byte	1                       # DW_AT_call_file
	.byte	122                     # DW_AT_call_line
	.byte	7                       # Abbrev [7] 0x43a:0xf DW_TAG_formal_parameter
	.long	.Linfo_string19         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	101                     # DW_AT_decl_line
	.long	45                      # DW_AT_type
	.long	.Ldebug_loc99           # DW_AT_location
	.byte	11                      # Abbrev [11] 0x449:0xf DW_TAG_variable
	.long	.Linfo_string20         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	103                     # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc102          # DW_AT_location
	.byte	14                      # Abbrev [14] 0x458:0x1b DW_TAG_inlined_subroutine
	.long	156                     # DW_AT_abstract_origin
	.long	.Ldebug_range+192       # DW_AT_ranges
	.byte	1                       # DW_AT_call_file
	.byte	112                     # DW_AT_call_line
	.byte	7                       # Abbrev [7] 0x463:0xf DW_TAG_formal_parameter
	.long	.Linfo_string16         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	90                      # DW_AT_decl_line
	.long	1143                    # DW_AT_type
	.long	.Ldebug_loc106          # DW_AT_location
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x477:0xb DW_TAG_typedef
	.long	38                      # DW_AT_type
	.long	.Linfo_string17         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	83                      # DW_AT_decl_line
	.byte	19                      # Abbrev [19] 0x482:0x7 DW_TAG_base_type
	.long	.Linfo_string22         # DW_AT_name
	.byte	4                       # DW_AT_byte_size
	.byte	5                       # DW_AT_encoding
	.byte	20                      # Abbrev [20] 0x489:0xc DW_TAG_array_type
	.long	1143                    # DW_AT_type
	.byte	21                      # Abbrev [21] 0x48e:0x6 DW_TAG_subrange_type
	.long	1154                    # DW_AT_type
	.byte	2                       # DW_AT_upper_bound
	.byte	0                       # End Of Children Mark
	.byte	3                       # Abbrev [3] 0x495:0xb DW_TAG_typedef
	.long	38                      # DW_AT_type
	.long	.Linfo_string27         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	79                      # DW_AT_decl_line
	.byte	2                       # Abbrev [2] 0x4a0:0x7 DW_TAG_base_type
	.long	.Linfo_string38         # DW_AT_name
	.byte	6                       # DW_AT_encoding
	.byte	1                       # DW_AT_byte_size
	.byte	4                       # Abbrev [4] 0x4a7:0x5 DW_TAG_pointer_type
	.long	1184                    # DW_AT_type
	.byte	4                       # Abbrev [4] 0x4ac:0x5 DW_TAG_pointer_type
	.long	1191                    # DW_AT_type
	.byte	3                       # Abbrev [3] 0x4b1:0xb DW_TAG_typedef
	.long	38                      # DW_AT_type
	.long	.Linfo_string40         # DW_AT_name
	.byte	1                       # DW_AT_decl_file
	.byte	14                      # DW_AT_decl_line
	.byte	0                       # End Of Children Mark
.L.debug_info_end0:
	.section	.debug_abbrev,"",@progbits
.L.debug_abbrev_begin:
	.byte	1                       # Abbreviation Code
	.byte	17                      # DW_TAG_compile_unit
	.byte	1                       # DW_CHILDREN_yes
	.byte	37                      # DW_AT_producer
	.byte	14                      # DW_FORM_strp
	.byte	19                      # DW_AT_language
	.byte	5                       # DW_FORM_data2
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	16                      # DW_AT_stmt_list
	.byte	6                       # DW_FORM_data4
	.byte	27                      # DW_AT_comp_dir
	.byte	14                      # DW_FORM_strp
	.ascii	 "\341\177"             # DW_AT_APPLE_optimized
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	2                       # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	3                       # Abbreviation Code
	.byte	22                      # DW_TAG_typedef
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	4                       # Abbreviation Code
	.byte	15                      # DW_TAG_pointer_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	5                       # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	2                       # DW_AT_location
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	6                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.ascii	 "\347\177"             # DW_AT_APPLE_omit_frame_ptr
	.byte	25                      # DW_FORM_flag_present
	.byte	32                      # DW_AT_inline
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	7                       # Abbreviation Code
	.byte	5                       # DW_TAG_formal_parameter
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	8                       # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.ascii	 "\347\177"             # DW_AT_APPLE_omit_frame_ptr
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	9                       # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	10                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	0                       # DW_CHILDREN_no
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	11                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	2                       # DW_AT_location
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	12                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	13                      # Abbreviation Code
	.byte	11                      # DW_TAG_lexical_block
	.byte	1                       # DW_CHILDREN_yes
	.byte	85                      # DW_AT_ranges
	.byte	6                       # DW_FORM_data4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	14                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	85                      # DW_AT_ranges
	.byte	6                       # DW_FORM_data4
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	15                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	16                      # Abbreviation Code
	.byte	52                      # DW_TAG_variable
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	28                      # DW_AT_const_value
	.byte	10                      # DW_FORM_block1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	17                      # Abbreviation Code
	.byte	46                      # DW_TAG_subprogram
	.byte	1                       # DW_CHILDREN_yes
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	58                      # DW_AT_decl_file
	.byte	11                      # DW_FORM_data1
	.byte	59                      # DW_AT_decl_line
	.byte	11                      # DW_FORM_data1
	.byte	39                      # DW_AT_prototyped
	.byte	25                      # DW_FORM_flag_present
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	63                      # DW_AT_external
	.byte	25                      # DW_FORM_flag_present
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	64                      # DW_AT_frame_base
	.byte	10                      # DW_FORM_block1
	.ascii	 "\347\177"             # DW_AT_APPLE_omit_frame_ptr
	.byte	25                      # DW_FORM_flag_present
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	18                      # Abbreviation Code
	.byte	29                      # DW_TAG_inlined_subroutine
	.byte	1                       # DW_CHILDREN_yes
	.byte	49                      # DW_AT_abstract_origin
	.byte	19                      # DW_FORM_ref4
	.byte	17                      # DW_AT_low_pc
	.byte	1                       # DW_FORM_addr
	.byte	18                      # DW_AT_high_pc
	.byte	1                       # DW_FORM_addr
	.byte	88                      # DW_AT_call_file
	.byte	11                      # DW_FORM_data1
	.byte	89                      # DW_AT_call_line
	.byte	5                       # DW_FORM_data2
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	19                      # Abbreviation Code
	.byte	36                      # DW_TAG_base_type
	.byte	0                       # DW_CHILDREN_no
	.byte	3                       # DW_AT_name
	.byte	14                      # DW_FORM_strp
	.byte	11                      # DW_AT_byte_size
	.byte	11                      # DW_FORM_data1
	.byte	62                      # DW_AT_encoding
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	20                      # Abbreviation Code
	.byte	1                       # DW_TAG_array_type
	.byte	1                       # DW_CHILDREN_yes
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	21                      # Abbreviation Code
	.byte	33                      # DW_TAG_subrange_type
	.byte	0                       # DW_CHILDREN_no
	.byte	73                      # DW_AT_type
	.byte	19                      # DW_FORM_ref4
	.byte	47                      # DW_AT_upper_bound
	.byte	11                      # DW_FORM_data1
	.byte	0                       # EOM(1)
	.byte	0                       # EOM(2)
	.byte	0                       # EOM(3)
.L.debug_abbrev_end:
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
	.quad	.Lfunc_begin0
	.quad	.Ltmp0
.Lset0 = .Ltmp172-.Ltmp171              # Loc expr size
	.short	.Lset0
.Ltmp171:
	.byte	85                      # DW_OP_reg5
.Ltmp172:
	.quad	0
	.quad	0
.Ldebug_loc2:
	.quad	.Lfunc_begin1
	.quad	.Ltmp7
.Lset1 = .Ltmp174-.Ltmp173              # Loc expr size
	.short	.Lset1
.Ltmp173:
	.byte	85                      # DW_OP_reg5
.Ltmp174:
	.quad	.Ltmp7
	.quad	.Ltmp10
.Lset2 = .Ltmp176-.Ltmp175              # Loc expr size
	.short	.Lset2
.Ltmp175:
	.byte	83                      # DW_OP_reg3
.Ltmp176:
	.quad	0
	.quad	0
.Ldebug_loc6:
	.quad	.Lfunc_begin2
	.quad	.Ltmp21
.Lset3 = .Ltmp178-.Ltmp177              # Loc expr size
	.short	.Lset3
.Ltmp177:
	.byte	85                      # DW_OP_reg5
.Ltmp178:
	.quad	.Ltmp21
	.quad	.Ltmp23
.Lset4 = .Ltmp180-.Ltmp179              # Loc expr size
	.short	.Lset4
.Ltmp179:
	.byte	94                      # DW_OP_reg14
.Ltmp180:
	.quad	.Ltmp23
	.quad	.Ltmp26
.Lset5 = .Ltmp182-.Ltmp181              # Loc expr size
	.short	.Lset5
.Ltmp181:
	.byte	83                      # DW_OP_reg3
.Ltmp182:
	.quad	0
	.quad	0
.Ldebug_loc10:
	.quad	.Ltmp21
	.quad	.Lfunc_end2
.Lset6 = .Ltmp184-.Ltmp183              # Loc expr size
	.short	.Lset6
.Ltmp183:
	.byte	16                      # DW_OP_constu
	.byte	0
.Ltmp184:
	.quad	0
	.quad	0
.Ldebug_loc14:
	.quad	.Ltmp24
	.quad	.Ltmp30
.Lset7 = .Ltmp186-.Ltmp185              # Loc expr size
	.short	.Lset7
.Ltmp185:
	.byte	82                      # DW_OP_reg2
.Ltmp186:
	.quad	0
	.quad	0
.Ldebug_loc16:
	.quad	.Lfunc_begin3
	.quad	.Ltmp46
.Lset8 = .Ltmp188-.Ltmp187              # Loc expr size
	.short	.Lset8
.Ltmp187:
	.byte	85                      # DW_OP_reg5
.Ltmp188:
	.quad	.Ltmp46
	.quad	.Ltmp60
.Lset9 = .Ltmp190-.Ltmp189              # Loc expr size
	.short	.Lset9
.Ltmp189:
	.byte	94                      # DW_OP_reg14
.Ltmp190:
	.quad	0
	.quad	0
.Ldebug_loc20:
	.quad	.Ltmp48
	.quad	.Ltmp59
.Lset10 = .Ltmp192-.Ltmp191             # Loc expr size
	.short	.Lset10
.Ltmp191:
	.byte	16                      # DW_OP_constu
	.byte	1
.Ltmp192:
	.quad	.Ltmp59
	.quad	.Ltmp60
.Lset11 = .Ltmp194-.Ltmp193             # Loc expr size
	.short	.Lset11
.Ltmp193:
	.byte	92                      # DW_OP_reg12
.Ltmp194:
	.quad	0
	.quad	0
.Ldebug_loc23:
	.quad	.Ltmp50
	.quad	.Ltmp52
.Lset12 = .Ltmp196-.Ltmp195             # Loc expr size
	.short	.Lset12
.Ltmp195:
	.byte	95                      # DW_OP_reg15
.Ltmp196:
	.quad	.Ltmp52
	.quad	.Ltmp55
.Lset13 = .Ltmp198-.Ltmp197             # Loc expr size
	.short	.Lset13
.Ltmp197:
	.byte	83                      # DW_OP_reg3
.Ltmp198:
	.quad	0
	.quad	0
.Ldebug_loc26:
	.quad	.Ltmp52
	.quad	.Lfunc_end3
.Lset14 = .Ltmp200-.Ltmp199             # Loc expr size
	.short	.Lset14
.Ltmp199:
	.byte	16                      # DW_OP_constu
	.byte	0
.Ltmp200:
	.quad	0
	.quad	0
.Ldebug_loc30:
	.quad	.Ltmp53
	.quad	.Ltmp60
.Lset15 = .Ltmp202-.Ltmp201             # Loc expr size
	.short	.Lset15
.Ltmp201:
	.byte	82                      # DW_OP_reg2
.Ltmp202:
	.quad	0
	.quad	0
.Ldebug_loc32:
	.quad	.Lfunc_begin4
	.quad	.Ltmp75
.Lset16 = .Ltmp204-.Ltmp203             # Loc expr size
	.short	.Lset16
.Ltmp203:
	.byte	85                      # DW_OP_reg5
.Ltmp204:
	.quad	0
	.quad	0
.Ldebug_loc35:
	.quad	.Lfunc_begin4
	.quad	.Ltmp78
.Lset17 = .Ltmp206-.Ltmp205             # Loc expr size
	.short	.Lset17
.Ltmp205:
	.byte	84                      # DW_OP_reg4
.Ltmp206:
	.quad	0
	.quad	0
.Ldebug_loc38:
	.quad	.Lfunc_begin4
	.quad	.Ltmp71
.Lset18 = .Ltmp208-.Ltmp207             # Loc expr size
	.short	.Lset18
.Ltmp207:
	.byte	81                      # DW_OP_reg1
.Ltmp208:
	.quad	.Ltmp71
	.quad	.Ltmp78
.Lset19 = .Ltmp210-.Ltmp209             # Loc expr size
	.short	.Lset19
.Ltmp209:
	.byte	88                      # DW_OP_reg8
.Ltmp210:
	.quad	.Ltmp109
	.quad	.Ltmp117
.Lset20 = .Ltmp212-.Ltmp211             # Loc expr size
	.short	.Lset20
.Ltmp211:
	.byte	88                      # DW_OP_reg8
.Ltmp212:
	.quad	0
	.quad	0
.Ldebug_loc43:
	.quad	.Ltmp70
	.quad	.Ltmp76
.Lset21 = .Ltmp214-.Ltmp213             # Loc expr size
	.short	.Lset21
.Ltmp213:
	.byte	84                      # DW_OP_reg4
.Ltmp214:
	.quad	.Ltmp78
	.quad	.Ltmp114
.Lset22 = .Ltmp216-.Ltmp215             # Loc expr size
	.short	.Lset22
.Ltmp215:
	.byte	84                      # DW_OP_reg4
.Ltmp216:
	.quad	0
	.quad	0
.Ldebug_loc48:
	.quad	.Ltmp71
	.quad	.Ltmp73
.Lset23 = .Ltmp218-.Ltmp217             # Loc expr size
	.short	.Lset23
.Ltmp217:
	.byte	16                      # DW_OP_constu
	.byte	0
.Ltmp218:
	.quad	.Ltmp73
	.quad	.Ltmp74
.Lset24 = .Ltmp220-.Ltmp219             # Loc expr size
	.short	.Lset24
.Ltmp219:
	.byte	82                      # DW_OP_reg2
.Ltmp220:
	.quad	.Ltmp78
	.quad	.Ltmp79
.Lset25 = .Ltmp222-.Ltmp221             # Loc expr size
	.short	.Lset25
.Ltmp221:
	.byte	83                      # DW_OP_reg3
.Ltmp222:
	.quad	.Ltmp83
	.quad	.Ltmp84
.Lset26 = .Ltmp224-.Ltmp223             # Loc expr size
	.short	.Lset26
.Ltmp223:
	.byte	82                      # DW_OP_reg2
.Ltmp224:
	.quad	.Ltmp90
	.quad	.Ltmp91
.Lset27 = .Ltmp226-.Ltmp225             # Loc expr size
	.short	.Lset27
.Ltmp225:
	.byte	82                      # DW_OP_reg2
.Ltmp226:
	.quad	.Ltmp111
	.quad	.Ltmp113
.Lset28 = .Ltmp228-.Ltmp227             # Loc expr size
	.short	.Lset28
.Ltmp227:
	.byte	82                      # DW_OP_reg2
.Ltmp228:
	.quad	0
	.quad	0
.Ldebug_loc55:
	.quad	.Ltmp71
	.quad	.Lfunc_end4
.Lset29 = .Ltmp230-.Ltmp229             # Loc expr size
	.short	.Lset29
.Ltmp229:
	.byte	16                      # DW_OP_constu
	.byte	0
.Ltmp230:
	.quad	0
	.quad	0
.Ldebug_loc59:
	.quad	.Ltmp74
	.quad	.Ltmp108
.Lset30 = .Ltmp232-.Ltmp231             # Loc expr size
	.short	.Lset30
.Ltmp231:
	.byte	16                      # DW_OP_constu
	.byte	1
.Ltmp232:
	.quad	.Ltmp108
	.quad	.Ltmp114
.Lset31 = .Ltmp234-.Ltmp233             # Loc expr size
	.short	.Lset31
.Ltmp233:
	.byte	90                      # DW_OP_reg10
.Ltmp234:
	.quad	0
	.quad	0
.Ldebug_loc63:
	.quad	.Ltmp75
	.quad	.Ltmp78
.Lset32 = .Ltmp236-.Ltmp235             # Loc expr size
	.short	.Lset32
.Ltmp235:
	.byte	85                      # DW_OP_reg5
.Ltmp236:
	.quad	.Ltmp82
	.quad	.Ltmp84
.Lset33 = .Ltmp238-.Ltmp237             # Loc expr size
	.short	.Lset33
.Ltmp237:
	.byte	85                      # DW_OP_reg5
.Ltmp238:
	.quad	.Ltmp89
	.quad	.Ltmp91
.Lset34 = .Ltmp240-.Ltmp239             # Loc expr size
	.short	.Lset34
.Ltmp239:
	.byte	85                      # DW_OP_reg5
.Ltmp240:
	.quad	.Ltmp92
	.quad	.Lfunc_end4
.Lset35 = .Ltmp242-.Ltmp241             # Loc expr size
	.short	.Lset35
.Ltmp241:
	.byte	16                      # DW_OP_constu
	.byte	0
.Ltmp242:
	.quad	0
	.quad	0
.Ldebug_loc69:
	.quad	.Ltmp80
	.quad	.Ltmp81
.Lset36 = .Ltmp244-.Ltmp243             # Loc expr size
	.short	.Lset36
.Ltmp243:
	.byte	85                      # DW_OP_reg5
.Ltmp244:
	.quad	.Ltmp87
	.quad	.Ltmp88
.Lset37 = .Ltmp246-.Ltmp245             # Loc expr size
	.short	.Lset37
.Ltmp245:
	.byte	85                      # DW_OP_reg5
.Ltmp246:
	.quad	0
	.quad	0
.Ldebug_loc72:
	.quad	.Ltmp96
	.quad	.Ltmp97
.Lset38 = .Ltmp248-.Ltmp247             # Loc expr size
	.short	.Lset38
.Ltmp247:
	.byte	85                      # DW_OP_reg5
.Ltmp248:
	.quad	.Ltmp97
	.quad	.Ltmp98
.Lset39 = .Ltmp250-.Ltmp249             # Loc expr size
	.short	.Lset39
.Ltmp249:
	.byte	82                      # DW_OP_reg2
.Ltmp250:
	.quad	0
	.quad	0
.Ldebug_loc75:
	.quad	.Ltmp103
	.quad	.Ltmp104
.Lset40 = .Ltmp252-.Ltmp251             # Loc expr size
	.short	.Lset40
.Ltmp251:
	.byte	82                      # DW_OP_reg2
.Ltmp252:
	.quad	.Ltmp104
	.quad	.Ltmp105
.Lset41 = .Ltmp254-.Ltmp253             # Loc expr size
	.short	.Lset41
.Ltmp253:
	.byte	81                      # DW_OP_reg1
.Ltmp254:
	.quad	0
	.quad	0
.Ldebug_loc78:
	.quad	.Lfunc_begin5
	.quad	.Ltmp141
.Lset42 = .Ltmp256-.Ltmp255             # Loc expr size
	.short	.Lset42
.Ltmp255:
	.byte	85                      # DW_OP_reg5
.Ltmp256:
	.quad	0
	.quad	0
.Ldebug_loc80:
	.quad	.Lfunc_begin5
	.quad	.Ltmp140
.Lset43 = .Ltmp258-.Ltmp257             # Loc expr size
	.short	.Lset43
.Ltmp257:
	.byte	84                      # DW_OP_reg4
.Ltmp258:
	.quad	.Ltmp140
	.quad	.Ltmp143
.Lset44 = .Ltmp260-.Ltmp259             # Loc expr size
	.short	.Lset44
.Ltmp259:
	.byte	83                      # DW_OP_reg3
.Ltmp260:
	.quad	0
	.quad	0
.Ldebug_loc84:
	.quad	.Ltmp147
	.quad	.Ltmp148
.Lset45 = .Ltmp262-.Ltmp261             # Loc expr size
	.short	.Lset45
.Ltmp261:
	.byte	80                      # DW_OP_reg0
.Ltmp262:
	.quad	0
	.quad	0
.Ldebug_loc86:
	.quad	.Ltmp149
	.quad	.Ltmp168
.Lset46 = .Ltmp264-.Ltmp263             # Loc expr size
	.short	.Lset46
.Ltmp263:
	.byte	94                      # DW_OP_reg14
.Ltmp264:
	.quad	0
	.quad	0
.Ldebug_loc89:
	.quad	.Ltmp150
	.quad	.Ltmp167
.Lset47 = .Ltmp266-.Ltmp265             # Loc expr size
	.short	.Lset47
.Ltmp265:
	.byte	95                      # DW_OP_reg15
.Ltmp266:
	.quad	0
	.quad	0
.Ldebug_loc92:
	.quad	.Ltmp151
	.quad	.Ltmp165
.Lset48 = .Ltmp268-.Ltmp267             # Loc expr size
	.short	.Lset48
.Ltmp267:
	.byte	86                      # DW_OP_reg6
.Ltmp268:
	.quad	0
	.quad	0
.Ldebug_loc95:
	.quad	.Ltmp153
	.quad	.Ltmp164
.Lset49 = .Ltmp270-.Ltmp269             # Loc expr size
	.short	.Lset49
.Ltmp269:
	.byte	16                      # DW_OP_constu
	.byte	1
.Ltmp270:
	.quad	.Ltmp164
	.quad	.Ltmp165
.Lset50 = .Ltmp272-.Ltmp271             # Loc expr size
	.short	.Lset50
.Ltmp271:
	.byte	93                      # DW_OP_reg13
.Ltmp272:
	.quad	.Ltmp165
	.quad	.Lfunc_end5
.Lset51 = .Ltmp274-.Ltmp273             # Loc expr size
	.short	.Lset51
.Ltmp273:
	.byte	16                      # DW_OP_constu
	.byte	1
.Ltmp274:
	.quad	0
	.quad	0
.Ldebug_loc99:
	.quad	.Ltmp155
	.quad	.Ltmp157
.Lset52 = .Ltmp276-.Ltmp275             # Loc expr size
	.short	.Lset52
.Ltmp275:
	.byte	92                      # DW_OP_reg12
.Ltmp276:
	.quad	.Ltmp157
	.quad	.Ltmp160
.Lset53 = .Ltmp278-.Ltmp277             # Loc expr size
	.short	.Lset53
.Ltmp277:
	.byte	83                      # DW_OP_reg3
.Ltmp278:
	.quad	0
	.quad	0
.Ldebug_loc102:
	.quad	.Ltmp157
	.quad	.Lfunc_end5
.Lset54 = .Ltmp280-.Ltmp279             # Loc expr size
	.short	.Lset54
.Ltmp279:
	.byte	16                      # DW_OP_constu
	.byte	0
.Ltmp280:
	.quad	0
	.quad	0
.Ldebug_loc106:
	.quad	.Ltmp158
	.quad	.Ltmp165
.Lset55 = .Ltmp282-.Ltmp281             # Loc expr size
	.short	.Lset55
.Ltmp281:
	.byte	82                      # DW_OP_reg2
.Ltmp282:
	.quad	0
	.quad	0
.Ldebug_loc108:
	.section	.debug_aranges,"",@progbits
	.section	.debug_ranges,"",@progbits
	.quad	.Ltmp24
	.quad	.Ltmp25
	.quad	.Ltmp27
	.quad	.Ltmp29
	.quad	0
	.quad	0
	.quad	.Ltmp24
	.quad	.Ltmp25
	.quad	.Ltmp27
	.quad	.Ltmp29
	.quad	0
	.quad	0
	.quad	.Ltmp53
	.quad	.Ltmp54
	.quad	.Ltmp56
	.quad	.Ltmp58
	.quad	0
	.quad	0
	.quad	.Ltmp77
	.quad	.Ltmp78
	.quad	.Ltmp101
	.quad	.Ltmp107
	.quad	0
	.quad	0
	.quad	.Ltmp158
	.quad	.Ltmp159
	.quad	.Ltmp161
	.quad	.Ltmp163
	.quad	0
	.quad	0
	.section	.debug_macinfo,"",@progbits
	.section	.debug_str,"MS",@progbits,1
.Linfo_string0:
	.asciz	 "clang version 3.3 (trunk 171645)"
.Linfo_string1:
	.asciz	 "prog2.c"
.Linfo_string2:
	.asciz	 "/scratch/mferdman/tests/prog2"
.Linfo_string3:
	.asciz	 "pi"
.Linfo_string4:
	.asciz	 "long long int"
.Linfo_string5:
	.asciz	 "SHORT"
.Linfo_string6:
	.asciz	 "powers"
.Linfo_string7:
	.asciz	 "term"
.Linfo_string8:
	.asciz	 "size"
.Linfo_string9:
	.asciz	 "INDEXER"
.Linfo_string10:
	.asciz	 "OutDig"
.Linfo_string11:
	.asciz	 "PrintVal"
.Linfo_string12:
	.asciz	 "PrintShort"
.Linfo_string13:
	.asciz	 "Print"
.Linfo_string14:
	.asciz	 "arctan"
.Linfo_string15:
	.asciz	 "_main"
.Linfo_string16:
	.asciz	 "dig"
.Linfo_string17:
	.asciz	 "INT"
.Linfo_string18:
	.asciz	 "val"
.Linfo_string19:
	.asciz	 "num"
.Linfo_string20:
	.asciz	 "x"
.Linfo_string21:
	.asciz	 "digits"
.Linfo_string22:
	.asciz	 "int"
.Linfo_string23:
	.asciz	 "multiplier"
.Linfo_string24:
	.asciz	 "denom"
.Linfo_string25:
	.asciz	 "sign"
.Linfo_string26:
	.asciz	 "denom2"
.Linfo_string27:
	.asciz	 "LONG"
.Linfo_string28:
	.asciz	 "NotZero"
.Linfo_string29:
	.asciz	 "divisor"
.Linfo_string30:
	.asciz	 "adv"
.Linfo_string31:
	.asciz	 "remain"
.Linfo_string32:
	.asciz	 "temp"
.Linfo_string33:
	.asciz	 "sum"
.Linfo_string34:
	.asciz	 "borrow"
.Linfo_string35:
	.asciz	 "carry"
.Linfo_string36:
	.asciz	 "argc"
.Linfo_string37:
	.asciz	 "argv"
.Linfo_string38:
	.asciz	 "char"
.Linfo_string39:
	.asciz	 "T1"
.Linfo_string40:
	.asciz	 "time_t"
.Linfo_string41:
	.asciz	 "T2"

	.section	".note.GNU-stack","",@progbits
