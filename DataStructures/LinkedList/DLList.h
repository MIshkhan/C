#ifndef Doubly_Linked_List
#define Doubly_Linked_List
  
template <typename T>
class DLList {

private:
  
  struct Node {

    T value;
    Node* prev;
    Node* next;
    
    Node() {
      prev = next = 0;
    }
    
    Node(const T& v) {
      value = v;
      prev = next = 0;
    }

    Node(const T& v, Node p, Node n) {
      value = v;
      prev = p;
      next = n;    
    }

  };
  
  Node* head;
  Node* tail;
  unsigned int length;
  
public:
  
  DLList() {
    head = tail = new Node();
    length = 0;
  }
  
  ~DLList() {
    clear();
    delete head;
  }

  T& front() {
    return head->value;
  }

  T& back() {
    return tail->value;
  }
  
  void pushFront(const T& v) {
    head->prev = new Node(v, 0, head);
    head = head->prev;
    ++length; 
  }

  void pusBack(const T& v) {
    tail->next = tail;
    tail->value = v;
    tail = tail->next;
    ++length;
  }

  void popFront() {
    if( head != tail ) {
      head = head->next;
      delete head->prev;
      --length;
    }
  }

  void popBack() {
    if( head != tail ) {
      tail = tail->prev;
      delete tail->next;
      --length;
    }
  }
  
  void clear() {
    while( head != tail ) {
      head = head->next;
      delete head->prev;
    }
  }
  
  unsigned int getSize() const {
    return length;
  }

  bool isEmpty() {
    return head == tail;
  }

};  
#endif
