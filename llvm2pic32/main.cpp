//
//  main.cpp (Compile with clang -o llvm2pic32 -std=c++1z main.cpp)
//  llvm2pic32
//

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using Elf32_Addr = uint32_t; // Program address
using Elf32_Off = uint32_t;  // File offset
using Elf32_Half = uint16_t;
using Elf32_Word = uint32_t;
using Elf32_Sword = int32_t;

struct Elf32_Ehdr {
    unsigned char e_ident[16]; // ELF Identification bytes
    Elf32_Half e_type;      // Type of file (see ET_* below)
    Elf32_Half e_machine;   // Required architecture for this file (see EM_*)
    Elf32_Word e_version;   // Must be equal to 1
    Elf32_Addr e_entry;     // Address to jump to in order to start program
    Elf32_Off e_phoff;      // Program header table's file offset, in bytes
    Elf32_Off e_shoff;      // Section header table's file offset, in bytes
    Elf32_Word e_flags;     // Processor-specific flags
    Elf32_Half e_ehsize;    // Size of ELF header, in bytes
    Elf32_Half e_phentsize; // Size of an entry in the program header table
    Elf32_Half e_phnum;     // Number of entries in the program header table
    Elf32_Half e_shentsize; // Size of an entry in the section header table
    Elf32_Half e_shnum;     // Number of entries in the section header table
    Elf32_Half e_shstrndx;  // Sect hdr table index of sect name string table
};

struct Elf32_Shdr { // Section header
    Elf32_Word sh_name;      // Section name (index into string table)
    Elf32_Word sh_type;      // Section type (SHT_*)
    Elf32_Word sh_flags;     // Section flags (SHF_*)
    Elf32_Addr sh_addr;      // Address where section is to be loaded
    Elf32_Off sh_offset;     // File offset of section data, in bytes
    Elf32_Word sh_size;      // Size of section, in bytes
    Elf32_Word sh_link;      // Section type-specific header table index link
    Elf32_Word sh_info;      // Section type-specific extra information
    Elf32_Word sh_addralign; // Section address alignment
    Elf32_Word sh_entsize;   // Size of records contained within the section
};

enum { // File types
    ET_EXEC = 2 // Executable file
};

void
Hex( // TeX §64 and §67
    uint64_t n,
    uint8_t digitsOrLetter, // Not more than 8 digits!
    void (^touchbase)(char s)
)
{
    auto printDigits = ^(char *buf, char digits, void (^progress)(char
      utf8)) { char c;
        while (digits > 0) { digits--;
            if (buf[digits] < 10) { c = '0' + buf[digits]; }
            else { c = 'A' - 10 + buf[digits]; }
            progress(c);
        }
    };
    
    char buf[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    char k = 0;
    do { buf[k] = n % 16; n = n/16; k++; } while (n != 0);
    printDigits(buf, digitsOrLetter, touchbase);
}

#define MIN(a,b) (((a)<(b))?(a):(b))

// The Microchip PIC32 mapping
Elf32_Addr virtualToPhysical(Elf32_Addr vAddr) { return vAddr & 0x1FFFFFFF; }

int
main(
     int argc,
     const char *argv[]
)
{
    const char *pathIn = NULL;
    if (argc != 2 && argc != 4) { fprintf(stderr, "Usage: llvm2pic32 [-b <bootloader.hex file>] <elf32 file>\n");  return 1; }
    if (argc == 4) { 
        if (argv[1][0] != '-' || argv[1][1] != 'b') { 
            fprintf(stderr, "Unknown command-line argument\n"); return 2; 
        }
        FILE * boot = fopen(argv[2], "r"); char c;
        if (boot == NULL) { fprintf(stderr, "Unable to open bootloader file\n"); return 3; }
        while (fread(&c, 1, 1, boot)) { fprintf(stdout, "%c", c); }
        fclose(boot); pathIn = argv[3];
    } else { pathIn = argv[1]; }
    FILE *in = fopen(pathIn, "rb");
    if (in == NULL) { fprintf(stderr, "Unable to open file\n"); return 4; }
    Elf32_Ehdr elfHeader;
    fread(&elfHeader, sizeof(Elf32_Ehdr), 1, in);
    Elf32_Off sectHeaderOffset = elfHeader.e_shoff;
    Elf32_Half sectHeaderCount = elfHeader.e_shnum;
    Elf32_Half sectHeaderSize = elfHeader.e_shentsize;
    Elf32_Half sectionNameStringTableSectionIndex = elfHeader.e_shstrndx;
    Elf32_Half fileType = elfHeader.e_type;
    if (fileType != ET_EXEC) {} // error
    if (sectHeaderSize != sizeof(Elf32_Shdr)) {} // error
    // Read the section name string table
    fseek(in, sectHeaderOffset + sectHeaderSize*sectionNameStringTableSectionIndex, SEEK_SET);
    Elf32_Shdr stringTableHeader;
    fread(&stringTableHeader, sizeof(Elf32_Shdr), 1, in);
    fseek(in, stringTableHeader.sh_offset, SEEK_SET);
    const char * stringTable = (const char *)malloc(stringTableHeader.sh_size);
    fread((void *)stringTable, 1, stringTableHeader.sh_size, in);
    // Read the sections
    // printf("index name offset bytes linaddr type\n");
    for (int i = 0; i < sectHeaderCount; i++) {
        fseek(in, sectHeaderOffset + i*sectHeaderSize, SEEK_SET);
        // long int x = ftell(file); printf("ftell is %ld ", x);
        Elf32_Shdr sectionHeader;
        fread(&sectionHeader, sizeof(Elf32_Shdr), 1, in);
        const char *name = stringTable + sectionHeader.sh_name;
        if (sectionHeader.sh_size != 0 && (strcmp(name, ".text") == 0 || 
              strcmp(name, ".data") == 0 || strcmp(name, ".bss") == 0 || 
              strcmp(name, ".conf") == 0)) {
            // fprintf(stderr, "%d\t%s\t%x\t%x\t%x\t%x\n", i, name, sectionHeader.sh_offset,
            //   sectionHeader.sh_size, sectionHeader.sh_addr, sectionHeader.sh_type);
            fseek(in, sectionHeader.sh_offset, SEEK_SET);
            uint64_t bytesLeft = sectionHeader.sh_size;
            uint8_t *sectionData = (uint8_t *)malloc(bytesLeft);
            fread((void *)sectionData, 1, bytesLeft, in);
            // Extended Linear Address
            // :0200000 4FFFF FC  // Two big endian data bytes contains the upper two bytes of a 32-bit address.
            // Note that the programmer expects a physical address and not a
            // virtual address so we have to map back to a physical address space.
            fprintf(stdout, ":02000004");
            sectionHeader.sh_addr = virtualToPhysical(sectionHeader.sh_addr);
            uint8_t msb = 0xff&(sectionHeader.sh_addr>>24);
            uint8_t lsb = 0xff&(sectionHeader.sh_addr>>16);
            uint8_t checksum = 6 + msb + lsb;
            Hex(msb, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            Hex(lsb, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            Hex(-checksum, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            fprintf(stdout, "\x0d\x0a");
        again:
            fprintf(stdout, ":");
            uint64_t bytesInLine = MIN(bytesLeft, 16);
            checksum = bytesInLine;
            Hex(bytesInLine, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            uint64_t offset = sectionHeader.sh_size - bytesLeft;
            uint16_t address = 0xFFFF&(sectionHeader.sh_addr + offset);
            Hex(address, 4, ^(char s) { fprintf(stdout, "%c", s); } );
            checksum += 0xff&address;
            checksum += 0xff&(address>>8);
            Hex(0, 2, ^(char s) { fprintf(stdout, "%c", s); } ); // Data follows
            for (int i = 0; i < bytesInLine; i++) {
                uint8_t data = *(sectionData + (i + sectionHeader.sh_size - bytesLeft));
                Hex(data, 2, ^(char s) { fprintf(stdout, "%c", s); } );
                checksum += data;
            }
            Hex(-checksum, 2, ^(char s) { fprintf(stdout, "%c", s); } );
            fprintf(stdout, "\x0d\x0a");
            bytesLeft -= bytesInLine;
            if (bytesLeft > 0) goto again;
        }
    }
    
    fprintf(stdout, ":00000001FF\x0d\x0a");
    fclose(in);
    return 0;
}
