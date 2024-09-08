#!/bin/bash

#
# Installs dependencies used by most python interfaces.
#

# ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

# Install Paho MQTT Library for Python
pip install python3 python3-pip paho-mqtt