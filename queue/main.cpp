#include<iostream>
#include "ArrayQueue.hpp"
using namespace std;

int main(){
  ArrayQueue<int> Q;
  cout << "How much elements do you want to enqueue ? (max 100) ";
  size_t size;
  cin >> size;
  cout << "Enqueue elements !\n";
  for(int i = 0; i < size; ++i){
    int number;
    cin >> number;
    Q.Enqueue(number);
  }

  for(int i = 0; i < size; ++i){
    cout << Q.Front() << " ";
    Q.Dequeue();
  }
}
