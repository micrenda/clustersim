#!/bin/sh


OPTS=`getopt -o t -l target: -- "$@"`
if [ $? != 0 ]
then
    exit 1
fi

eval set -- "$OPTS"

TARGET=""

while true ; do
    case "$1" in
        #-t) TARGET=$2; shift;;
        
        #--target) TARGET=$2; shift 2;;
        --) shift; break;;
    esac
done

if [ $# -lt 1 ]
then
	echo "Usage:"
	echo "$0 <basename_1> <basename_2> <basename_3>"
	exit;
fi

for arg
do

    ./collect_stats.sh ${arg}_run*/ > `basename ${arg}`.csv
    echo "Created: `basename ${arg}`.csv"
done

