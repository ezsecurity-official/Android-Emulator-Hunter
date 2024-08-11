//
// Created by MasterGames on 10/08/2024.
//

#ifndef ANDROID_EMULATOR_HUNTER_JNILOGS_H
#define ANDROID_EMULATOR_HUNTER_JNILOGS_H


#include <jni.h>
#include <string>
#include <vector>

// Struct to store log entries
struct LogEntry
{
    std::string message; // Log message
    int level; // Log level (e.g., INFO, WARNING, ERROR)
};

// Extern vector to hold log entries
extern std::vector<LogEntry> logEntries;

class JMethod
{
private:
    JNIEnv* env; // Pointer to JNI environment
    jobject obj; // Reference to the Java object

public:
    // Log levels
    static const int APK_DETECTED = 0;
    static const int WARNING = 1;
    static const int ERROR = 2;

    // Static method to add a log entry to the list
    static void addLogEntry(const std::string& message, int level)
    {
        logEntries.push_back({message, level});
    }

    // Constructor to initialize JMethod with JNI environment and Java object
    JMethod(JNIEnv* jniEnv, jobject javaObject)
            : env(jniEnv)
            , obj(javaObject)
    {
        // ...
    }

    // Method to call Java's displayLogMessage method from C++
    void displayLogMessage(const std::string& message, int status = 0)
    {
        // Find the MainActivity class
        jclass mainActivityClass = env->FindClass("com/ezsecurity/emulator/hunter/MainActivity");

        // Get the method ID for displayLogMessage
        jmethodID logMethodID = env->GetMethodID(mainActivityClass, "displayLogMessage", "(Ljava/lang/String;I)V");

        // Convert the C++ string to a JNI string and call the method
        jstring jMessage = env->NewStringUTF(message.c_str());
        env->CallVoidMethod(obj, logMethodID, jMessage, status);

        // Clean up local references
        env->DeleteLocalRef(jMessage);
    }
};

#endif //ANDROID_EMULATOR_HUNTER_JNILOGS_H
