// Author: Tony Xiao
#include "vector.h"
#include "plane.h"

#include <climits>


#include <iomanip>
#include <cstring>

#include <cstdlib>
#include <iostream>
using namespace std;


void addPlaneInformation(Plane planes[], int *pCount)
{
  planes[*pCount].getPlane();
  ofstream outf("planes.dat", ios::app | ios::binary);
  outf.write((char*) &planes[(*pCount)++], sizeof(Plane));
}  // addPlaneInformation()

void calcDistance(const Vector *cities)
{
  char airport1[80], airport2[80];
  int index1, index2, distance, passengers;
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> airport1 >> airport2;
  index2 = cities->findAirport(airport2);
  index1 = cities->findAirport(airport1);

  if (index1 >= 0 && index2 >= 0)
    cities->calcDistance(index1, index2, &distance, &passengers, true);
}  // calcDistance())


void determineAirportTraffic(const Vector *cities)
{
  char airport[80];
  int index;
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  index = cities->findAirport(airport);

  if (index >= 0 && index >= 0)
    cities->calcAirportTraffic(index);
}  // determinAirportTraffic()

void readPlanes(Plane planes[], int *pCount)
{
  ifstream inf("planes.dat", ios::binary);
  *pCount = 0;
  
  if (! inf)
    return;

  while(inf.read((char*) &planes[(*pCount)++], sizeof(Plane)));

  --(*pCount);
  inf.close();
} // readPlanes()

void determineBestPlane(const Vector *cities, const Plane *planes, 
                        int pCount)
{
  char airport1[80], airport2[80];
  int index1, index2, distance, passengers, minIndex = -1, minCost = INT_MAX, 
    minTrips, trips, cost;
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> airport1 >> airport2;
  index1 = cities->findAirport(airport1);
  index2 = cities->findAirport(airport2);

  if (index1 >= 0 && index2 >= 0)
  {
    cities->calcDistance(index1, index2, &distance, &passengers, false);
      
    for (int i = 0; i < pCount; i++)
    {
       cost = planes[i].calcCost(distance, passengers, &trips);
       
       if (trips > 0 && cost < minCost)
       {
         minTrips = trips;
         minCost = cost;
         minIndex = i;
       }  // if lower cost
    }  // for each plane
    
    if (minIndex == -1)
      cout << "No planes available\n";
    else // print the message
    {
      cout << "Passengers Miles  Trips Name      Cost\n";
      cout << left << setw(11) << passengers << setw(7) << distance << setw(6) 
        << minTrips << setw(10) << planes[minIndex].getName() << '$' << minCost 
        << endl;
    } // end of else
  }   // if valid inputs  
}  //  determineBestPlane



void displayPlaneInformation(const Plane *planes, int pCount)
{
  cout << "\nPlane Information\n";
  cout << "Name        Pass. Range Speed Fuel   MPG   $/mi  Price * 10^6\n";
  
  for (int i = 0; i < pCount; i++)
    cout << planes[i];

}  // displayPlaneInformation()


int getChoice()
{
  int choice;

  do
  {
    cout << "\nFlight Simulator Menu" << endl;
    cout << "0. Done." << endl;
    cout << "1. Determine distance and passengers between two airports." 
         << endl;
    cout << "2. Determine all traffic from one airport." 
         << endl;
    cout << "3. Display planes information." << endl;
    cout << "4. Add plane information." << endl;
    cout << "5. Determine best plane between two airports.\n" 
         << endl;
    cout << "Your choice (0 - 5): ";
    cin >> choice;
    cin.ignore(1000, '\n');
   
    if  (choice < 0 || choice > 5)
      cout << "Your choice must be between 0 and 5. Please try again.\n\n";
  } while(choice < 0 || choice > 5);
   
  return choice;
}  // getChoice()  






void run(const Vector *cities, Plane *planes, int pCount)
{
  int choice;
  
  do
  {
    choice = getChoice();

    if (choice == 1){calcDistance(cities); } // choice 1

    if (choice == 2){determineAirportTraffic(cities); } // choice 2

    if (choice == 3){displayPlaneInformation(planes, pCount); } // choice 3

    if (choice == 4){addPlaneInformation(planes, &pCount); } // choice 4

    if (choice == 5)
    {
      determineBestPlane(cities, planes, pCount);
    } // choice 5

  } while(choice != 0);
}  // run())


int main(int argc, char** argv) 
{
  Vector cities;

  Plane planes[10];
  int Count = 0;
  cities.readCities();

  cities.readAirports();
  cities.cleanCities();

  readPlanes(planes, &Count);
  run(&cities, planes, Count);
  return 0;
} // main())

