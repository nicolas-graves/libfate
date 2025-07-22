#define _GNU_SOURCE
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

// Fixed epoch timestamp: 2024-01-01 00:00:00 UTC
static const time_t FIXED_TIME = 1704067200;
static const long FIXED_NSEC = 0;

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
    if (tp) {
        tp->tv_sec = FIXED_TIME;
        tp->tv_nsec = FIXED_NSEC;
    }
    return 0;
}
