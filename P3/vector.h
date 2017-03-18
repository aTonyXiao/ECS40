#ifndef VECTOR_H
#define	VECTOR_H
// Author Tony Xiao

#include "city.h"
#include <iostream>
#include <fstream>
using namespace std;

class Vector
{
  private:
    City *cityArray;
    int size, count;
  public:
    void calcDistance(int index1, int index2)const;
    void cleanCities();
    int findAirport(const char *airport)const;
    void readAirports();
    void readCities();
    void resize();
    void calcAirportTraffic(const char* input);
    Vector();
    ~Vector();
}; // Vector class

#endif	// VECTOR_H 

