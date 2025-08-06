SUMMARY = "IOTISTIC Camera Monitoring and Recording Application"
DESCRIPTION = "Application for checking camera connectivity and recording video streams"
LICENSE = "CLOSED"
SECTION = "multimedia"

# Source files
SRC_URI = " \
    file://main.cpp \
    file://iotisitic_cam.hpp \
    file://iotisitic_cam.cpp \
"

# Dependencies - add ffmpeg for recording functionality
DEPENDS = "ffmpeg"

S = "${WORKDIR}"

# Add compiler flags for C++11 and threading support
CXXFLAGS += "-std=c++11 -pthread"
LDFLAGS += "-pthread"

do_compile() {
    ${CXX} ${CXXFLAGS} -I${S} \
    ${S}/iotisitic_cam.cpp \
    ${S}/main.cpp \
    -o m2nvr-cam \
    ${LDFLAGS} -lpthread
}

do_install() {
    # Install binary
    install -d ${D}${bindir}
    install -m 0755 ${S}/m2nvr-cam ${D}${bindir}
    
    # Create recordings directory
    install -d ${D}/var/lib/m2nvr-cam/recordings
    chmod 0777 ${D}/var/lib/m2nvr-cam/recordings
}

# Add systemd service if needed (optional)
# SYSTEMD_SERVICE_${PN} = "m2nvr-cam.service"