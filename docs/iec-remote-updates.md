## ForgeRock Identity Edge Controller Remote Updates

Although ForgeRock does not provide an Over The Air (OTA) remote update system, it is important to show that the IEC
Service and SDK can be updated remotely. There are already many frameworks proven for remote update, so to use the 
[Mender update system](https://docs.mender.io/) as an example for remote OTA updates :

* download the repos and build the project, following the [Mender documentation](https://docs.mender.io/1.7/artifacts)
* be familiar with the manual for [Yocto / OpenEmbedded project](https://www.yoctoproject.org/docs/) and bitbake
* once the build is successfully building `.mender` artifact files, add the IEC Service and SDK files using bitbake:
1. use an append file in a layer within the Yocto project, for example the `hello-mender` layer
1. add a bitbake append recipe such as [hello-mender%.bbappend](attachments/hello-mender%25.bbappend)
1. rerun the bitbake build `bitbake core-image-base`
1. upload the `.mender` artifact to a Mender server, such as [Hosted Mender](https://hosted.mender.io/ui/#/)
1. the artifact can now be deployed to devices, see the [Mender Help](https://hosted.mender.io/ui/#/help)

Example recipe:
```
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/Apache-2.0;md5=89aea4e17d99a7cacdbeed46a0096b10"

SRC_URI_append += " \
                   file://iecservice \
                   file://libiecclient.so \
                   file://libsodium.so \
                   file://libzmq.so \
                   "

do_install_append() {
    # refresh the iec service binary and libs
    install -d ${D}/opt/forgerock/iec/lib
    install -m 0644 ${WORKDIR}/libsodium.so ${D}/opt/forgerock/iec/lib/
    install -m 0644 ${WORKDIR}/libzmq.so ${D}/opt/forgerock/iec/lib/
    install -d ${D}/opt/forgerock/iec/bin
    install -m 0755 ${WORKDIR}/iecservice ${D}/opt/forgerock/iec/bin/
    # refresh the iec client lib
    install -m 0644 ${WORKDIR}/libiecclient.so ${D}/opt/forgerock/iec/lib/
}

INSANE_SKIP_${PN} = "ldflags"

FILES_${PN} += " \
                /opt/forgerock/iec/bin/iecservice \
                /opt/forgerock/iec/lib/libiecclient.so \
                /opt/forgerock/iec/lib/libsodium.so \
                /opt/forgerock/iec/lib/libzmq.so \
               "
```
