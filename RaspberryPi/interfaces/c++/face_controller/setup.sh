#!/bin/bash

sudo apt install -y build-essential cmake wget i2c-tools libcap-dev

# Install SPI dependency
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
tar xvfz bcm2835-1.71.tar.gz
cd bcm2835-1.71
./configure
make
make install
cd ..

# Install i2c dependency
wget https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/i2c-tools-4.3.tar.xz
tar -xf i2c-tools-4.3.tar.xz
cd i2c-tools-4.3
make
make install
cd ..

rm bcm2835-1.71.tar.gz i2c-tools-4.3.tar.xz
rm -r i2c-tools-4.3 bcm2835-1.71