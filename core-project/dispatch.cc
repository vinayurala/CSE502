#include "dispatch.h"
// #define DEBUG

void Dispatch::reset_regfile()
{
	regfile.rax = 0;
	regfile.rbx = 0;
	regfile.rcx = 0;
	regfile.rdx = 0;
	regfile.rsp = 0;
	regfile.rbp = 0;
	regfile.rsi = 0;
	regfile.rdi = 0;
	regfile.r8 = 0;
	regfile.r9 = 0;
	regfile.r10 = 0;
	regfile.r11 = 0;
	regfile.r12 = 0;
	regfile.r13 = 0;
	regfile.r14 = 0;
	regfile.r15 = 0;
}

void Dispatch::do_reset()
{
  if(reset){
    reset_regfile();
    dd_uop_queue = queue<uop>();
  }
  return;
}

void Dispatch::work()
{
	cyclecount++;
	// cout<<"\nDispatch "<<dec<<cyclecount<<endl;
	out_ready = false;
  
	if (reset)
    	return;
  
	if (clear){
		dd_uop_queue = queue<uop>();			//line needs to be set hi for each cycle that the pipeline is stalled for
    	return;
    }
  
	if (!in_ready)								// Decode wasn't ready i guess?
    	return;

	if (dd_uop_queue.empty())					// queue is empty. we have no work to do so return
		return;

	if(de_uop_queue.size()>0){
		// cout<<"returning. de_uop_queue full"<<endl;
		out_ready = true;
		return;
	}

	int i = 0;
	sc_addr front_addr = dd_uop_queue.front().address;

	while(i < dd_uop_queue.size() && dd_uop_queue.front().address == front_addr) 
	{
		uop Op = dd_uop_queue.front();
		if(Op.src == REG || Op.src == IMUL_2R || Op.src == IMUL_3)
		{
			switch(Op.reg1){
				case UD_R_RAX:
					Op.value1 = regfile.rax;
					break;
				case UD_R_RBX:
					Op.value1 = regfile.rbx;
					break;
				case UD_R_RCX:
					Op.value1 = regfile.rcx;
					break;
				case UD_R_RDX:
					Op.value1 = regfile.rdx;
					break;
				case UD_R_RSP:
					Op.value1 = regfile.rsp;
					break;
				case UD_R_RBP:
					Op.value1 = regfile.rbp;
					break;
				case UD_R_RSI:
					Op.value1 = regfile.rsi;
					break;
				case UD_R_RDI:
					Op.value1 = regfile.rdi;
					break;
				case UD_R_R8:
					Op.value1 = regfile.r8;
					break;
				case UD_R_R9:
					Op.value1 = regfile.r9;
					break;
				case UD_R_R10:
					Op.value1 = regfile.r10;
					break;
				case UD_R_R11:
					Op.value1 = regfile.r11;
					break;
				case UD_R_R12:
					Op.value1 = regfile.r12;
					break;
				case UD_R_R13:
					Op.value1 = regfile.r13;
					break;
				case UD_R_R14:
					Op.value1 = regfile.r14;
					break;
				case UD_R_R15:
					Op.value1 = regfile.r15;
					break;
				case UD_R_RIP:
					Op.value1 = Op.address+Op.opsize;
					break;
				default:
					// Op.value1 = -1;
					break;
			}
		}
		else if(Op.src == IMMED || Op.src == IMUL_2I || Op.src == LOADMUL)
		{
			Op.reg1 = scratchreg;
			Op.value1 = Op.immed;
		}

		switch(Op.reg2){
			case UD_R_RAX:
				Op.value2 = regfile.rax;
				break;
			case UD_R_RBX:
				Op.value2 = regfile.rbx;
				break;
			case UD_R_RCX:
				Op.value2 = regfile.rcx;
				break;
			case UD_R_RDX:
				Op.value2 = regfile.rdx;
				break;
			case UD_R_RSP:
				Op.value2 = regfile.rsp;
				break;
			case UD_R_RBP:
				Op.value2 = regfile.rbp;
				break;
			case UD_R_RSI:
				Op.value2 = regfile.rsi;
				break;
			case UD_R_RDI:
				Op.value2 = regfile.rdi;
				break;
			case UD_R_R8:
				Op.value2 = regfile.r8;
				break;
			case UD_R_R9:
				Op.value2 = regfile.r9;
				break;
			case UD_R_R10:
				Op.value2 = regfile.r10;
				break;
			case UD_R_R11:
				Op.value2 = regfile.r11;
				break;
			case UD_R_R12:
				Op.value2 = regfile.r12;
				break;
			case UD_R_R13:
				Op.value2 = regfile.r13;
				break;
			case UD_R_R14:
				Op.value2 = regfile.r14;
				break;
			case UD_R_R15:
				Op.value2 = regfile.r15;
				break;
			case UD_R_RIP:
				Op.value2 = Op.address+Op.opsize;
				break;
			default:
				// Op.value2 = -1;
				break;
		}

		switch(Op.reg3){
			case UD_R_RAX:
				Op.value3 = regfile.rax;
				break;
			case UD_R_RBX:
				Op.value3 = regfile.rbx;
				break;
			case UD_R_RCX:
				Op.value3 = regfile.rcx;
				break;
			case UD_R_RDX:
				Op.value3 = regfile.rdx;
				break;
			case UD_R_RSP:
				Op.value3 = regfile.rsp;
				break;
			case UD_R_RBP:
				Op.value3 = regfile.rbp;
				break;
			case UD_R_RSI:
				Op.value3 = regfile.rsi;
				break;
			case UD_R_RDI:
				Op.value3 = regfile.rdi;
				break;
			case UD_R_R8:
				Op.value3 = regfile.r8;
				break;
			case UD_R_R9:
				Op.value3 = regfile.r9;
				break;
			case UD_R_R10:
				Op.value3 = regfile.r10;
				break;
			case UD_R_R11:
				Op.value3 = regfile.r11;
				break;
			case UD_R_R12:
				Op.value3 = regfile.r12;
				break;
			case UD_R_R13:
				Op.value3 = regfile.r13;
				break;
			case UD_R_R14:
				Op.value3 = regfile.r14;
				break;
			case UD_R_R15:
				Op.value3 = regfile.r15;
				break;
			case UD_R_RIP:
				Op.value3 = Op.address+Op.opsize;
				// Op.value3 = Op.address + Op.opsize;
				break;
			default:
				// Op.value3 = -1;
				break;
		}

		if (Op.opcode == UD_Icall || Op.opcode == UD_Iret || Op.opcode == UD_Ipop || Op.opcode == UD_Ipush || Op.opcode == UD_Ipushfq){
			Op.reg3 = UD_R_RSP;
			Op.value3 = regfile.rsp;
			// cout<<"Address:"<<hex<<Op.address<<"RSP value"<<Op.value3<<endl;
		}
		else if (Op.opcode == UD_Imul || Op.opcode == UD_Idiv || Op.opcode == UD_Iidiv){
			Op.reg2 = UD_R_RAX;
			Op.value2 = regfile.rax;
			Op.reg3 = UD_R_RDX;
			Op.value3 = regfile.rdx;
		}
		else if (Op.opcode == UD_Inop){
			Op.reg1 = Op.reg2 = Op.reg3 = 0;
			Op.value1 = Op.value2 = Op.value3 = 0;
		}
		else if (Op.opcode == UD_Icqo){
			Op.reg1 = UD_R_RAX;
			Op.value1 = regfile.rax;
			Op.reg2 = UD_R_RDX;
			Op.value2 = 0;
		}
		else if (Op.opcode == UD_Iimul) {
			if(Op.src == IMUL_1) {
				Op.reg2 = UD_R_RAX;
				Op.value2 = regfile.rax;
				Op.reg3 = UD_R_RDX;
				Op.value3 = regfile.rdx;		
			}
			else if (Op.src == IMUL_3){
				if(Op.reg3 == 0){
					Op.reg3 = scratchreg;
					Op.value3 = Op.immed;
				} 
			}
		}

		
		#ifdef DEBUG
			cout<<hex<<"\nAddress in dispatch"<<Op.address<<endl;
			cout<<"Opcode in dispatch"<<dec<<Op.opcode<<endl;
			cout<<"REG1 in dispatch"<<Op.reg1<<endl;
			cout<<"value1 in dispatch"<<Op.value1<<endl;
			cout<<"REG2 in dispatch"<<Op.reg2<<hex<<endl;
			cout<<"Value2 in dispatch"<<Op.value2<<hex<<endl;
			cout<<"REG3 in dispatch"<<Op.reg3<<hex<<endl;
			cout<<"Value3 in dispatch"<<Op.value3<<hex<<endl;
		#endif
		
		de_uop_queue.push_back(Op);
		dd_uop_queue.pop();
		i++;
	}
	out_ready = true;
	
	return;
}



//  sc_signal<mem_op>   i_op[i_ports];        NONE - stable state READ - when you need work done.
//	sc_signal<int>      i_tagin[i_ports];     Addr & ~15
//	sc_signal<sc_addr>  i_addr[i_ports];      Addr & ~15
//	sc_in<bool>         i_ready[i_ports];     Check if ready. true for ready and false otherwise.
//	sc_in<int>          i_tagout[i_ports];    Check with Addr & ~15
//	sc_in<sc_inst>      i_data[i_ports];      Data read out of cache
//	
//	sc_signal<sc_inst>  out_data[i_ports];      Data to Decode stage
//	sc_addr RIP;                              RIP for next Execute.
//  sc_signal<sc_addr>  out_addr[i_ports];
