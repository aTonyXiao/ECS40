#ifndef CITY_H
#define CITY_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int R = 3963;
const double Rad = M_PI / 180;
const bool has_airport = true;
const bool no_airport = false;

typedef struct aCity_struct 
{
  double longitude;
  double latitude;
  int population;
  char* name;
  char* state;
  char airport[4];
} City; // City struct

void initialize(City* city);
void readCity(City *city, char *input);
bool isEqual(const City* city1, const City* city2);
void deallocate(City* city);
void copyLocation(const City* city1, City* city2);
double num_passenger(City* city1, City* city2, int distance);
bool hasAirport(City* city);
void setAirport(City* city1, const City* city2);
void calcDistance(City* c1, City* c2, int* dis, const int R, const double Rad);
void readAirport(const char* abbr, const double latitude,
                 const double longitude, City* city);
void copyCity(City* city1, City* city2);
bool isAirport(const City* city, const char* str);
#endif
