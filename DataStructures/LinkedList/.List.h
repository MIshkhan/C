#ifndef _List_h_
#define _List_h_

template<typename Type>
class List
{
  class Node;
  
public:
  class Iterator;

  List();
  ~List();

  Type& front();
  Type& back();

  void insert(Iterator position,const Type& element);
  void insert(Iterator beginPosition, Iterator endPosition, const Type& element);
  void erase(Iterator position);
  void erase(Iterator beginPosition, Iterator endPosition);

  void pushBack(const Type& element);
  void pushFront(const Type& element);
  void popBack();
  void popFront();

  unsigned int getSize() const;
  bool isEmpty() const;
  void clear();


  Iterator begin() { return first; }
  Iterator end() { return last; }

private:
  struct Node
  {
    Node* next;
    Node* prew;
    Type value;
    Node() : next(0), prew(0)
    {}
    Node(const Type& element)
    {
      value = element;
      next = prew = 0;
    }
  };

public:
  class Iterator
  {
  public:
    friend List<Type>;

    Iterator() {};
    Iterator(Node* element) : current(element) {}

    Type& operator* () { return current->value;	}

    Iterator operator+(int n) { while (n-- > 0) current = current->next; return *this; }		
    Iterator operator-(int n) { while (n-- > 0) current = current->prew; return *this; };

    Iterator& operator++(int) { current = current->next; return *this; }
    Iterator& operator--(int) { current = current->prew; return *this; }
    Iterator& operator++() { current = current->next; return *this; }
    Iterator& operator--() { current = current->prew; return *this; }

    bool operator==(const Iterator& it) { return current == it.current; }
    bool operator!=(const Iterator& it)	{ return current != it.current;	}

  private:
    Node* current;
  };
	
private:
  Node* first;
  Node* last;
  unsigned int size;
};

template<typename Type>
List<Type>::List() {
  size = 0;
  first = last = new Node;
}

template<typename Type>
List<Type>::~List() {
  while (first != last)
    {
      first = first->next;
      delete first->prew;
    }
  delete first;
}

template<typename Type>
Type& List<Type>::front() {
  return first->value;
}

template<typename Type>
Type& List<Type>::back() {
  return last->prew->value;
}

template<typename Type>
void List<Type>::insert(Iterator position, const Type& element) {
  Node* temp = new Node(element);
  temp->next = position.current;
  temp->prew = position.current->prew;
  position.current->prew = temp;
  if (temp->prew != 0)
    temp->prew->next = temp;
  else
    first = temp;
  ++size;
}

template<typename Type>
void List<Type>::insert(Iterator beginPosition, Iterator endPosition, const Type& element) {
  unsigned int count = 0;
  while (endPosition != beginPosition)
    {
      count++;
      endPosition--;
    }

  Iterator begin = beginPosition;
  while (count-->0)
    {
      insert(begin, element);
    }
}

template<typename Type>
void List<Type>::erase(Iterator position)
{
  Node* temp = position.current;
  temp->next->prew = temp->prew;
  if (temp != first)
    temp->prew->next = temp->next;
  else
    first = temp->next;
  delete temp;
  --size;
}

template<typename Type>
void List<Type>::erase(Iterator beginPosition, Iterator endPosition)
{
  Iterator temp;
  while (beginPosition != endPosition)
    {
      temp = beginPosition;
      beginPosition++;
      erase(temp);
    }
}


template<typename Type>
void List<Type>::clear()
{
  while (first != last)
    {
      first = first->next;
      delete first->prew;
    }
  size = 0;
}

template<typename Type>
void List<Type>::pushBack(const Type& element)
{
  last->value = element;
  last->next = new Node;
  last->next->prew = last;
  last = last->next;		
  ++size;
}

template<typename Type>
void List<Type>::pushFront(const Type& element)
{
  first->prew = new Node(element);
  first->prew->next = first;
  first = first->prew;
  ++size;
}

template<typename Type>
void List<Type>::popBack()
{
  if (last != first)
    {
      last = last->prew;
      delete last->next;
      --size;
    }
}

template<typename Type>
void List<Type>::popFront()
{
  if (first != last)
    {
      first = first->next;
      delete first->last;
      --size;
    }
}

template<typename Type>
unsigned int List<Type>::getSize() const
{
  return size;
}

template<typename Type>
bool List<Type>::isEmpty() const
{
  return first == last;
};

#endif // _List_h_
