/*  unstall-coalesc.c | mandatory-required and non-specific. (DO-NOT-CIRCULATE) */

#include "twinbeam-inner.h"

__builtin_int_t least₋possible₋residue(
  __builtin_int_t dividend, __builtin_int_t divisor)
{
   __builtin_int_t y = dividend % divisor;
   return y < 0 ? y + divisor : y;
} /*  patch to the '%' operator in a C language undefined case. */

#pragma recto still chronology and sequential

void init₋monoton(struct Act * ❶, __builtin_int_t oldest) { ❶->memory=oldest; }

__builtin_int_t monoton₋ordinal(int * wrapped, struct Act * ❶) {
   __builtin_int_t Ɀ=❶->memory;
   if (Ɀ == BUILTIN₋INT₋MAX) { ❶->memory=0; *wrapped=true; }
   else { *wrapped=false; } ❶->memory += 1; return Ɀ;
}

void
Base𝕟( /* TeX §64, §65 and §67. */
  __builtin_uint_t ℕ,
  unsigned short base,
  unsigned short digitsOr0, /* ⬷ not more than 32 or 64 digits depending on 
    your machines' word size! (Or set to `0` to skip leading zeros.) */
  void (^output)(char digits)
) ⓣ
{
    typedef void (^Impression)(unsigned short r, void (^out)(char));
    Impression 𝟬to𝗙 = ^(unsigned short r, void (^out)(char u8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0 }; short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k+=1; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k=k-1) { 𝟬to𝗙(cycle[k], 
      output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k=k-1; }
       for (; k >= 0; k=k-1) { 𝟬to𝗙(cycle[k], output); }
    }
} /*   note 128-bit duplicate in --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp>. */

void
Base𝕫(
  __builtin_int_t ℤ,
  unsigned short base,
  unsigned short digitsOr0,
  void (^output)(char digitsAndMinus)
) ⓣ
{
   if (ℤ < 0) { output('-'); ℤ = -ℤ; }
   Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, output);
}

#if defined usage₋𝟷𝟸𝟾₋bit₋integer

void
Base𝕟(
  __uint128_t ℕ, 
  unsigned short base, 
  unsigned short digitsOr0, 
  void (^out)(char digits)
) ⓣ
{
    typedef void (^Impression)(unsigned short, void (^out)(char));
    Impression Fand0 = ^(unsigned short r, void (^out)(char u8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[128] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k+=1; } while (ℕ);
    /* if (fractions(uint64_t num, 𝟷𝟶, uint64_t &ℕ, uint64_t &modula)) { return 0; } */
    if (digitsOr0) { for (k=digitsOr0-1; k>=0; k=k-1) { 
      Fand0(cycle[k], out); } }
    else { k=127; while (cycle[k]==0 && k>0) { k=k-1; }
      for (; k>=0; k=k-1) { Fand0(cycle[k], out); }
    }
} /*  requires 128-bits-`fractions`, { `__umodti3`, `__udivti3` }, `__udivmodti4`. */

void Base𝕫(__int128_t ℤ, 
  unsigned short base, unsigned short digitsOr0, 
  void (^out)(char digitsAndMinus)
) ⓣ
{
  if (ℤ < +0) { out('-'); ℤ = -ℤ; }
  Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, out);
}

#endif

void *
ExactSeek₂(
  const void * key, 
  const void * base, 
  size_t num, size_t size, 
  int (^cmp)(const void * key, const void * elt)
)
{ uint8_t * pivot; int y;
   while (num > 0) { pivot = (uint8_t *)base + (num>>1) * size;
     y = cmp(key,pivot);
     if (y == 0) return (void *)pivot;
     if (y > 0) { base = pivot+size; num=num-1; }
     num >>= 1;
   }
   return ΨΛΩ;
} /*  todo: add to Pinecone implementation and switch to interpolation search
 (that is log log instead of log that according to Knuth delivers somewhere 
 around N > 64K). */

void Stillsort(int count, uint8_t * material, int bytesitem, 
 void (*cmp)(uint8_t * p₁, uint8_t p₂))
{
   
} /* sorting after comparision on /three/. */

void Identity₋Tb(char ** text)
{
  *text=SHA1GIT;
}

int
IsPrefixOrEqual(
  const char * 𝟽alt𝟾₋bitstring, /*  possibly 'normalizedUtf8' */
  const char * 𝟽alt𝟾₋bitprefix  /*  smiley appears when 'prompt> nm'! */
) /*  consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
{  const char *s=𝟽alt𝟾₋bitstring, *p=𝟽alt𝟾₋bitprefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters 'string' and 'prefix' are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in 'prefix' equal to 'string'. Return first character following 'eightbitPrefix'. */
    /* *p != 0 && *s != 0 */
    char diff = *s - *p;
    if (diff) { return 0; } /* Savannah and Samura. */
    s++, p++;
    goto again;
}

ByteAlignedRef
Clear8Memory(
  ByteAlignedRef mem, 
  __builtin_int_t bytes
) /*  a․𝘬․a `bzero`. */
{
   if (!bytes) { return mem; }
   return Overwrite8Memory(mem, 0, bytes);
} /*  a․𝘬․a 'clear₋page'. */

ByteAlignedRef
Copy8Memory(
  ByteAlignedRef dst, 
  ByteAlignedRef src, 
  __builtin_int_t bytes
) /*  a․𝘬․a 'memcpy'. */
{
   char * d = (char *)dst;
   char * s = (char *)src;
   while (bytes--) *d++ = *s++;
   return dst;
} /* cf․ copying using an asychronous dma a․𝘬․a OptimisticAsync8Copy. */

ByteAlignedRef
Overwrite8Memory(
  ByteAlignedRef src,
  uint8_t val,
  __builtin_int_t bytes
) /*  a․𝘬․a `memset`. */
{
   uint8_t *s = (uint8_t *)src;
again:
   while (bytes == 0) goto unagain;
   *s = val; s+=1; bytes=bytes-1; goto again;
unagain:
   return src;
}

/* µA("x86_64", "haswell", x₁, x₂)
µA("mips", "r2", x₃, x₄) */
FOCAL
int
Compare8Memory(
  ByteAlignedRef l,
  ByteAlignedRef r,
  __builtin_int_t bytes
) /*  a․𝘬․a 'memcmp'. */
{
   const unsigned char *p₁=l, *p₂=r;
   while (bytes--) {
     if (*p₁ != *p₂) return *p₁ - *p₂;
     else p₁++,p₂++;
   }
   return 0;
} /*  notice that this method is 'too cristalline' when dealing with 
 Unicodes but not with 7-bit text. */

