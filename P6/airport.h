#ifndef AIRPORT_H
#define AIRPORT_H
// Author: Tony Xiao
#include <fstream>
#include "city.h"
#include "list.h"
using namespace std;
class Flight;

class Airport : public City
{
  int count;
  List<Flight> flights;
public:
  void readFlights(char *line);
  void getPrint();
  void hasRoute(const List<Airport> &cities, List<Flight> &route,
                const char* company, const char* airport2, bool *has) const;
  friend ostream& operator <<(ostream& os, const Airport &rhs);
};  // class City


class Flight
{
  char company[10];
  char desti[4];
public:
  void setCompany(const char* company2);
  void getCompany();
  char* getDesti();
  void setDesti(const char* desti2);
  bool operator< (const Flight& rhs) const;
  friend ostream& operator <<(ostream& os, const Flight &rhs);
    friend class Airport;
};  // class CityNode


#endif  // AIRPORT_H 

