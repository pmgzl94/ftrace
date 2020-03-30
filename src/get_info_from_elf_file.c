/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

// #include <libelf.h>
#include <gelf.h>
#include "strace.h"

int get_info_elf_file(struct info_elf *infos, char *filename)
{
    printf("%s\n", filename);
    int fd = open(filename, O_RDONLY);
    GElf_Ehdr ehdr;
    Elf *e;

    printf("fd = %d\n", fd);
    e = elf_begin(fd, ELF_C_READ, 0);
    if (elf_kind(e) != ELF_K_ELF) {
        printf("c'est pas un elf\n");
    }
    if (e == NULL) {
        printf("c'est null\n");
    }
    gelf_getehdr(e, &ehdr);
    infos->start_address = ehdr.e_entry;
    printf("value = %04x\n", infos->start_address);
    elf_end(e);
    close(fd);
    return (0);
}
