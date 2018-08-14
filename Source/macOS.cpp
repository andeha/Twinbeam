//
//  macOS.cpp
//  Twinbeam
//

#include <Twinbeam.h>
#include "malloc.cxx"

// µA("x86_64", "haswell", x₁, x₂)
// µA("mips", "r2", x₃, x₄)
int // difference between the two first differing bytes.
__attribute__((target("sse4.2")))
Compare8Memory(
    ByteAlignedRef one,
    ByteAlignedRef two,
    __builtin_uint_t bytes
) // memcmp i.e fixed size and fast.
// constexpr bool IsEqual(ByteAlignedRef one, ByteAlignedRef two, __builtin_uint_t bytes)
{
    if (bytes == 0 || (one == two)) { return 0; }
    
    const uint8_t mode = _SIDD_UBYTE_OPS | _SIDD_CMP_EQUAL_EACH |
      _SIDD_NEGATIVE_POLARITY | _SIDD_LEAST_SIGNIFICANT;
    
    __m128i const *p1 = (__m128i const *)one;
    __m128i const *p2 = (__m128i const *)two;
    
    for (/**/; bytes != 0; p1++, p2++) {
        
        const __m128i a = _mm_loadu_si128(p1), b = _mm_loadu_si128(p2);
        
        if (_mm_cmpestrc(a, bytes, b, bytes, mode)) {
            
            const auto idx = _mm_cmpestri(a, bytes, b, bytes, mode);
            
            const uint8_t b1 = ((char *)(p1))[idx];
            const uint8_t b2 = ((char *)(p2))[idx];
            
            if (b1 < b2) { return -1; } else if (b1 > b2) { return +1; }
            else { return 0; }
        }
        
        if (bytes > 16) { bytes -= 16; } else { bytes = 0; }
    }
    
    return 0;
}

#include <mach-o/loader.h>
#include <mach-o/nlist.h>

void
Symbols(
    const char * utf8exepath,
    void (^callback)(const char *, uint64_t, bool&))
{
    if (Opt<Memoryregion> regionOpt = Memoryregion::reflect(utf8exepath)) {
        
        char *obj = (char *)(*regionOpt).pointer(0).pointer;
        
        char *obj_p = (char *)obj;
        struct mach_header_64 *header = (struct mach_header_64 *)obj_p;
        obj_p += sizeof *header;
        struct section *sections = NULL;
        uint32_t nsects;
        
        __block bool outerStop = false;
        
        for (int i = 0; i < header->ncmds; ++i) {
            struct load_command *lc = (struct load_command *)obj_p;
            if (lc->cmd == LC_SYMTAB) {
                struct symtab_command *symtab = (struct symtab_command *)obj_p;
                obj_p += sizeof *symtab;
                struct nlist_64 *ns = (struct nlist_64 *)(obj + symtab->symoff);
                char *strtable = obj + symtab->stroff;
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
}

#include <stdio.h>

void
RunUnitTests(
    const char * filepath
)
{
    Symbols(filepath, ^(const char * sym, uint64_t addr, bool& stop) {
        if (addr && IsPrefixOrEqual((char *)sym, (char *)"_UnitTest_")) {
            printf("\nRunning %s\n",  sym);
            typedef void (*Testcase)(); void (*testcase)() = (Testcase)addr;
            testcase();
        }
    });
}
