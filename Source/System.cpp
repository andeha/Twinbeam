/*  System.cpp | Mandatory-required and non-specific. (DO-NOT-CIRCULATE) */

#include <Twinbeam.h>

struct TwinbeamContext {
  jmp_buf2 /* volatile */ singleTaskProgramState;
  Chronology calendricChronology, computationalChronology;
} __twinbeamContext;

extern "C"
DISORDERABLE /* Overridden when linked together with 𝘦․𝘨 `SlimScheduler.o`. */
jmp_buf2 * /* volatile */
JmpBuf() { return &(__twinbeamContext.singleTaskProgramState); }

#pragma mark - See --<🥽 ¹𝙁𝘿𝙄𝙑.cpp> for 64-bits and 32-bits 𝗳𝗹𝗼𝗮𝘁𝗶𝗻𝗴-𝗽𝗼𝗶𝗻𝘁 division

FOCAL
int
fractions(
  uint32_t num, uint32_t denom, /* ⬷ a․𝘬․a `dividend` and `divisor`. */
  uint32_t &ℕ, uint32_t &modula /* ⬷ Sometimes called 'quotient` and `remainder`. */
)
{ ℕ=0;
   if (denom == 0) { return -1; }
   while (num >= denom) { ℕ++; num -= denom; }
   modula = num;
   return 0;
#ifdef WHEN_IDIV_ROUNDS_TOWARDS_NINF /* Suitable for a UDIV and UMUL  ⃫ HW architecture ⤐ */
   if (denom == 0) { return -1; }
   if (denom >= num) { ℕ=0; modula=num; }
   ℕ = num/denom; 
   /* Given the integer division did 'rounds towards -∞' a․𝘬․a 'a floored division': */
   modula = num - denom * ℕ;
   return 0;
#endif /* ⬷ `divmod`: 'Simultaneous division and multiplication in HW'. */
} /* 
 
 Om mips, when multu, mfhi access the upper part and mflo the lower part.
 On mips, when divu, mfhi holds the remainder and mflo the quotient.
 
 In C and for 'signed fractions' when either num` or `denom` is negative, the 
 result after '%' is implementation-dependent. The `LeastPossibleResidue` gives 
 a well-defined result.

 The Pascal/Algol68 always gives a positive 'modula' when performing 'mod' on 
 an sign-alternating `num` and denom`. The signed version of 'div' rounds 
 towards -∞ or zero.
 
 Below, the signed `fractions₁` and `fractions₂` gives `modula` that is equal 
 to `LeastPossibleResidue` when Euclidean division is selected. The sign 
 is returned separately in `sum₋negative`.
 
 */

inexorable int fractions₁(
  int32_t num, int32_t denom, int32_t &ℤ, int32_t &modula, bool &sum₋negative
) {
   uint32_t numᵢ=(uint32_t)abs32i(num),denomᵢ=(uint32_t)abs32i(denom),ℕ,modulaᵢ;
   if (fractions(numᵢ,denomᵢ,ℕ,modulaᵢ)) { return -1; }
   ℤ=int32_t(ℕ), modula=int32_t(modulaᵢ);
   bool negn=num<+0, negd=denom<+0;
   sum₋negative = negn ^ negd;
   return 0;
}

#ifdef __mips__
inexorable int mips-fractions(
  uint32_t num, uint32_t denom, uint32_t &ℕ, uint32_t &modula
) {
    if (denom == 0) { return -1; }
    Mips
 "    divu $4, $5            \n"      /* Division: divu a0, a1. */
/*    nop, nop in MIPS I to MIPS III. */
 "    mfhi $8                \n"      /* Retrieve modulo: mfhi t0. */
 "    mflo $9                \n"      /* Retrieve quotient: mflo t1. */
 "    sw $9, 0($6)           \n"      /* Write through pointer: sw $t1, 0($6). */
 "    sw $8, 0($7)           \n"      /* Write through pointer: sw $t0, 0($7). */
    );
    return 0;
} /* Removed according to 'The MIPS32® Instruction Set Manual, Revision 6.06'. */
#endif

inexorable void invert(int32_t & x) { x = ~x; } /* a․𝘬․a `toggle₋all`. */
inexorable void increment₁(int32_t & x) { ++x; } /* a․𝘬․a `möbius-at-intmax`. */
inexorable int 𝟸₋compl(int32_t & x) { invert(x); increment₁(x); }

inexorable int
fractions₂(
  int32_t num, int32_t denom, 
  int32_t &ℤ, int32_t &modula, 
  int * sum₋negative
)
{ /* Beware of 0b10000...01: */
   /* int32_t 🥈 intmax = 0b01111111111111111111111111111111; */
   int32_t 🥈 intmin = 0b10000000000000000000000000000001;
   if (num==intmin || denom==intmin) { return -1; }
   int32_t d=denom,n=num;
   int negd=(d&SIGNBIT_INT32), negn=(n&SIGNBIT_INT32);
   if (negd) { 𝟸₋compl(d); } /* Alt. return x < 0 ? 𝟸₋compl(x) : x; */
   if (negn) { 𝟸₋compl(n); } /* Alt. x < 0 ? -x : x; */
   /* Alt. return x <= -0.0 ? -x : x; */
   uint32_t numᵢ=uint32_t(n),denomᵢ=uint32_t(d),ℕ,modulaᵢ;
   if (fractions(numᵢ,denomᵢ,ℕ,modulaᵢ)) { return -2; }
   ℤ=int32_t(ℕᵢ); modula=int32_t(modulaᵢ);
   *sum₋negative = negn ^ negd;
   return 0;
}

FOCAL int fractions(int32_t num, int32_t denom, int32_t &ℤ, int32_t &modula, 
int * sum₋negative) { return fractions₂(num,denom,ℤ,modula,sum₋negative); }

int
fractions(
  uint64_t num, uint64_t denom,
  uint64_t &ℕ, uint64_t &modula
)
{ ℕ=0;
   if (denom == 0) { return -1; }
   while (num >= denom) { ℕ++; num -= denom; }
   modula = num;
   return 0;
}

int
fractions(
  __uint128_t num, __uint128_t denom, 
  __uint128_t &ℕ, __uint128_t &modula)
{ ℕ=0;
   if (denom == 0) { return -1; }
   while (num >= denom) { ℕ++; num -= denom; }
   modula = num;
   return 0;
} /* a․𝘬․a (in llvm): '__udivmodti4' with friends. */

/*  Requires: if (!IsOdd(x)) { x >>= 1; } */

#pragma mark - …and one more signed counterparts a․𝘬․a `IDIV` for 64-bits:

FOCAL int fractions(int64_t num, int64_t denom, int64_t &ℤ, int64_t &modula, bool &sum₋negative)
{
   uint64_t numᵢ=(uint64_t)abs64i(num),denomᵢ=(uint64_t)abs64i(denom),ℕ,modulaᵢ;
   if (fractions(numᵢ,denomᵢ,ℕ,modulaᵢ)) { return -1; }
   ℤ=int64_t(ℕ), modula=int64_t(modulaᵢ);
   int negn=num<+0, negd=denom<+0;
   sum₋negative= negn ^ negd;
   return 0;
}

/*  Not required... ⤐ 
  
  FOCAL int fractions(__builtin_int_t num, __builtin_int_t denom, __builtin_int_t &ℤ, 
    __builtin_int_t &modula, bool &sum₋negative)
  
  and
  
  FOCAL int fractions(int num, int denom, int &ℤ, int &modula, bool &sum₋negative)
  
  ⬷ ...type is inferred. */

#pragma mark - Octa ⟷ 8×8 bit matrix (for 'extern' declarations in examples)

unionᵢ Individual { uint64_t le; uint8_t radio[8]; };

uint64_t MXOR(uint64_t X, uint64_t 👈)
{  Individual x { .le=X }, sel { .le=👈 }, y { .le=0 };
    for (__builtin_int_t i=0; i<8; ++i) { for (__builtin_int_t j=0; j<8; ++j) { 
      if (sel.radio[i]) { y.radio[j] ^= x.radio[i]; } } }
    return y.le;
} /* a․𝘬․a 'multiple-xor'. The 👈 selects bytes in X that are xor-ed together. */

uint64_t MOR(uint64_t X, uint64_t 👈)
{  Individual x { .le=X }, sel { .le=👈 }, y { .le=0 };
    for (__builtin_int_t i=0; i<8; ++i) { for (__builtin_int_t j=0; j<8; ++j) { 
      if (sel.radio[i]) { y.radio[j] |= x.radio[i]; } } }
    return y.le;
} /* a․𝘬․a 'multiple-or'. The 👈 selects bytes in X that are or-ed together. */

/*  For example 8 ascii to 8 unicodes, cyclically/arithmetically/logically shift a 
 register. See MMIX 1.3.1 for additional use-cases such as addition and reflection. */

#pragma mark - Circular reasoning

__builtin_int_t LeastPossibleResidue(
  __builtin_int_t dividend, __builtin_int_t divisor)
{
    __builtin_int_t y = dividend % divisor;
    return y < 0 ? y + divisor : y;
} /* ⬷ Patches undefined '%' operator. */

#pragma mark - Utility functions

void
Base𝕟( /* TeX §64, §65 and §67. */
  __builtin_uint_t ℕ,
  unsigned short base,
  unsigned short digitsOr0, /* Not more than 32 or 64 digits depending on 
    your machines' word size! (Or set to `0` to skip leading zeros.) */
  void (^output)(char 𝟶to𝟿)
)
{
    auto 𝟶to𝙵 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0 }; short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 𝟶to𝙵(cycle[k], 
      output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k--; }
       for (; k >= 0; k--) { 𝟶to𝙵(cycle[k], output); }
    }
} /* See duplicate in --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp> for improved details. */

void
Base𝕫(
  __builtin_int_t ℤ,
  unsigned short base,
  unsigned short digitsOr0,
  void (^output)(char 𝟶to𝟿and₋)
)
{
    if (ℤ < 0) { output('-'); ℤ = -ℤ; }
    Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, output);
}

int
#ifdef __x86_64__
__attribute__((target("rtm")))
#endif
OptimisticSwap(
  __builtin_int_t /* volatile */ * p₁,
  __builtin_int_t /* volatile */ * p₂,
  Impediment it
)
{
#ifdef __x86_64__
    int y=-1; unsigned status = _xbegin();
    if (status == _XBEGIN_STARTED) {
        if (it != MustBeOrdered) { __atomic_exchange(p₁, p₂, p₂, __ATOMIC_SEQ_CST); }
        if (it == MustBeOrdered && (*p₁ > *p₂)) { _xabort(0xff); }
        y = 0;
        *p₁ = *p₁ ^ *p₂;
        *p₂ = *p₁ ^ *p₂;
        *p₁ = *p₁ ^ *p₂;
        _xend(); /* Also, reconsider the swapping above using a temporary storage location again. */
    } else { _xabort(0xfe); }
    return y;
#elif defined __mips__
    static __builtin_int_t maynotlock=0;
    if (__sync_bool_compare_and_swap(&maynotlock, 0, 1)) {
        /* Core-exclusive: */
        if (it != MustBeOrdered) { __atomic_exchange(p₁, p₂, p₂, __ATOMIC_SEQ_CST); }
        else { if (*p₁ <= *p₂) __atomic_exchange(p₁, p₂, p₂, __ATOMIC_SEQ_CST); }
        /* Leaving critical-section */
        __sync_lock_release(&maynotlock);
        return 0;
    } else { return -1; }
#endif
}

__builtin_int_t
ByteoffsetMips𝟷ᵈ(
  __builtin_int_t byteNº, __builtin_int_t 𝛥mips, 
  Sentinel wrap, __builtin_int_t totmips
)
{ __builtin_int_t relative=0;
  if (byteNº < 0 || 𝛥mips < 0 || totmips <= 0) { return -1; } switch (wrap) {
  case Sentinel::cyclic: relative = 𝛥mips % totmips; break;
  case Sentinel::last: relative = (𝛥mips <= totmips) ? 𝛥mips : 
    (totmips - 1); break;
  case Sentinel::crash: relative = 𝛥mips; if (relative + byteNº >= 
    totmips<<2) { /* ⭐️ */ Sheriff(); } break;
  case Sentinel::bound: relative = 𝛥mips; if (relative + byteNº >= 
    totmips<<2) { return -1; } break;
  }
  __builtin_int_t offset = (relative<<2) + byteNº;
  if (offset >= (totmips<<2)) { return -1; }
  return offset;
}

__builtin_int_t
Byteoffset⁸𝟷ᵈ(
  __builtin_int_t byteNº, __builtin_int_t 𝛥bytes, 
  Sentinel wrap, __builtin_int_t totbytes
)
{ __builtin_int_t relative=0;
  if (byteNº < 0 || 𝛥bytes < 0 || totbytes <= 0) { return -1; } switch (wrap) {
  case Sentinel::cyclic: relative = 𝛥bytes % totbytes; break;
  case Sentinel::last: relative = (𝛥bytes <= totbytes) ? 𝛥bytes : 
    (totbytes - 1); break;
  case Sentinel::crash: relative = 𝛥bytes; if (relative + byteNº >= 
    totbytes) { /* ⭐️ */ Sheriff(); } break;
  case Sentinel::bound: relative = 𝛥bytes; if (relative + byteNº >= 
    totbytes) { return -1; } break;
  }
  __builtin_int_t offset = relative + byteNº;
  if (offset >= totbytes) { return -1; }
  return offset;
}

void *
ExactSeek₂(
  const void * key, 
  const void * base, 
  size_t num, size_t size, 
  int (^cmp)(const void * key, const void * elt)
)
{ uint8_t * pivot; int y;
   while (num > 0) { pivot = (uint8_t *)base + (num>>1) * size;
     y = cmp(Critic(key),pivot);
     if (y == 0) return (void *)pivot;
     if (y > 0) { base = pivot+size; num--; }
     num >>= 1;
   }
   return NULL;
} /* TODO: Add to Pinecone implementation and switch to interpolation search
 (that is log log instead of log that according to Knuth delivers somewhere 
 around N > 64K). */

int
IsPrefixOrEqual(
  const char * 𝟽alt𝟾₋bitstring, /* Possibly `normalizedUtf8` */
  const char * 𝟽alt𝟾₋bitprefix  /* Smiley appears when `prompt> nm`! */
) /* Consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
{  const char *s=𝟽alt𝟾₋bitstring, *p=𝟽alt𝟾₋bitprefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in `prefix` equal to `string`. Return first character following `eightbitPrefix`. */
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
) /* A․𝘬․a `memset`. */
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
) /* A․𝘬․a `bzero`. */
{
    if (!bytes) { return mem; }
#ifdef  __mips__
    return Overwrite8Memory(mem, 0, bytes);
#elif defined __x86_64__
    asm("rep stosl;"::"a"(0),"D"((size_t)mem),"c"(bytes / 4));
    asm("rep stosb;"::"a"(0),"D"(((size_t)mem) + ((bytes / 4) * 4)),"c"(bytes - ((bytes / 4) * 4)));
    return mem;
#endif
}

#pragma mark - Mortem analysis and set-up

extern "C" void ASSEMBLERONLY Sheriff()
{
#ifdef __mips__ // Snapshot and reference using `DeSAVE`.
    Mips
 "    sdbbp 13    \n" /* Enters debug mode (CP0 DM will be set) 0xBFC0_0480. */
    );
#elif defined  __x86_64_
   Intel👈
     int 3
   } /* Unavailable: __builtin_trap(), raise(SIGTRAP), __builtin_debugtrap() */
#endif
} /*  For details peek on --<pic32rt>--<Control.cpp>. */

Chronology& ComputationalChronology() { return 
  __twinbeamContext.computationalChronology; }

Chronology& SystemCalendricChronology() { return 
  __twinbeamContext.calendricChronology; }

void ResetSetLongjmp() 
{ Clear8Memory((ByteAlignedRef)JmpBuf(), sizeof(jmp_buf2)); }


