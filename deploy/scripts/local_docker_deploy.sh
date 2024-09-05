#!/bin/bash

#
# Builds all docker images and launches them locally.
#

echo ""
echo "################################################"
echo "Launching local docker deployment process."
echo "################################################"
echo ""

ARCH=$(uname -m)
BUILD_ARCH=$ARCH docker compose build
docker compose up