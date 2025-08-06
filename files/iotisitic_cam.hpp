// iotisitic_cam.hpp
#pragma once
#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <memory>
#include <chrono>
#include <ctime>

class clsM2nvrCam {
private: 
    int cam_id;
    std::string cam_ip;
    std::atomic<bool> recording_flag;
    std::unique_ptr<std::thread> recording_thread;
    std::string rtsp_url;
    std::string output_directory;
    
    // Private helper methods
    bool ping_camera() const;
    void record_video(const std::string& output_file);

public: 
    // Constructor
    clsM2nvrCam(int id, const std::string& ip, 
               const std::string& rtsp = "rtsp://admin:123456@192.168.1.101:554/stream0",
               const std::string& output_dir = "./");
    ~clsM2nvrCam();
    
    // Public interface
    bool is_cam_online() const;
    
    // Getters
    int get_cam_id() const { return cam_id; }
    std::string get_cam_ip() const { return cam_ip; }
    
    // Recording methods
    bool start_recording();
    bool stop_recording();
    bool is_recording() const { return recording_flag.load(); }
};