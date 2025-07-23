#include "minunit.h"
#include <time.h>
#include <stdlib.h>

static char *test_clock_gettime_fixed() {
    struct timespec ts1, ts2;
    const char *source_date_epoch = getenv("SOURCE_DATE_EPOCH");
    time_t expected_time = source_date_epoch ? (time_t)atoll(source_date_epoch) : 1;

    clock_gettime(CLOCK_REALTIME, &ts1);
    clock_gettime(CLOCK_REALTIME, &ts2);

    mu_assert("clock_gettime should return deterministic time",
              ts1.tv_sec == expected_time && ts1.tv_nsec == 0);
    mu_assert("clock_gettime should be consistent",
              ts1.tv_sec == ts2.tv_sec && ts1.tv_nsec == ts2.tv_nsec);
    return 0;
}

mu_main(test_clock_gettime_fixed);
