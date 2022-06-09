/*  pic32-institut.cpp | sometimes many legs, sometimes organized. */

import Twinbeam; /* -D__Pic32MMCuriosity__ and -D__MZDAStarterBoard__ */

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
} /* ⬷ c𝘧․ copying using a asyncronous dma a․𝘬․a OptimisticAsync8Copy. */

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
  for (__builtin_int_t i=0, offset=0; i<count; ++i, offset += 4096) {
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
} /* ⬷ a․𝘬․a 'best fit' and consecutive, not 'first fit'. */

void * Heap₋alloc(__builtin_int_t bytes) { return backpack₋alloc(bytes); }
__builtin_int_t Heap₋object₋size(void * ref) { return backpack₋object₋size(ref); }
void Heap₋unalloc(void * ref) { backpack₋free(ref); }

void Fallow(void * ref) { Heap₋unalloc(ref); }
void * Alloc(__builtin_int_t bytes) { return Heap₋alloc(bytes); }

/*                                               the callee must preserve    
   zero $0   |  always the value 'zero'.                              No     
   at   $1   |  assembler temporary.                                  No     
   v0   $2   |  the returned value for 32-bit and smaller….           No     
   v1   $3   |  …returned 'hi' value when 64-bits are required.       No     
   a0   $4   |  first integer argument.                               No     
   a1   $5   |  second integer argument.                              No     
   a2   $6   |  third integer argument.                               No     
   a3   $7   |  fourth integer argument.                              No     
   t0   $8   |  1:st temporary reg. that must not be preserved.       No     
   t1   $9   |  2:nd temporary reg. that must not be preserved.       No     
   t2  $10   |  3:th temporary reg. that must not be preserved.       No     
   t3  $11   |  4:th temporary reg. that must not be preserved.       No     
   t4  $12   |  5:th temporary reg. that must not be preserved.       No     
   t5  $13   |  6:th temporary reg. that must not be preserved.       No     
   t6  $14   |  7:th temporary reg. that must not be preserved.       No     
   t7  $15   |  8:th temporary reg. that must not be preserved.       No     
   s0  $16   |                                                       Yes     
   s1  $17   |  ''                                                   Yes     
   s2  $18   |   function prologue copies the register value …       Yes     
   s3  $19   |   to the stack frame and the function …               Yes     
   s4  $20   |   epilogue copies the values back to the …            Yes     
   s5  $21   |   register.                                           Yes     
   s6  $22   |                                               ''      Yes     
   s7  $23   |                                                       Yes     
   t8  $24   |  nineth temporary register.                            No     
   t9  $25   |  tenth temporary register.                             No     
   k0  $26   |  kernel and/or _ register.                             No     
   k1  $27   |  kernel and/or _ register.                             No     
   gp  $28   |  global pointer, the addr. to static globals.         Yes     
   sp  $29   |  the last pushed argument on the stack.               Yes     
⬷ the sp register must be 8-bytes aligned.                                  
   fp  $30   |  the frame pointer.                                   Yes     
   ra  $31   |  the address to return to when running a ftn.         Yes   */
/* Parameters smaller than 32-bits are promoted to 32-bits. */
/* Sixty-four bits parameters are for little-endian passed in e.g a1:a0 and a3:a2. */

