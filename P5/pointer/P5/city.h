#ifndef CITY_H
#define	CITY_H
// Author: Tony Xiao
#include <fstream>
using namespace std;

class City
{
public:
  double longitude;
  double latitude;
  char *name;
  char *state;
  char airport[4];
  int population;
public:
  City();
  ~City();
  City(const City* city);
  void calcDistance(const City *city2, int *distance, int *passengers, 
                    bool display) const;
  void copyLocation(const City *srcCity);
  void deallocate();
  bool hasAirport();
  char* getName();
  char* getState();
  char* getAirport();
  bool isxiangdeng(const City *city2) const;
  void readAirport(char *line, const char *state2);
  void readCity(ifstream &inf);
  void setAirport(const char *airport);
  int showTraffic(const City &destCity) const;
  City& operator= (const City& rhs);
  bool operator== (City* rhs);
  void operator>> (ifstream &inf);
};  // class City

#endif	// CITY_H 

