/*  llvm2pic32 | Executable and Linkable Format (.elf) to .hex. */

/* clang++ -o llvm2pic32₂ -DSHA1GIT=`git log -1 '--pretty=format:%h'` \
     -std=c++2a main.cpp */

#ifdef __x86_64__
typedef unsigned int        uint32_t;
#elif defined __mips__
typedef unsigned long       uint32_t;
#endif
typedef unsigned long long  uint64_t;
typedef unsigned short      uint16_t;
typedef unsigned char       uint8_t;
#define NULL 0

typedef uint32_t addr32; /* Program address */
typedef uint32_t offset32; /* File offset */
typedef uint32_t uint32;

struct Elf32_Ehdr {
  unsigned char e_ident[16]; /* ELF identification bytes. */
  uint16_t type;      /* Type of file (see ET_* below) */
  uint16_t machine;   /* Required architecture for 'this file' (see EM_*) */
  uint32 version;     /* Must be equal to 1 */
  addr32 entry;       /* Address to jump to in order to start program */
  offset32 phoff;     /* Program header table's file (in bytes) offset */
  offset32 shoff;     /* Section header table's file (in bytes) offset */
  uint32 flags;       /* Processor-specific flags */
  uint16_t ehsize;    /* Size - in bytes - of ELF header */
  uint16_t phentsize; /* Size of an entry in the program header table */
  uint16_t phnum;     /* Number of entries in the program header table */
  uint16_t shentsize; /* Size of an entry in the section header table */
  uint16_t shnum;     /* Number of entries in the section header table */
  uint16_t shstrndx;  /* Sect hdr table index of sect name string table */
}; /* See also Plan9's `src/libmach/elf.h` for a mature alternative definition. */

enum { ET_EXEC = 2 /* File type is 'Executable file'. */ };

struct Elf32_Phdr { /* Program segment header. */
   uint32 type; // Segment type
   offset32 offset; // Segment file offset
   addr32 vaddr, paddr; // Segment virtual and physical address
   uint32 filesz; // Segment size in file
   uint32 memsz; // Segment size in memory
   uint32 flags; // Segment flags
   uint32 align; // Segment alignment
};

struct Elf32_Shdr {  // Section header.
   uint32_t name;    // Section name (index into string table)
   uint32 type;      // Section type (SHT_*)
   uint32 flags;     // Section flags (SHF_*)
   uint32_t addr;    // Address where section is to be loaded
   offset32 offset;  // File offset of section data, in bytes
   uint32 size;      // Size of section, in bytes
   uint32_t link;    // Section type-specific header table index link
   uint32 info;      // Section type-specific extra information
   uint32 addralign; // Section address alignment
   uint32 entsize;   // Size of records contained within the section
};

#pragma mark - Helper functions

void
Hex( /* TeX §64 and §67 */
  uint64_t n,
  uint8_t digitsOrLetter, /* Not more than 8 digits! */
  void (^output)(char c)
)
{
    auto print = ^(char * buf, char digits, void (^touch)(char
      utf8)) { char c;
        while (digits > 0) { digits--;
          if (buf[digits] < 10) { c = '0' + buf[digits]; }
          else { c = 'A' - 10 + buf[digits]; }
          touch(c);
        }
    };
    
    char buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, k = 0;
    do { buf[k] = n % 16; n = n/16; k++; } while (n != 0);
    print(buf, digitsOrLetter, output);
}

int
IsPrefixOrEqual(
  const char * eightbitString, /* Possibly `normalizedUtf8` */
  const char * eightbitPrefix  /* Smiley appears when `prompt> nm`! */
) /* Consider changing the below to include muslticore. */
{
    const char *s=eightbitString, *p=eightbitPrefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in `prefix` equal to `string`. */
    /* *p != 0 && *s != 0 */
    char diff = *s - *p;
    if (diff) { return 0; }
    s++, p++;
    goto again;
}

#pragma mark - Intermediate definitions:

static
bool
isLoadable(
  const char * sectname,
  bool inclMipsSects
)
{
    const char * loadables[] = { ".text", ".rodata", ".data", ".conf",
 /* the 4ᵗʰ: */ ".boot", ".start", ".tlb", ".cache", ".special", NULL };
    if (inclMipsSects) { loadables[4] = NULL; } int i; const char * sct;
    for (i = 0, sct = loadables[i]; sct; i++) {
       if (IsPrefixOrEqual(sectname, sct) == 0) { return true; } /* Includes 
  prefixes '.text,.' and '.data,.'. */
    }
    return false;
}

template <typename T> T min(T x₁, T x₂) { return x₂ < x₁ ? x₂ : x₁; }
static uint32_t AsPhysical(addr32 vAddr) { return vAddr & 0x1FFFFFFF; }
#define STRINGIFY(s) #s
#define QUOTE(s) STRINGIFY(s) /* ☜😐: ! */

#include <stddef.h> /* For `size_t`… */
#include <stdio.h> /* ...and `fprintf`, `FILE`, `fopen`, `fread`, `fseek`, 
 `fclose`, `SEEK_SET`, `stdout` and `stderr`… */
#include <stdlib.h> /* …together with `malloc` and `exit`. */

 /*
  
  Extended Linear Address: 𝘌․𝘨 :𝟶𝟸𝟶𝟶𝟶𝟶 𝟶𝟺 𝙵𝙵𝙵𝙵 𝙵𝙲, 𝘪․𝘦 two big endian
  data bytes contains the upper two bytes of a 32-bit address.
  
  Note that the programmer expects a physical address and not a virtual
  address so we have to map back into the physical address space.
  
  */

auto emitIntelExtendedLinAddr = ^(
  uint32_t paddr
) {
  uint8_t msb=0xff&(paddr>>24), lsb=0xff&(paddr>>16);
  fprintf(stdout, ":02000004");
  uint8_t checksum = 6 + msb + lsb;
  Hex(msb, 2, ^(char s) { fprintf(stdout, "%c", s); } );
  Hex(lsb, 2, ^(char s) { fprintf(stdout, "%c", s); } );
  Hex(-checksum, 2, ^(char s) { fprintf(stdout, "%c", s); } );
  fprintf(stdout, "\x0d\x0a"); /* The 'symbols' 'cr/lf' on the go. */
};

#pragma mark - …and the main entry-point

#define ⁺⁼ProcessCommandline(ARGV)                                              \
auto process_commandline = ^(const char * argv[]) {                             \
  auto scan_option = ^(const char * arg) {                                      \
    switch (*arg) {                                                             \
    case 'h': fprintf(stderr, "Usage: %s [-b <bootloader.hex file>] [-s] "      \
      "<elf32 file>\n", argv[0]); exit(1);                                      \
    case 'b': open_bootloader_file(*ca++); return;                              \
    case 's': inclMipsSects = true; return;                                     \
    case 'v': fprintf(stderr, "%s version: %s\n", argv[0], QUOTE(SHA1GIT));     \
      exit(2);                                                                  \
    default: fprintf(stderr, "Unknown command-line argument\n"); exit(3); }     \
  }; /* argv[argc] == NULL, so: */                                              \
  for (ca = argv + 1; *ca && (*ca)[0] == '-'; ca++) scan_option(1 + *ca);       \
  if (!*ca) scan_option("h"); /* 'No args' ∧ 'ends with argument'. */           \
}; process_commandline(ARGV) /* Implicits in lambda expression: `ca`, 
  `inclMipsSects` and `SHA1GIT`. */

int
main(
  int argc,
  const char *argv[]
)
{ __block bool inclMipsSects=false; __block FILE * boot=NULL;
    __block const char **ca;
#define elf32_filenameOrNULL *ca
    auto open_bootloader_file = ^(const char *utf8path𝘖𝘳𝙽𝚄𝙻𝙻) {
      boot = fopen(utf8path𝘖𝘳𝙽𝚄𝙻𝙻, "r");
      if (boot == NULL) { fprintf(stderr, "Unable to open bootloader file\n");
        exit(3); } };
    ⁺⁼ProcessCommandline(argv);
    if (boot) { char c; while (fread(&c, 1, 1, boot)) { fprintf(stdout, "%c", c); }
      fclose(boot); } /* ⬷ 𝖨․𝘦 pasting the content of the boot file as a prefix to the elf32 file. */
    __block FILE * in = fopen(elf32_filenameOrNULL, "rb");
    if (!elf32_filenameOrNULL) { fprintf(stderr, "No elf32 file given at your command line\n"); exit(5); }
    if (!in) { fprintf(stderr, "Unable to open elf32 file\n"); exit(4); }
    /* Parse open file */
#define EXIT_INVALID_FILE 7
    auto fixElf32 = ^(long offset) { if (fseek(in, offset, SEEK_SET)) { exit(EXIT_INVALID_FILE); } };
    auto readElf32 = ^(void * __restrict p, size_t bytes, size_t nitems) {
      size_t actual = fread(p, bytes, nitems, in); if (bytes * nitems != actual) {
      fprintf(stderr, "Read error\n"); exit(6); } };
/* 1 */ Elf32_Ehdr elfHeader;
    readElf32(&elfHeader, sizeof(Elf32_Ehdr), 1);
    /* offset32 pgmheaderOffset = elfHeader.e_phoff;
    uint16_t pgmheaderSize = elfHeader.e_phentsize; */
    offset32 offsetSectHeader = elfHeader.shoff;
    uint16_t bytesSectHeader = elfHeader.shentsize;
    if (elfHeader.type != ET_EXEC) { fprintf(stderr, "Input file is not an executable\n"); exit(EXIT_INVALID_FILE); }
    if (bytesSectHeader != sizeof(Elf32_Shdr)) { fprintf(stderr, "Invalid section header table size\n"); exit(EXIT_INVALID_FILE); }
    /* Now, read the section name string table. */
/* 2 */ Elf32_Shdr SectionNames;
    long offsetSectnames = offsetSectHeader + bytesSectHeader*elfHeader.shstrndx;
    fixElf32(offsetSectnames);
    readElf32(&SectionNames, sizeof(Elf32_Shdr), 1);
    fixElf32(SectionNames.offset);
    const char * sectionnames = (const char *)malloc(SectionNames.size);
    readElf32((void *)sectionnames, 1, SectionNames.size);
    
    /* fprintf(stderr, "index name offset bytes linaddr type\n"); */
    
    for (int i = 0; i < elfHeader.shnum; i++) {
/* N */ Elf32_Shdr sectionHeader;
        fixElf32(offsetSectHeader + i*bytesSectHeader);
        readElf32(&sectionHeader, sizeof(Elf32_Shdr), 1);
        const char * name = sectionnames + sectionHeader.name;
        if (sectionHeader.size != 0 && isLoadable(name, inclMipsSects)) {
         /* fprintf(stderr, "%d\t%s\t%x\t%x\t%x\t%x\n", i, name, sectionHeader.sh_offset,
              sectionHeader.sh_size, sectionHeader.sh_addr, sectionHeader.sh_type); */
            uint64_t bytesleft = sectionHeader.size;
            uint8_t * sectcontent = (uint8_t *)malloc(bytesleft);
/* N+1 */   fixElf32(sectionHeader.offset);
            readElf32((void *)sectcontent, 1, bytesleft);
            /* Retrieve LMA, not VMA (𝘪․𝘦 the Flash-address not the RAM-adress.) */
            /* Elf32_Phdr programHeader;
               setElf32Pos(pgmheaderOffset + i*pgmheaderSize);
               fread(&programHeader, sizeof(Elf32_Phdr), 1, in);
               fprintf(stderr, "LMA for %s is %x, VMA is %x sectionHeader is %x\n", name, programHeader.p_paddr, programHeader.p_vaddr, sectionHeader.sh_addr);
               programHeader.p_paddr = AsPhysical(programHeader.p_paddr);
               uint8_t msb, lsb; parts(programHeader.p_paddr, msb, lsb); */
            addr32 vAddr = sectionHeader.addr;
            uint32_t paddr = AsPhysical(vAddr);
        again:
            uint64_t offset = sectionHeader.size - bytesleft;
            if (offset % 32768 == 0) { emitIntelExtendedLinAddr(paddr + offset); }
            fprintf(stdout, ":");
            uint64_t bytesOnline = min(bytesleft, (uint64_t)16);
            uint8_t checksum = bytesOnline;
            Hex(bytesOnline, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            uint16_t address = 0xFFFF&(paddr + offset);
            Hex(address, 4, ^(char s) { fprintf(stdout, "%c", s); } );
            checksum += 0xff&address; checksum += 0xff&(address>>8);
            Hex(0, 2, ^(char s) { fprintf(stdout, "%c", s); } ); /* Content follows */
            for (int i = 0; i < bytesOnline; i++) {
                uint8_t data = *(sectcontent + (i + sectionHeader.size - bytesleft));
                Hex(data, 2, ^(char s) { fprintf(stdout, "%c", s); } );
                checksum += data;
            }
            Hex(-checksum, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            fprintf(stdout, "\x0d\x0a"); /* ...and again. */
            bytesleft -= bytesOnline;
            if (bytesleft > 0) goto again;
        }
    }
    /* In-case we're creating a boot loader… */
    if (boot) { fprintf(stdout, ":00000001FF\x0d\x0a"); }
    fclose(in); // …else bootloader 𝑎𝑐𝑐𝑖𝑑𝑒𝑛𝑡𝑙𝑦 ends up optional.
    return 0;
}
