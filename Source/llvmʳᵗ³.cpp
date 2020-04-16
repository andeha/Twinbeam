/*  llvmʳᵗ³.cpp - With blocks dynamic memory and an UART are required. */

#include <Twinbeam.h>

void * __gxx_personality_v0;
void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];
struct { __builtin_int_t board₁, palm₂; } cxaGuard;
extern "C" int __cxa_guard_acquire() { return 🔒(cxaGuard); }
extern "C" void __cxa_guard_release() { 🔓(cxaGuard); }
extern "C" int __cxa_atexit(void (* fn)(void *), void * arg, void * dso_handle) { return 0; }
extern "C" void __cxa_pure_virtual() { /* print("Pure virtual function called\n"); */ /* boot_Reset(PIC32MZDA_KEY1,PIC32MZDA_KEY2); */ /* ⭐️ Sheriff() */ while (1); } /* `BLURT` unpossible since one error allowed. */
namespace std { void terminate() { /* ⭐️ Sheriff() */ } }
extern "C" void * __cxa_begin_catch(void * exceptionObject) throw() { /* ⭐️ Sheriff() */ return NULL; }
void * operator new(size_t size) { return Alloc(size); } /* ⬷ E․𝘨 for impl_ ∧ 😐 */
void operator delete(void * p) throw() { Fallow₋ₒ(p); }
auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Fallow₋ₒ = ^(void * p) { free(p); };
/* ⬷ To access primitive, include 'extern void * (^Alloc)(__builtin_int_t);' inside your .cpp file. */
extern "C" void * memcpy(void *dst, const void *src, size_t n)
{ return (void *)Copy8Memory((ByteAlignedRef)dst, (ByteAlignedRef)src, (__builtin_int_t)n); }
extern "C" void * memset(void *b, int c, size_t len)
{ return (void *)Overwrite8Memory((ByteAlignedRef)b, (uint8_t)c, (__builtin_int_t)len); }
/* void * memmove(void * dst𝘖𝘳Void, const void * src𝘖𝘳Void, size_t length)
{ return (void *)Copy8Memory((ByteAlignedRef)dst𝘖𝘳Void, (ByteAlignedRef)src𝘖𝘳Void, (__builtin_int_t)len); } */
#ifdef __x86_64__
extern "C" int write(int fd, const void * s, short unsigned b);
DISORDERABLE auto Putₒ = ^(uint8_t * utf8s, uint16_t bytes) {
  write(1, (const void *)utf8s, bytes); };
#include <wchar.h>
#elif defined __mips__
#include <pic32rt/mips.hpp>
#include <pic32rt/pic32mz.hpp>
#include <pic32rt/pic32mzda.hpp>
#include <pic32rt/stable.hpp>
auto Putₒ = ^(uint8_t * utf8s, uint16_t bytes) {
  for (int i = 0; i < bytes; i++) putch(*(utf8s+i)); };
#endif
/* Returns `0` when a key has been captured, `1` on timeout, other 
  numbers on error. */
DISORDERABLE auto WaitTerminal = ^(int periods𝘖𝘳Zero, int 
  ᵗᵉⁿᵗʰseconds, void (^ping)(bool &stop), char32_t * uc) {
#ifdef __mips__
  
  /*
   
   See --<🥽 Keyput.cpp> for details on:
   H₁ Call `uint8_t getutf8()` and wait as in uint8_t utf8 = getutf8();
   H₂ Intermingle with Timer1-Timer9
   
   */
  
#elif defined __x86_64__
  *uc = (char32_t)fgetwc(stdin);
#endif
  return 0;
}; /* Locks until keypress. See --<🥽 Keyput.cpp> for a slightly different version. */

/* See --<Fossilate.h|cpp> for additional prepacked lambdas. */

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
    static Framestore<9> f₂ __attribute__ ((section(".ddr2")); /* Store at 0xA8000000 (non-cachable) and 0x88000000 (cachable). */
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

