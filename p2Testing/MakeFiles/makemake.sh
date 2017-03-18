#! /bin/bash

# Tony Xiao
# Create on 4/15/2015

> Makefile

if [[ $# -lt 1 ]]
then
	echo -e "Executable name required.\nusage: makemake.sh executable_name";
	exit
elif [[ -z "$1" ]]
then
	echo -e "Executable name required.\nusage: makemake.sh executable_name";
	exit
else 
	str1=$1
	shift
	if [[ -n "$@" ]]
	then
		str2=$@" "
	fi
	#echo "2"
	echo -e "$str1 : $(ls|awk ' /.cpp/ {printf $str1" "}'| 
		 sed s/cpp/o/g) \n\tg++ -ansi -Wall -g -o $str1 $str2$(ls|
		 awk ' /.cpp/ {printf $str1" "}'|sed s/cpp/o/g) \n">>Makefile
	#echo "3"
	for filename in *.cpp; do
		#echo "fix : bug "
		Ofile=`echo $filename|cut -f1 -d'.'`
		headerFile=$(cat $filename|awk ' /#include "/ {printf $2" "}'|sed s/'"'//g)
		echo -e "$Ofile.o : $filename $headerFile">>Makefile
		echo -e "\tg++ -ansi -Wall -g -c $str2$filename\n">>Makefile	

	done
		# echo -e "clean : \n\trm -f $str1 $(ls|awk ' /.cpp/ {printf $str1" "}'|sed s/cpp/o/g)">>Makefile
		echo -e "clean : ">>Makefile
		echo -e "\trm -f $str1 $(ls|awk ' /.cpp/ {printf $str1" "}'|sed s/cpp/o/g)">>Makefile
fi
