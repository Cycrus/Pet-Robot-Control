#!/bin/bash

# ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

# Install general dependencies
sudo apt-get install -y build-essential cmake wget i2c-tools libcap-dev

# Install SPI dependency
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
tar xvfz bcm2835-1.71.tar.gz
cd bcm2835-1.71
./configure
sudo make
sudo make install
cd ..

# Install i2c dependency
wget https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/i2c-tools-4.3.tar.xz
tar -xf i2c-tools-4.3.tar.xz
cd i2c-tools-4.3
sudo make
sudo make install
cd ..

sudo rm bcm2835-1.71.tar.gz i2c-tools-4.3.tar.xz
sudo rm -r i2c-tools-4.3 bcm2835-1.71