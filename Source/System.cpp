/*  System.cpp | mandatory-required and non-specific. (DO-NOT-CIRCULATE) */

#include <Twinbeam.h>

extern jmp_buf2 /* volatile */ singleTaskProgramState;
extern Chronology calendricChronology, computationalChronology;
extern "C" DISORDERABLE /* ⬷ overridden when linked together with 𝘦․𝘨 `SlimScheduler.o`. */
jmp_buf2 * /* volatile */ JmpBuf() { return &(singleTaskProgramState); }

FOCAL int IADD(short id, int32_t addend, int32_t augend, 
  int32_t &ℕ₋hi, uint32_t &ℕ₋lo, int * sum₋negative
)
{
   extern uint32_t __ℕ₋🅻[4], __ℕ₋🅷[4];
   return 0;
}

FOCAL int Fused₋IMUL(short id, int32_t augend, int32_t multiplier, 
 int invMultiplyThenAdd, int32_t &ℕ₋hi, uint32_t &ℕ₋lo, int * accumulator₋negative
)
{
   extern uint32_t __ℕ₋🅻[4], __ℕ₋🅷[4];
   if (invMultiplyThenAdd) { return -1; }
   return 0;
} /* ⬷ a․𝘬․a 'linear-combine'. */

#pragma mark - F-old-err/f-i-le, m-a-p and gr-o-u-p/in-di-vid-u-all

FOCAL
int
Acquire𝟷ᵈ(
  __builtin_int_t ﹟, /* ⬷ a․𝘬․a '#shatters', '﹟skeletons' and '﹟turnstiles'. */
  __builtin_int_t 𝑙𝑜𝑔₂Pages, 
  __builtin_uint_t pages[], __builtin_uint_t avails[], 
  void (^every)(uint8_t * 𝟸ⁿ₋frame, bool& stop)
) /* ⬷ given a transactional memory, reconsider acquire with and without rollback. */
{  __builtin_int_t 🥈 BytesPerWord=sizeof(__builtin_uint_t), Bits=BytesPerWord<<3;
   __builtin_int_t Pages=0b1<<𝑙𝑜𝑔₂Pages, Idxs=(Pages/BytesPerWord)>>3;
     if (﹟ <= 0) { return -1; } bool stop=false;
     for (int i=0; i<Idxs; i++) {
again:
       __builtin_int_t occupied = ~avails[i];
       if (occupied == TriboolUnknown) { continue; }
#if defined __mips__ || defined __armv6__ || defined espressif
       __builtin_int_t onesUntilZero = __builtin_ctz(~occupied);
#elif defined __x86_64__ || defined __armv8a__
       __builtin_int_t onesUntilZero = __builtin_ctzll(~occupied);
#endif
       avails[i] ^= 1<<onesUntilZero; /* ⬷ see also note at --<Additions.h>{Bitsetˢᵘᵖ}. */
       __builtin_int_t byteOffset = Syspagesize()*(Bits*i + onesUntilZero);
       every((uint8_t *)pages+byteOffset, stop);
       if (stop) { return -3; }
       if (--﹟ == 0) { return 0; } else { goto again; }
    }
    return -2;
} /* ⬷ similar to `new` and `malloc` but returns multiple same-sized and non-
  consecutive memory areas. */

FOCAL
int
Release𝟷ᵈ(
  void * 𝟸ⁿ₋frame, 
  __builtin_int_t 𝑙𝑜𝑔₂Pages, 
  __builtin_uint_t pages[], __builtin_uint_t avails[], 
  bool secure
)
{  __builtin_int_t 🥈 BytesPerWord=sizeof(__builtin_uint_t);
    __builtin_int_t Pages=0b1<<𝑙𝑜𝑔₂Pages, Idxs=(Pages/BytesPerWord)>>3, 
    ᵇoffset = 1 + (uint8_t *)(𝟸ⁿ₋frame)-(uint8_t *)pages, 
       ᵚidx = (__builtin_int_t)Frame(ᵇoffset,8*BytesPerWord) - 1, 
       bitᵚ = ᵇoffset - ᵚidx*BytesPerWord;
    __builtin_uint_t toggle = 0b1<<bitᵚ;
    /* *** 🎿-begin *** */
    if (avails[ᵚidx] & toggle) { return -2; }
    avails[ᵚidx] ^= toggle;
    /* *** 🎿-end *** */
    if (secure) { Overwrite8Memory((ByteAlignedRef)𝟸ⁿ₋frame, 0x0, Syspagesize()); }
    return 0; /* See also --<Virtual.cxx>{Forget} for a frame-granular overwrite method. */
} /* ⬷ similar to 'Fallow' and 'free' but assumes same-sized areas. */

#pragma mark - Therapeutic grip for one realization:

extern void Reservoir(unsigned expeditionary, __builtin_int_t *𝑙𝑜𝑔₂Pages, __builtin_int_t *Idxs, 
  __builtin_uint_t **pages, __builtin_uint_t **avails); /* ⬷ a․𝘬․a 'Universe' and defined in --<llvm-rt3.cpp>. */

int CoalescingAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{
    __builtin_int_t 𝑙𝑜𝑔₂Pages, Idxs; __builtin_uint_t *pages, *avails;
    Reservoir(expeditionary,&𝑙𝑜𝑔₂Pages,&Idxs,&pages,&avails); /* *** 🎿-start *** */
    auto rollback = ^(__builtin_int_t count, void * frames[], __builtin_int_t 𝑙𝑜𝑔₂Pages, 
      __builtin_uint_t pages[], __builtin_uint_t avails[]) /* -> int */ { 
      for (__builtin_int_t i=0; i<count; i++) { if (Release𝟷ᵈ(frames[i], 𝑙𝑜𝑔₂Pages, 
        pages, avails, false)) { return -1; } } return 0; };
    __builtin_uint_t * frms = (__builtin_uint_t *)𝟺kbframes; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __builtin_int_t brk=0;
    if (Acquire𝟷ᵈ(﹟, 𝑙𝑜𝑔₂Pages, pages, avails, ^(uint8_t * frm, bool& stop) { 
      *(frms + brk++) = (__builtin_uint_t)frm;
    })) { if (rollback(brk,𝟺kbframes,𝑙𝑜𝑔₂Pages,pages,avails)) { return -2; } return -1; }
    /* *** 🎿-end *** */ return 0;
} /* ⬷ a․𝘬․a 'Coalesce'. */

int 🄕allo⒲(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{
    __builtin_int_t 𝑙𝑜𝑔₂Pages, Idxs; __builtin_uint_t *pages, *avails;
    Reservoir(expeditionary,&𝑙𝑜𝑔₂Pages,&Idxs,&pages,&avails);
    for (__builtin_int_t i=0; i<﹟; i++) {
      if (Release𝟷ᵈ(𝟺kbframes[i],𝑙𝑜𝑔₂Pages,pages,avails,false)) { return -(i+1); }
    }
    return 0;
}

int ContiguousAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟)
{
    __builtin_int_t 𝑙𝑜𝑔₂Pages, Idxs; __builtin_uint_t *pages, *avails;
    Reservoir(expeditionary,&𝑙𝑜𝑔₂Pages,&Idxs,&pages,&avails); /* *** 🎿-start *** */
    if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { return -1; }
    if (﹟ >= 2) { for (__builtin_int_t i=0; i<﹟; ++i) {
      uint8_t * next = (uint8_t *)𝟺kbframes[i+1], * present = (uint8_t *)𝟺kbframes[i];
      if (next - present != 4096) { return -2; }
    } }
    return 0;
}

void InitFrames(int count, unsigned expeditionaries[])
{
   __builtin_int_t 𝑙𝑜𝑔₂Pages, Idxs; __builtin_uint_t *pages, *avails;
   for (int i=0; i<count; i++) {
     Reservoir(expeditionaries[i],&𝑙𝑜𝑔₂Pages,&Idxs,&pages,&avails);
     for (__builtin_int_t i=0; i<Idxs; i++) { avails[i]=~0x0; }
   }
}

#pragma mark - anglosaxians and circular reasoning\n\t/sl inner workings of

__builtin_int_t least₋possible₋residue(
  __builtin_int_t dividend, __builtin_int_t divisor)
{
   __builtin_int_t y = dividend % divisor;
   return y < 0 ? y + divisor : y;
} /* ⬷ patch to the '%' operator in a C language undefined case. */

#pragma mark - saturation equal-to min(2ⁿ - 1, x₁ + x₂) and max(-(2ⁿ - 1), x₁ + x₂)

int saturating₋24bits₋add(int32_t 𝟸𝟺₋bits₋biased₋x₁, int32_t 𝟸𝟺₋bits₋biased₋x₂, 
 int32_t * 𝟸𝟺₋bits₋biased₋y) {
   /* int neg = x₁ & x₂ & SIGNBIT_INT64; */
   int32_t 🥈 dynamic = (0b1<<23) - 1;
   int32_t y = 𝟸𝟺₋bits₋biased₋x₁ + 𝟸𝟺₋bits₋biased₋x₂; /* ⬷ see also '24-bit-carry-add'. */
   y = min(dynamic, y);
   y = max(-dynamic, y); /* ⬷ note abelian value pass-through. */
   *𝟸𝟺₋bits₋biased₋y = y;
   return 0;
} /* ⬷ a․𝘬․a 'typedef signed short _Sat saturated16bit' in ISO/IEC TR 18037 and stdfix.h. 
 also _ExtInt(24). */

#pragma mark - time series and peg collections

struct Monoton::Internals { __builtin_int_t soon; 
   
   void init₂(__builtin_int_t oldest) { soon=oldest; }
   
   __builtin_int_t ordinal(bool * wrapped) { __builtin_int_t Ɀ=soon; 
     if (Ɀ == BUILTIN₋INT₋MAX) { soon=0; *wrapped=true; }
     else { *wrapped=false; } soon++; return Ɀ;
   }
   
};

Monoton::Monoton(__builtin_int_t oldest)
{
   auto init₁ = ^(Internals * elem) { impl_=elem; };
   Elements𝘖𝘳Heap(1,1,init₁); impl_->init₂(oldest);
}

__builtin_int_t Monoton::ordinal(bool * wrapped) 
{ return impl_->ordinal(wrapped); }

#pragma mark - utility functions

void
Base𝕟( /* TeX §64, §65 and §67. */
  __builtin_uint_t ℕ,
  unsigned short base,
  unsigned short digitsOr0, /* ⬷ not more than 32 or 64 digits depending on 
    your machines' word size! (Or set to `0` to skip leading zeros.) */
  void (^output)(char 𝟬to𝟵)
)
{
    auto 𝟬to𝗙 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0 }; short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 𝟬to𝗙(cycle[k], 
      output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k--; }
       for (; k >= 0; k--) { 𝟬to𝗙(cycle[k], output); }
    }
} /*  ⬷ note 128-bit duplicate in --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp> and --<Print.cpp>. */

void
Base𝕫(
  __builtin_int_t ℤ,
  unsigned short base,
  unsigned short digitsOr0,
  void (^output)(char 𝟬to𝟵and₋)
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
  void (^out)(char 𝟶to𝟿)
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
    
    do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
    /* if (fractions(uint64_t num, 𝟷𝟶, uint64_t &ℕ, uint64_t &modula)) { return 0; } */
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 
      𝟶to𝖥(cycle[k], out); } }
    else { k = 127; while (cycle[k] == 0 && k > 0) { k--; }
      for (; k >= 0; k--) { 𝟶to𝖥(cycle[k], out); }
    }
} /* ⬷ requires 128-bits-`fractions`, { `__umodti3`, `__udivti3` }, `__udivmodti4`. */

void Base𝕫(__int128_t ℤ, 
  unsigned short base, unsigned short digitsOr0, 
  void (^out)(char 𝟶to𝟿and₋)
)
{
  if (ℤ < +0) { out('-'); ℤ = -ℤ; }
  Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, out);
}

#endif

int
#ifdef __x86_64__
__attribute__((target("rtm"))) /* Arm "tme": uint64_t __tstart(), 
 void __tcommit(), void __tcancel(uint64_t); */
#endif
OptimisticSwap(
  __builtin_int_t /* volatile */ * p₁,
  __builtin_int_t /* volatile */ * p₂,
  Impediment it
) {
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
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
    static __builtin_int_t may₋not₋lock=0;
    if (__sync_bool_compare_and_swap(&may₋not₋lock, 0, 1)) {
      /* Core-exclusive: */
      if (it != MustBeOrdered) { __atomic_exchange(p₁, p₂, p₂, __ATOMIC_SEQ_CST); }
      else { if (*p₁ <= *p₂) __atomic_exchange(p₁, p₂, p₂, __ATOMIC_SEQ_CST); }
      /* Leaving critical-section */
      __sync_lock_release(&may₋not₋lock);
      return 0;
    } else { return -1; }
#endif
} /* ⬷ for/in iso/iec ts: Synchronized { } and atomic_noexcept|cance|commit { }. */

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

#pragma mark - coroutine-based schedulers and the formerly-named 'fiber':

int
Scheduler::Incubate(
  𝟄₋int₁ * coroutine₋err, int32_t ﹟irq, 
  void * (^node₋alloc)(int bytes)
)
{
#if defined  __mips__ || defined __armv6__ || defined espressif
   int32_t val = (int32_t)﹟irq;
#elif defined __x86_64__ || defined __armv8a__
   int64_t val = (int64_t)﹟irq;
#endif
   Treeint valkey { .keyvalue = { val, (__builtin_uint_t)coroutine₋err } };
   void * node = Insert(hw₋collection,valkey,node₋alloc);
   if (node == NULL) { return -1; }
   return 0;
}

int Scheduler::Process(int32_t ﹟irq, 𝟄₋int₁::Waiver * ref)
{
#if defined  __mips__ || defined __armv6__ || defined espressif
   int32_t key=(int32_t)﹟irq; tetra val;
#elif defined __x86_64__ || defined __armv8a__
   int64_t key=(int64_t)﹟irq; octa val;
#endif
   Treeint keyvalue { .keyvalue = { key, 0x0 } };
   Treeint * leaf = Lookup(hw₋collection,keyvalue);
   val.bits = leaf->keyvalue.val;
   𝟄₋int₁ * coroutine₋err = (𝟄₋int₁ *)val.bits;
   Resume(coroutine₋err->coroutine.address());
   return 0;
}

int 
Scheduler::Operational(
  𝟄₋int₁ * coroutine₋err, 
  void * (^perl₋alloc)(int bytes)
)
{
   Necklace * box = (Necklace *)perl₋alloc(sizeof(Necklace));
   if (box == NULL) { return -1; }
   box->err = (𝟄₋int₁ &)coroutine₋err;
   box->nxt = last;
   if (first == NULL || last == NULL) {
     Scheduler::first = curr = last = box;
   }
   Scheduler::last = box;
   return 0;
}

void Scheduler::Init() { hw₋collection = first = curr = last = NULL; }

#pragma mark - miscellaneous initialization functions

void InitFpu()
{
#ifdef __x86_64__
   asm {
     finit
   }
#endif
}

#pragma mark - analysis: post-mortem and single-stepping

extern "C" void ASSEMBLERONLY Sheriff()
{
#ifdef __mips__ /* ⬷ snapshot and reference using the 'DeSAVE' register. */
    Mips
 "    sdbbp 13    \n" /* ⬷ transition debug mode (CP0 DM will be set) 0xBFC0_0480. */
    );
#elif defined  __x86_64_
   Intel👈
     int 3
   } /* Unavailable: __builtin_trap(), raise(SIGTRAP), __builtin_debugtrap() */
#elif defined __armv6__ || defined espressif || defined __armv8a__
#endif
} /* ⬷ details given in --<pic32rt>--<Control.cpp>. */

Chronology& ComputationalChronology() { return computationalChronology; }

Chronology& SystemCalendricChronology() { return calendricChronology; }

void Tuned₋longjmp()
{
   Clear8Memory((ByteAlignedRef)JmpBuf(), sizeof(jmp_buf2));
}


