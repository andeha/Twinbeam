/* pic32mz.cpp | Sometimes many legs, sometimes… */

#include <Twinbeam.h>

#define ONLY_MSPACES        0
#define LACKS_SYS_TYPES_H   1
#define NO_MALLOC_STATS     1
#define USE_LOCKS           0
#define LACKS_ERRNO_H       1
#define LACKS_TIME_H        1
#define LACKS_STDLIB_H      1
#define LACKS_STRING_H      1
#define HAVE_MMAP           0
#define LACKS_UNISTD_H      1
#define LACKS_SYS_PARAM_H   1
#define MALLOC_FAILURE_ACTION
#define ABORT
#define EINVAL              22
#define ENOMEM              12
typedef long int ptrdiff_t;
extern "C" void * memset(void * b, int c, size_t len);
extern "C" void * memcpy(void * dest, void const * src, size_t n);
void * sbrk(ptrdiff_t incr) { return 0; }
#include "malloc.cxx"

/* µA("mips", "r2", x₃, x₄) */
FOCAL
ByteAlignedRef
Copy8Memory(
  ByteAlignedRef dst,
  ByteAlignedRef src,
  __builtin_int_t bytes
) /* ⬷ a․𝘬․a 'memcpy'. */
{
   char * dp = (char *)dst;
   const char * sp = (const char *)src;
   while (bytes--) *dp++ = *sp++;
   return dst;
} /* ⬷ see also --<Additions.h>{OptimisticAsync8Copy} 𝘪․𝘦 copying using a DMA-facility. */


