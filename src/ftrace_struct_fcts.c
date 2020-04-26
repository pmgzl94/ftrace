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

static void free_sym_list(list_t **list)
{
    while ((*list)) {
        free_symbol_s((*list)->data);
        remove_element(list);
    }
}

void free_lists(list_functions_t *arr_list)
{
    if (arr_list->near_call)
        free_sym_list(&(arr_list->near_call));
    if (arr_list->far_call)
        free_sym_list(&(arr_list->far_call));
    if (arr_list->stack_fcts)
        free_sym_list(&(arr_list->stack_fcts));
}

void free_symbol_s(struct symbol_s *symbol)
{
    free(symbol->name);
    free(symbol);
}