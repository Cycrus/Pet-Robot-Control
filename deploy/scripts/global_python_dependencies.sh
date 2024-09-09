#!/bin/bash

#
# Installs dependencies used by most python interfaces.
#

# ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

sudo apt-get install python3 python3-pip

# Install Paho MQTT Library for Python
pip3 install paho-mqtt python-dotenv --break-system-packages