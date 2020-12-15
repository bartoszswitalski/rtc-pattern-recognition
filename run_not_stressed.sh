#!/bin/bash

rm ../visuals/times.log

./init

(sleep 120 && ./dest && echo 'dest uruchomiony')&
(sleep 120 && python3 ../visuals/visuals.py ../visuals/times.log)&

./gene &
GENE_PID=$!

./conv config.txt &
GENE_PID1=$!

./disp &
GENE_PID2=$!

chrt -p $GENE_PID
chrt -p $GENE_PID1
chrt -p $GENE_PID2

