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

static void get_plt_addrs(char *elf_name, list_functions_t *arr_list)
{
    int fd = open(elf_name, O_RDONLY);
    Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
    GElf_Shdr shdr;
    GElf_Ehdr ehdr;
    Elf_Scn *scn = NULL;
    size_t shstrndx = 0;
    int index = 0;

    elf_getshdrstrndx(elf, &shstrndx);
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (strcmp(elf_strptr(elf, shstrndx, shdr.sh_name), ".plt") == 0) {
            arr_list->start_plt = shdr.sh_addr;
            index = 1;
        } else if (index == 1) {
            arr_list->end_plt = shdr.sh_addr;
            index = 0;
        }
    }
    elf_end(elf);
    close(fd);
}

static void fill_arr_list(char *elf_name, list_functions_t *arr_list)
{
    elf_version(EV_CURRENT);
    arr_list->near_call = get_functions(elf_name);
    if (arr_list->near_call)
        arr_list->is_stripped = 0;
    else
        arr_list->is_stripped = 1;
    arr_list->far_call = check_rel_rela(elf_name);
    arr_list->stack_fcts = NULL;
    arr_list->elf_name = elf_name;
    get_plt_addrs(elf_name, arr_list);
}

static int fork_program(char **args, char **env, char flag)
{
    pid_t pid;
    long *args_syscall = malloc(sizeof(long) * 7);
    int return_value = 0;
    list_functions_t arr_list;

    fill_arr_list(args[0], &arr_list);
    if ((pid = fork()) == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        kill(getpid(), SIGSTOP);
        execve(args[0], args, env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
    return_value = browse_instructions(pid, flag, args_syscall, &arr_list);
    free(args_syscall);
    free_lists(&arr_list);
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
