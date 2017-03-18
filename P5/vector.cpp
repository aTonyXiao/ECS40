// Author: Sean Davis

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "citylist.h"
using namespace std;

Vector::Vector()
{
  size = 10;
  count = 0;
  cityArray = new City[size];
}  // initialize()


void Vector::calcAirportTraffic(int index) const
{
  int total = 0;
  
  for (int i = 0; i < count; i++)
    if (i != index)
      total += cityArray[index].showTraffic(cityArray[i]);
  
  cout << "Total passengers: " << total << endl;
}  // calcAirportTraffic()

Vector::~Vector()
{
  delete [] cityArray;
}  // deallocate())


void Vector::calcDistance(int index1, int index2, int *distance, 
                          int *passengers, bool display) const
{
  cityArray[index1].calcDistance( &cityArray[index2], distance, passengers,
    display);
}  // calcDistance()

void Vector::cleanCities()
{
  int i = 0;
  
  while (i < count)
  {
    if (!cityArray[i].hasAirport())
    {
      cityArray[i] = cityArray[--count];
    }  // if city does not have an airport
    else // city has an airport
      i++;
  }  // while more in array
}  // cleanCities())


int Vector::findAirport(const char *airport) const
{
  City city;
  
  city.setAirport(airport);
  
  for (int i = 0; i < count; i++)
    if (cityArray[i].isEqual(&city))
      return i;
  
  cout << airport << " is not a valid airport.\n";
  return -1;
}  // findAirport()


void Vector::readAirports()
{
  char line[1000], state2[80];
  City city;
  ifstream inf("airportLL.txt");

  while (inf.getline(line, 1000))
  {
    if (isalpha(line[0]))
      strcpy(state2, strtok(line, "\n"));
    
    if (line[0] == '[')
    {
      city.readAirport(line, state2);
      
      for (int i = 0; i < count; i++)
        if (cityArray[i].isEqual(&city))
        {
          cityArray[i].copyLocation(&city);
          break;
        }  // if found a matching name
      
      city.deallocate();
    }  // if an airport line
  }  // while
}  // readAirports()


void Vector::readCities()
{
  ifstream inf("citypopulations.csv");
  
  while(!inf.eof())
  {
    if (size == count)
      resize();
  
    cityArray[count++].readCity(inf);
  } // while more in file
  
  count--;
  inf.close();
}  // readCities()


void Vector::resize()
{
  int i;
  City *temp = new City[2 * size];
  
  for (i = 0; i < size; i++)
    temp[i] = cityArray[i];
  
  size *= 2;
  
  delete[] cityArray;
  cityArray = temp;
}  // resize()


