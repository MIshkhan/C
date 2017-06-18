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
  bitset<8>   IP_32;  //It must be 32bit but this is for convenience
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

  void jump( bitset<8>& r1, bitset<8> value ) {
    r1 = value;
  }
  
  //Functional representation of assembler operations
  map<string, myFunc> opMap = {
    {"ADD",  &Operations::add},
    {"SUB",  &Operations::sub},
    {"MUL",  &Operations::mul},
    {"MOV",  &Operations::mov},
    {"JUMP", &Operations::jump}
  };

};

class Ram {
  
public:
  
  Ram() {
    ram.reserve(1024);
  }

  void add(string command) {
    if( !isFull() ) {
      ram.push_back(command);
      ++lastCommandIndex;
    }
    else
      throw runtime_error("Ram is Full ...");
  }
  
  bool isFull() {
    return ram.size() == ram.capacity();
  }

  void free() {
    currentCommand = 0;
    lastCommandIndex = 0;
    ram.clear();
  }

  string fetch(unsigned long address) {
    if(address < lastCommandIndex)
      return ram[address++];
    else
      return "";
  }

  void traverseAndPrint() {
    r.IP_32 = bitset<8>(0);
    string command = fetch( r.IP_32.to_ulong() );
    while( command != "" ) {
      r.IP_32 = bitset<8>(r.IP_32.to_ulong() + 1);
      decodeExecuteAndPrintInfo(command);
      command = fetch( r.IP_32.to_ulong() );
    }
  }

private:

  vector<string> ram;
  int lastCommandIndex = 0;
  int currentCommand = 0;
  Operations o; 
  Registers r;
  
  void decodeExecuteAndPrintInfo( string line ) {
    string e1 = "R_8\\[[0-9]+\\] [0-1][0-1][0-1][0-1][0-1][0-1][0-1][0-1]";
    string e2 = "R_8\\[[0-9]+\\] R_8\\[[0-9]+\\]";
    int regsterIndex1, regsterIndex2;
    string command;
    bitset<8> bits;
    //operation register bits
    if ( regex_match(line, regex("(ADD|SUB|MUL|MOV) "+ e1)) ) {
    
      command = line.substr(0, line.find(" ") );
      regsterIndex1 = stoi(line.substr(line.find("[")+1, line.find("]")));
      int a = line.find_last_of(" ");
      bits = bitset<8>(line.substr(a+1, line.length()-a));

      (o.*(o.opFunc(command)))(r.R_8[regsterIndex1], bits);
    
      cout << "Excecuting ...   " + line << "   Result: " + r.R_8[regsterIndex1].to_string() << endl;
      return;
    }
    //operation register register
    if (regex_match(line, regex("(ADD|SUB|MUL|MOV) "+ e2)) ) {
    
      command = line.substr(0, line.find(" ") );
      regsterIndex1 = stoi(line.substr(line.find("[")+1, line.find("]")));
      regsterIndex2 = stoi(line.substr(line.find_last_of("[")+1, line.find_last_of("]")));
    
      (o.*(o.opFunc(command)))(r.R_8[regsterIndex1], r.R_8[regsterIndex2]);
    
      cout << "Excecuting ...   " + line <<  "     Result: " + r.R_8[regsterIndex1].to_string() << endl;
      return;
    }
    //JUMP bits
    if (regex_match(line, regex("JUMP [0-1][0-1][0-1][0-1][0-1][0-1][0-1][0-1]")) ) {

      command = line.substr(0, line.find(" ") );
      int a = line.find_last_of(" ");
      bits = bitset<8>(line.substr(a+1, line.length()-a));

      (o.*(o.opFunc(command)))(r.IP_32, bits);
    
      cout << "Excecuting ...   " + line <<  "         IP: " + r.IP_32.to_string() << endl;
      return;
    }
    //otherwise
    throw runtime_error("Wrong assembly command: '" + line + "'");
    exit(1);
  }
};



int main(int argc, char* argv[]) {
  
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  //RAM init
  else {
    Ram ram;
    fstream f;
    string data;
    
    f.open(argv[1], ios::in);
    getline(f, data);
    while(data != "") {
      ram.add(data);
      getline(f, data);
    }
    cout << endl;
    f.close();
    ram.traverseAndPrint();
  }
  
  return 0;
}
