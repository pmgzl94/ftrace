/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#ifndef REF_SYSCALL_H_
#define REF_SYSCALL_H_

enum typeArg {
    INT = 1,
    STRING = 2,
    STRUCT = 4,
    FLAG = 8,
    ADDR = 16,
    ARRAY = 32,
    UNDEFINED = 64
};

typedef struct ref_syscall {
    const char *name;
    int args[6];
    int nb_args;
} ref_syscall_t;

#endif
