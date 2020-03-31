/*
** EPITECH PROJECT, 2019
** linked_list functions
** File description:
** insert element from one to another
*/

#include "list.h"

void detach_node(list_t **list)
{
    list_t *pt;

    pt = (*list)->next;
    pt->prev = (*list)->prev;
    pt = (*list)->prev;
    pt->next = (*list)->next;
    if ((*list)->next != (*list))
        (*list) = (*list)->next;
    else
        (*list) = NULL;
}

void insert_element(list_t **list, list_t **new_list)
{
    list_t *pt = (*list);

    detach_node(list);
    if ((*new_list) == NULL) {
        (*new_list) = pt;
        (*new_list)->prev = (*new_list);
        (*new_list)->next = (*new_list);
    } else {
        pt->next = (*new_list);
        pt->prev = (*new_list)->prev;
        (*new_list)->prev->next = pt;
        (*new_list)->prev = pt;
        (*new_list) = pt;
    }
}
