LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# Include Paths
LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)

# Source Files
LOCAL_SRC_FILES := src/so_main.cpp

# Module Name
LOCAL_MODULE := ezsecurity

include $(BUILD_SHARED_LIBRARY)