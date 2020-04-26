/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "ftrace.h"

int display_return_call(list_t **stack_fcts, unsigned long long inst)
{
    unsigned char c = inst;

    if (*stack_fcts != NULL && c == 0xC3) {
        printf("Leaving function %s\n", (*stack_fcts)->data);
        remove_element(stack_fcts);
    }
    return (0);
}