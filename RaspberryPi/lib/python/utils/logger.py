"""
A custom logger which uses a certain datetime format, colors the terminal, and flushes after each line.
This is required for the file logging which is piped to the stdout meachanism implemented in the framework.
"""

from datetime import datetime

WHITE = "\033[00m"
RED = "\033[91m"
YELLOW = "\033[93m"
GREEN = "\033[92m"
CYAN = "\033[96m"


class Logger:
  def __init__(self, interface_name: str):
    self._interface_name = interface_name
    self._datetime_format = "%Y-%m-%d %H:%M:%S.%f"

  def debug(self, msg: str):
    self._print(msg, "DEBUG", CYAN)

  def success(self, msg: str):
    self._print(msg, "SUCCESS", GREEN)

  def info(self, msg: str):
    self._print(msg, "INFO", WHITE)

  def warning(self, msg: str):
    self._print(msg, "WARNING", YELLOW)

  def error(self, msg: str):
    self._print(msg, "ERROR", RED)

  def _print(self, msg: str, level: str, color: str):
    log_time = datetime.now()
    log_time_str = log_time.strftime(self._datetime_format)
    print(f"{self._interface_name} | {log_time_str} {color}[{level}] {msg}{WHITE}", flush = True)

