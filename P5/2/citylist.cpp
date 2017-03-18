#include "citylist.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <math.h>
#include "city.h"
using namespace std;

int CityList::count = 0;
CityList::CityList()
{
  head = NULL;
  tail = NULL;
} // constructor of CityList with no value


CityList::~CityList()
{
  // if (head)
  //   delete [] head;
  // if (tail)
  //   delete [] tail;
} // destructor of CityList



CityList& CityList::operator+= (const City& rhs)
{
  CityNode* tmp = new CityNode(rhs);
  if (!head)
  {
    head = new CityNode(rhs);
    count += 1;
    return *this;
  } // add city to list when list is empty
  else // if it not empty
  {
    tail = head;
    while (tail->next) tail = tail->next;
    tail->next = tmp;
    count += 1;
    return *this;
  } // add node at the tail
} // overload operatot +=


CityList& CityList::operator-= (const City& rhs)
{
  CityNode* tmp, *prev = NULL;
  for (tmp = head; tmp && !(tmp->city.isEqual(&rhs)); tmp = tmp->next)
    prev = tmp;
  prev->next = tmp->next; 
  count -= 1;
  return *this;
} // overload operatot -=


City& CityList::operator[] (const int index)const
{
  CityNode* tmp = head;
  for (int i = 0; i < count && i != index; i++)
  {
    tmp = tmp->next;
  }// find the desire node
  return tmp->city;
}// const function 

City& CityList::operator[] (const int index)
{
  CityNode* tmp = head;
  for (int i = 0; i < count && i != index; i++)
  {
    tmp = tmp->next;
  } // find the desire node
  return tmp->city;
} // const function

