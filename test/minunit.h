/* MinUnit - A minimal unit testing framework for C
 * http://www.jera.com/techinfo/jtns/jtn002.html
 * Adapted for a single test per file.
 */
#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>
#include <string.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)

#define mu_main(test_func) \
int main() { \
    char *result = test_func(); \
    if (result) { \
        printf("FAILED: %s\n", result); \
        return 1; \
    } \
    printf("Test passed!\n"); \
    return 0; \
}

#endif
