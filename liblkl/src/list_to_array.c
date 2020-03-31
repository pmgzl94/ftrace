/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** list to array
*/

#include "list.h"

char **complete_array(list_t **list, int size)
{
    char **tab = malloc(sizeof(char *) * (size + 1));
    int i = 0;

    for (i = 0; list; i++) {
        tab[i] = (*list)->data;
        remove_element(list);
    }
    tab[i] = NULL;
    return (tab);
}

char **list_to_array(list_t **list)
{
    int size = return_size_list(list);
    char **tab = NULL;

    if (size != 0) {
        tab = complete_array(list, size);
    }
    return (tab);
}