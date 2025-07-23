#define _GNU_SOURCE
#include <sys/sysinfo.h>

int sysinfo(struct sysinfo *info) {
    if (!info) {
        return -1;
    }

    // Constants for clarity
    static const int LOAD_SCALE = 65536;     // Kernel load average scaling factor
    static const int MB = 1024 * 1024;       // Megabyte in bytes
    static const long GB = 1024L * 1024 * 1024; // Gigabyte in bytes

    // Set realistic values for a typical Linux system
    info->uptime = 24 * 60 * 60;         // 24 hours uptime
    info->loads[0] = 1.0 * LOAD_SCALE;   // 1.0 load average (1-minute)
    info->loads[1] = 0.5 * LOAD_SCALE;   // 0.5 load average (5-minute)
    info->loads[2] = 0.25 * LOAD_SCALE;  // 0.25 load average (15-minute)
    info->totalram = 8 * GB;             // 8GB total RAM
    info->freeram = 4 * GB;              // 4GB free RAM
    info->sharedram = 256 * MB;          // 256MB shared memory
    info->bufferram = 128 * MB;          // 128MB buffer cache
    info->totalswap = 2 * GB;            // 2GB swap space
    info->freeswap = 1536 * MB;          // 1.5GB free swap
    info->procs = 256;                   // 256 running processes
    info->totalhigh = 0;                 // No high memory (64-bit system)
    info->freehigh = 0;                  // No high memory (64-bit system)
    info->mem_unit = 1;                  // Memory unit size in bytes

    return 0;
}
