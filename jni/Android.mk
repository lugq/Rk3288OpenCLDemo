LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := libGLES_mali.so
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_LDLIBS    := -lm -llog


# To allow building native part of application with OpenCL,
# OpenCL header files and statically linked library are required.
# They are used from Intel OpenCL SDK installation directories,
# that are determined below: 

#ifeq ($(TARGET_ARCH),x86)
#    OCL_POSTFIX := android32
#else ifeq ($(TARGET_ARCH),x86_64)
#    OCL_POSTFIX := android64
#else
    # Unsupported target, do nothing
#endif


ifneq ($(OS),Windows_NT)
    # ifndef INTELOCLSDKROOT
    #    INTELOCLSDKROOT := /etc/alternatives/opencl-intel-tools
    # endif

    # Setting LOCAL_CFLAGS with -I is not good in comparison to LOCAL_C_INCLUDES
    # according to NDK documentation, but this only variant that works correctly

    # LOCAL_CFLAGS    += -I$(INTELOCLSDKROOT)/include
    LOCAL_MODULE    := step
    LOCAL_SRC_FILES := opencl-info.c
    # LOCAL_LDFLAGS   += -llog -ljnigraphics -L$(INTELOCLSDKROOT)/lib64/$(OCL_POSTFIX) -lOpenCL
else
    # Setting LOCAL_CFLAGS with -I is not good in comparison to LOCAL_C_INCLUDES
    # according to NDK documentation, but this only variant that works correctly

    # LOCAL_CFLAGS    += -I"$(INTELOCLSDKROOT)\include"
    LOCAL_MODULE    := step
    LOCAL_SRC_FILES := opencl-info.c
    # LOCAL_LDFLAGS   += -llog -ljnigraphics -L"$(INTELOCLSDKROOT)\lib\$(OCL_POSTFIX)" -lOpenCL
endif


#库文件目录

LOCAL_LDLIBS := libGLES_mali.so
include $(BUILD_EXECUTABLE)
