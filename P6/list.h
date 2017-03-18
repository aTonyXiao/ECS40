#ifndef LIST_H
  #define LIST_H

template <class T>
class List;

#include <iostream>
#include <fstream>
using namespace std;

template <class T>
ostream& operator << (ostream& os, const List<T>& rhs);

template <class T>
class ListNode
{
  T data;
  ListNode<T> *next;
  ListNode(const T &c, ListNode<T> *node);
  friend class List<T>;
};  // class CityNode

template <class T>
class List 
{

  ListNode<T> *head;
  ListNode<T> *tail;
  int count;
public:
  List();
 // List(const List<T>& orig);
  ~List();
  const int getCount() const;
  void decreCount();
 List<T>&  operator += (const T &rhs);
 List<T>& operator -= (const T &rhs);
 const T& operator [] (int index) const;
 T& operator [] (int index);
 friend ostream& operator <<<T>(ostream& os, const List<T> &rhs);

}; // class CityList 

#include "list.cpp"
#endif  // LIST_H 

