FROM ubuntu:16.04

RUN apt-get update --yes && \
    apt-get install --yes \
    curl \
    build-essential \
    zip \
    git \
    vim && \
    apt-get clean --yes

# Install Go and set variables
RUN mkdir -p /usr/local/lib
ADD https://dl.google.com/go/go1.12.linux-amd64.tar.gz /tmp
RUN tar xf /tmp/go1.12.linux-amd64.tar.gz -C /usr/local/lib
ENV GOROOT /usr/local/lib/go
ENV PATH /usr/local/lib/go/bin:$PATH

# Add IEC resources
WORKDIR /root/forgerock
ADD resources/iec-sdk-linux-x86_64-lr-richos-*.tgz sdk
ADD resources/iec-service-linux-x86_64-lr-richos-*.tgz service
ADD resources/iec-config.json service/iec-config.json
ADD commands.sh /opt/forgerock/iec/commands.sh
RUN chmod a+x /opt/forgerock/iec/commands.sh
RUN /bin/bash -c "echo \"source /opt/forgerock/iec/commands.sh\" >> /root/.bashrc"

# Set bash as the default command in the new container
CMD ["bash"]
