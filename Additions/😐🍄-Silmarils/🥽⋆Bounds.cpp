/*  Bounds.cpp | On 'interval' and pointer. 
 
 The pointer arithmetic protection method developed by Intel named MPX 
 appears to lack an llvm foundation. In Mach: `vm_region` and `vm_protect` 
 and in UNIX: `madvise`, `minherit`, `mincore`, `mlock` and `mprotect`. For 
 pic32mzda: SBFLAG.TxPGV, SBTxREGy (up to 14 areas) and other registers 
 described in section 48 'Memory Organization and Permissions'.
 
 None of the technologies appear yet to encompass memory intervals 
 a․𝘬․a 'pointer arithmetics' and dereferencing.
 
 𝘊𝘧․ HW-flag indicating pointer + register + size₋register or SW: 
 
 Compile with:
 
 xcrun clang @ccargs_macᵧ² -o Bounds '🥽⋆Bounds.cpp' ../../Source/llvmʳᵗ³.cpp 
 
*/
 
#include <Twinbeam.h> /* Also --<Additions>--<Reference.hpp>. */

struct Delegate : public Refdelegate { void issue(int nº) { print("Issue ⬚\n", ﹟d(nº)); } };

#pragma mark - Main entry point:

int
main(
  int argc,
  const char * argv[]
)
{  int 🥈 bytes=4096; void *buf=malloc(bytes); Delegate delegate;
    
    Reference interval₁(buf,bytes,&delegate);
    
    auto hitch = ^{ print("Writing outside bounds\n"); exit(1); };
    auto ʳᵈissue = ^(int nº) { print("Reading outside bounds\n"); exit(2); };
    uint8_t * /* byteaddress */ wloc=100+(uint8_t *)buf; __builtin_uint_t word=0xadbccafe;
    if (interval₁.keep(wloc,word)) { hitch(); return 1; }
    short lshbits; __builtin_uint_t word₁=interval₁.word(wloc,lshbits,ʳᵈissue);
    print("word₁ is ⬚\n", ﹟x(word₁));
    
    /* Slim detailed-interface case: */
    __builtin_int_t byteNº₁=8, 𝛥bytes=8, totbytes=100;
    uint8_t 𝟾old₁=interval₁.⁸𝟷ᵈ(byteNº₁, 𝛥bytes, Sentinel::last, totbytes, 
      ^(uint8_t &shifted) { shifted=0xca; });
    uint8_t 𝟾old₂=interval₁.⁸𝟷ᵈ(byteNº₁, 𝛥bytes, Sentinel::last, totbytes);
    print("Byte old₁/old₂ is ⬚/⬚\n", ﹟x(𝟾old₁), ﹟x(𝟾old₂));
    
    /* Natural detail-interface case: */
    __builtin_int_t byteNº₂=8, 𝛥mips=8, totmips=100;
    uint32_t 𝟹𝟸old₁=interval₁.mips𝟷ᵈ(byteNº₂, 𝛥mips, Sentinel::last, totmips, 
      ^(uint32_t &shifted) { shifted=0xca; });
    uint32_t 𝟹𝟸old₂=interval₁.mips𝟷ᵈ(byteNº₂, 𝛥bytes, Sentinel::last, totmips);
    print("32-bits old₁/old₂ is ⬚/⬚\n", ﹟x(𝟹𝟸old₁), ﹟x(𝟹𝟸old₂));
    
    /* ...and when using indexing: */
    uint8_t y₁=interval₁[5];
    interval₁[5]=0xcc;
    uint8_t y₂=interval₁[5];
    print("y₁/y₂ is ⬚/⬚\n", ﹟x((int)y₁), ﹟x((int)y₂));
    
    return 0;
}


