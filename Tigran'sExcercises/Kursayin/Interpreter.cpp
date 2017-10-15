#include <fstream>
#include <iostream>
#include <vector>
#include <string> 
#include "Registers.cpp"
#include "Instructions.cpp"

using namespace std;

class Interpreter {
public:
  
  Interpreter(string fileName) {
    regs = new Registers();
    inst = new Instructions(regs);

    file.open(fileName, ios::in);

    string data;
    while(getline(file, data)) 
      inst->content.push_back(data);
    
    file.close();
  }

  ~Interpreter() {
    delete regs;
    delete inst;
  }

  void start() {
    try {
      while( inst->content.size() != regs->LineNumber ) {
	string command = fetch();
	decodeAndExecute(command);
	regs->LineNumber += 1;
      }
    } catch (const runtime_error& e) {
      cout << "[ERROR] - " << e.what() << endl;
    }
  }
  
private :
  fstream file;
  Registers* regs;
  Instructions* inst;
  
  string fetch() {
    return inst->content[regs->LineNumber];
  }
 
  void decodeAndExecute(string command) {
    string operation, type = "DW";
    uint regOne, regTwo, value;
    
    vector<string> tokens = split(command);
    uint size = tokens.size();
   
    printCurrCommand();
    detectKey();
    
    if( size < 2 || size > 4) 
      return;
    
    operation = tokens[0];

    // INC, DEC 
    if( inst->isROperation(operation) ) {

      if( size != 2 )
        throwWrongNumOfArguments(2);
      
      regOne = regs->getRegister(tokens[2]);

      cout << "(" << tokens[2] << " = " << regs->R_8[regOne].to_ulong() << ")" << endl;
      (inst->*( inst->RFunc(operation)))(regs->R_8[regOne]);
      return;
    }

    // ASSIGN
    if( inst->isRVOperation(operation) ) {

      if( size != 4 )
        throwWrongNumOfArguments(4);

      type   = inst->getType(tokens[1]);
      regOne = regs->getRegister(tokens[2]);
      value  = inst->getValue(tokens[3], type);

      cout << "(" << tokens[2] << " = " << regs->R_8[regOne].to_ulong() << ")" << endl;
      (inst->*( inst->RVFunc(operation)))(regs->R_8[regOne], value);
      return;
    }
    
    if( inst->isRROperation(operation) ) {

      if( size != 4 )
        throwWrongNumOfArguments(4);
      
      type   = inst->getType(tokens[1]);
      regOne = regs->getRegister(tokens[2]);
      regTwo = regs->getRegister(tokens[3]);
      
      cout << "(" << tokens[2] << " = " << regs->R_8[regOne].to_ulong() << ", ";
      cout << tokens[3] << " = " << regs->R_8[regTwo].to_ulong() << ")" << endl;
      (inst->*( inst->RRFunc(operation)))(regs->R_8[regOne], regs->R_8[regTwo]);
      return;
    }

    throw runtime_error("Unknown command: " + command);
  }

  void detectKey() {
    // TODO
  }
  
  void printCurrCommand() {
    cout << "Line: " << regs->LineNumber << " " << fetch() << " ";
  }
  
  void throwWrongNumOfArguments(char num) {
    throw runtime_error("Wrong number of arguments required : " + to_string(num));
  }

  vector<string> split(string data) {
    vector<string> tokens;
    stringstream str(data);
    string token;
    while (str >> token) {
      tokens.push_back(token);
    }
    return tokens;
  }
  
};
