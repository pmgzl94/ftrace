/*
** EPITECH PROJECT, 2018
** my_pushswap
** File description:
** init_tab
*/

#include "list.h"

int handle_add_element(list_t **tab)
{
    if (*tab == NULL) {
        if (add_first_element(tab) == 84)
            return (84);
    } else {
        if (add_element(tab) == 84)
            return (84);
    }
    return (0);
}

int add_first_element(list_t **tab)
{
    list_t *element = malloc(sizeof(struct list));

    if (element == NULL)
        return (84);
    element->next = element;
    element->prev = element;
    *tab = element;
    return (0);
}

int add_element(list_t **tab)
{
    list_t *element = malloc(sizeof(list_t));

    if (element == NULL)
        return (84);
    element->prev = (*tab)->prev;
    (*tab)->prev->next = element;
    (*tab)->prev = element;
    element->next = *tab;
    *tab = element;
    return (0);
}
