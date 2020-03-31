/*
** EPITECH PROJECT, 2019
** linked_list function
** File description:
** function to swap two nodes
*/

#include "list.h"

void swap_first_element(list_t **tab)
{
    list_t *pt;
    list_t *pt2;

    if (tab == NULL || (*tab)->next == NULL)
        return;
    pt = *tab;
    pt2 = pt->next;
    pt->next = pt2->next;
    pt2->next->prev = pt;
    pt2->prev = pt->prev;
    pt->prev->next = pt2;
    pt->prev = pt2;
    pt2->next = pt;
    *tab = pt2;
}

void swap_elements(list_t *element, list_t *element2, list_t **list)
{
    list_t *pt;

    if (element == *list) {
        *list = element2;
    } else if (element2 == *list)
        *list = element;
    pt = element->next;
    element->next = element2->next;
    element2->next = pt;
    element->next->prev = element;
    element2->next->prev = element2;
    pt = element->prev;
    element->prev = element2->prev;
    element2->prev = pt;
    element->prev->next = element;
    element2->prev->next = element2;
}
