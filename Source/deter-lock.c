/*  deter-lock.c | lines closed temporarily. */

import Twinbeam;

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
     if (it != MustBeOrdered) { __atomic_exchange(p₁,p₂,p₂,__ATOMIC_SEQ_CST); return 0; }
     if (*p₁ > *p₂) { _xabort(0xff); }
     y=0;
     *p₁ = *p₁ ^ *p₂;
     *p₂ = *p₁ ^ *p₂;
     *p₁ = *p₁ ^ *p₂;
     _xend();
   } else { _xabort(0xfe); }
   return y;
#elif defined __armv8a__
/* uint64_t __tstart, void __tcommit(), void __tcancel(uint64_t) */
#elif defined __mips__ || defined espressif || defined __armv6__
#endif
}

void Initstagnatic(__builtin_int_t * may₋not₋lock)
{
   *may₋not₋lock = 0;
}

int StagnaticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, 
 __builtin_int_t * may₋not₋lock, enum Impediment it)
{
   if (it != MustBeOrdered) { __atomic_exchange(p₁,p₂,p₂,__ATOMIC_SEQ_CST); } /* storage × original × attic × memorder */
   else { __builtin_int_t old₁=*p₁, old₂=*p₂; 
     if (old₁ > old₂) { __sync_val_compare_and_swap(p₁,old₂,); } /* storage ×is old ×then new */
   }

   else if (__sync_bool_compare_and_swap(may₋not₋lock,0,1)) { /* a.k.a if `0`, write `1` in 'may-not-lock'. */
     if (*p₁ <= *p₂) { __atomic_exchange(p₁,p₂,p₂,__ATOMIC_SEQ_CST); }
     __sync_lock_release(may₋not₋lock);
     return 0;
   } else { return -1; }
}