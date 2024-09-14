"""
A class to automatically connect to the MQTT broker specified in the .env file.
"""

import paho.mqtt.client as mqtt
from config import EnvConfig
from logger import Logger


class MqttClient:
  def __init__(self, logger: Logger, interface_name: str):
    self.env = EnvConfig()
    self.logger = logger
    self.mqtt_id = (self.env.getValue("MQTT_HOST"), int(self.env.getValue("MQTT_PORT")))
    self.mqtt_client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, client_id = interface_name)

  def connect(self) -> bool:
    """
    Connects an MQTT client to the broker.
    """
    self.logger.info(f"Setting up MQTT client to {self.mqtt_id[0]}:{self.mqtt_id[1]}.")
    try:
      self.mqtt_client.connect(self.mqtt_id[0], self.mqtt_id[1])
      self.logger.success("MQTT client connected.")
      return True
    except Exception as e:
      self.logger.error(f"Cannot setup MQTT client. {e}.")
      self.mqtt_client = None
      return False

  def on_connect(self, callback: callable) -> bool:
    """
    Defines the callback for a new connection event.
    Needs following parameters: (client, userdata, flags, reason_code, properties)
    """
    try:
      self.mqtt_client.on_connect = callback
      self.logger.success("Assigned on_connect() callback to MQTT client.")
      return True
    except Exception as e:
      self.logger.error(f"Cannot assign on_connect() callback to MQTT client. {e}.")
      return False
    
  def on_message(self, callback: callable) -> bool:
    """
    Defines the callback for a new message event.
    Needs the following parameters: (client, userdata, msg)
    """
    try:
      self.mqtt_client.on_message = callback
      self.logger.success("Assigned on_message() callback to MQTT client.")
      return True
    except Exception as e:
      self.logger.error(f"Cannot assign on_message() callback to MQTT client. {e}.")
      return False
    
  def start_loop(self, blocking: bool = False) -> bool:
    self.logger.info(f"Starting MQTT loop. Blocking = {blocking}.")
    try:
      if blocking:
        self.mqtt_client.loop_forever()
      else:
        self.mqtt_client.loop_start()
      return True
    except Exception as e:
      self.logger.error(f"Could not start MQTT event loop. {e}.")
      return False

  def stop_loop(self) -> bool:
    self.logger.info("Stopping MQTT loop.")
    try:
      self.mqtt_client.loop_stop()
      return True
    except Exception as e:
      self.logger.error(f"Could not stop MQTT loop. {e}.")
      return False

  def close(self) -> bool:
    self.logger.info(f"Closing MQTT client to {self.mqtt_id[0]}:{self.mqtt_id[1]}.")
    try:
      self.mqtt_client.disconnect()
      self.mqtt_client = None
      self.logger.success("Successfully closed MQTT client.")
      return True
    except Exception as e:
      self.logger.error(f"Cannot close MQTT client. {e}.")
      return False

  def subscribe(self, topic: str) -> bool:
    self.logger.info(f"Subscribing to topic {topic}.")
    try:
      self.mqtt_client.subscribe(topic)
      return True
    except Exception as e:
      self.logger.error(f"Not able to subscribe to topic {topic}. {e}.")
      return False
    
  def publish(self, topic_prefix: str, data_dict: dict) -> bool:
    try:
      for key in data_dict:
        data = data_dict[key]
        self.mqtt_client.publish(topic_prefix + "/" + key, data)
      return True
    except Exception as e:
      self.logger.error(f"Cannot publish data. {e}.")
      return False