/*  Bounds.cpp | On 'interval' and pointer. 
 
 The pointer arithmetic protection method developed by Intel named MPX 
 appears to lack an llvm foundation. In Mach: `vm_region` and `vm_protect` 
 and in UNIX: `madvise`, `minherit`, `mincore`, `mlock` and `mprotect`. For 
 pic32mzda: SBFLAG.TxPGV, SBTxREGy (up to 14 areas) and other registers 
 described in section 48 'Memory Organization and Permissions'.
 
 None of the technologies appear yet to encompass memory intervals 
 a․𝘬․a 'pointer arithmetics' and dereferencing.
 
 𝘊𝘧․ HW-flag indicating pointer + register + size₋register or SW: 
 
 Compile with clang++ -g -I ../.. --std=c++2a -o Bounds '🥽⋆Bounds.cpp' */
 
#include <Twinbeam.h>
#include <stdio.h>

struct Intervallic;
struct Delegate { void issue(Intervallic * d, int nº) { printf("Issue %d\n", nº); } };

struct Intervallic { /* A․𝘬․a `TransitiveIntervalPointer`. */
  
  enum { UnableToAccess=10, UnableToRead=12, UnableToKeep=11 };
  
  __builtin_uint_t 🥈 wordbits=sizeof(__builtin_uint_t), mask=~(wordbits-1);
  
  Intervallic(void * p, int bytes, Delegate * d) 
  { base=(uint8_t *)p; bʸtes=bytes; delegate=d; }
  
  uint8_t * base; __builtin_int_t bʸtes; Delegate * delegate;
  
#pragma mark - First a word-granola:
  
  __builtin_uint_t * aligned(uint8_t * /* byteaddress */ unaligned, short &lshbits) const {
    __builtin_uint_t * wordloc = (__builtin_uint_t *)(__builtin_uint_t(unaligned)&mask);
    lshbits = wordbits - (__builtin_uint_t(unaligned) & ~mask);
    return wordloc;
  };
  
  __builtin_uint_t word(uint8_t * /* byteaddress */ unaligned, void (^issue)(int nº)) const {
    /* virtuaddr vaddr=loc.pointer; int ᵇoffset=vaddr&0xfff; int long idxᵖᵗ=vaddr>>12; */
    static __builtin_uint_t dummy=0;
    if (unaligned < base || unaligned >= base + bʸtes) { issue(UnableToRead); return dummy; }
    short dummybits; __builtin_uint_t * wordloc=aligned(unaligned,dummybits);
    return *wordloc;
  } /* A․𝘬․a `deref` and `alignedword`. */
  
  int keep(uint8_t * /* byteaddress */ unaligned, __builtin_uint_t word) const {
    /* virtuaddr vaddr=loc.pointer; int ᵇoffset=vaddr&0xfff; int long idxᵖᵗ=vaddr>>12; */
    if (unaligned < base || unaligned >= base + bʸtes) { return -1; }
    short dummybits; __builtin_uint_t * wordloc=aligned(unaligned,dummybits);
    *wordloc=word;
    return 0;
  }
  
#pragma mark - The overt simplification
  
  uint8_t& operator[](int idx) {
    auto issue = ^(int nº) { };
    uint8_t * /* byteaddress */ loc = idx + base;
    __builtin_uint_t y₁ = word(loc,issue);
    /* uint8_t y₂ = ⁸𝟷ᵈ(loc,y₁,issue); ⬷ Becomes a returning copy of value here. */
    uint8_t y₂ = 0; /* ⁸𝟷ᵈ(0,idx,bʸtes,last,issue); ⬷ Becomes a returning copy of value here. */
    return y₂;
  } /* Retrieve disjunct/sediment/segments. */
  
#pragma mark - Nitty-gritty and the details
  
  enum Sentinel { cyclic, last }; /* Does not define `keep𝟷ᵈ`/`⁸𝟷ᵈ` also for idx < 0. */
  
  __builtin_int_t byteoffset😐⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, 
      Sentinel wrap, __builtin_int_t totbytes) { 
    if (byteNº < 0 || 𝛥bytes < 0 || totbytes <= 0) { return -1; }
    switch (wrap) { case cyclic: return 𝛥bytes % totbytes; 
    case last: return 𝛥bytes < totbytes ? 𝛥bytes : totbytes - 1;
  } };
  
  /* enum Width { 𝟾, 𝟷𝟼, 𝟹𝟸, 𝟼𝟺, 𝟼𝟺lo, 𝟼𝟺hi, 𝟷𝟸𝟾lo, 𝟷𝟸𝟾hi };
  
  __builtin_uint_t place(__builtin_uint_t original, Width w) { } */
  
  uint8_t * /* byteaddress */ relative(__builtin_int_t addend) { return base + addend; }
  
  uint8_t ⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, Sentinel wrap, 
      __builtin_int_t totbytes, void (^keep)(uint8_t& shifted) = ^(uint8_t &) { }
  )
  {  Delegate * d = delegate; static uint8_t dummy=0;
    __builtin_int_t toadd=byteoffset😐⁸𝟷ᵈ(byteNº,𝛥bytes,wrap,totbytes);
    auto issue = ^(int nº) { if (d) d->issue(this,nº); };
    if (toadd == -1) { issue(UnableToAccess); }  /* *byteloc=byte; Or: */
    uint8_t * /* byteaddress */ unaligned=relative(toadd);
    short lshbits; __builtin_uint_t * dummyloc=aligned(unaligned,lshbits);
    __builtin_uint_t original=word(unaligned,issue);
    auto byteExtract = ^(__builtin_uint_t w, short lshbits) /* -> uint8_t */ { 
      uint8_t shifted=uint8_t(w>>lshbits); return shifted; };
    auto updateByte = ^(__builtin_uint_t w, short lshbits, uint8_t byte) { return 
      (w & ~(__builtin_uint_t(0xff)<<lshbits)) | __builtin_uint_t(byte)<<lshbits; };
    uint8_t shifted₁,shifted₂; shifted₁=shifted₂=byteExtract(original,lshbits);
    if (keep) { keep(shifted₂); }
    __builtin_uint_t current=updateByte(original,lshbits,shifted₂);
    if (this->keep(unaligned,current)) { issue(UnableToKeep); return dummy; }
    return shifted₁;
  }
  
}; /* This variant is for MMU-based CPUs. */

#pragma mark - Main entry point:

int
main(
  int argc,
  const char * argv[]
)
{  int 🥈 bytes=4096; void *buf=malloc(bytes); Delegate delegate;
    
    Intervallic interval₁(buf,bytes,&delegate);
    
    auto hitch = ^{ printf("Writing outside bounds\n"); exit(1); };
    auto ʳᵈissue = ^(int nº) { printf("Reading outside bounds\n"); exit(2); };
    uint8_t * /* byteaddress */ wloc=100+(uint8_t *)buf; __builtin_uint_t word=0xadbccafe;
    if (interval₁.keep(wloc,word)) { hitch(); return 1; }
    __builtin_uint_t word₁=interval₁.word(wloc,ʳᵈissue);
    printf("word₁ is %llx\n", word₁);
    
    /* Detail interface case: */
    __builtin_int_t byteNº=1, 𝛥bytes=3, totbytes=10;
    uint8_t old₁ = interval₁.⁸𝟷ᵈ(byteNº, 𝛥bytes, Intervallic::last, totbytes, 
      ^(uint8_t& shifted) { shifted=0xca; });
    uint8_t old₂ = interval₁.⁸𝟷ᵈ(byteNº, 𝛥bytes, Intervallic::last, totbytes);
    printf("Old₁/old₂ is %x/%x\n", old₁, old₂);
    
    return 0;
}


