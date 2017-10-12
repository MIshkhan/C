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
    Registers* registers = new Registers();

    file.open(fileName, ios::in);

    while(getline(file, data)) 
      content.push_back(data);
    
    file.close();
  }

  ~Interpreter() {
    delete registers;
  }

  void start() {
    string command = fetch();
    decodeAndExecute(command);
  }
  
private :
  fstream file;
  vector<string> content;
  Registers* registers;

  string fetch() {
    return content[0];//registers->LineNumber];
  }
 
  void decodeAndExecute(string command) {
    string operation, type = "DW";
    int regIndex1, regIndex2;
    uint value;
    
    vector<string> tokens = split(command);
    uint size = tokens.size();
    Instructions* inst = new Instructions();
    
    
    if( size == 0 || size > 4) 
      return;
    
    operation = tokens[0];

    if( inst->isROperation(operation) ) {
      regIndex1 = registers->getRegister(tokens[2]);

      if( regIndex1 == -1 )
        throw runtime_error("Illegal command: " + command);

      (inst->*( inst->RFunc(operation)))(registers->R_8[regIndex1]);
    }
    
    // if( inst->isRVOperation(operation) ) {
    //   regIndex1 = registers->getRegister(tokens[1]);
    //   value = inst->getValue(tokens[2]);

    //   if( regIndex1 == -1 || value == -1 )
    //     throw runtime_error("Illegal command: " + command);

    //   (inst->*( inst->RVFunc(operation)))(registers->R_8[regIndex1], value);
    // }

    // if( inst->isRROperation(operation) ) {
    //   regIndex1 = registers->getRegister(tokens[1]);
    //   regIndex2 = registers->getRegister(tokens[2]);
      
    //   if( regIndex1 == -1 || regIndex2 == -1 )
    //     throw runtime_error("Illegal command: " + command);

    //   (inst->*( inst->RRFunc(operation)))(registers->R_8[regIndex1], registers->R_8[regIndex2]);
    // }

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
