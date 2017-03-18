#include "citylist.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
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
  // CityNode* prev, ptr;
  // ptr = head;
  // for (ptr; ptr; ptr->next)
  // {


  // } 
} // destructor of CityList

CityNode::CityNode(const City& ci)
{
  cout<<"construct of node1"<<endl;
  City city(ci);
  cout<<"construct of city in node1"<<endl;
  cout<<"city name rhs"<<ci.name<<endl;
  cout<<"city name "<<city.name<<endl;
  next = NULL;
}

CityNode::CityNode(const City& ci, CityNode* n)
{
  // cout<<"construct of node2"<<endl;
  City city(ci);
  // cout<<"construct of city in node1"<<endl;
  next = n;
}

CityList& CityList::operator+= (const City& rhs)
{
  // cout<<"operator over"<<endl;
  CityNode* tmp = new CityNode(rhs);
  cout<<"+= "<<rhs.name<<endl;
  cout<<"tmp "<<tmp->city.name<<endl;
  if (!head)
  {
    head = tmp;
    tail = head;
    count += 1;
  } // add city to list when list is empty
  else // if it not empty
  {
    tail = head;
    while (tail->next) tail = tail->next;
    tail->next = tmp;
    count += 1;
  } // add node at the tail
  return *this;
} // overload operatot +=


CityList& CityList::operator-= (const City& rhs)
{
  CityNode* tmp, *prev = NULL;
  for (tmp = head; tmp && !(tmp->city.isEqual(rhs)); tmp = tmp->next)
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

