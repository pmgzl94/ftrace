/*
** EPITECH PROJECT, 2020
** project
** File description:
** function
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "strace.h"
#include "ftrace.h"

static int is_function(size_t sh_idx, Elf *elf)
{
    GElf_Shdr shdr;
    Elf_Scn *scn;
    
    scn = elf_getscn(elf,  sh_idx);
    if (!gelf_getshdr(scn, &shdr)) {
        return (0);
    }
    if (shdr.sh_type == SHT_PROGBITS 
        && shdr.sh_flags == (SHF_ALLOC | SHF_EXECINSTR)) {
        return (1);
    }
    return (0);
}

Elf_Scn *find_symbol_section(Elf *elf)
{
    GElf_Shdr shdr;
    Elf_Scn *scn = NULL;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_SYMTAB) {
            break;
        }
    }
    return (scn);
}

static list_t *fill_list(Elf_Scn *scn, Elf_Data *data, Elf *elf)
{
    GElf_Shdr shdr;
    GElf_Sym sym;
    list_t *list = NULL;
    int size;
    char *symbol_name;
    char message[50];

    if (gelf_getshdr(scn, &shdr) == NULL || shdr.sh_entsize == 0) {
        return (NULL);
    }
    size = shdr.sh_size / shdr.sh_entsize;
    for (int i = 0; i < size; i++) {
        gelf_getsym(data, i, &sym);
        symbol_name = elf_strptr(elf, shdr.sh_link, sym.st_name);
        if (strlen(symbol_name) && is_function(sym.st_shndx, elf)) {
            handle_add_element(&list);
            list->data = create_symbol_s(symbol_name, sym.st_value);
        }
    }
    return (list);
}

list_t *get_functions(char *elf_name)
{
    int fd = open(elf_name, O_RDONLY);
    Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
    Elf_Scn *scn = find_symbol_section(elf);
    Elf_Data *data = elf_getdata(scn, NULL);
    list_t *list = fill_list(scn, data, elf);

    elf_end(elf);
    close(fd);
    return (list);
}
