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

list_t *get_functions(char *elf_name);

struct symbol_s *create_symbol_s(char *name, unsigned long addr);
void free_symbol_s(struct symbol_s *symbol);

int display_near_call(pid_t pid, unsigned long long inst, list_t *fct_list, list_t **stack_fcts);

int display_return_call(list_t **stack_fcts, unsigned long long inst);

char *fetch_symbol_name(list_t *fct_list, unsigned long long addr);

#endif
