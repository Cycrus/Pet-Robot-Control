#!/bin/bash

#
# A script to watch a currently running interface.
#

INTERFACE_NAME=$1
INTERFACE_DIRECTORY_PYTHON=RaspberryPi/interfaces/python
INTERFACE_DIRECTORY_CPP=RaspberryPi/interfaces/c++
LOG_DIRECTORY_PYTHON=logs/python
LOG_DIRECTORY_CPP=logs/c++
LOCAL_INTERFACES_LIST=local_interfaces.conf


# If "all" is passed, it checks for the existence of any process.
if [[ "${INTERFACE_NAME}" == "all" ]]; then
  INTERFACE_LIST=""
  while IFS= read -r line; do
    IPATH="${line// /}"
    IFS='/' read -r ILANGUAGE INAME <<< "$IPATH"
    if [[ "${IPATH}" != \#* ]]; then
      if [[ "$ILANGUAGE" == "c++" ]]; then
        INTERFACE_LIST="$INTERFACE_LIST $LOG_DIRECTORY_CPP/$INAME.log"
      fi

      if [[ "$ILANGUAGE" == "python" ]]; then
        INTERFACE_LIST="$INTERFACE_LIST $LOG_DIRECTORY_PYTHON/$INAME.log"
      fi
    fi
  done < "$LOCAL_INTERFACES_LIST"
  echo $INTERFACE_LIST
  tail -f -n 50 $INTERFACE_LIST | sed "/==>.*<==/d; /^\s*$/d"
  exit
fi

# If a specific interface is passed, it logs its stdout and stderr on the console.
# Check c++ interfaces
if [ -f "$LOG_DIRECTORY_CPP/$INTERFACE_NAME.log" ]; then
  tail -f -n 50 $LOG_DIRECTORY_CPP/$INTERFACE_NAME.log
  exit
fi

if [ -f "$LOG_DIRECTORY_PYTHON/$INTERFACE_NAME.log" ]; then
  tail -f -n 50 $LOG_DIRECTORY_PYTHON/$INTERFACE_NAME.log
  exit
fi
