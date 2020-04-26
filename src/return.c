/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"

int display_return_call(list_t **stack_fcts, unsigned long long inst, pid_t pid)
{
    unsigned char c = inst;
    struct symbol_s *symb;
    struct user_regs_struct reg;

    if (*stack_fcts != NULL && c == 0xC3) {
        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
        waitpid(pid, NULL, 0);
        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
        symb = (*stack_fcts)->data;
        if (symb->addr == reg.rip) {
            printf("Leaving function %s\n", symb->name);
            free_symbol_s(symb);
            remove_element(stack_fcts);
        }
        return (1);
    }
    return (0);
}