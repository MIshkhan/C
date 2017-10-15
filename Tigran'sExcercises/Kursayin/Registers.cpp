#include <vector>
#include <bits/stdc++.h>
#include "Registers.cpp"

using namespace std;

class Registers {
public :

  uint LineNumber;
  
  // General purpose registers
  array<bitset<8>, 1024> R_8;
  
  bitset<64> ZERO;

  // Flags OF,SF,ZF,PF,CF
  bitset<16> FLAGS;  

  Registers() {
    LineNumber = 0;
  }

  uint getRegister(string reg) {
    uint index, size = reg.size();
    
    if( size < 2 || reg[0] != 'R')
      throw runtime_error("No such register: " + reg);
    
    for(int i = 1; i < size; ++i) {
      if( reg[i] < '0' || reg[i] > '9')
        throw runtime_error("No such register: " + reg);
    }

    index = stoi(reg.substr(1, reg.size()));
    if(index >= 0 && index <= 1023)
      return index;
    else
      throw runtime_error("No such register: " + reg);
  }
  
};
