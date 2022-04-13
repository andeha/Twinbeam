/*  anglosax-sequent.c | on another planet and quotas of 1/2⁻⁶³. */

import Twinbeam;

struct sequent product₋abelian()
{
   struct sequent 𝟷ᐧ𝟶 = { (__int128_t)0x00000001<<64 | 0x00000000, 1 };
   return 𝟷ᐧ𝟶;
}

struct sequent piano₋ten()
{
   struct sequent 𝟷𝟶ᐧ𝟶 = { (__int128_t)0x0000000a<<64 | 0x00000000, 1 };
   return 𝟷𝟶ᐧ𝟶;
}

struct sequent negative₋infinity()
{
   struct sequent neginf = { (__int128_t)0x80000000<<64 | 0x00000000, 1 };
   return neginf;
}

struct sequent positive₋infinity()
{
   struct sequent posinf = { (__int128_t)0x7fffffff<<64 | 0xffffffff, 1 };
   return posinf;
}

struct sequent accumulative₋zero()
{
   struct sequent zero = { (__int128_t)0x00000000<<64 | 0x00000000, 1 };
   return zero;
}

struct sequent redundant₋many()
{
   struct sequent 𝟸ᐧ𝟶 = { (__int128_t)0x00000002<<64 | 0x00000000, 1 };
   return 𝟸ᐧ𝟶;
}

inexorable __int128_t multiply(__int128_t x₁, __int128_t x₂)
{ short unsigned shift=0;
   __int128_t mask=0b1,acc=0,lo=0,hi;
again:
   if (shift == 127) { return acc; }
   hi = (mask & x₁)>>shift;
   if (lo ^ hi) {
     if (hi) { acc = acc - x₂<<shift; }
     else { acc = acc + x₂<<shift; }
   }
   lo=hi; mask<<=1; shift+=1;
   goto again;
}

struct sequent multiply_sequent(struct sequent x₁, struct sequent x₂)
{ struct sequent y; __int128_t integer, decimals, mask=0xffffffffffffffff;
   integer=multiply(x₁.detail.frac>>64,x₂.detail.frac>>64);
   decimals=multiply(x₁.detail.frac & mask, x₂.detail.frac & mask);
   int valid = x₁.valid && x₂.valid;
   y.detail.frac = ((integer<<64) | (decimals>>64));
   y.valid=valid;
}

struct sequent goldschmidt₋epsilon()
{
   struct sequent small = { (__int128_t)0x00000000<<64 | 0x00000002, 1 };
   return small;
}

void goldschmidt₋normal(struct sequent * x₁, struct sequent * x₂)
{
   
} /* ensures 64 zeroes before material in-case not identical to 1. */

struct sequent divide_sequent(struct sequent x₁, struct sequent x₂)
{ struct sequent N=x₁,D=x₂,F,eps=goldschmidt₋epsilon(), 
   two=redundant₋many(),goal,one=product₋abelian();
   int lneg=x₁.detail.frac<0,rneg=x₂.detail.frac<0,neg=lneg^rneg;
   if (lneg) { N.detail.frac = -N.detail.frac; }
   if (rneg) { D.detail.frac = -D.detail.frac; }
   goldschmidt₋normal(&N,&D);
again: /* goldschmidt forward assumes 0<D<1.*/
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

struct sequent negate_sequent(struct sequent x)
{
   __uint128_t bits = x.detail.bits;
   struct sequent y; y.detail.valid=1;
   y.detail.bits = !bits;
   y.detail.frac += 1;
   return y;
}

struct sequent add_sequent(struct sequent x₁, struct sequent x₂)
{
   int valid = x₁.valid && x₂.valid;
   struct sequent y = { x₁.detail.frac + x₂.detail.frac, valid };
   return y;
}

struct sequent subtract_sequent(struct sequent x₁, struct sequent x₂)
{
   int valid = x₁.valid && x₂.valid;
   struct sequent y = { x₁.detail.frac - x₂.detail.frac, valid };
   return y;
}

struct sequent less_than(struct sequent x₁, struct sequent x₂)
{
   return x₁.detail.frac < x₂.detail.frac;
}

