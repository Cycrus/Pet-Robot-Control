"""
A test script to publish data to the locally running MQTT broker.
Command to start broker:
docker run -d --restart unless-stopped -p 1883:1883 -p 9001:9001 -v /opt/mosquitto/config/mosquitto.conf:/mosquitto/config/mosquitto.conf -v /opt/mosquitto/data:/mosquitto/data -v /opt/mosquitto/log:/mosquitto/log eclipse-mosquitto
"""

import time
import paho.mqtt.client as mqtt

if __name__ == "__main__":
  address = "localhost"
  port = 1883
  topic = "input/motor/led_b"
  print(f"[Info] Connecting to MQTT broker on {address}:{port}")
  mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
  mqttc.connect(address, port, 60)
  mqttc.loop_start()

  print("[Info] Starting message publishing.")
  i = 0
  try:
    while True:
        i += 1
        mqttc.publish(topic, 20)
        time.sleep(1)
  except KeyboardInterrupt:
    print("[Info] User interrupt.")
    mqttc.publish(topic, 0)

  mqttc.loop_stop()
