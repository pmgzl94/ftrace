/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"
#include "error_handling.h"

int strace(int ac, char **av, char **env)
{
    int pid = -1;
    int flag = 0;

    if (ac == 2 && (strcmp("--help", av[1]) == 0 ||
                    strcmp("-h", av[1]) == 0)) {
        printf("USAGE: ftrace executable file [-s]\n\n");
        printf("Output format:\n");
        printf(" -s    display the detailled arguments (see below)\n");
        printf("          -integers in decimal form\n");
        printf("          -pointers on a character string in the form of a");
        printf(" character string\n");
        return (0);
    }
    if ((flag = check_args(av, &pid)) == -1)
        return (84);
    return trace_program(ac, av, env, flag);
}
