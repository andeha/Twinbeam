/*  convoj-sequence.c | multiple-sized objects. */

import Twinbeam;

int init₋convoj(struct collection * 🅵₁, struct collection * 🅵₂)
{
   if (collection₋init(8,4096,🅵₂)) { return -2; }
   if (collection₋init(1,4096,🅵₁)) { return -1; }
   return 0;
}

int copy₋include₋convoj(ALLOC alloc, 
  struct collection * 🅵₁, struct collection * 🅵₂, 
  __builtin_int_t count, __builtin_int_t bytes[], ...)
{ uint8_t *original; __builtin_int_t item₋idx,byte₋idx=0,cachedbytes;
   va_prologue(bytes);
   for (item₋idx=0; item₋idx<count; item₋idx+=1) {
     original = __builtin_va_arg(__various, uint8_t *);
     cachedbytes = bytes[item₋idx];
     /* __builtin_memcpy(dst,src,bytes); */
     if (copy₋append₋items(1,&cachedbytes,🅵₂,alloc)) { return -2; }
     if (copy₋append₋items(cachedbytes,original,🅵₁,alloc)) { return -1; }
     byte₋idx += cachedbytes;
   }
   va_epilogue
   return 0;
}

__builtin_int_t convoj₋count(struct collection * 🅵₁, struct collection * 🅵₂)
{
   return collection₋count(🅵₂);
}

uint8_t * convoj₋relative(__builtin_int_t idx, struct collection * 🅵₁, 
 struct collection * 🅵₂)
{
   __builtin_int_t offset = collection₋relative(idx,🅵₂);
   return collection₋relative(offset,🅵₁);
}

