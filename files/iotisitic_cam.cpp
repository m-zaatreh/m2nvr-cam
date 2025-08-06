// iotisitic_cam.cpp
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "iotisitic_cam.hpp"

clsM2nvrCam::clsM2nvrCam(int id, const std::string& ip, const std::string& rtsp, const std::string& output_dir) 
    : cam_id(id), cam_ip(ip), rtsp_url(rtsp), output_directory(output_dir), recording_flag(false) {}

clsM2nvrCam::~clsM2nvrCam() {
    if (is_recording()) {
        stop_recording();
    }
}

bool clsM2nvrCam::is_cam_online() const {
    std::string cmd = "ping -c 1 -W 1 " + cam_ip + " > /dev/null 2>&1";
    return (system(cmd.c_str()) == 0);
}

void clsM2nvrCam::record_video(const std::string& output_file) {
    std::string cmd = "ffmpeg -rtsp_transport tcp -i \"" + rtsp_url + "\" "
                      "-c:v copy -c:a aac -f segment -segment_time 300 -strftime 1 "
                      "-reset_timestamps 1 \"" + output_file + "\"";
    
    std::cout << "Executing: " << cmd << std::endl;
    int result = system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Recording failed with error code: " << result << std::endl;
    }
}

bool clsM2nvrCam::start_recording() {
    if (!is_cam_online()) {
        std::cerr << "Cannot start recording - camera is offline" << std::endl;
        return false;
    }
    
    if (is_recording()) {
        std::cerr << "Recording is already in progress" << std::endl;
        return false;
    }
    
    // Generate timestamped filename
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);
    
    std::ostringstream filename;
    filename << output_directory 
             << "cam_" << cam_id << "_"
             << std::put_time(&now_tm, "%Y%m%d_%H%M%S")
             << ".mp4";
    
    recording_flag = true;
    recording_thread.reset(new std::thread([this, filename = filename.str()]() {
        record_video(filename);
    }));
    
    return true;
}

bool clsM2nvrCam::stop_recording() {
    if (!is_recording()) {
        std::cerr << "No recording in progress" << std::endl;
        return false;
    }
    
    recording_flag = false;
    // Send SIGTERM to ffmpeg process (if needed)
    system("pkill -SIGTERM ffmpeg");
    
    if (recording_thread && recording_thread->joinable()) {
        recording_thread->join();
    }
    return true;
}