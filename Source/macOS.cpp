//
//  macOS.cpp
//  Twinbeam
//

#include <Twinbeam.h>
#include "malloc.cxx"

/* µA("x86_64", "haswell", x₁, x₂)
µA("mips", "r2", x₃, x₄) */
int
__attribute__((target("sse4.2")))
Compare8Memory(
  ByteAlignedRef p₁,
  ByteAlignedRef p₂,
  __builtin_uint_t bytes
) /* A․𝘬․a 𝚖𝚎𝚖𝚌𝚖𝚙: Also consider DMA and __attribute__ ((target ("default"))). */
{
    uint8_t 🥈ᵢ mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH |
      _SIDD_NEGATIVE_POLARITY | _SIDD_LEAST_SIGNIFICANT;
    
    for (/**/; bytes != 0; p₁ += 16, p₂ += 16) {
        __builtin_uint_t clamp = bytes > 16 ? 0 : 16 - bytes;
        __m128i 𝟷 = _mm_loadu_si128((__m128i const *)p₁),
           𝟸 = _mm_loadu_si128((__m128i const *)p₂);
        int idx = _mm_cmpestri(𝟷, bytes, 𝟸, bytes, mode);
        if (idx != 0) { return bytes; }
        if (bytes > 16) { bytes -= 16; } else { bytes = 0; }
    }
    return 0;
} /* Notice that this method is 'too cristalline' when dealing with Unicodes. */

#ifdef __x86_64__
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#elif defined __mips__
#endif

void *
mapfileʳᵚ( /* A․𝘬․a `findAndmap`, `mapregularfile`, `mapfileʳᵚ₊₀`. */
  const char * canonicalRegularOrLinkpathᵘᵗf⁸, /* A․𝘬․a `canonicalRegularOrLinkpathᵚ` */
  __builtin_int_t pagesOffset,
  __builtin_int_t pagesCountOrZero,
  __builtin_int_t * bytesActual,
  bool append𝙴𝙾𝚃at𝙴𝙾𝙵
) /* Optionally asynchronous, essential also in run-time and not 
  between the sheets of sysenters. */
{ void *p;
    __builtin_int_t bytesOffset = pagesOffset*SystemInfoPagesize();
#ifdef __x86_64__
    /* bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ =
    Utf8BytesIncludingNull(canonicalFilepathᵚ.tetras<<2, 
      canonicalFilepathᵚ.unicodes, invalid);
    if (invalid) { return NULL; };
    char utf8Filepath[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(utf8Filepath, ³²b, ⁸b)) { return NULL; } */
    int fd = open(canonicalRegularOrLinkpathᵘᵗf⁸, O_RDONLY);
    if (fd == -1) { return NULL; } struct stat sb;
    if (fstat(fd, &sb) == -1) { goto err; }
    if (!S_ISREG(sb.st_mode)) { goto err; } /* Not regular. */
    *bytesActual = pagesCountOrZero == 0 ? sb.st_size - bytesOffset : 
      pagesCountOrZero*SystemInfoPagesize();
    p = mmap(0, *bytesActual, PROT_READ, MAP_SHARED, fd, bytesOffset);
    if (p == MAP_FAILED) { goto err; }
#elif defined __mips__
    /* See --<🥽 Memclone.cpp>{Copy} */
#endif
    return p;
err:
#ifdef __x86_64__
    if (close(fd) == -1) { return NULL; } /* TODO: Close when not error. */
#endif
    return NULL;
} /* See --<🥽 Cordal.cpp> when ⁻ᵚ and also the version for Unicode and Pic32. */

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

void
Symbols(
  const char * utf8exepath,
  void (^callback)(const char *, uint64_t, bool&))
{ __builtin_int_t bytesActual;
    uint8_t * obj = (uint8_t *)mapfileʳᵚ(utf8exepath, 0, 0, &bytesActual, false);
    uint8_t * obj_p = obj;
    
    struct mach_header_64 * header = (struct mach_header_64 *)obj_p;
    obj_p += sizeof *header;
    struct section * sections = 0;
    uint32_t nsects;
    
    __block bool outerStop = false;
    
    for (int i = 0; i < header->ncmds; ++i) {
        struct load_command *lc = (struct load_command *)obj_p;
        if (lc->cmd == LC_SYMTAB) {
           struct symtab_command *symtab = (struct symtab_command *)obj_p;
           obj_p += sizeof *symtab;
           struct nlist_64 *ns = (struct nlist_64 *)(obj + symtab->symoff);
           char * strtable = (char *)(obj + symtab->stroff);
           for (int i = 0; i < symtab->nsyms; i++) {
              struct nlist_64 *entry = ns + i;
              uint32_t idx = entry->n_un.n_strx;
              callback(strtable + idx, entry->n_value, outerStop);
              if (outerStop) { return; }
           }
        } else if (lc->cmd == LC_SEGMENT) {
           segment_command *segment = (struct segment_command *)obj_p;
           obj_p += sizeof *segment;
           nsects = segment->nsects;
           sections = (struct section *)obj_p;
           obj_p += nsects * sizeof *sections;
        } else { obj_p += lc->cmdsize; }
    }
}

void
RunUnitTests(
  const char * filepath,
  void (^out)(const char *s)
)
{
    Symbols(filepath, ^(const char * sym, uint64_t addr, bool& stop) {
        if (addr && IsPrefixOrEqual((char *)sym, (char *)"_Unittest_")) {
            out("\nRunning "); out(sym); out("\n");
            typedef void (*Testcase)(); void (*testcase)() = (Testcase)addr;
            testcase();
        }
    });
}
