//
// Created by MasterGames on 24/07/2024.
//

#ifndef ANDROID_EMULATOR_HUNTER_MEMORYMAP_H
#define ANDROID_EMULATOR_HUNTER_MEMORYMAP_H

#include <string>
#include <vector>
#include <cstddef>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <sys/mman.h>

class MemoryMap
{
public:
    unsigned long long startAddress; // Start address of the memory region
    unsigned long long endAddress;   // End address of the memory region
    size_t length;                   // Length of the memory region
    int protectionFlags;             // Protection flags (e.g., read, write, execute)
    bool isReadable;                 // Is the memory region readable
    bool isWritable;                 // Is the memory region writable
    bool isExecutable;               // Is the memory region executable
    bool isPrivate;                  // Is the memory region private (not shared)
    bool isShared;                   // Is the memory region shared
    unsigned long long offset;       // Offset in the file or memory map
    std::string device;              // Device associated with the memory region
    unsigned long inode;             // Inode number (file identifier)
    std::string filePath;            // Path to the file or memory mapping

    /*
     * Constructor to initialize the members with default values
     */
    MemoryMap();

    /*
     * Destructor to clean up resources
     */
    ~MemoryMap();

    /*
     * Determines if the memory region is valid based on its attributes
     * @return True if the memory region has valid start and end addresses, and length
     */
    bool isValid() const;

    /*
     * Retrieves the name of the current process from /proc/self/cmdline
     * @return The name of the process
     */
    std::string getProcessName();

    /*
     * Retrieves information about all memory maps in the current process
     * @return A vector of MemoryMap objects representing all memory regions
     */
    std::vector<MemoryMap> getAllMaps();

    /*
     * Retrieves all shared libraries (.so files) currently loaded in the process
     * @return A vector of MemoryMap objects representing all .so files
     */
    std::vector<MemoryMap> getSharedLibraries();
};

#endif //ANDROID_EMULATOR_HUNTER_MEMORYMAP_H
