/*  pic32mz.cpp | sometimes many legs, sometimes organized. */

import Twinbase;

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
} /* ⬷ c𝘧․ copying using a Dma-facility and 'asyncronicity' a․𝘬․a OptimisticAsync8Copy. */

inexorable __builtin_int_t 𝟺kbframe₋count(__builtin_int_t bytes) 
{ return 1 + bytes/4096; }

void backpack₋free(void * ref)
{
  struct sh₋unk { __builtin_int_t bytes; } * start = (sh₋unk *)ref;
  __builtin_int_t ﹟ = 𝟺kbframe₋count(start->bytes);
  unsigned expeditionary=1; void * 𝟺kbpages[﹟];
  for (__builtin_int_t i=0, offset=0; i<﹟; ++i, offset += 4096) { 𝟺kbpages[i] = offset + (uint8_t *)ref; }
  if (🄕allo⒲(expeditionary,𝟺kbpages,﹟)) { return; }
  return;
}

void * backpack₋alloc(__builtin_int_t bytes)
{
  __builtin_int_t ﹟ = 𝟺kbframe₋count(bytes + 1*Wordbytes);
  unsigned expeditionary=1; void * 𝟺kbframes[﹟];
  if (ContiguousAcquire(expeditionary,𝟺kbframes,﹟)) { return NULL; }
  return 𝟺kbframes[0];
} /* ⬷ a․𝘬․a 'first fit' and consecutive. */

