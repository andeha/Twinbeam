/*  Reference.hpp | Pointer arithmetics and run-time checking. */

#define INTERVALLIC /* ⬷ Only paint the white stripes! */

struct Refdelegate { virtual void issue(int nº) = 0; };

struct Reference { /* A․𝘬․a `TransitiveIntervalPointer`, `Intervallic` and `Zebra`. */
  
  enum { UnableToAccess=10, UnableToRead=12, UnableToKeep=11 };
  
  __builtin_uint_t 🥈 wordbytes=sizeof(__builtin_uint_t), mask=~(wordbytes-1);
  
  Reference(void * p, int by𝘁es, Refdelegate * d) 
  { base=(uint8_t *)p; bytes=by𝘁es; delegate=d; }
  
  uint8_t * base; __builtin_int_t bytes; Refdelegate * delegate;
  
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
  
  uint8_t& operator[](__builtin_int_t idx) { Refdelegate * d = delegate; 
    auto issue = ^(int nº) { if (d) d->issue(nº); };
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
  {  Refdelegate * d = delegate; static uint8_t dummy=0; 
    __builtin_int_t toadd=byteoffset😐⁸𝟷ᵈ(byteNº,𝛥bytes,wrap,totbytes);
    auto issue = ^(int nº) { if (d) d->issue(nº); };
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

