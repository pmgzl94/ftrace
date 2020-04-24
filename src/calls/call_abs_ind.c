#include "ftrace.h"
#include "strace.h"

int call_abs_ind(pid_t pid, long long unsigned inst, list_t **fct_list)
{
    unsigned char reg_opcode = 0;

    isolate_mod_rm(inst >> 8, NULL, &reg_opcode, NULL);
    if (reg_opcode == 3) {
        printf("\ntype 3 !\n");

    }
    if (reg_opcode == 2) {
        // printf("%X %X %X %X %X %X\n", (unsigned char) inst, (unsigned char) (inst >> 8), 
        // (unsigned char) (inst >> 16), (unsigned char) (inst >> 24), (unsigned char) (inst >> 32), (unsigned char) (inst >> 40));
        long long unsigned addr = return_addr_from_modrm(pid, inst);
        printf("addr = %X\n", addr);
        char *symbol_name = fetch_symbol_name((*fct_list), addr);
            if (symbol_name) {
                printf("enter in %s\n", symbol_name);
            }
    }
    return (0);
}