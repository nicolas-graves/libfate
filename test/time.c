#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
    struct timespec ts;
    struct timeval tv;
    time_t t;

    // Test clock_gettime
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("clock_gettime: %ld.%09ld\n", ts.tv_sec, ts.tv_nsec);

    return 0;
}
