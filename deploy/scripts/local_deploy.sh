#!/bin/bash

# Only to be called from the root Makefile

ARCH=$(uname -m)
BUILD_ARCH=$ARCH docker compose build