#**********************************************************************
# reset_boards.py
# 
# Opens the serial port for a short time of an arduino board to reset
# its state.
# Use with arguments <port>.
# 
# Author: Cyril Marx
# Created: February 2023
#**********************************************************************

import serial
import sys

if __name__ == "__main__":
  if len(sys.argv) != 2:
    print("[ERROR] Program arguments: <port>.")
    exit()
  port = sys.argv[1]
  con = serial.Serial(port)