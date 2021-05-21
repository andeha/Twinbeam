/* pic32mz.cpp | sometimes many legs, sometimes organized. */

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
} /* ⬷ 𝘊𝘧. copying using a Dma-facility and 'asyncronicity' a․𝘬․a OptimisticAsync8Copy. */

void backpack₋free(void * ref)
{
  
}

void * backpack₋malloc(__builtin_int_t bytes)
{
  return NULL;
}

