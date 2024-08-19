#-----------------------------------------------------------------------------------------------------------------------
#
# Makefile for Pet Robot Arduino Sketches
#
# Author: Cyril Marx
# Date: February 2023
#
#-----------------------------------------------------------------------------------------------------------------------

SENSORY_PORT = /dev/ttyACM0
MOTOR_PORT = /dev/ttyACM1

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

build_servo_ref:
	@echo "Building servo motor referencing."
	arduino --upload tools/servo_referencing/servo_referencing.ino --port $(MOTOR_PORT) --board $(TESTFILE_BOARD)