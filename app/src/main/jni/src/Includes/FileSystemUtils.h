//
// Created by MasterGames on 24/07/2024.
//

#ifndef ANDROID_EMULATOR_HUNTER_FILESYSTEMUTILS_H
#define ANDROID_EMULATOR_HUNTER_FILESYSTEMUTILS_H
#include <filesystem>
#include <iostream>
#include <string>

#include <src/Includes/Logger.h>

namespace fs = std::filesystem;

//#define ENABLE_FILE_SYSTEM_UTILS_DEBUG_LOGGING

bool containsSubdirectory(const std::string& parentDir, const std::string& subDir)
{
    try
    {
        fs::path parentPath(parentDir);

        // Check if the parent directory exists
        if (!fs::exists(parentPath))
        {
#if defined(ENABLE_FILE_SYSTEM_UTILS_DEBUG_LOGGING)
            LOGE("Parent directory does not exist: %s", parentDir.c_str());
#endif
            return false;
        }

        // Check if the path is a directory
        if (!fs::is_directory(parentPath))
        {
#if defined(ENABLE_FILE_SYSTEM_UTILS_DEBUG_LOGGING)
            LOGE("Parent path is not a directory: %s", parentDir.c_str());
#endif
            return false;
        }

        fs::path subPath = parentPath / subDir;

        // Check if the subdirectory exists and is a directory
        if (fs::exists(subPath) && fs::is_directory(subPath))
        {
#if defined(ENABLE_FILE_SYSTEM_UTILS_DEBUG_LOGGING)
            LOGI("Found subdirectory: %s", subPath.c_str());
#endif
            return true;
        }
        else
        {
#if defined(ENABLE_FILE_SYSTEM_UTILS_DEBUG_LOGGING)
            LOGE("Subdirectory not found: %s", subPath.c_str());
#endif
            return false;
        }
    } catch (const std::filesystem::filesystem_error& e) {
#if defined(ENABLE_FILE_SYSTEM_UTILS_DEBUG_LOGGING)
        LOGE("Filesystem error: %s", e.what());
#endif
        return false;
    }
}

#endif //ANDROID_EMULATOR_HUNTER_FILESYSTEMUTILS_H
