/*  nevada-institut.c | sometimes many legs and sometimes organized. */

import Twinbeam;

__builtin_int_t backpack₋object₋size(void * ref)
{
  __builtin_uint_t * wordref = (__builtin_uint_t *)ref;
  return *(wordref - 1);
}

inexorable __builtin_int_t fourkbframe₋bytecount(__builtin_int_t bytes) 
{ return 1 + bytes/4096; }

void backpack₋free(void * ref)
{
  __builtin_int_t bytes = backpack₋object₋size(ref);
  __builtin_int_t ﹟ = fourkbframe₋bytecount(bytes);
  unsigned expeditionary=1; void * fourkb[﹟];
  for (__builtin_int_t i=0, offset=0; i<count; i+=1, offset += 4096) {
    fourkb[i] = offset + (uint8_t *)ref; }
  if (Fallow(expeditionary,fourkb,﹟)) { return; }
  return;
}

void * backpack₋alloc(__builtin_int_t bytes)
{ __builtin_int_t Wordbytes=sizeof(__builtin_uint_t);
  __builtin_int_t ﹟ = fourkbframe₋bytecount(bytes + 1*Wordbytes);
  __builtin_int_t wordcount = ﹟ / Wordbytes;
  unsigned expeditionary=1; __builtin_uint_t * fourkbframes[wordcount];
  if (ContiguousAcquire(expeditionary,fourkbframes,﹟)) { return ΨΛΩ; }
  return 1 + fourkbframes;
} /*  a․𝘬․a 'best fit' and consecutive, not 'first fit'. */

void * Heap₋alloc(__builtin_int_t bytes) { return backpack₋alloc(bytes); }
__builtin_int_t Heap₋object₋size(void * ref) { return backpack₋object₋size(ref); }
void Heap₋unalloc(void * ref) { backpack₋free(ref); }

void Fallow(void * ref) { Heap₋unalloc(ref); }
void * Alloc(__builtin_int_t bytes) { return Heap₋alloc(bytes); }

#pragma recto analysis post-mortem and single-steps

void Sheriff(void)
{
   __builtin_debug();
}

