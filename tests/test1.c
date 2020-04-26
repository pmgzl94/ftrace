/*
** EPITECH PROJECT, 2019
** cpp d03
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <dlfcn.h>
#include "../include/strace.h"

void redirect_all_std(void);
char **read_tab(char *path);

Test (strace, strace_working_syscall, redirect_all_std)
{
    char *av[4] = {"./strace", "./tests/hello_world", "-s", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(0, strace(3, av, NULL));
}

Test (strace, strace_working_int, redirect_all_std)
{
    char *av[40] = {"./strace", "./tests/test", "-s", "tt", "tt", "tt",
                    "tt", "tt", "tt", "tt", "tt", "tt", "tt", "tt",
                    "tt", "tt", "tt", "tt", "tt", "tt", "tt", "tt",
                    "tt", "tt", "tt", "tt", "tt", "tt", "tt", "tt",
                    "tt", "tt", "tt", "tt", "tt", "tt", "tt", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(0, strace(36, av, env));
}

Test (strace, strace_working_striped_file, redirect_all_std)
{
    char *av[3] = {"./strace", "./tests/striped_toto", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(0, strace(3, av, NULL));
}

Test (strace, strace_working_but_tracee_failing, redirect_all_std)
{
    char *av[3] = {"./strace", "./tests/ret_error", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(2, av, env));
}

Test (strace, strace_no_pid, redirect_all_std)
{
    char *av[4] = {"./strace", "./tests/hello_world", "-p", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(3, av, env));
}

Test (strace, strace_not_a_pid, redirect_all_std)
{
    char *av[5] = {"./strace", "./tests/hello_world", "-p", "85pid", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(4, av, env));
}

Test (strace, strace_false_pid, redirect_all_std)
{
    char *av[5] = {"./strace", "./tests/hello_world", "-p", "858484", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(0, strace(4, av, env));
}

Test (strace, strace_no_file, redirect_all_std)
{
    char *av[3] = {"./strace", "-s", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(2, av, env));
}

Test (strace, strace_wrong_file_format, redirect_all_std)
{
    char *av[4] = {"./strace", "./tests/test1.c", "-s", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(3, av, env));
}

Test (strace, strace_wrong_not_a_file, redirect_all_std)
{
    char *av[4] = {"./strace", "./sdffsdssfssdfsdcsdsdfsfd", "-s", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(3, av, env));
}

Test (strace, strace_strace_no_file, redirect_all_std)
{
    char *av[4] = {"./strace", "./strace", "-s", NULL};
    char **env = read_tab("tests/env.txt");

    cr_assert_eq(84, strace(3, av, env));
}
