#ifndef CITY_H
#define	CITY_H
// Author: Tony Xiao
#include <iostream>
#include <fstream>
using namespace std;

class City
{
  private:
    double longitude;
    double latitude;
    char *name;
    char *state;
    char airport[4];
    int population;
  public:
    char* getname(){return name; };
    char* getstate(){return state; };
    char* getairport(){return airport; };
    void calcDistance(const City &city2)const;
    void copyLocation(const City &srcCity);
    bool hasAirport();
    int calctraffic(City &city2)const;
    bool isEqual(const City &city2)const;
    void readAirport(char *line, char* stat);
    void readCity(ifstream &infile);
    void setAirport(const char *airportin);
    City& operator = (const City &city1);
    City();
    ~City();
}; // City class

#endif	// CITY_H 

