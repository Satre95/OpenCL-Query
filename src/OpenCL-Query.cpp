#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_TARGET_OPENCL_VERSION 200

#include <CL/cl2.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    
    if(platforms.empty()) {
        std::cout << "No OpenCL platforms found!" << std::endl;
        return 0;
    }

    std::cout << "Found " << platforms.size() << " OpenCL Platform";
    std::cout << ((platforms.size() > 1) ? "s." : ".") << std::endl;

    for(auto & platform: platforms) {
        std::cout << "--------------------" << std::endl;
        auto name = platform.getInfo<CL_PLATFORM_NAME>();
        std::cout << "Name: " << name << std::endl;
        auto vendor = platform.getInfo<CL_PLATFORM_VENDOR>();
        std::cout << "Vendor: " << vendor << std::endl;
        auto version = platform.getInfo<CL_PLATFORM_VERSION>();
        std::cout << "Version: " << version << std::endl;
        auto profile = platform.getInfo<CL_PLATFORM_PROFILE>();
        std::cout << "Supported profile: " << profile << std::endl;

        auto extensions = platform.getInfo<CL_PLATFORM_EXTENSIONS>();

        if(extensions.empty() || extensions == " ")
            std::cout << "No extensions found." << std::endl;
        else
            std::cout << "Supported extensions: " << extensions << std::endl;

        // Get the devices supported under this platform.
        std::vector<cl::Device> cpuDevices;
        std::vector<cl::Device> gpuDevices;
        std::vector<cl::Device> acceleratorDevices;

        int deviceCount = 1;

        try {
            std::cout << "Platform has these device(s):" << std::endl;
            platform.getDevices(CL_DEVICE_TYPE_GPU, &gpuDevices);

            for(auto & aDevice: cpuDevices) {
                std::cout << "\t" << deviceCount << ". ";
                std::cout << aDevice.getInfo<CL_DEVICE_VERSION>() << std::endl;
                deviceCount++;
            }
        } catch(...) {std::cout << "Exception when querying GPU devices" << std::endl;}

        try {
            platform.getDevices(CL_DEVICE_TYPE_CPU, &cpuDevices);
            for(auto & aDevice: gpuDevices) {
                std::cout << "\t" << deviceCount << ". ";
                std::cout << aDevice.getInfo<CL_DEVICE_VERSION>() << std::endl;
                deviceCount++;
            }

        } catch(...) {std::cout << "Exception when querying CPU devices" << std::endl;}

        try {
            platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &acceleratorDevices);
            for(auto & aDevice: acceleratorDevices) {
                std::cout << "\t" << deviceCount << ". ";
                std::cout << aDevice.getInfo<CL_DEVICE_VERSION>() << std::endl;
                deviceCount++;
            }

        } catch(...) {}std::cout << "Exception when querying Accelerator devices" << std::endl;

        //cl::Device d = cl::Device::getDefault();
        //std::cout << "Max pipe args: " << d.getInfo<CL_DEVICE_MAX_PIPE_ARGS>() << "\n";
        //std::cout << "Max pipe active reservations: " << d.getInfo<CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS>() << "\n";
        //std::cout << "Max pipe packet size: " << d.getInfo<CL_DEVICE_PIPE_MAX_PACKET_SIZE>() << "\n";
        //std::cout << "Device SVM capabilities: " << d.getInfo<CL_DEVICE_SVM_CAPABILITIES>() << "\n";
        //std::cout << "\tCL_DEVICE_SVM_COARSE_GRAIN_BUFFER = " << CL_DEVICE_SVM_COARSE_GRAIN_BUFFER << "\n";
        //std::cout << "\tCL_DEVICE_SVM_FINE_GRAIN_BUFFER = " << CL_DEVICE_SVM_FINE_GRAIN_BUFFER << "\n";
        //std::cout << "\tCL_DEVICE_SVM_FINE_GRAIN_SYSTEM = " << CL_DEVICE_SVM_FINE_GRAIN_SYSTEM << "\n";
        //std::cout << "\tCL_DEVICE_SVM_ATOMICS = " << CL_DEVICE_SVM_ATOMICS << "\n";
    }
    std::cout << "--------------------" << std::endl;
}
