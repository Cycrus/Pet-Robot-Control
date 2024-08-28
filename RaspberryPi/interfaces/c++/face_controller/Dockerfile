# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG interface_name=DefaultInterface

WORKDIR /

RUN apt-get update && apt-get upgrade -y && apt-get install -y build-essential cmake wget i2c-tools libcap-dev

USER $USER
RUN echo 'SUBSYSTEM=="mem", KERNEL=="mem", GROUP="kmem", MODE="0660"' | tee /etc/udev/rules.d/98-mem.rules

# Install SPI dependency
WORKDIR /root
RUN wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.71.tar.gz
RUN tar xvfz bcm2835-1.71.tar.gz
WORKDIR /root/bcm2835-1.71
RUN ./configure
RUN make
RUN make install

# Install i2c dependency
WORKDIR /root
RUN wget https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/i2c-tools-4.3.tar.xz
RUN tar -xf i2c-tools-4.3.tar.xz
WORKDIR /root/i2c-tools-4.3
RUN make
RUN make install

RUN mkdir -p /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir -p /opt/RaspberryPi/lib/c++

COPY interfaces/c++/${interface_name} /opt/RaspberryPi/interfaces/c++/${interface_name}
COPY lib/c++ /opt/RaspberryPi/lib/c++

# Build and start main file
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir build
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}/build
RUN cmake ..
RUN make
#CMD ["./main"]
