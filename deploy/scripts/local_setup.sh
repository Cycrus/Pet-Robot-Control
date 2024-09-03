#!/bin/bash

# ignore sudo when run as root
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
sudo apt update
sudo apt upgrade
sudo apt install -y build-essential cmake wget python3-pip

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

# Install Arduino libraries
echo ""
echo "[Info] Installing Arduino libraries."
arduino-cli lib update-index
while IFS= read -r line; do
    library_name=$line
    arduino-cli lib install "$library_name"
done < "$ARDUINO_LIBS_FILE"

# Install all interface dependencies
echo ""
echo "[Info] Installing all c++ interface dependencies."
find "$INTERFACE_SRC_PATH/c++" -type d | while read -r subdir; do
    if [[ -x "$subdir/setup.sh" ]]; then
        "$subdir/setup.sh"
    fi
done

echo ""
echo "[Info] Installing all python interface dependencies."
find "$INTERFACE_SRC_PATH/python" -type d | while read -r subdir; do
    if [[ -x "$subdir/setup.sh" ]]; then
        "$subdir/setup.sh"
    fi

    echo "$subdir/requirements.txt"
    if [[ -f "$subdir/requirements.txt" ]]; then
        pip3 install -r $subdir/requirements.txt --break-system-packages
    fi
done

echo ""
echo "[Info] Cleaning up temporary installation location."
cd /tmp
rm -r robot-setup