//
// Created by MasterGames on 10/08/2024.
//

#ifndef ANDROID_EMULATOR_HUNTER_SCAN_X86_SCRIPT_H
#define ANDROID_EMULATOR_HUNTER_SCAN_X86_SCRIPT_H

const char* scan_x86_script = R"(
-- Function to check if a path is valid and points to a .so file
local function is_valid_so_path(s_path)
    return s_path:match("^/system/") or s_path:match("^/data/") or
           s_path:match("^/lib/") or s_path:match("^/sbin/") or
           s_path:match("^/sys/") and s_path:match("%.so$")
end

-- Check if the file exists and is a valid ELF file for x86 architecture
local function check_elf_file_x86(file_path)
    if not is_valid_so_path(file_path) then return false end
    local f = io.open(file_path, 'rb')
    if f then
        if f:seek("end") > 1024 then
            f:seek("set")
            local content = f:read(18 + 2) -- Read up to CPU type
            if content:sub(1, 4) == "\127ELF" and content:byte(5) == 1 then
                local cpu_type = content:sub(19, 20)
                f:close()
                return cpu_type == "\003\000" -- x86 CPU type
            end
        end
        f:close()
    end
    return false
end

-- Scan for emulator-specific files
local function scan_emulator()
    local has_x86_file = false
    local libhoudini_file_name = ""
    local files_to_check = {
        "/system/lib/libc.so", "/system/lib/libhoudini.so",
        "/system/lib64/libc.so", "/system/lib64/libhoudini.so"
    }

    for _, file_path in ipairs(files_to_check) do
        local file_name = file_path:match("([^/]+)$")
        if check_elf_file_x86(file_path) then
            has_x86_file = true
            print("Detected x86 library: " .. file_name)
        end
        if file_name == "libhoudini.so" then
            libhoudini_file_name = file_name
            print("Detected libhoudini: " .. file_name)
        end
    end

    print("Scan result: x86 file detected = " .. tostring(has_x86_file) .. ", libhoudini file = " .. libhoudini_file_name)
end

scan_emulator()
)";

#endif //ANDROID_EMULATOR_HUNTER_SCAN_X86_SCRIPT_H
