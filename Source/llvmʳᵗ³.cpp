/*  llvmʳᵗ³.cpp - Compiler when blocks, dynamic memory and an UART are required. */

#include <Twinbeam.h>

void * __gxx_personality_v0;
void * _NSConcreteStackBlock[32];
void * _NSConcreteGlobalBlock[32];

auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Fallow = ^(void * p) { free(p); };

void * operator new(size_t size) { return Alloc(size); }
void operator delete(void * p) { Fallow(p); }

extern "C" void * memcpy(void *dst, const void *src, size_t n)
{ return (void *)Copy8Memory((ByteAlignedRef)dst, (ByteAlignedRef)src, (__builtin_int_t)n); }
extern "C" void * memset(void *b, int c, size_t len)
{ return (void *)Overwrite8Memory((ByteAlignedRef)b, (uint8_t)c, (__builtin_int_t)len); }
/* void * memmove(void *dst_void, const void* src_void, size_t length)
{ return (void *)Copy8Memory((ByteAlignedRef)dst0, (ByteAlignedRef)src0, (__builtin_int_t)len0); } */

#ifdef __x86_64__
extern "C" int write(int fd, const void *s, short unsigned b);
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
  
  /* See --<🥽 Keyput.cpp> for details on:
   
   H₁ Call `uint8_t getutf8()` and wait as in uint8_t utf8 = getutf8();
   H₂ Intermingle with Timer1-Timer9 
   
   */
  
#elif defined __x86_64__
  *uc = (char32_t)fgetwc(stdin);
#endif
  return 0;
}; /* This function locks until keypress. See --<🥽 Keyput.cpp> for 
  a slightly different version. */

/* See --<Fossilate.h|cpp> for additional prepacked lambdas. */

