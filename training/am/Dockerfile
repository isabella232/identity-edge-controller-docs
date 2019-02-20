FROM tomcat:8.5-jre8

# Add AM resources
ADD resources/AM-*.war /usr/local/tomcat/webapps/openam.war
ADD resources/Amster-*.zip /tmp/amster.zip
RUN mkdir -p /opt/forgerock/amster && unzip -q /tmp/amster.zip -d /opt/forgerock/amster
ADD install-am.amster /opt/forgerock/amster/install-am.amster
ADD import-config.amster /opt/forgerock/amster/import-config.amster
ADD commands.sh /opt/forgerock/am/commands.sh
RUN chmod a+x /opt/forgerock/am/commands.sh
RUN /bin/bash -c "echo \"source /opt/forgerock/am/commands.sh\" >> /root/.bashrc"
ADD configuration /opt/forgerock/am/configuration

# Install AM
RUN /bin/bash -c "source /opt/forgerock/am/commands.sh && install_am"

# Add IEC resources
WORKDIR /root/forgerock
COPY resources/iec-am-plugin-*.tgz .
ADD resources/edge-identity-manager-*.war .

# Set bash as the default command in the new container
CMD ["bash"]
