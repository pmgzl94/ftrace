/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** filter_list
*/

#include "list.h"

void filter_list(list_t **list, fpt fonction_filter)
{
  int size = return_size_list(list);

  while (size--) {
    if (fonction_filter((*list)->data) == 0) {
      remove_element(list);
    } else {
      first_become_last(list);
    }
  }
}
