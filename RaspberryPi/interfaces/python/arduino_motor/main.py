import serial
import struct
from interface import Interface
from arduinoconn import ArduinoSerial


class SensorArduino(Interface):
  def __init__(self):
    super().__init__("MotorArduino")

    self.arduino_port = self.env.getValue("SENSORY_PORT")
    self.arduino_baud = self.env.getValue("SENSORY_BAUD")
    self.sensor_dict = {}
    self.mqttc = None
    self.arduino = ArduinoSerial(self.arduino_port, self.arduino_baud)
    self.data_format = {
      "distance_front": "int16",
      "distance_back": "int16",
      "temperature": "int16",
      "pressure": "uint16",
      "altitude_1": "uint16",
      "humidity": "uint8",
      "gas": "float32",
      "rfid": "uint8",
      "compass_x": "float32",
      "compass_y": "float32",
      "compass_z": "float32",
      "compass_heading": "float32",
      "current_per_hour": "float32",
      "current": "float32",
      "accx": "float32",
      "accy": "float32",
      "accz": "float32",
      "gyrx": "float32",
      "gyry": "float32",
      "gyrz": "float32",
      "angx": "float32",
      "angy": "float32",
      "angz": "float32",
      "gps_lon": "float64",
      "gps_lat": "float64",
      "year": "uint16",
      "month": "uint16",
      "day": "uint16",
      "hour": "uint16",
      "second": "uint16",
      "centisecond": "uint16",
      "altitude_2": "uint16",
      "speed": "float32",
      "course": "uint16",
      "satellite_number": "uint8",
      "frequency": "uint16"
    }

  def close(self):
    self.mqtt_client.stop_loop()
    self.mqtt_client.close()
    
  def main(self):
    self.arduino.connect()
    self.mqtt_client.connect()
    self.mqtt_client.start_loop(blocking = False)

    while not self.exit_event.is_set():
      self.logger.debug("heeeeeeewwooooooo")
      try:
        size_matches, self.sensor_dict = self.arduino.receive_arduino_data(self.data_format, "little", self.exit_event)
        if not size_matches:
          self.logger.warning("Size of format specifier does not match.")
        self.mqtt_client.publish("output/sensor", self.sensor_dict)
      except Exception as e:
        self.logger.error(f"{self.name} died. {e}.")
        break

    self.arduino.close()
    self.close()


if __name__ == "__main__":
  interface = SensorArduino()
  interface.main()
  interface.exit_event.wait(interface.exit_timeout)
  interface.logger.success("Gracefully exited interface.")
