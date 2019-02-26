FROM tomcat:8.5-jre8

ENV CATALINA_HOME /usr/local/tomcat
ENV PATH $CATALINA_HOME/bin:$PATH

# The default home for IG config. To set a different location, override these values.
ENV IG_INSTANCE_DIR /var/openig

# Remove unecessary information from Tomcat
RUN rm -fr webapps/*

# Add the downloaded .war file to the working directory
ADD resources/openig.war /tmp/openig.war

# Add OpenIG configuration from /var/openig.
ADD custom-config /var/openig

RUN unzip /tmp/openig.war -d /usr/local/tomcat/webapps/ROOT \
 && rm -f /tmp/*zip

WORKDIR $IG_INSTANCE_DIR
