#!/bin/sh
#unused since we have cmake :)
gcc -fopenmp src/pi.c -o bin/pi
gcc -fopenmp src/mm.c -o bin/mm
