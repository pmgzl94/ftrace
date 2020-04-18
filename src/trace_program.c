/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include "strace.h"
#include "ftrace.h"

static int check_executable(char **args)
{
    if (args[0] == NULL) {
        fprintf(stderr, "no file provided\n");
        return (1);
    }
    else if (access(args[0], F_OK) == -1) {
        fprintf(stderr, "this file doesn't exist: %s\n", args[0]);
        return (1);
    }
    if (access(args[0], X_OK) == -1) {
        fprintf(stderr, "this file isn't an executable: %s\n", args[0]);
        return (1);
    }
    return (0);
}

static int fork_program(char **args, char **env, char flag)
{
    pid_t pid;
    long *args_syscall = malloc(sizeof(long) * 7);
    int return_value = 0;
    list_t *list;

    elf_version(EV_CURRENT);
    list = get_functions(args[0]);
    if ((pid = fork()) == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGSTOP);
        execve(args[0], args, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return_value = read_syscall(pid, flag, args_syscall, list);
    free(args_syscall);
    //have to free struct s 
    remove_whole_list(&list);
    return (return_value);
}

int trace_program(int ac, char **av, char **env, char flag)
{
    struct info_elf infos;
    char **args = get_args(ac, av);
    int return_value = 0;

    if (check_executable(args) == 1)
        return (84);
    return_value = fork_program(args, env, flag);
    free(args);
    return (return_value);
}
