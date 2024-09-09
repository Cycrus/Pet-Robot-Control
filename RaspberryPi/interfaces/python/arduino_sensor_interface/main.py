
import os
import time
from dotenv import load_dotenv

i = 0
if __name__ == "__main__":
  load_dotenv()

  while True:
    print(os.getenv("MQTT_HOST"), flush=True)
    print(os.getenv("MQTT_PORT"), flush=True)
    print(os.getenv("MOTOR_PORT"), flush=True)
    print(i, flush=True)
    i += 1
    time.sleep(0.033)
