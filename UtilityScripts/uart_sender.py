#**********************************************************************
# uart_sender.py
# 
# A small script to send a single message via a UART stream.
# Works best with characters written in the stream.
# Call the script with python3 sensor_listener.py <PORT> <BAUD_RATE> <message>.
# The message is to be defined as a string of numbers separated by commas,
# such as 3,255,5,34,254,254,254,254.
# 
# Author: Cyril Marx
# Created: February 2023
#**********************************************************************

import serial
import sys
import struct
import os
import time


def strToBytes(array):
  num_array = array.split(",")
  for i in range(len(num_array)):
    num_array[i] = int(num_array[i])
  byte_array = bytes(num_array)
  return byte_array, num_array


if __name__ == "__main__":
  if len(sys.argv) != 4:
    print("[ERROR] Program arguments: <port> <baud_rate> <message>.")
    exit()

  port = sys.argv[1]
  baud_rate = int(sys.argv[2])
  con = serial.Serial(port, baud_rate)
  byte_msg, int_msg = strToBytes(sys.argv[3])
  print("[INFO] Wating for a few seconds to let the board reset due to opened Serial connection.")
  time.sleep(2)

  con.write(byte_msg)
  print(f"[INFO] Sent data <{byte_msg}> or <{int_msg}>")