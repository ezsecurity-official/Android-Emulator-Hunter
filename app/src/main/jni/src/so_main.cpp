#include <jni.h>
#include <thread>

#include "src/Includes/Logger.h"
#include "src/Includes/FileSystemUtils.h"
#include "src/vendors/JNILogs/JNILogs.h"
#include "scan_x86.h"
#include "AppInstallerChecker.h"

#define PACKAGE_NAME "com.ezsecurity.emulator.hunter"

void checkAppInstaller(JNIEnv *env, jobject thiz)
{
    AppInstallerChecker checker(env, thiz, PACKAGE_NAME);
    std::string installer = checker.getInstallerPackageName();

    if (installer.empty())
    {
        std::string errorMsg = "Failed to get installer package name: " + checker.getErrorMessage();
        LOGE("%s", errorMsg.c_str());
        JMethod::addLogEntry(errorMsg, JMethod::ERROR);
        return;
    }

    std::string logMsg = "The app was installed by: " + installer;
    LOGI("%s", logMsg.c_str());
    JMethod::addLogEntry(logMsg, JMethod::WARNING);

    if (installer.find("com.bluestacks.BstCommandProcessor") == 0)
    {
        std::string blueStacksMsg = "Detected BlueStacks installer: " + installer;
        LOGI("%s", blueStacksMsg.c_str());
        JMethod::addLogEntry(blueStacksMsg, JMethod::APK_DETECTED);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ezsecurity_emulator_hunter_MainActivity_initiateEmulatorScan(JNIEnv *env, jobject thiz)
{
    JMethod jMethod = JMethod(env, thiz);

    checkAppInstaller(env, thiz);
    scan_x86();

    for (const LogEntry& logEntry : logEntries)
    {
        jMethod.displayLogMessage(logEntry.message, logEntry.level);
    }

    logEntries.clear();
}