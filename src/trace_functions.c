/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"
#include "error_handling.h"
#include "ref_syscall_snd.h"
#include "ref_syscall_fst.h"
#include "ref_syscall.h"
#include "ftrace.h"

void get_registers(pid_t pid, struct user_regs_struct *reg,
        unsigned short value, long *args_syscall)
{
    args_syscall[0] = reg->rax;
    if (value == 0x80CD) {
        args_syscall[1] = reg->rbx;
        args_syscall[2] = reg->rcx;
        args_syscall[3] = reg->rdx;
        args_syscall[4] = reg->rsi;
        args_syscall[5] = reg->rdi;
        args_syscall[6] = reg->rbp;
    } else if (value == 0x050F) {
        args_syscall[1] = reg->rdi;
        args_syscall[2] = reg->rsi;
        args_syscall[3] = reg->rdx;
        args_syscall[4] = reg->r10;
        args_syscall[5] = reg->r8;
        args_syscall[6] = reg->r9;
    }
}

static int check_read(long *syscalls, unsigned short syscall_type)
{
    ref_syscall_t sys = syscall_type == 0x80CD ? ref_syscall_fst[syscalls[0]] :
                        ref_syscall_snd[syscalls[0]];

    if (strcmp(sys.name, "read") == 0) {
        printf("%s(%d, ", sys.name, syscalls[1]);
        return (1);
    }
    return (0);
}

static int get_and_print_syscall(pid_t pid, char flag, long *args_syscall,
        struct user_regs_struct reg)
{
    int status = 0;
    unsigned short syscall_type;

    syscall_type = (unsigned short)ptrace(PTRACE_PEEKTEXT, pid, reg.rip, NULL);
    get_registers(pid, &reg, syscall_type, args_syscall);
    if (flag & FLAG_S && check_read(args_syscall, syscall_type) == 1)
        return (syscall_read(args_syscall, syscall_type, pid, reg));
    display_syscall(flag, args_syscall, syscall_type, pid);
    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    waitpid(pid, &status, 0);
    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    get_registers(pid, &reg, syscall_type, args_syscall);
    if (!WIFEXITED(status))
        if (flag & FLAG_S) {
            print_return_value_s(args_syscall);
        } else
            print_return_value(args_syscall);
    return (status);
}

int read_syscall(pid_t pid, char flag, long *args_syscall, list_t *fct_list)
{
    int status = 0;
    struct user_regs_struct reg;
    unsigned short syscall_type;
    list_t *stack_fcts = NULL;
    unsigned char c;
    unsigned long long inst;

    while (1) {
        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
        syscall_type = (unsigned short)ptrace(PTRACE_PEEKTEXT, pid, reg.rip,
                NULL);
        inst = ptrace(PTRACE_PEEKTEXT, pid, reg.rip, NULL);
        c = ((unsigned char *) &inst)[0];
        // printf("%X\n", c);
        if (syscall_type == 0x80CD || syscall_type == 0x050F) {
            status = get_and_print_syscall(pid, flag, args_syscall, reg);
            if (WIFEXITED(status)) {
                printf(") = ?\n");
                printf("+++ exited with %d +++\n", WEXITSTATUS(status));
                return (WEXITSTATUS(status));
            }
        } else if (c == 0xE8) {
            display_near_call(pid, inst, fct_list, &stack_fcts);
        }
        else if (c == 0xC3 || c == 0xCB) {
            display_return_call(&stack_fcts, inst);
        }
        else if (c == 0xFF) {
            // call_abs_ind(pid, inst, &fct_list);
        }
        //check_ret
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        waitpid(pid, &status, 0);
    }
}
