#!/bin/bash

#
# Stops one or all interfaces without dockerization.
# ./local_stop.sh <INTERFACE_NAME|all>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++

if [ "${INTERFACE_NAME}" == "" ]; then
  echo "[Error] Please provide an interface name to launch or simply launch \"all\"."
  echo "./local_run.sh <INTERFACE_NAME|all>"
  exit
fi

if [ "${INTERFACE_NAME}" == "all" ]; then
  # Stop all interfaces if "all" is provided.
  for cpp_interface in $INTERFACE_DIRECTORY_CPP/*/; do
    INTERFACE_PID=$(ps aux | grep $(basename "$cpp_interface") | grep -v "grep" | awk '{print $2}' | head -n 1)
    kill $INTERFACE_PID
  done
  
  for python_interface in $INTERFACE_DIRECTORY_PYTHON/*/; do
    INTERFACE_PID=$(ps aux | grep $(basename "$python_interface") | grep -v "grep" | awk '{print $2}' | head -n 1)
    kill $INTERFACE_PID
  done

else
  # Stop single process if its name is provided.
  if [ -d "$INTERFACE_DIRECTORY_PYTHON/$INTERFACE_NAME" ]; then
    INTERFACE_PID=$(ps aux | grep $INTERFACE_NAME | grep -v "grep" | awk '{print $2}' | head -n 1)
    kill $INTERFACE_PID
    exit
  fi
  if [ -d "$INTERFACE_DIRECTORY_CPP/$INTERFACE_NAME" ]; then
    INTERFACE_PID=$(ps aux | grep $INTERFACE_NAME | grep -v "grep" | awk '{print $2}' | head -n 1)
    kill $INTERFACE_PID
    exit
  fi
fi