import time
from config import EnvConfig
from logger import Logger
import paho.mqtt.client as mqtt


class MqttListener:
  def __init__(self):
    self.name = "MqttListener"
    self.logger = Logger(self.name)
    self.env = EnvConfig()
    self.mqtt_id = (self.env.getValue("MQTT_HOST"), int(self.env.getValue("MQTT_PORT")))
    self.mqttc = None
    self.running = True

  def close(self):
    self.running = False
    self.close_mqtt_client()

  def subscribe_mqtt(self, topic):
    self.mqttc.on_message = self.echo_message
    self.mqttc.subscribe(topic)

  def loop_mqtt(self):
    self.mqttc.loop_forever()

  def echo_message(self, client, userdata, msg):
    self.logger.debug(msg.topic + " " + str(msg.payload))

  def connect_mqtt_client(self):
    """
    Connects an MQTT client to the broker.
    """
    self.logger.info(f"Setting up MQTT client to {self.mqtt_id[0]}:{self.mqtt_id[1]}.")
    try:
      if self.mqttc is None:
        self.mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
        self.mqttc.connect(self.mqtt_id[0], self.mqtt_id[1])
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


if __name__ == "__main__":
  listener = MqttListener()
  listener.connect_mqtt_client()
  listener.subscribe_mqtt("output/sensor/distance_front")
  listener.loop_mqtt()
