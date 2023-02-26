#**********************************************************************
# motor_connector.py
# 
# A small script to listen to the motor messages while writing something.
# Works best with characters written in the stream.
# Call the script with python3 sensor_listener.py <PORT> <BAUD_RATE>.
# The message is to be defined as a string of numbers separated by commas,
# such as 3,255,5,34,254,254,254,254.
# Listens to the final bytestream output of the system.
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


def uByteTosByte(byte):
  if byte > 127:
    byte = byte - 255
  return byte


if __name__ == "__main__":
  if len(sys.argv) != 3:
    print("[ERROR] Program arguments: <port> <baud_rate>.")
    exit()

  port = sys.argv[1]
  baud_rate = int(sys.argv[2])
  con = serial.Serial(port, baud_rate)

  message_len = "13,0"
  end_bytes = "254,254,254,254"

  dc_plus = "30"
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

  end_byte_num = 0
  data_size = 0
  read_data = False
  
  time.sleep(2)

  i = 0
  try:
    while True:
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

      byte = con.read()
      byte_val = int.from_bytes(bytes = byte, byteorder  = "little", signed = False)

      if byte_val == 254:
        end_byte_num = end_byte_num + 1
      else:
        end_byte_num = 0
      if end_byte_num == 4:
        end_byte_num = 0
        read_data = True

      if read_data:
        data_size = con.read(2)
        data_size_val = int.from_bytes(bytes = data_size, byteorder  = "little", signed = False)
        data = con.read(data_size_val - 6)

        try:
          right_force = uByteTosByte(data[0])
          left_force = uByteTosByte(data[1])
          x_servo_pos = data[2]
          x_servo_force = uByteTosByte(data[3])
          z_servo_pos = data[4]
          z_servo_force = uByteTosByte(data[5])
        except IndexError:
          read_data = False
          continue

        print_lines = 6
        empty_cells = "                                                               "

        print("**************************************************")
        print(f"Right DC Force = {right_force}{empty_cells}")
        print(f"Left DC Force = {left_force}{empty_cells}")
        print(f"X Axis Servo Pos = {x_servo_pos}{empty_cells}")
        print(f"X Axis Servo Force = {x_servo_force}{empty_cells}")
        print(f"Z Axis Servo Pos = {z_servo_pos}{empty_cells}")
        print(f"Z Axis Servo Force = {z_servo_force}{empty_cells}")
        print("**************************************************", end = ("\033[A" * (print_lines)) + "\033[F")

        read_data = False

      i = i + 1

  except KeyboardInterrupt:
    print("[INFO] User exit.")