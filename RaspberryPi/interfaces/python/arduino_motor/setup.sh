#!/bin/bash

# ignore sudo when run as root
sudo() {
  [[ "${EUID}" == 0 ]] || set -- command sudo "${@}"
  "${@}"
}

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

pip3 install -r $SCRIPT_DIR/requirements.txt --break-system-packages