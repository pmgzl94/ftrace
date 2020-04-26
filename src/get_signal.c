/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "signals.h"
#include "strace.h"

int get_signal(pid_t pid)
{
    siginfo_t siginf;

    bzero(&siginf, sizeof(siginfo_t));
    ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginf);
    if (siginf.si_signo == 0 || siginf.si_signo == 5) {
        return (1);
    }
    for (int i = 0; i < 65; i++) {
        if (signal_array[i].key  == siginf.si_signo) {
            printf("Received signal %s\n",
                signal_array[i].value);
        }
    }
    return (0);
}