#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <utility>
#include <queue>
#include <sstream>

#include "core_cse502.h"
#include "systemc.h"

using namespace std;

static bool stack_has_opcode;
static bool stack_has_modrm;

struct uop
{
  string opcode;
  string reg1;
  string reg2;
  string immed;
};

class opcodes 
{
  string prefix;
  string opcode1;
  string opcode2;
  string modrm;
  string sib;
  string immed_disp;
public: opcodes() {
  prefix = string();
  opcode1 = string();
  opcode2 = string();
  modrm = string();
  sib = string();
  immed_disp = string();
}
  void clear_opcodes() 
  {
    prefix = opcode1 = opcode2 = modrm = sib = immed_disp = string();
  }

};

queue<uop> uop_queue;
queue<opcodes> opcode_queue;

void 
init_reg_map() 
{
  reg_map.insert(make_pair("0000", "rax"));
  reg_map.insert(make_pair("0001", "rcx"));
  reg_map.insert(make_pair("0010", "rdx"));
  reg_map.insert(make_pair("0011", "rbx"));
  reg_map.insert(make_pair("0100", "rsp"));
  reg_map.insert(make_pair("0101", "rbp"));
  reg_map.insert(make_pair("0110", "rsi"));
  reg_map.insert(make_pair("0111", "rdi"));
  reg_map.insert(make_pair("1000", "r8"));
  reg_map.insert(make_pair("1001", "r9"));
  reg_map.insert(make_pair("1010", "r10"));
  reg_map.insert(make_pair("1011", "r11"));
  reg_map.insert(make_pair("1100", "r12"));
  reg_map.insert(make_pair("1101", "r13"));
  reg_map.insert(make_pair("1110", "r14"));
  reg_map.insert(make_pair("1111", "r15"));  
}

string 
infer_type(sc_bv<8> instBits)
{
  switch (instBits)
    {
    case "01001000" :                                           // 0x48 - REX Prefix
    case "01001001" :                                           // 0x49 - REX Prefix
    case "01001100" :                                           // 0x4C - REX Prefix
    case "01001101" : return "prefix";                          // 0x4D - REX Prefix
    case "11000111" :                                           // 0xC7 - mov
    case "00110001" :                                           // 0x31 - xor
    case "10001001" :                                           // 0x89 - mov
    case "10000011" : if (stack_has_opcode && stack_has_modrm)  // 0x83 - and
	                return "immed/disp";
                      else if (stack_has_opcode) {
			stack_has_modrm = true;
			return "modrm"
                      }
                      else {
	                stack_has_opcode = true;
	                return "opcode";
                      }
    case "00001111" :        
    case "00000101" :                        // 0x0f 0x05 - syscall
    case "11111111" : return "opcode";       // 0xff - call
    default         : return "NOP";
    }

  // should never come here, but just in case
  return "ERR";
}

string
get_opcode(string bit_stream, bool *next_byte_op)
{
  if (*next_byte_op) {
    *next_byte_op = false;
    if (bit_stream == "00000101")
      return "syscall";
  }

  switch(bit_stream)
    {
    case "00001111" : *next_byte_op = true; 
                      return string();
    case "10001001" : return "move /r";
    case "11000111" : return "move /immed";
    case "10000011" : return "and /immed";
    case "00110001" : return "xor /r";
    case "11111111" : return "call";
    default         : return "nop";    
    }
}

string 
alt_reverse (string temp)
{
  string ret, scratch;
  int i, j;

  for(i = (temp.len() - 1), j = 0; i > 0; i-=2, j+=2) {
    scratch[j] = temp[i-1];
    scratch[j+1] = temp[i]
  }
  ret.assign(8-temp.len(), scratch[0]);
  ret += scratch;
  
  return ret;
}

void 
crack_opcodes(queue<opcodes> opcode_list)
{
  int i;
  struct uop temp_uop;
  string prefix, opcode1, opcode2, immed_val, disp_val, mrm_val, modrm_val;
  bool gpr_64bit = false, next_byte_op = false, sib_present = false;
  int i;
  string phys_reg = "r";
  int phys_reg_idx = 16; // phys_reg starts from r16
  opcodes temp;
  string reg1, reg2, t_str;
  
  while (!opcode_list.empty()) {

    temp = opcode_list.front(); 
    opcode_list.pop();

    opcode1 = get_opcode(temp.opcode1);
    if (!temp.opcode2.empty())
      opcode2 = get_opcode(temp_opcode2);
    
    if (temp.sib.empty() && temp.immed_disp.empty()) {    // reg to reg op
      
      if (temp.prefix == "01001001") {
	reg1 = "0" + temp.modrnm.substr(2,3);
	reg2 = "1" + temp.modrm.substr(5,3); 
      }
      
      else if (temp.prefix == "01001101") {
	reg1 = "1" + temp.modrnm.substr(2,3);
	reg2 = "1" + temp.modrnm.substr(5,3);
      }
      
      else if (temp.prefix == "01001100") {
	reg1 = "1" + temp.modrnm.substr(2,3);
	reg2 = "0" + temp.modrnm.substr(5,3);
      }
      
      else {
	reg1 = "0" + temp.modrnm.substr(2,3);
	reg2 = "0" + temp.modrnm.substr(5,3);
      }
      
      uop.opcode = temp.opcode1;
      uop.reg1 = reg_map.find(reg1)->second;
      uop.reg2 = reg_map.find(reg2)->second;

    }
 
    else if (temp.sib.empty()) {             // reg and immed
      if (tem.prefix == "01001100") 
	reg1 = "1" + temp.modrm.substr(5,3);
      else
	reg1 = "0" + temp.modrm.substr(5,3);
 
      uop.opcode = temp.opcode1;
      uop.reg1 = reg_map.find(reg1)->second;
      
      t_str = temp.immed_disp;
      uop.immed = alt_reverse(t_str);
      uop.reg2 = string();
    }
    uop_queue.push(uop);
  }
}


void 
decode(sc_bv<16*8> instBits)
{
  unsigned long tInt;
  bool oldInst = false;
  string oldInstBuf = string();
  opcodes opcode_list;
  bool inst_in_next_line = false;
  int i, j;
  string opcode_type;
  stack<string> prev_opc_type;
  string temp_modrm;

  stack_has_opcode = false;
  stack_has_modrm = false;
  
  for (i = 127, j= 0; i >= 0; i -= 8) {
    opcode_type = infer_type(instBits.range(i, i - 7));
    
    assert(opcode_type != "ERR");

    if (opcode_type == "NOP") {
      opcode_list.opcode = "NOP";
      opcode_queue.push(opcode_list);
      opcode_list.clear_opcodes();
      if (!prev_opc_type.empty())
	prev_opc_type.empty();
      
    }

    if (!prev_opc_type.empty()) {
      if (opcode_type == "opcode" && prev_opc_type.top() == "prefix") {
	opcode_list.prefix += instBits.range(i, i - 7);
	prev_opc_type.push(opcode_type);
      }

      if (opcode_type == "modrm" && prev_opc_type.top() == "opcode") {
	opcode_list.modrm += instBits.range(i, i - 7);
	temp_modrm = opcode_list.modrm;
	prev_opc_type.push(opcode_type);
      }
      
      if (opcode_type == "opcode" && prev_opc_type.top() == "opcode") {
	opcode_list.opcode2 += instBits.range(i, i - 7);
	prev_opc_type.push(opcode_type);
      }

      if (opcode_type == "immed/disp") {
	if (prev_opc_type == "modrm" && temp_modrm.substr(0,2) != "11") {
	  if (temp_modrm.substr(2,3))
	    opcode_list.sib = instBits.range(i, i-7);
	}
	else
	  opcode_list.immed_disp += instBits.range(i, i - 7);
      }
    }

    else if (!prev_opc_type.empty() && opcode_type == "prefix") {
      opcode_queue.push(opcode_list);
      opcode_list.clear_opcodes();
      prev_opc_type.empty();
      opcode_list.prefix += instBits.range(i, i - 7);
      prev_opc_type.push(opcode_type);
      stack_has_opcode = false;
      stack_has_modrm = false;
    }

    else 
      opcode_list.immed_disp += instBits.range(i, i-7);
  }

  // cout<<"\nDetected opcode in stream: \n";
  // for (i = 0; i < j; i++) {
  //   temp = opcodes();
  //   temp = opcode_list.front
    
  // }

  // uop struct initialization follow here
  crack_opcodes(opcode_list);
  
}
