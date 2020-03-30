/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"
#include "error_handling.h"

int main(int ac, char **av, char **env)
{
    return (strace(ac, av, env));
}
