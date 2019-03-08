#!/bin/bash

#
# Copyright 2019 ForgeRock AS
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# Environment variables
export WORK_DIR="/root/forgerock/service"

#
# Run the IEC Service install script
#
function install_iec_service() {
    echo "Installing IEC Service"
    cd ${WORK_DIR}
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
# Quick install will install the IEC Service and start it
#
function quick_install() {
    install_iec_service
    start_iec_service
}
