#**********************************************************************
# uart_listener.py
# 
# A small script to listen to any incoming UART message.
# Works best with characters written in the stream.
# Call the script with python3 sensor_listener.py <PORT> <BAUD_RATE>.
# 
# Author: Cyril Marx
# Created: February 2023
#**********************************************************************

import serial
import sys
import struct
import os

if __name__ == "__main__":
  if len(sys.argv) != 3:
    print("[ERROR] Program arguments: <port> <baud_rate>.")
    exit()

  port = sys.argv[1]
  baud_rate = int(sys.argv[2])
  con = serial.Serial(port, baud_rate)

  end_byte_num = 0
  data_size = 0
  read_data = False

  print(f"\n[INFO] Starting general UART listener on port {port} with rate {baud_rate}.\n")
  
  try:
    while True:
      line = con.readline()
      print(line.decode("utf-8"))

  except KeyboardInterrupt:
    os.system("clear")
    print("[INFO] User exit.")