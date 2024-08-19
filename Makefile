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

MQTT_ADDRESS = localhost
MQTT_PORT = 1883

#-------------------------------------------------------------------------------------
# Building and Uploading instructions
#
build: build_sensor build_motor
	@echo "Finished Job."

build_sensor:
	$(MAKE) -C Arduino/ build_sensor

build_motor:
	$(MAKE) -C Arduino/ build_motor

#-------------------------------------------------------------------------------------
# Instructions to connect to the Arduino systems.
#
connect_sensor:
	@echo "Connecting to sensory system via CLI terminal."
	python3 UtilityScripts/sensor_connector.py $(SENSORY_PORT) $(SENSORY_BAUD)
	# minicom -D $(SENSORY_PORT) -b $(SENSORY_BAUD)

connect_motor:
	@echo "Connecting to motor system via CLI terminal."
	python3 UtilityScripts/motor_connector.py $(MOTOR_PORT) $(MOTOR_BAUD)
	# minicom -D $(MOTOR_PORT) -b $(MOTOR_BAUD)

connect_mqtt:
	@echo "Connecting to Arduinos and forwarding to MQTT broker."
	python3 UtilityScripts/mqtt_test_injector.py $(SENSORY_PORT) $(SENSORY_BAUD) $(MOTOR_PORT) $(MOTOR_BAUD) $(MQTT_ADDRESS) $(MQTT_PORT)

#-------------------------------------------------------------------------------------
# Instructions to send messages to the motor system.
#
send_motor:
	@echo "Sending a single state message to motor system."
	python3 UtilityScripts/uart_sender.py $(MOTOR_PORT) $(MOTOR_BAUD) $(MOTOR_MESSAGE)

check_motor:
	@echo "Sending state message to motor system."
	python3 UtilityScripts/motor_check.py $(MOTOR_PORT) $(MOTOR_BAUD)

#-------------------------------------------------------------------------------------
# Instruction to build and upload test and tool sketches.
#
build_servo_ref:
	$(MAKE) -C Arduino/ build_servo_ref

reset:
	@echo "Reset Arduino board state."
	python3 UtilityScripts/reset_boards.py $(SENSORY_PORT)
	python3 UtilityScripts/reset_boards.py $(MOTOR_PORT)