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

  Iterable<int> iterator = list->begin();
  cout << iterator.getCurrent()->value << endl;

  cout << "Size: " << list->getSize()  << "\nFirst: " << list->front() << "\nLast: " << list->back() << endl;
  
  while( iterator.hasNext() ) {
    cout << iterator.getCurrent()->value << endl;
    iterator.next();
  }

  //  delete iterator; // how must i delete it ?????
  
  return 0;

}
