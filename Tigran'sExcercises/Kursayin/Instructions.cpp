#include <map>
#include <bits/stdc++.h>

using namespace std;

class Instructions {

public:

  typedef void(Instructions::*myFunc)(bitset<8>&, bitset<8>);

  myFunc opFunc(string name) {
    if( opMap.find(name) == opMap.end() )
      throw runtime_error("Illegal operation: " + name);
    return opMap[name];
  }

private:
  
  map<string, myFunc> opMap = {
    // {"NOP",    &Instructions::nop},
    // {"JUMP",   &Instructions::jump},
    // {"ASSIGN", &Instructions::assign},
    // {"MOV",    &Instructions::mov},
    // {"SWAP",   &Instructions::swap},
    // {"AND",    &Instructions::and},
    // {"OR",     &Instructions::or},
    // {"XOR",    &Instructions::xor},
    // {"NOT",    &Instructions::not},
    {"NAND",   &Instructions::nand},
    // {"NOR",    &Instructions::nor},
    {"ADD",    &Instructions::add},
    {"SUB",    &Instructions::sub},
    {"MUL",    &Instructions::mul},
    {"DIV",    &Instructions::div} 
    // {"INC",    &Instructions::inc},
    // {"DEC",    &Instructions::dec}    
  }; 
  
  void nop() {
    
  } 

  void jump( uint lineNumber ) {
    
  }
  
  void assign( bitset<8>& r1, uint value ) {
    r1 = bitset<8>(r1.to_ulong() + value);
  }

  void mov( bitset<8>& r1, bitset<8> value ) {
    r1 = value;
  }

  void swap( bitset<8>& r1, bitset<8>& r2 ) {
    bitset<8> temp = r1;
    r1 = r2;
    r2 = temp;
  }

  // void and( bitset<8>& r1, bitset<8> r2 ) {
    
  // }
  
  // void or( bitset<8>& r1, bitset<8> r2 ) {
    
  // }

  // void xor( bitset<8>& r1, bitset<8> r2 ) {
    
  // }
  
  // void not( bitset<8>& r1 ) {
    
  // }

  void nand( bitset<8>& r1, bitset<8> r2 ) {
    
  }
  
  void nor( bitset<8>& r1 ) {
    
  }
  
  void add( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong());
  }
  
  void sub( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong());
  }

  void mul( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong());
  }

  void div( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong());
  }
  
  void inc( bitset<8>& r1 ) {
    r1 = bitset<8>(r1.to_ulong() + 1);
  }

  void dec( bitset<8>& r1 ) {
    r1 = bitset<8>(r1.to_ulong() - 1);
  }
  
};
