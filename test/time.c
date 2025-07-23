#include "minunit.h"
#include <time.h>

static char *test_clock_gettime_fixed() {
    struct timespec ts1, ts2;

    clock_gettime(CLOCK_REALTIME, &ts1);
    clock_gettime(CLOCK_REALTIME, &ts2);

    mu_assert("clock_gettime should return fixed time",
              ts1.tv_sec == 1704067200 && ts1.tv_nsec == 0);
    mu_assert("clock_gettime should be consistent",
              ts1.tv_sec == ts2.tv_sec && ts1.tv_nsec == ts2.tv_nsec);
    return 0;
}

mu_main(test_clock_gettime_fixed);
