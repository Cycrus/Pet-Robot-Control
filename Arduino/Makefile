#-----------------------------------------------------------------------------------------------------------------------
#
# Makefile for Pet Robot Arduino Sketches
#
# Author: Cyril Marx
# Date: February 2023
#
#-----------------------------------------------------------------------------------------------------------------------

SENSORY_PORT = /dev/ttyACM0
SENSORY_BAUD = 115200

MOTOR_PORT = /dev/ttyACM1
MOTOR_BAUD = 115200

TESTFILE = infrared_transmitter/infrared_transmitter.ino
TESTFILE_BOARD = arduino:avr:uno 

build: build_sensor build_motor
	@echo "Finished Job."

build_sensor: sensory_system/sensory_system.ino
	@echo "Building and uploading sensory system."
	arduino --upload sensory_system/sensory_system.ino --port $(SENSORY_PORT) --board arduino:avr:mega

build_motor: motor_system/motor_system.ino
	@echo "Building and uploading motor system."
	arduino --upload motor_system/motor_system.ino --port $(MOTOR_PORT) --board arduino:avr:uno 

connect_sensor:
	@echo "Connecting to sensory system via CLI terminal."
	python3 ../UtilityScripts/sensor_listener.py $(SENSORY_PORT) $(SENSORY_BAUD)
	# minicom -D $(SENSORY_PORT) -b $(SENSORY_BAUD)

connect_motor:
	@echo "Connecting to motor system via CLI terminal."
	python3 ../UtilityScripts/uart_listener.py $(MOTOR_PORT) $(MOTOR_BAUD)
	# minicom -D $(MOTOR_PORT) -b $(MOTOR_BAUD)

build_testfile:
	@echo "Building and uploading testfile."
	arduino --upload test_sketches/$(TESTFILE) --port $(MOTOR_PORT) --board $(TESTFILE_BOARD)