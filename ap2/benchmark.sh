#!/bin/sh

#build
mkdir -p bin
cd bin
cmake ..
make

#run
echo "\n\n ./pi 8 100"
./pi 8 100

echo "\n\n ./mm 500 8 100"
./mm 500 8 100

echo "\n\n ./mm 750 8 100"
./mm 750 8 100

echo "\n\n ./mm 1000 8 100"
./mm 1000 8 100

echo "\n\n ./mm 2000 8 100"
./mm 2000 8 100