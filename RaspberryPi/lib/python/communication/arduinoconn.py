"""
A class to connect to and handle communication with an Arduino on a
specfied serial port.
"""

import serial
import struct
import threading
from logger import Logger
from typing import Optional, Tuple


class ArduinoMessage:
  def __init__(self, endianness: str = "little"):
    self.msg_bytes = b""
    self.msg_len = 2
    self.finished = False
    self.endianness = endianness

  def get_bytes(self):
    return self.msg_bytes
  
  def reset(self):
    """
    Resets and empties the message buffer. Can be rewritten afterwards.
    """
    self.msg_bytes = b""
    self.msg_len = 2
    self.finished = False

  def add_int(self, value: int, size: int, signed: bool = False) -> bool:
    """
    Concatenates an integer to the message.
    :param value: The integer to append.
    :param size: In bytes the size of the integer bytes to append.
    :param signed: If true, the integer is interpreted as signed.
    :return: True if everything went ok.
    """
    if self.finished:
      return False
    if size != 1 and size != 2 and size != 4 and size != 8:
      return False

    self.msg_bytes += value.to_bytes(size, byteorder = self.endianness, signed = signed)
    self.msg_len += size
    return True

  def add_float(self, value: float, size: int) -> bool:
    """
    Concatenates a float to the message.
    :param value: The float to append.
    :param size: In bytes the size of the float bytes to append.
    :return: True if everything went ok.
    """
    if self.finished:
      return False
    if size != 2 and size != 4 and size != 8:
      return False

    if self.endianness == "little":
      sign = "<"
    elif self.endianness == "big":
      sign = ">"
    else:
      return False

    if size == 2:
      self.msg_bytes += struct.pack(f"{sign}e", value)
    elif size == 4:
      self.msg_bytes += struct.pack(f"{sign}f", value)
    elif size == 8:
      self.msg_bytes += struct.pack(f"{sign}d", value)

    self.msg_len += size
    return True

  def finish(self, msg_start_signature: int, msg_start_signature_number: int) -> bool:
    """
    Prepares and finishes the message in order to be sent. After calling this method, the message is
    frozen and cannot be modified anymore.
    :param msg_start_signature: The signature which is always appended at the start of every message.
    :param msg_start_signature_number: The amount of times the message signature is appended.
    :return: True if everything went ok.
    """
    if self.finished:
      return False
    
    self.msg_len += msg_start_signature_number
    
    self.msg_bytes = bytes([msg_start_signature] * msg_start_signature_number) +\
                     self.msg_len.to_bytes(2, byteorder = self.endianness, signed = False) +\
                     self.msg_bytes
    self.finished = True
    return True


class ArduinoSerial:
  def __init__(self, port: str, baud: int, logger: Logger):
    self.arduino = None
    self.port = port
    self.baud = baud
    self.logger = logger
    self.msg_start_signature = 254
    self.msg_start_signature_number = 4

  def connect(self):
    """
    Connects the process to an Arduino.
    """
    self.logger.info(f"Connecting to Arduino at {self.port} using a baud of {self.baud}.")
    try:
      if self.arduino is None:
        self.arduino = serial.Serial(self.port, self.baud, timeout = 1, write_timeout = 1)
        self.logger.success("Successfully connected to Arduino.")
      else:
        self.logger.warning("Arduino already connected. Not connecting again.")
    except Exception as e:
      self.logger.error(f"Cannot connect to Arduino. {e}.")
      self.arduino = None

  def close(self):
    """
    Closes an opened Arduino connection.
    """
    self.logger.info(f"Closing Arduino connection at {self.port}")
    try:
      if self.arduino is not None:
        self.arduino.close()
        self.arduino = None
        self.logger.success(f"Successfully closed Arduino connection.")
      else:
        self.warning("Arduino connection already closes. Not closing again.")
    except Exception as e:
      self.logger.error(f"Arduino connection could not be closed. {e}.")

  def receive_bytes(self, size: int) -> Optional[bytes]:
    """
    Receives a number of unconverted bytes from the Arduino.
    :param size: The number of bytes to receive.
    :return: The bytes received. None if something went wrong.
    """
    if size == 0:
      self.logger.error(f"Cannot receive a size of 0 bytes.")
      return None
    try:
      byte_data = self.arduino.read(size)
      return byte_data
    except Exception as e:
      self.logger.error(f"Cannot receive bytes from Arduino. {e}.")
      return None
    
  def receive_string(self, size: int, encoding: str = "utf-8") -> Optional[str]:
    """
    Receives a fixed size string from the Arduino.
    :param size: The number of characters to receive.
    :param encoding: The encoding of the string. Typically is "utf-8".
    :return: The string received. None if something went wrong.
    """
    byte_data = self.receive_bytes(size)
    try:
      return byte_data.decode(encoding)
    except Exception as e:
      self.logger.error(f"Cannot cast bytes {byte_data} of size {size} to {encoding}-string. {e}.")
      return None
    
  def receive_int(self, size: int = 4, endianness: str = "little", signed: bool = True) -> Optional[int]:
    """
    Receives an integer of variable size from the Arduino.
    :param size: The size of the integer in bytes.
    :param endianness: The endianness of the integer. Can be little or big.
    :param signed: If true, the bytes of the string are interpreted as signed.
    :return: The integer received. None if something went wrong.
    """
    if size != 1 and size != 2 and size != 4 and size != 8:
      self.logger.error(f"Incorrect size of {size} given to receive integer from Arduino.")
      return None

    byte_data = self.receive_bytes(size)
    try:
      return int.from_bytes(bytes = byte_data, byteorder  = endianness, signed = signed)
    except Exception as e:
      self.logger.error(f"Cannot cast bytes {byte_data} of size {size} to integer. {e}.")
      return None
    
  def receive_float(self, size: int = 4, endianness: str = "little") -> Optional[float]:
    """
    Receives a float of variable size from the Arduino.
    :param size: The size of the float in bytes.
    :param endianness: The endianness of the float. Can be little or big.
    :return: The float received. None if something went wrong.
    """
    if size != 2 and size != 4 and size != 8:
      self.logger.error(f"Incorrect size of {size} given to receive float from Arduino.")
      return None

    if endianness == "little":
      sign = "<"
    elif endianness == "big":
      sign = ">"
    else:
      self.logger.error(f"Incorrect endianness of {endianness} given to receive float from Arduino.")
      return None
    
    byte_data = self.receive_bytes(size)
    try:
      if size == 2:
        return struct.unpack(f"{sign}e", byte_data)[0]
      if size == 4:
        return struct.unpack(f"{sign}f", byte_data)[0]
      elif size == 8:
        return struct.unpack(f"{sign}d", byte_data)[0]
    except Exception as e:
      self.logger.error(f"Cannot cast bytes {byte_data} of size {size} to float. {e}.")
      return None
    
  def receive_batch(self, format_dict: dict, check_size: int,
                    endianness: str = "little") -> Tuple[bool, Optional[dict]]:
    """
    Receives a batch of data with a predefined format and returns a populated
    dictionary filled with the data.
    :param format_dict: The format dictionary of the data to receive. The keys
                        contain the names of the fields to populate with data,
                        the values the format specifiers. Following specifiers
                        are legit:
                          int8, int16, int32, int64,
                          uint8, uint16, uint32, uint64,
                          float16, float32, float64,
                          bytes:byte-size
                          string:string-size
    :param check_size: The number of expected bytes. Can be used to check if the
                       format specifier fulfills the data expectations.
    :param endianness: The endianness of the data. Can be little or big.
    :param signed: If true, the bytes of the string are interpreted as signed.
    :return: A Tuple with a boolean indicating if the expected size of check_size
             has been received, and the data. The data is None, if an error occured.
    """
    data_dict = {}
    for name in format_dict:
      try:
        format = format_dict[name]
        if format == "int8":
          data_dict[name] = self.receive_int(1, endianness, True)
          check_size -= 1
        elif format == "int16":
          data_dict[name] = self.receive_int(2, endianness, True)
          check_size -= 2
        elif format == "int32":
          data_dict[name] = self.receive_int(4, endianness, True)
          check_size -= 4
        elif format == "int64":
          data_dict[name] = self.receive_int(8, endianness, True)
          check_size -= 8

        elif format == "uint8":
          data_dict[name] = self.receive_int(1, endianness, False)
          check_size -= 1
        elif format == "uint16":
          data_dict[name] = self.receive_int(2, endianness, False)
          check_size -= 2
        elif format == "uint32":
          data_dict[name] = self.receive_int(4, endianness, False)
          check_size -= 4
        elif format == "uint64":
          data_dict[name] = self.receive_int(8, endianness, False)
          check_size -= 8

        elif format == "float16":
          data_dict[name] = self.receive_float(2, endianness)
          check_size -= 2
        elif format == "float32":
          data_dict[name] = self.receive_float(4, endianness)
          check_size -= 4
        elif format == "float64":
          data_dict[name] = self.receive_float(8, endianness)
          check_size -= 8

        elif "string" in format:
          str_size = format.split(":")[1]
          data_dict[name] = self.receive_string(str_size)
          check_size -= str_size

        elif "bytes" in format:
          byte_size = format.split(":")[1]
          data_dict[name] = self.receive_bytes(byte_size)
          check_size -= byte_size

      except Exception as e:
        self.logger.error(f"Cannot receive batch of data with format {format_dict} from Arduino. {e}.")
        self.logger.error(f"Issue was: {name} - {format}.")
        return False, None
    
    if check_size != 0:
      self.logger.warning(f"Check size of batch receive is invalid: {check_size} bytes left.")
    return (check_size == 0), data_dict
    
  def receive_arduino_data(self, format_dict: dict, endianness = "little",
                           stop_event: Optional[threading.Event] = None) -> Tuple[bool, Optional[dict]]:
    """
    Receives a batch of data using a predefined Arduino serial protocol. The protocol waits for a specified
    number of signature values (currently 4 times 245) and then starts to receive 2 bytes of length followed
    by the data itself. For a description of the format_dict, look into the function receive_batch().
    :param format_dict: The data format descriptor. Look it up in the function receive_batch().
    :param endianness: The endianness of all data. Can be little or big.
    :param stop_event: The stop event to listen to for preemtive termination of the receiving loop.
    :return: A Tuple with a boolean indicating if the sent data length matches the size indicated by the
             format_dict.
    """
    start_byte_num = 0
    read_data = False

    while True:
      if stop_event is not None:
        if stop_event.is_set():
          break

      byte = self.receive_int(1, endianness = endianness, signed = False)

      if byte == self.msg_start_signature:
        start_byte_num = start_byte_num + 1
      else:
        start_byte_num = 0
      if start_byte_num == self.msg_start_signature_number:
        start_byte_num = 0
        read_data = True

      if read_data:
        data_size = self.receive_int(2, endianness = endianness, signed = False)
        received_data = self.receive_batch(format_dict, data_size, endianness)
        return received_data
      
    return True, None

  def send_arduino_data(self, message: ArduinoMessage) -> bool:
    """
    Sends a well formed message to the Arduino.
    :param message: The message to send. Should be populated beforehand with data.
    :return: True if everything went ok.
    """
    try:
      if message.msg_len <= 0:
        self.logger.error(f"Cannot send an empty message to the Arduino on port {self.port}.")
        return False
      message.finish(self.msg_start_signature, self.msg_start_signature_number)
      self.arduino.write(message.get_bytes())
      return True
    except Exception as e:
      self.logger.error(f"Could not send Arduino message {message.get_bytes()} to Arduino on port {self.port}. {e}.")
      return False
