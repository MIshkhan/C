#include <iostream>
#include "LinkedStack.h"

using namespace std;

int main() {
  
  cout << "Input number of your brackets (max 100)!\n";
  unsigned int number;
  cin >> number;
  
  LinkedStack<char> stack;
  bool inputIsCorrect = true;
  cout << "Input " << number <<" brackets \" ( ) { } [ ] \"\n";
  for (unsigned int i = 0; i < number; ++i){
    char value;
    cin >> value;
    if(inputIsCorrect)
      switch (value){
      case '(': {stack.push('('); break; }
      case '{': {stack.push('{'); break; }
      case '[': {stack.push('['); break; }
      case ')': { if(stack.size() != 0 && stack.top() == '(') stack.pop(); else inputIsCorrect = false; break; }
      case '}': { if(stack.size() != 0 && stack.top() == '{') stack.pop(); else inputIsCorrect = false; break; }
      case ']': { if(stack.size() != 0 && stack.top() == '[') stack.pop(); else inputIsCorrect = false; break; }
      }
  }
  if (inputIsCorrect && stack.isEmpty()) 
    cout << "You input is correct ... \n";
  else 
    cout << "You input is incorrect ... \n";
  return 0;
}	
