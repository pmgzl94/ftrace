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

struct symbol_s {
    unsigned long addr;
    char *name;
};

list_t *get_functions(char *elf_name);

struct symbol_s *create_symbol_s(char *name, unsigned long addr);
void free_symbol_s(struct symbol_s *symbol);



#endif
