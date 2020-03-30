/*
** EPITECH PROJECT, 2019
** dante
** File description:
** get_map
*/

#include "../include/strace.h"
#include <string.h>

static char *my_strdup_n(char const *src)
{
    int len = strlen(src);
    char *str = malloc(sizeof(char) * (len + 1));
    int i = 0;

    if (src == NULL || str == NULL)
        return (NULL);
    for (; i < len && src[i] != '\n'; i++)
        str[i] = src[i];
    str[i] = 0;
    return (str);
}

static int count_length_tab(char *path)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    int len = 0;

    if (file == NULL)
        return (-1);
    while (getline(&line, &(size_t){0}, file) != -1) {
        free(line);
        len++;
    }
    fclose(file);
    free(line);
    return (len);
}

char **read_tab(char *path)
{
    int size = count_length_tab(path);
    FILE *file = fopen(path, "r");
    char *line = NULL;
    char **tab;
    int i = 0;

    if (size == -1 || file == NULL)
        return (NULL);
    tab = malloc(sizeof(char *) * (size + 1));
    if (tab == NULL)
        return (NULL);
    for (; getline(&line, &(size_t){0}, file) != -1; i++) {
        tab[i] = my_strdup_n(line);
        if (tab[i] == NULL)
            return (NULL);
        free(line);
    }
    tab[i] = NULL;
    fclose(file);
    free(line);
    return (tab);
}
