#!/bin/bash

#
# A wrapper to include the libraries in the lib/python directory in the
# python script.
# Do not edit.
#

SCRIPT_PATH=$1
LIB_PATH=$2

for lib in $LIB_PATH/*; do
  export PYTHONPATH="${PYTHONPATH}:$lib"
done

python3 $SCRIPT_PATH
