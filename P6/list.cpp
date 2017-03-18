// Author: Tony Xiao
#include <iostream>
#include <cstdlib>

using namespace std;




template <class T>
ListNode<T>::ListNode(const T &c, ListNode<T> *node) : data(c), next(node){}//



template <class T>
void List<T>::decreCount()
{
  count--;
}// count --

template <class T>
List<T>::List() : head(NULL), tail(NULL), count(0){}//const


template <class T>
List<T>::~List() {}//destr

template <class T>
const int List<T>::getCount() const
{
  return count;
}  // getCount

template <class T>
List<T>&  List<T>::operator += (const T &rhs)
{
  
    ListNode<T> *ptr, *prev = NULL;

    for (ptr = head; (ptr && (ptr->data < rhs)); ptr = ptr->next)
      prev = ptr;

    if (!prev)
      head = new ListNode<T>(rhs, ptr);
    else //else
      prev->next = new ListNode<T>(rhs, ptr);
  
  count++;

  return *this;
}  // operator+=

template <class T>
List<T>& List<T>::operator -= (const T &rhs)
{
  ListNode<T> *ptr, *prev = NULL;
  
  for (ptr = head; ptr && ! (ptr->data == rhs); ptr = ptr->next)
    prev = ptr;
  
  if (ptr)
  {
    count--;
    
    if (!prev)  // found at front of list
    {
      head = ptr->next;
      
      if (!head)  // head == NULL so now empty list
        tail = NULL;
    }  // if removing first node
    else // removing node after the first
    {
      prev->next = ptr->next;
      
      if (tail == ptr)
        tail = prev;
    }  // else removing after the first node
    
    delete ptr;
  }  // if found 

  return *this;
}  // operator -=

template <class T>
const T& List<T>::operator [] (int index) const
{
  int pos = 0;
  ListNode<T> *ptr;
  
  for (ptr = head; ptr && pos != index; ptr = ptr->next, pos++);
   
  if (!ptr)
  {
     cout << "Error in array indexing!\n";
     exit(1);
  }  // if index beyond end of list

  return ptr->data; 
}  // const operator[]
 
template <class T>
T& List<T>::operator [] (int index)
{
  int pos = 0;
  ListNode<T> *ptr;
   
  for (ptr = head; ptr && pos != index; ptr = ptr->next, pos++);
   
  if (!ptr)
  {
    cout << "Error in array indexing!\n";
    exit(1);
  } // if index beyond end of the array.

  return ptr->data; 
}  // non-const operator[]

template <class T>
ostream& operator <<(ostream& os, const List<T> &rhs)
{
  for ( int i = 0; i < rhs.getCount(); i++)
    os << rhs[i];

  return os;
}//<<