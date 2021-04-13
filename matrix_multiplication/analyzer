#!/bin/bash

ANA="bin/analyzer.out"

# READ THE INPUT PARAMETERS
RANGE=$1
SIZE=$2
NUM=$3

ERROR_32="matrices/error/32/R${RANGE}S${SIZE}"
ERROR_POSIT="matrices/error/posit/R${RANGE}S${SIZE}"

$ANA matrices/result/32/R${RANGE}S${SIZE} $NUM > $ERROR_32
$ANA matrices/result/posit/R${RANGE}S${SIZE} $NUM > $ERROR_POSIT

