#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <map>
#include <stack>
#include <bits/stdc++.h>
#include "registers.h"

using namespace std;

class Instructions {
public:
  
  vector<string> content;
  
  typedef bitset<8> byte;
  typedef bitset<16> word;
  typedef bitset<32> dword;
  typedef bitset<64> qword;
  typedef void(Instructions::*R)(byte&);
  typedef void(Instructions::*RR)(byte&, byte&);
  typedef void(Instructions::*RV)(byte&, uint);
  
  Instructions(Registers* r);

  R RFunc(string name);
  RR RRFunc(string name);
  RV RVFunc(string name);
  bool isROperation(string name);
  bool isRROperation(string name);
  bool isRVOperation(string name);
  string getType(string type);
  ulong getValue(string expression, string type);
  
private:
  Registers* regs;
  stack<byte> Stack;

  map<string, RR> RROperations = {
    {"NAND",   &Instructions::nand},
    {"ADD",    &Instructions::add},
    {"SUB",    &Instructions::sub},
    {"MUL",    &Instructions::mul},
    {"DIV",    &Instructions::div},
    {"SWAP",   &Instructions::swap},
    {"AND",    &Instructions::And},
    {"OR",     &Instructions::Or},
    {"NOR",    &Instructions::nor},
    {"XOR",    &Instructions::Xor},
    {"MOV",    &Instructions::mov}
  };
  
  map<string, R> ROperations = {
    {"NOT",    &Instructions::Not},
    {"INC",    &Instructions::inc},
    {"DEC",    &Instructions::dec}    
  };

  map<string, RV> RVOperations = {
    {"ASSIGN", &Instructions::assign},
  };

  // {"NOP",    &Instructions::nop},
  // {"JUMP",   &Instructions::jump},
  
  void nop   ();
  void jump  ( uint lineNumber );
  void assign( byte& r1, uint value );
  void mov   ( byte& r1, byte& r2 );
  void swap  ( byte& r1, byte& r2 );
  void And   ( byte& r1, byte& r2 );
  void Or    ( byte& r1, byte& r2 );
  void Xor   ( byte& r1, byte& r2 );
  void Not   ( byte& r1 );
  void nand  ( byte& r1, byte& r2 );
  void nor   ( byte& r1, byte& r2 );
  void add   ( byte& r1, byte& r2 );
  void sub   ( byte& r1, byte& r2 );
  void mul   ( byte& r1, byte& r2 );
  void div   ( byte& r1, byte& r2 );
  void inc   ( byte& r1 );
  void dec   ( byte& r1 );

  // Conditional inatructions
  void je_jz   (string lable);
  void jne_jnz (string lable);
  void ja_jnbe (string lable);
  void jae_jnbe(string lable);
  void jb_jnae (string lable);
  void jbe_jna (string lable);
  void jg_jnle (string lable);
  void jge_jnl (string lable);
  void jl_jnge (string lable);
  void jle_jng (string lable);
  void jo (string lable);
  void jno(string lable);
  void js (string lable);
  void jns(string lable);
  void jp (string lable);
  void jnp(string lable);
  void jump(string lable);

  // TODO
  void call(uint lineNumber);
  void ret ();
  void test(byte r1, byte r2);
  void cmp (byte r1, byte r2);
  void shr (byte r1, byte r2);
  void ror (byte r1, byte r2);
  void rol (byte r1, byte r2);
  void push(byte r);
  void pop (byte& r);
  void pushf(byte r1, byte r2);
  void popf(byte r1, byte r2);
  
  bool isNumOfType(ulong num, string type);
  void updateFlags(byte prevValue, byte currValue);
  void setFlags(char OF, char SF, char ZF, char PF, char CF);
  
};

#endif
