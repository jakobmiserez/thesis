#!/bin/bash 

OMNETPPINI=$1
CONFIG=$2

echo "$1"

make MODE=release 


./src/thesis -u Qtenv -c $CONFIG -n "src/:../inet/src/:simulations/" --sim-time-limit "300s" $OMNETPPINI 