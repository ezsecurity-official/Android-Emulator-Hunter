#ifndef LOGGER_H
#define LOGGER_H

#include <jni.h>
#include <android/log.h>

// Enum for log types
enum LogType {
    oDEBUG = ANDROID_LOG_DEBUG,
    oERROR = ANDROID_LOG_ERROR,
    oINFO  = ANDROID_LOG_INFO,
    oWARN  = ANDROID_LOG_WARN
};

// Log tag
#define TAG "EZSecurityEmulatorHunter"

// Logging macros
#define LOGD(...) ((void)__android_log_print(oDEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(oERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(oINFO,  TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(oWARN,  TAG, __VA_ARGS__))

#endif // LOGGER_H