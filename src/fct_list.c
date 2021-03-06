/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "ftrace.h"

char *fetch_symbol_name(list_t *fct_list, unsigned long long addr)
{
    list_t *head = fct_list;
    struct symbol_s *symbol;

    if (!fct_list)
        return (NULL);
    do {
        symbol = fct_list->data;
        if (addr == symbol->addr)
            return symbol->name;
        first_become_last(&fct_list);
    } while (fct_list != head);
    return (NULL);
}