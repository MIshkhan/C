#include<iostream>
#include <fstream>
#include "Interpreter.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2 ) {
   cout << "You must input a file path!\n";
   return 1;
  }
  else {
    Interpreter* interpreter = new Interpreter(argv[1]);
    interpreter->start();
    delete interpreter;
  }
}
