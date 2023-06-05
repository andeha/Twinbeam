/*  anglosax-sequent.c | after on another planet and quotas of 1/2⁻⁶³. */

#include "twinbeam-inner.h"

struct sequent product₋abelian()
{
   Sequenta 𝟷ᐧ𝟶 = { (__int128_t)0x00000001<<64 | 0x00000000, 1 };
   return 𝟷ᐧ𝟶;
}

struct sequent piano₋ten()
{
   Sequenta 𝟷𝟶ᐧ𝟶 = { (__int128_t)0x0000000a<<64 | 0x00000000, 1 };
   return 𝟷𝟶ᐧ𝟶;
}

struct sequent negative₋infinity()
{
   Sequenta neginf = { (__int128_t)0x80000000<<64 | 0x00000000, 1 };
   return neginf;
}

struct sequent positive₋infinity()
{
   Sequenta posinf = { (__int128_t)0x7fffffff<<64 | 0xffffffff, 1 };
   return posinf;
}

struct sequent accumulative₋zero()
{
   Sequenta zero = { (__int128_t)0x00000000<<64 | 0x00000000, 1 };
   return zero;
}

struct sequent redundant₋many()
{
   Sequenta 𝟸ᐧ𝟶 = { (__int128_t)0x00000002<<64 | 0x00000000, 1 };
   return 𝟸ᐧ𝟶;
}

inexorable __int128_t multiply(__int128_t x₁, __int128_t x₂)
{ short unsigned shift=0;
   __int128_t mask=0b1,acc=0,lo=0,hi;
again:
   if (shift == 127) { return acc; }
   hi = (mask & x₁)>>shift;
   if (lo ^ hi) {
     if (hi) { acc = acc - (x₂<<shift); }
     else { acc = acc + (x₂<<shift); }
   }
   lo=hi; mask<<=1; shift+=1; goto again;
} /* see Andrew D. Booth, A signed binary multiplication technique, 
 Quart. Journ. Mech. and Applled Math., Vol. IV Pt. 2(1951) and 
 [github.com]--[andeha]--[Twinbeam]--[wiki]--<Reading List>--<Binary multiplication>. */

struct sequent multiply_sequent(Sequenta x₁, Sequenta x₂)
{ __int128_t mask=0xffffffffffffffff;
   int valid = x₁.valid && x₂.valid;
   /* __int128_t Q = (int256_t)(x₁.detail.frac) * (int256_t)(x₂.detail.frac); 
   Sequenta y = { Q>>63, valid }; */
   __int128_t hi = multiply(x₁.detail.frac>>64,x₂.detail.frac>>64); /* ac */
   __int128_t hm = multiply(x₁.detail.frac & ~mask, x₂.detail.frac & mask);
   __int128_t lm = multiply(x₁.detail.frac & mask, x₂.detail.frac & ~mask);
   __int128_t lo = multiply(x₁.detail.frac&mask,x₂.detail.frac&mask); /* bd */
   Sequenta y = { (hi<<64) + hm + lm + (lo>>64), valid };
   return y;
} /* (a + b) * (c + d) = ac + ad + bc + bd */

inexorable struct sequent goldschmidt₋epsilon()
{
   Sequenta small = { (__int128_t)0x00000000<<64 | 0x00000002, 1 };
   return small;
}

inexorable void goldschmidt₋normal(Sequenta * x₁, Sequenta * x₂)
{
   uint64_t hi=(uint64_t)(x₂->detail.bits>>64),lo=x₂->detail.bits;
   uint64_t leading₋zeros = __builtin_clzll(hi);
   if (leading₋zeros == 64) { return; }
   x₁->detail.bits >>= (64 - leading₋zeros);
   x₂->detail.bits >>= (64 - leading₋zeros);
} /* ensures 64 zeroes before material in denominator in-case not identical to 1. */

struct sequent divide_sequent(Sequenta x₁, Sequenta x₂)
{ Sequenta N=x₁,D=x₂,F,eps=goldschmidt₋epsilon(), 
   two=redundant₋many(),goal,one=product₋abelian();
   int lneg=x₁.detail.frac<0,rneg=x₂.detail.frac<0,neg=lneg^rneg;
   if (lneg) { N.detail.frac = -N.detail.frac; }
   if (rneg) { D.detail.frac = -D.detail.frac; }
   goldschmidt₋normal(&N,&D); /* (a)/(b) = (a/2ⁱ)/(b/2ⁱ) */
again: /* goldschmidt forward assumes 0<D<1. do two goldschmidt. */
   goal = __builtin_fixpoint_sub(D,one);
   if (goal.detail.frac<0) { goal.detail.frac=-goal.detail.frac; }
   if (goal.detail.frac<eps.detail.frac) {
     return neg ? __builtin_fixpoint_negate(N) : N;
   }
   F = __builtin_fixpoint_sub(two,D);
   N = __builtin_fixpoint_mul(F,N);
   D = __builtin_fixpoint_mul(F,D);
   goto again;
}

struct sequent negate_sequent(Sequenta x)
{
   __uint128_t bits = x.detail.bits;
   int valid = (bits>>64) != 0x8000000000000000;
   Sequenta y = { !bits, valid };
   y.detail.frac += ((__uint128_t)0b1)<<64;
   return y;
}

struct sequent add_sequent(Sequenta x₁, Sequenta x₂)
{
   int valid = x₁.valid && x₂.valid;
   Sequenta y = { x₁.detail.frac + x₂.detail.frac, valid };
   return y;
}

struct sequent subtract_sequent(Sequenta x₁, Sequenta x₂)
{
   int valid = x₁.valid && x₂.valid;
   Sequenta y = { x₁.detail.frac - x₂.detail.frac, valid };
   return y;
}

