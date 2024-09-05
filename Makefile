#-----------------------------------------------------------------------------------------------------------------------
#
# Makefile for Pet Robot Arduino Sketches
#
# Author: Cyril Marx
# Date: February 2023
#
#-----------------------------------------------------------------------------------------------------------------------

ifneq (,$(wildcard ./.env))
    include .env
    export
endif

setup:
ifeq ($(BUILD_LOCAL), 0)
	./deploy/scripts/remote_setup.sh $(BUILD_HOST) $(BUILD_USER)
else
	./deploy/scripts/local_setup.sh
endif

build:
ifeq ($(BUILD_LOCAL), 0)
	./deploy/scripts/remote_docker_deploy.sh $(BUILD_HOST) $(BUILD_USER) $(BUILD_ARCHITECTURE)
else
	./deploy/scripts/local_docker_deploy.sh
endif

run_docker:
	sudo docker run --privileged \
	--device /dev/mem \
  --device /dev/gpiomem \
	-v /sys/class/gpio:/sys/class/gpio \
	-it pet-robot-control-face_controller

#-------------------------------------------------------------------------------------
# Building and Uploading instructions
#
arduino_build: build_sensor build_motor
	@echo "Finished Job."

arduino_build_sensor:
	./deploy/scripts/arduino_deploy.sh Arduino/sensory_system/sensory_system.ino $(SENSORY_BOARD) $(SENSORY_PORT)

arduino_build_motor:
	./deploy/scripts/arduino_deploy.sh Arduino/motor_system/motor_system.ino $(MOTOR_BOARD) $(MOTOR_PORT)

#-------------------------------------------------------------------------------------
# Instructions to connect to the Arduino systems.
#
connect_sensor:
	@echo "Connecting to sensory system via CLI terminal."
	python3 UtilityScripts/sensor_connector.py $(SENSORY_PORT) $(SENSORY_BAUD)
	# minicom -Dsensory_system/sensory_system.ino $(SENSORY_PORT) -b $(SENSORY_BAUD)

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
	./deploy/scripts/arduino_deploy.sh Arduino/tools/servo_referencing/servo_referencing.ino $(MOTOR_BOARD) $(MOTOR_PORT)

build_rfid_writer:
	./deploy/scripts/arduino_deploy.sh Arduino/tools/rfid_writer/rfid_writer.ino $(SENSORY_BOARD) $(SENSORY_PORT)

arduino_reset:
	@echo "Reset Arduino board state."
	python3 UtilityScripts/reset_boards.py $(SENSORY_PORT)
	python3 UtilityScripts/reset_boards.py $(MOTOR_PORT)