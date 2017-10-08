#include <array>
#include <bits/stdc++.h>

using namespace std;

class Registers {
public :

  uint LineNumber;
  
  //General purpose registers
  array<bitset<8>, 1024> R_8;
  
  bitset<64> ZERO;
  
};
