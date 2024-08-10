//
// Created by MasterGames on 21/07/2024.
//
#include "scan_x86.h"
#include "src/lua_scripts/scan_x86_script.h"

using namespace ELFPP;

void print_ELF_architecture(unsigned long long startAddress, size_t length, const std::string& libraryName)
{
    try {
        std::unique_ptr<IELF> elf = ELFPP::FromBuffer(reinterpret_cast<void*>(startAddress));
        EMachine machine = elf->GetTargetMachine();

        switch (machine)
        {
            case EMachine::X86:
                 LOGI("x86 architecture found in: %s, 0x%llx", libraryName.c_str(), startAddress);
                 JMethod::addLogEntry("x86 architecture found: local(" + libraryName + "), address(0x" + std::to_string(startAddress) + ")", JMethod::LIB_DETECTED);
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
    std::unique_ptr<MemoryMap> memoryMap = std::make_unique<MemoryMap>();
    std::vector<MemoryMap> libraries = memoryMap->MemoryMap::getSharedLibraries();

    for (const MemoryMap& lib : libraries)
    {
        // Check if the memory map is valid
        if (lib.isValid())
        {
            print_ELF_architecture(lib.startAddress, lib.length, lib.filePath);
        }
    }
}

void analyze_lua_libraries()
{
    run_lua_script(scan_x86_script);
}

void scan_x86()
{
    LOGI("[scan_x86] Starting x86 scan");

    analyze_libraries();
    analyze_lua_libraries();

    LOGI("[scan_x86] Finished x86 scan");
}