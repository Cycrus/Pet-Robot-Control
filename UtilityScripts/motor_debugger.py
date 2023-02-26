#**********************************************************************
# motor_debugger.py
# 
# A small script to listen to the motor messages while writing something.
# Works best with characters written in the stream.
# Call the script with python3 sensor_listener.py <PORT> <BAUD_RATE>.
# The message is to be defined as a string of numbers separated by commas,
# such as 3,255,5,34,254,254,254,254.
# Listens to ASCII formatted debug outputs of the system.
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
  if len(sys.argv) != 3:
    print("[ERROR] Program arguments: <port> <baud_rate>.")
    exit()

  port = sys.argv[1]
  baud_rate = int(sys.argv[2])
  con = serial.Serial(port, baud_rate, timeout = 0.005)

  message_len = "13,0"
  end_bytes = "254,254,254,254"

  dc_plus = "50"
  dc_minus = str(255 - int(dc_plus))
  servo_plus = "10"
  servo_minus = str(255 - int(servo_plus))
  str_msg1 = f"{message_len},{dc_minus},{dc_plus},{servo_plus},0,10,0,0,{end_bytes}"
  byte_msg1, int_msg1 = strToBytes(str_msg1)
  str_msg2 = f"{message_len},{dc_plus},{dc_minus},{servo_minus},{servo_plus},0,10,0,{end_bytes}"
  byte_msg2, int_msg2 = strToBytes(str_msg2)
  str_msg3 = f"{message_len},{dc_plus},{dc_plus},0,{servo_minus},0,0,10,{end_bytes}"
  byte_msg3, int_msg3 = strToBytes(str_msg3)

  str_ret = message_len + ",0,0,0,0,0,0,0," + end_bytes
  byte_ret, int_ret = strToBytes(str_ret)

  print(f"\n[INFO] Starting motor system check on port {port} with rate {baud_rate}.\n")
  
  time.sleep(2)

  i = 0
  try:
    while True:
      # print(i)
      if i == 50:
        con.write(byte_msg1)
        print(f"[INFO] Sent data <{byte_msg1}> or <{int_msg1}>")
      elif i == 350:
        con.write(byte_msg2)
        print(f"[INFO] Sent data <{byte_msg2}> or <{int_msg2}>")
      elif i == 650:
        con.write(byte_msg3)
        print(f"[INFO] Sent data <{byte_msg3}> or <{int_msg3}>")
      elif i == 950:
        con.write(byte_ret)
        print(f"[INFO] Sent data <{byte_ret}> or <{int_ret}>")
        print("[INFO] Finished check.")
        break

      try:
        line = con.readline()
        if len(line) > 0:
          print("[RECEIVED] " + line.decode("utf-8"))
      except UnicodeDecodeError:
        print("[ERROR] Could not decode message to utf-8.")

      i = i + 1

  except KeyboardInterrupt:
    print("[INFO] User exit.")