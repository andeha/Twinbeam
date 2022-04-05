/*  unstall-system.c | mandatory-required and non-specific. (DO-NOT-CIRCULATE) */

import Twinbeam;

__builtin_int_t least₋possible₋residue(
  __builtin_int_t dividend, __builtin_int_t divisor)
{
   __builtin_int_t y = dividend % divisor;
   return y < 0 ? y + divisor : y;
} /* ⬷ patch to the '%' operator in a C language undefined case. */

#pragma header still chronology and sequential

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
)
{
    auto 𝟬to𝗙 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0 }; short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k+=1; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 𝟬to𝗙(cycle[k], 
      output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k--; }
       for (; k >= 0; k--) { 𝟬to𝗙(cycle[k], output); }
    }
} /*  ⬷ note 128-bit duplicate in --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp>. */

void
Base𝕫(
  __builtin_int_t ℤ,
  unsigned short base,
  unsigned short digitsOr0,
  void (^output)(char digitsAndMinus)
)
{
   if (ℤ < 0) { output('-'); ℤ = -ℤ; }
   Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, output);
}

#ifdef 𝟷𝟸𝟾₋bit₋integers

void
Base𝕟(
  __uint128_t ℕ, 
  unsigned short base, 
  unsigned short digitsOr0, 
  void (^out)(char digits)
)
{
    auto 𝟶to𝖥 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
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
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 
      𝟶to𝖥(cycle[k], out); } }
    else { k = 127; while (cycle[k] == 0 && k > 0) { k--; }
      for (; k >= 0; k--) { 𝟶to𝖥(cycle[k], out); }
    }
} /* ⬷ requires 128-bits-`fractions`, { `__umodti3`, `__udivti3` }, `__udivmodti4`. */

void Base𝕫(__int128_t ℤ, 
  unsigned short base, unsigned short digitsOr0, 
  void (^out)(char digitsAndMinus)
)
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
     if (y > 0) { base = pivot+size; num-=1; }
     num >>= 1;
   }
   return NULL;
} /* ⬷ todo: add to Pinecone implementation and switch to interpolation search
 (that is log log instead of log that according to Knuth delivers somewhere 
 around N > 64K). */

int
IsPrefixOrEqual(
  const char * 𝟽alt𝟾₋bitstring, /* ⬷ possibly 'normalizedUtf8' */
  const char * 𝟽alt𝟾₋bitprefix  /* ⬷ smiley appears when 'prompt> nm'! */
) /* ⬷ consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
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
Overwrite8Memory(
  ByteAlignedRef src,
  uint8_t val,
  __builtin_int_t bytes
) /* ⬷ a․𝘬․a `memset`. */
{
    uint8_t *s = (uint8_t *)src;
again:
    while (bytes == 0) goto unagain;
    *s = val; s++; bytes--; goto again;
unagain:
    return src;
}

ByteAlignedRef
Clear8Memory(
  ByteAlignedRef mem, 
  __builtin_int_t bytes
) /* ⬷ a․𝘬․a `bzero`. */
{
    if (!bytes) { return mem; }
#if defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
    return Overwrite8Memory(mem, 0, bytes);
#elif defined __x86_64__
    asm("rep stosl;"::"a"(0),"D"((size_t)mem),"c"(bytes / 4));
    asm("rep stosb;"::"a"(0),"D"(((size_t)mem) + ((bytes / 4) * 4)),"c"(bytes - ((bytes / 4) * 4)));
    return mem;
#endif
} /* ⬷ a․𝘬․a 'clear₋page'. */

/* µA("x86_64", "haswell", x₁, x₂)
µA("mips", "r2", x₃, x₄) */
FOCAL
int
Compare8Memory(
  ByteAlignedRef l,
  ByteAlignedRef r,
  __builtin_uint_t bytes
) /* ⬷ a․𝘬․a 'memcmp'. */
{
    const unsigned char *p₁ = l, *p₂ = r;
    while (bytes--) {
      if (*p₁ != *p₂) return *p₁ - *p₂;
      else p₁++,p₂++;
    }
    return 0;
} /* ⬷ notice that this method is 'too cristalline' when dealing with Unicodes. */

#pragma header - time intervals

short₋chronology₋relative
duration(
  chronology₋instant t₁, chronology₋instant t₂
)
{ union stomp₋ntp { uint64_t bits; struct { uint32_t seconds; chronology₋UQ32 frac; } } since; };
   stomp₋ntp s₁ { .since = { t₁.l, t₁.h } }, s₂ { .since = { t₂.l, t₂.h } };
   
   typedef int (^Lessthan)(stomp₋ntp, stomp₋ntp);
   Lessthan lt = ^(stomp₋ntp t₁, stomp₋ntp t₂) {
    if (t₁.since.seconds == t₂.since.seconds) { return t₁.since.frac < t₂.since.frac; }
    return t₁.since.seconds < t₂.since.seconds;
   };
   
   if (lt(s₂,s₁)) { stomp₋ntp storage=s₁,s₁=s₂,s₂=storage; }
   
   int32_t frac, seconds; int unit₋deduct; short₋chronology₋relative z;
   if (s₁.since.frac > s₂.since.frac) { unit₋deduct=1; frac=s₁.since.frac - s₂.since.frac; }
   else { frac=s₂.since.frac-s₁.since.frac; unit₋deduct=0; }
   seconds = s₂.since.seconds - s₁.since.seconds - (unit₋deduct ? 1 : 0);
   z = { .frac= (frac | (seconds<<15)) };
   return z;
} /* ⬷ with an irreversive differential: t₂ - t₁ alt․ t₁ - t₂. */

#pragma header - miscellaneous initialization functions

void InitFpu()
{
#if defined __x86_64__
   asm {
     finit
   }
#endif
}

#pragma header - analysis: post-mortem and single-stepping

#if defined __x86_64__

void Sheriff(void)
{
#if defined  __x86_64__
   Intel👈
     int 3
   }
#elif defined __armv8a__
   __builtin_debug();
#endif
}

#endif

