/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "ftrace.h"

struct symbol_s *create_symbol_s(char *name, unsigned long addr)
{
    struct symbol_s *symbol = malloc(sizeof(struct symbol_s));

    if (symbol) {
        symbol->name = strdup(name);
        symbol->addr = addr;
    } else
        fprintf(stderr, "symbol_s creation failed\n");
    return (symbol);
}

void free_symbol_s(struct symbol_s *symbol)
{
    free(symbol->name);
    free(symbol);
}