#include "minunit.h"
#include <sys/random.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

static char *test_random() {
    // Test that getrandom gives deterministic sequence
    unsigned char buf1[8];
    unsigned char buf2[8];

    getrandom(buf1, 8, 0);
    getrandom(buf2, 8, 0);

    // Verify deterministic output (based on LCG with seed 0x12345678)
    unsigned char expected1[] = {0x51, 0xb6, 0xb7, 0x24, 0x8d, 0x42, 0x53, 0x90};
    mu_assert("getrandom should produce deterministic sequence",
              memcmp(buf1, expected1, 8) == 0);

    // Test /dev/urandom reading
    int fd = open("/dev/urandom", O_RDONLY);
    mu_assert("/dev/urandom should open", fd >= 0);

    unsigned char urandom_buf[8];
    ssize_t n = read(fd, urandom_buf, 8);
    mu_assert("/dev/urandom read should succeed", n == 8);

    // The sequence continues from where getrandom left off
    // So urandom_buf should NOT match buf1 or buf2, but should be deterministic
    mu_assert("/dev/urandom should produce different bytes than initial getrandom",
              memcmp(urandom_buf, buf1, 8) != 0);

    // Test that another read continues the sequence
    unsigned char urandom_buf2[8];
    n = read(fd, urandom_buf2, 8);
    mu_assert("/dev/urandom second read should succeed", n == 8);
    mu_assert("/dev/urandom should produce different bytes on each read",
              memcmp(urandom_buf, urandom_buf2, 8) != 0);

    close(fd);

    // Test /dev/random as well (should behave the same)
    fd = open("/dev/random", O_RDONLY);
    if (fd >= 0) {
        unsigned char random_buf[4];
        n = read(fd, random_buf, 4);
        mu_assert("/dev/random read should succeed", n == 4);
        close(fd);
    }

    return 0;
}

mu_main(test_random);
