#include "scan_x86.h"
#include <thread>

__attribute__((constructor))
void lib_main()
{
    std::thread scan_x86(scan_x86_thread);
    scan_x86.detach();
}