#!/bin/bash

#
# Launches all interfaces without dockerization.
# ./local_run.sh <INTERFACE_NAME|all>
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++
LOCAL_INTERFACES_LIST=local_interfaces.conf

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
  while IFS= read -r line; do
    IPATH="${line// /}"
    IFS='/' read -r ILANGUAGE INAME <<< "$IPATH"
    if [[ "${IPATH}" != \#* ]]; then
      if [[ "$ILANGUAGE" == "c++" ]]; then
        ./deploy/scripts/local_build_c++.sh $INAME
      fi
    fi
  done < "$LOCAL_INTERFACES_LIST"

else
  if [ -d "$INTERFACE_DIRECTORY_CPP/$INTERFACE_NAME" ]; then
    ./deploy/scripts/local_build_c++.sh $INTERFACE_NAME
    exit
  fi
fi
