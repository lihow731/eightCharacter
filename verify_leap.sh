#!/bin/bash

for y in `seq 1900 2000`
do
	echo $y `./time $y 3 22 | grep "is leap year"`
done
