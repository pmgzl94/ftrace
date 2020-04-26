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

static void fill_arr_list(char *elf_name, list_functions_t *arr_list)
{
    arr_list->near_call = get_functions(elf_name);
    if (arr_list->near_call)
        arr_list->is_stripped = 0;
    else
        arr_list->is_stripped = 1;
    arr_list->far_call = check_rel_rela(elf_name);
    arr_list->elf_name = elf_name;
    get_plt_addrs(elf_name, arr_list);
}

static int fork_program(char **args, char **env, char flag)
{
    pid_t pid;
    long *args_syscall = malloc(sizeof(long) * 7);
    int return_value = 0;
    list_functions_t arr_list;

    elf_version(EV_CURRENT);
    fill_arr_list(args[0], &arr_list);
    if ((pid = fork()) == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGSTOP);
        execve(args[0], args, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return_value = read_syscall(pid, flag, args_syscall, &arr_list);
    free(args_syscall);
    //have to free struct s 
    remove_whole_list(&(arr_list.near_call));
    if (arr_list.far_call)
        remove_whole_list(&(arr_list.far_call));
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
