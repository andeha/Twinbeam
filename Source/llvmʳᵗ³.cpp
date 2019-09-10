/*  llvmʳᵗ³.cpp - When blocks, dynamic memory and an UART are required. */

#include <Twinbeam.h>

void * __gxx_personality_v0;
void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];
extern "C" void __cxa_pure_virtual() { BLURT("Pure virtual function called"); while (1); }
extern "C" int __cxa_atexit(void (* fn)(void *), void * arg, void * dso_handle) { return 0; }
struct { __builtin_int_t board₁, palm₂; } cxaGuard;
extern "C" int __cxa_guard_acquire() { return 🔒(cxaGuard); }
extern "C" void __cxa_guard_release() { 🔓(cxaGuard); }
auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Fallow = ^(void * p) { free(p); };
void * operator new(size_t size) { return Alloc(size); }
void operator delete(void * p) { Fallow(p); }
extern "C" void * memcpy(void *dst, const void *src, size_t n)
{ return (void *)Copy8Memory((ByteAlignedRef)dst, (ByteAlignedRef)src, (__builtin_int_t)n); }
extern "C" void * memset(void *b, int c, size_t len)
{ return (void *)Overwrite8Memory((ByteAlignedRef)b, (uint8_t)c, (__builtin_int_t)len); }
/* void * memmove(void * dst𝘖𝘳Void, const void * src𝘖𝘳Void, size_t length)
{ return (void *)Copy8Memory((ByteAlignedRef)dst0, (ByteAlignedRef)src0, (__builtin_int_t)len0); } */
/* See also: Implementations inside Imagination technologies. */
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

void _Block_object_assign(void * dst, const void * obj, const int flags)
{
}

void _Block_object_dispose(const void * obj, const int flags)
{
#ifdef XXX
    if (flags & BLOCK_FIELD_IS_BYREF)  {
       // get rid of the __block data structure held in a Block
       _Block_byref_release(object);
    }
    else if ((flags & (BLOCK_FIELD_IS_BLOCK|BLOCK_BYREF_CALLER)) == BLOCK_FIELD_IS_BLOCK) {
       // get rid of a referenced Block held by this Block
       // (ignore __block Block variables, compiler doesn't need to call us)
       _Block_destroy(object);
    }
    else if ((flags & (BLOCK_FIELD_IS_WEAK|BLOCK_FIELD_IS_BLOCK|BLOCK_BYREF_CALLER)) == BLOCK_FIELD_IS_OBJECT) {
       // get rid of a referenced object held by this Block
       // (ignore __block object variables, compiler doesn't need to call us)
       _Block_release_object(object);
    }
#endif
}
