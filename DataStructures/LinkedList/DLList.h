#ifndef Doubly_Linked_List
#define Doubly_Linked_List

#include "Iterable.h"
#include "Node.h"

template <typename T>
class DLList {

private:

  Node<T>* head;
  Node<T>* tail;
  unsigned int length;
  
public:
  
  DLList() {
    head = tail = new Node<T>();
    length = 0;
  }
  
  ~DLList() {
    clear();
    delete head;
  }

  T& front() {
    if( !isEmpty() )
      return head->value;
    throw new EmptyList;
  }

  T& back() {
    if( !isEmpty() )
      return tail->prev->value;
    throw new EmptyList;
  }
  
  void pushFront(const T& v) {
    head->prev = new Node<T>(v);
    head->prev->next = head;
    
    head = head->prev;
    ++length;
  }

  void pushBack(const T& v) {
    tail->value = v;
    tail->next = new Node<T>(v); 
    tail->next->prev = tail;
    
    tail = tail->next;
    ++length;
  }

  void popFront() {
    if( !isEmpty() ) {
      head = head->next;
      delete head->prev;
      --length;
    }
  }

  void popBack() {
    if( !isEmpty() ) {
      tail = tail->prev;
      delete tail->next;
      --length;
    }
  }
  
  void clear() {
    while( !isEmpty() ) {
      head = head->next;
      delete head->prev;
    }
    
    length = 0;
  }
  
  unsigned int getSize() const {
    return length;
  }

  bool isEmpty() {
    return head == tail;
  }
  
  Iterable<T> begin() {
    return *(new Iterable<T>(head));
  }

  Iterable<T> end() {
    return *(new Iterable<T>(tail->prev));    
  }

  struct EmptyList {};

};  
#endif
