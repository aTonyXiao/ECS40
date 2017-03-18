#ifndef VECTOR_H
#define	VECTOR_H
// Author Sean Davis

#include "city.h"

class Vector
{
  City *cityArray;
  int size;
  int count;
  void resize();
public:
  Vector();
  ~Vector();
  void calcAirportTraffic(int index) const;
  void calcDistance(int index1, int index2, int *distance, int *passengers, 
                    bool display) const;
  void cleanCities();
  int findAirport(const char *airport) const;
  void readAirports();
  void readCities();
};  // class Vector

#endif	// VECTOR_H 

