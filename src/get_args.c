/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "error_handling.h"

static int is_a_flag(char *str)
{
    for (int i = 0; i < 4; i++) {
        if (!strcmp(array_flags[i].key, str)) {
            return (0);
        }
    }
    return (1);
}

static char **return_args(int ac, char **av, int index)
{
    int size = (ac - index + 1);
    char **args = malloc(sizeof(char *) * size);
    int i = 0;

    for (i = 0; i < size; i++, index++)
        args[i] = av[index];
    return (args);
}

char **get_args(int ac, char **av)
{
    int i = 0;

    for (i = 1; av[i]; i++) {
        if (is_a_flag(av[i])) {
            return (return_args(ac, av, i));
        }
    }
    return (return_args(ac, av, i));
}
