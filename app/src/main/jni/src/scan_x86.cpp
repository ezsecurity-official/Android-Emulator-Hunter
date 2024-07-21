//
// Created by MasterGames on 21/07/2024.
//
#include "scan_x86.h"

#include <string>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <src/Includes/Logger.h>
#include <src/vendors/ELFPP.hpp>
#include <src/memory_manager.h>

using namespace ELFPP;

void print_ELF_architecture(unsigned long long startAddress, size_t length)
{
    try {
        std::unique_ptr<IELF> elf = ELFPP::FromBuffer(reinterpret_cast<void*>(startAddress));

        EMachine machine = elf->GetTargetMachine();
        std::string library_name = MemoryManager::getLibraryNameByAddr(startAddress);

        switch (machine)
        {
            case EMachine::X86:
                LOGI("x86 architecture found in: %s, 0x%llx", library_name.c_str(), startAddress);
                break;
            case EMachine::ARM:
                // LOGI("ARM architecture found in: %s, 0x%llx", library_name.c_str(), startAddress);
                break;
            default:
                // LOGI("Unknown or unsupported architecture found in: %s, 0x%llx", library_name.c_str(), startAddress);
                break;
        }
    } catch (const std::exception& e) {
        LOGI("Error: %s", e.what());
    }
}

void analyze_libraries()
{
    std::vector<MemoryRegion> library_regions;
    MemoryManager::getLibraryMemoryRegions(library_regions);

    for (const MemoryRegion& region : library_regions)
    {
        print_ELF_architecture(region.startAddress, region.length);
    }
}

void scan_x86_thread()
{
    LOGI("thread [scan_x86] loaded");
    analyze_libraries();
}