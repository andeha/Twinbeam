/*  llvmʳᵗ³.cpp - With blocks dynamic memory and an UART are required. */

#include <Twinbeam.h>

void * __gxx_personality_v0;
void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];
uint32_t __ℕ₋🅻[4], __ℕ₋🅷[4];
struct { __builtin_int_t board₁, palm₂; } cxaGuard;
jmp_buf2 /* volatile */ singleTaskProgramState;
void * Scheduler::ʰᵚcollection; 
Scheduler::Necklace *first, *curr, *last;
Chronology calendricChronology, computationalChronology;
extern "C" int __cxa_guard_acquire() { return 🔒(cxaGuard); }
extern "C" void __cxa_guard_release() { 🔓(cxaGuard); }
extern "C" int __cxa_atexit(void (* fn)(void *), void * arg, void * dso_handle) { return 0; }
extern "C" void __cxa_pure_virtual() { /* print("Pure virtual function called\n"); */ /* boot_Reset(PIC32MZDA_KEY1,PIC32MZDA_KEY2); */ /* ⭐️ Sheriff() */ while (1); } /* `BLURT` unpossible since one error allowed. */
namespace std { void terminate() { /* ⭐️ Sheriff() */ } }
extern "C" void * __cxa_begin_catch(void * exceptionObject) throw() { /* ⭐️ Sheriff() */ return NULL; }
void * operator new(size_t size) { return Alloc(size); } /* ⬷ E․𝘨 for impl_ ∧ 😐 */
void operator delete(void * ref) throw() { Fall⒪⒲﹠o(ref); }
auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Fall⒪⒲﹠o = ^(void * ref) { free(ref); };
/* ⬷ To access primitive, include 'extern void * (^Alloc)(__builtin_int_t);' inside your .cpp file. */
extern "C" void * memcpy(void * dst, const void * src, size_t bytes)
{ return Copy8Memory(ByteAlignedRef(dst), ByteAlignedRef(src), __builtin_int_t(bytes)); }
extern "C" void * memset(void * base, int value, size_t bytes)
{ return Overwrite8Memory(ByteAlignedRef(base), (uint8_t)value, __builtin_int_t(bytes)); }
#ifdef __x86_64__
extern "C" int write(int fd, const void * s, short unsigned nbyte);
DISORDERABLE auto Putₒ = ^(uint8_t * u8s, __builtin_int_t bytes) {
  write(/* stdout, i.e */ 1, (const void *)u8s, bytes); };
DISORDERABLE auto Traceₒ = ^(uint8_t * u8s, __builtin_int_t bytes) {
  write(/* stderr, i.e */ 2, (const void *)u8s, bytes); };
#include <wchar.h>
#elif defined __mips__
extern void putch(uint8_t c);
extern void Putₒ(uint8_t c, __builtin_int_t bytes);
DISORDERABLE auto Putₒ = ^(uint8_t * u8s, __builtin_int_t bytes) {
  for (__builtin_int_t i=0; i<bytes; i++) putch(*(u8s+i)); };
DISORDERABLE auto Traceₒ = ^(uint8_t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
extern "C" const char * tab = "\t"; /* Also U+0009 'Character tabulation'. */
extern "C" const char * eol = "\n"; /* Also U+2028 'Line separator' and `␍`+`␊`, `␤`. */
extern "C" const char * sep = "\n\n"; /* Also U+2029 'Paragraph separator'. */
namespace VT100 { const char * bright = "\x1B[1m", *dim = "\x1B[2m", *fgBlue = "\x1B[34m", 
 *fgRed = "\x1B[31m", *reset = "\x1B[0m", *reverse = "\x1B[7m"; }

#ifdef __x86_64__
#include <dispatch/dispatch.h>
#include <pthread.h>
#endif

𝟄₋int₁ corout₋irqUART5Rx₋Wa₋it(unsigned expeditionary, int periods𝘖rZero, 
  int 𝟷𝟶ᵗʰ₋seconds, char32_t * uc, void * (^alloc)(int bytes))
{
#ifdef __mips__
   int 🥈 word₋elems=1024; void * 𝟷₋tile₋utf8=alloc(word₋elems), 
    * 𝟷₋tile₋keydown=alloc(word₋elems), *𝟷₋tile₋length=alloc(word₋elems);
   static Fifo<uint8_t> utf8bytes;
   if (utf8bytes.init(word₋elems,𝟷₋tile₋utf8)) { co_return -1; }
   static Fifo<char32_t> uc₋keydownAndOrnaments; /* Possibly-maybe: 'little-endian'. */
   if (uc₋keydownAndOrnaments.init(word₋elems,𝟷₋tile₋keydown)) { co_return -2; }
   static Fifo<Chronology::Interval> key₋when;
   if (key₋when.init(word₋elems,𝟷₋tile₋length)) { co_return -3; }
   co_yield 1; uint8_t c=0; while (1) { __builtin_int_t count=1; 
     co_yield c; uint8_t c₁=getutf8(); __builtin_uint_t c₂=(__builtin_uint_t)c₁;
     if (utf8bytes.copy₋include(expeditionary,count,&c₂)) { co_return -4; }
    }
#elif defined __x86_64__
 /* void * Readthread(void * param) { *uc = (char32_t)fgetwc(stdin); return (void *)NULL; };
   int y = pthread_create(readthread,attr,Readthread,arg);
   if (y) { co_return -1; } */
   /* Locks until keypress. See --<🥽 Keyput.cpp> for a slightly different version. */
#endif
   co_return 0;
} /* a․𝘬․a `Stimulus` and `Waitterminal`.  Previously returned `0` when a 
 key has been captured, `1` on timeout, other numbers on error. 
   
  See --<🥽 Keyput.cpp> for details on: 
   H₁ Call `uint8_t getutf8()` and wait as in uint8_t utf8 = getutf8();
   H₂ Intermingle with Timer1-Timer9
   H₃ static Fifo<uint8_t> utf8bytes;
      static Fifo<char32_t> unicodesKeyupsAndOrnaments
      static Fifo<Chronology::Instant> keyWhen  */
 
/* See --<Fossilate.h|cpp> for additional prepacked lambdas and coroutines. */

enum { BLOCK_IS_FLUCTUANT=8, BLOCK_IS_WEAK=16, BLOCK_IS_ANOTHERBLOCK=7 };

extern "C" void _Block_object_assign(void * dst, const void * obj, const int flags)
{}

extern "C" void _Block_object_dispose(const void * obj, const int flags)
{ /* May utilize `Acquire` and `Release`. */
#ifdef XXX
    if (flags & BLOCK_FIELD_IS_BYREF)  {
       /* Get rid of the fluctuant data structure held in a block. */
       _Block_byref_release(object);
    }
    else if ((flags & (BLOCK_FIELD_IS_BLOCK|BLOCK_BYREF_CALLER)) == BLOCK_FIELD_IS_BLOCK) {
       /* Get rid of a referenced block held by this block. (Ignore fluctuant 
         block variables, compiler does not need to call us.) */
       _Block_destroy(object);
    }
    else if ((flags & (BLOCK_FIELD_IS_WEAK|BLOCK_FIELD_IS_BLOCK|BLOCK_BYREF_CALLER)) == BLOCK_FIELD_IS_OBJECT) {
       /* Get rid of a referenced object held by this block. (Ignore fluctuant object 
        variables, compiler does not need to call us.) */
       _Block_release_object(object);
    }
#endif
}

#ifdef __mips__
extern int fractions(__uint128_t num, __uint128_t denom, __uint128_t &ℕ, __uint128_t &modula);
extern "C" __uint128_t __udivmodti4(__uint128_t a, __uint128_t b, __uint128_t * rem) {
  __uint128_t ℕ; int y = fractions(a, b, ℕ, (__uint128_t&)rem); return ℕ; } /* Returns 'a/b' and 'a mod b'. */
extern "C" __uint128_t __umodti3(__uint128_t a, __uint128_t b) { __uint128_t r; __udivmodti4(a, b, &r); return r; }
extern "C" __uint128_t __udivti3(__uint128_t a, __uint128_t b) { __uint128_t r, d; d = __udivmodti4(a, b, &r); return d; }
#endif

#pragma mark - Frames and multiple frame stores

template <int 𝑙𝑜𝑔₂Frames>
struct Framestore { __builtin_int_t 🥈 𝑙𝑜𝑔₂Pages=𝑙𝑜𝑔₂Frames, 
  Pages=0b1<<𝑙𝑜𝑔₂Frames,
  BytesPerWord=sizeof(__builtin_uint_t),
  Words=Pages*(SystemInfoPagesize()/BytesPerWord),
  Idxs=(Pages/BytesPerWord)>>3;
  __builtin_uint_t pages[Words], avails[Idxs];
}; 

void
Reservoir(unsigned expeditionary, 
  __builtin_int_t *𝑙𝑜𝑔₂Pages, __builtin_int_t *Idxs, 
  __builtin_uint_t **pages, __builtin_uint_t **avails
)
{
    /* int count=2; static unsigned expeditionaries[] = { 9, 9 }; */
#if defined (__mips__) && defined (__MZ__)
    static Framestore<9> f₁;
    static Framestore<9> f₂ __attribute__ ((section(".ddr2"))); /* Store at 0xA8000000 (non-cachable) and 0x88000000 (cachable). */
    static Expeditionary exp₁ = Expeditionary { f₁.𝑙𝑜𝑔₂Pages, f₁.Idxs, f₁.pages, f₁.avails };
    static Expeditionary exp₂ = Expeditionary { f₂.𝑙𝑜𝑔₂Pages, f₂.Idxs, f₂.pages, f₂.avails };
    switch (expeditionary) {
    case 0: *𝑙𝑜𝑔₂Pages=exp₁.𝑙𝑜𝑔₂Pages; *Idxs=exp₁.Idxs; *pages=exp₁.pages; *avails=exp₁.avails; break;
    case 1: *𝑙𝑜𝑔₂Pages=exp₂.𝑙𝑜𝑔₂Pages; *Idxs=exp₂.Idxs; *pages=exp₂.pages; *avails=exp₂.avails; break;
    default: *𝑙𝑜𝑔₂Pages=0; *Idxs=0; *pages=NULL; *avails=NULL; break;
    }
#elif defined __x86_64__
    static Framestore<9> f;
    static Expeditionary exp = Expeditionary { f.𝑙𝑜𝑔₂Pages, f.Idxs, f.pages, f.avails };
    *𝑙𝑜𝑔₂Pages=exp.𝑙𝑜𝑔₂Pages; *Idxs=exp.Idxs; *pages=exp.pages; *avails=exp.avails;
#endif
}
