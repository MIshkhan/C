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


  bool isRROperation(string name) {
    return !(RROperations.find(name) == RROperations.end());
  }
  
  bool isRVOperation(string name) {
    return !(RVOperations.find(name) == RVOperations.end());
  }

  bool isROperation(string name) {
    return !(ROperations.find(name) == ROperations.end());
  }
  
  R RFunc(string name) {
    if( !isROperation(name) )
      throw runtime_error("Illegal operation: " + name);
    return ROperations[name];
  }
  
  RR RRFunc(string name) {
    if( !isRROperation(name) )
      throw runtime_error("Illegal operation: " + name);
    return RROperations[name];
  }  

  RV RVFunc(string name) {
    if( !isRVOperation(name) )
      throw runtime_error("Illegal operation: " + name);
    return RVOperations[name];
  }

  ulong getValue(string expression, string type) {
    
    for(int i = 0; i < expression.size(); ++i) 
      if( expression[i] < '0' || expression[i] > '9')
        throw runtime_error("Value " + expression + " isn't number\n");

    ulong result = stol(expression);
    
    if ( !isNumOfType(result, type) )
      throw runtime_error("Value " + expression + " isn't not of type " + type + "\n");
    
    return result; 
  }

  bool isNumOfType(ulong num, string type) {
    if (type.compare("B") == 0)
      return num >= 0 && num <= 255;
    if (type.compare("W") == 0)
      return num >= 0 && num <= 65535;
    if (type.compare("DW") == 0)
      return num >= 0 && num <= 4294967296;
    if (type.compare("QW") == 0)
      return true;
  }

  string getType(string type) {
    if ( type.compare("B") == 0 || type.compare("W") == 0 || 
         type.compare("DW") == 0 || type.compare("QW") == 0 )
      return type;
    throw runtime_error("Unknown type: " + type + "\n");
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
  
  void nop() {
    
  } 

  void jump( uint lineNumber ) {
    
  }
  
  void assign( byte& r1, uint value ) {
    r1 = byte (value);
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
    r1 = byte(~r1.to_ulong());
  }

  void nand( byte& r1, byte& r2 ) {
    And(r1, r2);
    r1 = byte(~r1.to_ulong());
  }
  
  void nor( byte& r1, byte& r2 ) {
    Or(r1, r2);
    r1 = byte(~r1.to_ulong());
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
