#ifndef stack_h
#define stack_h

//
// abstract Stack
//
template <typename T > class Stack {
public:
	Stack() {} //default constructor
	virtual ~Stack() {} //base constructor
	virtual unsigned int size() const = 0; //number of elements
	virtual unsigned int capacity() const = 0; //maximal number of elements
	virtual T& top() = 0; //returns last element
	virtual bool push(const T&) = 0; //insert from end
	virtual bool pop() = 0; //remove from end
	virtual bool isEmpty() const = 0; //returns true if stack is empty
	virtual void clear() = 0; //removes all elemets from stack
};
#endif 
