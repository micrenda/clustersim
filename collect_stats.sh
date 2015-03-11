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

echo "#time,new_clusters_asked,new_clusters_created,clusters_total,volume_grow,volume_total,volume_totale_perc"

for arg
do
    find $arg -name stats.csv | while read FILE
    do
		echo `grep -v "^#" $FILE`
    done
done
