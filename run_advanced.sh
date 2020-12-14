#!/bin/bash

./init

taskset -c 1 ./gene &

taskset -c 1 ./conv config.txt &

taskset -c 1 ./disp &
