#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include "city.h"
#include <string.h>
using namespace std;


// void findBracket(Vector *cities)
// {
//   for (int i = 0; i < cities->count; ++i)
//   {
//     City *city = cities->cityArray[i];
//     if (city->state[strlen(city->state)-1] == ')')
//     {
//       printf("Find right bracket at %d: %s\n", i, city->state);
//     }
//   }
// }

void initialize(Vector* vector)
{
  vector -> size = 10;
  vector -> count = 0;
  vector -> cityArray = (City**)malloc((vector -> size) * sizeof(City));
  int i;

  for (i = 0; i < vector -> size; i++)
  {
    vector -> cityArray[i] = (City *)malloc(sizeof(City));
    initialize(vector -> cityArray[i]);
  }// initiallized every city
} // initialized the vector 

void resize(Vector* vector)
{
  int i;
  Vector* tmp = (Vector*)malloc(sizeof(Vector));
  tmp -> size = vector -> size;
  tmp -> count = vector -> count;
  tmp -> cityArray = (City**)malloc(tmp -> size * sizeof(City));

  for (i = 0; i < vector -> size; ++i)
  {
    tmp -> cityArray[i] = (City *)malloc(sizeof(City));
    setAirport((tmp -> cityArray[i]), vector -> cityArray[i]);
  }// set the airport to tmp

  vector -> size = 2 * vector -> size;
  vector -> cityArray = (City**)malloc((vector -> size) * sizeof(City));

  for (i = 0; i < vector -> size / 2 ; ++i)
  {
    vector -> cityArray[i] = (City *)malloc(sizeof(City));
    setAirport(vector -> cityArray[i], tmp -> cityArray[i]);
  }//set the airport back

  for (i = vector -> count; i < vector -> size; i++)
  {
    vector -> cityArray[i] = (City *)malloc(sizeof(City));
    initialize(vector -> cityArray[i]);
  }// initiallized the new half of the city array
  
  for (i = 0; i < vector -> size / 2; ++i)
  {
    deallocate(tmp -> cityArray[i]);
  }// deallocate the vector

  free(tmp -> cityArray);
  free(tmp);
} // resize vector array

void read_citypopulation(Vector* vector)
{
  char str[100];
  ifstream inf("citypopulations.csv");

  while(inf.getline(str, 100) != NULL)
  {   
    if (vector -> count >= vector -> size) 
    {
      resize(vector);
    }// resize

    readCity((vector -> cityArray)[vector -> count], str);
    vector -> count += 1;
  }// read City
} // read citypopulation


void readAirports(Vector* vector)
{
  char *abbr, *name, str[80]; 
  int i = 0, count = 1;
  FILE* inFile = fopen("airportLL.txt", "r");

  while(fgets(str, 70, inFile) != NULL)
  {
    if (str[0] != '[')
    {
      continue;
    }// continue to ingnore the space

    abbr = strtok(str, " ");
    double latitude = atof(strtok(NULL, " "));
    double longitude = atof(strtok(NULL, " "));
    name = strtok(NULL, ",") + 1;
    City* city = (City*)malloc(sizeof(City));
    initialize(city);
    city -> name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    readAirport(abbr, latitude, longitude, city);
    strcpy(city -> name, name);

    for (i = 0; i < vector -> count; i++)
    {
      if (isEqual(city, (vector -> cityArray[i])))
      {
        copyLocation(city, (vector -> cityArray[i]));
      }// copy location if is equal
    }// copy all to city array in vector

    count++;
  }// read line by line of airpotLL.txt  

  fclose(inFile);
}// read Airports

void cleanCities(Vector* vector)
{
  int i = 0;

  for (i = 0; i< vector -> size; i++)
  {
    if (vector -> cityArray[i] -> longitude == -1 ||
        vector -> cityArray[i] -> population == -1)
    {
      // vector -> cityArray[i] = NULL;
    }// remove the city without population or longitude
  } // end of the for loop
}//clean city withour airport

City* findAirport(const Vector* vector, City* city, const char* str)
{
  int i = 0;

  for (i = 0; i < (vector -> count); i++)
  {
    if (isAirport((vector -> cityArray)[i], str))
    {
      setAirport(city, (vector -> cityArray[i]));
      return city;
    }// return the city with airport 
  }//set all city with airport

    return NULL;
} // find the airport

void calcDistance(const int R, const double Rad, 
                  Vector *vector, char *str1, City *city1,
                  char *str2, City *city2, int* dis)
{
  calcDistance(findAirport(vector, city1, str1),
               findAirport(vector, city2, str2), dis, R, Rad);
} // calculate the distance

double num_passenger(const int R, const double Rad,
                     Vector *vector, char *str1, 
                     City *city1, char *str2, City *city2, int* dis)
{
  calcDistance(R, Rad, vector, str1, city1, str2, city2, dis);
  return num_passenger(city1, city2, *dis);
} // get the num_passenger

void deallocate(Vector* vector)
{

  for (int i = 0; i < vector->size; ++i)
  {
    deallocate(vector->cityArray[i]);
  }// deallocate the city array

  free(vector->cityArray);
}// deallocate city array

void run()
{
  char input1[80];
  char input2[80];
  int num_passengers;
  int miles;
  Vector* cities = (Vector*)malloc(sizeof(Vector));
  initialize(cities);
  read_citypopulation(cities);
  readAirports(cities);
  cleanCities(cities);
  City* city1 = (City *)malloc(sizeof(City));
  City* city2 = (City *)malloc(sizeof(City));
  initialize(city1);
  initialize(city2);
  runpart2(input1, input2, &num_passengers, &miles, cities, city1, city2);
  deallocate(cities);
}// run the function

void runpart2(char* input1, char* input2, int* num_passengers,
              int* miles, Vector* cities, City* city1, City* city2)
{

  while(!(strcmp(input1, "XXX") == 0 && strcmp(input2, "XXX") == 0))
  {
    printf("\nPlease enter two airport abbreviations (XXX XXX = done): ");

    scanf("%s %s", input1, input2); exit(input1, input2);

    if (findAirport(cities, city1, input1) == NULL)
    {
      printf("%s is not a valid airport.\n", input1);

      if (findAirport(cities, city2, input2) == NULL)
      {
        printf("%s is not a valid airport.\n", input2); continue;
      }// invalid input

      continue;
    }// invalid input

    if (findAirport(cities, city2, input2) == NULL)
    {
      printf("%s is not a valid airport.\n", input2); continue;
    }//invalid input

    calcDistance(R, Rad, cities, input1, city1, input2, city2, miles);
    *num_passengers = (int)num_passenger
      (R, Rad, cities, input1, city1, input2, city2, miles);
    printf("%d passengers fly the %d miles from\n%s,%s to %s,%s\n",
           *num_passengers, *miles, city1 -> name,
           city1 -> state, city2 -> name, city2 -> state);
  }// run-time 
}// run input 


void exit(char* input1, char* input2)
{
  if ((strcmp(input1, "XXX") == 0 && strcmp(input2, "XXX") == 0))
  {
    exit(0);
  }// exit
}// exit when input "XXX XXX"
