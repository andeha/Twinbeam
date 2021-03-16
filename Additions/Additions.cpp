/*  Additions.cpp | Twinbeam (c++2a for clang to x86_64 or Mips.) */

#include <Twinbeam.h>
#include <Additions/Additions.h>

#pragma mark conversions for --<Additions>--<Filesystem.hpp>

__builtin_int_t
Utf8BytesUntilNull(
  char8_t * u8s,
  __builtin_int_t maxbytes
)
{ __builtin_int_t i=0;
again:
   if (i >= maxbytes) { return maxbytes; }
   char8_t * leadOr8Bit = u8s + i;
   if (*leadOr8Bit == 0x0) { return i; }
   __builtin_int_t followers = Utf8Followers(*leadOr8Bit);
   if (followers < 0) { return -1; }
   i += followers + 1;
   goto again;
}

__builtin_int_t TetrasUntilNull(char32_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t i=0;
again:
   if (i >= maxtetras) { return maxtetras; }
   char32_t * uc = ucs + i;
   if (*uc == 0x0000) { return i; }
   ++i; goto again;
}

__builtin_int_t ExactUtf8bytes(char32_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t sum=0, i=0;
again:
   if (i >= maxtetras) { return sum; }
   char32_t uc = *(ucs + i);
   if (uc < 0x80L) { sum += 1; }
   else if (uc < 0x800L) { sum += 2; }
   else if (uc < 0x10000L) { sum += 3; }
   else if (uc <= 0x0010FFFFL) { sum += 4; }
   else { return -1; }
   ++i; goto again;
   return 0;
}

__builtin_int_t ExactTetras(char8_t * u8s, __builtin_int_t maxutf8bytes)
{ __builtin_int_t i=0, sum=0;
again:
   char8_t leadOr8Bit = *(i + u8s);
   if (leadOr8Bit == 0x0) { return sum; }
   __builtin_int_t followers = Utf8Followers(leadOr8Bit);
   if (followers < 0) { return -1; }
   sum += 1+followers; ++i; goto again;
   return 0;
}

#pragma mark still chronological when sequential

__builtin_int_t Ordinal(Chronology₋peg * /* act a․𝘬․a */ sequent, bool * didwrap)
{  __builtin_int_t Ɀ=sequent->soon;
    if (Ɀ == BUILTIN₋INT₋MAX) { sequent->soon=0; *didwrap=true; }
    else { *didwrap=false; } sequent->soon++; return Ɀ;
}

#pragma mark software interrupts a․𝘬․a 'notifications' and 'signals'

#include <Source/fifo.h>

namespace Messaging {
   
   int Init(int fifo₋words, void * 𝟷₋fifo₋tile)
   {  extern void * sw₋signals; /* = Map<int32_t, 𝟄₋int₁ * 𝟷₋coroutine> */
      extern fifo jobs; sw₋signals=NULL;
      if (jobs.init(fifo₋words,𝟷₋fifo₋tile)) { return -1; }
      return 0;
   }
   
   int
   Informed(int32_t signal, 𝟄₋int₁ * 𝟷₋coroutineToInfluence, 
     void * (^node₋alloc)(int bytes)
   ) {
#if defined __x86_64__ || defined __armv8a__
      Treeint valkey { .keyvalue = { (int64_t)signal, uint64_t(𝟷₋coroutineToInfluence) } };
#elif defined __mips__ || defined __armv6__ || defined espressif
      Treeint valkey { .keyvalue = { signal, uint32_t(𝟷₋coroutineToInfluence) } };
#endif
      extern void * sw₋signals;
      void * node = Insert(sw₋signals,valkey,node₋alloc);
      if (node == NULL) { return -1; }
      return 0;
   } /* void (^influence)(void * ctx) */
   
   int Entrust(int32_t signal, void * ctx)
   {
     Treeint leafkey { signal, 0ull };
     extern void * sw₋signals;
     Treeint * node = Lookup(sw₋signals,leafkey);
     𝟄₋int₁ * 𝟷₋coroutine = (𝟄₋int₁ *)node->keyvalue.val; /* 𝟷₋coroutine->ctx=ctx; */
     Resume(𝟷₋coroutine->coroutine.address());
     return 0;
   }
   
}

