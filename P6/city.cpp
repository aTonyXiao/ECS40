// Author: Tony Xiao
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"
using namespace std;

City::City()
{
  name = NULL;
  state = NULL;
  population = 0;
  airport[0] = '\0';  // sentinel value
}  // City()


City::City(const City &rhs) : longitude(rhs.longitude), latitude(rhs.latitude),
  name(NULL), state(NULL), population(rhs.population)
{
  if (rhs.name)
  {
    name = new char [strlen(rhs.name) + 1];
    strcpy(name, rhs.name);
  }  // if rhs has a name
  
  if (rhs.state)
  {
    state = new char[strlen(rhs.state) + 1];
    strcpy(state, rhs.state);
  }  // if rhs has a state

  strcpy(airport, rhs.airport); 
}  // City copy constructor

City::~City()
{
  // if (name)
  //   delete [] name;

  // if (state)
  //   delete [] state;
}  // deallocate()


void City::calcDistance(const City *city2, int *distance, int *passengers, 
                        bool display) const
{
  *passengers = (double) population * city2->population / 2500000000U;
  *distance = acos(
    sin(latitude * M_PI / 180) * sin(city2->latitude * M_PI / 180) 
    + cos(latitude * M_PI / 180) * cos(city2->latitude * M_PI / 180)
    * cos((longitude - city2->longitude) * M_PI / 180)) * 3963;
  
  if (*distance < 100)
    *passengers = 0;

  if (display)
  {
    cout << *passengers << " passengers fly the " << *distance 
      << " miles from\n";
    cout << name << ", " << state << " to "
      << city2->name << ", " << city2->state << ".\n";
  }  // if display
}  // calcDistance())


void City::copyLocation(const City *srcCity)
{
  strcpy(airport, srcCity->airport);
  latitude = srcCity->latitude;
  longitude = srcCity->longitude;
}  // copyLocation()

void City::deallocate()
{
  // if (name)
  //   delete[] name;

  // name = NULL;
    
  // if (state)
  //  delete[] state;
   
  //  state = NULL;
}  // deallocate()


bool City::hasAirport()
{
  return airport[0] != '\0';
}  // hasAirport()

char* City::getAirport()
{
  return airport;
}//get airport


void City::readAirport(char *line, const char *state2)
{
  char *ptr;
  
  strtok(line, "] ");
  strcpy(airport, &line[1]);
  latitude = atof(strtok(NULL, " "));
  longitude = atof(strtok(NULL, " "));
  ptr = strtok(NULL, ",") + 1;
  name = new char[strlen(ptr) + 1];
  strcpy(name, ptr);
  state = new char[strlen(state2) + 1];
  strcpy(state, state2);
}  // readAirport


void City::setAirport(const char *airport2)
{
  strcpy(airport, airport2);
}  // setAirport()


int City::showTraffic(const City &destCity) const
{
  int passengers = (double) population * destCity.population / 2500000000U;
  
  int distance = acos(
    sin(latitude * M_PI / 180) * sin(destCity.latitude * M_PI / 180) 
    + cos(latitude * M_PI / 180) * cos(destCity.latitude * M_PI / 180)
    * cos((longitude - destCity.longitude) * M_PI / 180)) * 3963;
  
  if (distance < 100)
    passengers = 0;
  
  cout << destCity.name << ", " << destCity.state << ": "
    << passengers << endl;
  return passengers;
}  // showTraffic())

City& City::operator= (const City& rhs)
{
  if (&rhs == this)
    return *this;
  
  if (name)
    delete[] name;

  if (state)
   delete[] state;
   
  name = state = NULL;
  
  longitude = rhs.longitude;
  latitude = rhs.latitude;
  
  if (rhs.name)
  {
    name = new char[strlen(rhs.name) + 1];
    strcpy(name, rhs.name);
  }  // if rhs has a name 
  
  if (rhs.state)
  {
    state = new char[strlen(rhs.state) + 1];
    strcpy(state, rhs.state);
  }  // if rhs has a state
  
  strcpy(airport, rhs.airport);
  population = rhs.population;
  return *this;
}  // operator=

bool City::operator == (const City &rhs) const
{
  if (name && rhs.name && state && rhs.state)
    return strcmp(name, rhs.name) == 0 
      && strcmp(state, rhs.state) == 0;
  
  if (airport[0] && rhs.airport[0])
    return strcmp(airport, rhs.airport) == 0;
  
  return false;
}  // operator==()

istream& operator >> (istream &is, City &rhs)
{
  char line[1000], *ptr;
  
  if (! is.getline(line, 1000) || !strstr(line, ","))
    return is;
  
  ptr = strtok(line, ",");
  
  if (ptr)
  {  
    rhs.name = new char[strlen(ptr) + 1];
    strcpy(rhs.name, ptr);
    ptr = strtok(NULL, ",");
    rhs.state = new char[strlen(ptr) + 1];
    strcpy(rhs.state, ptr);
    rhs.population = atoi(strtok(NULL, ",\n"));
  } // if something on line
  
  return is;
}  // readCity()

bool City::operator < (const City &rhs) const
{
  return (this->population < rhs.population);
}  // operator<()