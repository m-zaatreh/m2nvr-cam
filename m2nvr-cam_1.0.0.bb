SUMMARY = "IOTISTIC Camera Monitoring Application"
DESCRIPTION = "Application for checking camera connectivity via ping"
LICENSE = "CLOSED"
SECTION = "multimedia"

# Source files
SRC_URI = " \
    file://main.cpp \
    file://iotisitic_cam.hpp \
    file://iotisitic_cam.cpp \
"

DEPENDS = "libstdc++"

S = "${WORKDIR}"


do_compile() {
    ${CXX} ${CXXFLAGS} -I${S} \
    ${S}/iotisitic_cam.cpp \
    ${S}/main.cpp \
    -o m2nvr-cam \
    ${LDFLAGS} -lpthread
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/m2nvr-cam ${D}${bindir}
}
