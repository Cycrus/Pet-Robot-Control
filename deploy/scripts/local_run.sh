#!/bin/bash

#
# Launches all interfaces without dockerization.
# ./local_run.sh <INTERFACE_NAME|all>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++
LOCAL_INTERFACES_LIST=local_interfaces.conf

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

mkdir -p logs/python
mkdir -p logs/c++

# Starting up Mosquitto MQTT broker
docker compose up mosquitto -d

if [ "${INTERFACE_NAME}" == "all" ]; then
  # If "all" is provided as the interface name, then all interfaces are
  # launched in detached mode.
  # Launch all uncommented interfaces in the file local_interfaces.conf
  while IFS= read -r line; do
    IPATH="${line// /}"
    IFS='/' read -r ILANGUAGE INAME <<< "$IPATH"
    if [[ "${IPATH}" != \#* ]]; then
      if [[ "$ILANGUAGE" == "c++" ]]; then
        ./deploy/scripts/local_run_c++.sh $INAME detached
      fi

      if [[ "$ILANGUAGE" == "python" ]]; then
        ./deploy/scripts/local_run_python.sh $INAME detached
      fi
    fi
  done < "$LOCAL_INTERFACES_LIST"

else
  # If a certain interface name is provided, it launches in attached mode.
  # This is a debug utility.
  # One python interface.
  if [ -d "$INTERFACE_DIRECTORY_PYTHON/$INTERFACE_NAME" ]; then
    ./deploy/scripts/local_run_python.sh $INTERFACE_NAME attached
     exit
  fi

  # One c++ interface.
  if [ -d "$INTERFACE_DIRECTORY_CPP/$INTERFACE_NAME" ]; then
    ./deploy/scripts/local_run_c++.sh $INTERFACE_NAME attached
    exit
  fi
fi