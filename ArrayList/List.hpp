#ifndef list_hpp
#define list_hpp

//
// abstract List
//
template <typename T> class List{
public:
  List(){} //default constructor
  virtual ~List(){} //base destructor
  virtual unsigned int size() const = 0; //number of elements
  virtual unsigned int currentPosition() const = 0; //current position
  virtual T value() const = 0; //current elements value
  virtual bool insert(const T&) = 0; //insert from specified position
  virtual bool append(const T&) = 0; //append from end
  virtual bool isEmpty() = 0; //returns true if list is empty
  virtual bool erase(const T&) = 0; //removes elements with specified value
  virtual bool eraseCurrrent() = 0; //removes current element
  virtual void clear() = 0; //removes all elements from list
  virtual void next() = 0; //moves pointer to next element
  virtual void moveToStart() = 0; //moves pointer to first element
  virtual void moveTo(unsigned int) = 0; //move the pointer to the specified position
};
#endif
  
