import time
from config import EnvConfig
from logger import Logger
import serial
import paho.mqtt.client as mqtt
import struct


class SensorArduino:
  def __init__(self):
    self.name = "ArduinoSensor"
    self.logger = Logger(self.name)
    self.env = EnvConfig()
    self.mqtt_id = (self.env.getValue("MQTT_HOST"), int(self.env.getValue("MQTT_PORT")))
    self.arduino_port = self.env.getValue("SENSORY_PORT")
    self.arduino_baud = self.env.getValue("SENSORY_BAUD")
    self.sensor_dict = {}
    self.mqttc = None
    self.arduino = None
    self.running = True

  def close(self):
    self.running = False
    self.close_arduino()
    self.close_mqtt_client()

  def connect_mqtt_client(self):
    """
    Connects an MQTT client to the broker.
    """
    self.logger.info(f"Setting up MQTT client to {self.mqtt_id[0]}:{self.mqtt_id[1]}.")
    try:
      if self.mqttc is None:
        self.mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.mqttc.connect(self.mqtt_id[0], self.mqtt_id[1])
        self.mqttc.loop_start()
        self.logger.success("MQTT client connected.")
      else:
        self.logger.warning("MQTT client already running. Not setting up again.")
    except Exception as e:
      self.logger.error(f"Cannot setup MQTT client. {e}.")
      self.mqttc = None

  def close_mqtt_client(self):
    """
    Closes an established MQTT client connection.
    """
    self.logger.info(f"Closing MQTT cient to {self.mqtt_id[0]}:{self.mqtt_id[1]}")
    try:
      if self.arduino is not None:
        self.mqttc.loop_stop()
        self.mqttc = None
        self.logger.success(f"Successfully closed MQTT client.")
      else:
        self.logger.warning("MQTT client already closed. Not closing again.")
    except Exception as e:
      self.logger.error(f"MQTT client could not be closed. {e}.")

  def connect_arduino(self):
    """
    Connects the process to an Arduino.
    """
    self.logger.info(f"Connecting to Arduino at {self.arduino_port} using a baud of {self.arduino_baud}.")
    try:
      if self.arduino is None:
        self.arduino = serial.Serial(self.arduino_port, self.arduino_baud)
        self.logger.success("Successfully connected to Arduino.")
      else:
        self.logger.warning("Arduino already connected. Not connecting again.")
    except Exception as e:
      self.logger.error(f"Cannot connect to Arduino. {e}.")
      self.arduino = None

  def close_arduino(self):
    """
    Closes an opened Arduino connection.
    """
    self.logger.info(f"Closing Arduino connection at {self.arduino_port}")
    try:
      if self.arduino is not None:
        self.arduino.close()
        self.arduino = None
        self.logger.success(f"Successfully closed Arduino connection.")
      else:
        self.warning("Arduino connection already closes. Not closing again.")
    except Exception as e:
      self.logger.error("Arduino connection could not be closed. {e}.")

  def get_sensor_data(self):
    """
    Fetches the sensor data from the Arduino.
    """
    end_byte_num = 0
    data_size = 0
    read_data = False
    
    while self.running:
      byte = self.arduino.read(1)
      byte_val = int.from_bytes(bytes = byte, byteorder  = "little", signed = False)

      if byte_val == 254:
        end_byte_num = end_byte_num + 1
      else:
        end_byte_num = 0
      if end_byte_num == 4:
        end_byte_num = 0
        read_data = True

      if read_data:
        data_size = self.arduino.read(2)
        data_size_val = int.from_bytes(bytes = data_size, byteorder  = "little", signed = False)
        data = self.arduino.read(data_size_val)
        
        distance_front = int.from_bytes(bytes = data[0:2], byteorder  = "little", signed = True)
        distance_back = int.from_bytes(bytes = data[2:4], byteorder  = "little", signed = True)
        temperature = int.from_bytes(bytes = data[4:6], byteorder  = "little", signed = True)
        pressure = int.from_bytes(bytes = data[6:8], byteorder  = "little", signed = False)
        altitude_1 = int.from_bytes(bytes = data[8:10], byteorder  = "little", signed = False)
        humidity = data[10]
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

        self.sensor_dict["distance_front"] = distance_front
        self.sensor_dict["distance_back"] = distance_back
        self.sensor_dict["temperature"] = temperature
        self.sensor_dict["pressure"] = pressure
        self.sensor_dict["altitude_1"] = altitude_1
        self.sensor_dict["humidity"] = humidity
        self.sensor_dict["gas"] = gas
        self.sensor_dict["rfid"] = rfid

        self.sensor_dict["compass_x"] = compass_x
        self.sensor_dict["compass_y"] = compass_y
        self.sensor_dict["compass_z"] = compass_z
        self.sensor_dict["compass_heading"] = compass_heading
        self.sensor_dict["current_per_hour"] = current_per_hour
        self.sensor_dict["current"] = current
        self.sensor_dict["accx"] = accx
        self.sensor_dict["accy"] = accy
        self.sensor_dict["accz"] = accz
        self.sensor_dict["gyrx"] = gyrx
        self.sensor_dict["gyry"] = gyry
        self.sensor_dict["gyrz"] = gyrz
        self.sensor_dict["angx"] = angx
        self.sensor_dict["angy"] = angy
        self.sensor_dict["angz"] = angz
        self.sensor_dict["gps_lon"] = gps_lon
        self.sensor_dict["gps_lat"] = gps_lat

        self.sensor_dict["year"] = year
        self.sensor_dict["month"] = month
        self.sensor_dict["day"] = day
        self.sensor_dict["hour"] = hour
        self.sensor_dict["minute"] = minute
        self.sensor_dict["second"] = second
        self.sensor_dict["centisecond"] = centisecond
        self.sensor_dict["altitude_2"] = altitude_2
        self.sensor_dict["speed"] = speed
        self.sensor_dict["course"] = course
        self.sensor_dict["satellite_number"] = satellite_number
        self.sensor_dict["frequency"] = frequency

        return
      
  def publish_sensor_data(self, prefix):
    """
    Publishes the sensor data from the Arduino on MQTT topics.
    """
    for key in self.sensor_dict:
      data = self.sensor_dict[key]
      self.mqttc.publish(prefix + "/" + key, data)


if __name__ == "__main__":
  sensor_interface = SensorArduino()
  sensor_interface.connect_arduino()
  sensor_interface.connect_mqtt_client()

  while True:
    try:
      sensor_interface.get_sensor_data()
      sensor_interface.publish_sensor_data("output/sensor")
    except Exception as e:
      sensor_interface.logger.error(f"{sensor_interface.name} died. {e}.")
      sensor_interface.close()
      exit(0)
