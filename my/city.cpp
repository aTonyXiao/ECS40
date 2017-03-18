#include "city.h"

void initialize(City* city)
{
  city -> longitude = -1;
  city -> latitude = -1;
  city -> population = -1;
  city -> name = NULL;
  city -> state = NULL;
  city -> airport[0] = 'D';
  city -> airport[1] = 'D';
  city -> airport[2] = 'D';
  city -> airport[3] = '\0';
} // initialize the city


void readCity(City *city, char *input)
{
  char *cityname = strtok(input, ",");
  char *state = strtok(NULL, ",");
  city -> name = (char*)malloc((strlen(cityname) + 1) * sizeof(char));
  strcpy(city -> name, cityname);
  city -> state = (char*)malloc((strlen(state) + 1) * sizeof(char));
  strcpy(city -> state, state);
  city -> population = atoi(strtok(NULL, ","));
} // read city from each line

void readAirport(const char* abbr, const double latitude, 
                 const double longitude, City* city)
{
  int i;
  char abbra[4];

  for (i = 1; i < 4; i++)
  {
    abbra[i - 1] = abbr[i];
  }// delete the braket

  strcpy(city -> airport, abbra);
  city -> longitude = longitude;
  city -> latitude = latitude;
} // read Airport


bool isEqual(const City* city1, const City* city2)
{
 
  if (strcmp(city1 -> name, city2 -> name) == 0 ||
      strcmp(city1 -> airport, city2 -> airport) == 0)
  {
    return true;
  }// return true if is equal
  else // otherwise
  { 
    return false;
  }// return false if is not
} // compare names & airport of two cities 

void deallocate(City* city)
{
  free(city -> name);
  free(city -> state);
} // deallocate city

void copyLocation(const City* city1, City* city2)
{
  city2 -> longitude = city1 -> longitude;
  city2 -> latitude = city1 -> latitude;
  strcpy(city2 -> airport, city1 -> airport);
} // copy location 

bool hasAirport(City* city)
{
  if (city -> longitude == -1)
  {
    return false;
  }// not airport
  else // otherwise
  {
    return true;
  }// has airport
}// check if has a airport

void setAirport(City* city1, const City* city2)
{
  city1 -> longitude = city2 -> longitude;
  city1 -> latitude = city2 -> latitude;
  city1 -> population = city2 -> population;
  city1 -> name = (char*)malloc((strlen(city2 -> name) + 1) * sizeof(char));
  strcpy(city1 -> name, city2 -> name);
  city1 -> state = (char*)malloc((strlen(city2 -> state) + 1) * sizeof(char));
  strcpy(city1 -> state, city2 -> state);
  strcpy(city1 -> airport, city2 -> airport);
}// give city2 value to city1

void calcDistance(City* c1, City* c2,
                  int* dis, const int R, const double Rad)
{
  *dis = (int)(acos(sin(c1 -> latitude * Rad) * 
                    sin(c2 -> latitude * Rad) +
                    cos(c1 -> latitude * Rad) * 
                    cos(c2 -> latitude * Rad) *
                    cos(c1 -> longitude * Rad - 
                    c2 -> longitude * Rad)) * R);
}// calculate the distance between two city

double num_passenger(City* city1, City* city2, int distance)
{
  if (distance < 100)
  {
  return 0;
  }// no passengers would fly when distance < 100
  else // otherwise return the num
  {
  return (((double)city1 -> population) * city2 -> population) / 250000000;
  }// return the num of passengers
}// return the num of passenger

bool isAirport(const City* city, const char* str)
{
  if (strcmp(str, city->airport) == 0)
  {
    return true;
  }// find airport
  else // otherwise
  {
    return false;
  }// not find  
} // find the airport