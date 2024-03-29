/*  deter-lock.c | lines closed temporarily and hardware spinlock. */

#include "twinbeam-inner.h"
#if defined __SSE2__
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/immintrin.h"
#elif defined __ARM_NEON__
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/arm_acle.h"
#endif

int
#if defined __x86_64__
__attribute__((target("rtm")))
#elif defined __armv8a__
__attribute__((target("tme")))
#endif
OptimisticSwap(
  __builtin_int_t * p₁, 
  __builtin_int_t * p₂, 
  enum Impediment it
)
{ int y=-1;
#if defined __x86_64__
   unsigned state = _xbegin();
   if (state == _XBEGIN_STARTED) {
     if (it == MustBeOrdered && *p₁ > *p₂) { _xabort(0xff); }
     *p₁ = *p₁ ^ *p₂;
     *p₂ = *p₁ ^ *p₂;
     *p₁ = *p₁ ^ *p₂;
     y=0; _xend();
   } else { _xabort(0xfe); }
   return y;
#elif defined __armv8a__
   uint64_t transactional₋state = __tstart();
   if (transactional₋state == 0) {
    if (it == MustBeOrdered && *p₁ > *p₂) { __tcancel(0xff & _TMFAILURE_REASON); }
    *p₁ = *p₁ ^ *p₂;
    *p₂ = *p₁ ^ *p₂;
    *p₁ = *p₁ ^ *p₂;
    y=0; __tcommit();
   } else { __tcancel(_TMFAILURE_RTRY | (0xfe & _TMFAILURE_REASON)); }
   return y;
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   while (1) { continue; }
   return -1;
#endif
} /* when a hierachial __tstart fails with a non-zero value, it causes all within and *the* outer to fail. */
/* the result of a hierarchial transaction is not visible until the outer transaction commits. */

void Initstagnatic(__builtin_int_t * may₋not₋lock)
{
   *may₋not₋lock = 0;
}

int StagnaticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, 
 __builtin_int_t * may₋not₋lock, enum Impediment it)
{
   return 0;
}


