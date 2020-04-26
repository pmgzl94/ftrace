/*
** EPITECH PROJECT, 2020
** strace
** File description:
** strace
*/

#ifndef STRACE_H_
#define STRACE_H_
#define _GNU_SOURCE

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include "ref_syscall.h"
#include "ftrace.h"

struct info_elf {
    long long unsigned start_address;
};

int strace(int ac, char **av, char **env);

char **get_args(int ac, char **av);

void get_registers(pid_t pid, struct user_regs_struct *reg,
        unsigned short value, long *args_syscall);
int browse_instructions(pid_t pid, char flag, long *syscall,
        list_functions_t *arr_list);

int trace_pid(pid_t pid, char flag);

int trace_program(int ac, char **av, char **env, char flag);

int get_info_elf_file(struct info_elf *infos, char *filename);

int display_syscall(int flag, long *syscalls, unsigned short value, pid_t pid);
int print_return_value(long *syscalls);
int print_arg_option_s(long syscall_number, unsigned short value,
        long *syscalls, pid_t pid);
int print_return_value_s(long *syscalls);
int syscall_read(long *syscalls, unsigned short syscall_type, pid_t pid,
        struct user_regs_struct reg);

int display_array(pid_t pid, long *args_syscall, ref_syscall_t *sys,
        int reg_idx);


#endif
