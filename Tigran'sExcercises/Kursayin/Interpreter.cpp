#include <fstream>
#include <iostream>
#include <vector>
#include <string> 
#include "Registers.cpp"

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
    return content[3];//registers->LineNumber];
  }
 
  void decodeAndExecute(string command) {
    string RRCommands = "(NAND|ADD|SUB|MUL|DIV|SWAP|AND|OR|XOR|MOV)";
    string RCommands  = "(NOT|NOR|INC|DEC)";
    string RVCommands = "(ASSIGN)"; 
    string VCommands  = "(JUMP)";
    string types      = "(B|QW|W|DW)";
    string reg        = "R\\[[0-1023]]";

    string value, operation, type = "DW";
    string regIndex1, regIndex2;

    if ( regex_match(command, regex( RRCommands + " (" + types + " )." + reg + " " + reg)) ) {
      vector<string> tokens = split(command);
      uint size = tokens.size();
      
      operation = tokens[0];
      if( size == 4 ) type = tokens[1];  
      regIndex1 = tokens[size-2];
      regIndex2 = tokens[size-1];
      
      // cout << operation << "  " << type << "  " << regIndex1 << "  " << regIndex2 << endl; 
    } 
    
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
