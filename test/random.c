#include "minunit.h"
#include <sys/random.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

static char *test_getrandom_deterministic() {
    // Test that restarting gives same sequence
    unsigned char expected[] = {0x51, 0xb6, 0xb7, 0x24, /* ... */};
    unsigned char buf[4];
    getrandom(buf, 4, 0);
    mu_assert("getrandom should start with known sequence",
              memcmp(buf, expected, 4) == 0);
    return 0;
}

mu_main(test_getrandom_deterministic);
