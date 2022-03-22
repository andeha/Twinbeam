/*  convoj-sequence.c | multiple-sized objects. */

import Twinbeam;

int init₋convoj(struct collection * 🅵₁, struct collection * 🅵₂)
{
   collection₋init(8,4096,🅵₂);
   collection₋init(1,4096,🅵₁);
}

int copy₋include₋convoj(
  struct collection * 🅵₁, struct collection * 🅵₂, 
  __builtin_int_t count, __builtin_int_t bytes[], ...)
{ uint8_t * src, *dst; __builtin_int_t idx,i;
   va_prologue(bytes);
   src = __builtin_va_arg(__various, uint8_t *);
   for (i=0; i<count; i+=1) {
     idx = 
     dst =
     __builtin_memcpy(dst,src,bytes[i]);
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

