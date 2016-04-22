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
	echo "$0 <dir1> <dir2> <dir3> ..."
	exit;
fi

echo "# basename, dimensions, volume_space, volume_fill, clusters, fit_n, fit_k, theo_n, theo_k"

for arg
do
    find $arg -name stats.csv | while read FILE
    do
		echo `grep -v "^#" $FILE`
    done
done
