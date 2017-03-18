#! /bin/bash

testerDirectory="/home/ssdavis/40/p3/Testing"

if [ $# -ne 1 ]; then
  echo "usage p3tester.sh: $testerDirectory/p3tester.sh simulator.out_directory" 1>&2
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  echo "You may not use Testing as your own source directory!"  1>&2
  exit
fi

if [[ ! -e $1/simulator.out ]]; then # simulator not found
  echo "simulator.out not found in $1!"  1>&2
  exit
fi

cd $1
rm -f out*.txt citypopulations.csv airportLL.txt &> /dev/null

cp $testerDirectory/citypopulations.csv $testerDirectory/airportLL.txt .

fileNum=1
opScore=0
echo Operation testing:  1>&2

while [[ $fileNum -lt 12 ]]; do
  echo $fileNum  1>&2
  echo -n $fileNum: >> operationsResults.txt
  rm -f out$fileNum.txt  
  (simulator.out < $testerDirectory/input$fileNum.txt > out$fileNum.txt )&
  sleep 1
  pkill simulator.out &> /dev/null
  diff out$fileNum.txt $testerDirectory/out$fileNum.txt &> temp

  if [[ ( ! -e out$fileNum.txt) || ( -s temp ) ]]; then
    echo -e "\nDifferences on " input$fileNum.txt >> operationsResults.txt
    echo Yours: >> operationsResults.txt
    cat out$fileNum.txt  >> operationsResults.txt
    echo -e "\nSeans:" >> operationsResults.txt
    cat $testerDirectory/out$fileNum.txt >> operationsResults.txt
  else
    echo OK >> operationsResults.txt
    (( opScore += 1 ))
  fi

  fileNum=$((fileNum + 1))
done  # while less than 12


while [[ $fileNum -lt 17 ]]; do
  echo $fileNum  1>&2
  echo -n $fileNum: >> operationsResults.txt
  rm -f out$fileNum.txt
  (simulator.out < $testerDirectory/input$fileNum.txt > out$fileNum.txt )&
  sleep 1
  pkill simulator.out &> /dev/null
  diff out$fileNum.txt $testerDirectory/out$fileNum.txt &> temp

  if [[ ( ! -e out$fileNum.txt) || ( -s temp ) ]]; then
    echo -e "\nDifferences on " input$fileNum.txt >> operationsResults.txt
    echo Yours: >> operationsResults.txt
    cat out$fileNum.txt  >> operationsResults.txt
    echo -e "\nSeans:" >> operationsResults.txt
    cat $testerDirectory/out$fileNum.txt >> operationsResults.txt
  else
    echo OK >> operationsResults.txt
    (( opScore += 2 ))
  fi

  fileNum=$((fileNum + 1))
done  # while less than 17

while [[ $fileNum -lt 19 ]]; do
  echo $fileNum  1>&2
  echo -n $fileNum: >> operationsResults.txt
  rm -f out$fileNum.txt
  (simulator.out < $testerDirectory/input$fileNum.txt | sort > out$fileNum.txt )&
  sleep 1
  pkill simulator.out &> /dev/null
  diff out$fileNum.txt $testerDirectory/out$fileNum.txt &> temp

  if [[ ( ! -e out$fileNum.txt) || ( -s temp ) ]]; then
    echo -e "\nDifferences on " input$fileNum.txt >> operationsResults.txt
    echo Yours: >> operationsResults.txt
    cat out$fileNum.txt  >> operationsResults.txt
    echo -e "\nSeans:" >> operationsResults.txt
    cat $testerDirectory/out$fileNum.txt >> operationsResults.txt
  else
    echo OK >> operationsResults.txt
    (( opScore += 2 ))
  fi

  fileNum=$((fileNum + 1))
done  # while less than 19

echo $opScore   # this is the only line that goes to stdout

