#!  /bin/bash

testerDirectory="/home/ssdavis/40/p3/P1testing"

if [ $# -ne 1 ]; then
  >&2 echo "usage p3DesignChecker.sh: $testerDirectory/p1DesignChecker.sh simulator.out_directory"
  exit
fi

if [[ $1 =~ P1testing ]]; then # Use from this directory is not allowed
  >&2 echo "You may not use p3testing as your own source directory!"
  exit
fi

cd $1

rm -f designResults.txt
designError=0

grep "/\*" *.cpp *.h > temp
if [ -s temp ]; then
  cat temp >> designResults.txt
  echo 'Fatal design error: "\*" found.' >> designResults.txt
  ((++designError))
fi

CCount=`egrep "malloc|free| struct|stdio" *.cpp *.h | wc -l`

if [ $CCount -ne 0 ]; then
  echo "Fatal design error: malloc, free, struct, or stdio found." >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi


egrep "^(void|int).*\(" city.cpp | grep -v "City *::"  > temp
if [ -s temp ]; then
  echo 'Fatal design error: non-City method found in city.cpp' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

egrep "^(void|int).*\(" vector.cpp | grep -v "Vector *::"  > temp
if [ -s temp ]; then
  echo 'Fatal design error: non-Vector method found in vector.cpp' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

# None fatal design errors from here on, so one line per error

grep -v "//" city.cpp | grep "^ *City *:: *City *(.*)" > temp 
if [ ! -s temp ]; then
  echo 'Design error: Default constructor of City not found in city.cpp.' >> designResults.txt
fi

grep -v "//" vector.cpp | grep "^ *Vector *:: *Vector *(.*)" > temp          
if [ ! -s temp ]; then
  echo 'Design error: Default constructor of Vector not found in vector.cpp.' >> designResults.txt
fi

grep -v "//" city.cpp | grep "^ *City *:: *~City *(.*)" > temp          
if [ ! -s temp ]; then
  echo 'Design error: Destructor of City not found in city.cpp.' >> designResults.txt
fi

grep -v "//" vector.cpp | grep "^ *Vector *:: *~Vector *(.*)" > temp    
if [ ! -s temp ]; then
  echo 'Design error: Destructor of Vector not found in vector.cpp.' >> designResults.txt
fi

grep -v "//" city.cpp | grep "^ *City *& *City *:: *operator *= *(.*)" > temp
if [ ! -s temp ]; then
  echo 'Design error: Overloaded assignment operator of City not found in city.cpp.' >> designResults.txt
fi

grep -v "//" vector.cpp | grep ".*Vector *:: *calcAirportTraffic *(.*)" > temp
if [ ! -s temp ]; then
  echo 'Design error: calcAirportTraffic of Vector not found in vector.cpp.' >> designResults.txt
fi

echo $designError  # Only standard out

