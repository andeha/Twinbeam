/*  chim-model.c | also known as a 'preference'. */

#include "twinbeam-inner.h"

int IMUL(short id, int32_t left, int32_t right, uint32_t * low, 
 uint32_t * high, int * negative)
{
   union rad { struct { uint32_t lo, hi; } 𝓘; uint64_t bits; } 𝓞;
   union realizable { uint64_t bits; int64_t amount; } y;
   extern uint32_t cumulative₋🅷[4], cumulative₋🅻[4];
   y.amount = left * right; 𝓞.bits = y.amount; *low = 𝓞.𝓘.lo; *high = 𝓞.𝓘.hi;
   cumulative₋🅷[id] = 𝓞.𝓘.hi; cumulative₋🅻[id] = 𝓞.𝓘.lo;
   *negative = (0x80000000 & cumulative₋🅷[id]) ? 1 : 0;
   return 0;
}

int32_t invsignextend(int64_t figure)
{
   int neg = figure < 0;
   int32_t y = (int32_t)(neg ? -figure : figure);
   return y;
} /* a․𝘬․a 'sign-cutaway'. See the microMIPS32 instruction set and 'seh' and 
 'seb' for one instruction encoding. */

int IADD(short id, int32_t left, int32_t right, uint32_t * sum, 
 int * negative, int * overflow)
{
   union realizable { uint32_t bits; int32_t amount; };
   extern uint32_t cumulative[8];
   int64_t thesis = right + left;
   if (thesis > 0x7fffffffffffffff) { *overflow=1; }
   if (thesis > 0xffffffffffffffff) { *overflow=1; }
   *sum = invsignextend(thesis);
   *negative = 0x8000000000000000 & thesis ? 1 : 0;
   return 0;
}

int INEG(short id, int32_t custom, uint32_t * reflection, 
 int * negative)
{
   union realizable { uint32_t bits; int32_t amount; } xoxXooox = { .amount=custom };
   if (xoxXooox.bits == 0x80000000) return -1;
   uint32_t thesis = ~custom; /* bits copied. 'Actual theory'. */
   extern uint32_t cumulative[8];
   cumulative[id] = 1 + thesis;
   *reflection = thesis;
   *negative = (cumulative[id] & 0x80000000) ? 1 : 0;
   return 0;
}

