// Author: Tony Xiao
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "airport.h"
using namespace std;


ostream& operator <<(ostream& os, const Airport &rhs)
{
  os << rhs.airport << ": ";

  for (int i = 0; i < rhs.flights.getCount(); i++)
    os << rhs.flights[i];

  os << "\n";
  return os;
} // airport

ostream& operator <<(ostream& os, const Flight &rhs)
{
  char abbravAir[3];
  abbravAir[0] = rhs.company[0];
  abbravAir[1] = rhs.company[1];
  os << abbravAir << "-" << rhs.desti << " ";
  return os;
}//123


void Airport::hasRoute(const List<Airport> &cities, 
                       List<Flight> &route, const char* company, 
                       const char* airport2, bool *has) const
{ 
  Flight fly;
  strcpy(fly.company, company);
  strcpy(fly.desti, airport);

  if (strcmp(airport2, airport) == 0)
  {
      *has = true;
      route += fly;
      return;
  }//if
  else //else
  {
    for (int i = 0; i < flights.getCount(); i++)
    {
      if (strcmp(flights[i].company, company) == 0)
      {
        for (int j = 0; j < cities.getCount(); j++)
        {
          if (strcmp(cities[j].airport, flights[i].desti) == 0)
          {
            cities[j].hasRoute(cities, route, company, airport2, has);
            break;
          }//if
        }//for

        if (*has == true)
        { 
          route += fly;
          return;
        }//if
      }//for
    }//else
  }//else
}//hasRoute

void Airport::getPrint()
{
  for (int i = count - 1; i >= 0; i--)
  {
    flights[i].getCompany();
    cout << "-" << flights[i].getDesti() << " ";
  }//get print
}// get priont

void Flight::getCompany()
{
  char twoco[3];
  strncpy(twoco, company, 2);
  twoco[2] = '\0';
  cout << twoco;
}//get 2 company

char* Flight::getDesti()
{
  return desti;
} // getDesti


void Airport::readFlights(char *line)
{
  // cout<<line<<endl;
  strtok(line, " ");
  // cout<<line<<endl;
  count = atoi(strtok(NULL, " "));
  // cout<<count<<endl;
  for (int i = 0; i < count; i++)
  {
    Flight fly;
    fly.setCompany(strtok(NULL, " "));
    fly.setDesti(strtok(NULL, " "));
    flights += fly;
  } //for

  return;
} //airport
// Airport::Airport()


bool Flight::operator< (const Flight& rhs) const
{
  return false;
} // operator <
void Flight::setCompany(const char* company2)
{
  strcpy(company, company2);
} // setCompany


void Flight::setDesti(const char* desti2)
{
  strcpy(desti, desti2);
} // serde 


