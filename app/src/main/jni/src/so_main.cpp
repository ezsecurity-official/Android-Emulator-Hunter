#include <jni.h>
#include <thread>

#include "src/Includes/Logger.h"
#include "src/Includes/FileSystemUtils.h"

#include "EmulatorMappings.h"
#include "scan_x86.h"
#include "AppInstallerChecker.h"

#define PACKAGE_NAME "com.ezsecurity.emulator.hunter"

void checkProfilesDirectories()
{
    std::string profilesDirectory = "data/misc/profiles/cur/0/";
    if (profilesDirectory.empty())
        return;

    for (const auto& dir : blueStacksTargetPackages)
    {
        if (containsSubdirectory(profilesDirectory, dir))
        {
            LOGI("The directory contains the BlueStacks target directory: %s", dir.c_str());
        }
        else
        {
            LOGE("The directory does not contain the BlueStacks target directory: %s", dir.c_str());
        }
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ezsecurity_emulator_hunter_MainActivity_checkAppInstaller(JNIEnv *env, jobject thiz)
{
    AppInstallerChecker checker(env, thiz, PACKAGE_NAME);
    std::string installer = checker.getInstallerPackageName();

    if (installer.empty())
    {
        LOGE("Failed to get installer package name: %s", checker.getErrorMessage().c_str());
        return;
    }

    LOGI("The app was installed by: %s", installer.c_str());

    if (installer.find("com.bluestacks.BstCommandProcessor") == 0)
    {
        LOGI("Detected BlueStacks installer: %s", installer.c_str());
    }
}

__attribute__((constructor))
void lib_main()
{
    std::thread scan_x86(scan_x86_thread);
    scan_x86.detach();
}