SUMMARY = "IOTISTIC CAM application"

LICENSE = "CLOSED"

SRC_URI = "file://main.h \
           file://main.cpp"


S = "${WORKDIR}"
TARGET_CC_ARCH += "${LDFLAGS}"

DEPENDS = "hiredis cjson ffmpeg"

do_compile() {
    ${CC} ${CFLAGS} -I${S} \
    ${S}/main.c \
    -o m2nvr-cam -lhiredis -lavformat -lavcodec -lavutil -lswresample -lswscale -lavdevice -lavfilter -lm -lrt
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${S}/m2nvr-cam ${D}${bindir}
}