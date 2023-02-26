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
MOTOR_BAUD = 57600
MOTOR_MESSAGE = 13,0,0,0,0,0,0,0,0,254,254,254,254

TESTFILE = infrared_transmitter/infrared_transmitter.ino
TESTFILE_BOARD = arduino:avr:uno 

#-------------------------------------------------------------------------------------
# Building and Uploading instructions
#
build: build_sensor build_motor
	@echo "Finished Job."

build_sensor: sensory_system/sensory_system.ino
	@echo "Building and uploading sensory system."
	arduino --upload sensory_system/sensory_system.ino --port $(SENSORY_PORT) --board arduino:avr:mega

build_motor: motor_system/motor_system.ino
	@echo "Building and uploading motor system."
	arduino --upload motor_system/motor_system.ino --port $(MOTOR_PORT) --board arduino:avr:uno 

#-------------------------------------------------------------------------------------
# Instructions to listen to the output of the systems.
#
connect_sensor:
	@echo "Connecting to sensory system via CLI terminal."
	python3 ../UtilityScripts/sensor_connector.py $(SENSORY_PORT) $(SENSORY_BAUD)
	# minicom -D $(SENSORY_PORT) -b $(SENSORY_BAUD)

connect_motor:
	@echo "Connecting to motor system via CLI terminal."
	python3 ../UtilityScripts/motor_connector.py $(MOTOR_PORT) $(MOTOR_BAUD)
	# minicom -D $(MOTOR_PORT) -b $(MOTOR_BAUD)

#-------------------------------------------------------------------------------------
# Instructions to send messages to the motor system.
#
send_motor:
	@echo "Sending a single state message to motor system."
	python3 ../UtilityScripts/uart_sender.py $(MOTOR_PORT) $(MOTOR_BAUD) $(MOTOR_MESSAGE)

check_motor:
	@echo "Sending state message to motor system."
	python3 ../UtilityScripts/motor_check.py $(MOTOR_PORT) $(MOTOR_BAUD)

#-------------------------------------------------------------------------------------
# Instruction to build and upload test and tool sketches.
#
build_testfile:
	@echo "Building and uploading testfile."
	arduino --upload test_sketches/$(TESTFILE) --port $(MOTOR_PORT) --board $(TESTFILE_BOARD)

build_servo_ref:
	@echo "Building servo motor referencing."
	arduino --upload tools/servo_referencing/servo_referencing.ino --port $(MOTOR_PORT) --board $(TESTFILE_BOARD)

reset:
	@echo "Reset Arduino board state."
	python3 ../UtilityScripts/reset_boards.py $(SENSORY_PORT)
	python3 ../UtilityScripts/reset_boards.py $(MOTOR_PORT)