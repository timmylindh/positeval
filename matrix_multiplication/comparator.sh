#!/bin/bash

COMP="bin/comp.out"

# READ THE INPUT PARAMETERS
RANGE=$1
SIZE=$2
NUM=$(($3 - 1))

RESULT_32="matrices/result/32/R${RANGE}S${SIZE}"
RESULT_POSIT="matrices/result/posit/R${RANGE}S${SIZE}"

for i in $(seq 1 $NUM); do
    $COMP matrices/out/32/M${i}R${RANGE}S${SIZE} matrices/out/64/M${i}R${RANGE}S${SIZE} >> $RESULT_32
    $COMP matrices/out/posit/M${i}R${RANGE}S${SIZE} matrices/out/64/M${i}R${RANGE}S${SIZE} >> $RESULT_POSIT
done

