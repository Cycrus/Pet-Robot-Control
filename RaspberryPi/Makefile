build:
	docker build --build-arg interface_name=ST7735_face_engine -f interfaces/c++/ST7735_face_engine/Dockerfile -t robot/face .

run:
	docker run --privileged \
	--device /dev/mem:/dev/mem \
  --device /dev/gpiomem:/dev/gpiomem \
  --device /dev/spidev0.0:/dev/spidev0.0 \
  --device /dev/spidev0.1:/dev/spidev0.1 \
	-v /sys/bus:/sys/bus -it robot/face