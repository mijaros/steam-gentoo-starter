#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define CHROOT_SCRIPT "/usr/local/bin/steam-chroot"

int main()
{
    uid_t uid = geteuid();
    if (setuid(uid)) {
        fprintf(stderr, "setuid failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (execl(CHROOT_SCRIPT, CHROOT_SCRIPT)) {
        fprintf(stderr, "execl failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

