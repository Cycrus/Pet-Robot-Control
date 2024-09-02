# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG interface_name=DefaultInterface

WORKDIR /

RUN apt-get update && apt-get upgrade -y

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
