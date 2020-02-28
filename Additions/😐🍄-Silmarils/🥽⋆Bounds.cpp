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
  
  __builtin_uint_t 🥈 wordbytes=sizeof(__builtin_uint_t), mask=~(wordbytes-1);
  
  Intervallic(void * p, int by𝘁es, Delegate * d) 
  { base=(uint8_t *)p; bytes=by𝘁es; delegate=d; }
  
  uint8_t * base; __builtin_int_t bytes; Delegate * delegate;
  
#pragma mark - First a word-granola:
  
  __builtin_uint_t * aligned(uint8_t * /* byteaddress */ unaligned, short &lshbits) const {
    __builtin_uint_t * wordloc = (__builtin_uint_t *)(__builtin_uint_t(unaligned)&mask);
    lshbits = (__builtin_uint_t(unaligned) & ~mask);
    return wordloc;
  }
  
  __builtin_uint_t& word(uint8_t * /* byteaddress */ unaligned, short &lshbits, void 
      (^issue)(int nº)) const { static __builtin_uint_t dummy=0;
    /* virtuaddr vaddr=loc.pointer; int ᵇoffset=vaddr&0xfff; int long idxᵖᵗ=vaddr>>12; */
    if (unaligned < base || unaligned >= base + bytes) { issue(UnableToRead); return dummy; }
    __builtin_uint_t * wordloc=aligned(unaligned,lshbits);
    return *wordloc; } /* A․𝘬․a `deref` and `alignedword`. */
  
#pragma mark - The overt simplification
  
  uint8_t& operator[](__builtin_int_t idx) { Delegate * d = delegate; 
    auto issue = ^(int nº) { if (d) d->issue(this,nº); };
    if (idx >= bytes || idx < 0) { issue(UnableToAccess); }
    uint8_t * /* byteaddress */ loc=idx+base; /* return *loc; */
    short lshbits; __builtin_uint_t& y=word(loc,lshbits,issue);
    return *(lshbits + (uint8_t *)(__builtin_uint_t *)&y);
  } /* Retrieve disjunct/sediment/segments. */
  
#pragma mark - Nitty-gritty and the details
  
  enum Sentinel { cyclic, last }; /* Does not define `keep𝟷ᵈ`/`⁸𝟷ᵈ` also for idx < 0. */
  
  __builtin_int_t byteoffset😐⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, 
      Sentinel wrap, __builtin_int_t totbytes) { __builtin_int_t relative=0; 
    if (byteNº < 0 || 𝛥bytes < 0 || totbytes <= 0) { return -1; }
    switch (wrap) { case cyclic: relative = 𝛥bytes % totbytes; break; case last: 
      relative = (𝛥bytes <= totbytes) ? 𝛥bytes : (totbytes - 1); break; }
    __builtin_int_t offset = relative + byteNº;
    if (offset >= totbytes) { return -1; }
    return offset;
  }
  
  enum Width { 𝟾, 𝟷𝟼, 𝟹𝟸, 𝟼𝟺, lo𝟼𝟺, hi𝟼𝟺, lo𝟷𝟸𝟾, hi𝟷𝟸𝟾 };
  
  int keep(uint8_t * /* byteaddress */ unaligned, __builtin_uint_t word) const {
    /* virtuaddr vaddr=loc.pointer; int ᵇoffset=vaddr&0xfff; int long idxᵖᵗ=vaddr>>12; */
    if (unaligned < base || unaligned >= base + bytes) { return -1; }
    short dummybits; __builtin_uint_t * wordloc=aligned(unaligned,dummybits);
    *wordloc=word;
    return 0;
  }
  
  uint8_t * /* byteaddress */ relative(__builtin_int_t addend) { return base + addend; }
  
  uint8_t ⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, Sentinel wrap, __builtin_int_t 
     totbytes, void (^keep)(uint8_t &shifted) = ^(uint8_t &) { }
  )
  {  Delegate * d = delegate; static uint8_t dummy=0; 
    __builtin_int_t toadd=byteoffset😐⁸𝟷ᵈ(byteNº,𝛥bytes,wrap,totbytes);
    auto issue = ^(int nº) { if (d) d->issue(this,nº); };
    if (toadd < 0) { issue(UnableToAccess); } /* *byteloc=byte; Or: */
    uint8_t * /* byteaddress */ unaligned=relative(toadd);
    short lshbits; __builtin_uint_t& original=word(unaligned,lshbits,issue);
    auto byteExtract = ^(__builtin_uint_t w, short lshbits) /* -> uint8_t * */ { 
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
    short lshbits; __builtin_uint_t word₁=interval₁.word(wloc,lshbits,ʳᵈissue);
    printf("word₁ is %llx\n", word₁);
    
    /* Detailed-interface case: */
    __builtin_int_t byteNº=8, 𝛥bytes=8, totbytes=100;
    uint8_t old₁ = interval₁.⁸𝟷ᵈ(byteNº, 𝛥bytes, Intervallic::last, totbytes, 
      ^(uint8_t &shifted) { shifted=0xca; });
    uint8_t old₂ = interval₁.⁸𝟷ᵈ(byteNº, 𝛥bytes, Intervallic::last, totbytes);
    printf("Old₁/old₂ is %x/%x\n", old₁, old₂);
    
    /* ...and when using indexing: */
    uint8_t y₁=interval₁[5];
    interval₁[5]=0xcc;
    uint8_t y₂=interval₁[5];
    printf("y₁/y₂ is %x/%x\n", (int)y₁, (int)y₂);
    
    return 0;
}


