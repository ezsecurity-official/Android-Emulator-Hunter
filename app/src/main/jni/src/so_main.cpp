#include "scan_x86.h"
#include "AppInstallerChecker.h"
#include "src/Includes/Logger.h"
#include <thread>
#include <jni.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_ezsecurity_emulator_hunter_MainActivity_checkAppInstaller(JNIEnv *env, jobject thiz)
{
    AppInstallerChecker checker(env, thiz, "com.ezsecurity.emulator.hunter");
    std::string installer = checker.getInstallerPackageName();

    if (!installer.empty())
    {
        LOGI("The app was installed by: %s", installer.c_str());
    } else {
        LOGE("Failed to get installer package name: %s", checker.getErrorMessage().c_str());
    }
}

__attribute__((constructor))
void lib_main()
{
    std::thread scan_x86(scan_x86_thread);
    scan_x86.detach();
}