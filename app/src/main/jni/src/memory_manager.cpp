//
// Created by MasterGames on 21/07/2024.
//
#include "memory_manager.h"
#include <cstdio>
#include <cstring>
#include <iostream>

/*
 * Function to parse a line and check if the start address falls within the specified range
*/
std::string MemoryManager::parseLineForLibrary(unsigned long long startAddress, const char* line)
{
    unsigned long long line_start_address, line_end_address;
    char path[256];

    if (sscanf(line, "%llx-%llx %*s %*s %*x:%*x %*d %255s", &line_start_address, &line_end_address, path) == 3)
    {
        if (startAddress >= line_start_address && startAddress < line_end_address)
        {
            return std::string(path);
        }
    }
    return "";
}

/*
 * Function to parse a line and check if the start address falls within the specified range
*/
std::string MemoryManager::getLibraryNameByAddr(unsigned long long startAddress)
{
    FILE* maps = fopen("/proc/self/maps", "r");
    if (!maps)
    {
        perror("fopen");
        return "";
    }

    char line[256];
    std::string library_name;

    while (fgets(line, sizeof(line), maps))
    {
        library_name = parseLineForLibrary(startAddress, line);
        if (!library_name.empty())
        {
            break;
        }
    }

    fclose(maps);
    return library_name;
}

/*
 * Function to get the library name by its start address
*/
void MemoryManager::getLibraryMemoryRegions(std::vector<MemoryRegion>& regions)
{
    FILE* maps = fopen("/proc/self/maps", "r");
    if (!maps)
    {
        perror("fopen");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), maps))
    {
        uintptr_t start_address, end_address;
        if (sscanf(line, "%lx-%lx", &start_address, &end_address) == 2)
        {
            if (strstr(line, ".so"))
            {
                size_t size = end_address - start_address;
                regions.push_back({ start_address, size });
            }
        }
    }

    fclose(maps);
}