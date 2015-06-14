#!/bin/sh


OPTS=`getopt -o i:o: -- "$@"`
if [ $? != 0 ]
then
    exit 1
fi

eval set -- "$OPTS"

SRC_DIR=""
DST_DIR=""

while true ; do
    case "$1" in
        -i) SRC_DIR=$2; shift 2;;
        -o) DST_DIR=$2; shift 2;;
        
        #--target) TARGET=$2; shift 2;;
        --) shift; break;;
    esac
done

if [ -z "${SRC_DIR}" ]
then
	echo "Error: missing source directory"
	echo "Usage:"
	echo "$0 -i <src_dir> -o <dst_dir>"
	exit;
fi

if [ -z "${DST_DIR}" ]
then
	echo "Error: missing destination directory"
	echo "Usage:"
	echo "$0 -i <src_dir> -o <dst_dir>"
	exit;
fi

ls $SRC_DIR | sed 's/\_run[0-9]*//g' | sort | uniq | while read BASE
do
	`dirname $0`/collect_stats.sh ${SRC_DIR}/${BASE}_run*/ > ${DST_DIR}/${BASE}.csv
	echo "Created: ${BASE}.csv"
done


