#! /bin/sh

#  cpdirs.sh

# Tony Xiao

if [[ $# -lt 3 ]] || [[ $# -gt 3 ]]
then
    echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
    exit
fi


if [[ ! -d $1 ]] || [[ ! -d $2 ]]
then
	echo "usage: cpdirs.sh source_directory1 source_directory2 dest_directory"
	exit
fi


if [[ ! -d $3 ]]
then
	mkdir $3
fi

# find $1 -type f -exec cp -p {} $3 \; &> /dev/null
cp -p $1/* $3 &> /dev/null
cp -p -u $2/* $3 &> /dev/null
