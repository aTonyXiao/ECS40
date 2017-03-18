// Author: Tony Xiao
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

City::City():name(NULL), state(NULL)
{
  airport[0] = '\0';  // sentinel value
}  // initialize()


City::~City()
{
  if (name)
    delete name;

  if (state)
    delete state;
}  // deallocate()


void City::calcDistance(const City &city2)const
{
  int distance, passengers;
  
  passengers = (double) population * city2.population / 2500000000U;
  distance = acos(
    sin(latitude * M_PI / 180) * sin(city2.latitude * M_PI / 180) 
    + cos(latitude * M_PI / 180) * cos(city2.latitude * M_PI / 180)
    * cos((longitude - city2.longitude) * M_PI / 180)) * 3963;
  
  if (distance < 100)
    passengers = 0;

  cout << passengers << " passengers fly the " << distance 
       << " miles from" << endl << name << ", " << state << " to " 
       << city2.name << ", " << city2.state << '.' << endl;
  
}  // calcDistance())

void City::copyLocation(const City &srcCity)
{
  strcpy(airport, srcCity.airport);
  latitude = srcCity.latitude;
  longitude = srcCity.longitude;
}  // copyLocation()


bool City::hasAirport()
{
  return airport[0] != '\0';
}  // hasAirport()


bool City::isEqual(const City &city2)const
{

  if (name && city2.name)
    return (strcmp(name, city2.name) == 0 && strcmp(state, city2.state) == 0);
  
  if (airport[0] && city2.airport[0])
    return strcmp(airport, city2.airport) == 0;

  return false;
}  // isName()


void City::readCity(ifstream &infile)
{
  char line[1000], *ptr;
  
  if (!infile.getline(line, 1000) || !strstr(line, ","))
    return;
  
  ptr = strtok(line, ",");
  
  if (ptr)
  {  
    name = new char[strlen(ptr) + 1];
    strcpy(name, ptr);
    ptr = strtok(NULL, ",");
    state = new char[strlen(ptr) + 1];
    strcpy(state, ptr);
    population = atoi(strtok(NULL, ",\n"));
  } // if something on line
}  // readCity()

void City::readAirport(char *line, char* stat)
{
  char *ptr;
  strtok(line, "] ");
  strcpy(airport, &line[1]);
  latitude = atof(strtok(NULL, " "));
  longitude = atof(strtok(NULL, " "));
  ptr = strtok(NULL, ",") + 1;
  name = new char[strlen(ptr) + 1];
  strcpy(name, ptr);
  state = new char[strlen(stat) + 1];
  strcpy(state, stat);
}  // readAirport


void City::setAirport(const char *airportin)
{
  strcpy(airport, airportin);
}  // setAirport()

City& City::operator = (const City &city1)
{
  longitude = city1.longitude;
  latitude = city1.latitude;
  population = city1.population;
  name = new char[strlen(city1.name) + 1];
  strcpy(name, city1.name);
  state = new char[strlen(city1.state) + 1];
  strcpy(state, city1.state);
  strcpy(airport, city1.airport);
  return *this;
} // operator overloard


int City::calctraffic(City &city2)const
{
  int distance, passengers;
  
  passengers = (double) population * city2.population / 2500000000U;
  distance = acos(
    sin(latitude * M_PI / 180) * sin(city2.latitude * M_PI / 180) 
    + cos(latitude * M_PI / 180) * cos(city2.latitude * M_PI / 180)
    * cos((longitude - city2.longitude) * M_PI / 180)) * 3963;
  
  if (distance < 100)
    passengers = 0;

return passengers;
}  // calcDistance())
