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

# Dependencies (ensure ping/system() works)
DEPENDS = "libstdc++"

S = "${WORKDIR}"

# Fix private access errors by:
# 1. Making is_cam_online() public
# 2. Using getters for cam_id/cam_ip
do_compile() {
    ${CXX} ${CXXFLAGS} -I${S} \
    ${S}/iotisitic_cam.cpp \
    ${S}/main.cpp \
    -o iotistic-cam \
    ${LDFLAGS} -lpthread
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/iotistic-cam ${D}${bindir}
}

FILES:${PN} = "${bindir}/iotistic-cam"