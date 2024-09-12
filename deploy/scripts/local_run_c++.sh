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

# This step is required to not lose the name identity of the process after launching.
cd $INTERFACE_DIRECTORY/build
cd ../../../../..

# Check if process already running.
INTERFACE_PID=$(ps aux | grep c++/$INTERFACE_NAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 1)
if [ "${INTERFACE_PID}" == "" ]; then
  # Run if no.
  echo ""
  echo "Launching c++ module $INTERFACE_NAME undockerized in $MODE mode."
  echo ""
  if [ "$MODE" = "detached" ]; then
    nohup sudo ./$INTERFACE_DIRECTORY/build/main > $PWD/logs/c++/$INTERFACE_NAME.log 2>&1 &
  else
    sudo ./$INTERFACE_DIRECTORY/build/main
  fi
else
  echo ""
  echo "[Warning] <$INTERFACE_NAME> already running. Not launching again."
  echo ""
fi
