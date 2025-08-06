#include <iostream>
#include "iotisitic_cam.hpp"

int main() {
    clsM2nvrCam camera(1, "192.168.1.101");
    
    if (camera.is_cam_online()) {
        std::cout << "Camera " << camera.get_cam_id() 
                  << " (" << camera.get_cam_ip() << ") is ONLINE!\n";
    } else {
        std::cout << "Camera " << camera.get_cam_id() 
                  << " (" << camera.get_cam_ip() << ") is OFFLINE!\n";
    }
    
    return 0;
}