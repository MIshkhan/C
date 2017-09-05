#ifndef Node_h
#define Node_h

template <typename T>
class Node {

public:
  
  T value;
  Node<T>* prev;
  Node<T>* next;
    
  Node() {
    prev = next = 0;
  }
    
  Node(const T& v) {
    value = v;
    prev = next = 0;
  }

};

#endif
