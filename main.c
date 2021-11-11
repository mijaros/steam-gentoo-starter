#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define STR(A) #A
#define EVAL_STR(A) STR(A)

#define SCRIPT_NAME "/steam-chroot"

#ifndef TARGET_DIR
#error "TARGET_DIR macro not specified"
#endif

#define TARGET_DIR_STR EVAL_STR(TARGET_DIR)
#define CHROOT_SCRIPT TARGET_DIR_STR SCRIPT_NAME

int main(int argc, char *argv[])
{
    uid_t uid = geteuid();
    if (setuid(uid)) {
        fprintf(stderr, "setuid failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    char *exec_argv[argc+1]; //Make space for past-the-end NULL
    exec_argv[0] = CHROOT_SCRIPT; //Change argv[0] to correct value
    for (int i = 1; i <= argc; i++) { // Copy including NULL
        exec_argv[i] = argv[i];
    }

    if (execvp(CHROOT_SCRIPT, exec_argv)) {
        fprintf(stderr, "execvp failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

