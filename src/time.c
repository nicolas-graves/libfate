#define _GNU_SOURCE
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Fixed epoch timestamp: 1970-01-01 00:00:01 UTC (fallback)
static const time_t FIXED_TIME = 1;
static const long FIXED_NSEC = 0;

static time_t get_deterministic_time() {
    const char *source_date_epoch = getenv("SOURCE_DATE_EPOCH");

    if (source_date_epoch && *source_date_epoch) {
        char *endptr;
        errno = 0;
        long long timestamp = strtoll(source_date_epoch, &endptr, 10);

        if (errno == 0 && *endptr == '\0' && timestamp >= 0) {
            return (time_t)timestamp;
        }
    }
    // Fall back to fixed time if SOURCE_DATE_EPOCH is not set or invalid
    return FIXED_TIME;
}

int clock_gettime(clockid_t clk_id, struct timespec *tp) {
    (void)clk_id;

    tp->tv_sec = get_deterministic_time();
    tp->tv_nsec = FIXED_NSEC;
    return 0;
}
