#!/bin/bash

GEN="bin/gen.out"

# READ THE INPUT PARAMETERS
RANGE=$1
SIZE=$2
NUM=$3

for i in $(seq 1 $NUM); do
    $GEN $RANGE $SIZE M${i}R${RANGE}S${SIZE}
done
