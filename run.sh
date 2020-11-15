#!/bin/bash

./init &
./gene &
./conv ../model.pth &
./disp &
