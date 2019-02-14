FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI_append += " \
                   file://iecservice \
                   file://libiecclient.so \
                   file://libsodium.so \
                   file://libzmq.so \
                   file://libstdc++.so \
                   "

do_install_append() {
    # refresh the iec service binary and libs
    install -d ${D}/opt/forgerock/iec/lib
    install -m 0644 ${WORKDIR}/libsodium.so ${D}/opt/forgerock/iec/lib/
    install -m 0644 ${WORKDIR}/libzmq.so ${D}/opt/forgerock/iec/lib/
    install -d ${D}/opt/forgerock/iec/bin
    install -m 0755 ${WORKDIR}/iecservice ${D}/opt/forgerock/iec/bin/
    # need the std libc library for iec clients
    install -m 0644 ${WORKDIR}/libstdc++.so ${D}/opt/forgerock/iec/lib/
    # refresh the iec client lib
    install -m 0644 ${WORKDIR}/libiecclient.so ${D}/opt/forgerock/iec/lib/
}

INSANE_SKIP_${PN} = "ldflags"

FILES_${PN} += " \
                /opt/forgerock/iec/bin/iecservice \
                /opt/forgerock/iec/lib/libiecclient.so \
                /opt/forgerock/iec/lib/libsodium.so \
                /opt/forgerock/iec/lib/libzmq.so \
                /opt/forgerock/iec/lib/libstdc++.so \
               "
