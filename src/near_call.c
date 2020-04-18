#include "ftrace.h"
#include "strace.h"

int display_near_call(pid_t pid, unsigned long long inst, list_t *fct_list, list_t **stack_fcts)
{
    struct user_regs_struct reg;
    char *symbol_name;

    if ((unsigned char) (inst) == 0xE8) {
            ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
            waitpid(pid, NULL, 0);
            ptrace(PTRACE_GETREGS, pid, NULL, &reg);
            symbol_name = fetch_symbol_name(fct_list, reg.rip);
            if (symbol_name) {
                printf("Entering function %s at %#x\n", symbol_name, reg.rip);
                handle_add_element(stack_fcts);
                (*stack_fcts)->data = symbol_name;
            }
    }
    //else (0xFF/2)
    return (0);
}