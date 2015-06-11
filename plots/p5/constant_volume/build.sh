#!/bin/sh

ls *.csv | while read CSV_FILE
do
	echo "Building: $CSV_FILE"
	N_FILE=`basename $CSV_FILE .csv`.sum_n
	K_FILE=`basename $CSV_FILE .csv`.sum_k
	
	
	D=`echo $CSV_FILE | grep '[0-9]d' -o | tr '[:lower:]' '[:upper:]'`
	
	TITLE=`basename $CSV_FILE .csv | grep '[0-9]d.*$' -o | tr '_' ' '`

	python ../make_hist_csv.py -i $CSV_FILE -o $N_FILE -c 6 -b 5
	python ../make_hist_csv.py -i $CSV_FILE -o $K_FILE -c 7 -b 5
	
	N_THEO=`csvtool col 8 $CSV_FILE | uniq | tail -n 1`
	K_THEO=`csvtool col 9 $CSV_FILE | uniq | tail -n 1`
	
	ctioga2 --csv --load $N_FILE   --set theo_value $N_THEO -f ../hist_n.ct2 --name `basename $CSV_FILE .csv`_n --title  "$TITLE" 
	ctioga2 --csv --load $K_FILE   --set theo_value $K_THEO -f ../hist_k.ct2 --name `basename $CSV_FILE .csv`_k --title  "$TITLE"
	ctioga2 --csv --load $CSV_FILE -f ../graph_nk.ct2 --name `basename $CSV_FILE .csv`_nk --title  "$TITLE"
	
done;
