build: build_sensor
	@echo "Finished Job."

build_sensor: sensory_system/sensory_system.ino
	@echo "Building and uploading sensory system."
	arduino --upload sensory_system/sensory_system.ino --port /dev/ttyACM0

connect_sensor:
	@echo "Connecting to sensory system via CLI terminal."
	minicom -D /dev/ttyACM0 -b 19200