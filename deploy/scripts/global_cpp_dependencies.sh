#!/bin/bash

#
# Installs dependencies used by most c++ interfaces.
#

# ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

sudo apt-get install -y build-essential cmake

# Install Paho MQTT Library for C++
git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
git co v1.4.0
git submodule init
git submodule update
cmake -Bbuild -H. -DPAHO_WITH_MQTT_C=ON -DPAHO_BUILD_EXAMPLES=ON
sudo cmake --build build/ --target install
cd ..
rm -r paho.mqtt.cpp