# syntax=docker/dockerfile:1

FROM ubuntu:22.04

ARG interface_name=DefaultInterface

WORKDIR /

RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y python3 python3-pip

RUN mkdir -p /opt/RaspberryPi/interfaces/python/${interface_name}
RUN mkdir -p /opt/RaspberryPi/lib/python

# Install global dependencies
COPY deploy/scripts/global_python_dependencies.sh /opt/RaspberryPi/interfaces/python/${interface_name}
RUN /opt/RaspberryPi/interfaces/python/${interface_name}/global_python_dependencies.sh

# Install specific dependencies
COPY interfaces/python/${interface_name}/setup.sh /opt/RaspberryPi/interfaces/python/${interface_name}
RUN /opt/RaspberryPi/interfaces/python/${interface_name}/setup.sh

# Copy all other files
COPY interfaces/python/${interface_name} /opt/RaspberryPi/interfaces/python/${interface_name}
COPY lib/python /opt/RaspberryPi/lib/pyton

CMD ["./run.sh", "/opt/RaspberryPi/interfaces/python/${interface_name} /opt/RaspberryPi/lib/python"]
