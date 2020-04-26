/*
** EPITECH PROJECT, 2020
** strace
** File description:
** strace
*/

#include "strace.h"
#include "ref_syscall_fst.h"
#include "ref_syscall_snd.h"
#include "error_handling.h"
#include <sys/user.h>

int trace_pid(pid_t pid, char flag)
{
    long *args_syscall = malloc(sizeof(long) * 8);
    int return_value = 0;

    if (ptrace(PTRACE_ATTACH, pid, NULL, NULL)) {
        fprintf(stderr,
        "strace: attach: ptrace(PTRACE_SEIZE, %d): No such process\n", pid);
        return (84);
    }
    waitpid(pid, NULL, 0);
    // return_value = read_syscall(pid, flag, args_syscall); //TODO what to do with this?????????
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    return (return_value);
}
