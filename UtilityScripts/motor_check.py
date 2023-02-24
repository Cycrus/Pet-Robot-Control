#**********************************************************************
# motor_check.py
# 
# A small script to listen to the motor messages while writing something.
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
  byte_msg1, int_msg1 = strToBytes(sys.argv[3])
  byte_msg2, int_msg2 = strToBytes("11,0,66,67,68,69,70,254,254,254,254")
  byte_msg3, int_msg3 = strToBytes("7,0,186,254,254,254,254")

  print(f"\n[INFO] Starting general UART listener on port {port} with rate {baud_rate}.\n")
  
  i = 0
  try:
    while True:
      if i == 50:
        con.write(byte_msg1)
        print(f"[INFO] Sent data <{byte_msg1}> or <{int_msg1}>")
      elif i == 100:
        con.write(byte_msg2)
        print(f"[INFO] Sent data <{byte_msg2}> or <{int_msg2}>")
      elif i == 150:
        con.write(byte_msg3)
        print(f"[INFO] Sent data <{byte_msg3}> or <{int_msg3}>")

      line = con.readline()
      try:
        print("[RECEIVED] " + line.decode("utf-8"))
      except UnicodeDecodeError:
        print("[ERROR] Could not decode message to utf-8.")

      i = i + 1

  except KeyboardInterrupt:
    print("[INFO] User exit.")