/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#ifndef ERROR_HANDLING_H_
#define ERROR_HANDLING_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct orig_pair {
    char *key;
    int value;
} orig_pair_t;

#define FLAG_S 1
#define FLAG_P 2

static const struct orig_pair array_flags[4] = {{"-p", FLAG_P},
        {"-s", FLAG_S }, {"-sp", FLAG_S | FLAG_P},
        {"-ps", FLAG_S | FLAG_P}};

int check_args(char **av, int *pid);


#endif
