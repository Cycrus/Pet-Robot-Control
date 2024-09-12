#-----------------------------------------------------------------------------------------------------------------------
#
# Makefile for Pet Robot Project.
# Set the .env variables to build locally or remotely.
# Set the INTERFACE env variable to build/run/stop a certain interface, or leave it to build/run/stop everything.
#
# Author: Cyril Marx
# Date: September 2024
#
#-----------------------------------------------------------------------------------------------------------------------

INTERFACE ?= all

# Reads the .env file and sets all environment variables.
ifneq (,$(wildcard ./.env))
    include .env
    export
endif

#-------------------------------------------------------------------------------------
# Setup rules
# The following sets up the whole local or remote system for everything you need.
# A remote system can only be deployed dockerized, a local system can be
# deployed dockerized and on bare metal.
# make setup      ... sets up the PC to start developing/launching     
#
setup:
ifeq ($(BUILD_LOCAL), 0)
	./deploy/scripts/remote_setup.sh $(BUILD_HOST) $(BUILD_USER)
else
	./deploy/scripts/local_setup.sh
endif

#-------------------------------------------------------------------------------------
# Undockerized, local rules
# The following rules all use no dockerization, except of the Mosquitto MQTT broker.
# make ibuild     ... Builds a single or all c++ interfaces
# make irun       ... Runs a single or all interfaces
# make istop      ... Stops a single or all interfaces
#
ibuild:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only build undockerized interfaces with BUILD_LOCAL=1."
else
	./deploy/scripts/local_build.sh $(INTERFACE)
endif
	
irun:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only run undockerized interfaces with BUILD_LOCAL=1."
else
	./deploy/scripts/local_run.sh $(INTERFACE)
endif

ireset:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only reset undockerized interfaces with BUILD_LOCAL=1."
else
	./deploy/scripts/local_stop.sh $(INTERFACE)
	./deploy/scripts/local_run.sh $(INTERFACE)
endif

iwatch:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only watch undockerized interfaces with BUILD_LOCAL=1."
else
	./deploy/scripts/watch_interface.sh $(INTERFACE)
endif

istate:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only check undockerized interface states with BUILD_LOCAL=1."
else
	./deploy/scripts/check_interface_state.sh $(INTERFACE)
endif

istop:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only stop undockerized interfaces with BUILD_LOCAL=1."
else
	./deploy/scripts/local_stop.sh $(INTERFACE)
endif
	

#-------------------------------------------------------------------------------------
# Dockerized, local and remote rules
# make idockerize ... Builds and launches all interfaces in a dockerized manner
#
idockerize:
ifeq ($(BUILD_LOCAL), 0)
	./deploy/scripts/remote_docker_deploy.sh $(BUILD_HOST) $(BUILD_USER) $(BUILD_ARCHITECTURE)
else
	./deploy/scripts/local_docker_deploy.sh
endif

#-------------------------------------------------------------------------------------
# Building and Uploading Arduino rules
#
arduino_build: build_sensor build_motor
	@echo "Finished Job."

arduino_build_sensor:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only build and deploy sensor arduino system with BUILD_LOCAL=1."
else
	./deploy/scripts/arduino_deploy.sh Arduino/sensory_system/sensory_system.ino $(SENSORY_BOARD) $(SENSORY_PORT)
endif
	

arduino_build_motor:
ifeq ($(BUILD_LOCAL), 0)
	@echo "Can only build and deploy motor arduino system with BUILD_LOCAL=1."
else
	./deploy/scripts/arduino_deploy.sh Arduino/motor_system/motor_system.ino $(MOTOR_BOARD) $(MOTOR_PORT)
endif

#-------------------------------------------------------------------------------------
# Rules to build and upload test and tool sketches.
#
arduino_build_servo_ref:
	./deploy/scripts/arduino_deploy.sh Arduino/tools/servo_referencing/servo_referencing.ino $(MOTOR_BOARD) $(MOTOR_PORT)

arduino_build_rfid_writer:
	./deploy/scripts/arduino_deploy.sh Arduino/tools/rfid_writer/rfid_writer.ino $(SENSORY_BOARD) $(SENSORY_PORT)

arduino_reset:
	@echo "Reset Arduino board state."
	python3 UtilityScripts/reset_boards.py $(SENSORY_PORT)
	python3 UtilityScripts/reset_boards.py $(MOTOR_PORT)