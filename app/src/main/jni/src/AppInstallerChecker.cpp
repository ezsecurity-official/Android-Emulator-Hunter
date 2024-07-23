//
// Created by MasterGames on 23/07/2024.
//
#include "AppInstallerChecker.h"

AppInstallerChecker::AppInstallerChecker(JNIEnv *env, jobject context, const std::string &packageName)
        : env(env)
        , context(context)
        , packageName(packageName)
{
    // ...
}

jobject AppInstallerChecker::getPackageManager()
{
    jclass contextClass = env->GetObjectClass(context);
    if (contextClass == nullptr)
    {
        errorMessage = "Context class not found";
        return nullptr;
    }

    jmethodID getPackageManagerMethod = env->GetMethodID(contextClass, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    if (getPackageManagerMethod == nullptr)
    {
        errorMessage = "getPackageManager method not found";
        return nullptr;
    }

    jobject packageManager = env->CallObjectMethod(context, getPackageManagerMethod);
    if (packageManager == nullptr)
        errorMessage = "PackageManager instance not found";

    env->DeleteLocalRef(contextClass);
    return packageManager;
}

std::string AppInstallerChecker::getInstallerPackageName()
{
    jobject packageManager = getPackageManager();
    if (packageManager == nullptr)
        return "";

    jclass packageManagerClass = env->GetObjectClass(packageManager);
    jmethodID getInstallerPackageNameMethod = env->GetMethodID(packageManagerClass, "getInstallerPackageName", "(Ljava/lang/String;)Ljava/lang/String;");
    if (getInstallerPackageNameMethod == nullptr)
    {
        errorMessage = "getInstallerPackageName method not found";
        env->DeleteLocalRef(packageManagerClass);
        return "";
    }

    jstring jPackageName = env->NewStringUTF(packageName.c_str());
    jstring installerPackageName = (jstring) env->CallObjectMethod(packageManager, getInstallerPackageNameMethod, jPackageName);

    std::string result;
    if (installerPackageName != nullptr)
    {
        const char *installerPackageNameStr = env->GetStringUTFChars(installerPackageName, nullptr);
        result = installerPackageNameStr;
        env->ReleaseStringUTFChars(installerPackageName, installerPackageNameStr);
        env->DeleteLocalRef(installerPackageName);
    } else {
        errorMessage = "Installer package name is null";
    }

    env->DeleteLocalRef(jPackageName);
    env->DeleteLocalRef(packageManagerClass);
    env->DeleteLocalRef(packageManager);
    return result;
}

std::string AppInstallerChecker::getErrorMessage() const
{
    return errorMessage;
}