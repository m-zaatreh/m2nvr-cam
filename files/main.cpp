// main.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "iotisitic_cam.hpp"

int main() {
    // Initialize camera with RTSP URL and output directory
    clsM2nvrCam camera(1, "192.168.1.101",
                      "rtsp://admin:123456@192.168.1.101:554/stream0",
                      "./recordings/");
    
    // Check camera status
    if (camera.is_cam_online()) {
        std::cout << "Camera " << camera.get_cam_id() 
                  << " (" << camera.get_cam_ip() << ") is ONLINE!\n";
    } else {
        std::cout << "Camera " << camera.get_cam_id() 
                  << " (" << camera.get_cam_ip() << ") is OFFLINE!\n";
        return 1;
    }
    
    // Start recording
    if (camera.start_recording()) {
        std::cout << "Recording started successfully\n";
    } else {
        std::cout << "Failed to start recording\n";
        return 1;
    }
    
    // Check recording status for 10 seconds
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Recording status: " 
                  << (camera.is_recording() ? "ACTIVE" : "INACTIVE") 
                  << " (" << i+1 << "s)\n";
    }
    
    // Stop recording
    if (camera.stop_recording()) {
        std::cout << "Recording stopped successfully\n";
    } else {
        std::cout << "Failed to stop recording\n";
    }
    
    // Final recording status check
    std::cout << "Final recording status: " 
              << (camera.is_recording() ? "ACTIVE" : "INACTIVE") << "\n";
    
    return 0;
}