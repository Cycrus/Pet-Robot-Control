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
  STOPPED_SOMETHING=0
  # All C++ interfaces.
  for cpp_interface in $INTERFACE_DIRECTORY_CPP/*/; do
    INAME=$(basename "$cpp_interface")
    INTERFACE_PID=$(ps aux | grep c++/$INAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 1)
    STATUS=$(kill $INTERFACE_PID 2>&1)
    if [ "${STATUS}" == "" ]; then
      echo ""
      echo "Successfully stopped <$INAME>."
      echo ""
      STOPPED_SOMETHING=1
    fi
  done
  
  # All python interfaces.
  for python_interface in $INTERFACE_DIRECTORY_PYTHON/*/; do
    INAME=$(basename "$python_interface")
    INTERFACE_PID=$(ps aux | grep python/$INAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 2)
    STATUS=$(kill $INTERFACE_PID 2>&1)
    if [ "${STATUS}" == "" ]; then
      echo ""
      echo "Successfully stopped <$INAME>."
      echo ""
      STOPPED_SOMETHING=1
    fi
  done

  if [ "$STOPPED_SOMETHING" == 0 ]; then
    echo ""
    echo "[Warning] No interfaces running. Nothing to stop."
    echo ""
  fi

else
  # Stop single process if its name is provided.
  # One python interface.
  if [ -d "$INTERFACE_DIRECTORY_PYTHON/$INTERFACE_NAME" ]; then
    INTERFACE_PID=$(ps aux | grep python/$INTERFACE_NAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 2)
    STATUS=$(kill $INTERFACE_PID 2>&1)
    echo ""
    if [ "${STATUS}" == "" ]; then
      echo "Successfully stopped <$INTERFACE_NAME>."
    else
      echo "[Warning] <$INTERFACE_NAME> not running. Could not stop."
    fi
    echo ""
    exit
  fi

  # One c++ interface.
  if [ -d "$INTERFACE_DIRECTORY_CPP/$INTERFACE_NAME" ]; then
    INTERFACE_PID=$(ps aux | grep c++/$INTERFACE_NAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 1)
    STATUS=$(kill $INTERFACE_PID 2>&1)
    echo ""
    if [ "${STATUS}" == "" ]; then
      echo "Successfully stopped <$INTERFACE_NAME>."
    else
      echo "[Warning] <$INTERFACE_NAME> not running. Could not stop."
    fi
    echo ""
    exit
  fi
fi