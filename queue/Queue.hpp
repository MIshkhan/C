#ifndef queue_h
#define queue_h

//
// abstract Queue
//
#define MAX_SIZE 100
template <typename T>
class Queue {
public:
  bool IsEmpty(){}
  bool IsFull(){}
  void Enqueue(T){}
  void Dequeue(){}
  int  Front(){}
};

#endif
