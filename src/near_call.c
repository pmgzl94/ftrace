/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"

void get_plt_addrs(char *elf_name, list_functions_t *arr_list)
{
    int fd = open(elf_name, O_RDONLY);
    Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
    GElf_Shdr shdr;
    GElf_Ehdr ehdr;
    Elf_Scn *scn = NULL;
    size_t shstrndx = 0;
    int index = 0;

    elf_getshdrstrndx(elf, &shstrndx);
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (strcmp(elf_strptr(elf, shstrndx, shdr.sh_name), ".plt") == 0) {
            arr_list->start_plt = shdr.sh_addr;
            index = 1;
        } else if (index == 1) {
            arr_list->end_plt = shdr.sh_addr;
            index = 0;
        }
    }
    elf_end(elf);
    close(fd);
}

unsigned long long call_abs_ind(pid_t pid, unsigned long long inst)
{
    unsigned char reg_opcode = 0;
    long long unsigned addr = 0;
    char *symbol_name;

    isolate_mod_rm(inst >> 8, NULL, &reg_opcode, NULL);
    if (reg_opcode == 3) {
        fprintf(stderr, "\ntype 3 !\n");
    }
    if (reg_opcode == 2) {
        addr = return_addr_from_modrm(pid, inst);
    }
    return (addr);
}

unsigned long long call_rel(pid_t pid, unsigned long long *rsp)
{
    struct user_regs_struct reg;

    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
    waitpid(pid, NULL, 0);
    get_signal(pid);
    ptrace(PTRACE_GETREGS, pid, NULL, &reg);
    *rsp = ptrace(PTRACE_PEEKTEXT, pid, reg.rsp, NULL);
    return reg.rip;
}

static int check_plt(pid_t pid, unsigned long long rip,
        list_functions_t *arr_list, unsigned long long rsp)
{
    char *symbol_name;
    unsigned long long inst;

    inst = (int)ptrace(PTRACE_PEEKTEXT, pid, rip + 2);
    if (rip > arr_list->start_plt && rip < arr_list->end_plt &&
            !fetch_symbol_name(arr_list->near_call, rip)) {
        symbol_name = fetch_symbol_name(arr_list->far_call, (rip + 0x6 + inst));
        if (!symbol_name || strcmp(symbol_name, "exit") == 0)
            return (1);
        handle_add_element(&(arr_list->stack_fcts));
        arr_list->stack_fcts->data = create_symbol_s(symbol_name, rsp);
        printf("Entering function %s at %#x\n", symbol_name, rip);
        return (0);
    }
    return (1);
}

int display_near_call(pid_t pid, unsigned long long inst,
        list_functions_t *arr_list, unsigned long long rsp)
{
    char *symbol_name;
    char *tmp;
    unsigned long long addr = 0;

    if ((unsigned char) (inst) == 0xE8)
        addr = call_rel(pid, &rsp);
    else if ((unsigned char) (inst) == 0xFF)
        addr = call_abs_ind(pid, inst);
    if ((unsigned char) (inst) == 0xE8 &&
        check_plt(pid, addr, arr_list, rsp) == 0)
        return (0);
    if (addr) {
        symbol_name = fetch_symbol_name(arr_list->near_call, addr);
        if (!symbol_name && arr_list->is_stripped == 0)
            return (0);
        if (!symbol_name)
            asprintf(&symbol_name, "func_%#X@%s", addr, arr_list->elf_name);
        else
            symbol_name = strdup(symbol_name);
        handle_add_element(&(arr_list->stack_fcts));
        arr_list->stack_fcts->data = create_symbol_s(symbol_name, rsp);
        printf("Entering function %s at %#x\n", symbol_name, addr);
        free(symbol_name);
    }
    return (0);
}