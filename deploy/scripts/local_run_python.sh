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

echo ""
echo "Launching python module $INTERFACE_NAME undockerized in $MODE mode."
echo ""

if [ "$MODE" = "detached" ]; then
  nohup sudo ./RaspberryPi/interfaces/python/$INTERFACE_NAME/run.sh $PWD/RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py $PWD/RaspberryPi/lib/python &>/dev/null & 
  #nohup sudo python3 RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py &>/dev/null &
else
  sudo ./RaspberryPi/interfaces/python/$INTERFACE_NAME/run.sh $PWD/RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py $PWD/RaspberryPi/lib/python
  #sudo python3 RaspberryPi/interfaces/python/$INTERFACE_NAME/main.py
fi