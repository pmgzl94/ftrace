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

static int print_word(unsigned char *str, int pos, int i, int end)
{
    char *arr[7] = {"\\a", "\\b", "\\t", "\\n", "\\v", "\\f", "\\r"};

    fflush(0);
    for (i = 0; i < 8 && pos + i < end && pos + i < 32; ++i) {
        if (str[i] < 7 || str[i] > 126 || (str[i] > 13 && str[i] < 32))
            printf("\\%d", str[i]);
        else if (str[i] > 6 && str[i] < 14)
            printf("%s", arr[str[i] - 7]);
        else
            write(1, &(str[i]), 1);
        fflush(0);
    }
    return (i);
}

static void print_string(int pos, long *syscalls, pid_t pid,
        ref_syscall_t syscall)
{
    unsigned char *str;
    unsigned long long tmp;
    int i = 0;
    int i2 = 0;

    printf("\"");
    fflush(0);
    for (; i2 * 8 < 32; i2++) {
        tmp = ptrace(PTRACE_PEEKTEXT, pid, (syscalls[pos] + i2 * 8), NULL);
        str = (unsigned char *)(&tmp);
        if (strcmp(syscall.name, "read") == 0 ||
            strcmp(syscall.name, "write") == 0)
            i = print_word(str, i2 * 8, i, syscalls[3]);
        else
            for (i = 0; str[i] && i < 8; ++i)
                write(1, &(str[i]), 1);
        if (i != 8)
            break;
    }
    i + i2 * 8 >= 32 ? printf("\"...") : printf("\"");
}

static int check_type(ref_syscall_t sys, pid_t pid,
        long *syscalls, int i)
{
    int tmp = sys.args[i];

    if (tmp & INT || tmp & FLAG)
        printf("%d", syscalls[i + 1]);
    if (tmp & STRING)
        print_string(i + 1, syscalls, pid, sys);
    if (tmp & ADDR || tmp & STRUCT)
        syscalls[i + 1] == 0 ? printf("NULL") :
            printf("%p", syscalls[i + 1]);
    if (tmp & UNDEFINED)
        printf("0x%x", syscalls[i + 1]);
    return (0);
}

int print_arg_option_s(long syscall_number, unsigned short value,
        long *syscalls, pid_t pid)
{
    int arg_type = 0;
    ref_syscall_t sys = value == 0x80CD ? ref_syscall_fst[syscall_number] :
                        ref_syscall_snd[syscall_number];

    printf("(");
    for (int i = 0; i < sys.nb_args; i++) {
        fflush(0);
        arg_type = sys.args[i];
        if (arg_type & ARRAY) {
            display_array(pid, syscalls, &sys, i + 1);
        } else
            check_type(sys, pid, syscalls, i);
        if (i + 1 != sys.nb_args)
            printf(", ");
    }
    return (0);
}

int syscall_read(long *syscalls, unsigned short syscall_type, pid_t pid,
        struct user_regs_struct reg)
{
    unsigned char *str;
    unsigned long long tmp;
    int status = 0;
    int i = 8;
    int i2 = 0;

    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    waitpid(pid, &status, 0);
    get_signal(pid);
    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    get_registers(pid, &reg, syscall_type, syscalls);
    printf("\"");
    for (; i2 * 8 < 32 && i == 8; i2++) {
        tmp = ptrace(PTRACE_PEEKTEXT, pid, (syscalls[2] + i2 * 8), NULL);
        str = (unsigned char *)(&tmp);
        i = print_word(str, i2 * 8, i, syscalls[3]);
    }
    i + i2 * 8 >= 32 ? printf("\"..., %d) = %d\n", syscalls[3], syscalls[0]) :
        printf("\", %d) = %d\n", syscalls[3], syscalls[0]);
    return (status);
}
