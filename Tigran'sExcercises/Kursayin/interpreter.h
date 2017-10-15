#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string> 
#include "registers.h"
#include "instructions.h"

using namespace std;

class Interpreter {
public:
  
  Interpreter(string fileName);
  ~Interpreter();
  void start();
  
private :
  fstream file;
  Registers* regs;
  Instructions* inst;
  
  string fetch();
  void decodeAndExecute(string command);
  void detectKey();
  void printCurrCommand();
  void throwWrongNumOfArguments(char num);
  vector<string> split(string data);
  
};

#endif
