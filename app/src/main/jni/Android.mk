LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# Include Paths
LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)

LOCAL_CPPFLAGS := -std=c++17 -frtti -fexceptions

# Source Files
LOCAL_SRC_FILES := src/so_main.cpp \
    src/vendors/MemoryMap/MemoryMap.cpp \
    src/scan_x86.cpp \
    src/AppInstallerChecker.cpp

# Module Name
LOCAL_MODULE := ezsecurity

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)