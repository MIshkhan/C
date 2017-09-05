#include "DLList.h"
#include "Iterable.h"

#include <iostream>

using namespace std;

int main() {
  
  DLList<int>* list = new DLList<int>();

  list->pushFront(65);
  list->pushFront(68);
  list->pushFront(70);
  list->pushBack(75);

  cout << "Size: " << list->getSize()  << "\nFirst: " << list->front() << "\nLast: " << list->back() << endl;
    
  Iterable<int>* iterator = list->begin();
  while( iterator->hasNext() ) {
    cout << iterator->getCurrent()->value << " ";
    iterator->next();
  }
  cout << endl;
  
  delete iterator; 
 
  return 0;

}
