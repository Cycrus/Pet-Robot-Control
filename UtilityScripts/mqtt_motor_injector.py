#**********************************************************************
# sensor_connector.py
# 
# A small script to listen to the output of the motor module.
# Called in the Arduino makefile with the argument "connect_sensor".
# Call the script with python3 sensor_listener.py <PORT> <BAUD_RATE>.
# 
# Author: Cyril Marx
# Created: August 2024
#**********************************************************************

import serial
import sys
import time
import paho.mqtt.client as mqtt

class MotorInstruction:
  def __init__(self):
    self.message_len = 13
    self.dc_right = 0
    self.dc_left = 0
    self.servo_x = 0
    self.servo_z = 0
    self.r = 0
    self.g = 0
    self.b = 0
    self.end_bytes = [254, 254, 254, 254]

  def assign_instruction_value(self, key, value):
    if key == "input/motor/right_motor_force":
      self.dc_right = int(value)
    elif key == "input/motor/left_motor_force":
      self.dc_left = int(value)
    elif key == "input/motor/x_servo_force":
      self.servo_x = int(value)
    elif key == "input/motor/z_servo_force":
      self.servo_z = int(value)
    elif key == "input/motor/led_r":
      self.r = int(value)
    elif key == "input/motor/led_g":
      self.g = int(value)
    elif key == "input/motor/led_b":
      self.b = int(value)

  def toBytes(self):
    instruction_bytes = self.message_len.to_bytes(2, byteorder="little", signed=False) +\
                        self.dc_right.to_bytes(1, byteorder="little", signed=True) +\
                        self.dc_left.to_bytes(1, byteorder="little", signed=True) +\
                        self.servo_x.to_bytes(1, byteorder="little", signed=True) +\
                        self.servo_z.to_bytes(1, byteorder="little", signed=True) +\
                        self.r.to_bytes(1, byteorder="little", signed=True) +\
                        self.g.to_bytes(1, byteorder="little", signed=True) +\
                        self.b.to_bytes(1, byteorder="little", signed=True) +\
                        bytes(self.end_bytes)
    return instruction_bytes

sensor_dict = {}
motor_instruction = MotorInstruction()

def uByteTosByte(byte):
  if byte > 127:
    byte = byte - 255
  return byte

def get_motor_data(output_dict, con):
  end_byte_num = 0
  data_size = 0
  read_data = False
  
  while True:
    byte = con.read(1)
    byte_val = int.from_bytes(bytes = byte, byteorder  = "little", signed = False)

    if byte_val == 254:
      end_byte_num = end_byte_num + 1
    else:
      end_byte_num = 0
    if end_byte_num == 4:
      end_byte_num = 0
      read_data = True

    if read_data:
      data_size = con.read(2)
      data_size_val = int.from_bytes(bytes = data_size, byteorder  = "little", signed = False)
      data = con.read(data_size_val)
      
      right_motor_force = uByteTosByte(data[0])
      left_motor_force = uByteTosByte(data[1])
      x_servo_pos = data[2]
      x_servo_force = uByteTosByte(data[3])
      z_servo_pos = data[4]
      z_servo_force = uByteTosByte(data[5])

      output_dict["right_motor_force"] = right_motor_force
      output_dict["left_motor_force"] = left_motor_force
      output_dict["x_servo_pos"] = x_servo_pos
      output_dict["x_servo_force"] = x_servo_force
      output_dict["z_servo_pos"] = z_servo_pos
      output_dict["z_servo_force"] = z_servo_force

      return
    
def inject_mqtt_data(data_dict, mqtt_con, prefix):
  for key in data_dict:
    data = data_dict[key]
    mqtt_con.publish(prefix + "/" + key, data)

def fetch_motor_input_data(client, userdata, msg):
  motor_instruction.assign_instruction_value(msg.topic, msg.payload)

def inject_motor_instruction_data(motor_con, instruction):
  injected_data = instruction.toBytes()
  motor_con.write(injected_data)

if __name__ == "__main__":
  if len(sys.argv) != 5:
    print("[ERROR] Program arguments: <motor_port> <motor_baud_rate> <mqtt_address> <mqtt_port>.")
    exit()

  motor_port = sys.argv[1]
  motor_baud_rate = int(sys.argv[2])
  mqtt_address = sys.argv[3]
  mqtt_port = int(sys.argv[4])

  print(f"[Info] Connecting to MQTT broker on {mqtt_address}:{mqtt_port}")
  mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
  mqttc.connect(mqtt_address, mqtt_port, 60)
  mqttc.subscribe("input/motor/right_motor_force")
  mqttc.subscribe("input/motor/left_motor_force")
  mqttc.subscribe("input/motor/x_servo_force")
  mqttc.subscribe("input/motor/z_servo_force")
  mqttc.subscribe("input/motor/led_r")
  mqttc.subscribe("input/motor/led_g")
  mqttc.subscribe("input/motor/led_b")
  mqttc.on_message = fetch_motor_input_data
  mqttc.loop_start()

  print(f"\n[Info] Starting motor UART listener on port {motor_port} with rate {motor_baud_rate}.\n")
  motor_con = serial.Serial(motor_port, motor_baud_rate)
  time.sleep(2)

  while True:
    try:
      get_motor_data(sensor_dict, motor_con)
      inject_mqtt_data(sensor_dict, mqttc, "output/motor")
      inject_motor_instruction_data(motor_con, motor_instruction)
    except KeyboardInterrupt:
      print("[Info] User exit.")
      mqttc.loop_stop()
      exit(0)


