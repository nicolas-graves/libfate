#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;

    if (sysinfo(&info) == 0) {
        printf("sysinfo({uptime=%ld, loads=[%ld, %ld, %ld], totalram=%ld, freeram=%ld, sharedram=%ld, bufferram=%ld, totalswap=%ld, freeswap=%ld, procs=%d, totalhigh=%ld, freehigh=%ld, mem_unit=%d}) = 0\n",
               info.uptime,
               info.loads[0], info.loads[1], info.loads[2],
               info.totalram, info.freeram, info.sharedram, info.bufferram,
               info.totalswap, info.freeswap,
               info.procs,
               info.totalhigh, info.freehigh,
               info.mem_unit);
    } else {
        printf("sysinfo() failed\n");
        return 1;
    }

    return 0;
}
