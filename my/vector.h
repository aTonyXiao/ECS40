#ifndef VECTOR_H
#define VECTOR_H
#include "city.h"


typedef struct aVector_struct
{
  City** cityArray;
  int size;
  int count;
} Vector; // vector struct

void initialize(Vector* vector);
void resize(Vector* vector);
void read_citypopulation(Vector* vector);
void readAirports(Vector* vector);
void deallocate(Vector* vector);
void cleanCities(Vector* vector);
City* findAirport(const Vector* vector, City* city, const char* str);
void calcDistance(const int R, const double Radian,
                  Vector *vector, char *str1, City *city1,
                  char *str2, City *city2, int* dis);
double num_passenger(const int R, const double Radian,
                     Vector *vector, char *str1, City *city1,
                     char *str2, City *city2, int* dis);
void run();
void runpart2(char* input1, char* input2, int* num_passengers,
              int* miles, Vector* cities, City* city1, City* city2);
void exit(char* input1, char* input2);

#endif