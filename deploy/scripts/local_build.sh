#!/bin/bash

#
# Launches all interfaces without dockerization.
# ./local_run.sh <INTERFACE_NAME|all>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++

if [ "${INTERFACE_NAME}" == "" ]; then
  echo "[Error] Please provide an interface name to build or simply build \"all\"."
  echo "./local_build.sh <INTERFACE_NAME|all>"
  exit
fi

echo ""
echo "################################################"
echo "Building $INTERFACE_NAME undockerized."
echo "################################################"
echo ""

if [ "${INTERFACE_NAME}" == "all" ]; then
  for cpp_interface in $INTERFACE_DIRECTORY_CPP/*/; do
    ./deploy/scripts/local_build_c++.sh $(basename "$cpp_interface")
  done

else
  if [ -d "$INTERFACE_DIRECTORY_CPP/$INTERFACE_NAME" ]; then
    ./deploy/scripts/local_build_c++.sh $INTERFACE_NAME
    exit
  fi
fi