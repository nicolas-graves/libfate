#include "minunit.h"
#include <sys/sysinfo.h>

static char *test_sysinfo_fixed() {
    struct sysinfo info1, info2;

    int ret1 = sysinfo(&info1);
    int ret2 = sysinfo(&info2);

    mu_assert("sysinfo should succeed", ret1 == 0 && ret2 == 0);
    mu_assert("sysinfo uptime should be fixed", info1.uptime == 42438);
    mu_assert("sysinfo should be consistent",
              info1.uptime == info2.uptime &&
              info1.totalram == info2.totalram &&
              info1.procs == info2.procs);
    return 0;
}

mu_main(test_sysinfo_fixed);
