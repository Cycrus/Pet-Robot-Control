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

if __name__ == "__main__":
  while True:
    try:
      print(os.getenv("MQTT_HOST"))
      print(os.getenv("MQTT_PORT"))
    except Exception as e:
      print(e)