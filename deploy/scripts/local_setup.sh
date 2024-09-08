#!/bin/bash

#
# Installs all dependencies to run the whole stack locally with and without dockerization.
#

echo ""
echo "################################################"
echo "Launching local setup process."
echo "################################################"
echo ""

# Ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

ROBOT_PROJECT_DIR=$(pwd)
ARDUINO_LIBS_FILE=$ROBOT_PROJECT_DIR/Arduino/lib_requirements.txt
INTERFACE_SRC_PATH=$ROBOT_PROJECT_DIR/RaspberryPi/interfaces

echo ""
echo "[Info] Setting up temporary installation location."
mkdir /tmp/robot-setup
cd /tmp/robot-setup

echo ""
echo "[Info] Installing default programs with apt."
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install -y build-essential cmake wget python3-pip git

# Install docker
echo ""
echo "[Info] Installing docker"
if command -v docker &> /dev/null
then
  echo "[Info] Docker is already installed. I am not installing it again."
else
  curl -fsSL https://get.docker.com -o install-docker.sh
  sudo sh install-docker.sh 
  sudo groupadd docker
  sudo usermod -aG docker $USER
  docker network create internal-net
  docker buildx create --use
fi

# Install Arduino cli
echo ""
echo "[Info] Installing arduino-cli."
if command -v arduino-cli &> /dev/null
then
  echo "[Info] arduino-cli is already installed. I am not installing it again."
else
  wget https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh
  sudo chmod +x install.sh
  sudo -E BINDIR=/usr/bin ./install.sh
fi

arduino-cli core install arduino:avr@1.8.3

# Install Arduino libraries
echo ""
echo "[Info] Installing Arduino libraries."
arduino-cli lib update-index
while IFS= read -r line; do
    library_name=$line
    arduino-cli lib install "$library_name"
done < "$ARDUINO_LIBS_FILE"

# Install global dependencies
echo ""
echo "[Info] Installing global interface dependencies."
sudo ./$ROBOT_PROJECT_DIR/deploy/scripts/global_cpp_dependencies.sh
sudo ./$ROBOT_PROJECT_DIR/deploy/scripts/global_python_dependencies.sh

# Install all interface dependencies
echo ""
echo "[Info] Installing specific c++ interface dependencies."
find "$INTERFACE_SRC_PATH/c++" -type d | while read -r subdir; do
    if [[ -x "$subdir/setup.sh" ]]; then
        "$subdir/setup.sh"
    fi
done

echo ""
echo "[Info] Installing specific python interface dependencies."
find "$INTERFACE_SRC_PATH/python" -type d | while read -r subdir; do
    if [[ -x "$subdir/setup.sh" ]]; then
        "$subdir/setup.sh"
    fi

    echo "$subdir/requirements.txt"
    if [[ -f "$subdir/requirements.txt" ]]; then
        pip3 install -r $subdir/requirements.txt --break-system-packages
    fi
done

sudo sed -i 's/#dtparam=spi=on/dtparam=spi=on/' /boot/firmware/config.txt

echo ""
echo "[Info] Cleaning up temporary installation location."
cd /tmp
rm -r robot-setup

echo ""
echo "#########################################"
echo "Please reboot the machine now."
echo "#########################################"