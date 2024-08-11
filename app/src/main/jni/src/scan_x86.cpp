#include "scan_x86.h"
#include "src/lua_scripts/scan_x86_script.h"
#include "src/EmulatorMappings.h"

using namespace ELFPP;

std::string convertAddressToHex(unsigned long long address)
{
    std::stringstream ss;
    ss << "0x" << std::hex << address;
    return ss.str();
}

void detectELFArchitecture(unsigned long long startAddress, const std::string& libraryName)
{
    try {
        std::unique_ptr<IELF> elf = ELFPP::FromBuffer(reinterpret_cast<void*>(startAddress));
        EMachine machine = elf->GetTargetMachine();

        if (machine == EMachine::X86)
        {
            std::string logMessage = "x86 architecture found: local(" + libraryName + "), address(" + convertAddressToHex(startAddress) + ")";
            LOGI("%s", logMessage.c_str());
            JMethod::addLogEntry(logMessage, JMethod::WARNING);
        }
    } catch (const std::exception& e) {
        LOGI("Error: %s", e.what());
        JMethod::addLogEntry("Error: " + std::string(e.what()), JMethod::ERROR);
    }
}

bool checkForSpecificLibraries(const std::vector<MemoryMap>& libraries, const std::vector<const char*>& targetLibraries)
{
    std::unordered_map<std::string, bool> libraryFound;

    for (const auto& targetLib : targetLibraries)
    {
        libraryFound[targetLib] = false;
    }

    for (const auto& lib : libraries)
    {
        if (lib.isValid())
        {
            for (const auto& targetLib : targetLibraries)
            {
                if (lib.filePath.find(targetLib) != std::string::npos)
                {
                    if (!libraryFound[targetLib])
                    {
                        std::string logMessage = "Emulator library detected: local(" + lib.filePath + ")";
                        LOGI("%s", logMessage.c_str());
                        JMethod::addLogEntry(logMessage, JMethod::APK_DETECTED);
                        libraryFound[targetLib] = true;
                    }
                }
            }
        }
    }

    bool allFound = true;
    for (const auto& entry : libraryFound)
    {
        if (!entry.second)
        {
            std::string logMessage = "Emulator library not found: " + entry.first;
            LOGI("%s", logMessage.c_str());
            JMethod::addLogEntry(logMessage, JMethod::ERROR);
            allFound = false;
        }
    }

    return allFound;
}

void analyze_libraries()
{
    std::unique_ptr<MemoryMap> memoryMap = std::make_unique<MemoryMap>();
    std::vector<MemoryMap> libraries = memoryMap->getSharedLibraries();

    // Check and log specific emulator libraries
    checkForSpecificLibraries(libraries, emulatorLibs);

    // Analyze the remaining libraries
    for (const auto& lib : libraries)
    {
        if (lib.isValid() && std::none_of(emulatorLibs.begin(), emulatorLibs.end(), [&](const char* excludeLib) {
            return lib.filePath.find(excludeLib) != std::string::npos;
        }))
        {
            detectELFArchitecture(lib.startAddress, lib.filePath);
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