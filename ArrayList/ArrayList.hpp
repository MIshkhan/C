#ifndef Array_List
#define Array_List

#include "List.hpp"

using namespace std;

struct EmptyList{}; 

template <typename T>
class ArrayList: public List<T>{
private:
  unsigned int length;
  unsigned int maxSize;
  int curr;
  T* array;
public:
  ArrayList(unsigned int n = 100){
    n > 100 ? maxSize = 100 : maxSize = n;
    length = 0;
    curr = 0;
    array = new T[maxSize];
  }
  
  ~ArrayList(){
    delete[] array;
  }
  
  unsigned int size() const {
    return length;
  }
  
  unsigned int currentPosition() const {
    return curr;
  }
  
  T value() const {
    if(length == 0) throw EmptyList();
    return array[curr];
  }
  
  bool insert(const T& value) {
    if(length == maxSize) return false;   
    for(int i = length; i > curr; --i)
      array[i] = array[i-1];
    array[curr] = value;
    ++length;
    return true;
  }
  
  bool append(const T& value) {
    if(length == maxSize) return false;
    array[length++] = value;
    return true;
  }
  
  bool isEmpty() {
    return length == 0;
  }
  
  bool erase(const T& value) {
    int arr[length];
    int j = 0;
    int match = 0;
    for(int i = 0; i < length; ++i)
      if(array[i] != value) arr[j++] = array[i];
      else match++;
    if(match == length){
      clear();
      return true;
    }
    if(j == 0) return false;
    for(int i = 0; i < j; ++i)
      array[i] = arr[i];
    length = j;
    return true;
  }
  
  bool eraseCurrrent() {
   switch(length){
    case 0 : return false;
    default : {
     for(int i = curr; i < length; --i)
       array[i] = array[i+1];
     --length;
     return true;
    } 
   }
  }
  
  void clear() {
    delete [] array;
    length = curr = 0;
    array = new T[maxSize];
  }
  
  void next() {
    if(curr != length) ++curr; 
  }
  
  void moveToStart() {
    curr = 0; 
  }
  
  void moveTo(unsigned int index) {
    if(index > length-1) index = length-1;
    curr = index;
  }
};  
#endif
