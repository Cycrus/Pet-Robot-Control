#!/bin/bash

#
# Builds and launches a single c++ interface without dockerization.
# ./local_run_c++.sh <INTERFACE_NAME> <detached/attached>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY=RaspberryPi/interfaces/c++/$INTERFACE_NAME

if [ "${INTERFACE_NAME}" == "" ]; then
    echo "[Error] Please provide a c++ interface name to build."
    echo "./local_build_c++.sh <INTERFACE_NAME>"
    exit
fi

if [ ! -d "$INTERFACE_DIRECTORY" ]; then
    echo "[Error] No c++ interface with name $INTERFACE_NAME found."
    exit
fi

echo ""
echo "Building c++ module $INTERFACE_NAME undockerized."
echo ""

mkdir $INTERFACE_DIRECTORY/build
cd $INTERFACE_DIRECTORY/build
cmake ..
make
