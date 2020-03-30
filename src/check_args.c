/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "error_handling.h"
#include <ctype.h>

static int is_number(char *str)
{
    int i = 0;

    while (str[i]) {
        if (!isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}

static int check_pid(char *next, int *pid)
{
    if (!is_number(next)) {
        *pid = atoi(next);
        return (0);
    }
    fprintf(stderr, "Invalid process id: %s\n", next);
    return (-1);

}

static int check_flag(const orig_pair_t *pair, char *next, int *pid)
{
    if (pair->value & FLAG_P)
        return (check_pid(next, pid));
    return (0);
}

static int compare_to_flags(char *str, char *next, int *value, int *pid)
{
    if (strcmp(str, "-p") == 0 && next == NULL) {
        fprintf(stderr, "no pid provided\n");
        return (-1);
    }
    for (int i = 0; i < 4; i++) {
        if (!strcmp(array_flags[i].key, str)) {
            *value |= array_flags[i].value;
            return check_flag(&array_flags[i], next, pid);
        }
    }
    return (1);
}

int check_args(char **av, int *pid)
{
    int value = 0;
    int return_value = 0;

    for (int i = 1; av[i] && !(value & FLAG_P); i++) {
        return_value = compare_to_flags(av[i], av[i + 1], &value, pid);
        if (return_value == -1)
            return (-1);
    }
    return (value);
}
