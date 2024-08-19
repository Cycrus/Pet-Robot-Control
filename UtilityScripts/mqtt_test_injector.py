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

import serial
import sys
import struct
import time
import paho.mqtt.client as mqtt

sensor_dict = {}

def get_sensor_data(output_dict, con):
  end_byte_num = 0
  data_size = 0
  read_data = False
  
  while True:
    byte = con.read(1)
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
      data = con.read(data_size_val)
      
      distance_front = int.from_bytes(bytes = data[0:2], byteorder  = "little", signed = True)
      distance_back = int.from_bytes(bytes = data[2:4], byteorder  = "little", signed = True)
      temperature = int.from_bytes(bytes = data[4:6], byteorder  = "little", signed = True)
      pressure = int.from_bytes(bytes = data[6:8], byteorder  = "little", signed = False)
      altitude_1 = int.from_bytes(bytes = data[8:10], byteorder  = "little", signed = False)
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
      altitude_2 = int.from_bytes(bytes = data[106:108], byteorder  = "little", signed = False)
      [speed] = struct.unpack("f", data[108:112])
      course = int.from_bytes(bytes = data[112:114], byteorder  = "little", signed = False)
      satellite_number = data[114]
      frequency = int.from_bytes(bytes = data[115:117], byteorder  = "little", signed = False)

      output_dict["distance_front"] = distance_front
      output_dict["distance_back"] = distance_back
      output_dict["temperature"] = temperature
      output_dict["pressure"] = pressure
      output_dict["altitude_1"] = altitude_1
      output_dict["humidity"] = humidity
      output_dict["gas"] = gas
      output_dict["rfid"] = rfid

      output_dict["compass_x"] = compass_x
      output_dict["compass_y"] = compass_y
      output_dict["compass_z"] = compass_z
      output_dict["compass_heading"] = compass_heading
      output_dict["current_per_hour"] = current_per_hour
      output_dict["current"] = current
      output_dict["accx"] = accx
      output_dict["accy"] = accy
      output_dict["accz"] = accz
      output_dict["gyrx"] = gyrx
      output_dict["gyry"] = gyry
      output_dict["gyrz"] = gyrz
      output_dict["angx"] = angx
      output_dict["angy"] = angy
      output_dict["angz"] = angz
      output_dict["gps_lon"] = gps_lon
      output_dict["gps_lat"] = gps_lat

      output_dict["year"] = year
      output_dict["month"] = month
      output_dict["day"] = day
      output_dict["hour"] = hour
      output_dict["minute"] = minute
      output_dict["second"] = second
      output_dict["centisecond"] = centisecond
      output_dict["altitude_2"] = altitude_2
      output_dict["speed"] = speed
      output_dict["course"] = course
      output_dict["satellite_number"] = satellite_number
      output_dict["frequency"] = frequency

      return 
    
def inject_mqtt_data(data_dict, mqtt_con, prefix):
  for key in data_dict:
    data = data_dict[key]
    mqttc.publish(prefix + "/" + key, data)

if __name__ == "__main__":
  if len(sys.argv) != 7:
    print("[ERROR] Program arguments: <sensor_port> <sensor_baud_rate> <motor_port> <motor_baud_rate> <mqtt_address> <mqtt_port>.")
    exit()

  sensor_port = sys.argv[1]
  sensor_baud_rate = int(sys.argv[2])
  motor_port = sys.argv[3]
  motor_baud_rate = int(sys.argv[4])
  mqtt_address = sys.argv[5]
  mqtt_port = int(sys.argv[6])

  print(f"[Info] Connecting to MQTT broker on {mqtt_address}:{mqtt_port}")
  mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
  mqttc.connect(mqtt_address, mqtt_port, 60)
  mqttc.loop_start()

  print(f"\n[Info] Starting sensor UART listener on port {sensor_port} with rate {sensor_baud_rate}.\n")
  sensor_con = serial.Serial(sensor_port, sensor_baud_rate)
  #print(f"\n[Info] Starting motor UART listener on port {motor_port} with rate {motor_baud_rate}.\n")
  #motor_con = serial.Serial(motor_port, motor_baud_rate)
  time.sleep(2)

  while True:
    try:
      get_sensor_data(sensor_dict, sensor_con)
      inject_mqtt_data(sensor_dict, mqttc, "sensor")
    except KeyboardInterrupt:
      print("[Info] User exit.")
      mqttc.loop_stop()
      exit(0)


