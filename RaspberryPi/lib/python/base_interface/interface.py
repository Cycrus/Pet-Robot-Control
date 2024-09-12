"""
The base class of the interface all other interfaces are derived of.
"""

from config import EnvConfig
from logger import Logger
from mqttclient import MqttClient
from typing import Optional
import signal
import threading


class Interface:
  def __init__(self, name: str):
    self.name: str = name
    self.logger: Logger = Logger(self.name)
    self.env: EnvConfig = EnvConfig()
    self.mqtt_client: MqttClient = MqttClient(self.name)

    self.exit_timeout = 2
    self.exit_event = threading.Event()
    self.exit_callback: Optional[callable] = None
    signal.signal(signal.SIGINT, self.signal_handler)
    signal.signal(signal.SIGTERM, self.signal_handler)

  def on_exit(self, callback: callable):
    """
    Defines the callback called when the program is externally terminated,
    which is the default method of the framework.
    :param callback: The callback which should be called at the end.
    """
    self.exit_callback = callback

  def signal_handler(self, sig, frame):
    """
    The function called by the signal handler whenever a sigterm or sigint
    are detected.
    """
    self.logger.info(f"Closing down interface {self.name}.")
    if self.exit_callback is not None:
      self.exit_callback()
    self.exit_event.set()
    #exit(0)