#!/bin/bash

#
# Launches all interfaces without dockerization.
# ./local_run.sh <INTERFACE_NAME|all>
#

INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++
LOCAL_INTERFACES_LIST=autorun_interfaces.conf

mkdir -p logs/python
mkdir -p logs/c++


# Starting up Mosquitto MQTT broker
docker compose up mosquitto -d

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