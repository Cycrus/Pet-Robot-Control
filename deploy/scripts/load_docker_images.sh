#!/bin/bash

#
# Loads all tared docker images in ./deploy/docker_images into the system.
# ./load_docker_images.sh
#

# Define the base directory (current directory)
BASE_DIR=$(pwd)/deploy/docker_images

# Find all .tar files in the current directory and all subdirectories
tarballs=$(find "$BASE_DIR" -type f -name "*.tar")

# Check if any tarballs were found
if [ -z "$tarballs" ]; then
    echo "No tarballs found in $BASE_DIR or its subdirectories."
    exit 1
fi

# Loop over each found tarball and load it
for tarball in $tarballs; do
    echo "Loading Docker image from $tarball..."
    docker load -i "$tarball"
done

echo "All Docker images have been loaded."
