#include <stdio.h>
#include <sys/random.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    unsigned char buf[16];

    // Test 1: getrandom()
    printf("getrandom() results:\n");
    if (getrandom(buf, sizeof(buf), 0) == sizeof(buf)) {
        for (int i = 0; i < sizeof(buf); i++) {
            printf("%02x ", buf[i]);
        }
        printf("\n");
    }

    // Test 2: /dev/urandom
    printf("/dev/urandom results:\n");
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
        if (read(fd, buf, sizeof(buf)) == sizeof(buf)) {
            for (int i = 0; i < sizeof(buf); i++) {
                printf("%02x ", buf[i]);
            }
            printf("\n");
        }
        close(fd);
    }

    return 0;
}
