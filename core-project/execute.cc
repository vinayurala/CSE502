#include <cmath>

#include "execute.h"
#include "common.h"

// #define DEBUG
// #define DEBUG_UNIMPL_INSTR
// #define DEBUG_EXEC_PATH
// #define DEBUG_OP
// #define DEBUG_REGISTERS
// #define DEBUG_UNEXPECTED_ADDR
// #define DEBUG_LOAD
// #define DEBUG_TEMP


#define MASK_CF 0
#define	MASK_PF 2
#define	MASK_AF 4
#define	MASK_ZF 6
#define	MASK_SF 7
#define	MASK_OF 11

// long long eflags;
bitset<64> eflags;

void Execute::do_reset()
{
	if(reset){
		de_uop_queue = deque<uop>();
	}
	return;
}

void dump_values()
{
#ifdef DEBUG_REGISTERS
	cout<<__FILE__<<"\nREGFILE"<<endl;
	cout<<" rax "<<regfile.rax<<endl;
	cout<<" rbx " <<regfile.rbx<<endl;
	cout<<" rcx " <<regfile.rcx<<endl;
	cout<<" rdx " <<regfile.rdx<<endl;
	cout<<" rsp " <<regfile.rsp<<endl;
	cout<<" rbp " <<regfile.rbp<<endl;
	cout<<" rsi " <<regfile.rsi<<endl;
	cout<<" rdi " <<regfile.rdi<<endl;
	cout<<" r8  "  <<regfile.r8<<endl;
	cout<<" r9  "  <<regfile.r9<<endl;
	cout<<" r10 " <<regfile.r10<<endl;
	cout<<" r11 " <<regfile.r11<<endl;
	cout<<" r12 " <<regfile.r12<<endl;
	cout<<" r13 " <<regfile.r13<<endl;
	cout<<" r14 " <<regfile.r14<<endl;
	cout<<" r15 " <<regfile.r15<<endl;
	cout<<" rip " <<regfile.rip<<endl;
	cout<<" EFL " <<eflags<<endl;
#endif
}

void dump_op(uop Op){
#ifdef DEBUG_OP
	cout<<endl<<__FILE__;
	cout<<" Src "<<Op.src;
	cout<<" Address "<<hex<<Op.address;
	cout<<" opcode "<<Op.opcode;
	cout<<" reg1 "<<Op.reg1;
	cout<<" value1 "<<Op.value1;
	cout<<" reg2 "<<Op.reg2;
	cout<<" value2 "<<Op.value2;
	cout<<" reg3 "<<Op.reg3;
	cout<<" value3 "<<Op.value3;
	cout<<" immed "<<Op.immed;
	cout<<" opsize "<<Op.opsize<<endl;
#endif
}

void Execute::do_shift()
{
	int countmask = 63;

	int count = Op.value1 & countmask;
	long long tempval = Op.value2;
	while (count != 0){
		if(Op.opcode == UD_Isal || Op.opcode == UD_Ishl){
			if ((tempval & (1ULL<<63)) == (1ULL<<63))
				eflags.set(MASK_CF);
			else
				eflags.reset(MASK_CF);
			tempval = tempval * 2;
		}
		else if (Op.opcode == UD_Isar)
		{
			if ((tempval & 1) == 1)
				eflags.set(MASK_CF);
			else
				eflags.reset(MASK_CF);
			tempval = tempval >> 1;
		}
		else if (Op.opcode == UD_Ishr)
		{
			if ((tempval & 1) == 1)
				eflags.set(MASK_CF);
			else
				eflags.reset(MASK_CF);
			tempval = (unsigned long long)tempval >> 1;
		}
		// cout<<"\n\nDo_shift, tempval"<<tempval<<endl<<endl;
		count--;
	}
	if (Op.value1 & countmask == 1){
		if(Op.opcode == UD_Isal || Op.opcode == UD_Ishl){
			int OF = ((tempval & (1ULL << 63)) ^ eflags.test(MASK_CF));
			if(OF)
				eflags.set(MASK_OF);
			else
				eflags.reset(MASK_OF);
		}
		else if (Op.opcode == UD_Isar)
		{
			eflags.reset(MASK_OF);
		}
		else if (Op.opcode == UD_Ishr)
		{
			int OF = (Op.value2 & (1ULL << 63));
			if(OF)
				eflags.set(MASK_OF);
			else
				eflags.reset(MASK_OF);
		}
	}
	Op.value2 = tempval;
}


void Execute::do_jump(){
	rip_changed = true;
	change_RIP = true;
	if(Op.src == REG) {
		int jmp_src_reg = 0;
		assert(jmp_src_reg != REG);
		new_RIP = (sc_addr)Op.value1;
		expected_addr = (sc_addr)Op.value1;
	}
	else if(Op.src == IMMED){
		new_RIP = Op.address + Op.opsize + Op.value1;
		expected_addr = (sc_addr)Op.address + Op.opsize + Op.value1;
	}
	clear_out = true;
}

void Execute::do_syscall()
{
	#ifdef DEBUG
	dump_values();
	#endif
	switch(prev_reg1){
		case UD_R_RAX:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,prev_value1,regfile.rdi,regfile.rsi,
															 regfile.rdx,regfile.r10,regfile.r8,regfile.r9);
			break;
		case UD_R_RDX:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,regfile.rdi,regfile.rsi,
															 prev_value1,regfile.r10,regfile.r8,regfile.r9);
			break;
		case UD_R_RSP:
			regfile.rax = Core::syscall(prev_value1,Op.address,regfile.rax,regfile.rdi,regfile.rsi,
															 regfile.rdx,regfile.r10,regfile.r8,regfile.r9);
			break;
		case UD_R_RSI:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,regfile.rdi,prev_value1,
															 regfile.rdx,regfile.r10,regfile.r8,regfile.r9);
			break;
		case UD_R_RDI:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,prev_value1,regfile.rsi,
															 regfile.rdx,regfile.r10,regfile.r8,regfile.r9);
			break;
		case UD_R_R8:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,regfile.rdi,regfile.rsi,
															 regfile.rdx,regfile.r10,prev_value1,regfile.r9);
			break;
		case UD_R_R9:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,regfile.rdi,regfile.rsi,
															 regfile.rdx,regfile.r10,regfile.r8,prev_value1);
			break;
		case UD_R_R10:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,regfile.rdi,regfile.rsi,
															 regfile.rdx,prev_value1,regfile.r8,regfile.r9);
			break;
		default:
			regfile.rax = Core::syscall(regfile.rsp,Op.address,regfile.rax,regfile.rdi,regfile.rsi,
															 regfile.rdx,regfile.r10,regfile.r8,regfile.r9);
			break;
	}
	prev_reg2 = prev_reg1;
	prev_reg1 = UD_R_RAX;
	prev_value2 = prev_value1;
	prev_value1 = regfile.rax;
	// cout<<"\n\nrax value after syscall"<<hex <<prev_value1<<endl;
}


void Execute::work()
{
	out_ready = false;
	change_RIP = false;
	cyclecount++;
	// cout<<"\n\n\n\n\nExecute "<<dec<<cyclecount<<endl;
	
	if (reset)
		return;
	
	if (clear){
		clear_out = false;
		de_uop_queue.clear();
	}
	else if(state == STATE_READ){
		if(!d_ready[port]) {	//spin on this.
			return;
		}
		else {
			//stahp = false;
			switch(Op.opcode){
				case UD_Iret:
				{
					if(d_tagout[port] != Op.value3)
						return;
					sc_addr returnaddr = d_data[port].read();
					new_RIP = returnaddr;
					Op.value3 += 8;
					change_RIP = true;
					expected_addr = returnaddr;
					stackpointer = Op.value3;
					ew_uop_queue.push(Op);
					de_uop_queue.pop_front();
					out_ready = true;
					state = STATE_NORMAL;
					clear_out = true;
					#ifdef DEBUG_LOAD
					cout<<"\nRet. Stack returned "<<hex <<returnaddr<<" at stackpointer "<<Op.value3<<endl;
					dump_op(Op);
					dump_values();
					#endif
					return;
				}
				case UD_Ipop:
				{
					if(d_tagout[port] != Op.value3)
						return;
					Op.value2 = d_data[port].read();
					Op.value3 += 8;
					expected_addr = Op.address + Op.opsize;
					stackpointer = Op.value3;
					ew_uop_queue.push(Op);
					de_uop_queue.pop_front();
					out_ready = true;
					state = STATE_NORMAL;
					prev_reg2 = prev_reg1;
					prev_reg1 = Op.reg2;
					prev_value2 = prev_value1;
					prev_value1 = Op.value2;
					#ifdef DEBUG_LOAD
					cout<<"\nPop. Stack returned "<<hex<<Op.value2 <<" at stackpointer "<<Op.value3<<endl;
					dump_op(Op);
					dump_values();
					#endif
					return;
				}
				case UD_Iload:
				{
					if(d_tagout[port] != Op.value1)
						return;
					Op.value2 = d_data[port].read();
					// expected_addr = Op.address + Op.opsize;
					ew_uop_queue.push(Op);
					de_uop_queue.pop_front();
					out_ready = true;
					state = STATE_NORMAL;
					prev_reg2 = prev_reg1;
					prev_reg1 = Op.reg2;
					prev_value2 = prev_value1;
					prev_value1 = Op.value2;
					#ifdef DEBUG_LOAD
					cout<<"\nLoad. Memory returned " <<Op.value2<<endl;
					dump_op(Op);
					dump_values();
					#endif
					return;
				}
			}
		}
	}

	if (!in_ready)						// Dispatch wasn't ready i guess?
		return;

	if(ew_uop_queue.size()>1){
		// cout<<"returning ew_uop_queue full"<<endl;
		out_ready = true;
		return;
	}

	if (de_uop_queue.empty())			// queue is empty. we have no work to do so return
		return;
	// cout<<"de_uop_queue not empty"<<endl;

	Op = de_uop_queue.front();

	if(Op.address == prev_addr){
		// cout<<"Op.address == prev_addr "<<endl;
		expected_addr = Op.address;
	}

	int i = 0;
	sc_addr front_addr = Op.address;
	while(i < de_uop_queue.size() && de_uop_queue[i].address == front_addr) {
		if(de_uop_queue[i].reg1 == prev_reg2)
			de_uop_queue[i].value2 = prev_value2;
		else if(de_uop_queue[i].reg2 == prev_reg2)
			de_uop_queue[i].value2 = prev_value2;
		if(de_uop_queue[i].reg1 == prev_reg1)
			de_uop_queue[i].value1 = prev_value1;
		else if(de_uop_queue[i].reg2 == prev_reg1)
			de_uop_queue[i].value2 = prev_value1;
		// dump_op(de_uop_queue[i]);
		i++;
	}

	if(Op.address != expected_addr && !firstrun){
		#ifdef DEBUG_UNEXPECTED_ADDR
		cout<<__FILE__<<"\nUnexpected address! Expected: "<<hex <<expected_addr<<" Got: "<<Op.address<<endl;
		#endif
		de_uop_queue.pop_front();
		return;
	}

	if(firstrun)
		firstrun = false;

	if(Op.reg1 == load_store_reg)
		Op.value1 = offsetreg_value;

	if(Op.reg2 == load_store_reg)
		Op.value2 = offsetreg_value;

	if(Op.reg1 == prev_reg2)
		Op.value1 = prev_value2;
	
	if(Op.reg2 == prev_reg2)
		Op.value2 = prev_value2;

	if(Op.reg3 == prev_reg2)
		Op.value3 = prev_value2;

	if(Op.reg1 == prev_reg1)
		Op.value1 = prev_value1;
	
	if(Op.reg2 == prev_reg1)
		Op.value2 = prev_value1;

	if(Op.reg3 == prev_reg1)
		Op.value3 = prev_value1;

	if((Op.reg1 == UD_R_RSP) && (stackpointer != 0))
		Op.value1 = stackpointer;

	if((Op.reg2 == UD_R_RSP) && (stackpointer != 0))
		Op.value2 = stackpointer;

	if((Op.reg3 == UD_R_RSP) && (stackpointer != 0))
		Op.value3 = stackpointer;

	#ifdef DEBUG_EXEC_PATH
		cout<<"\n\nstackpointer"<<hex<<stackpointer<<endl;
		cout<<__FILE__<<"\n0 Expected: "<<hex <<expected_addr<<" Got: "<<Op.address <<" Op.size: "<<Op.opsize<<endl;
		dump_op(Op);
		dump_values();
	#endif

	switch(Op.opcode){
		case UD_Imov:
		{
			// cout<<__FILE__<<"reg1 "<<Op.reg1<<" value1 "<<Op.value1<<" reg2 "<<Op.reg2<<" Op.Value2 "<<Op.value2<<" IMMED "<<Op.immed<<endl;
			Op.value2 = Op.value1;

			break;
		}
		case UD_Icqo:
		{
			if( (Op.value1 & (1ULL<<63)) == 1ULL<<63 )
				Op.value2 =	Op.value2 | ~0x0;
			else
				Op.value2 = 0;
			break;
		}
		case UD_Iadd:
		{
			Op.value2 = Op.value2 + Op.value1;
			break;
		}
		case UD_Isub:
		{
			Op.value2 = Op.value2 - Op.value1;
			break;
		}
		case UD_Idec:
		{
			Op.reg2 = Op.reg1;
			Op.value2 =	Op.value1 - 1;
			break;
		}
		case UD_Iinc:
		{
			Op.reg2 = Op.reg1;
			Op.value2 =	Op.value1 + 1;
			break;
		}
		case UD_Imul:
		{
			if(Op.value1 == 0 || Op.value2 == 0)
			{	Op.value2 = 0;
				break;
			}
			int msb1 = 64 - __builtin_clz(Op.value1);
			int msb2 = 64 - __builtin_clz(Op.value2);
			if ((msb1+msb2) > 65 ) {	// need to deal with both rax and rdx
				__uint128_t tempval = (__uint128_t)Op.value2 * Op.value1;
				Op.value2 = (unsigned long long)tempval;
				Op.value3 = (unsigned long long)(tempval>>64);
			}
			else
			{
				Op.value2 = (unsigned long long)Op.value2 * Op.value1;
				Op.value3 = 0;
			}
			break;
		}
		case UD_Idiv:
		{
			if(Op.value3 != 0)	{	// need to deal with both rax and rdx
				__uint128_t tempval = ((__uint128_t)Op.value3<<64) | Op.value2;
				Op.value2 = (unsigned long long)tempval / Op.value1;
				Op.value3 = (unsigned long long)tempval % Op.value1;
			}
			else{
				Op.value3 = (unsigned long long)Op.value2 % Op.value1;
				Op.value2 = (unsigned long long)Op.value2 / Op.value1;
			}
			break;	
		}
		case UD_Iidiv:
		{
			if(Op.value3 != 0)	{	// need to deal with both rax and rdx
				__int128_t tempval = ((__int128_t)Op.value3<<64) | Op.value2;
				Op.value2 = tempval / Op.value1;
				Op.value3 = tempval % Op.value1;
			}
			else{
				Op.value3 = Op.value2 % Op.value1;
				Op.value2 = Op.value2 / Op.value1;
			}
			break;	
		}
		case UD_Iimul:
		{
			if (Op.src == IMUL_1){
				__int128_t tempval = (__int128_t)Op.value2 * Op.value1;
				Op.value2 = (long long)tempval;
				Op.value3 = (long long)(tempval>>64);
				if(Op.value3 == 0){
					eflags.reset(MASK_CF);
					eflags.reset(MASK_OF);
				}
				else {
					eflags.set(MASK_CF);
					eflags.set(MASK_OF);
				}
			}
			else if(Op.src == IMUL_2I || Op.src == IMUL_2R) {
				Op.value2 = Op.value2 * Op.value1;
				__int128_t tempval = (__int128_t)Op.value2 * Op.value1;
				if( tempval != Op.value2){
					eflags.set(MASK_CF);
					eflags.set(MASK_OF);
				}
				else {
					eflags.reset(MASK_CF);
					eflags.reset(MASK_OF);
				}
			}
			else if(Op.src == IMUL_3) {
				Op.value2 = Op.value3 * Op.value1;
				__int128_t tempval = (__int128_t)Op.value3 * Op.value1;
				if( tempval != Op.value2){
					eflags.set(MASK_CF);
					eflags.set(MASK_OF);
				}
				else {
					eflags.reset(MASK_CF);
					eflags.reset(MASK_OF);
				}
			}
			else if (Op.src == LOADMUL)	{
				Op.value2 = Op.value2 * Op.value1;
			}
			break;
		}
		case UD_Iand:
		{
			Op.value2 =	Op.value2 & Op.value1;
			break;
		}
		case UD_Ior:
		{
			Op.value2 =	Op.value2 | Op.value1;
			break;
		}
		case UD_Ixor:
		{
			Op.value2 = Op.value2 ^ Op.value1;
			break;
		}
		case UD_Ineg:
		{
			Op.reg2 = Op.reg1;
			if ( Op.value1 == 0 )
				eflags.reset(MASK_CF);
			else
				eflags.set(MASK_CF);
			Op.value2 =	-Op.value1;
			break;
		}
		case UD_Inop:
		{
			break;
		}
		case UD_Isyscall:
		{
			do_syscall();
			break;
		}
		case UD_Icall:
		{
			Op.value3 -= 8;
			d_op[port] = WRITE;
			d_tagin[port] = Op.value3;
			d_addr[port] = Op.value3;
			d_dout[port].write(Op.address+Op.opsize);
			// cout<<__FILE__<<hex<<"\nAddress pushed to stack"<<(Op.address+Op.opsize)<<"at address"<<Op.value3;
			rip_changed = true;
			change_RIP = true;
			if(Op.src == REG) {
				new_RIP = (sc_addr)Op.value1;
				expected_addr = (sc_addr)Op.value1;
			}
			else if(Op.src == IMMED){
				new_RIP = Op.address + Op.opsize + Op.value1;
				expected_addr = (sc_addr)Op.address + Op.opsize + Op.value1;
				// cout<<"\nCall immed"<<expected_addr<<" "<<Op.address<<" "<<Op.opsize<<" "<<Op.value1<<"\n";
			}
			clear_out = true;
			stackpointer = Op.value3;
			// cout<<__FILE__ <<hex <<"Addr "<<Op.address<<" size "<<Op.opsize<<endl <<"Reg1 "<<Op.reg1 <<" value1 "<<Op.value1  <<" Reg2 "<<Op.reg2 <<" Value2 "<<Op.value2 <<" Immed "<<Op.immed <<" Address " <<Op.address<<endl;
			break;
		}
		case UD_Iret:
		{ 
			d_op[port] = READ;
			d_tagin[port] = Op.value3;
			d_addr[port] = Op.value3;
			// cout<<"\nRet trying to read from address "<<Op.value3<<endl;
			state = STATE_READ;
			//stahp = true;
			return;
		}
		case UD_Ipop:
		{
			d_op[port] = READ;
			d_tagin[port] = Op.value3;
			d_addr[port] = Op.value3;
			state = STATE_READ;
			//stahp = true;
			#ifdef DEBUG
			cout<<__FILE__<<"POP instruction" <<hex <<"Addr "<<Op.address<<" size "<<Op.opsize<<endl <<"Reg1 "<<Op.reg1 <<" value1 "<<Op.value1  <<" Reg2 "<<Op.reg2 <<" Value2 "<<Op.value2 <<" Immed "<<Op.immed <<" Address " <<Op.address <<" Op.reg3 "<<Op.reg3 <<" Op.Value3 "<<Op.value3<<endl;
			#endif
			return;
		}
		case UD_Ipush:
		{
			Op.value3 -= 8;
			d_op[port] = WRITE;
			d_tagin[port] = Op.value3;
			d_addr[port] = Op.value3;
			d_dout[port].write(Op.value1);
			stackpointer = Op.value3;
			#ifdef DEBUG
			cout<<"\n\n"<<__FILE__<<": Value3 =  "<<hex<<Op.value3<<dec<<endl;
			#endif
			break;
		}
		case UD_Iload:
		{
			d_op[port] = READ;
			d_tagin[port] = Op.value1;
			d_addr[port] = Op.value1;
			state = STATE_READ;
			//stahp = true;
			#ifdef DEBUG_TEMP
			cout<<__FILE__<<"Load instruction" <<hex <<"Addr "<<Op.address<<" size "<<Op.opsize<<endl <<"Reg1 "<<Op.reg1 <<" value1 "<<Op.value1  <<" Reg2 "<<Op.reg2 <<" Value2 "<<Op.value2 <<" Immed "<<Op.immed <<" Address " <<Op.address <<" Op.reg3 "<<Op.reg3 <<" Op.Value3 "<<Op.value3<<endl;
			#endif
			return;
		}
		case UD_Istore:
		{
			d_op[port] = WRITE;
			d_tagin[port] = Op.value2;
			d_addr[port] = Op.value2;
			d_dout[port].write(Op.value1);
			#ifdef DEBUG
			cout<<"\n\n"<<__FILE__<<": Value3 =  "<<hex<<Op.value3<<dec<<endl;
			#endif
			break;
		}
		case UD_Ipushfq:
		{
			Op.value3 -= 8;
			d_op[port] = WRITE;
			d_tagin[port] = Op.value3;
			d_addr[port] = Op.value3;
			d_dout[port].write(eflags.to_ulong());
			stackpointer = Op.value3;
			#ifdef DEBUG
			cout<<__FILE__<<"\nPushed Flags\n: Value3 =  "<<hex<<Op.value3<<dec<<endl;
			#endif
			break;
		}
		case UD_Itest:
		{
			long long tempval = Op.value1 & Op.value2;
			
			// cout<<__FILE__<<__LINE__<<"\n\n tempval "<<tempval<<" value1 "<<Op.value1<<" value2 "<<Op.value2<<endl;

			if( (tempval & (1ULL<<63)) == 1 )
				eflags.set(MASK_SF);
			else
				eflags.reset(MASK_SF);

			if (tempval == 0)
				eflags.set(MASK_ZF);
			else
				eflags = eflags.reset(MASK_ZF);

			eflags.reset(MASK_CF);
			eflags.reset(MASK_OF);
			break;
		}
		case UD_Icmp:	// Check CF SF ZF and OF.
		{
			long long tempval = Op.value2 - Op.value1;

			if (tempval == 0)
				eflags.set(MASK_ZF);
			else
				eflags.reset(MASK_ZF);

			if ((tempval & (1ULL<<63)) == 1ULL<<63)
				eflags.set(MASK_SF);
			else
				eflags.reset(MASK_SF);
			  
			if ((unsigned long long)Op.value2 < (unsigned long long)Op.value1) //ERROR? IMPLEMENT 'OF' Flag.
				eflags.set(MASK_CF);
			else
				eflags.reset(MASK_CF);

			// Overflow - check only the sign bits of the input and output
			int sign_op1 = Op.value1 & (1ULL << 63);
			int sign_op2 = Op.value2 & (1ULL << 63);
			int sum_sign = tempval & (1ULL << 63);
			if ((!sign_op1 && !sign_op2 && sum_sign) || (sign_op1 && sign_op2 && !sum_sign))
				eflags.set(MASK_OF);
			else
				eflags.reset(MASK_OF);

			// cout<<"in CMP after cmp. Tempval: "<<tempval<<" Eflags:" <<eflags<<" Address"<<hex<<Op.address<<dec<<endl;
			break;
		}

		case UD_Ijmp:
		{
			do_jump();
			break;
		}
		case UD_Ija:
		{
			// cout<<"ja"<<eflags.test(MASK_CF)<<eflags.test(MASK_ZF)<<(eflags.test(MASK_CF) | eflags.test(MASK_ZF));
			if ((eflags.test(MASK_CF) | eflags.test(MASK_ZF)) == 0)
				do_jump();
				break;
		}
		case UD_Ijz:
		{	
			if (eflags.test(MASK_ZF)) {
				do_jump();
			}
			break;
		}
		case UD_Ijnz:
		{	
			if (eflags.test(MASK_ZF) == false)
				do_jump();
			break;
		}
		case UD_Ijb:
		{
			if (eflags.test(MASK_CF))
				do_jump();
			break;
		}
		case UD_Ijl:
		{
			if (eflags.test(MASK_SF) ^ eflags.test(MASK_OF))
				do_jump();
			break;
		}
		case UD_Ijle:
		{
			if (((eflags.test(MASK_SF) ^ eflags.test(MASK_OF)) | eflags.test(MASK_ZF)) == 1)
				do_jump();
			break;
		}
		case UD_Ijg:
		{
			if (((eflags.test(MASK_SF) ^ eflags.test(MASK_OF)) | eflags.test(MASK_ZF)) == 0)
				do_jump();
			break;
		}
		case UD_Ijge:
		{
			if ((eflags.test(MASK_SF) ^ eflags.test(MASK_OF)) == 0)
				do_jump();
			break;
		}
		case UD_Icmovnz:
		{
			if (eflags.test(MASK_ZF) == false)
				Op.value2 = Op.value1;
			break;
		}
		case UD_Icmovns:
		{
			if (eflags.test(MASK_SF) == false)
				Op.value2 = Op.value1;
			break;
		}
		case UD_Icmovg:
		{
			if (((eflags.test(MASK_SF) ^ eflags.test(MASK_OF)) | eflags.test(MASK_ZF)) == 0)
				Op.value2 = Op.value1;
			break;
		}
		case UD_Ishr:
		case UD_Isar:
		case UD_Ishl:
		case UD_Isal:
		{
			do_shift();
			break;
		}
		default:
		{
			cout<<__FILE__<<"Couldn't run this unknown instruction: "<<Op.opcode<<" at address "<<hex<<Op.address<<dec<<endl;
			#ifdef DEBUG_UNIMPL_INSTR
				assert(0);
			#endif
			break;
		}
	}

	if (!rip_changed){
		expected_addr = Op.address + Op.opsize;
		prev_addr = Op.address;
	}
	else
		rip_changed = false;
	
	if (Op.opcode != UD_Inop && Op.opcode != UD_Isyscall && Op.reg2 != 0) {
		prev_value2 = prev_value1;
		prev_value1 = Op.value2;
		prev_reg2 = prev_reg1;
		prev_reg1 = Op.reg2;
		if (Op.reg2 == UD_R_RSP)
			stackpointer = Op.value2;
	}

	if(Op.reg2 == load_store_reg)
		offsetreg_value = Op.value2;

	#ifdef DEBUG_TEMP
		cout<<__FILE__<<"After Switch"<<endl;
		dump_op(Op);
		cout <<__FILE__ <<"1 New expected Address: "<<hex <<expected_addr<<" Current Address: "<<Op.address<<endl;	
	#endif

	ew_uop_queue.push(Op);
	de_uop_queue.pop_front();

	out_ready = true;

	return;
}
