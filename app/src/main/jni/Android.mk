LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := lua_static
LOCAL_SRC_FILES := src/vendors/lua-5.4.7/libs/$(TARGET_ARCH_ABI)/liblua5.4.7.a
include $(PREBUILT_STATIC_LIBRARY)

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

LOCAL_STATIC_LIBRARIES := lua_static

LOCAL_LDLIBS := -llog -lc -lm

include $(BUILD_SHARED_LIBRARY)