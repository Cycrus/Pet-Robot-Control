#!/bin/bash

#
# Launches all interfaces without dockerization.
# ./local_run.sh <INTERFACE_NAME|all>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++

if [ "${INTERFACE_NAME}" == "" ]; then
  echo "[Error] Please provide an interface name to launch or simply launch \"all\"."
  echo "./local_run.sh <INTERFACE_NAME|all>"
  exit
fi

echo ""
echo "################################################"
echo "Launching $INTERFACE_NAME undockerized."
echo "################################################"
echo ""

# Starting up Mosquitto MQTT broker
docker compose up mosquitto -d

if [ "${INTERFACE_NAME}" == "all" ]; then
  # If "all" is provided as the interface name, then all interfaces are
  # launched in detached mode.
  for cpp_interface in $INTERFACE_DIRECTORY_CPP/*/; do
    ./deploy/scripts/local_run_c++.sh $(basename "$cpp_interface") detached
  done

  for python_interface in $INTERFACE_DIRECTORY_PYTHON/*/; do
    ./deploy/scripts/local_run_python.sh $(basename "$python_interface") detached
  done

else
  # If a certain interface name is provided, it launches in attached mode.
  # This is a debug utility.
  if [ -d "$INTERFACE_DIRECTORY_PYTHON/$INTERFACE_NAME" ]; then
    ./deploy/scripts/local_run_python.sh $INTERFACE_NAME attached
     exit
  fi
  if [ -d "$INTERFACE_DIRECTORY_CPP/$INTERFACE_NAME" ]; then
    ./deploy/scripts/local_run_c++.sh $INTERFACE_NAME attached
    exit
  fi
fi