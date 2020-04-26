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
//        struct user_regs_struct reg;

//    if (c == 0xC3) {
//        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
//        printf("BEFORE rip = %x\n", reg.rip);
//        printf("BEFORE rsp = %x\n", reg.rsp);
//        printf("BEFORE rbp = %x\n", reg.rbp);
        //TODO need to go to the next step to know if the value is equal to rip before call + 5
        // BUT IF  there is another call at the next instruction then it will be skipped !!!!!!!!!!
//        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
//        waitpid(pid, NULL, 0);
//        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
//        printf("AFTER rip = %x\n", reg.rip);
//    }
    if (*stack_fcts != NULL && c == 0xC3) {
//        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
//        printf("BEFORE rip = %x\n", reg.rip);
//        ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
//        waitpid(pid, NULL, 0);
//        ptrace(PTRACE_GETREGS, pid, NULL, &reg);
//        printf("AFTER rip = %x\n", reg.rip);
//        printf("symb->addr = %x\n", symb->addr);

//        if (symb->addr == rip - 5) {
        symb = (*stack_fcts)->data;
            printf("Leaving function %s\n", symb->name);
//        printf("Leaving function %s\n", (*stack_fcts)->data);
            free_symbol_s(symb);
            remove_element(stack_fcts);
//        }
    }
    return (0);
}