// Author: Tony Xiao
#include <iomanip>

#include <iostream>
#include <cmath>
#include <climits>

#include "plane.h"

using namespace std;

Plane::Plane() {} // Plane()

const char* Plane::getName() const
{
  return name;
} // get name



int Plane::calcCost(int distance, int numPass, int *trips) const
{
  double Cost, attendSalary, pioltSalary, maintan, hour;
  int crewH;
  
  if (distance <= range)
  {
    *trips = ceil ((double) numPass / (double) passengers);

    Cost =  fuelPrice * distance * fuel / range;
    hour = distance / (double) speed;
    crewH = ceil((double) hour + 2);

    attendSalary = crewH * ceil((double) passengers / 100) 
                        * attendantHourly;
    pioltSalary = 2 * crewH * pilotHourly;
    maintan =  0.000025 * distance * price / speed;
    return ceil(*trips 
                * (Cost + attendSalary + pioltSalary + maintan));
  } // if dis <= range calc the cost 
   
  *trips = 0;
  return INT_MAX;
} // calculate the cost


ostream& operator << (ostream &ost, const Plane &plane)
{
  ost << setw(12) << left << plane.name << setw(6) << plane.passengers;
  
  if (plane.range >= 1000)
    ost << plane.range / 1000 << ',' << setfill('0') << setw(3) 
      << right << plane.range % 1000 << setfill(' ');
  else // else range < 1000
    ost << setw(5) << right << plane.range;
  
  ost << setw(4) << right << plane.speed;
  
  if (plane.fuel >= 1000)
    ost << setw(5) << plane.fuel / 1000 << ',' << setfill('0') << setw(3) 
      << plane.fuel % 1000 << setfill(' ');
  else // else fuel < 1000
    ost << setw(10) << plane.fuel;
    
  ost << setw(6) << fixed << setprecision(3) 
    << plane.range / (double) plane.fuel << setw(6) << setprecision(2)
    << (plane.fuelPrice * plane.fuel) / plane.range << setw(2) << "$"
    << setw(5) << setprecision(1)  << plane.price / 1000000.0 << endl;
    
  return ost;
}  // overload operator<<



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
}  // getPlane


