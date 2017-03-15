#ifndef Linked_Stack
#define Linked_Stack

#include "Stack.h"
using namespace std;

struct EmptyLinkedStack {};

template <typename T>
struct Node{
  Node* child;
  Node* parent;
  T value;
};

template <typename T>
class LinkedStack : public Stack<T> {
 private:
  unsigned int length;
  Node<T>* curr;
 public:
  //constructor
  LinkedStack() {
    length = 0;
    curr = NULL;
  }
  //destructor
  ~LinkedStack() {
    if(length) clear();
    delete curr;
   }
  //number of elements
  unsigned int size() const {
    return length;
  }
  //current element
  T& top() {
    if (length == 0) throw EmptyLinkedStack();
    return curr->value;
  }
  //insert from end
  bool push(const T& value) {
    Node<T>* tmp = new Node<T>;
    tmp->value = value;
    tmp->child = curr;
    curr = tmp;
    ++length;
    return true;
  }
  //remove top element
  bool pop() {
    if (length == 0) return false;
    --length;
    Node<T>* tmp = curr;
    curr = curr->child;
    delete[] tmp;
    return true;
  }
  //removes all elements from stack
  void clear() {
    while(curr->child != 0){
      curr = curr->child;
      delete curr->parent;
    }
    length = 0;
    curr = NULL;
  }
  //returns true if stack is empty
  bool isEmpty() const {
    return length == 0;
  }
};
#endif // !Linked_Stack
