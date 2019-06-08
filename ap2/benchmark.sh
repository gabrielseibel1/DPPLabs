#!/bin/sh

#build
mkdir -p bin
cd bin
cmake ..
make

#run
echo "\n\nCPU info:\n"
sudo lshw -class cpu

echo "\n\n./pi 8 10"
./pi 8 10

echo "\n\n./mm 500 8 10"
./mm 500 8 10

echo "\n\n./mm 750 8 10"
./mm 750 8 10

echo "\n\n./mm 1000 8 10"
./mm 1000 8 10

echo "\n\n./mm 2000 8 10"
./mm 2000 8 10