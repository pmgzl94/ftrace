/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"
#include "ref_syscall.h"
#include <string.h>

int print_text(pid_t pid, long string_addr)
{
    char *str = calloc(1, 4096);
    long u = 0;
    char *tmp = 0;
    int pos = 0;
    int i = 0;

    for (int i2 = 0; 1; i2 = 0, i++) {
        u = ptrace(PTRACE_PEEKTEXT, pid, (string_addr + 8 * i), NULL);
        tmp = (char *) (&u);
        for (; i2 < 8 && tmp[i2]; i2++, pos++)
            str[pos] = tmp[i2];
        if (!tmp[i2] || pos >= 32)
            break;
    }
    printf("\"%s\"", str);
    if (pos >= 32)
        printf("...");
    free(str);
    return (0);
}

int browse_array(pid_t pid, long *args_syscall, int reg_idx)
{
    long addr = 1;
    int i = 0;

    printf("[");
    while (addr) {
        addr = ptrace(PTRACE_PEEKTEXT, pid,
                (args_syscall[reg_idx] + 8 * i), NULL);
        if (!addr)
            break;
        else if (i != 0)
            printf(", ");
        if (i == 32) {
            printf("...");
            break;
        } else
            print_text(pid, addr);
        i++;
    }
    printf("]");
    return (0);
}

static int count_nb_of_pointer(pid_t pid, long *args_syscall, int reg_idx)
{
    long addr = 1;
    int i = 0;

    while (addr) {
        addr = ptrace(PTRACE_PEEKTEXT, pid, (args_syscall[reg_idx] + 8 * i),
                NULL);
        i++;
    }
    return (i - 1);
}

int display_array(pid_t pid, long *args_syscall, ref_syscall_t *sys,
        int reg_idx)
{
    if (sys->args[reg_idx - 1] & STRING
        && !(reg_idx == 3 && !strcmp(sys->name, "execve"))) {
        browse_array(pid, args_syscall, reg_idx);
    }
    else if (sys->args[reg_idx - 1] & STRING) {
        printf("%p /* %d vars */", args_syscall[reg_idx],
                count_nb_of_pointer(pid, args_syscall, reg_idx));
    }
    else
        printf("%p", args_syscall[reg_idx]);
    return (0);
}
