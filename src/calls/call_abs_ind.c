#include "ftrace.h"
#include "strace.h"

// int check_modrm_byte(long long unsigned inst)
// {
//     // printf("1-%X\n", ((unsigned char *) &inst)[0]);
//     unsigned char mod = inst >> 8;
//     // printf("21-%X\n", mod);
//     mod = ((unsigned char *) &inst)[1];
//     // printf("22-%X\n", mod);
//     unsigned char c = (mod >> 3) & 1;
//     unsigned char c2 = (mod >> 4) & 1;
//     unsigned char c3 = (mod >> 5) & 1;

//     // printf("%d/%d/%d\n", c3, c2, c);
//     // printf("%X\n", mod);
//     if (!c && c2 && !c3) {
//         return (2);
//     }
//     if (c && c2 && !c3) {
//         return (3);
//     }
//     return (0);
// }


long long unsigned get_addr_from_register(pid_t pid, unsigned char mod_rm)
{
    struct user_regs_struct reg;
    long long unsigned regs[8];
    unsigned char reg_nb = (mod_rm & 1) + ((mod_rm >> 1) & 1) * 2 + ((mod_rm >> 2) & 1) * 4;

    // printf("reg nb = %d\n", reg_nb);
    ptrace(PTRACE_GETREGS, pid, &reg);
    regs[0] = reg.rax;
    regs[1] = reg.rcx;
    regs[2] = reg.rdx;
    regs[3] = reg.rbx;
    regs[4] = reg.rsp;
    regs[5] = reg.rbp;
    regs[6] = reg.rsi;
    regs[7] = reg.rdi;
    return (regs[reg_nb]);
}
//mod = 0
unsigned long long handle_fst_range_modrm(pid_t pid, long long unsigned inst, unsigned char rm)
{
    struct user_regs_struct reg;
    unsigned long long addr;

    ptrace(PTRACE_GETREGS, pid, &reg);
    if (rm == 7) {
        printf("\nsib\n");
        (-1); //SIB
    }
    if (rm == 8) {
        //addr
        return (inst >> 16);
    }
    else {
        addr = get_addr_from_register(pid, inst >> 8);
        return (ptrace(PTRACE_PEEKTEXT, pid, addr, NULL));
    }
}

unsigned long long handle_snd_range_modrm(pid_t pid, long long unsigned inst, unsigned char rm)
{
    struct user_regs_struct reg;
    unsigned long long addr;

    ptrace(PTRACE_GETREGS, pid, &reg);
    if (rm == 7) {
        printf("\nsib\n");
        (-1); //SIB
    }
    else {
        addr = get_addr_from_register(pid, inst >> 8);
        return (ptrace(PTRACE_PEEKTEXT, pid, addr, NULL));
    }
}


void isolate(unsigned char mod_rm, unsigned char *mod, unsigned char *reg, unsigned char *rm)
{
    if (mod)
       *mod = ((mod_rm >> 6) & 1) + ((mod_rm >> 7) & 1) * 2;
    if (reg)
       *reg = ((mod_rm >> 3) & 1) + ((mod_rm >> 4) & 1) * 2 + ((mod_rm >> 5) & 1) * 4;
    if (rm)
       *rm = (mod_rm & 1) + ((mod_rm >> 1) & 1) * 2 + ((mod_rm >> 2) & 1) * 4;
}

unsigned long long return_addr_from_modrm(pid_t pid, unsigned long long inst)
{
    unsigned char mod_rm = inst >> 8;
    unsigned char mod = 0;
    unsigned char rm = 0;
    unsigned long long addr = 0;

    isolate(mod_rm, &mod, NULL, &rm);

    // printf("mod = %d\n", mod);
    if (mod == 0)
        addr = handle_fst_range_modrm(pid, inst, rm);
    if (mod == 1) {
        //8bit
        addr = handle_fst_range_modrm(pid, inst, rm) + (inst >> 16);
    }
    if (mod == 2) {
        //32bit
        addr = handle_fst_range_modrm(pid, inst, rm) + (inst >> 16);
    }
    if (mod == 3)
        addr = get_addr_from_register(pid, mod_rm);
    return (addr);
}




int call_abs_ind(pid_t pid, long long unsigned inst, list_t **fct_list)
{
    //FF /3
    // unsigned char c = inst;
    // int type = 0;
    unsigned char reg_opcode = 0;
    isolate(inst >> 8, NULL, &reg_opcode, NULL);

    // printf("ff\n");
    // reg_opcode = check_modrm_byte(inst);
    if (reg_opcode == 3) {
        printf("\ntype 3 !\n");
        //check si mod == 11
        //retrieve addr
        // long long unsigned a = get_addr_from_register(pid_t pid, unsigned char mod_rm, int type);
        // char *name = fetch_symbol_name(fct_list, a);
        // if (name == NULL) {
        //     //fetch push
        // }
    }
    if (reg_opcode == 2) {
        // printf("%X %X %X %X %X %X\n", (unsigned char) inst, (unsigned char) (inst >> 8), (unsigned char) (inst >> 16), (unsigned char) (inst >> 24), (unsigned char) (inst >> 32), (unsigned char) (inst >> 40));
        // printf("type 2\n");
        long long unsigned addr = return_addr_from_modrm(pid, inst);
        // printf("addr = %X\n", addr);
            // printf("addr = %X\n", get_addr_from_register(pid, mod_rm));
        char *symbol_name = fetch_symbol_name((*fct_list), addr);
            if (symbol_name) {
                printf("enter in %s\n", symbol_name);
            }
    }
        //     printf("1 number = %d\n", (c) & 1);
        //     printf("2 number = %d\n", (c >> 1) & 1);
        //     printf("4 number = %d\n", (c >> 2) & 1);
        //     printf("%X\n", get_addr_from_register(pid, c));
    return (0);
}