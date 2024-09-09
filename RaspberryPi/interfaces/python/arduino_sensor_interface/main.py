#**********************************************************************
# sensor_connector.py
# 
# A small script to listen to the output of the sensory module.
# Called in the Arduino makefile with the argument "connect_sensor".
# Call the script with python3 sensor_listener.py <PORT> <BAUD_RATE>.
# 
# Author: Cyril Marx
# Created: February 2023
#**********************************************************************

import os
import time

i = 0
if __name__ == "__main__":
  while True:
    print(i, flush=True)
    i += 1
    time.sleep(0.033)