#include "ftrace.h"
#include "strace.h"

int check_modrm_byte(long long unsigned inst)
{
    // printf("1-%X\n", ((unsigned char *) &inst)[0]);
    unsigned char mod = inst >> 8;
    // printf("21-%X\n", mod);
    mod = ((unsigned char *) &inst)[1];
    // printf("22-%X\n", mod);
    unsigned char c = (mod >> 3) & 1;
    unsigned char c2 = (mod >> 4) & 1;
    unsigned char c3 = (mod >> 5) & 1;

    printf("%d/%d/%d\n", c3, c2, c);
    // printf("%X\n", mod);
    if (!c && c2 && !c3) {
        return (2);
    }
    if (c && c2 && !c3) {
        return (3);
    }
    return (0);
}

long long unsigned get_addr_from_register(pid_t pid, unsigned char mod_rm)
{
    struct user_regs_struct reg;
    long long unsigned regs[8];
    unsigned char reg_nb = (mod_rm & 1) + ((mod_rm >> 1) & 1) * 2 + ((mod_rm >> 2) & 1) * 4;

    printf("reg nb = %d\n", reg_nb);
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

int call_abs_ind(pid_t pid, long long unsigned inst, list_t **fct_list)
{
    //FF /3
    // unsigned char c = inst;
    int type = 0;

    // printf("ff\n");
    type = check_modrm_byte(inst);
    if (type == 3) {
        // printf("type 3 %d\n!");
        //check si mod == 11
        //retrieve addr
        // long long unsigned a = get_addr_from_register(pid_t pid, unsigned char mod_rm, int type);
        // char *name = fetch_symbol_name(fct_list, a);
        // if (name == NULL) {
        //     //fetch push
        // }
    }
    if (type == 2) {
        // printf("type 2\n");
        unsigned char mod_rm = inst >> 8;
        if (((mod_rm >> 6) & 1) && ((mod_rm >> 7) & 1)) {
            //is reg
            printf("is reg!\n");
            printf("addr = %X\n", get_addr_from_register(pid, mod_rm));
        }
        //     printf("1 number = %d\n", (c) & 1);
        //     printf("2 number = %d\n", (c >> 1) & 1);
        //     printf("4 number = %d\n", (c >> 2) & 1);
        //     printf("%X\n", get_addr_from_register(pid, c));
    }
    return (0);
}