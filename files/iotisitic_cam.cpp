
#include <iostream>
#include <cstdlib> // For system() command
#include "iotisitic_cam.hpp"

clsM2nvrCam::clsM2nvrCam(int id, const std::string& ip) 
    : cam_id(id), cam_ip(ip) {}

bool clsM2nvrCam::is_cam_online() const {
    std::string cmd = "ping -c 1 -W 1 " + cam_ip + " > /dev/null 2>&1";
    return (system(cmd.c_str()) == 0);
}

// Other method implementations...