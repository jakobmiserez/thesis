#!/bin/bash 

OMNETPPINI=$1
CONFIG=$2
SIMULATIONTIME=$3

echo "$PWD/sim.out"
echo ".ini file is "$OMNETPPINI

make MODE=release 


./src/thesis -u Cmdenv -c $CONFIG -n "src/:../inet/src/:simulations/" --sim-time-limit "$SIMULATIONTIME" $OMNETPPINI
