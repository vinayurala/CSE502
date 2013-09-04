#include <iostream>
#include <cmath>
#include <climits>
#include <bitset>
#include <iomanip>
#include <sstream>

#include "systemc.h"
#include "decoder.h"

using namespace std;

// #define DEBUG
// #define PRINT_DEBUG
// #define CPP_PRINT

static int die_counter = 0;
queue<string> scratch_q;
queue<int> size_bytes;
queue<sc_addr> addr_q;

int Decoder::byte_seek_ptr = 0;
string Decoder::byte_stream = string();
int Decoder::stream_len = 0;


int Decoder::input_hook(ud_t *ud_obj)
{
  if (byte_seek_ptr >= stream_len)
    return UD_EOI;

  istringstream scratch(byte_stream.substr(byte_seek_ptr, 2));
  int num;
  
  scratch>>hex>>num;

  assert(num <= 0xFF);
  
  byte_seek_ptr += 3;
  return (num & 0xFF);
}

string Decoder::bin2hex(string input)
{
  ostringstream c;
  int i, j;
  bitset<128> scratch_bitset;
  string str_set, scratch_str;

  str_set = string();

  for (i = 0, j = 0; i < input.length(); i+= 8, j++) {
    scratch_str.clear();                        
    scratch_str.assign(input, i, 8);
    scratch_bitset = bitset<128> (scratch_str);
    c<<hex<<setw(2)<<setfill('0')<<scratch_bitset.to_ulong();
    c<<" ";
  }

  str_set = c.str();
  c.str(string());

  return str_set;

}

uint64_t Decoder::sign_extend(long long immed_val, int size)
{
  uint64_t ret_val;
  ostringstream o;
  int num_bits;
  string temp, scratch;

  o<<hex<<immed_val;
  num_bits = (o.str().length()) * 4;        // Can use log2 function as well; optimizations to be done later
  o.str(string());

  // cout<<"\n\n"<<__FILE__<<": sign_extend: immed = "<<hex<<immed_val<<dec<<"\tsize: "<<size<<endl;

  if (num_bits == size) {
    unsigned int msb = (1 << (size-1)) & immed_val;
    o<<hex<<immed_val;
    temp = o.str();
    char ch1 = (msb) ? 'f' : '0';
    temp = scratch.assign(16-temp.length(), ch1) + temp; 
    istringstream i(temp);
    // cout<<"\n"<<__FILE__<<": temp = "<<temp<<endl;
    i>>hex>>ret_val;
    o.str(string());
    // cout<<"\n"<<__FILE__<<": ret_val: "<<hex<<ret_val<<dec<<endl;
  }

  else
    ret_val = immed_val;

  return ret_val;
}

// void Decoder::clear_struct(struct uop *temp_uop)
// {
//   // Since we don't touch value1 and value2, they won't be initialized
//   temp_uop->opcode = temp_uop->reg1 = temp_uop->reg2 = 1;
//   temp_uop->immed = INT_MIN;
//   temp_uop->src = NO_SRC;
// }


void Decoder::push2q(int mnemonic, int reg1, int reg2, int reg3, uint64_t immed_val, int source)
{
  struct uop temp_uop;
  
  temp_uop.opcode = mnemonic;
  temp_uop.reg1 = reg1;
  temp_uop.reg2 = reg2;
  temp_uop.reg3 = reg3;
  temp_uop.src = (enum src_type)source;
  temp_uop.immed = immed_val;                     // sign extended immed_val
  temp_uop.opsize = size_bytes.front();
  temp_uop.address = addr_q.front();

  dd_uop_queue.push(temp_uop);
}

// UDIS86 return format
// ud_obj.operand[0] = target
// ud_obj.operand[1] = source
void Decoder::crack_opcodes(queue<ud_t> opcodes)
{
   struct uop temp_uop;
  ud_t ud_obj;
  int offset, scale, i, j, opsize;
  enum ud_mnemonic_code load_o_store;
  
  while (!opcodes.empty()) {
    ud_obj = opcodes.front();
    opcodes.pop();

#ifdef PRINT_DEBUG
    cout<<"\n"<<__FILE__<<": "<<dec<<__LINE__<<" ASM: "<<ud_insn_asm(&ud_obj);
#endif

// #ifdef CPP_PRINT
//     // cout<<"\n"<<__FILE__<<": ASM: "<<ud_insn_asm(&ud_obj);
//     cout<<"\n"<<__FILE__<<": "<<dec<<__LINE__<<" ud_obj.operand[0].type = "<<ud_obj.operand[0].type<<" ud_obj.operand[1].type = "<<ud_obj.operand[1].type<<" ud_obj.operand[2].type "<<ud_obj.operand[2].type<<endl;
//     cout<<"\n"<<__FILE__<<": "<<__LINE__<<" ud_obj.operand[1].scale = "<<(int)ud_obj.operand[1].scale<<endl;
// #endif

    // retq, syscall etc
    if (ud_obj.operand[0].type == UD_NONE && ud_obj.operand[1].type == UD_NONE) {    
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<" : "<<dec<<__LINE__<<" mnenomic = "<<ud_obj.mnemonic<<endl; 
#endif
      push2q(ud_obj.mnemonic, UD_NONE, UD_NONE, UD_NONE, UD_NONE, NO_SRC);
      addr_q.pop();
      size_bytes.pop();
      continue;
    }

    // imul - can't think a better way of handling it
    if (ud_obj.mnemonic == UD_Iimul) {
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<" : "<<dec<<__LINE__<<" mnenomic = "<<ud_obj.mnemonic<<endl;
#endif
      int third_operand = (ud_obj.operand[2].type != UD_NONE) ? (ud_obj.operand[2].type == UD_OP_REG ? 1 : 2) : 0;
      int second_operand = (ud_obj.operand[1].type != UD_NONE) ? (ud_obj.operand[1].type == UD_OP_REG ? 1 : 2) : 0;

      // cout<<"\n\n"<<__FILE__<<":"<<__LINE__<<" second operand = "<<second_operand<<" third operand = "<<third_operand<<endl;
      
      // imul dst, src1, src2
      if (third_operand == 1)
        push2q(ud_obj.mnemonic, ud_obj.operand[1].base, ud_obj.operand[0].base, ud_obj.operand[2].base, UD_NONE, IMUL_3);

      // imul dst, src1, immed
      else if (third_operand == 2)
        push2q(ud_obj.mnemonic, ud_obj.operand[1].base, ud_obj.operand[0].base, UD_NONE, sign_extend(ud_obj.operand[2].lval.uqword, ud_obj.operand[2].size), IMUL_3);

      else {
        // imul dst, src
        if (second_operand == 1)
          push2q(ud_obj.mnemonic, ud_obj.operand[1].base, ud_obj.operand[0].base, UD_NONE, UD_NONE, IMUL_2R);
     
        // imul dst, immed
        else if (second_operand == 2)
          push2q(ud_obj.mnemonic, UD_NONE, ud_obj.operand[0].base, UD_NONE, sign_extend(ud_obj.operand[2].lval.uqword, ud_obj.operand[2].size), IMUL_2I);
      
        else
          // imul src
          push2q(ud_obj.mnemonic, ud_obj.operand[0].base, UD_NONE, UD_NONE, UD_NONE, IMUL_1);
      }
      addr_q.pop();
      size_bytes.pop();
      continue;
    }

    // reg to reg 
    if (ud_obj.operand[0].type == UD_OP_REG && ud_obj.operand[1].type == UD_OP_REG) {
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<" : "<<dec<<__LINE__<<" mnenomic = "<<ud_obj.mnemonic<<endl;
      cout<<"\n\n"<<__FILE__<<" : "<<dec<<__LINE__<<" operand[0] type = "<<ud_obj.operand[0].type<<" operand[1] type = "<<ud_obj.operand[1].type<<endl;
#endif
      push2q(ud_obj.mnemonic, ud_obj.operand[1].base, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<":"<<dec<<__LINE__<<" mnemonic = "<<ud_obj.mnemonic<<" reg1 = "<<ud_obj.operand[0].base<<" reg2 = "<<ud_obj.operand[1].base<<hex<<" address = "<<addr_q.front()<<endl; 
#endif
      addr_q.pop();
      size_bytes.pop();
      
      continue;
    }

    // jmp immed_val      
    else if (ud_obj.operand[0].type == UD_OP_JIMM) {                                      
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<" : "<<dec<<__LINE__<<" mnenomic = "<<ud_obj.mnemonic<<endl;
#endif
      push2q(ud_obj.mnemonic, UD_NONE, UD_NONE, UD_NONE, sign_extend(ud_obj.operand[0].lval.uqword, ud_obj.operand[0].size), IMMED);
      addr_q.pop();
      size_bytes.pop();
      continue;
    }

    // callq, push etc
    else if (ud_obj.operand[1].type == UD_NONE && ud_obj.operand[0].type != UD_OP_MEM) {    
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<": "<<dec<<__LINE__<<" mnemonic: "<<ud_obj.mnemonic<<endl;
#endif
      if (ud_obj.mnemonic == UD_Ipop )    
        push2q(ud_obj.mnemonic, UD_NONE, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);
      else
        push2q(ud_obj.mnemonic, ud_obj.operand[0].base, UD_NONE, UD_NONE, UD_NONE, REG);
      addr_q.pop();
      size_bytes.pop();
      continue;
    }

    // sar(l) with one operand
    else if (ud_obj.operand[0].type == UD_OP_REG && ud_obj.operand[1].type == UD_OP_CONST) {
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<": "<<dec<<__LINE__<<" mnemonic: "<<ud_obj.mnemonic<<endl;
#endif
      push2q(ud_obj.mnemonic, UD_NONE, ud_obj.operand[0].base, UD_NONE, 0x1, IMMED);
      addr_q.pop();
      size_bytes.pop();
    }

    // immed to reg
    else if (ud_obj.operand[1].type == UD_OP_IMM && ud_obj.operand[0].type == UD_OP_REG) { 
#ifdef CPP_PRINT
      cout<<"\n\n"<<__FILE__<<" : "<<dec<<__LINE__<<" mnenomic = "<<ud_obj.mnemonic<<endl;
#endif
      push2q(ud_obj.mnemonic, UD_NONE, ud_obj.operand[0].base, UD_NONE, sign_extend(ud_obj.operand[1].lval.uqword, ud_obj.operand[1].size), IMMED);
      addr_q.pop();
      size_bytes.pop();
      continue;
    }

    // reg with displacement
    else if (ud_obj.operand[1].type == UD_OP_MEM || ud_obj.operand[0].type == UD_OP_MEM) {          
      i = (ud_obj.operand[0].type == UD_OP_MEM) ? 0: 1;  
      j = (i + 1) % 2;
      
      // cout<<"\n\n"<<__FILE__<<": i = "<<i<<endl;
      load_o_store = ((ud_obj.mnemonic == UD_Ilea) ? UD_Ilea : ((i == 0) ? UD_Istore : UD_Iload));
      if (ud_obj.operand[1].type == UD_NONE)
        load_o_store = UD_Iload;

#ifdef CPP_PRINT
        cout<<"\n"<<__FILE__<<":"<<dec<<__LINE__<<": mnemonic = "<<dec<<ud_obj.mnemonic<<endl;
        cout<<"\n\n"<<__FILE__<<":"<<dec<<__LINE__<<": operand_i_index = "<<(int)ud_obj.operand[i].index<<endl;
#endif

      // opcode immed(src_reg), dst_reg
      // if ((int)ud_obj.operand[i].scale == 0) {
      if (ud_obj.operand[i].index == UD_NONE) {
#ifdef CPP_PRINT
        cout<<"\n"<<__FILE__<<":"<<dec<<__LINE__<<": mnemonic = "<<dec<<ud_obj.mnemonic<<endl;
        cout<<"\n\n"<<__FILE__<<":"<<dec<<__LINE__<<": operand_i_scale = "<<(int)ud_obj.operand[i].scale<<endl;
#endif
        offset = sign_extend(ud_obj.operand[i].lval.uqword, (int)ud_obj.operand[i].offset);
        
        // Copy over the value to a scratch_reg
        push2q(UD_Imov, ud_obj.operand[i].base, load_store_reg, UD_NONE, UD_NONE, REG);
        // Add the sign extended offset      
        if (offset)
          push2q(UD_Iadd, UD_NONE, load_store_reg, UD_NONE, offset, IMMED);


        // Load in case of compare or test; no matter where the operands are
        if (ud_obj.mnemonic == UD_Icmp || ud_obj.mnemonic == UD_Itest) {
#ifdef CPP_PRINT
          cout<<"\n\n"<<__FILE__<<" :" <<dec<<__LINE__<<"\nud_obj.operand[0].base = "<<ud_obj.operand[0].base<<endl;
#endif
          // load
          push2q(UD_Iload, load_store_reg, scratchregls, UD_NONE, UD_NONE, REG);
          // Actual op to do
          if (ud_obj.operand[j].base != UD_NONE)
            push2q(ud_obj.mnemonic, scratchregls, ud_obj.operand[j].base, UD_NONE, UD_NONE, REG);
          else
            push2q(ud_obj.mnemonic, UD_NONE, scratchregls, UD_NONE, sign_extend(ud_obj.operand[j].lval.uqword, ud_obj.operand[j].size) , IMMED);
          
        }
        else if (load_o_store == UD_Iload) {
          // load          
          push2q(load_o_store, load_store_reg, scratchregls, UD_NONE, UD_NONE, REG);
          // Actual op to do
          push2q(ud_obj.mnemonic, scratchregls, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);
        }
        
        else if (load_o_store == UD_Istore)  {
          // Actual op to do
          push2q(ud_obj.mnemonic, ud_obj.operand[1].base, scratchregls, UD_NONE, UD_NONE, REG);
          // store 
          push2q(load_o_store, scratchregls, load_store_reg, UD_NONE, UD_NONE, REG);

        }

        else {                         
          // lea no need to load values
          push2q(UD_Imov, load_store_reg, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);
        }

        // Restore the value of offset added to the register
        // push2q(UD_Isub, UD_NONE, ud_obj.operand[i].base, UD_NONE, offset, IMMED);

        size_bytes.pop();
        addr_q.pop();
        continue;
      }

      // immed(base, index, scale), dest
      else if (ud_obj.operand[i].index != UD_NONE) {                        
#ifdef CPP_PRINT
        cout<<"\n"<<__FILE__<<":"<<dec<<__LINE__<<": mnemonic = "<<dec<<ud_obj.mnemonic<<endl;
        cout<<"\n\n"<<__FILE__<<":"<<dec<<__LINE__<<"\nMnemonic and cmp: "<<(ud_obj.mnemonic == UD_Icmp)<<endl;
#endif
        // if ((int)ud_obj.operand[i].scale == 0)
        //   ud_obj.operand[i].scale = (uint8_t)1;

        if (ud_obj.operand[i].base == ud_obj.operand[i].index) {      // base == index; so base *= (scale + 1)

          // Move the base register to a scratch register
          push2q(UD_Imov, ud_obj.operand[i].base, load_store_reg, UD_NONE, UD_NONE, REG);
          // base = base * scale + 1
          if ((int)ud_obj.operand[i].scale != 0)
            push2q(UD_Iimul, UD_NONE, load_store_reg, UD_NONE, (int)ud_obj.operand[i].scale + 1, LOADMUL);

          // if (offset) base = base + offset
          if ((int)ud_obj.operand[i].offset) {
            offset = sign_extend(ud_obj.operand[i].lval.uqword, (int)ud_obj.operand[i].offset);
            push2q(UD_Iadd, UD_NONE, load_store_reg, UD_NONE, offset, IMMED);
          }
          
          // Do the actual op we're meant to
          if (ud_obj.mnemonic == UD_Ilea)
            push2q(UD_Imov, load_store_reg, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);

          else if (ud_obj.mnemonic == UD_Icmp || ud_obj.mnemonic == UD_Itest) {
            push2q(UD_Iload, load_store_reg, scratchregls, UD_NONE, UD_NONE, REG);
            if (ud_obj.operand[j].base != UD_NONE)
              push2q(ud_obj.mnemonic, scratchregls, ud_obj.operand[j].base, UD_NONE, UD_NONE, REG);
            else
              push2q(ud_obj.mnemonic, UD_NONE, scratchregls, UD_NONE, sign_extend(ud_obj.operand[j].lval.uqword, ud_obj.operand[j].size), IMMED);
          }

          else {
            if (load_o_store == UD_Iload) {
              push2q(UD_Iload, load_store_reg, scratchregls, UD_NONE, UD_NONE, REG);
              push2q(ud_obj.mnemonic, scratchregls, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);
            }
            else {
              if (ud_obj.operand[j].base != UD_NONE)
                push2q(ud_obj.mnemonic, ud_obj.operand[j].base, scratchregls, UD_NONE, UD_NONE, REG);
              else
                push2q(ud_obj.mnemonic, UD_NONE, scratchregls, UD_NONE, sign_extend(ud_obj.operand[j].lval.uqword, ud_obj.operand[j].size), IMMED);
              push2q(load_o_store, scratchregls, load_store_reg, UD_NONE, UD_NONE, REG);
            }
          }

          // // if (offset) base = base - offset
          // if ((int)ud_obj.operand[i].offset) {
          //   push2q(UD_Isub, UD_NONE, ud_obj.operand[i].base, UD_NONE, offset, IMMED);
          // }

          // // base = base / scale
          // push2q(UD_Idiv, UD_NONE, ud_obj.operand[i].base, UD_NONE, (int)ud_obj.operand[i].scale + 1, IMMED);
        }
        else {                                                   // base = base + index * scale
          // Move the value of the index register to a scratch register
          push2q(UD_Imov, ud_obj.operand[i].index, load_store_reg, UD_NONE, UD_NONE, REG);
          // index = scale * index
          // push2q(UD_Imul, UD_NONE, ud_obj.operand[i].index, UD_NONE, (int)ud_obj.operand[i].scale, IMMED);
          if ((int)ud_obj.operand[i].scale != 0)
            push2q(UD_Iimul, UD_NONE, load_store_reg, UD_NONE, (int)ud_obj.operand[i].scale, LOADMUL);

          bool base_present;
          if (ud_obj.operand[i].base == UD_NONE)
            base_present = false;
          else
            base_present = true;

          // base = base + index
          if (base_present)
            push2q(UD_Iadd, ud_obj.operand[i].base, load_store_reg, UD_NONE, UD_NONE, REG);

          // if (offset) base = base + offset
          if ((int)ud_obj.operand[i].offset) {
            offset = sign_extend(ud_obj.operand[i].lval.uqword, (int)ud_obj.operand[i].offset);
            push2q(UD_Iadd, UD_NONE, load_store_reg, UD_NONE, offset, IMMED);
          }
          
          // Do the actual op we were meant to
          // lea
          if (ud_obj.mnemonic == UD_Ilea)
            push2q(UD_Imov, load_store_reg, ud_obj.operand[j].base, UD_NONE, UD_NONE, REG);

          // cmp || test
          else if (ud_obj.mnemonic == UD_Icmp || ud_obj.mnemonic == UD_Itest) {
            // cout<<"\n\n"<<__FILE__<<" : "<<__LINE__<<" operand[j].base = "<<ud_obj.operand[j].base<<" operand[i].base = "<<ud_obj.operand[i].base<<endl;
            push2q(UD_Iload, load_store_reg, scratchregls, UD_NONE, UD_NONE, REG);
            if (ud_obj.operand[j].base != UD_NONE)
              push2q(ud_obj.mnemonic, scratchregls, ud_obj.operand[j].base, UD_NONE, UD_NONE, REG);
            else
              push2q(ud_obj.mnemonic, UD_NONE, scratchregls, UD_NONE, sign_extend(ud_obj.operand[j].lval.uqword, ud_obj.operand[j].size), IMMED);
          }

          else {
            if (load_o_store == UD_Iload) {
              push2q(load_o_store, load_store_reg, scratchregls, UD_NONE, UD_NONE, REG);
              push2q(ud_obj.mnemonic, scratchregls, ud_obj.operand[0].base, UD_NONE, UD_NONE, REG);
            }
            else {
              if (ud_obj.operand[j].base != UD_NONE)
                push2q(ud_obj.mnemonic, ud_obj.operand[j].base, scratchregls, UD_NONE, UD_NONE, REG);
              else
                push2q(ud_obj.mnemonic, UD_NONE, scratchregls, UD_NONE, sign_extend(ud_obj.operand[j].lval.uqword, ud_obj.operand[j].size), IMMED);
              push2q(load_o_store, scratchregls, load_store_reg, UD_NONE, UD_NONE, REG);
            }
          }
        }
        size_bytes.pop();
        addr_q.pop();
        continue;
      }
    }
  }
}

void Decoder::build_byte_stack(string bit_stream)
{
  string scratch;
  int i;
  
  for (i = 0; i < bit_stream.length(); i+= 3) {
    scratch.assign(bit_stream, i, 2);
    scratch_q.push(scratch);
  }

}

void Decoder::decode_opcodes(sc_bv<128> inData)
{
  string bit_stream, scratch;
  ud_t ud_obj;
  int rem_bytes = 0;
  int tot_decoded_bytes = 0, inv_bytes = 0, ctr = 0;
  int decoded_bytes, start_pos;
  uint8_t *buf;
  int pos = in_alignedaddr;
 
  queue<ud_t> opcodes;
  sc_addr temp_addr;

#ifdef DEBUG
    unsigned long long test_not_null = inData.to_uint();       // Will overflow, but doesn't matter
  if (!test_not_null)
    die_counter++;

  else
    die_counter = 0;

  assert(die_counter < 5);    
#endif

  if (first_run) {
    temp_addr = in_addr;
  }

  else if (RIP_jump) 
    temp_addr = in_addr;

  else
    temp_addr = last_good_addr;

  ud_init(&ud_obj);
  ud_set_mode(&ud_obj, 64);
  ud_set_syntax(&ud_obj, UD_SYN_ATT);
  
  bit_stream = bin2hex(inData.to_string());
  // cout<<"\n\n"<<__FILE__<<": Original bit_stream = "<<bit_stream<<endl;
  // cout<<"\n"<<__FILE__<<": rem_string = "<<rem_string<<endl;

  if (first_run) {
    while (bit_stream[0] == '0' || bit_stream[0] == ' ') {
      ctr = 0;
      if (ctr == bit_stream.length())
        break;
      bit_stream.erase(bit_stream.begin()); 
      ctr++;
    }
    temp_addr += pos;
    first_run = false;
  }

  // cout<<"\n\n"<<__FILE__<<": pos: "<<pos<<endl;
  if (!rem_string.empty() && !RIP_jump) {
    if (pos) {
      bit_stream.insert(pos, rem_string);         
      bit_stream.insert(pos - 1, " ");
    }
    else
      bit_stream = rem_string + bit_stream;
    
  }
  else if (RIP_jump) {
    while (bit_stream[0] == '0' || bit_stream[0] == ' ') {
      ctr = 0;
      if (ctr == bit_stream.length())
        break;
      bit_stream.erase(bit_stream.begin()); 
      ctr++;
    }
    temp_addr += pos;
    // cout<<"\n\n"<<__FILE__<<": temp_addr = "<<hex<<temp_addr<<dec<<endl;
    // cout<<"\n\n"<<__FILE__<<": RIP_jump:  bit_stream = "<<bit_stream<<endl;
    RIP_jump = false;
  }

  build_byte_stack (bit_stream);
  size_bytes = queue<int>();
  addr_q = queue<sc_addr>();

  Decoder::byte_seek_ptr = 0;
  Decoder::byte_stream = bit_stream;
  Decoder::stream_len = bit_stream.length();

  #ifdef PRINT_DEBUG
  cout<<"\n"<<__FILE__<<": bit_stream = "<<bit_stream<<endl;
  #endif

  buf = (uint8_t *)bit_stream.c_str();
  ud_set_input_buffer(&ud_obj, buf, stream_len);
  ud_set_input_hook(&ud_obj, input_hook);
  rem_string = string();
  
  while (1) {
    decoded_bytes = ud_disassemble(&ud_obj);

    if (!decoded_bytes) {
      while (!scratch_q.empty()) {
        rem_string += scratch_q.front() + " ";
        scratch_q.pop();
      }
      break;
    }

    if (ud_obj.mnemonic == UD_Iinvalid) {
      while (!scratch_q.empty()) {
        rem_string += scratch_q.front() + " ";
        scratch_q.pop();
      }
      last_good_addr = temp_addr;
      // cout<<"\n"<<__FILE__<<": last_good_addr = "<<last_good_addr<<"\ttemp_addr = "<<temp_addr<<endl;
      // cout<<"\n"<<__FILE__<<": rem_string = "<<rem_string<<endl;
      continue;
    }
    // cout<<"\n\n"<<__FILE__<<": ASM: "<<ud_insn_asm(&ud_obj);
    size_bytes.push(decoded_bytes);
    addr_q.push(temp_addr);
    // cout<<"\n"<<__FILE__<<": temp_addr: "<<hex<<temp_addr.to_ulong()<<dec<<endl;
    temp_addr += decoded_bytes;
    last_good_addr = temp_addr;
    // cout<<"\n"<<__FILE__<<": Decode temp_addr: "<<hex<<temp_addr<<endl;

    while (decoded_bytes) {
      if (!scratch_q.empty())
        scratch_q.pop();
      decoded_bytes--;
    }

    opcodes.push(ud_obj);
  }
  
  crack_opcodes(opcodes);
#ifdef PRINT_DEBUG
  print_uops(dd_uop_queue);
#endif
  
}

void Decoder::work() 
{
  if (reset)
    return;

  if (!in_ready)
    return;

  if (clear) {                     // Make this more efficient later
    return;
  }
 
  out_ready = false;
  decode_opcodes(in_data);
  out_ready = true;
}

void Decoder::do_reset()
{
  if (reset)
    reset_flag = true;
}

void Decoder::print_uops(queue<uop> uop_list)
{
  queue<uop> scratch(uop_list);
  struct uop scratch_uop;
  int idx = 0;

  cout<<"\n"<<__FILE__<<":"<<__LINE__<<" Uops: \n";
  while (!uop_list.empty()) {
    scratch_uop = uop_list.front();
    uop_list.pop();

    if (scratch_uop.opcode == UD_Isyscall || scratch_uop.opcode == UD_Iret){
      cout<<"\nOpcode = "<<dec<<scratch_uop.opcode;
      cout<<"\nOpsize = "<<dec<<scratch_uop.opsize;
      cout<<"\nAddress = "<<hex<<scratch_uop.address;
      continue;
    }

    cout<<"\nOpcode = "<<dec<<scratch_uop.opcode;
    if (scratch_uop.src == REG)
      cout<<"\nReg1 = "<<dec<<scratch_uop.reg1;
    else if(scratch_uop.src == IMMED)
      cout<<"\nImmed = "<<hex<<scratch_uop.immed;

    else if (scratch_uop.src == IMUL_3) {
      cout<<"\nReg1 = "<<dec<<scratch_uop.reg1;
      cout<<"\nReg2 = "<<dec<<scratch_uop.reg2;
      if (scratch_uop.reg3 != UD_NONE)
        cout<<"\nReg3 = "<<dec<<scratch_uop.reg3;
      else
        cout<<"\nImmed = "<<hex<<scratch_uop.immed;
    }

    else if (scratch_uop.src == IMUL_2R || scratch_uop.src == IMUL_2I) {
      cout<<"\nReg2 = "<<dec<<scratch_uop.reg2;
      if (scratch_uop.reg1 != UD_NONE)
        cout<<"\nReg1 = "<<dec<<scratch_uop.reg1; 
      else
        cout<<"\nImmed = "<<hex<<scratch_uop.immed;
    }

    else if (scratch_uop.src == IMUL_1) {
      if (scratch_uop.reg1 != UD_NONE)
        cout<<"\nReg1 = "<<dec<<scratch_uop.reg1;
      else
        cout<<"\nImmed = "<<dec<<scratch_uop.immed;
    }
    

    if (scratch_uop.src != NO_SRC)
      cout<<"\nReg2 = "<<dec<<scratch_uop.reg2;
    
    cout<<"\nOpsize = "<<dec<<scratch_uop.opsize;
    cout<<"\nAddress = "<<hex<<scratch_uop.address;
    cout<<"\nSource = "<<scratch_uop.src<<endl;
  }
  
}
