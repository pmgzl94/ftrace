/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** destroy element list
*/

#include "list.h"

int remove_element(list_t **tab)
{
    list_t *pt;

    if ((*tab)->prev == *tab) {
        free(*tab);
        *tab = NULL;
        return (0);
    } else {
        pt = (*tab)->next;
        pt->prev = (*tab)->prev;
        pt->prev->next = pt;
        free((*tab));
        (*tab) = NULL;
        *tab = pt;
        return (1);
    }
}

void remove_whole_list(list_t **tab)
{
    while (remove_element(tab) == 1);
}
