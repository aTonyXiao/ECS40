#ifndef CITYLIST_H
#define CITYLIST_H
// Author: Tony Xiao
#include <fstream>
#include "city.h"

class CityNode;
class CityList
{
private:
  CityNode* head;
  CityNode* tail;
  static int count;
public:
  CityList();
  ~CityList();
  City* operator[] (const int index)const;
  City* operator[] (const int index);
  CityList& operator += (const City* rhs);
  CityList& operator-= (const City* rhs);
  static int getCount();
}; //City list



class CityNode
{
friend class CityList;
  City* city;
  CityNode* next;
  CityNode(const City* ci);
  CityNode(const City* ci, CityNode* n);
}; //City node

#endif  // CITYLIST_H 