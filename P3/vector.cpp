// Author: Tony Xiao


#include <iostream>
#include <cstdlib>
#include <cstring>
#include "vector.h"
#include <fstream>
using namespace std;

Vector::Vector()
{
  size = 10; 
  count = 0;
  cityArray = new City[size];
} // cons

Vector::~Vector()
{
  // if (cityArray != NULL)
  //   delete [] cityArray;
} // dest

void Vector::calcDistance(int index1, int index2)const
{
  cityArray[index1].calcDistance(cityArray[index2]);
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


int Vector::findAirport(const char *airport)const
{
  City city;
  city.setAirport(airport);

  for (int i = 0; i < count; i++)
    if (cityArray[i].isEqual(city))
      return i;

    cout << airport << " is not a valid airport." << endl;
  return -1;
}  // findAirport()


void Vector::readAirports()
{
  char line[1000];
  City city;
  char* stat;
  ifstream inf("airportLL.txt");

  while (inf.getline(line, 1000))
  {
    if (isalpha(line[0]))
    {  
      strtok(line, "\n");
      stat = new char[strlen(line) + 1];
      strcpy(stat, line);
    } // check the state

    if (line[0] == '[')
    {
     city.readAirport(line, stat);
      
     for (int i = 0; i < count; i++)
     {
       if (cityArray[i].isEqual(city))
        {
          cityArray[i].copyLocation(city);
          break;
        }  // if found a matching name
      }// end of the for loop
      // city.deallocate();
    } // if an airport line
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
  cityArray = temp;
}  // resize()

void Vector::calcAirportTraffic(const char* input)
{
  int totalnum = 0, num = 0;
  int i = findAirport(input);

  if (i < 0)
  {
    return;
  } // if input is invalid return

  for (int j = 0; j < i; j++)
  {
    num = cityArray[i].calctraffic(cityArray[j]);
    totalnum += num;
    cout << cityArray[j].getname() << ", " 
         << cityArray[j].getstate() << ": " << num << endl;
  } // print the city before input

  for (int j = i + 1; j < count; j++)
  {
    num = cityArray[i].calctraffic(cityArray[j]);
    totalnum += num;
    cout << cityArray[j].getname() << ", " 
         << cityArray[j].getstate() << ": " << num << endl;
  } // print the city after input
  
  cout << "Total passengers: " << totalnum << endl;
} // calculate the airport traffic
