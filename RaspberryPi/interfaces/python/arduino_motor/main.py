import serial
import struct
from interface import Interface
from arduinoconn import ArduinoSerial, ArduinoMessage


class MotorArduino(Interface):
  def __init__(self):
    super().__init__("MotorArduino")

    self.arduino_port = self.env.getValue("MOTOR_PORT")
    self.arduino_baud = self.env.getValue("MOTOR_BAUD")
    self.motor_dict = {}
    self.arduino = ArduinoSerial(self.arduino_port, self.arduino_baud, self.logger)
    self.motor_instructions = ArduinoMessage()
    self.instruction_dict = {}
    self.reset_motor_instructions(True)
    self.data_format = {
      "right_motor_force": "int8",
      "left_motor_force": "int8",
      "x_servo_pos": "uint8",
      "x_servo_force": "int8",
      "z_servo_pos": "uint8",
      "z_servo_force": "int8"}

  def close(self):
    self.mqtt_client.stop_loop()
    self.mqtt_client.close()

  def reset_motor_instructions(self, reset_values):
    if reset_values:
      self.instruction_dict = {
        "right_motor_force": 0,
        "left_motor_force": 0,
        "x_servo_force": 0,
        "z_servo_force": 0,
        "led_r": 0,
        "led_g": 0,
        "led_b": 0}
    self.motor_instructions.reset()

  def inject_motor_instructions(self):
    self.motor_instructions.add_int(self.instruction_dict["right_motor_force"], 1, True)
    self.motor_instructions.add_int(self.instruction_dict["left_motor_force"], 1, True)
    self.motor_instructions.add_int(self.instruction_dict["x_servo_force"], 1, True)
    self.motor_instructions.add_int(self.instruction_dict["z_servo_force"], 1, True)
    self.motor_instructions.add_int(self.instruction_dict["led_r"], 1, False)
    self.motor_instructions.add_int(self.instruction_dict["led_g"], 1, False)
    self.motor_instructions.add_int(self.instruction_dict["led_b"], 1, False)
    self.arduino.send_arduino_data(self.motor_instructions)
    self.reset_motor_instructions(False)

  def subscribe_motor_topics(self, client, userdata, flags, reason_code, properties):
    for key in self.instruction_dict:
      self.mqtt_client.subscribe(f"input/motor/{key}")

  def collect_motor_instructions(self, client, userdata, msg):
    for key in self.instruction_dict:
      if key in msg.topic:
        value = int(msg.payload.decode("utf-8"))
        self.instruction_dict[key] = value
    
  def main(self):
    self.arduino.connect()
    self.mqtt_client.on_connect(self.subscribe_motor_topics)
    self.mqtt_client.on_message(self.collect_motor_instructions)
    self.mqtt_client.connect()
    self.mqtt_client.start_loop(blocking = False)

    while not self.exit_event.is_set():
      _, self.motor_dict = self.arduino.receive_arduino_data(self.data_format, "little", self.exit_event)
      if self.motor_dict is not None:
        self.mqtt_client.publish("output/motor", self.motor_dict)
        self.inject_motor_instructions()

    self.arduino.close()
    self.close()


if __name__ == "__main__":
  interface = MotorArduino()
  interface.main()
  interface.exit_event.wait(interface.exit_timeout)
  interface.logger.success("Gracefully exited interface.")
