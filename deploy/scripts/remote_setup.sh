#!/bin/bash

HOST=$1
USER=$2

# Install Docker

ssh $USER@$HOST <<EOF
  curl -fsSL https://get.docker.com -o install-docker.sh
  sudo sh install-docker.sh 
  sudo groupadd docker
  sudo usermod -aG docker $USER
EOF

echo "Please reboot machine now."