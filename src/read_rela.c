
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "strace.h"
#include <gelf.h>
#include "ftrace.h"

Elf_Scn *find_rela(Elf *elf, Elf_Scn *scn)
{
    GElf_Shdr shdr;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_RELA) {
            break;
        }
    }
    return (scn);
}

Elf_Scn *find_symbol_section2(Elf *elf)
{
    GElf_Shdr shdr;
    Elf_Scn     *scn = NULL;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_type == SHT_DYNSYM) {
            break;
        }
    }
    return (scn);
}

int get_rela(char *elf_name)
{
    int fd = open(elf_name, O_RDONLY);
    Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
    
    GElf_Rela rela;
    GElf_Shdr shdr;
    Elf_Data *data;
    Elf_Scn *scn = find_rela(elf, NULL);
    scn = find_rela(elf, scn);

    data = elf_getdata(scn, NULL);
    gelf_getshdr(scn, &shdr);

    int size = shdr.sh_size / shdr.sh_entsize;
    printf("size = %d\n", size);
    for (int i = 0; i < size; i++) {
        gelf_getrela(data, i, &rela);
        printf("%X\n", rela.r_offset);
        printf("index = %d\n", GELF_R_SYM(rela.r_info));
        Elf_Scn *scn2 = find_symbol_section2(elf);
        GElf_Shdr shdr2;
        gelf_getshdr(scn2, &shdr2);
        Elf_Data *data2 = elf_getdata(scn2, NULL);
        GElf_Sym sym;
        gelf_getsym(data2, GELF_R_SYM(rela.r_info), &sym);
        printf("type = %d\n", GELF_R_TYPE(rela.r_info));
        printf("%d\n", R_386_JMP_SLOT);
        printf("%X\n", sym.st_value);
        printf("%s\n", elf_strptr(elf, shdr2.sh_link, sym.st_name));
    }
    elf_end(elf);
    close(fd);
    return (0);
}