#!/bin/bash

./init

./gene &
GENE_PID=$!
taskset -cp 0 $GENE_PID

./conv config.txt &
CONV_PID=$!
taskset -cp 1 $CONV_PID

./disp &
DISP_PID=$!
taskset -cp 2 $DISP_PID
