#!  /bin/bash

testerDirectory="/home/ssdavis/40/p1/P1testing"

if [ $# -ne 1 ]; then
  >&2 echo "usage p1DesignChecker.sh: $testerDirectory/p1DesignChecker.sh simulator.out_directory"
  exit
fi

if [[ $1 =~ P1testing ]]; then # Use from this directory is not allowed
  >&2 echo "You may not use p1testing as your own source directory!"
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

cityCount=`awk '/typedef|class/,/}/' city.h | egrep "latitude|longitude|state|name|population|airport" | wc -l`

if [ $cityCount -ne 6 ]; then
  echo "Fatal design error: latitude, longitude, state, name, population, or airport not found in City class or struct." >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

functionCount=`grep "{" city.h | wc -l`
if [ $functionCount -ne 1 ]; then
  echo 'Fatal design error: More than one "{" found in city.h, so implementation found.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

grep -v "^ *//" main.cpp vector.cpp vector.h | egrep  "(\.|\->)(latitude|longitude|state|name|population|airport)" > temp
if [[ -s temp ]]; then
  echo 'Fatal design error: latitude, longitude, state, name, population, or airport found outside city.*.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError)) 
fi

vectorCount=`awk '/typedef|class/,/}/' vector.h | egrep "cityArray|count| size" | wc -l`

if [ $vectorCount -ne 3 ]; then
  echo "Fatal design error: cityArray, size, or count not found in Vector class or struct." >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

functionCount=`grep "{" vector.h | wc -l`
if [ $functionCount -ne 1 ]; then
  echo 'Fatal design error: More than one "{" found invector.h, so implementation found.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

grep -v "^ *//" main.cpp city.cpp city.h | egrep  "(\.|\->)(cityArray|size|count)" > temp
if [[ -s temp ]]; then
  echo 'Fatal design error: cityArray, size, or count found outside vector.*.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError)) 
fi

grep -v "^ *//" city.h | grep " City"| grep -v class | egrep -v "City *[;\*]" > temp
if [[ -s temp ]]; then
  echo 'Fatal design error: City not passed as pointer in city.h.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi


grep -v "^ *//" vector.h | grep " Vector"| grep -v class | egrep -v "Vector *[;\*]" > temp
if [[ -s temp ]]; then
  echo 'Fatal design error: Vector not passed as pointer in vector.h.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi


grep "g++ " Makefile | grep -v " -ansi" > temp
if [[ -s temp ]]; then
  echo 'Fatal design error: Makefile with g++ without -ansi found.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi

grep "g++ " Makefile | grep -v " -Wall" > temp
if [[ -s temp ]]; then
  echo 'Fatal design error: Makefile with g++ without -Wall found.' >> designResults.txt
  echo "Zero for assignment." >> designResults.txt
  ((++designError))
fi


# None fatal design errors from here on, so one line per error

grep "#ifndef" city.h > temp
if [ ! -s temp ]; then
  echo 'Design error: #ifndef .. #endif missing from city.h.' >> designResults.txt
fi

grep "#ifndef" vector.h > temp 
if [ ! -s temp ]; then
  echo 'Design error: #ifndef .. #endif missing from vector.h.' >> designResults.txt
fi

grep "void.*initialize *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: initialize( missing from vector.cpp.' >> designResults.txt
fi

awk '/void.*initialize *\(/ , /^}/' vector.cpp | egrep "(malloc|new).*City" > temp
if [[ ! -s temp ]]; then
  echo 'Design error: malloc or new of City not found in initialize() of vector.cpp.' >> designResults.txt
fi

grep "void.*initialize *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: initialize( missing from city.cpp.' >> designResults.txt
fi

grep "void.*resize *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: resize( missing from vector.cpp.' >> designResults.txt
fi

awk '/void.*resize *\(/ , /^}/' vector.cpp | egrep "(malloc|new).*City" > temp
if [[ ! -s temp ]]; then
  echo 'Design error: malloc or new of City not found in resize() of vector.cpp.' >> designResults.txt
fi

awk '/void.*resize *\(/ , /^}/' vector.cpp | egrep "(free|delete).*cityArray" > temp
if [[ ! -s temp ]]; then
  echo 'Design error: free or delete of cityArray not found in resize() of vector.cpp.' >> designResults.txt
fi

grep "void.*readAirports *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: readAirports( missing from vector.cpp.' >> designResults.txt
fi

grep "void.*readAirport *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: readAirport( missing from city.cpp.' >> designResults.txt
fi

grep "bool.*isEqual *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: bool isEqual( missing from city.cpp.' >> designResults.txt
fi

grep "void.*copyLocation *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: copyLocation( missing from city.cpp.' >> designResults.txt
fi

grep "void.*deallocate *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: deallocate( missing from city.cpp.' >> designResults.txt
fi

freeCount=`awk '/void.*deallocate *\(/ , /^}/' city.cpp | egrep "(free|delete)" | wc -l`
if [ $freeCount -ne 2 ]; then
  echo 'Design error: name and/or state not freed in deallocate of city.cpp.' >> designResults.txt
fi

grep "void.*cleanCities *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: cleanCities( missing from vector.cpp.' >> designResults.txt
fi

grep "hasAirport *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: hasAirport( missing from city.cpp.' >> designResults.txt
fi

grep "findAirport *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: findAirport( missing from vector.cpp.' >> designResults.txt
fi

grep "void.*setAirport *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: setAirport( missing from city.cpp.' >> designResults.txt
fi

grep "void.*calcDistance *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: calcDistance( missing from vector.cpp.' >> designResults.txt
fi

grep "void.*calcDistance *(" city.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: calcDistance( missing from city.cpp.' >> designResults.txt
fi

grep "void.*deallocate *(" vector.cpp > temp
if [ ! -s temp ]; then
  echo 'Design error: deallocate( missing from vector.cpp.' >> designResults.txt
fi

awk '/void.*deallocate *\(/ , /^}/' vector.cpp | egrep "(free|delete).*cityArray" > temp
if [ ! -s temp ]; then
  echo 'Design error: cityArray not freed or deleted in deallocate of vector.cpp.' >> designResults.txt
fi

 awk '/void.*deallocate *\(/ , /^}/' vector.cpp | grep "deallocate.*(" | egrep "cityArray\[" > temp
if [ ! -s temp ]; then
  echo 'Design error: cityArray elements not passed to deallocate() of city.cpp in deallocate of vector.cpp.' >> designResults.txt
fi


echo $designError  # Only standard out

