#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <map>
#include <bits/stdc++.h>

using namespace std;

class Registers {
  public :
 
  //Control Register 
  bitset<32>  FLAGS_32;

  //Hidden Register
  bitset<32>  IR_32;
  
  //Data Registers
  array<bitset<8>, 1024> R_8;
  
  //Address Registers
  bitset<32>  IP_32;
  bitset<32>  TR_32;
  bitset<32>  SP_32;
  bitset<32>  SF_32;
  bitset<32>  A1_32;
  bitset<32>  A2_32;
  bitset<32>  A3_32;
  bitset<32>  A4_32;
  
};

class Operations {

  public:
  
  typedef void(Operations::*myFunc)(bitset<8>&, bitset<8>);
  
  myFunc opFunc(string name) {
    if( opMap.find(name) == opMap.end() )
      throw runtime_error("Illegal operation: " + name);
    return opMap[name];
  }

  private:

  void add( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong() + r2.to_ulong());
  }
  
  void sub( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong() - r2.to_ulong());
  }

  void mul( bitset<8>& r1, bitset<8> r2 ) {
    r1 = bitset<8>(r1.to_ulong() * r2.to_ulong());
  }

  void inc( bitset<8>& r1 ) {
    r1 = bitset<8>(r1.to_ulong() + 1);
  }

  void dec( bitset<8>& r1 ) {
    r1 = bitset<8>(r1.to_ulong() - 1);
  }
  
  void mov( bitset<8>& r1, bitset<8> value ) {
    r1 = value;
  }
  
  //Functional representation of assembler operations
  map<string, myFunc> opMap = {
    {"ADD", &Operations::add},
    {"SUB", &Operations::sub},
    {"MUL", &Operations::mul},
    {"MOV", &Operations::mov}
  };

};

Operations o; 
Registers r;

void executeAndPrintInfo( string line ) {
  string e1 = "R_8\\[[0-9]+\\] [0-1][0-1][0-1][0-1][0-1][0-1][0-1][0-1]";
  string e2 = "R_8\\[[0-9]+\\] R_8\\[[0-9]+\\]";
  int regsterIndex1, regsterIndex2;
  string command;
  bitset<8> bits;
  //operation register bits
  if ( regex_match(line, regex("ADD "+ e1)) ||
       regex_match(line, regex("SUB "+ e1)) ||
       regex_match(line, regex("MUL "+ e1)) ||
       regex_match(line, regex("MOV "+ e1)) ) {
    
    command = line.substr(0, line.find(" ") );
    regsterIndex1 = stoi(line.substr(line.find("[")+1, line.find("]")));
    int a = line.find_last_of(" ");
    bits = bitset<8>(line.substr(a+1, line.length()-a));

    (o.*(o.opFunc(command)))(r.R_8[regsterIndex1], bits);
    
    cout << "Excecuting ...   " + line << "   Result: " + r.R_8[regsterIndex1].to_string() << endl;
  }
  else
    //operation register register
    if (regex_match(line, regex("ADD "+ e2)) ||
        regex_match(line, regex("SUB "+ e2)) ||
        regex_match(line, regex("MUL "+ e2)) ||
        regex_match(line, regex("MOV "+ e2)) ) {

      command = line.substr(0, line.find(" ") );
      regsterIndex1 = stoi(line.substr(line.find("[")+1, line.find("]")));
      regsterIndex2 = stoi(line.substr(line.find_last_of("[")+1, line.find_last_of("]")));

      (o.*(o.opFunc(command)))(r.R_8[regsterIndex1], r.R_8[regsterIndex2]);
    
      cout << "Excecuting ...   " + line <<  "     Result: " + r.R_8[regsterIndex1].to_string() << endl;
    }
    else {
      throw runtime_error("Wrong assembly command: '" + line + "'");
      exit(1);
    }
}


int main(int argc, char* argv[]) {
  
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    fstream f;
    string data;
    f.open(argv[1], ios::in);
    getline(f, data);
    cout << endl;
    while(data != "") {
      executeAndPrintInfo(data);
      getline(f, data);
    }
    cout << endl;
    f.close();  
  }
  
  return 0;
}
