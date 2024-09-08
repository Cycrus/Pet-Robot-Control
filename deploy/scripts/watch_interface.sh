#!/bin/bash

#
# A script to watch a currently running interface.
#

INTERFACE_NAME=$1
LOG_DIRECTORY_PYTHON=logs/python
LOG_DIRECTORY_CPP=logs/c++


if [[ "${INTERFACE_NAME}" == "all" ]]; then
  echo ""
  echo "[Warning] Please select an interface to watch."
  exit
fi

# Check c++ interfaces
INTERFACE_PID=$(ps aux | grep c++/$INTERFACE_NAME | grep -v "grep" | awk '{print $2}' | head -n 1)
if [ "${INTERFACE_PID}" != "" ]; then
  watch -n 1 "cat $LOG_DIRECTORY_CPP/$INTERFACE_NAME.log"
  exit
fi

INTERFACE_PID=$(ps aux | grep python/$INTERFACE_NAME | grep -v "grep" | awk '{print $2}' | head -n 1)
if [ "${INTERFACE_PID}" != "" ]; then
  watch -n 1 "cat $LOG_DIRECTORY_PYTHON/$INTERFACE_NAME.log"
  exit
fi

echo ""
echo "[Warning] Interface $INTERFACE_NAME currently not running."
