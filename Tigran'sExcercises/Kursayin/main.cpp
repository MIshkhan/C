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
    fstream f;
    f.open(argv[1], ios::in);

    Interpreter* interpreter = new Interpreter();
    // interpreter->start(f);

    delete interpreter;
    f.close();
  }
}
