#include <jni.h>
#include <thread>

#include "src/Includes/Logger.h"
#include "src/Includes/FileSystemUtils.h"
#include "src/vendors/JNILogs/JNILogs.h"
#include "EmulatorMappings.h"
#include "scan_x86.h"
#include "AppInstallerChecker.h"

#define PACKAGE_NAME "com.ezsecurity.emulator.hunter"

void checkAppInstaller(JNIEnv *env, jobject thiz)
{
    AppInstallerChecker checker(env, thiz, PACKAGE_NAME);
    std::string installer = checker.getInstallerPackageName();

    if (installer.empty())
    {
        LOGE("Failed to get installer package name: %s", checker.getErrorMessage().c_str());
        JMethod::addLogEntry("Failed to get installer package name : " + checker.getErrorMessage(), JMethod::ERROR);
        return;
    }

    if (!installer.empty())
    {
        LOGI("The app was installed by: %s", installer.c_str());
        JMethod::addLogEntry("The app was installed by: " + installer, JMethod::APK_DETECTED);
    }

    if (installer.find("com.bluestacks.BstCommandProcessor") == 0)
    {
        LOGI("Detected BlueStacks installer: %s", installer.c_str());
        JMethod::addLogEntry("Detected BlueStacks installer: " + installer, JMethod::APK_DETECTED);
        return;
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