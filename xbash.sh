#!/bin/sh

./build/setbuf
./build/camProducer &
gnome-terminal -- /bin/bash -c './build/converter' 
./build/cleanup &
