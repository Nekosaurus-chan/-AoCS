#include <CL/cl.h>
#include <iostream>
#include <vector>

// The OpenCL kernel source code
const char* kernel_source = R"(
    __kernel void Y(__global float* x, __global float* result) 
    {
        int i = get_global_id(0);
        result[i] = sin(x[i]);
    }

    int factorial(int n) 
    {
        int result = 1;

        for (int i = 1; i <= n; i++) 
        {
            result *= i;
        }

        return result;
    }

    __kernel void S(__global float* x, int n, __global float* result)
    {
        int i = get_global_id(0);
        result[i] = 0;

        for (int j = 0; j <= n; j++) 
        {
            result[i] += pow(-1, j) * pow(x[i], 2 * j + 1) / factorial(2 * j + 1);
        }
    }
)";

int main() 
{
    int n = 0;
    // Set up OpenCL context, command queue, and memory buffers
    cl_platform_id platform;
    clGetPlatformIDs(1, &platform, NULL);

    cl_device_id device;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, 0, NULL);

    cl_mem x_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * 1000, NULL, NULL);  
    cl_mem result_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * 1000, NULL, NULL);

    // Compile the kernel source code
    cl_int err;
    cl_program program = clCreateProgramWithSource(context, 1, &kernel_source, NULL, &err);
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL);

    // Create the kernel objects
    cl_kernel kernel_Y = clCreateKernel(program, "Y", &err);
    cl_kernel kernel_S = clCreateKernel(program, "S", &err);

    // Set the kernel arguments
    clSetKernelArg(kernel_Y, 0, sizeof(cl_mem), &x_buffer);
    clSetKernelArg(kernel_Y, 1, sizeof(cl_mem), &result_buffer);
    clSetKernelArg(kernel_S, 0, sizeof(cl_mem), &x_buffer);
    clSetKernelArg(kernel_S, 1, sizeof(int), &n);
    clSetKernelArg(kernel_S, 2, sizeof(cl_mem), &result_buffer);

    // Define the number of work items and the size of the work groups
    size_t global_work_size = 1000;
    size_t local_work_size = 64;

    // Enqueue the kernels for execution
    clEnqueueNDRangeKernel(queue, kernel_Y, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);
    clEnqueueNDRangeKernel(queue, kernel_S, 1, NULL, &global_work_size, &local_work_size, 0, NULL, NULL);

    // Read the results from the device
    float* result = new float[1000];
    clEnqueueReadBuffer(queue, result_buffer, CL_TRUE, 0, sizeof(float) * 1000, result, 0, NULL, NULL);

    // Don't forget to release OpenCL resources at the end
    clReleaseMemObject(x_buffer);
    clReleaseMemObject(result_buffer);
    clReleaseProgram(program);
    clReleaseKernel(kernel_Y);
    clReleaseKernel(kernel_S);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);

    delete[] result;



    return 0;
}