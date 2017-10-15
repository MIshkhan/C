#include "registers.h"
#include "instructions.h"

Instructions::Instructions(Registers* r): regs(r) {}
  
bool Instructions::isRROperation(string name) {
  return !(RROperations.find(name) == RROperations.end());
}
  
bool Instructions::isRVOperation(string name) {
  return !(RVOperations.find(name) == RVOperations.end());
}

bool Instructions::isROperation(string name) {
  return !(ROperations.find(name) == ROperations.end());
}
  
Instructions::R Instructions::RFunc(string name) {
  if( !isROperation(name) )
    throw runtime_error("Illegal operation: " + name);
  return ROperations[name];
}
  
Instructions::RR Instructions::RRFunc(string name) {
  if( !isRROperation(name) )
    throw runtime_error("Illegal operation: " + name);
  return RROperations[name];
}  

Instructions::RV Instructions::RVFunc(string name) {
  if( !isRVOperation(name) )
    throw runtime_error("Illegal operation: " + name);
  return RVOperations[name];
}

ulong Instructions::getValue(string expression, string type) {
    
  for(int i = 0; i < expression.size(); ++i) 
    if( expression[i] < '0' || expression[i] > '9')
      throw runtime_error("Value " + expression + " isn't number");

  ulong result = stol(expression);    
  if ( !isNumOfType(result, type) )
    throw runtime_error("Value " + expression + " isn't of type " + type);
    
  return result; 
}

string Instructions::getType(string type) {
  if ( type.compare("B") == 0 || type.compare("W") == 0 || 
       type.compare("DW") == 0 || type.compare("QW") == 0 )
    return type;
  throw runtime_error("Unknown type: " + type);
}

void Instructions::nop() {
    
} 

void Instructions::jump( uint lineNumber ) {
    
}
  
void Instructions::assign( byte& r1, uint value ) {
  r1 = byte (value);
}

void Instructions::mov( byte& r1, byte& r2 ) {
  r1 = r2;
}
  
void Instructions::swap( byte& r1, byte& r2 ) {
  byte temp = r1;
  r1 = r2;
  r2 = temp;
}

void Instructions::And( byte& r1, byte& r2 ) {
  r1 = byte(r1.to_ulong() & r2.to_ulong());
}
  
void Instructions::Or( byte& r1, byte& r2 ) {
  r1 = byte(r1.to_ulong() | r2.to_ulong());
}

void Instructions::Xor( byte& r1, byte& r2 ) {
  r1 = byte(r1.to_ulong() ^ r2.to_ulong());
}
  
void Instructions::Not( byte& r1 ) {
  r1 = byte(~r1.to_ulong());
}

void Instructions::nand( byte& r1, byte& r2 ) {
  And(r1, r2);
  r1 = byte(~r1.to_ulong());
}
  
void Instructions::nor( byte& r1, byte& r2 ) {
  Or(r1, r2);
  r1 = byte(~r1.to_ulong());
}
  
void Instructions::add( byte& r1, byte& r2 ) {
  r1 = byte(r1.to_ulong() + r2.to_ulong());
}
  
void Instructions::sub( byte& r1, byte& r2 ) {
  r1 = byte(r1.to_ulong() - r2.to_ulong());
}
  
void Instructions::mul( byte& r1, byte& r2 ) {
  r1 = byte(r1.to_ulong() * r2.to_ulong());
}

void Instructions::div( byte& r1, byte& r2 ) {
  if(r2.to_ulong() == 0)
    throw runtime_error("Division by zero");
  r1 = byte(r1.to_ulong() / r2.to_ulong());
}
  
void Instructions::inc( byte& r1 ) {
  r1 = byte(r1.to_ulong() + 1);
}

void Instructions::dec( byte& r1 ) {
  r1 = byte(r1.to_ulong() - 1);
}

void Instructions::je_jz   (string lable) {
  if( regs->FLAGS[2] == 1 )
    jump(lable);
}

void Instructions::jne_jnz (string lable) {
  if( regs->FLAGS[2] == 0 )
    jump(lable);
}

void Instructions::ja_jnbe (string lable) {
  if( regs->FLAGS[0] == 0 && regs->FLAGS[2] == 0 ) 
    jump(lable);
}

void Instructions::jae_jnbe(string lable) {
  if( regs->FLAGS[0] == 0 ) 
    jump(lable);
}

void Instructions::jb_jnae (string lable) {
  if( regs->FLAGS[0] == 1 ) 
    jump(lable);
}

void Instructions::jbe_jna (string lable) {
  if( regs->FLAGS[0] == 1 || regs->FLAGS[2] == 1) 
    jump(lable);
}

void Instructions::jg_jnle (string lable) {
  if( regs->FLAGS[2] == 0 && regs->FLAGS[3] == regs->FLAGS[4] ) 
    jump(lable);
}

void Instructions::jge_jnl (string lable) {
  if( regs->FLAGS[3] == regs->FLAGS[4] ) 
    jump(lable);
}

void Instructions::jl_jnge (string lable) {
  if( regs->FLAGS[3] != regs->FLAGS[4] ) 
    jump(lable);
}

void Instructions::jle_jng (string lable) {
  if( regs->FLAGS[2] == 1 && regs->FLAGS[3] != regs->FLAGS[4] ) 
    jump(lable);
}

void Instructions::jo (string lable) {
  if( regs->FLAGS[4] == 1 ) 
    jump(lable);
}

void Instructions::jno(string lable) {
  if( regs->FLAGS[4] == 0 )
    jump(lable);
}

void Instructions::js (string lable) {
  if( regs->FLAGS[3] == 1 ) 
    jump(lable);
}

void Instructions::jns(string lable) {
  if( regs->FLAGS[3] == 0 ) 
    jump(lable);
}

void Instructions::jp (string lable) {
  if( regs->FLAGS[1] == 1 ) 
    jump(lable);
}

void Instructions::jnp(string lable) {
  if( regs->FLAGS[1] == 0 ) 
    jump(lable);
}

void Instructions::jump(string lable) {
  // TODO
  // find lable then jump
}

void Instructions::push( byte r ) {
  Stack.push(r);
} 

void Instructions::pop( byte& r) {
  r = Stack.top();
  Stack.pop();
}

bool Instructions::isNumOfType(ulong num, string type) {
  if (type.compare("B") == 0)
    return num >= 0 && num <= 255;
  if (type.compare("W") == 0)
    return num >= 0 && num <= 65535;
  if (type.compare("DW") == 0)
    return num >= 0 && num <= 4294967296;
  if (type.compare("QW") == 0)
    return true;
}

void Instructions::updateFlags(byte prevValue, byte currValue) {
  //TODO
  setFlags(0, 0, 0, 0, 0);
}

void Instructions::setFlags( char CF, char PF, char ZF, char SF, char OF ) {
  regs->FLAGS.set(0, OF);
  regs->FLAGS.set(1, SF);
  regs->FLAGS.set(2, ZF);
  regs->FLAGS.set(3, PF);
  regs->FLAGS.set(4, CF);
}
