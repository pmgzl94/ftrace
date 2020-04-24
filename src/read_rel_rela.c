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
#include <gelf.h>

static Elf_Scn *find_rel_and_rela(Elf *elf, Elf_Scn *scn, int *rela)
{
    GElf_Shdr shdr;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_REL) {
            *rela = 0;
            break;
        } else if (shdr.sh_type == SHT_RELA) {
            *rela = 1;
            break;
        }
    }
    return (scn);
}

static Elf_Scn *find_symbol_section2(Elf *elf)
{
    GElf_Shdr shdr;
    Elf_Scn *scn = NULL;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_DYNSYM)
            break;
    }
    return (scn);
}

static int get_rela(Elf_Scn *scn, GElf_Shdr shdr, Elf *elf, list_t **list)
{
    Elf_Data *data;
    GElf_Rela rela;
    Elf_Scn *scn2;
    GElf_Shdr shdr2;
    Elf_Data *data2;
    GElf_Sym sym;
    data = elf_getdata(scn, NULL);
    int size = shdr.sh_size / shdr.sh_entsize;

    for (int i = 0; i < size; i++) {
        gelf_getrela(data, i, &rela);
//        printf("address = %X\n", rela.r_offset);
        scn2 = find_symbol_section2(elf);
        gelf_getshdr(scn2, &shdr2);
        data2 = elf_getdata(scn2, NULL);
        gelf_getsym(data2, GELF_R_SYM(rela.r_info), &sym);
        if (GELF_R_TYPE(rela.r_info) == R_386_JMP_SLOT) {
//            printf("name = %s\n", elf_strptr(elf, shdr2.sh_link, sym.st_name));
            handle_add_element(list);
//            (*list)->data = create_symbol_s(symbol_name, sym.st_value);
            (*list)->data = create_symbol_s(elf_strptr(elf, shdr2.sh_link, sym.st_name), rela.r_offset);
        }
//        printf("type = %d\n", GELF_R_TYPE(rela.r_info));
//        printf("R_386_JMP_SLOT = %d\n", R_386_JMP_SLOT);
//        printf("elf_strptr(elf, shdr2.sh_link, sym.st_name) = %s\n\n", elf_strptr(elf, shdr2.sh_link, sym.st_name));
    }
    return (0);
}

static int get_rel(Elf_Scn *scn, GElf_Shdr shdr, Elf *elf, list_t **list)
{
    Elf_Data *data;
    GElf_Rel rel;
    Elf_Scn *scn2;
    GElf_Shdr shdr2;
    Elf_Data *data2;
    GElf_Sym sym;
    data = elf_getdata(scn, NULL);
    int size = shdr.sh_size / shdr.sh_entsize;

    for (int i = 0; i < size; i++) {
        gelf_getrel(data, i, &rel);
//        printf("address = %X\n", rel.r_offset);
        scn2 = find_symbol_section2(elf);
        gelf_getshdr(scn2, &shdr2);
        data2 = elf_getdata(scn2, NULL);
        gelf_getsym(data2, GELF_R_SYM(rel.r_info), &sym);
        if (GELF_R_TYPE(rel.r_info) == R_386_JMP_SLOT) {
//            printf("name = %s\n", elf_strptr(elf, shdr2.sh_link, sym.st_name));
            handle_add_element(list);
            (*list)->data = create_symbol_s(elf_strptr(elf, shdr2.sh_link, sym.st_name), rel.r_offset);
        }
//        printf("type = %d\n", GELF_R_TYPE(rel.r_info));
//        printf("R_386_JMP_SLOT = %d\n", R_386_JMP_SLOT);
//        printf("elf_strptr(elf, shdr2.sh_link, sym.st_name) = %s\n\n", elf_strptr(elf, shdr2.sh_link, sym.st_name));
    }
    return (0);
}

list_t *check_rel_rela(char *elf_name)
{
    int fd = open(elf_name, O_RDONLY);
    Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
    int rela = -1;
    GElf_Shdr shdr;
    Elf_Scn *scn = find_rel_and_rela(elf, NULL, &rela);
    list_t *list = NULL;

    while (scn) {
        gelf_getshdr(scn, &shdr);
        if (rela == 1)
            get_rela(scn, shdr, elf, &list);
        else if (rela == 0)
            get_rel(scn, shdr, elf, &list);
        rela = -1;
        scn = find_rel_and_rela(elf, scn, &rela);
    }
    elf_end(elf);
    close(fd);
    return (list);
}
