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
    string data;
    registers = new Registers();

    file.open(fileName, ios::in);

    while(getline(file, data)) 
      content.push_back(data);
    
    file.close();
  }

  ~Interpreter() {
    delete registers;
  }

  void start() {
    while( content.size() != registers->LineNumber ) {
      string command = fetch();
      decodeAndExecute(command);
      registers->LineNumber += 1;
    }
  }
  
private :
  fstream file;
  vector<string> content;
  Registers* registers;

  string fetch() {
    return content[registers->LineNumber];
  }
 
  void decodeAndExecute(string command) {
    string operation, type = "DW";
    uint regOne, regTwo, value;
    
    vector<string> tokens = split(command);
    uint size = tokens.size();
    Instructions* inst = new Instructions();
    
    
    if( size < 2 || size > 4) 
      return;
    
    operation = tokens[0];

    // INC, DEC 
    if( inst->isROperation(operation) ) {

      if( size != 2 )
        throwWrongNumOfArguments(2);
      
      regOne = registers->getRegister(tokens[2]);

      printCurrCommand();
      detectKey();
      (inst->*( inst->RFunc(operation)))(registers->R_8[regOne]);
      return;
    }

    // ASSIGN
    if( inst->isRVOperation(operation) ) {

      if( size != 4 )
        throwWrongNumOfArguments(4);

      type   = inst->getType(tokens[1]);
      regOne = registers->getRegister(tokens[2]);
      value  = inst->getValue(tokens[3], type);
      
      printCurrCommand();
      detectKey();
      (inst->*( inst->RVFunc(operation)))(registers->R_8[regOne], value);
      return;
    }
    
    if( inst->isRROperation(operation) ) {

      if( size != 4 )
        throwWrongNumOfArguments(4);
      
      type   = inst->getType(tokens[1]);
      regOne = registers->getRegister(tokens[2]);
      regTwo = registers->getRegister(tokens[3]);

      printCurrCommand();
      detectKey();
      (inst->*( inst->RRFunc(operation)))(registers->R_8[regOne], registers->R_8[regTwo]);
      return;
    }

    throw runtime_error("Unknown command: " + command);
  }

  void detectKey() {
    // TODO
  }
  
  void printCurrCommand() {
    cout << "Line: " + to_string(registers->LineNumber) + " " + fetch() + "\n";
  }
  
  void throwWrongNumOfArguments(char num) {
    throw runtime_error("Wrong number of arguments required :" + to_string(num) + "\n" +
                        fetch() + " (line: " + to_string(registers->LineNumber) + ")\n");
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
