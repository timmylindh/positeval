#!/bin/bash

F32="bin/f32.out"
F64="bin/f64.out"
P32="bin/p32.out"

# READ THE INPUT PARAMETERS
RANGE=$1
SIZE=$2
NUM=$(($3 - 1))

for i in $(seq 1 $NUM); do
    $F32 matrices/in/M${i}R${RANGE}S${SIZE} matrices/in/M$(($i + 1))R${RANGE}S${SIZE} matrices/out/32/M${i}R${RANGE}S${SIZE}
    $F64 matrices/in/M${i}R${RANGE}S${SIZE} matrices/in/M$(($i + 1))R${RANGE}S${SIZE} matrices/out/64/M${i}R${RANGE}S${SIZE}
    $P32 matrices/in/M${i}R${RANGE}S${SIZE} matrices/in/M$(($i + 1))R${RANGE}S${SIZE} matrices/out/posit/M${i}R${RANGE}S${SIZE}
done
