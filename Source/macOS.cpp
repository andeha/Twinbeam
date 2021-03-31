/*  macOS.cpp | specializations and unique. */

#include <Twinbeam.h>
#define USE_LOCKS           0
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include "malloc.cxx"

#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void *
mapfileʳᵚ( /* ⬷ a․𝘬․a 'findAndmap', 'mapregularfile', 'mapfileʳᵚ₊₀'. */
  const char * canonicalUtf8RegularOrLinkpath, /* todo `canonicalRegularOrLinkpathᵚ`. */
  __builtin_int_t bytesOffset, /* pagesOffset is for sector-based physical non-volatility (💰). */
  __builtin_int_t pages𝘖rZero, __builtin_int_t bytesAugment, 
  __builtin_int_t * bytesActual
/*  bool optionallyAppend𝙴𝙾𝚃at𝙴𝙾𝙵 i․𝘦 0x00000004 (Unicode) or 0x4 (utf-8). */
) /* ⬷ optionally asynchronous, essential also in run-time and not 
  between the sheets of sysenters. */
{ void * p; 
    /* __builtin_int_t bytesOffset = pagesOffset*SystemInfoPagesize(); */
#ifdef __x86_64__ 
    /* if (UnicodeToUtf8(char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 ucs𝘈𝘯𝘥𝟶𝚡𝟶𝟶𝟶𝟶𝘖𝘳𝖤𝖮𝖳, Maxpathᵗᵉᵗʳᵃˢ,
      ^(const char * utf8, int tetras, int utf8bytes) { }) { return NULL; } */
    int fd = open(canonicalUtf8RegularOrLinkpath, O_RDONLY);
    if (fd == -1) { return NULL; } struct stat sb;
    if (fstat(fd, &sb) == -1) { goto err; }
    if (!S_ISREG(sb.st_mode)) { goto err; } /* ⬷ not regular file. */
    *bytesActual = pages𝘖rZero == 0 ? sb.st_size - bytesOffset : 
      pages𝘖rZero*Syspagesize();
    p = mmap(0, bytesAugment + *bytesActual, PROT_READ, MAP_SHARED, fd, bytesOffset);
    if (p == MAP_FAILED) { goto err; }
#elif defined __mips__
    /* ⬷ see --<🥽 Memclone.cpp>{Copy} */
#endif
    return p; /* ⬷ additional background: `man munmap` and `man msync`. */
err:
#ifdef __x86_64__
    if (close(fd) == -1) { return NULL; } /* todo: close when not error. */
#endif
    return NULL;
} /* ⬷ see --<🥽 Cordal.cpp> when ⁻ᵚ and also the version for Unicode and Pic32. */

#pragma mark - automatically /for units testing/

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

void
Symbols(
  const char * utf8exepath,
  void (^callback)(const char * sym, uint64_t addr, bool& stop))
{ __builtin_int_t bytesActual;
    uint8_t * obj = (uint8_t *)mapfileʳᵚ(utf8exepath, 0, 0, 0, &bytesActual);
    uint8_t * obj_p = obj;
    
    struct mach_header_64 * header = (struct mach_header_64 *)obj_p;
    obj_p += sizeof *header;
    struct section * sections = 0;
    uint32_t nsects;
    
    bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 outerStop = false;
    
    for (int i=0; i<header->ncmds; ++i) {
        struct load_command *lc = (struct load_command *)obj_p;
        if (lc->cmd == LC_SYMTAB) {
           struct symtab_command *symtab = (struct symtab_command *)obj_p;
           obj_p += sizeof *symtab;
           struct nlist_64 *ns = (struct nlist_64 *)(obj + symtab->symoff);
           char * strtable = (char *)(obj + symtab->stroff);
           for (int i = 0; i < symtab->nsyms; i++) {
              struct nlist_64 *entry = ns + i;
              uint32_t idx = entry->n_un.n_strx;
              if ((entry->n_type & N_TYPE) == N_SECT) { callback(strtable + idx, 
                entry->n_value, outerStop); }
              if (outerStop) { return; }
           }
        } else if (lc->cmd == LC_SEGMENT) {
           segment_command * segment = (struct segment_command *)obj_p;
           obj_p += sizeof *segment;
           nsects = segment->nsects;
           sections = (struct section *)obj_p;
           obj_p += nsects * sizeof *sections;
        } else { obj_p += lc->cmdsize; }
    }
}


