#!/bin/bash

#
# A script to check which interfaces are currently running.
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++
LOG_DIRECTORY_PYTHON=logs/python
LOG_DIRECTORY_CPP=logs/c++


for cpp_interface in $INTERFACE_DIRECTORY_CPP/*/; do
  INAME=$(basename "$cpp_interface")
  INTERFACE_PID=$(ps aux | grep c++/$INAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 1)
  if [ "${INTERFACE_PID}" != "" ]; then
    echo ""
    echo "Interface cpp/$INAME running!"
  fi
done

# All python interfaces.
for python_interface in $INTERFACE_DIRECTORY_PYTHON/*/; do
  INAME=$(basename "$python_interface")
  INTERFACE_PID=$(ps aux | grep python/$INAME | grep -v "grep" | grep -v ".log" | awk '{print $2}' | head -n 1)
  if [ "${INTERFACE_PID}" != "" ]; then
    echo ""
    echo "Interface python/$INAME running!"
  fi
done
echo ""
