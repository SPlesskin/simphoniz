#!/bin/bash

#
# NOTE: THIS SCRIPT SHOULD BE RUN WITH ROOT PRIVILEGES.
#
# FOR MORE DETAILS PLEASE SEE https://docs.docker.com/engine/install/linux-postinstall/.
#

# Copy the installer in the current directory (a.k.a. Docker build context)
cp ../../../../build/*.deb .

# Build a Docker image and run it as a container
TAG=erwan/debian-simphoniz:1.0
SHELL=/bin/bash

docker build -t $TAG . ; rm -f *.deb
docker run --rm -ti $TAG $SHELL
