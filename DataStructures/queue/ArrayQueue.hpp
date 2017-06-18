#ifndef arrayQueue_h
#define arrayQueue_h

#include "Queue.hpp"

template <typename T>
class ArrayQueue : public Queue<T> {
private:  
  int A[MAX_SIZE];
  int front, rear;
public:  
  ArrayQueue(){
    front = -1; 
    rear = -1;
  }
  
  bool IsEmpty(){
    return (front == -1 && rear == -1); 
  }

  bool IsFull(){
    return (rear+1)%MAX_SIZE == front ? true : false;
  }

  void Enqueue(T x){
    if(IsFull()) return;
    if (IsEmpty()) front = rear = 0; 
    else rear = (rear+1)%MAX_SIZE;
    A[rear] = x;
  }

  void Dequeue(){
    if(IsEmpty()) return;
    else if(front == rear ) rear = front = -1;
    else front = (front+1)%MAX_SIZE;
  }
  
  int Front(){
    if(front == -1) return -1; 
    return A[front];
  }
};
#endif
