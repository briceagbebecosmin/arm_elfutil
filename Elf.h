/**
 * @Author : Bebe-Cosmin Briceag 2017.  briceagcosmin@icloud.com
 */

#ifndef _ELF_H_
#define _ELF_H_


#define ELF_ST_BIND(st_info)  ((st_info)>>4)
#define ELF_ST_TYPE(st_info)  ((st_info) & (0x0F))



/* =========================== E L F - T Y P E =====================*/
#define ET_NONE ((uint8_t)0)
#define ET_REL  ((uint8_t)1)
#define ET_EXEC ((uint8_t)2)
#define ET_DYN  ((uint8_t)3)
#define ET_CORE ((uint8_t)4)
/*=================================================================*/

/*=========================== E L F - M A C H I N E ===============*/
#define EM_ARM  ((uint16_t)40)


/*=================================================================*/


/*=========================== E L F - V E R S I O N ===============*/
#define EV_NONE    ((uint8_t)0)
#define EV_CURRENT ((uint8_t)1)
/*=================================================================*/


/*=========================== E L F - I D E N T ===================*/

#define ELF_MAGIC_SIZE    ((uint8_t)16)

#define EI_MAG0_OFFSET    ((uint8_t)0)
#define EI_MAG1_OFFSET    ((uint8_t)1)
#define EI_MAG2_OFFSET    ((uint8_t)2)
#define EI_MAG3_OFFSET    ((uint8_t)3)
#define EI_CLASS_OFFSET   ((uint8_t)4)
#define EI_DATA_OFFSET    ((uint8_t)5)
#define EI_VERSION_OFFSET ((uint8_t)6)
#define EI_PAD_OFFSET     ((uint8_t)7)

#define EI_ELF_MAGIC      ((uint8_t)0x7F)
#define EI_MAGIC1_DATA    'E'
#define EI_MAGIC2_DATA    'L'
#define EI_MAGIC3_DATA    'F'


#define EI_CLASS_NONE    ((uint8_t)0)
#define EI_CLASS_32BIT   ((uint8_t)1)
#define EI_CLASS_64BIT   ((uint8_t)2)


#define EI_DATA_NONE     ((uint8_t)0)
#define EI_DATA_LSB      ((uint8_t)1)
#define EI_DATA_MSB      ((uint8_t)2)

/*=================================================================*/


/*======================= S E C T I O N - T Y P E =================*/
#define SHT_NULL         ((uint8_t)0)
#define SHT_PROGBITS     ((uint8_t)1)
#define SHT_SYMTAB       ((uint8_t)2)
#define SHT_STRTAB       ((uint8_t)3)
#define SHT_RELA         ((uint8_t)4)
#define SHT_HASH         ((uint8_t)5)
#define SHT_DYNAMIC      ((uint8_t)6)
#define SHT_NOTE         ((uint8_t)7)
#define SHT_NOBITS       ((uint8_t)8)
#define SHT_REL          ((uint8_t)9)
#define SHT_SHLIB        ((uint8_t)10)
#define SHT_DYNSYM       ((uint8_t)11)
/*=================================================================*/

/*====================== S E C T I O N - A T T R I B U T E ========*/
#define SHF_WRITE        ((uint8_t)0x01)
#define SHF_ALLOC        ((uint8_t)0x02)
#define SHF_EXECINSTR    ((uint8_t)0x04)
/*=================================================================*/


/*====================== P R O G R A M - H E A D E R - T Y P E ===*/
#define PT_NULL        ((uint8_t)0)
#define PT_LOAD        ((uint8_t)1)
#define PT_DYNAMIC     ((uint8_t)2)
#define PT_INTERP      ((uint8_t)3)
#define PT_NOTE        ((uint8_t)4)
#define PT_SHLIB       ((uint8_t)5)
#define PT_PHDR        ((uint8_t)6)


/*================================================================*/

typedef uint32_t ElfAddr;
typedef uint32_t ElfOffset;
typedef uint32_t Elf32_t;

typedef struct _elf_header
{
    uint8_t    magic_value[ELF_MAGIC_SIZE];
    uint16_t   elf_type;
    uint16_t   elf_machine;
    uint32_t   elf_version;
    ElfAddr    elf_address;
    ElfOffset  elf_phOffset;
    ElfOffset  elf_shOffset;
    uint32_t   elf_flags;
    uint16_t   elf_ehsize;
    uint16_t   elf_phentsize;
    uint16_t   elf_phnum;
    uint16_t   elf_shentsize;
    uint16_t   elf_shnum;
    uint16_t   elf_shstrndx;

}ELFHeader;

typedef struct _program_header
{
    Elf32_t p_type;
    Elf32_t p_offset;
    Elf32_t p_vaddr;
    Elf32_t p_paddr;
    Elf32_t p_filesz;
    Elf32_t p_memsz;
    Elf32_t p_flags;
    Elf32_t p_align;
}ELFProgramHeader;


typedef struct _section_header
{
    Elf32_t sh_name;
    Elf32_t sh_type;
    Elf32_t sh_flags;
    Elf32_t sh_addr;
    Elf32_t sh_offset;
    Elf32_t sh_size;
    Elf32_t sh_link;
    Elf32_t sh_info;
    Elf32_t sh_addr_align;
    Elf32_t sh_ent_size;
}ELFSectionHeader;

typedef struct _symbol_table
{
    Elf32_t st_name;
    Elf32_t st_value;
    Elf32_t st_size;
    uint8_t st_info;
    uint8_t st_other;
    Elf32_t st_shndx;
}ELFSymTable;



#endif
