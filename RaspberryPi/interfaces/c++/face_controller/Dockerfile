# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG interface_name=DefaultInterface

WORKDIR /

RUN apt-get update && apt-get upgrade -y && apt-get install -y build-essential cmake wget i2c-tools libcap-dev

USER $USER
RUN echo 'SUBSYSTEM=="mem", KERNEL=="mem", GROUP="kmem", MODE="0660"' | tee /etc/udev/rules.d/98-mem.rules

RUN mkdir -p /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir -p /opt/RaspberryPi/lib/c++

COPY interfaces/c++/${interface_name} /opt/RaspberryPi/interfaces/c++/${interface_name}
COPY lib/c++ /opt/RaspberryPi/lib/c++

# Install dependencies
RUN /opt/RaspberryPi/interfaces/c++/${interface_name}/setup.sh

# Build and start main file
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir build
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}/build
RUN cmake ..
RUN make
#CMD ["/bin/bash"]
CMD ["./main"]
