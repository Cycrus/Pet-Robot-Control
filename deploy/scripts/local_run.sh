#!/bin/bash

#
# Launches all interfaces without dockerization.
# ./local_run.sh
#

echo ""
echo "################################################"
echo "Launching system undockerized."
echo "################################################"
echo ""

# Starting up Mosquitto MQTT broker
docker compose pull eclipse-mosquitto
docker compose up eclipse-mosquitto -d