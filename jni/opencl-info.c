#include <stdio.h>
#include <stdlib.h>
#include <CL/opencl.h>

void printPlatformInfo(cl_int ret ,cl_uint i, const char* part , char* buf)
{
    if(ret==CL_SUCCESS){
            printf("\t platform index=%d %s : %s\n",i,part,buf);
    }else if(ret==CL_INVALID_PLATFORM){
            printf("\t platform index=%d %s : invalid platform.\n",i,part);
        }else if(ret==CL_INVALID_VALUE){
            printf("\t platform index=%d %s : invalid value.\n",i,part);
        }else if(ret==CL_OUT_OF_HOST_MEMORY){
            printf("\t platform index=%d %s : out of host memory.\n",i,part);
        }else{
            printf("\t platform index=%d %s : i don't know why.\n",i,part);
        }

}

void printDevice(cl_device_id device)
{
    char buf[128];
    size_t size = 0 ;
    cl_device_type type;
    cl_int ret = CL_SUCCESS;
    printf("\t   ######################\n");
    ret = clGetDeviceInfo(device,CL_DEVICE_NAME,128,buf,&size);
    if(ret==CL_SUCCESS){
        printf("\t   device name=%s\n",buf);
    }else{
        printf("\t   get device name fail !\n");
    }
    
    ret = clGetDeviceInfo(device,CL_DEVICE_TYPE,sizeof(cl_device_type),&type,&size);
    if(ret==CL_SUCCESS){
        printf("\t   device type=%lu\n",type);
    }else{
        printf("\t   get device type fail !\n");
    }
    
    
    ret = clGetDeviceInfo(device,CL_DEVICE_VENDOR,128,buf,&size);
    if(ret==CL_SUCCESS){
        printf("\t   device vendor=%s\n",buf);
    }else{
        printf("\t   get device vendor fail !\n");
    }
    ret = clGetDeviceInfo(device,CL_DRIVER_VERSION,128,buf,&size);
    if(ret==CL_SUCCESS){
        printf("\t   device version=%s\n",buf);
    }else{
        printf("\t   get device version fail !\n");
    }
    ret = clGetDeviceInfo(device,CL_DEVICE_PROFILE,128,buf,&size);
    if(ret==CL_SUCCESS){
        printf("\t   device profile=%s\n",buf);
    }else{
        printf("\t   get device profile fail !\n");
    }
    printf("\t   ######################\n");
}

void printDevices(cl_platform_id platform , cl_device_type device_type)
{
    cl_device_id devices[8];
    cl_uint i ;
    cl_uint num = 0 ;
    cl_int ret = clGetDeviceIDs(platform,device_type,8,devices,&num);
    if(ret==CL_SUCCESS){
        printf("\t  getDeviceIDs success ! num=%d\n",num);
        
        for(i=0;i<num;i++){
            printDevice(devices[i]);
        }
    }else{
        printf("\t  getDeviceIDs fail !\n");
    }
    
}

void printOpenCL()
{
        cl_platform_id platforms[8];
        cl_uint num = 0 ;
        cl_uint i=0;
        cl_int err = clGetPlatformIDs(8,platforms,&num);
        if(err==CL_SUCCESS){
                printf("printOpenCL got %d platforms : \n",num);
                for(i=0;i<num;i++){
                    char buf[128];
                    size_t size = 0 ;
                    cl_int ret = 0 ;
                    
                    ret = clGetPlatformInfo(platforms[i],CL_PLATFORM_PROFILE,128,buf,&size);
                    printPlatformInfo(ret,i,"profile",buf);
                
                ret = clGetPlatformInfo(platforms[i],CL_PLATFORM_VERSION,128,buf,&size);
                    printPlatformInfo(ret,i,"version",buf);
                    
                ret = clGetPlatformInfo(platforms[i],CL_PLATFORM_NAME,128,buf,&size);
                printPlatformInfo(ret,i,"name",buf);
                    
                    ret = clGetPlatformInfo(platforms[i],CL_PLATFORM_VENDOR,128,buf,&size);
                printPlatformInfo(ret,i,"vendor",buf);
                
                ret = clGetPlatformInfo(platforms[i],CL_PLATFORM_EXTENSIONS,128,buf,&size);
                printPlatformInfo(ret,i,"extensions",buf);
                
                printf("Device cpu:\n");
                printDevices(platforms[i],CL_DEVICE_TYPE_CPU);
                
                printf("Device gpu:\n");
                printDevices(platforms[i],CL_DEVICE_TYPE_GPU);
                
                printf("Device accelerator:\n");
                printDevices(platforms[i],CL_DEVICE_TYPE_ACCELERATOR);
                
                printf("Device default:\n");
                printDevices(platforms[i],CL_DEVICE_TYPE_DEFAULT);
                
                printf("Device all :\n");
                printDevices(platforms[i],CL_DEVICE_TYPE_ALL);
                
                }
        }else if(err==CL_INVALID_VALUE){
                printf("printOpenCL invalid value.\n");
        }else if(err==CL_OUT_OF_HOST_MEMORY){
                printf("printOpenCL out of host memory.\n");
        }else{
                printf("printOpenCL i don't know why.\n");
        }

}


int main(){
        printOpenCL();
        return 0;
}