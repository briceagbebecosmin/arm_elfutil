#include <stdint.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/mman.h>
#include "Elf.h"
#include "ElfHeader.h"

void elf_printElfHeader()
{
    int elf_fd;
    uint8_t *mem_map;
    ELFHeader *elfHeader;
    struct stat elf_info;

    elf_fd = open(optarg,O_RDONLY);

    if(elf_fd < 0)
    {
        fprintf(stderr,"Cannot open file [%s]\n",optarg);
        exit(-1);
    }

    fstat(elf_fd,&elf_info);

    mem_map = mmap(NULL,elf_info.st_size,PROT_READ,MAP_PRIVATE,elf_fd,0);

    elfHeader = (ELFHeader*)mem_map;

    if((elfHeader->magic_value[EI_MAG0_OFFSET] != EI_ELF_MAGIC)      ||
            elfHeader->magic_value[EI_MAG1_OFFSET] != EI_MAGIC1_DATA ||
            elfHeader->magic_value[EI_MAG2_OFFSET] != EI_MAGIC2_DATA ||
            elfHeader->magic_value[EI_MAG3_OFFSET] != EI_MAGIC3_DATA ||
            elfHeader->elf_machine != EM_ARM)
    {
        fprintf(stderr,"File [%s] cannot be classified \n",optarg);
        exit(-1);
    }

    printf("*----------------------------------------------------------------------------*\n");
    printf("%-30s","ELF:");
    printf("%s\n",optarg);


    printf("%-30s","Magic Number:");
    for(int index = 0; index < ELF_MAGIC_SIZE; index++)
    {
        printf("%02X ",elfHeader->magic_value[index]);
    }
    printf("\n");

    printf("%-30s","Machine:");
    switch(elfHeader->elf_machine)
    {
    case EM_ARM :
    {
        printf("ARM\n");
        break;
    }

    default : break;
    }

    printf("%-30s","Data:");
    switch(elfHeader->magic_value[EI_DATA_OFFSET])
    {
    case EI_DATA_LSB :
    {
        printf("Two's complement, Little Endian\n");
        break;
    }

    case EI_DATA_MSB :
    {
        printf("Two's complement, Big Endian\n");
        break;
    }

    default : {printf("Unknown data format\n"); }break;
    }

    printf("%-30s","Version:");
    switch(elfHeader->magic_value[EI_VERSION_OFFSET])
    {
    case EV_CURRENT :
    {
        printf("Current Version 0x%02X\n",EV_CURRENT);
        break;
    }

    default: {printf("Unknown version\n");} break;
    }

    printf("%-30s","Class:");
    switch(elfHeader->magic_value[EI_CLASS_OFFSET])
    {
    case EI_CLASS_32BIT :
    {
        printf("ELF32\n");
        break;
    }
    case EI_CLASS_64BIT :
    {
        printf("ELF64\n");
        break;
    }

    default : {printf("Unknown\n");}break;
    }

    if(elfHeader->magic_value[EI_DATA_OFFSET] == EI_DATA_LSB)
    {
        printf("%-30s","Program entry point:");
        printf("0x%02X%02X%02X%02X\n",
               (uint8_t)(elfHeader->elf_address >> (uint32_t)24),
               (uint8_t)(elfHeader->elf_address >> (uint32_t)16),
               (uint8_t)(elfHeader->elf_address >> (uint32_t)8),
               (uint8_t)(elfHeader->elf_address));

        printf("%-30s","Program header offset:");
        printf("0x%02X%02X%02X%02X\n",
               (uint8_t)(elfHeader->elf_phOffset >> (uint32_t)24),
               (uint8_t)(elfHeader->elf_phOffset >> (uint32_t)16),
               (uint8_t)(elfHeader->elf_phOffset >> (uint32_t)8),
               (uint8_t)(elfHeader->elf_phOffset));

        printf("%-30s","Section header offset:");
        printf("0x%02X%02X%02X%02X\n",
               (uint8_t)(elfHeader->elf_shOffset >> (uint32_t)24),
               (uint8_t)(elfHeader->elf_shOffset >> (uint32_t)16),
               (uint8_t)(elfHeader->elf_shOffset >> (uint32_t)8),
               (uint8_t)(elfHeader->elf_shOffset));

        printf("%-30s","ELF header size:");
        printf("%d %s\n",
               ((uint32_t)(elfHeader->elf_ehsize >> (uint32_t)24) |
                       (elfHeader->elf_ehsize >> (uint32_t)16) |
                       (elfHeader->elf_ehsize >> (uint32_t)8) |
                       (elfHeader->elf_ehsize))," bytes");

        printf("%-30s","Section header size:");
        printf("%d %s\n",
               ((uint32_t)(elfHeader->elf_shentsize >> (uint32_t)24) |
                       (elfHeader->elf_shentsize >> (uint32_t)16) |
                       (elfHeader->elf_shentsize >> (uint32_t)8) |
                       (elfHeader->elf_shentsize))," bytes");

        printf("%-30s","Program header size:");
        printf("%d %s\n",
               ((uint32_t)(elfHeader->elf_phentsize >> (uint32_t)24) |
                       (elfHeader->elf_phentsize >> (uint32_t)16) |
                       (elfHeader->elf_phentsize >> (uint32_t)8) |
                       (elfHeader->elf_phentsize))," bytes");

    }else if(elfHeader->magic_value[EI_DATA_OFFSET] == EI_DATA_MSB)
    {
        printf("%-30s","Program entry point:");
        printf("%0x02X%02X%02X%02X\n",
               (uint8_t)(elfHeader->elf_address << (uint32_t)24),
               (uint8_t)(elfHeader->elf_address << (uint32_t)16),
               (uint8_t)(elfHeader->elf_address << (uint32_t)8),
               (uint8_t)(elfHeader->elf_address));
        printf("%-30s","Program header offset:");
        printf("0x%02X%02X%02X%02X\n",
               (uint8_t)(elfHeader->elf_phOffset << (uint32_t)24),
               (uint8_t)(elfHeader->elf_phOffset << (uint32_t)16),
               (uint8_t)(elfHeader->elf_phOffset << (uint32_t)8),
               (uint8_t)(elfHeader->elf_phOffset));
        printf("%-30s","Section header offset:");
        printf("0x%02X%02X%02X%02X\n",
               (uint8_t)(elfHeader->elf_shOffset << (uint32_t)24),
               (uint8_t)(elfHeader->elf_shOffset << (uint32_t)16),
               (uint8_t)(elfHeader->elf_shOffset << (uint32_t)8),
               (uint8_t)(elfHeader->elf_shOffset));

        printf("%-30s","ELF header size:");
        printf("%d %s\n",
               ((uint32_t)(elfHeader->elf_ehsize << (uint32_t)24) |
                       (elfHeader->elf_ehsize << (uint32_t)16) |
                       (elfHeader->elf_ehsize << (uint32_t)8) |
                       (elfHeader->elf_ehsize))," bytes");

        printf("%-30s","Section header size:");
        printf("%d %s\n",
               ((uint32_t)(elfHeader->elf_shentsize << (uint32_t)24) |
                       (elfHeader->elf_shentsize << (uint32_t)16) |
                       (elfHeader->elf_shentsize << (uint32_t)8) |
                       (elfHeader->elf_shentsize))," bytes");

        printf("%-30s","Program header size:");
        printf("%d %s\n",
               ((uint32_t)(elfHeader->elf_phentsize << (uint32_t)24) |
                       (elfHeader->elf_phentsize << (uint32_t)16) |
                       (elfHeader->elf_phentsize << (uint32_t)8) |
                       (elfHeader->elf_phentsize))," bytes");


    }else
    {
        fprintf(stderr,"Cannot identify the endianess \n");
        exit(-1);
    }

    printf("%-30s","ELF Type:");
    switch(elfHeader->elf_type)
    {
    case ET_REL :
    {
        printf("Relocatable\n");
        break;
    }

    case ET_EXEC :
    {
        printf("Executable\n");
        break;
    }

    case ET_DYN :
    {
        printf("Dynamic\n");
        break;
    }

    case ET_CORE :
    {
        printf("Core\n");
        break;
    }
    default : {printf("Unknown\n");}break;
    }

    printf("%-30s","Number of program headers:");
    printf("%d\n",elfHeader->elf_phnum);
    printf("%-30s","Number of section header:");
    printf("%d\n",elfHeader->elf_shnum);
    printf("%-30s","Section header string table:");
    printf("%d\n",elfHeader->elf_shstrndx);

    printf("*----------------------------------------------------------------------------*\n");

    close(elf_fd);
}

void elf_printProgramHeader()
{
    int elf_fd;
    uint8_t *mem_map;
    ELFHeader *elfHeader;
    ELFProgramHeader *elfProgramHeader;
    struct stat elf_info;

    elf_fd = open(optarg,O_RDONLY);

    if(elf_fd < 0)
    {
        fprintf(stderr,"Cannot open file [%s]\n",optarg);
        exit(-1);
    }

    fstat(elf_fd,&elf_info);

    mem_map = mmap(NULL,elf_info.st_size,PROT_READ,MAP_PRIVATE,elf_fd,0);
    elfHeader = (ELFHeader*)mem_map;

    elfProgramHeader = (ELFProgramHeader*)&mem_map[elfHeader->elf_phOffset];

    if(elfHeader->elf_phnum == 0)
    {
        fprintf(stderr,"There is no program header to be displayed\n");
        exit(-1);
    }else
    {
        printf("*----------------------------------------------------------------------------*\n");
        printf("%-10s %-10s %-10s %-10s %-10s\n","Type ","VAddress","RAddress","File Size (bytes)","Memory Size (bytes)");
        printf("*----------------------------------------------------------------------------*\n");
        for(int pIndex = 0; pIndex < elfHeader->elf_phnum;pIndex++)
        {
            switch(elfProgramHeader->p_type)
            {

            case PT_LOAD :
            {

                printf("%-10s","PT_LOAD");
                break;
            }

            case PT_DYNAMIC :
            {
                printf("%-10s","PT_DYNAMIC");
                break;
            }

            case PT_INTERP:
            {
                printf("%-10s","PT_INTERP");
                break;
            }

            case PT_NOTE:
            {
                printf("%-10s","PT_NOTE");
                break;
            }

            case PT_SHLIB :
            {
                printf("%-10s","PT_SHLIB");
                break;
            }

            case PT_PHDR :
            {
                printf("%-10s","PT_PHDR");
                break;
            }

            default : {printf("Unknown type\n");}break;
            }

            if(elfHeader->magic_value[EI_DATA_OFFSET] == EI_DATA_LSB)
            {
                printf("%s 0x%08X","",
                       ((elfProgramHeader->p_vaddr >> 24)   |
                               (elfProgramHeader->p_vaddr >> 16)    |
                               (elfProgramHeader->p_vaddr >> 8)     |
                               (elfProgramHeader->p_vaddr)));
                printf("%s 0x%08X","",
                       ((elfProgramHeader->p_paddr >> 24)   |
                               (elfProgramHeader->p_paddr >> 16)    |
                               (elfProgramHeader->p_paddr >> 8)     |
                               (elfProgramHeader->p_paddr)));

                printf("%s %d","",
                       ((elfProgramHeader->p_filesz >> 24)   |
                               (elfProgramHeader->p_filesz >> 16)    |
                               (elfProgramHeader->p_filesz >> 8)     |
                               (elfProgramHeader->p_filesz)));

                printf("%-12s %d"," ",
                       ((elfProgramHeader->p_memsz >> 24)   |
                               (elfProgramHeader->p_memsz >> 16)    |
                               (elfProgramHeader->p_memsz >> 8)     |
                               (elfProgramHeader->p_memsz)));

            }else if (elfHeader->magic_value[EI_DATA_OFFSET] == EI_DATA_MSB)
            {
                printf("%s","0x%08X"," ",
                       ((elfProgramHeader->p_vaddr << 24)   |
                               (elfProgramHeader->p_vaddr << 16)    |
                               (elfProgramHeader->p_vaddr << 8)     |
                               (elfProgramHeader->p_vaddr)));

                printf("%s","0x%08X"," ",
                       ((elfProgramHeader->p_paddr << 24)   |
                               (elfProgramHeader->p_paddr << 16)    |
                               (elfProgramHeader->p_paddr << 8)     |
                               (elfProgramHeader->p_paddr)));

                printf("%s %d","",
                       ((elfProgramHeader->p_filesz << 24)   |
                               (elfProgramHeader->p_filesz << 16)    |
                               (elfProgramHeader->p_filesz << 8)     |
                               (elfProgramHeader->p_filesz)));

                printf("%-12s %d"," ",
                       ((elfProgramHeader->p_memsz << 24)   |
                               (elfProgramHeader->p_memsz << 16)    |
                               (elfProgramHeader->p_memsz << 8)     |
                               (elfProgramHeader->p_memsz)));
            }
            printf("\n");

            elfProgramHeader++;
        }

        printf("*----------------------------------------------------------------------------*\n");
    }

    close(elf_fd);

}
