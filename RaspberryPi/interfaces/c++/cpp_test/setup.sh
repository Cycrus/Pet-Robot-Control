#!/bin/bash

# ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

# Install general dependencies
sudo apt-get install -y build-essential cmake