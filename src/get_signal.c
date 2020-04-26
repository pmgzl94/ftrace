#include "signals.h"
#include "strace.h"

int get_signal(pid_t pid)
{
    siginfo_t siginf;

    // printf("la\n");
    bzero(&siginf, sizeof(siginfo_t));
    ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginf);
    if (siginf.si_signo != 0) {
        // printf("la %d\n", siginf.si_signo);
//        printf("sig info = %d\n", siginf.si_signo);
        // for (int i = 0; i < 65; i++) {

        // }
    }
    return (0);
}