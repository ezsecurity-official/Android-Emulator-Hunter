//
// Created by MasterGames on 24/07/2024.
//

#ifndef ANDROID_EMULATOR_HUNTER_EMULATORMAPPINGS_H
#define ANDROID_EMULATOR_HUNTER_EMULATORMAPPINGS_H
#include <string>
#include <vector>
#include <iostream>

std::vector<const char*> emulatorLibs = {
    "libhoudini.so",
    "libGLES_bst.so" // BlueStacks
};

std::vector<std::string> blueStacksTargetPackages = {
    "com.bluestacks.BstCommandProcessor",
    "com.bluestacks.appmart",
    "com.bluestacks.billing.service",
    "com.bluestacks.bsxlauncher",
    "com.bluestacks.filemanager",
    "com.bluestacks.gamecenter",
    "com.bluestacks.home",
    "com.bluestacks.launcher",
    "com.bluestacks.nowgg",
    "com.bluestacks.piggy",
    "com.bluestacks.quest",
    "com.bluestacks.settings",
    "gg.now.accounts", // now.gg
    "gg.now.billing.service", // NowGGBillingService
    "gg.now.billing.service2" // NowGGBillingService2
};

std::vector<std::string> ldPlayerTargetPackages = {
    "com.android.ld.appstore",
    "com.ldmnq.launcher3"
};

#endif //ANDROID_EMULATOR_HUNTER_EMULATORMAPPINGS_H
