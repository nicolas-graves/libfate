#define _GNU_SOURCE
#include <sys/sysinfo.h>

// Fixed sysinfo values for deterministic behavior
int sysinfo(struct sysinfo *info) {
    if (!info) {
        return -1;
    }

    // Set fixed values based on the example provided
    info->uptime = 42438;                // 42438 seconds uptime
    info->loads[0] = 144640;             // 1-minute load average
    info->loads[1] = 127872;             // 5-minute load average
    info->loads[2] = 112800;             // 15-minute load average
    info->totalram = 33328635904;        // Total usable main memory size
    info->freeram = 21326249984;         // Available memory size
    info->sharedram = 1465171968;        // Amount of shared memory
    info->bufferram = 12288;             // Memory used by buffers
    info->totalswap = 17179865088;       // Total swap space size
    info->freeswap = 17127542784;        // Available swap space
    info->procs = 1463;                  // Number of current processes
    info->totalhigh = 0;                 // Total high memory size
    info->freehigh = 0;                  // Available high memory size
    info->mem_unit = 1;                  // Memory unit size in bytes

    return 0;
}
