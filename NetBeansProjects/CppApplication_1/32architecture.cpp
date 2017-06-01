#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <map>
#include <bits/stdc++.h>

using namespace std;

class Registers {
  public :
 
  //Control Register 
  bitset<32>  FLAGS_32;

  //Hidden Register
  bitset<32>  IR_32;
  
  //Data Registers
  array<bitset<8>, 1024> R_8;
  
  //Address Registers
  bitset<32>  IP_32;
  bitset<32>  TR_32;
  bitset<32>  SP_32;
  bitset<32>  SF_32;
  bitset<32>  A1_32;
  bitset<32>  A2_32;
  bitset<32>  A3_32;
  bitset<32>  A4_32;
  
};

class Operation {

  public:

  void add( bitset<8>& r1, bitset<8>& r2 ) {
    r1 = bitset<8>(r1.to_ulong() + r2.to_ulong());
  }

  void assign() {

  }

  //Returns binary representation of assembler operations  
  bitset<16> opCode(string name) {
    if( opMap.find(name) == opMap.end() )
      throw runtime_error("Illegal operation: " + name);
    return opMap[name];
  }

  private:
  
  //Binary representation of assembler operations
  map<string, bitset<16>> opMap = {
    //integral arithmetic 
    {"ADD" ,  bitset<16>(0)},
    {"ADC" ,  bitset<16>(1)},
    {"SUB" ,  bitset<16>(2)},
    {"SBB" ,  bitset<16>(3)},
    {"MUL" ,  bitset<16>(4)},
    {"IMUL",  bitset<16>(5)},
    {"DIV" ,  bitset<16>(6)},
    {"IDIV",  bitset<16>(7)},
    {"INC" ,  bitset<16>(8)},
    {"DEC" ,  bitset<16>(9)}, 
    {"NEG" ,  bitset<16>(10)},
    //logical 
    {"AND" ,  bitset<16>(11)},
    {"OR"  ,  bitset<16>(12)},
    {"XOR" ,  bitset<16>(13)},
    {"NAND",  bitset<16>(14)},
    {"NOR" ,  bitset<16>(15)},
    {"NOT" ,  bitset<16>(16)},
    //assignment 
    {"ASSIGN", bitset<16>(17)},
    //move
    {"MOVE", bitset<16>(18)},
    {"SWAP", bitset<16>(19)},
    //memory
    {"LOAD", bitset<16>(20)},
    {"STORE", bitset<16>(21)}
  };

};

int main() {
  Operation o;
  Registers r;
  
  r.R_8[0] = bitset<8>("00000011");
  r.R_8[1] = bitset<8>("00001010");
  o.add(r.R_8[0], r.R_8[1]);
  
  cout << r.R_8[0].to_string() << endl;
  return 0;  
}
