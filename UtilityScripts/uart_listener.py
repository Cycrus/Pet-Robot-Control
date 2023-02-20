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
  
  try:
    while True:
      byte = con.read()
      byte_val = int.from_bytes(bytes = byte, byteorder  = "little", signed = False)

      if byte_val == 255:
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

        distance_front = int.from_bytes(bytes = data[0:1], byteorder  = "little", signed = True)
        distance_back = int.from_bytes(bytes = data[2:3], byteorder  = "little", signed = True)
        temperature = int.from_bytes(bytes = data[4:5], byteorder  = "little", signed = True)
        pressure = int.from_bytes(bytes = data[6:7], byteorder  = "little", signed = False)
        altitude = int.from_bytes(bytes = data[8:9], byteorder  = "little", signed = False)
        humidity = bytes = data[10]
        #[gas] = struct.unpack("f", data[11:14]) #float.from_bytes(data[11:14], "little", )
        rfid = data[15]

        print(f"Distance Front = {distance_front}")
        print(f"Distance Back = {distance_back}")
        print(f"Temperature = {temperature}")
        print(f"Altitude = {altitude}")
        print(f"Humidity = {humidity}")
        print(f"RFID Data = {rfid}")
        print("**************************************************", end = "\033[A\033[A\033[A\033[A\033[A\033[F")

        read_data = False

  except KeyboardInterrupt:
    print("[INFO] User exit.")