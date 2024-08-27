# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG interface_name=DefaultInterface
ENV INTERFACE_NAME=${interface_name}

WORKDIR /

RUN mkdir -p /opt/RaspberryPi/interfaces/c++/${interface_name}
RUN mkdir -p /opt/RaspberryPi/lib/c++

COPY interfaces/c++/${interface_name} /opt/RaspberryPi/interfaces/c++/${interface_name}
COPY lib/c++ /opt/RaspberryPi/interfaces/lib
WORKDIR /opt/RaspberryPi/interfaces/c++/${interface_name}

RUN apt-get update && apt-get install -y build-essential

RUN mkdir build
WORKDIR build
RUN cmake ..
RUN make
CMD ["./main"]