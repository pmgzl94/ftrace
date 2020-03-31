/*
** EPITECH PROJECT, 2019
** tetris
** File description:
** return size
*/

#include "list.h"

int return_size_list(list_t **tab)
{
    list_t *pt = (*tab);
    int count = 0;

    if ((*tab) == NULL)
        return (0);
    do {
        first_become_last(tab);
        count++;
    } while ((*tab) != pt);
    return (count);
}
