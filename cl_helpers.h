#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "OpenCL/opencl.h"

std::vector<cl_platform_id> GetPlatformIDs()
{
  	cl_uint platform_count;
	clGetPlatformIDs(0, nullptr, &platform_count);

    std::vector<cl_platform_id> platform_ids(platform_count);
	clGetPlatformIDs(platform_count, platform_ids.data(), NULL);
    return platform_ids;
}

std::vector<cl_device_id> GetDeviceIDs(cl_platform_id pid)
{
  	cl_uint device_count;
	clGetDeviceIDs(pid, CL_DEVICE_TYPE_ALL, 0, NULL, &device_count);

    std::vector<cl_device_id> device_ids(device_count);
	clGetDeviceIDs(pid, CL_DEVICE_TYPE_ALL, device_count,
	               device_ids.data(), NULL);
    return device_ids;
}
   

std::string GetDeviceName (cl_device_id id)
{
	size_t size = 0;
	clGetDeviceInfo (id, CL_DEVICE_NAME, 0, nullptr, &size);

	std::string result;
	result.resize (size);
	clGetDeviceInfo (id, CL_DEVICE_NAME, size,
		const_cast<char*> (result.data ()), nullptr);

	return result;
}

void CheckError (cl_int error)
{
	if (error != CL_SUCCESS) {
		std::cerr << "OpenCL call failed with error " << error << std::endl;
		std::exit (1);
	}
}

cl_program CreateProgram (const std::string& source,
	cl_context context)
{
	size_t lengths [1] = { source.size () };
	const char* sources [1] = { source.data () };

	cl_int error = 0;
	cl_program program = clCreateProgramWithSource (context, 1, sources, lengths, &error);
	CheckError (error);

	return program;
}

std::string file_to_string(std::string filename)
{
    std::ifstream f(filename);
    std::stringstream ss;
	ss << f.rdbuf();
	return ss.str();
}
