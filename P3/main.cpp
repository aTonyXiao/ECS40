// Author: Tony Xiao

#include <cstdlib>
#include <cstring>
#include "vector.h"
#include <iostream>
using namespace std;

int getChoice()
{
  int num = 0;

  while(1)
  {  
    cout << "\nFlight Simulator Menu" << endl;
    cout << "0. Done." << endl;
    cout << "1. Determine distance and passengers between two airports."  
         << endl;
    cout << "2. Determine all traffic from one airport.\n" << endl;
    cout << "Your choice (0 - 2): ";
    cin >> num;

    if (num > 2 || num < 0)
    {
      cout << "Your choice must be between 0 and 2. Please try again." << endl;
    } // the error message

    if (num == 0) 
    {
      exit(0);
    } // exit

    if (num == 1) 
    {
      return 1;
    } // return 1

    if (num == 2) 
    {
      return 2;
    } // return 2
  } //while
} // get choice



void run(Vector cities)
{

  char airport1[80], airport2[80];
  int index1, index2;

  while (1)
  {
    int num = getChoice();

    if (num == 1)
    {

      cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
      cin >> airport1;
      cin >> airport2;
 
      index1 = cities.findAirport(airport1);
      index2 = cities.findAirport(airport2);
    
      if (index1 >= 0 && index2 >= 0)
        cities.calcDistance(index1, index2);
    } // end of if

    else // else 
    {
      cout << "\nPlease enter an airport abbreviation (XXX): ";
      cin >> airport1;
      cities.calcAirportTraffic(airport1);
    } // else
  }  // infinite while loop
}  // run())



int main(int argc, char** argv) 
{
  Vector cities;
  cities.readCities();
  cities.readAirports();
  cities.cleanCities();

  run(cities);

  return 0;
} // main())

