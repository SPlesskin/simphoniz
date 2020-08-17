FROM debian:9

# Add the installer to this Docker image
COPY *.deb /tmp

# Install Simphoniz (with root permissions)
RUN apt-get update && \
    apt-get install -y /tmp/*.deb && \
    ln -s /usr/bin/simphoniz/simphoniz /usr/local/bin/simphoniz

# Create a new user and login as that user
ENV user erwan
RUN useradd -ms /bin/bash ${user}
USER ${user}
WORKDIR /home/${user}

#
# NOW SIMPHONIZ CAN BE EXECUTED WITH A NON-ROOT USER.
#
