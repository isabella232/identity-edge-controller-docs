#!/bin/bash

# Environment variables
export WORK_DIR="/root/forgerock"

#
# Modify IEC Service configuration and run the install script
#
function install_iec_service() {
    echo "Installing IEC Service"
    cd ${WORK_DIR}
    tar -xzf iec-service-*.tgz
    sed -i 's/openam.example.com/am.iec.com/g' iec-config.json
    sed -i 's/openam.iecdemo.com/am.iec.com/g' iec-config.json
    ./install.sh
    cd - &>/dev/null
}

#
# Start the IEC Service if it is not already running
#
function start_iec_service() {
    if [ `pgrep -x iecservice` ] ; then
        echo "IEC Service already started"
        return 0
    fi

    /opt/forgerock/iec/bin/iecservice &
    if [ $? != 0 ] ; then
        echo "Failed to start IEC Service"
    else
        echo "IEC Service started"
    fi
}

#
# Stop the IEC Service if it is running
#
function stop_iec_service() {
    if [ `pgrep -x iecservice` ] ; then
        pkill -9 iecservice
        echo "IEC Service stopped"
    else
        echo "IEC Service not running"
    fi
}

#
# Quick install will bring the gateway environment to the state
# it would be in after the installation guide has been completed
#
function quick_install() {
    install_iec_service
    start_iec_service
}
