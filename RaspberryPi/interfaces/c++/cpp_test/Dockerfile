# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG interface_name=DefaultInterface

WORKDIR /

RUN apt-get update && apt-get upgrade -y

RUN mkdir -p /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir -p /opt/RaspberryPi/lib/c++

# Install global dependencies
COPY deploy/scripts/global_cpp_dependencies.sh /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN /opt/RaspberryPi/interfaces/c++/${interface_name}/global_cpp_dependencies.sh

# Install specific dependencies
COPY RaspberryPi/interfaces/c++/${interface_name}/setup.sh /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN /opt/RaspberryPi/interfaces/c++/${interface_name}/setup.sh

# Copy all other files
COPY RaspberryPi/interfaces/c++/${interface_name} /opt/RaspberryPi/interfaces/c++/${interface_name}
COPY RaspberryPi/lib/c++ /opt/RaspberryPi/lib/c++

# Build and start main file
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir build
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}/build
RUN cmake ..
RUN make

CMD ["./main"]
