#include <iostream>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

stack<string> varStack;
map<string, string> varMap;
double operand1;
double operand2;

//True if input string is one of this + - * /
bool is_operator(const string& c) {
  regex op("-|[+]|//|[*]");
  return regex_match(c, op);
}

//True if input string can be converted to int or double
bool is_operand(const string& c) {
  regex number("-?[0-9]+([.][0-9]+)?"); 
  return regex_match(c, number);
}

//True if input string is declared variable
bool is_variable(const string& c) {
  return varMap.find(c) != varMap.end();
}

//Resolves input string
void resolve(const string& input) {
  if(is_operand(input)) { 
    varStack.push(input); 
  }
  else 
    if(is_operator(input)) {
      assert(varStack.size() >= 2);
      operand1 = stod( varStack.top() );
      varStack.pop();
      operand2 = stod( varStack.top() );
      varStack.pop();
      
      switch( input[0] ) {
        case'+':{ varStack.push( to_string(operand2 + operand1) ); break; }
        case'-':{ varStack.push( to_string(operand2 - operand1) ); break; }
        case'*':{ varStack.push( to_string(operand2 * operand1) ); break; }
        case'/':{ varStack.push( to_string(operand2 / operand1) ); break; }
      }
    }
    else{
      string key = input.substr( 0, input.find("=") ); 
      if( is_variable(key) ) {
        varStack.push( varMap.find(key)->second );
      }
      else {
        cerr << "Invalid argument [" + input << "]" << endl;
        exit(1);
      }
    }
}

/**
 * Makes variables from input if everything is correct, otherwise ends program.
 * Variable declaration syntax [white space][variable name (a-zA-z)][=][value]
 */
void initialize_vars(const string& input) {
  regex varDeclar("^(\\s[a-zA-z]+=-?[0-9]+([.][0-9]+)?)+");
  if( regex_match(input, varDeclar) ) {
    stringstream ss(input);
    string item;
    while ( getline(ss, item, ' ') ) {
      if (item.length() > 0) {
        string key = item.substr( 0, item.find("=") );
        string value = item.substr( item.find("=")+1 );  
        varMap.insert( pair<string, string>(key, value) );  
      }
    }
  }
  else {
    cerr << "\nIncorrect variable declaration [" + input << "]"<< endl;
    cerr << "Example: [ n=100 double=-21.5]\n" << endl;
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
    //First line is only for variable declaration !!! 
    getline(f, data);
    if(data != "") {
      initialize_vars( data );
    }
    getline(f, data);
    while(data != "") {
      resolve(data);
      getline(f, data);
   }
   double result = stod(varStack.top());
   varStack.pop();
   cout << "\nResult: " << result << endl << endl;
   f.close();  
  }
  return 0;
}
