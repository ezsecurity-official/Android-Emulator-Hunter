//
// Created by MasterGames on 21/07/2024.
//
#ifndef ANDROID_EMULATOR_HUNTER_SCAN_X86_H
#define ANDROID_EMULATOR_HUNTER_SCAN_X86_H

#include <string>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <src/Includes/Logger.h>
#include <src/vendors/ELFPP.hpp>
#include <src/vendors/MemoryMap/MemoryMap.h>
#include "src/vendors/LuaUtils/LuaUtils.h"
#include "src/vendors/JNILogs/JNILogs.h"

void scan_x86();

#endif //ANDROID_EMULATOR_HUNTER_SCAN_X86_H