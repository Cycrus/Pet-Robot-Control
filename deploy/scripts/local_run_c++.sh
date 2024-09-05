#!/bin/bash

#
# Builds and launches a single c++ interface without dockerization.
# ./local_run_c++.sh <INTERFACE_NAME> <detached/attached>
#

INTERFACE_NAME=$1
MODE=$2
INTERFACE_DIRECTORY=RaspberryPi/interfaces/c++/$INTERFACE_NAME

if [ "${INTERFACE_NAME}" == "" ] || { [ "${MODE}" != "attached" ] && [ "${MODE}" != "detached" ]; }; then
    echo "[Error] Please provide a c++ interface name to launch."
    echo "./local_run_c++.sh <INTERFACE_NAME> <attached|detached>"
    exit
fi

if [ ! -d "$INTERFACE_DIRECTORY" ]; then
    echo "[Error] No c++ interface with name $INTERFACE_NAME found."
    exit
fi

echo ""
echo "Launching c++ module $INTERFACE_NAME undockerized in $MODE mode."
echo ""

# This step is required to not lose the name identity of the process after launching.
cd $INTERFACE_DIRECTORY/build
cd ../..
if [ "$MODE" = "detached" ]; then
  nohup sudo ./$INTERFACE_NAME/build/main &>/dev/null &
else
  sudo ./$INTERFACE_NAME/build/main
fi
