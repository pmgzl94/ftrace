/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#ifndef FTRACE_H_
#define FTRACE_H_

#include "list.h"

#include <libelf.h>
#include <gelf.h>
#include <stdio.h>
#include <string.h>

#define SYSCALL 1
#define RET 2
#define NEAR_CALL_REL_ADDR 3

struct symbol_s {
    unsigned long addr;
    char *name;
};

typedef struct list_functions_s {
    list_t *near_call;
    list_t *far_call;
} list_functions_t;

Elf_Scn *find_symbol_section(Elf *elf);
list_t *get_functions(char *elf_name);

list_t *check_rel_rela(char *elf_name);

struct symbol_s *create_symbol_s(char *name, unsigned long addr);
void free_symbol_s(struct symbol_s *symbol);

int display_near_call(pid_t pid, unsigned long long inst, list_t *fct_list, list_t **stack_fcts);

int display_return_call(list_t **stack_fcts, unsigned long long inst);

char *fetch_symbol_name(list_t *fct_list, unsigned long long addr);

int call_abs_ind(pid_t pid, long long unsigned inst, list_t **fct_list);

unsigned long long return_addr_from_modrm(pid_t pid, unsigned long long inst);
void isolate_mod_rm(unsigned char mod_rm, unsigned char *mod, unsigned char *reg, unsigned char *rm);

#endif