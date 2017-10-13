#include <vector>
#include <bits/stdc++.h>

using namespace std;

class Registers {
public :

  uint LineNumber;
  
  //General purpose registers
  array<bitset<8>, 1024> R_8;
  
  bitset<64> ZERO;

  Registers() {
    LineNumber = 0;
  }

  int getRegister(string reg) {
    uint index, size = reg.size();
    
    if( size < 2 || reg[0] != 'R')
      throw "No such register: R" + reg + "\n";
    
    for(int i = 1; i < size; ++i) {
      if( reg[i] < '0' || reg[i] > '9')
        throw "No such register: R" + reg + "\n";
    }

    index = stoi(reg.substr(1, reg.size()));
    if(index >= 0 || index <= 1023)
      return index;
    else
      throw "No such register: R" + reg + "\n";
  }
  
};
