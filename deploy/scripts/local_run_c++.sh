#!/bin/bash

#
# Builds and launches a single c++ interface without dockerization.
# ./local_run_c++.sh <INTERFACE_NAME>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY=RaspberryPi/interfaces/c++/$INTERFACE_NAME

if [ "${INTERFACE_NAME}" == "" ]; then
    echo "[Error] Please provide a c++ interface name to launch."
    exit
fi

if [ ! -d "$INTERFACE_DIRECTORY" ]; then
    echo "[Error] No c++ interface with name $INTERFACE_NAME found."
    exit
fi

mkdir $INTERFACE_DIRECTORY/build
rm $INTERFACE_DIRECTORY/build/*
echo "$PWD"
#cmake ..
#make

#./machine
