#!/bin/sh

BIN_DIR=../bin

${BIN_DIR}/make_avg_csv.py ../p5/constant_volume/avrami_*d_instant.csv		> cv_avrami_instant.csv
${BIN_DIR}/make_avg_csv.py ../p5/constant_volume/avrami_*d_sporadic.csv 	> cv_avrami_sporadic.csv

${BIN_DIR}/make_avg_csv.py ../p5/constant_volume/avrami_*d_instant_parabolic.csv	> cv_avrami_instant_parabolic.csv
${BIN_DIR}/make_avg_csv.py ../p5/constant_volume/avrami_*d_sporadic_parabolic.csv 	> cv_avrami_sporadic_parabolic.csv


${BIN_DIR}/make_avg_csv.py ../p5/constant_side/avrami_*d_instant.csv		> cs_avrami_instant.csv
${BIN_DIR}/make_avg_csv.py ../p5/constant_side/avrami_*d_sporadic.csv 		> cs_avrami_sporadic.csv

#${BIN_DIR}/make_avg_csv.py ../p5/constant_side/avrami_*d_instant_parabolic.csv	> cs_avrami_instant_parabolic.csv
#${BIN_DIR}/make_avg_csv.py ../p5/constant_side/avrami_*d_sporadic_parabolic.csv 	> cs_avrami_sporadic_parabolic.csv


ls *.ct2 | while read CT2
do
	ctioga2 -f ${CT2}
done
