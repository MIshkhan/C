#ifndef Array_Stack
#define Array_Stack

#include "Stack.h"
using namespace std;
struct EmptyStack {};

template <typename T>
class ArrayStack : public Stack<T> {
private:
	unsigned int length;
	unsigned int maxSize;
	T* array;
public:
	//constructor
	ArrayStack(unsigned int n = 100) {
		n > 100 ? maxSize = 100 : maxSize = n;
		length = 0;
		array = new T[maxSize];
	}
	//destructor
	~ArrayStack() {
		delete[] array;
	}
	//number of elements
	unsigned int size() const {
		return length;
	}
	//maximal number of elements
	unsigned int capacity() const {
		return maxSize;
	} 
	//current element
	T& top() {
		if (length == 0) throw EmptyStack();
		return array[length - 1];
	}
	//insert from end
	bool push(const T& value) {
		if (length == maxSize) return false;
		array[length++] = value;
		return true;
	}
	//remove current element
	bool pop() {
		if (length == 0) return false;
		--length;
		return true;
	}
	//removes all elements from stack
	void clear() {
		delete[] array;
		array = new T[maxSize];
	}
	//returns true if stack is empty
	bool isEmpty() const {
		return length == 0;
	}
};
#endif // !Array_Stack
