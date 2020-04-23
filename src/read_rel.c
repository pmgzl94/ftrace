
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "strace.h"
#include "ftrace.h"

Elf_Scn *find_rel(Elf *elf)
{
    GElf_Shdr shdr;
    Elf_Scn *scn = NULL;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (/*shdr.sh_type == SHT_RELA || */shdr.sh_type == SHT_REL) {
            break;
        }
    }
    return (scn);
}

int get_rel(char *elf_name)
{
    int fd = open(elf_name, O_RDONLY);
    Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
    
    GElf_Rel rel;
    GElf_Shdr shdr;
    Elf_Data *data;
    Elf_Scn *scn = find_rel(elf);

    data = elf_getdata(scn, NULL);
    gelf_getshdr(scn, &shdr);

    int size = shdr.sh_size / shdr.sh_entsize;
    printf("size2 = %d\n", size);
    for (int i = 0; i < size; i++) {
        gelf_getrel(data, i, &rel);
        printf("%X\n", rel.r_offset);
    }

    elf_end(elf);
    close(fd);
    return (0);
}