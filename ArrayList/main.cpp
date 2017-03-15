#include <iostream>
#include "ArrayList.hpp"

using namespace std;

ArrayList<int> arr(5);

int printList(std::string message = ""){
  cout << message + "[ ";
  arr.moveToStart();
  for(int i = 0; i < arr.size(); ++i){
    cout << arr.value() << " ";
    arr.next();
  }
  cout << "]" << endl;
  cout << "size: " << arr.size() << endl << endl;
}

int main(){
  cout << "is empty: " << arr.isEmpty() << endl << endl;

  arr.append(8);
  arr.append(8);
  arr.append(8);
  arr.append(8);
  printList("Before erase: ");

  arr.erase(8);
  printList("After erase: ");
  
  arr.insert(80); //from end
  printList("After insert: ");
    
  return 0;
}
