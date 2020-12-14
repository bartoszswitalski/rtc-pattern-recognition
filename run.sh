#!/bin/bash

rm ../visuals/times.log
rm ../visuals/graph.png

./init

(sleep 60 && ./dest && echo 'ok')&
(sleep 60 && python3 ../visuals/visuals.py ../visuals/times.log)&

./gene &
GENE_PID=$!

./conv config.txt &
GENE_PID2=$!

./disp &
GENE_PID3=$!
(stress-ng --cpu 128 --vm 128 --timer 128 --timeout 60s) &

#cpulimit -p $GENE_PID -l 1 
#cpulimit -p $GENE_PID2 -l 1 
#cpulimit -p $GENE_PID3 -l 1 
