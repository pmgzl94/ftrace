#include "strace.h"
#include "ftrace.h"

long long unsigned get_addr_from_register(pid_t pid, unsigned char mod_rm)
{
    struct user_regs_struct reg;
    long long unsigned regs[8];
    unsigned char reg_nb = (mod_rm & 1) + ((mod_rm >> 1) & 1) * 2 + ((mod_rm >> 2) & 1) * 4;

    ptrace(PTRACE_GETREGS, pid, NULL,  &reg);
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

unsigned long long handle_fst_range_modrm(pid_t pid, long long unsigned inst, unsigned char rm)
{
    struct user_regs_struct reg;
    unsigned long long addr;

    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    if (rm == 7) {
//        printf("\nsib\n");
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

    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    if (rm == 7) {
//        printf("\nsib\n");
        (-1); //SIB
    }
    else {
        addr = get_addr_from_register(pid, inst >> 8);
        return (ptrace(PTRACE_PEEKTEXT, pid, addr, NULL));
    }
}

void isolate_mod_rm(unsigned char mod_rm, unsigned char *mod, unsigned char *reg, unsigned char *rm)
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

    isolate_mod_rm(mod_rm, &mod, NULL, &rm);

    // printf("mod = %d\n", mod);
    if (mod == 0)
        addr = handle_fst_range_modrm(pid, inst, rm);
    if (mod == 1) {
        //8bit
//        printf("mod = 1\n");
        addr = handle_snd_range_modrm(pid, inst, rm) + (unsigned char) (inst >> 16);
    }
    if (mod == 2) {
        //32bit
//        printf("mod = 2\n");
        addr = handle_snd_range_modrm(pid, inst, rm) + (unsigned int) (inst >> 16);
    }
    if (mod == 3) {
//        printf("registre\n");
        addr = get_addr_from_register(pid, mod_rm);
    }
    return (addr);
}
