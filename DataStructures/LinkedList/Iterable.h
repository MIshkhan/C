#ifndef Iterable_h
#define Iterable_h

#include "Node.h"

template <typename T>
class Iterable {

private:

  Node<T>* current;
  
public:

  Iterable( Node<T>* current ) {
    this->current = current;
  }
  
  Iterable operator+(int n) {
    while (n-- > 0)
      current = current->next;
    return *this;
  }
  
  Iterable operator-(int n) {
    while (n-- > 0)
      current = current->prev;
    return *this;
  }
  
  Iterable& operator++(int) {
    current = current->next;
    return *this;
  }
  
  Iterable& operator--(int) {
    current = current->prev;
    return *this;
  }
  
  Iterable& operator++() {
    current = current->next;
    return *this;
  }
  
  Iterable& operator--() {
    current = current->prev;
    return *this;
  }

  bool operator==(const Iterable& i) {
    return current == i.current;
}
  
  bool operator!=(const Iterable& i) {
    return current != i.current;
  }

  bool hasNext() {
    return current->next != 0;
  }

  Iterable& next() {
    current = current->next;
    return *this;
  }
  
  Node<T>* getCurrent() {
    return current;
  }

};

#endif
