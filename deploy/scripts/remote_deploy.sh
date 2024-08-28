#!/bin/bash

# Only to be called from the root Makefile

# Store parameters
HOST=$1
USER=$2
ARCH=$3

# Build images for specific architecture
COMPOSE_DOCKER_CLI_BUILD=1 DOCKER_BUILDKIT=1 BUILD_ARCH=$ARCH docker compose pull mosquitto
COMPOSE_DOCKER_CLI_BUILD=1 DOCKER_BUILDKIT=1 BUILD_ARCH=$ARCH docker compose build

# Save all relevant docker images as tar balls
echo "Saving all relevant images as tarballs."
IMAGE_LOCATION=deploy/docker_images/${ARCH////_}
mkdir -p $IMAGE_LOCATION
docker save -o $IMAGE_LOCATION/mosquitto-prebuilt.tar eclipse-mosquitto:latest

PREFIX="pet-robot-"
images=$(docker images --format "{{.Repository}}:{{.Tag}}" | grep "^$PREFIX")
for image in $images; do
    TARBALL_NAME=$(echo $image | sed 's/[\/:]/_/g').tar
    echo "Saving image $image to $IMAGE_LOCATION/$TARBALL_NAME"
    docker save -o $IMAGE_LOCATION/$TARBALL_NAME $image
done

# Upload all tarball images to the host machine
echo "Uploading the images to the host machine."
REMOTE_USER=$USER
REMOTE_HOST=$HOST
REMOTE_IMAGE_DIR=/tmp/pet-robot_docker-images

sftp $REMOTE_USER@$REMOTE_HOST <<EOF
  mkdir $REMOTE_IMAGE_DIR
  cd $REMOTE_IMAGE_DIR
  put -r $IMAGE_LOCATION
  lcd deploy/scripts
  put load_docker_images.sh
EOF

ssh $REMOTE_USER@$REMOTE_HOST <<EOF
  cd $REMOTE_IMAGE_DIR
  ./load_docker_images.sh
EOF
