#! /bin/sh

#  grepdir.sh
# Tony Xiao

if [[ $# -lt 2 ]]
then
	# echo "0"
    echo "usage: grepdir.sh directory pattern [-grep option]*"
    exit
fi

if [[ ! -d $1 ]]
then
	# echo "1"
    echo "usage: grepdir.sh directory pattern [-grep option]*"
    exit
fi

directoryname=$1
pattern=$2

shift
shift

if [[ $# -gt 0 ]]
then
    for i in $@
    do
        if [[ ${i:0:1} != "-" ]]
        then
        	# echo "2"
            echo "usage: grepdir.sh directory pattern [-grep option]*"
            exit
        fi
    done
    find $directoryname -exec grep $pattern $@ {} \;
else
    find $directoryname -exec grep $pattern {} \;
fi
