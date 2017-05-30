#!/bin/bash
EXT=csv
# first make the directories 
mkdir -p full/csv
mkdir -p full/excel

mkdir -p dialer 

# cycle through all .csv files and save them in respective folders 
for i in *.${EXT}; do
 	cp $i full/csv
 	./a $i > dialer/"dialer-$i"
done 