//
// Created by MasterGames on 21/07/2024.
//
#ifndef ANDROID_EMULATOR_HUNTER_MEMORY_MANAGER_H
#define ANDROID_EMULATOR_HUNTER_MEMORY_MANAGER_H

#include <string>
#include <vector>
#include <cstddef>

struct MemoryRegion
{
    unsigned long long startAddress;
    unsigned long long endAddress;
    size_t length;
};

class MemoryManager
{
public:
    static std::string parseLineForLibrary(unsigned long long startAddress, const char* line);
    static std::string getLibraryNameByAddr(unsigned long long startAddress);
    static void getLibraryMemoryRegions(std::vector<MemoryRegion>& regions);
};

#endif //ANDROID_EMULATOR_HUNTER_MEMORY_MANAGER_H