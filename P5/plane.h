#ifndef PLANE_H
#define	PLANE_H

#include <iostream>
using namespace std;

class Plane 
{
  char name[12];
  int passengers;
  int range; // in miles
  int speed; // in mile per hour
  int fuel;  // in U.S. gallons
  int price;  // in U.S. dollars
  static const int attendantHourly = 30;
  static const int pilotHourly = 100;
public:
  Plane();
  int calcCost(int distance, int numPassengers, int *trips) const;
  const char* getName() const;
  void getPlane();
  friend ostream& operator << (ostream &os, const Plane &plane);
  static const double fuelPrice = 3.39;
};  // class Plane

#endif	// PLANE_H

