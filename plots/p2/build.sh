#!/bin/sh
ls *.ct2 | while read CT2
do
	ctioga2 -f ${CT2}
done
