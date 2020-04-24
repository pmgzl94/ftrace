#include "ftrace.h"
#include "strace.h"

unsigned long long call_abs_ind(pid_t pid, unsigned long long inst)//, list_functions_t **lists_fcts, list_t **stack_fct)
{
    unsigned char reg_opcode = 0;
    long long unsigned addr = 0;
    char *symbol_name;

    isolate_mod_rm(inst >> 8, NULL, &reg_opcode, NULL);
    if (reg_opcode == 3) {
        printf("\ntype 3 !\n");
    }
    if (reg_opcode == 2) {
        // printf("%X %X %X %X %X %X\n", (unsigned char) inst, (unsigned char) (inst >> 8), 
        // (unsigned char) (inst >> 16), (unsigned char) (inst >> 24), (unsigned char) (inst >> 32), (unsigned char) (inst >> 40));
        addr = return_addr_from_modrm(pid, inst);
        // printf("addr = %X\n", addr);
    }
    return (addr);
}

unsigned long long call_rel(pid_t pid)
{
    struct user_regs_struct reg;

    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    waitpid(pid, NULL, 0);
    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    return reg.rip;
}

int display_near_call(pid_t pid, unsigned long long inst, list_functions_t *arr_list, list_t **stack_fcts)
{
    char *symbol_name;
    char *tmp;
    unsigned long long addr = 0;

    if ((unsigned char) (inst) == 0xE8)
        addr = call_rel(pid);
    else if ((unsigned char) (inst) == 0xFF)
        addr = call_abs_ind(pid, inst);
    else {
        //TODO check if go to plt
    }
    if (addr) {
        symbol_name = fetch_symbol_name(arr_list->near_call, addr);
        handle_add_element(stack_fcts);
        if (!symbol_name)
            asprintf(&symbol_name, "func_%#X@%s", addr, "coco");
        else
            symbol_name = strdup(symbol_name);
        (*stack_fcts)->data = symbol_name;
        printf("Entering function %s at %#x\n", symbol_name, addr);
    }
    return (0);
}