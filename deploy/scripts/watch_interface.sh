#!/bin/bash

#
# A script to watch a currently running interface.
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++
LOG_DIRECTORY_PYTHON=logs/python
LOG_DIRECTORY_CPP=logs/c++


# If "all" is passed, it checks for the existence of any process.
if [[ "${INTERFACE_NAME}" == "all" ]]; then
  for cpp_interface in $INTERFACE_DIRECTORY_CPP/*/; do
    INAME=$(basename "$cpp_interface")
    INTERFACE_PID=$(ps aux | grep c++/$INAME | grep -v "grep" | awk '{print $2}' | head -n 1)
    if [ "${INTERFACE_PID}" != "" ]; then
      echo ""
      echo "Interface cpp/$INAME running!"
    fi
  done
  
  # All python interfaces.
  for python_interface in $INTERFACE_DIRECTORY_PYTHON/*/; do
    INAME=$(basename "$python_interface")
    INTERFACE_PID=$(ps aux | grep python/$INAME | grep -v "grep" | awk '{print $2}' | head -n 1)
    if [ "${INTERFACE_PID}" != "" ]; then
      echo ""
      echo "Interface python/$INAME running!"
    fi
  done
  exit
fi

# If a specific interface is passed, it logs its stdout and stderr on the console.
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
