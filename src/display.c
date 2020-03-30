/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "ref_syscall_snd.h"
#include "ref_syscall_fst.h"
#include "error_handling.h"
#include "strace.h"

static int print_syscall_name(long syscall_number, unsigned short value,
        int *nb_arg)
{
    if (value == 0x050F) {
        printf("%s", ref_syscall_snd[syscall_number].name);
        (*nb_arg) = ref_syscall_snd[syscall_number].nb_args;
    } else if (value == 0x80CD) {
        printf("%s", ref_syscall_fst[syscall_number].name);
        (*nb_arg) = ref_syscall_fst[syscall_number].nb_args;
    }
    return (0);
}

static int print_arg_fst_option(long *syscalls, int nb_arg)
{
    printf("(");
    for (int i = 0; i < nb_arg; i++) {
        printf("0x%x", syscalls[1 + i]);
        if (i + 1 != nb_arg)
            printf(", ");
    }
    fflush(0);
    return (0);
}

int print_return_value(long *syscalls)
{
    printf(") = ");
    printf("0x%x", syscalls[0]);
    printf("\n");
    return (0);
}

int print_return_value_s(long *syscalls)
{
    printf(") = ");
    if (syscalls[0] > 200000000)
        printf("%p", syscalls[0]);
    else
        printf("%d", syscalls[0]);
    printf("\n");
    return (0);
}

int display_syscall(int flag, long *syscalls, unsigned short value, pid_t pid)
{
    int nb_arg = 0;

    print_syscall_name(syscalls[0], value, &nb_arg);
    if (flag & FLAG_S) {
        print_arg_option_s(syscalls[0], value, syscalls, pid);
    } else
        print_arg_fst_option(syscalls, nb_arg);
    return (0);
}
