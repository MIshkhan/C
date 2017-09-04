#include "DLList.h"
#include <iostream>

using namespace std;

int main() {
  
  DLList<int>* list = new DLList<int>();
  list->pushFront(65);
    
  cout << list->getSize() << " " << list->front() << endl; 
    
  return 0;

}
