//
// Created by MasterGames on 24/07/2024.
//

#include "MemoryMap.h"

MemoryMap::MemoryMap()
        : startAddress(0), endAddress(0), length(0), protectionFlags(0)
        , isReadable(false), isWritable(false), isExecutable(false)
        , isPrivate(false), isShared(false), offset(0), inode(0)
{
    // ...
}

MemoryMap::~MemoryMap()
{
    // ...
}

bool MemoryMap::isValid() const
{
    return (startAddress && endAddress && length);
}

std::string MemoryMap::getProcessName()
{
    const char *filePath = "/proc/self/cmdline";
    char cmdline[128] = { 0 };

    // Open the file
    FILE *file = fopen(filePath, "r");
    if (!file)
        return "";

    // Read the process name
    if (fgets(cmdline, sizeof(cmdline), file) == nullptr)
    {
        fclose(file);
        return "";
    }

    // Close the file
    fclose(file);

    // Remove trailing null characters
    size_t len = strlen(cmdline);
    if (len > 0 && cmdline[len - 1] == '\0')
        cmdline[len - 1] = '\0';

    return std::string(cmdline);
}

std::vector<MemoryMap> MemoryMap::getAllMaps()
{
    std::vector<MemoryMap> maps;
    const char *filePath = "/proc/self/maps";
    char line[512] = {0};

    FILE *fp = fopen(filePath, "r");
    if (!fp)
        return maps;

    while (fgets(line, sizeof(line), fp))
    {
        MemoryMap map;
        char perms[5] = {0}, dev[11] = {0}, pathname[256] = {0};
        unsigned long long start, end, offset;
        unsigned long inode;

        // Parse the line: startAddress-endAddress perms offset dev inode pathname
        int fieldsParsed = sscanf(line, "%llx-%llx %4s %llx %10s %lu %255s", &start, &end, perms, &offset, dev, &inode, pathname);

        if (fieldsParsed < 6)
            continue;

        // Fill the MemoryMap structure using class members
        map.startAddress = start;
        map.endAddress = end;
        map.length = end - start;
        map.offset = offset;
        map.device = dev;
        map.inode = inode;
        map.filePath = pathname;

        // Set protection flags and attributes
        map.isReadable = perms[0] == 'r';
        map.isWritable = perms[1] == 'w';
        map.isExecutable = perms[2] == 'x';
        map.isPrivate = perms[3] == 'p';
        map.isShared = perms[3] == 's';

        // Construct protection flags
        map.protectionFlags = 0;
        if (map.isReadable) map.protectionFlags |= PROT_READ;
        if (map.isWritable) map.protectionFlags |= PROT_WRITE;
        if (map.isExecutable) map.protectionFlags |= PROT_EXEC;

        maps.push_back(map);
    }

    fclose(fp);
    return maps;
}

std::vector<MemoryMap> MemoryMap::getSharedLibraries()
{
    std::vector<MemoryMap> sharedLibraries;
    std::vector<MemoryMap> allMaps = getAllMaps();

    for (const MemoryMap& map : allMaps)
    {
        // Check if the file path ends with ".so"
        if (map.filePath.size() > 3 && map.filePath.compare(map.filePath.size() - 3, 3, ".so") == 0)
        {
            sharedLibraries.push_back(map);
        }
    }

    return sharedLibraries;
}
