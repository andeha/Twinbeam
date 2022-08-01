/*  deter-lock.c | lines closed temporarily and not algorithm + material. */

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
    if (it == MustBeOrdered && *p₁ > *p₂) { __tcancel(0xff & __TMFAILURE_REASON); }
    *p₁ = *p₁ ^ *p₂;
    *p₂ = *p₁ ^ *p₂;
    *p₁ = *p₁ ^ *p₂;
    y=0; __tcommit();
   } else { _tcancel(__TMFAILURE_RTRY | (0xfe & __TMFAILURE_REASON)); }
   return y;
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   return -1;
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
     if (old₁ > old₂) { __sync_val_compare_and_swap(p₁,old₂,old₁); } /* storage ×is old ×then new */
   }
   
   if (__sync_bool_compare_and_swap(may₋not₋lock,0,1)) { /* a․𝘬․a if `0`, write `1` in 'may-not-lock'. */
     if (*p₁ <= *p₂) { __atomic_exchange(p₁,p₂,p₂,__ATOMIC_SEQ_CST); }
     __sync_lock_release(may₋not₋lock);
     return 0;
   } else { return -1; }
}
