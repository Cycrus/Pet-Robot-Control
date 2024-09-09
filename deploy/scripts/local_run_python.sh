#!/bin/bash

#
# Launches a single python interface without dockerization.
# ./local_run_python.sh <INTERFACE_NAME> <detached/attached>
#

INTERFACE_NAME=$1
MODE=$2
INTERFACE_DIRECTORY=RaspberryPi/interfaces/python/$INTERFACE_NAME

if [ "${INTERFACE_NAME}" == "" ] || { [ "${MODE}" != "attached" ] && [ "${MODE}" != "detached" ]; }; then
  echo "[Error] Please provide a python interface name to launch."
  echo "./local_run_python.sh <INTERFACE_NAME> <attached|detached>"
  exit
fi

if [ ! -d "$INTERFACE_DIRECTORY" ]; then
  echo "[Error] No python interface with name $INTERFACE_NAME found."
  exit
fi

# Check if process already running.
INTERFACE_PID=$(ps aux | grep python/$INTERFACE_NAME | grep -v "grep" | awk '{print $2}' | head -n 1)
if [ "${INTERFACE_PID}" == "" ]; then
  # Run if no.
  echo ""
  echo "Launching python module $INTERFACE_NAME undockerized in $MODE mode."
  echo ""
  if [ "$MODE" = "detached" ]; then
    nohup sudo ./RaspberryPi/interfaces/python/$INTERFACE_NAME/run.sh $PWD/RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py $PWD/RaspberryPi/lib/python > $PWD/logs/python/$INTERFACE_NAME.log 2>&1 &
  else
    sudo ./RaspberryPi/interfaces/python/$INTERFACE_NAME/run.sh $PWD/RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py $PWD/RaspberryPi/lib/python
  fi
else
  echo ""
  echo "[Warning] <$INTERFACE_NAME> already running. Not launching again."
  echo ""
fi
