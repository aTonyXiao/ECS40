#!  /bin/bash

testerDirectory="/home/ssdavis/40/p3/P1testing"
constError=0

if [ $# -ne 1 ]; then
  >&2 echo "usage p3ConstChecker.sh: $testerDirectory/p3DesignChecker.sh simulator.out_directory"
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  >&2 echo "You may not use P1testing as your own source directory!"
  exit
fi

cd $1
rm -f constResults.txt &> /dev/null

grep -v "^ *//" city.h | grep "calcDistance.*const .*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: calcDistance() of city.h must have two consts.' >> constResults.txt
  ((++constError)) 
fi

grep -v "^ *//" city.h | grep "copyLocation.*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: copyLocation() of city.h must have a const.' >> constResults.txt
  ((++constError)) 
fi

grep -v "^ *//" city.h | grep "isEqual.*const .*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: isEqual() of city.h muat have two consts.' >> constResults.txt
  ((++constError)) 
fi

grep -v "^ *//" city.h | grep "setAirport.*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: setAirport() of city.h must have a const.' >> constResults.txt
  ((++constError)) 
fi

grep -v "^ *//" vector.h | grep "calcDistance.*const"  > temp
if [[ ! -s temp ]]; then
  echo 'Const error: calcDistance() in vector.h must have a const.' >> constResults.txt
  ((++constError)) 
fi

grep -v "^ *//" vector.h | grep "findAirport.*const.*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: findAirport() in vector.h must have two consts.' >> constResults.txt
  ((++constError)) 
fi

grep -v "^ *//" vector.h | grep "calcAirportTraffic.*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: calcAirportTraffic() in vector.h must have at least one const.' >> constResults.txt
  ((++constError))
fi

grep -v "^ *//" city.h | grep "operator *=.*const" > temp
if [[ ! -s temp ]]; then
  echo 'Const error: operator= of city.h must have a const.' >> constResults.txt
  ((++constError))
fi

echo $constError
