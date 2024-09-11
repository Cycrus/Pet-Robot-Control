import paho.mqtt.client as mqtt

# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, reason_code, properties):
    print(f"Connected with result code {reason_code}")
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe("input/motor/led_r")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

if __name__ == "__main__":
  address = "localhost"
  port = 1883
  print(f"[Info] Connecting to MQTT broker on {address}:{port}")
  mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
  mqttc.on_connect = on_connect
  mqttc.on_message = on_message

  mqttc.connect(address, port, 60)

  # Blocking call that processes network traffic, dispatches callbacks and
  # handles reconnecting.
  # Other loop*() functions are available that give a threaded interface and a
  # manual interface.
  print("[Info] Receiving messages now.")
  mqttc.loop_forever()
