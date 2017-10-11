#include <map>
#include <bits/stdc++.h>

using namespace std;

class Instructions {
public:
  
  typedef bitset<8> byte;
  typedef bitset<16> word;
  typedef bitset<32> dword;
  typedef bitset<64> qword;
  typedef void(Instructions::*R)(byte&);
  typedef void(Instructions::*RR)(byte&, byte&);
  typedef void(Instructions::*RV)(byte&, uint);
  
  R RFunc(string name) {
    if( ROperations.find(name) == ROperations.end() )
      throw runtime_error("Illegal operation: " + name);
    return ROperations[name];
  }
  
  RR RRFunc(string name) {
    if( RROperations.find(name) == RROperations.end() )
      throw runtime_error("Illegal operation: " + name);
    return RROperations[name];
  }  

  RV RVFunc(string name) {
    if( RVOperations.find(name) == RVOperations.end() )
      throw runtime_error("Illegal operation: " + name);
    return RVOperations[name];
  }
  
private:
  
  map<string, RR> RROperations = {
    {"NAND",   &Instructions::nand},
    {"ADD",    &Instructions::add},
    {"SUB",    &Instructions::sub},
    {"MUL",    &Instructions::mul},
    {"DIV",    &Instructions::div},
    {"SWAP",   &Instructions::swap},
    {"AND",    &Instructions::And},
    {"OR",     &Instructions::Or},
    {"XOR",    &Instructions::Xor},
    {"MOV",    &Instructions::mov}
  };
  
  map<string, R> ROperations = {
    {"NOT",    &Instructions::Not},
    {"NOR",    &Instructions::nor},
    {"INC",    &Instructions::inc},
    {"DEC",    &Instructions::dec}    
  };

  map<string, RV> RVOperations = {
    {"ASSIGN", &Instructions::assign},
  };

  // {"NOP",    &Instructions::nop},
  // {"JUMP",   &Instructions::jump},
    
  void nop() {
    
  } 

  void jump( uint lineNumber ) {
    
  }
  
  void assign( byte& r1, uint value ) {
    r1 = byte(value);
  }

  void mov( byte& r1, byte& r2 ) {
    r1 = r2;
  }
  
  void mov( word& r1, word& r2 ) {
    r1 = r2;
  }
  
  void swap( byte& r1, byte& r2 ) {
    byte temp = r1;
    r1 = r2;
    r2 = temp;
  }

  void And( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() & r2.to_ulong());
  }
  
  void Or( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() | r2.to_ulong());
  }

  void Xor( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() ^ r2.to_ulong());
  }
  
  void Not( byte& r1 ) {
    r1 = byte(!r1.to_ulong());
  }

  void nand( byte& r1, byte& r2 ) {
    And(r1, r2);
    r1 = !r1;
  }
  
  void nor( byte& r1 ) {
    Or(r1, r2);
    r1 = !r1;
  }
  
  void add( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() + r2.to_ulong());
  }
  
  void sub( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() - r2.to_ulong());
  }
  
  void mul( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() * r2.to_ulong());
  }

  void div( byte& r1, byte& r2 ) {
    r1 = byte(r1.to_ulong() / r2.to_ulong());
  }
  
  void inc( byte& r1 ) {
    r1 = byte(r1.to_ulong() + 1);
  }

  void dec( byte& r1 ) {
    r1 = byte(r1.to_ulong() - 1);
  }
  
};
