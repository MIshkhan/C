#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <stack>

#include <vector>
#include <sstream>
#include <regex>

using namespace std;

//True if input string is one of this + - * /
bool is_operator(const string& c) {
  regex op("-|[+]|//|[*]");
  return regex_match(c, op);
}

//True if input string can be convert to int or double
bool is_operand(const string& c) {
  regex number("-?[0-9]+([.][0-9]+)?"); 
  return regex_match(c, number);
}

stack<string> stacks;	
double operand1;
double operand2;

void calculate(const string& input) {
  if(is_operand(input)) { 
    stacks.push(input); 
  }
  else 
    if(is_operator(input)) {
      assert(stacks.size() >= 2);
      operand1 = stod( stacks.top() );
      stacks.pop();
      operand2 = stod( stacks.top() );
      stacks.pop();
      
      switch( input[0] ) {
        case'+':{ stacks.push( to_string(operand2 + operand1) ); break; }
        case'-':{ stacks.push( to_string(operand2 - operand1) ); break; }
        case'*':{ stacks.push( to_string(operand2 * operand1) ); break; }
        case'/':{ stacks.push( to_string(operand2 / operand1) ); break; }
      }
    } else {
        cerr << "invalid_argument :: " + input << endl;
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
    string expression;
    string data;
    f.open(argv[1], ios::in);
    getline(f, data); 
    while(data != "") {
      cout << data << endl;
      calculate(data);
      getline(f, data);
   }
   f.close();  
   double result = stod(stacks.top());
   stacks.pop();
   cout << "Result: " << result << endl;
  }
  return 0;
}
