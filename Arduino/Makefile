#-----------------------------------------------------------------------------------------------------------------------
#
# Makefile for Pet Robot Arduino Sketches
#
# Author: Cyril Marx
# Date: February 2023
#
#-----------------------------------------------------------------------------------------------------------------------

SENSORY_PORT = /dev/ttyACM0
SENSORY_BAUD = 19200

MOTOR_PORT = /dev/ttyACM1
MOTOR_BAUD = 9600

build: build_sensor
	@echo "Finished Job."

build_sensor: sensory_system/sensory_system.ino
	@echo "Building and uploading sensory system."
	arduino --upload sensory_system/sensory_system.ino --port $(SENSORY_PORT)

connect_sensor:
	@echo "Connecting to sensory system via CLI terminal."
	python3 ../UtilityScripts/uart_listener.py $(SENSORY_PORT) $(SENSORY_BAUD)
	# minicom -D $(SENSORY_PORT) -b $(SENSORY_BAUD)