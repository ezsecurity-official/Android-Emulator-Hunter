# armeabi-v7a for 32-bit ARM
# arm64-v8a for 64-bit ARM
# x86 for 32-bit Intel
# x86_64 for 64-bit Intel
APP_ABI := armeabi-v7a, arm64-v8a

# Minimum Android platform version
APP_PLATFORM := android-21

# Use the static C++ Standard Library
APP_STL := c++_static

# Set optimization level based on build type
APP_OPTIM := release