//
// Created by MasterGames on 23/07/2024.
//

#ifndef ANDROID_EMULATOR_HUNTER_APPINSTALLERCHECKER_H
#define ANDROID_EMULATOR_HUNTER_APPINSTALLERCHECKER_H

#include <jni.h>
#include <string>

class AppInstallerChecker
{
public:
    AppInstallerChecker(JNIEnv *env, jobject context, const std::string &packageName);
    std::string getInstallerPackageName();
    std::string getErrorMessage() const;

private:
    JNIEnv *env;
    jobject context;
    std::string packageName;
    std::string errorMessage;

    jobject getPackageManager();
};

#endif //ANDROID_EMULATOR_HUNTER_APPINSTALLERCHECKER_H
