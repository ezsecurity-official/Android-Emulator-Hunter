#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <unordered_map>
#include <string.h>

#ifdef _WIN32 
#include <Windows.h>
#endif

#ifdef __linux__
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#endif


/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _UAPI_LINUX_ELF_H
#define _UAPI_LINUX_ELF_H

/* 32-bit ELF base types. */
typedef uint32_t	Elf32_Addr;
typedef uint16_t	Elf32_Half;
typedef uint32_t	Elf32_Off;
typedef int32_t	Elf32_Sword;
typedef uint32_t	Elf32_Word;

/* 64-bit ELF base types. */
typedef uint64_t	Elf64_Addr;
typedef uint16_t	Elf64_Half;
typedef int16_t	Elf64_SHalf;
typedef uint64_t	Elf64_Off;
typedef int32_t	Elf64_Sword;
typedef uint32_t	Elf64_Word;
typedef uint64_t	Elf64_Xword;
typedef int64_t	Elf64_Sxword;

/* These constants are for the segment types stored in the image headers */
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7               /* Thread local storage segment */
#define PT_LOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff
#define PT_GNU_EH_FRAME		0x6474e550
#define PT_GNU_PROPERTY		0x6474e553

#define PT_GNU_STACK	(PT_LOOS + 0x474e551)

/*
 * Extended Numbering
 *
 * If the real number of program header table entries is larger than
 * or equal to PN_XNUM(0xffff), it is set to sh_info field of the
 * section header at index 0, and PN_XNUM is set to e_phnum
 * field. Otherwise, the section header at index 0 is zero
 * initialized, if it exists.
 *
 * Specifications are available in:
 *
 * - Oracle: Linker and Libraries.
 *   Part No: 817–1984–19, August 2011.
 *   https://docs.oracle.com/cd/E18752_01/pdf/817-1984.pdf
 *
 * - System V ABI AMD64 Architecture Processor Supplement
 *   Draft Version 0.99.4,
 *   January 13, 2010.
 *   http://www.cs.washington.edu/education/courses/cse351/12wi/supp-docs/abi.pdf
 */
#define PN_XNUM 0xffff

 /* These constants define the different elf file types */
#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

/* This is the info that is needed to parse the dynamic section of the file */
#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH 	15
#define DT_SYMBOLIC	16
#define DT_REL	        17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define DT_ENCODING	32
#define OLD_DT_LOOS	0x60000000
#define DT_LOOS		0x6000000d
#define DT_HIOS		0x6ffff000
#define DT_VALRNGLO	0x6ffffd00
#define DT_VALRNGHI	0x6ffffdff
#define DT_ADDRRNGLO	0x6ffffe00
#define DT_ADDRRNGHI	0x6ffffeff
#define DT_VERSYM	0x6ffffff0
#define DT_RELACOUNT	0x6ffffff9
#define DT_RELCOUNT	0x6ffffffa
#define DT_FLAGS_1	0x6ffffffb
#define DT_VERDEF	0x6ffffffc
#define	DT_VERDEFNUM	0x6ffffffd
#define DT_VERNEED	0x6ffffffe
#define	DT_VERNEEDNUM	0x6fffffff
#define OLD_DT_HIOS     0x6fffffff
#define DT_LOPROC	0x70000000
#define DT_HIPROC	0x7fffffff

/* This info is needed when parsing the symbol table */
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

#define ELF_ST_BIND(x)		((x) >> 4)
#define ELF_ST_TYPE(x)		(((unsigned int) x) & 0xf)
#define ELF32_ST_BIND(x)	ELF_ST_BIND(x)
#define ELF32_ST_TYPE(x)	ELF_ST_TYPE(x)
#define ELF64_ST_BIND(x)	ELF_ST_BIND(x)
#define ELF64_ST_TYPE(x)	ELF_ST_TYPE(x)

typedef struct dynamic {
    Elf32_Sword d_tag;
    union {
        Elf32_Sword	d_val;
        Elf32_Addr	d_ptr;
    } d_un;
} Elf32_Dyn;

typedef struct {
    Elf64_Sxword d_tag;		/* entry tag value */
    union {
        Elf64_Xword d_val;
        Elf64_Addr d_ptr;
    } d_un;
} Elf64_Dyn;

/* The following are used with relocations */
#define ELF32_R_SYM(x) ((x) >> 8)
#define ELF32_R_TYPE(x) ((x) & 0xff)

#define ELF64_R_SYM(i)			((i) >> 32)
#define ELF64_R_TYPE(i)			((i) & 0xffffffff)

typedef struct elf32_rel {
    Elf32_Addr	r_offset;
    Elf32_Word	r_info;
} Elf32_Rel;

typedef struct elf64_rel {
    Elf64_Addr r_offset;	/* Location at which to apply the action */
    Elf64_Xword r_info;	/* index and type of relocation */
} Elf64_Rel;

typedef struct elf32_rela {
    Elf32_Addr	r_offset;
    Elf32_Word	r_info;
    Elf32_Sword	r_addend;
} Elf32_Rela;

typedef struct elf64_rela {
    Elf64_Addr r_offset;	/* Location at which to apply the action */
    Elf64_Xword r_info;	/* index and type of relocation */
    Elf64_Sxword r_addend;	/* Constant addend used to compute value */
} Elf64_Rela;

typedef struct elf32_sym {
    Elf32_Word	st_name;
    Elf32_Addr	st_value;
    Elf32_Word	st_size;
    unsigned char	st_info;
    unsigned char	st_other;
    Elf32_Half	st_shndx;
} Elf32_Sym;

typedef struct elf64_sym {
    Elf64_Word st_name;		/* Symbol name, index in string tbl */
    unsigned char	st_info;	/* Type and binding attributes */
    unsigned char	st_other;	/* No defined meaning, 0 */
    Elf64_Half st_shndx;		/* Associated section index */
    Elf64_Addr st_value;		/* Value of the symbol */
    Elf64_Xword st_size;		/* Associated symbol size */
} Elf64_Sym;


#define EI_NIDENT	16

typedef struct elf32_hdr {
    unsigned char	e_ident[EI_NIDENT];
    Elf32_Half	e_type;
    Elf32_Half	e_machine;
    Elf32_Word	e_version;
    Elf32_Addr	e_entry;  /* Entry point */
    Elf32_Off	e_phoff;
    Elf32_Off	e_shoff;
    Elf32_Word	e_flags;
    Elf32_Half	e_ehsize;
    Elf32_Half	e_phentsize;
    Elf32_Half	e_phnum;
    Elf32_Half	e_shentsize;
    Elf32_Half	e_shnum;
    Elf32_Half	e_shstrndx;
} Elf32_Ehdr;

typedef struct elf64_hdr {
    unsigned char	e_ident[EI_NIDENT];	/* ELF "magic number" */
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;		/* Entry point virtual address */
    Elf64_Off e_phoff;		/* Program header table file offset */
    Elf64_Off e_shoff;		/* Section header table file offset */
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
} Elf64_Ehdr;

/* These constants define the permissions on sections in the program
   header, p_flags. */
#define PF_R		0x4
#define PF_W		0x2
#define PF_X		0x1

typedef struct elf32_phdr {
    Elf32_Word	p_type;
    Elf32_Off	p_offset;
    Elf32_Addr	p_vaddr;
    Elf32_Addr	p_paddr;
    Elf32_Word	p_filesz;
    Elf32_Word	p_memsz;
    Elf32_Word	p_flags;
    Elf32_Word	p_align;
} Elf32_Phdr;

typedef struct elf64_phdr {
    Elf64_Word p_type;
    Elf64_Word p_flags;
    Elf64_Off p_offset;		/* Segment file offset */
    Elf64_Addr p_vaddr;		/* Segment virtual address */
    Elf64_Addr p_paddr;		/* Segment physical address */
    Elf64_Xword p_filesz;		/* Segment size in file */
    Elf64_Xword p_memsz;		/* Segment size in memory */
    Elf64_Xword p_align;		/* Segment alignment, file & memory */
} Elf64_Phdr;

/* sh_type */
#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11
#define SHT_NUM		12
#define SHT_LOPROC	0x70000000
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000
#define SHT_HIUSER	0xffffffff

/* sh_flags */
#define SHF_WRITE		0x1
#define SHF_ALLOC		0x2
#define SHF_EXECINSTR		0x4
#define SHF_RELA_LIVEPATCH	0x00100000
#define SHF_RO_AFTER_INIT	0x00200000
#define SHF_MASKPROC		0xf0000000

/* special section indexes */
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_LIVEPATCH	0xff20
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

typedef struct elf32_shdr {
    Elf32_Word	sh_name;
    Elf32_Word	sh_type;
    Elf32_Word	sh_flags;
    Elf32_Addr	sh_addr;
    Elf32_Off	sh_offset;
    Elf32_Word	sh_size;
    Elf32_Word	sh_link;
    Elf32_Word	sh_info;
    Elf32_Word	sh_addralign;
    Elf32_Word	sh_entsize;
} Elf32_Shdr;

typedef struct elf64_shdr {
    Elf64_Word sh_name;		/* Section name, index in string tbl */
    Elf64_Word sh_type;		/* Type of section */
    Elf64_Xword sh_flags;		/* Miscellaneous section attributes */
    Elf64_Addr sh_addr;		/* Section virtual addr at execution */
    Elf64_Off sh_offset;		/* Section file offset */
    Elf64_Xword sh_size;		/* Size of section in bytes */
    Elf64_Word sh_link;		/* Index of another section */
    Elf64_Word sh_info;		/* Additional section information */
    Elf64_Xword sh_addralign;	/* Section alignment */
    Elf64_Xword sh_entsize;	/* Entry size if section holds table */
} Elf64_Shdr;

#define	EI_MAG0		0		/* e_ident[] indexes */
#define	EI_MAG1		1
#define	EI_MAG2		2
#define	EI_MAG3		3
#define	EI_CLASS	4
#define	EI_DATA		5
#define	EI_VERSION	6
#define	EI_OSABI	7
#define	EI_PAD		8

#define	ELFMAG0		0x7f		/* EI_MAG */
#define	ELFMAG1		'E'
#define	ELFMAG2		'L'
#define	ELFMAG3		'F'
#define	ELFMAG		"\177ELF"
#define	SELFMAG		4

#define	ELFCLASSNONE	0		/* EI_CLASS */
#define	ELFCLASS32	1
#define	ELFCLASS64	2
#define	ELFCLASSNUM	3

#define ELFDATANONE	0		/* e_ident[EI_DATA] */
#define ELFDATA2LSB	1
#define ELFDATA2MSB	2

#define EV_NONE		0		/* e_version, EI_VERSION */
#define EV_CURRENT	1
#define EV_NUM		2

#define ELFOSABI_NONE	0
#define ELFOSABI_LINUX	3

#ifndef ELF_OSABI
#define ELF_OSABI ELFOSABI_NONE
#endif

/*
 * Notes used in ET_CORE. Architectures export some of the arch register sets
 * using the corresponding note types via the PTRACE_GETREGSET and
 * PTRACE_SETREGSET requests.
 * The note name for all these is "LINUX".
 */
#define NT_PRSTATUS	1
#define NT_PRFPREG	2
#define NT_PRPSINFO	3
#define NT_TASKSTRUCT	4
#define NT_AUXV		6
 /*
  * Note to userspace developers: size of NT_SIGINFO note may increase
  * in the future to accomodate more fields, don't assume it is fixed!
  */
#define NT_SIGINFO      0x53494749
#define NT_FILE         0x46494c45
#define NT_PRXFPREG     0x46e62b7f      /* copied from gdb5.1/include/elf/common.h */
#define NT_PPC_VMX	0x100		/* PowerPC Altivec/VMX registers */
#define NT_PPC_SPE	0x101		/* PowerPC SPE/EVR registers */
#define NT_PPC_VSX	0x102		/* PowerPC VSX registers */
#define NT_PPC_TAR	0x103		/* Target Address Register */
#define NT_PPC_PPR	0x104		/* Program Priority Register */
#define NT_PPC_DSCR	0x105		/* Data Stream Control Register */
#define NT_PPC_EBB	0x106		/* Event Based Branch Registers */
#define NT_PPC_PMU	0x107		/* Performance Monitor Registers */
#define NT_PPC_TM_CGPR	0x108		/* TM checkpointed GPR Registers */
#define NT_PPC_TM_CFPR	0x109		/* TM checkpointed FPR Registers */
#define NT_PPC_TM_CVMX	0x10a		/* TM checkpointed VMX Registers */
#define NT_PPC_TM_CVSX	0x10b		/* TM checkpointed VSX Registers */
#define NT_PPC_TM_SPR	0x10c		/* TM Special Purpose Registers */
#define NT_PPC_TM_CTAR	0x10d		/* TM checkpointed Target Address Register */
#define NT_PPC_TM_CPPR	0x10e		/* TM checkpointed Program Priority Register */
#define NT_PPC_TM_CDSCR	0x10f		/* TM checkpointed Data Stream Control Register */
#define NT_PPC_PKEY	0x110		/* Memory Protection Keys registers */
#define NT_386_TLS	0x200		/* i386 TLS slots (struct user_desc) */
#define NT_386_IOPERM	0x201		/* x86 io permission bitmap (1=deny) */
#define NT_X86_XSTATE	0x202		/* x86 extended state using xsave */
#define NT_S390_HIGH_GPRS	0x300	/* s390 upper register halves */
#define NT_S390_TIMER	0x301		/* s390 timer register */
#define NT_S390_TODCMP	0x302		/* s390 TOD clock comparator register */
#define NT_S390_TODPREG	0x303		/* s390 TOD programmable register */
#define NT_S390_CTRS	0x304		/* s390 control registers */
#define NT_S390_PREFIX	0x305		/* s390 prefix register */
#define NT_S390_LAST_BREAK	0x306	/* s390 breaking event address */
#define NT_S390_SYSTEM_CALL	0x307	/* s390 system call restart data */
#define NT_S390_TDB	0x308		/* s390 transaction diagnostic block */
#define NT_S390_VXRS_LOW	0x309	/* s390 vector registers 0-15 upper half */
#define NT_S390_VXRS_HIGH	0x30a	/* s390 vector registers 16-31 */
#define NT_S390_GS_CB	0x30b		/* s390 guarded storage registers */
#define NT_S390_GS_BC	0x30c		/* s390 guarded storage broadcast control block */
#define NT_S390_RI_CB	0x30d		/* s390 runtime instrumentation */
#define NT_ARM_VFP	0x400		/* ARM VFP/NEON registers */
#define NT_ARM_TLS	0x401		/* ARM TLS register */
#define NT_ARM_HW_BREAK	0x402		/* ARM hardware breakpoint registers */
#define NT_ARM_HW_WATCH	0x403		/* ARM hardware watchpoint registers */
#define NT_ARM_SYSTEM_CALL	0x404	/* ARM system call number */
#define NT_ARM_SVE	0x405		/* ARM Scalable Vector Extension registers */
#define NT_ARM_PAC_MASK		0x406	/* ARM pointer authentication code masks */
#define NT_ARM_PACA_KEYS	0x407	/* ARM pointer authentication address keys */
#define NT_ARM_PACG_KEYS	0x408	/* ARM pointer authentication generic key */
#define NT_ARM_TAGGED_ADDR_CTRL	0x409	/* arm64 tagged address control (prctl()) */
#define NT_ARM_PAC_ENABLED_KEYS	0x40a	/* arm64 ptr auth enabled keys (prctl()) */
#define NT_ARC_V2	0x600		/* ARCv2 accumulator/extra registers */
#define NT_VMCOREDD	0x700		/* Vmcore Device Dump Note */
#define NT_MIPS_DSP	0x800		/* MIPS DSP ASE registers */
#define NT_MIPS_FP_MODE	0x801		/* MIPS floating-point mode */
#define NT_MIPS_MSA	0x802		/* MIPS SIMD registers */

#define EM_NONE		 0		/* No machine */
#define EM_M32		 1		/* AT&T WE 32100 */
#define EM_SPARC	 2		/* SUN SPARC */
#define EM_386		 3		/* Intel 80386 */
#define EM_68K		 4		/* Motorola m68k family */
#define EM_88K		 5		/* Motorola m88k family */
#define EM_860		 7		/* Intel 80860 */
#define EM_MIPS		 8		/* MIPS R3000 big-endian */
#define EM_S370		 9		/* IBM System/370 */
#define EM_MIPS_RS3_LE	10		/* MIPS R3000 little-endian */

#define EM_PARISC	15		/* HPPA */
#define EM_VPP500	17		/* Fujitsu VPP500 */
#define EM_SPARC32PLUS	18		/* Sun's "v8plus" */
#define EM_960		19		/* Intel 80960 */
#define EM_PPC		20		/* PowerPC */
#define EM_PPC64	21		/* PowerPC 64-bit */
#define EM_S390		22		/* IBM S390 */

#define EM_V800		36		/* NEC V800 series */
#define EM_FR20		37		/* Fujitsu FR20 */
#define EM_RH32		38		/* TRW RH-32 */
#define EM_RCE		39		/* Motorola RCE */
#define EM_ARM		40		/* ARM */
#define EM_FAKE_ALPHA	41		/* Digital Alpha */
#define EM_SH		42		/* Hitachi SH */
#define EM_SPARCV9	43		/* SPARC v9 64-bit */
#define EM_TRICORE	44		/* Siemens Tricore */
#define EM_ARC		45		/* Argonaut RISC Core */
#define EM_H8_300	46		/* Hitachi H8/300 */
#define EM_H8_300H	47		/* Hitachi H8/300H */
#define EM_H8S		48		/* Hitachi H8S */
#define EM_H8_500	49		/* Hitachi H8/500 */
#define EM_IA_64	50		/* Intel Merced */
#define EM_MIPS_X	51		/* Stanford MIPS-X */
#define EM_COLDFIRE	52		/* Motorola Coldfire */
#define EM_68HC12	53		/* Motorola M68HC12 */
#define EM_MMA		54		/* Fujitsu MMA Multimedia Accelerator*/
#define EM_PCP		55		/* Siemens PCP */
#define EM_NCPU		56		/* Sony nCPU embeeded RISC */
#define EM_NDR1		57		/* Denso NDR1 microprocessor */
#define EM_STARCORE	58		/* Motorola Start*Core processor */
#define EM_ME16		59		/* Toyota ME16 processor */
#define EM_ST100	60		/* STMicroelectronic ST100 processor */
#define EM_TINYJ	61		/* Advanced Logic Corp. Tinyj emb.fam*/
#define EM_X86_64	62		/* AMD x86-64 architecture */
#define EM_PDSP		63		/* Sony DSP Processor */

#define EM_FX66		66		/* Siemens FX66 microcontroller */
#define EM_ST9PLUS	67		/* STMicroelectronics ST9+ 8/16 mc */
#define EM_ST7		68		/* STmicroelectronics ST7 8 bit mc */
#define EM_68HC16	69		/* Motorola MC68HC16 microcontroller */
#define EM_68HC11	70		/* Motorola MC68HC11 microcontroller */
#define EM_68HC08	71		/* Motorola MC68HC08 microcontroller */
#define EM_68HC05	72		/* Motorola MC68HC05 microcontroller */
#define EM_SVX		73		/* Silicon Graphics SVx */
#define EM_ST19		74		/* STMicroelectronics ST19 8 bit mc */
#define EM_VAX		75		/* Digital VAX */
#define EM_CRIS		76		/* Axis Communications 32-bit embedded processor */
#define EM_JAVELIN	77		/* Infineon Technologies 32-bit embedded processor */
#define EM_FIREPATH	78		/* Element 14 64-bit DSP Processor */
#define EM_ZSP		79		/* LSI Logic 16-bit DSP Processor */
#define EM_MMIX		80		/* Donald Knuth's educational 64-bit processor */
#define EM_HUANY	81		/* Harvard University machine-independent object files */
#define EM_PRISM	82		/* SiTera Prism */
#define EM_AVR		83		/* Atmel AVR 8-bit microcontroller */
#define EM_FR30		84		/* Fujitsu FR30 */
#define EM_D10V		85		/* Mitsubishi D10V */
#define EM_D30V		86		/* Mitsubishi D30V */
#define EM_V850		87		/* NEC v850 */
#define EM_M32R		88		/* Mitsubishi M32R */
#define EM_MN10300	89		/* Matsushita MN10300 */
#define EM_MN10200	90		/* Matsushita MN10200 */
#define EM_PJ		91		/* picoJava */
#define EM_OPENRISC	92		/* OpenRISC 32-bit embedded processor */
#define EM_ARC_A5	93		/* ARC Cores Tangent-A5 */
#define EM_XTENSA	94		/* Tensilica Xtensa Architecture */
#define EM_NUM		95

  /* Note types with note name "GNU" */
#define NT_GNU_PROPERTY_TYPE_0	5

/* Note header in a PT_NOTE section */
typedef struct elf32_note {
    Elf32_Word	n_namesz;	/* Name size */
    Elf32_Word	n_descsz;	/* Content size */
    Elf32_Word	n_type;		/* Content type */
} Elf32_Nhdr;

/* Note header in a PT_NOTE section */
typedef struct elf64_note {
    Elf64_Word n_namesz;	/* Name size */
    Elf64_Word n_descsz;	/* Content size */
    Elf64_Word n_type;	/* Content type */
} Elf64_Nhdr;

/* .note.gnu.property types for EM_AARCH64: */
#define GNU_PROPERTY_AARCH64_FEATURE_1_AND	0xc0000000

/* Bits for GNU_PROPERTY_AARCH64_FEATURE_1_BTI */
#define GNU_PROPERTY_AARCH64_FEATURE_1_BTI	(1U << 0)

#endif /* _UAPI_LINUX_ELF_H */

namespace ELFPP {
    class FileMapping {
    public:
        inline FileMapping(const char* filePath)
            : fileHandle(nullptr)
            , fileMapping(nullptr)
            , mapView(nullptr)
        {

            Initialize(filePath);

#if defined(_WIN32) == 0 && defined(__linux__) == 0
#error "Invalid Plataform"
#endif

        }

        inline ~FileMapping() {

            Deinitialize();
        }

        inline void* GetMapping() const
        {
            return mapView;
        }

        inline size_t GetSize() const
        {
            return fileSize;
        }

    private:
        size_t fileSize;
        union {
            void* fileHandle;
            int fileHandleI;
        };
        void* fileMapping;
        union {
            void* mapView;
            int mapViewI;
        };

#ifdef __linux__
        inline void Initialize(const char* filePath)
        {
            fileSize = std::filesystem::file_size(filePath);

            if ((fileSize > 0) == false)
                throw std::runtime_error("Invalid File Size");

            fileHandleI = open(filePath, O_RDONLY);

            if (fileHandleI < 0)
                throw std::runtime_error("File Open Failed");

            mapView = mmap(nullptr, fileSize, PROT_READ, MAP_SHARED, fileHandleI, 0);

            if (mapViewI == -1)
            {
                close(fileHandleI);
                throw std::runtime_error("File Mapping Failed");
            }
        }

        inline void Deinitialize()
        {
            if (mapViewI != -1 && mapView != nullptr)
            {
                munmap(mapView, fileSize);
            }

            if (fileHandleI > 0)
                close(fileHandleI);
        }
#endif


#ifdef _WIN32
        inline void Initialize(const char* filePath)
        {
            fileHandle = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (fileHandle == INVALID_HANDLE_VALUE)
                throw std::runtime_error("Error opening file");

            fileSize = GetFileSize(fileHandle, nullptr);

            fileMapping = CreateFileMappingA(fileHandle, nullptr, PAGE_READWRITE, 0, 0, nullptr);
            if (fileMapping == nullptr)
            {
                CloseHandle(fileHandle);
                throw std::runtime_error("Error creating file mapping");
            }

            mapView = MapViewOfFile(fileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

            if (mapView == nullptr) {
                CloseHandle(fileMapping);
                CloseHandle(fileHandle);
                throw std::runtime_error("Error mapping view of file");
            }
        }

        inline void Deinitialize()
        {
            if (mapView != nullptr) {
                UnmapViewOfFile(mapView);
            }

            if (fileMapping != nullptr) {
                CloseHandle(fileMapping);
            }

            if (fileHandle != nullptr && fileHandle != INVALID_HANDLE_VALUE) {
                CloseHandle(fileHandle);
            }
        }
#endif
    };

    enum class EMachine {
        UNDEFINED,
        X86,
        ARM
    };

    struct IELF {
        virtual void* SectionByIndex(unsigned int sectionIdx) = 0;
        virtual void ForEachSection(std::function<bool(void* pCurrentSection)> callback) = 0;
        virtual void* LookupSectionByType(uint32_t sectionType) = 0;
        virtual const char* GetSectionHeadersStringBlob() = 0;
        virtual const char* GetSectionName(void* _sectionHdr) = 0;
        virtual void* LookupSectionByName(const std::string& sectionName) = 0;
        virtual void* GetSymbolSection() = 0;
        virtual bool ForEachSymbol(std::function<bool(void* pCurrentSym, const char* pCurrSymName)> callback, bool bOnlyGlobals = false) = 0;
        virtual bool LookupSymbol(const std::string& symbolName, uint64_t* outSymbolOff = nullptr, bool bOnlyGlobals = false) = 0;
        virtual void ForEachProgram(std::function<bool(void* pCurrenProgram)> callback) = 0;
        virtual std::vector<void*> GetPrograms(bool bSort = false) = 0;
        virtual std::vector<void*> GetLoadablePrograms() = 0;
        virtual bool Is64() = 0;
        virtual EMachine GetTargetMachine() = 0;
        virtual uint64_t GetSymbolOffset(void* sym) = 0;
    };

    template<typename T>
    inline bool IsELF(T buff)
    {
        Elf32_Ehdr* hdr = (Elf32_Ehdr*)buff;
        uint32_t magic =
            hdr->e_ident[EI_MAG0] |
            hdr->e_ident[EI_MAG1] << 8 |
            hdr->e_ident[EI_MAG2] << 16 |
            hdr->e_ident[EI_MAG3] << 24;

        if (magic != 0x464C457F)
            return false;

        switch (hdr->e_ident[EI_CLASS])
        {
        case ELFCLASS32:
        case ELFCLASS64:
            break;

        default:
            return false;
        }

        return true;
    }

    /**
    * @brief Holds the ELF File Mapping
    */
    template<typename TELFHdr, typename TELFSHdr, typename TELFPHdr, typename TELFSym>
    struct ELF : public IELF {

        inline uint64_t GetSymbolOffset(void* _sym) override {
            TELFSym* sym = (TELFSym*)_sym;

            return sym->st_value;
        }

        inline EMachine GetTargetMachine() override
        {
            static std::unordered_map<uint16_t, EMachine> eMachines{
                {EM_386, EMachine::X86},
                {EM_X86_64, EMachine::X86},
                {EM_ARM, EMachine::ARM}
            };

            if (eMachines.find(header->e_machine) == eMachines.end())
                return EMachine::UNDEFINED;

            return eMachines[header->e_machine];
        }

        inline bool Is64() override {
            return header->e_ident[EI_CLASS] == ELFCLASS64;
        }

        inline void* SectionByIndex(unsigned int sectionIdx) override
        {
            if ((sectionIdx < header->e_shnum) == false)
                return nullptr;

            TELFSHdr* libElfSections = (TELFSHdr*)(base + header->e_shoff);

            return libElfSections + sectionIdx;
        }

        inline const char* GetSectionHeadersStringBlob() override {
            if (header->e_shstrndx == SHN_UNDEF)
                return nullptr;

            const TELFSHdr* shStrSec = (const TELFSHdr*)SectionByIndex(header->e_shstrndx);

            if (shStrSec == nullptr || shStrSec->sh_offset < 1)
                return nullptr;

            return (const char*)(base + shStrSec->sh_offset);
        }

        inline void ForEachSection(std::function<bool(void* pCurrentSection)> callback) override
        {
            TELFSHdr* libElfSections = (TELFSHdr*)(base + header->e_shoff);

            for (int i = 0; i < header->e_shnum; i++)
            {
                if (callback(libElfSections + i) == false)
                    break;
            }
        }

        inline void* LookupSectionByType(uint32_t sectionType) override
        {
            TELFSHdr* secHeader = nullptr;

            ForEachSection([&](void* _currSection) {
                TELFSHdr* currSection = (TELFSHdr*)_currSection;
                if (currSection->sh_type != sectionType)
                    return true;

                secHeader = currSection;

                return false;
                });

            return secHeader;
        }

        inline const char* GetSectionName(void* _sectionHdr)
        {
            TELFSHdr* sectionHdr = (TELFSHdr*)_sectionHdr;
            const char* shStrBlob = GetSectionHeadersStringBlob();

            if (shStrBlob == nullptr)
                return nullptr;

            return shStrBlob + sectionHdr->sh_name;
        }

        inline void* LookupSectionByName(const std::string& sectionName) override
        {
            TELFSHdr* secHeader = nullptr;

            ForEachSection([&](void* _currSection) {
                TELFSHdr* currSection = (decltype(currSection))_currSection;
                const char* currSectionName = GetSectionName(currSection);

                if (currSectionName == nullptr)
                    return true;

                if (strcmp(currSectionName, sectionName.c_str()))
                    return true;

                secHeader = currSection;

                return false;
                });

            return secHeader;
        }

        inline void* GetSymbolSection() override
        {
            TELFSHdr* result = nullptr;

            result = (TELFSHdr*)LookupSectionByType(SHT_SYMTAB);

            if (result)
                return result;

            result = (TELFSHdr*)LookupSectionByType(SHT_DYNSYM);

            if (result)
                return result;

            return result;
        }

        inline bool ForEachSymbol(std::function<bool(void* pCurrentSym, const char* pCurrSymName)> callback, bool bOnlyGlobals = false) override
        {
            TELFSHdr* symTable = (TELFSHdr*)GetSymbolSection();

            if (symTable == nullptr)
                return false;

            TELFSHdr* strTable = (TELFSHdr*)SectionByIndex(symTable->sh_link);

            if (strTable == nullptr)
                return false;

            const char* elfStrBlob = (const char*)(base + strTable->sh_offset);

            int nSyms = symTable->sh_size / sizeof(TELFSym);
            TELFSym* symEntry = (TELFSym*)(base + symTable->sh_offset);
            TELFSym* symEnd = symEntry + nSyms;

            for (TELFSym* sym = symEntry; sym < symEnd; sym++)
            {
                if (bOnlyGlobals && (ELF_ST_BIND(sym->st_info) & STB_GLOBAL) == 0)
                    continue;

                if (callback(sym, elfStrBlob + sym->st_name) == false)
                    break;
            }

            return true;
        }

        inline bool LookupSymbol(const std::string& symbolName, uint64_t* outSymbolOff = nullptr, bool bOnlyGlobals = false) override
        {
            bool bSymbolFound = false;

            if (outSymbolOff)
                *outSymbolOff = 0;

            if (ForEachSymbol([&](void* _currSym, const char* currSymName) {
                TELFSym* currSym = (TELFSym*)_currSym;

                if (strcmp(currSymName, symbolName.c_str()))
                    return true;

                bSymbolFound = true;

                if (outSymbolOff)
                    *outSymbolOff = currSym->st_value;

                return false;
                }, bOnlyGlobals) == false)
                return false;

                return bSymbolFound;
        }

        inline void ForEachProgram(std::function<bool(void* pCurrenProgram)> callback) override
        {
            TELFPHdr* libElfPrograms = (TELFPHdr*)(base + header->e_phoff);

            for (int i = 0; i < header->e_phnum; i++)
            {
                if (callback(libElfPrograms + i) == false)
                    break;
            }
        }

        inline std::vector<void*> GetPrograms(bool bSort = false) override
        {
            std::vector<void*> result;

            ForEachProgram([&](void* _phdr) {
                TELFPHdr* phdr = (TELFPHdr*)_phdr;

                result.push_back(_phdr);

                return true;
                });

            if (bSort && result.empty() == false)
            {
                std::sort(result.begin(), result.end(), [&](const void* _left, const void* _right) {
                    const TELFPHdr& left = *(const TELFPHdr*)_left;
                    const TELFPHdr& right = *(const TELFPHdr*)_right;
                    return left.p_vaddr < right.p_vaddr;
                    });
            }

            return result;
        }

        inline std::vector<void*> GetLoadablePrograms() override
        {
            std::vector<void*> allPrograms = GetPrograms();
            std::vector<void*> result;

            for (void* _program : allPrograms)
            {
                const TELFPHdr& program = *(const TELFPHdr*)_program;
                if (program.p_type != PT_LOAD)
                    continue;

                result.push_back(_program);
            }

            return result;
        }


        std::unique_ptr<FileMapping> mapping;

        union {
            /**
             * @brief Pointer to ELF Header
            */
            TELFHdr* header;

            /**
             * @brief ELF File mapping base address
            */
            uintptr_t base;

            /**
             * @brief Pointer to the ELF Mapping
            */
            void* baseV;

            /**
             * @brief Lazy int version of the Mapping Pointer, to easily do checks
            */
            int res;
        };
    };

    inline bool ARMIsThumb(IELF* pElf)
    {
        if (pElf->GetTargetMachine() != EMachine::ARM)
            return false;

        if (pElf->Is64())
            return false;

        bool bIsThunk = false;

        pElf->ForEachSymbol([pElf, &bIsThunk](void* sym, const char* symName) {
            auto symOff = pElf->GetSymbolOffset(sym);

            if (symOff == 0)
                return true;

            if ((symOff & 1) != 1)
                return true;

            bIsThunk = true;
            return false;

            });

        return bIsThunk;
    }

    using ELF32 = ELF<Elf32_Ehdr, Elf32_Shdr, Elf32_Phdr, Elf32_Sym>;
    using ELF64 = ELF<Elf64_Ehdr, Elf64_Shdr, Elf64_Phdr, Elf64_Sym>;

    template<typename ELFT>
    inline ELFT FromBuffer(const void* entry) {
        ELFT res;
        res.baseV = (void*)entry;
        return res;
    }

    inline bool ElfPeekIs64(const void* elfBuff)
    {
        ELF32 dummy = FromBuffer<ELF32>(elfBuff);
        return dummy.header->e_ident[EI_CLASS] == ELFCLASS64;
    }

    inline std::unique_ptr<IELF> FromBuffer(const void* entry) {
        if (ElfPeekIs64(entry))
            return std::move(std::make_unique<ELF64>(FromBuffer<ELF64>(entry)));
        
        return std::move(std::make_unique<ELF32>(FromBuffer<ELF32>(entry)));
    }

    /**
     * @brief Initializes the ELF Library, Notify Callback, Cleanup, Frees the ELF library
     * @returns true if all the operations was sucessfully, false otherwise
    */
    inline bool ElfOpen(const std::string& fullModulePath, std::unique_ptr<IELF>& outElfPack)
    {
        try {
            auto mapping = std::make_unique<FileMapping>(fullModulePath.c_str());
            ELF32 dummy = FromBuffer<ELF32>(mapping->GetMapping());

            if (dummy.header->e_ident[EI_CLASS] == ELFCLASS64)
            {
                ELF64 elf64 = FromBuffer<ELF64>(mapping->GetMapping());
                elf64.mapping = std::move(mapping);
                outElfPack = std::move(std::make_unique<ELF64>(std::move(elf64)));
                return true;
            }

            ELF32 elf32 = FromBuffer<ELF32>(mapping->GetMapping());
            elf32.mapping = std::move(mapping);
            outElfPack = std::move(std::make_unique<ELF32>(std::move(elf32)));
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }

        return true;
    }

    /**
     * @brief Check if ELF file is 64 bits.
     * @returns true if ELF File is 64 bits, false otherwise
    */

    inline bool ElfPeekIs64(const std::string& fullModulePath, bool& outIs64)
    {
        try {
            FileMapping f(fullModulePath.c_str());
            outIs64 = ElfPeekIs64(f.GetMapping());
            return true;
        }
        catch (std::exception& e)
        {
            std::cerr << e.what();
            return false;
        }

        return true;
    }
}