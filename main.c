#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include <sys/mman.h>

#include "Elf.h"
#include "ElfHeader.h"

/**
 * @Author : Bebe-Cosmin Briceag 2017.  briceagcosmin@icloud.com
 */

#define ELF_INJECT_OPT         'i'
#define ELF_HEADER_OPT         'h'
#define ELF_PROGRAM_HEADER_OPT 'p'

static void printUsage(const char *programName);


static char *program_name;

static const struct option elf_options[] =
{
 { .name = "inject code",        .val = 'i', .has_arg = required_argument, .flag = 0 },
 { .name = "show ELF header",    .val = 'h', .has_arg = required_argument, .flag = 0 },
 { .name = "view program header",.val = 'p' ,.has_arg = required_argument, .flag = 0 },
 { .name = 0,                    .val = 0,   .has_arg = 0,                 .flag = 0 }
};

static const char *options = {"i:h:s:S:p:"};

int main(int argc, char *const argv[])
{

    int option_index;

    char option;

    if(argc < 1)
    {
        printUsage(argv[0]);
        exit(0);
    }

    program_name = (char*)malloc(sizeof(char) * strlen(argv[0]));
    strcpy(program_name,argv[0]);

    option = getopt_long(argc,argv,options,elf_options,&option_index);

    switch(option)
    {
    case ELF_INJECT_OPT :
    {
        break;
    }

    case ELF_HEADER_OPT :
    {
        elf_printElfHeader();

        break;
    }

    case ELF_PROGRAM_HEADER_OPT :
    {
        elf_printProgramHeader();
        break;
    }

    default : printUsage(argv[0]);break;

    }

    exit(EXIT_SUCCESS);
}


static void printUsage(const char *programName)
{
    printf("Usage %s %s\n",programName,
           "\n"
           "[-i] Inject Code\n"
           "[-h] View ELF header\n"
           "[-s] View ELF sections\n"
           "[-S] View ELF symbols\n"
           "[-p] View Program header\n");
}


