from interface import Interface


class MqttListener(Interface):
  def __init__(self):
    super().__init__("MqttListener")
    self.on_exit(self.close)

  def echo_message(self, client, userdata, msg):
    """
    Prints the arriving message.
    """
    self.logger.debug(msg.topic + " " + str(msg.payload))

  def subscribe_topics(self, client, userdata, flags, reason_code, properties):
    """
    Subscribes to all relevant topics.
    """
    self.mqtt_client.subscribe("output/sensor/distance_front")
    self.mqtt_client.subscribe("output/sensor/distance_back")

  def close(self):
    """
    Closes the MQTT client. is handed as a callback to the exit signal function.
    """
    self.mqtt_client.stop_loop()
    self.mqtt_client.close()

  def main(self):
    self.mqtt_client.on_message(self.echo_message)
    self.mqtt_client.on_connect(self.subscribe_topics)
    self.mqtt_client.connect()
    self.mqtt_client.start_loop(blocking = True)


if __name__ == "__main__":
  interface = MqttListener()
  interface.main()
  interface.exit_event.wait(interface.exit_timeout)
  interface.logger.success("Gracefully exited interface.")