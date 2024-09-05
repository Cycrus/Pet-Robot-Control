#!/bin/bash

#
# Uploads an Arduino sketch onto a device.
#

SKETCH_PATH=$1
BOARD=$2
PORT=$3


if [ "${SKETCH_PATH}" == "" ] || [ "${BOARD}" == "" ] || [ "${PORT}" == "" ]; then
    echo "[Error] Please provide sketch path, board type and arduino serial port path."
    exit
fi

echo ""
echo "################################################"
echo "Deploying arduino file $SKETCH_PATH"
echo "################################################"
echo ""

arduino-cli compile -v -b $BOARD -p $PORT -u $SKETCH_PATH