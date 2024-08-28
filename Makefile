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

create_network:
	docker network create external-net

run_docker:
	sudo docker run --privileged \
	--device /dev/mem \
  --device /dev/gpiomem \
	-v /sys/class/gpio:/sys/class/gpio \
	-it pet-robot-control-face_controller

#-------------------------------------------------------------------------------------
# Building and Uploading instructions
#
build: build_sensor build_motor build_raspi
	@echo "Finished Job."

build_sensor:
	$(MAKE) -C Arduino/ build_sensor

build_motor:
	$(MAKE) -C Arduino/ build_motor
	
build_raspi:
	$(MAKE) -C RaspberryPi/c++/ tests

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

connect_sensor_mqtt:
	@echo "Connecting to Arduinos and forwarding to MQTT broker."
	python3 UtilityScripts/mqtt_sensor_injector.py $(SENSORY_PORT) $(SENSORY_BAUD) $(MQTT_ADDRESS) $(MQTT_PORT)

connect_motor_mqtt:
	@echo "Connecting to Arduinos and forwarding to MQTT broker."
	python3 UtilityScripts/mqtt_motor_injector.py $(MOTOR_PORT) $(MOTOR_BAUD) $(MQTT_ADDRESS) $(MQTT_PORT)

#-------------------------------------------------------------------------------------
# Instruction to build and upload test and tool sketches.
#
build_servo_ref:
	$(MAKE) -C Arduino/ build_servo_ref

arduino_reset:
	@echo "Reset Arduino board state."
	python3 UtilityScripts/reset_boards.py $(SENSORY_PORT)
	python3 UtilityScripts/reset_boards.py $(MOTOR_PORT)