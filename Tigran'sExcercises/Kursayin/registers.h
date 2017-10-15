#ifndef REGISTERS_H
#define REGISTERS_H

#include <bits/stdc++.h>

using namespace std;

class Registers {
public :

  uint LineNumber;
  array<bitset<8>, 1024> R_8;   // General purpose registers
  bitset<64> ZERO;
  bitset<16> FLAGS;             // Flags OF,SF,ZF,PF,CF
  bitset<16> SP;                // Stack Pointer
  bitset<16> SF;                // Stack Frame
  
  Registers();
  uint getRegister(string reg);
};


#endif
