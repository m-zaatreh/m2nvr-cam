#pragma once
#include <iostream>
#include <string>

class clsM2nvrCam {
private: 
    int cam_id;
    std::string cam_ip;

    // Private helper method (if needed)
    bool ping_camera() const;

public: 
    // Constructor
    clsM2nvrCam(int id, const std::string& ip);
    
    // Public interface
    bool is_cam_online() const;  // Now public!
    
    // Getters
    int get_cam_id() const { return cam_id; }
    std::string get_cam_ip() const { return cam_ip; }
    
    // Other methods...
    bool stop_recording();
    bool start_recording(const std::string& cam);
};