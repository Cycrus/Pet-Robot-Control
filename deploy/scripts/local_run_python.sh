#!/bin/bash

#
# Launches a single python interface without dockerization.
# ./local_run_python.sh <INTERFACE_NAME>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY=RaspberryPi/interfaces/python/$INTERFACE_NAME

if [ "${INTERFACE_NAME}" == "" ]; then
    echo "[Error] Please provide a python interface name to launch."
    exit
fi

if [ ! -d "$INTERFACE_DIRECTORY" ]; then
    echo "[Error] No python interface with name $INTERFACE_NAME found."
    exit
fi

python3 RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py
