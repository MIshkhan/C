#include <fstream>
#include <iostream>

#include "Registers.cpp"

class Interpreter {
public:

  Interpreter() {
    Registers* registers = new Registers();
  }

  ~Interpreter() {
    delete registers;
  }

  void start(fstream file) {
    
  }

private :

  Registers* registers;
};
