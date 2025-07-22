#define _GNU_SOURCE
#include <sys/random.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <stdio.h>

// Simple deterministic PRNG (LCG)
static uint32_t seed = 0x12345678;

static uint32_t next_rand() {
    seed = seed * 1103515245 + 12345;
    return seed;
}

// Override getrandom syscall
ssize_t getrandom(void *buf, size_t buflen, unsigned int flags) {
    unsigned char *bytes = (unsigned char *)buf;
    for (size_t i = 0; i < buflen; i++) {
        bytes[i] = next_rand() & 0xFF;
    }
    return buflen;
}

// Override /dev/urandom reads
ssize_t read(int fd, void *buf, size_t count) {
    static ssize_t (*real_read)(int, void *, size_t) = NULL;

    if (!real_read) {
        real_read = dlsym(RTLD_NEXT, "read");
    }

    // Check if this is /dev/urandom by examining fd
    char path[256];
    snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);
    char target[256];
    ssize_t len = readlink(path, target, sizeof(target) - 1);
    if (len > 0) {
        target[len] = '\0';
        if (strstr(target, "/dev/urandom") || strstr(target, "/dev/random")) {
            unsigned char *bytes = (unsigned char *)buf;
            for (size_t i = 0; i < count; i++) {
                bytes[i] = next_rand() & 0xFF;
            }
            return count;
        }
    }

    return real_read(fd, buf, count);
}
