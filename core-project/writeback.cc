#include "writeback.h"
#include <iomanip>

void 
Writeback::do_reset()
{
  if(reset) 
    ew_uop_queue = queue<uop>();
  return;
}

void 
dump_values1()
{
#ifdef DEBUG_PRINT
  cout<<"rax="<<setw(16)<<setfill('0')<<regfile.rax<<endl;
  cout<<"rbx="<<setw(16)<<setfill('0')<<regfile.rbx<<endl;
  cout<<"rcx="<<setw(16)<<setfill('0')<<regfile.rcx<<endl;
  cout<<"rdx="<<setw(16)<<setfill('0')<<regfile.rdx<<endl;
  cout<<"rsi="<<setw(16)<<setfill('0')<<regfile.rsi<<endl;
  cout<<"rdi="<<setw(16)<<setfill('0')<<regfile.rdi<<endl;
  cout<<"rbp="<<setw(16)<<setfill('0')<<regfile.rbp<<endl;
  cout<<"rsp="<<setw(16)<<setfill('0')<<regfile.rsp<<endl;
  cout<<"r8="<<setw(16)<<setfill('0') <<regfile.r8<<endl;
  cout<<"r9="<<setw(16)<<setfill('0') <<regfile.r9<<endl;
  cout<<"r10="<<setw(16)<<setfill('0')<<regfile.r10<<endl;
  cout<<"r11="<<setw(16)<<setfill('0')<<regfile.r11<<endl;
  cout<<"r12="<<setw(16)<<setfill('0')<<regfile.r12<<endl;
  cout<<"r13="<<setw(16)<<setfill('0')<<regfile.r13<<endl;
  cout<<"r14="<<setw(16)<<setfill('0')<<regfile.r14<<endl;
  cout<<"r15="<<setw(16)<<setfill('0')<<regfile.r15<<endl;
  cout<<"rflags="<<endl;
  cout<<"ip=0x"<<hex<<(long)regfile.rip<<endl;
#endif
}

static int cycle_count = 0;

void 
Writeback::work()
{
  cyclecount++;

  if (reset)
    return;
  
  // Execute wasn't ready i guess?
  if (!in_ready) 				
    return;
  
  // queue is empty. we have no work to do so return
  if (ew_uop_queue.empty()) 			
    return;
  
  uop Op = ew_uop_queue.front();
	
#ifdef DEBUG
  cout<<"\n In Writeback. Address"<<hex<<Op.address;
  cout<<" Register being written to "<<Op.reg2<<". Value being written out.";
  cout<<Op.value2<<dec<<endl;
#endif
  
  regfile.rip = Op.address + Op.opsize;
  
  switch(Op.reg2) {
  case UD_R_RAX:
    regfile.rax = Op.value2;
    break;
  case UD_R_RBX:
    regfile.rbx = Op.value2;
    break;
  case UD_R_RCX:
    regfile.rcx = Op.value2;
    break;
  case UD_R_RDX:
    regfile.rdx = Op.value2;
    break;
  case UD_R_RSP:
    regfile.rsp = Op.value2;
    break;
  case UD_R_RBP:
    regfile.rbp = Op.value2;
    break;
  case UD_R_RSI:
    regfile.rsi = Op.value2;
    break;
  case UD_R_RDI:
    regfile.rdi = Op.value2;
    break;
  case UD_R_R8:
    regfile.r8 = Op.value2;
    break;
  case UD_R_R9:
    regfile.r9 = Op.value2;
    break;
  case UD_R_R10:
    regfile.r10 = Op.value2;
    break;
  case UD_R_R11:
    regfile.r11 = Op.value2;
    break;
  case UD_R_R12:
    regfile.r12 = Op.value2;
    break;
  case UD_R_R13:
    regfile.r13 = Op.value2;
    break;
  case UD_R_R14:
    regfile.r14 = Op.value2;
    break;
  case UD_R_R15:
    regfile.r15 = Op.value2;
    break;
  case UD_R_RIP:
    regfile.rip = Op.value2;
  default:
    break;
  }

  if(Op.opcode == UD_Icall || Op.opcode == UD_Iret\
     || Op.opcode == UD_Ipop) {
    
    regfile.rsp = Op.value3;    
  }
 
 else if(Op.opcode == UD_Imul || Op.opcode == UD_Idiv\
         || Op.opcode == UD_Iidiv || Op.src == IMUL_1) {

   regfile.rax = Op.value2;
   regfile.rdx = Op.value3;
 }
  
  dump_values1();
  ew_uop_queue.pop();
  
  return;
}
