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

  print(f"\n[INFO] Starting UART listener on port {port} with rate {baud_rate}.\n")
  
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

        distance_front = int.from_bytes(bytes = data[0:2], byteorder  = "little", signed = True)
        distance_back = int.from_bytes(bytes = data[2:4], byteorder  = "little", signed = True)
        temperature = int.from_bytes(bytes = data[4:6], byteorder  = "little", signed = True)
        pressure = int.from_bytes(bytes = data[6:8], byteorder  = "little", signed = False)
        altitude = int.from_bytes(bytes = data[8:10], byteorder  = "little", signed = False)
        humidity = bytes = data[10]
        [gas] = struct.unpack("f", data[11:15])
        rfid = data[15]

        [compass_x] = struct.unpack("f", data[16:20])
        [compass_y] = struct.unpack("f", data[20:24])
        [compass_z] = struct.unpack("f", data[24:28])
        [compass_heading] = struct.unpack("f", data[28:32])
        [current_per_hour] = struct.unpack("f", data[32:36])
        [current] = struct.unpack("f", data[36:40])
        [accx] = struct.unpack("f", data[40:44])
        [accy] = struct.unpack("f", data[44:48])
        [accz] = struct.unpack("f", data[48:52])
        [gyrx] = struct.unpack("f", data[52:56])
        [gyry] = struct.unpack("f", data[56:60])
        [gyrz] = struct.unpack("f", data[60:64])
        [angx] = struct.unpack("f", data[64:68])
        [angy] = struct.unpack("f", data[68:72])
        [angz] = struct.unpack("f", data[72:76])
        [gps_lon] = struct.unpack("d", data[76:84])
        [gps_lat] = struct.unpack("d", data[84:92])

        year = int.from_bytes(bytes = data[92:94], byteorder  = "little", signed = False)
        month = int.from_bytes(bytes = data[94:96], byteorder  = "little", signed = False)
        day = int.from_bytes(bytes = data[96:98], byteorder  = "little", signed = False)
        hour = int.from_bytes(bytes = data[98:100], byteorder  = "little", signed = False)
        minute = int.from_bytes(bytes = data[100:102], byteorder  = "little", signed = False)
        second = int.from_bytes(bytes = data[102:105], byteorder  = "little", signed = False)
        centisecond = int.from_bytes(bytes = data[105:106], byteorder  = "little", signed = False)
        altitude = int.from_bytes(bytes = data[106:108], byteorder  = "little", signed = False)
        [speed] = struct.unpack("f", data[108:112])
        course = int.from_bytes(bytes = data[112:114], byteorder  = "little", signed = False)
        satellite_number = data[114]
        frequency = int.from_bytes(bytes = data[115:117], byteorder  = "little", signed = False)

        print_lines = 30
        empty_cells = "                                                               "

        print("**************************************************")
        print(f"Distance Front = {distance_front}{empty_cells}")
        print(f"Distance Back = {distance_back}{empty_cells}")
        print(f"Temperature = {temperature}{empty_cells}")
        print(f"Altitude = {altitude}{empty_cells}")
        print(f"Humidity = {humidity}{empty_cells}")
        print("Gas PPM = {:.3f}".format(gas) + empty_cells)
        print(f"RFID Data = {rfid}{empty_cells}")
        print("Compass X = {:.3f}".format(compass_x) + empty_cells)
        print("Compass Y = {:.3f}".format(compass_y) + empty_cells)
        print("Compass Z = {:.3f}".format(compass_z) + empty_cells)
        print("Compass Heading = {:.3f}".format(compass_heading) + empty_cells)
        print("Current per Hour = {:.3f}".format(current_per_hour) + empty_cells)
        print("Current = {:.3f}".format(current) + empty_cells)
        print("Acc X = {:.3f}".format(accx) + empty_cells)
        print("Acc Y = {:.3f}".format(accy) + empty_cells)
        print("Acc Z = {:.3f}".format(accz) + empty_cells)
        print("Gyr X = {:.3f}".format(gyrx) + empty_cells)
        print("Gyr Y = {:.3f}".format(gyry) + empty_cells)
        print("Gyr Z = {:.3f}".format(gyrz) + empty_cells)
        print("Ang X = {:.3f}".format(angx) + empty_cells)
        print("Ang Y = {:.3f}".format(angy) + empty_cells)
        print("Ang Z = {:.3f}".format(angz) + empty_cells)
        print("GPS Lon = {:.7f}".format(gps_lon) + empty_cells)
        print("GPS Lat = {:.7f}".format(gps_lat) + empty_cells)
        print(f"GPS Time = {day}.{month}.{year} {hour}:{minute}:{second}.{centisecond}{empty_cells}")
        print(f"GPS Altitude = {altitude}{empty_cells}")
        print(f"GPS Speed = {speed}{empty_cells}")
        print(f"GPS Course = {course}{empty_cells}")
        print(f"GPS Satellite Number = {satellite_number}{empty_cells}")
        print(f"Frequency = {frequency}{empty_cells}")
        print("**************************************************", end = ("\033[A" * (print_lines)) + "\033[F")

        read_data = False

  except KeyboardInterrupt:
    os.system("clear")
    print("[INFO] User exit.")