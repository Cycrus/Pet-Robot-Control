#!/bin/bash

HOST=$1
USER=$2

if [ "${HOST}" == "" ] || [ "${USER}" == "" ]; then
    echo "[Error] Please provide remote hostname and remote user."
    exit
fi

# Install Docker
ssh $USER@$HOST <<EOF
  curl -fsSL https://get.docker.com -o install-docker.sh
  sudo sh install-docker.sh 
  sudo groupadd docker
  sudo usermod -aG docker $USER
  docker network create internal-net
EOF

echo "Please reboot machine now."