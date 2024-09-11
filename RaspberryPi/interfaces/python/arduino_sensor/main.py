import time
from config import EnvConfig
from logger import Logger


class SensorArduino:
  def __init__(self):
    self.logger = Logger("SensorArduino")
    self.env = EnvConfig()


i = 0
if __name__ == "__main__":
  sensor_interface = SensorArduino()
  mqtt_host = test.env.getValue("MQTT_HOST")
  mqtt_port = test.env.getValue("MQTT_PORT")
  sensor_port = test.env.getValue("SENSORY_PORT")

  while True:
    test.logger.success(mqtt_host)
    test.logger.error(mqtt_port)
    test.logger.debug(sensor_port)
    time.sleep(0.033)
