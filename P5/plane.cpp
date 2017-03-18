// Author: Sean Davis

#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
#include "plane.h"

using namespace std;

Plane::Plane() 
{
} // Plane()


int Plane::calcCost(int distance, int numPassengers, int *trips) const
{
  double fuelCost, attendantSalaries, pilotSalaries, maintenance, hours;
  int crewHours;
  
  if (distance <= range)
  {
    *trips = ceil ((double) numPassengers / passengers);
    fuelCost =  fuelPrice * distance * fuel / range;
    hours = distance / (double) speed;
    crewHours = ceil((double) hours + 2);
    attendantSalaries = crewHours * ceil((double) passengers / 100) 
      * attendantHourly;
    pilotSalaries = 2 * crewHours * pilotHourly;
    maintenance =  0.000025 * distance * price / speed;
    return ceil(*trips 
      * (fuelCost + attendantSalaries + pilotSalaries + maintenance));
  } // if plane has enough range for distance
   
  *trips = 0;
  return INT_MAX;
} // calcCost()

const char* Plane::getName() const
{
  return name;
}  // getName()


void Plane::getPlane()
{
  cout << "Name: ";
  cin >> name;
  cout << "Passengers: ";
  cin >> passengers;
  cout << "Fuel capacity (in U.S. gallons): ";
  cin >> fuel;
  cout << "Range (in miles): ";
  cin >> range;
  cout << "Speed (in mph): ";
  cin >> speed;
  cout << "Price: ";
  cin >> price;
}  // getPlane())


ostream& operator << (ostream &os, const Plane &plane)
{
  os << setw(12) << left << plane.name << setw(6) << plane.passengers;
  
  if (plane.range >= 1000)
    os << plane.range / 1000 << ',' << setfill('0') << setw(3) 
      << right << plane.range % 1000 << setfill(' ');
  else // range < 1000
    os << setw(5) << right << plane.range;
  
  os << setw(4) << right << plane.speed;
  
  if (plane.fuel >= 1000)
    os << setw(5) << plane.fuel / 1000 << ',' << setfill('0') << setw(3) 
      << plane.fuel % 1000 << setfill(' ');
  else  // plane.fuel < 1000
    os << setw(10) << plane.fuel;
    
  os << setw(6) << fixed << setprecision(3) 
    << plane.range / (double) plane.fuel << setw(6) << setprecision(2)
    << (plane.fuelPrice * plane.fuel) / plane.range << setw(2) << "$"
    << setw(5) << setprecision(1)  << plane.price / 1000000.0 << endl;
    
  return os;
}  // operator<<
