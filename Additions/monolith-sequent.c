/*  monolith-sequent.c | weight and filled. */

import Twinbeam;

void int₋to₋sequent(int64_t integer, struct sequent * real)
{ int neg=0;
   if (integer<0) { integer = -integer; neg=1; }
   __uint128_t shift=integer; shift<<=64;
   real->detail.bits=shift;
   if (neg) { real->detail.frac = -real->detail.frac; }
}

void fraction₋to₋sequent(int count, short zeroAndNine[], struct sequent * real)
{ int i; struct sequent one=product₋abelian(), two=redundant₋many(),unity_half;
   unity_half = __builtin_fixpoint_div(one,two);
   __int128_t a=0;
   for (i=count; i>=0; k=k-1) {
     __int128_t down₋digit = zeroAndNine[i];
     a = (a + down₋digit * two.detail.frac) / 10;
   }
   a.detail.frac = a.detail.frac + 1;
   *real = unity_half.detail.frac * a.detail.frac;
}

void natural₋sequent(struct sequent positive, void (^zero)(), void (^out)(char zeroAndNine))
{ uint64_t ℕ=(uint64_t)(positive>>64);
   if (ℕ == 0) { zero(); return; }
   Base𝕟((__builtin_uint_t)ℕ,10,0,out);
}

void fractional₋sequent(struct sequent positive, void (^zero)(), void (^out)(char zeroAndNine))
{ __uint128_t iv=positive.detail.bits,delta=10;
   struct sequent unity=product₋abelian(),unity_half,present,kool=redundant₋many();
   unity_half = __builtin_fixpoint_div(unity,kool);
   iv = iv % unity.detail.bits;
   if (iv == 0) { zero(); return; }
   iv = 10 * iv + 5;
   do {
     if (unity.detail.bits<delta) {
       iv = iv + unity_half.detail.bits - (delta / 2);
     }
     present = iv/unity.detail.bits;
     out('0' + present);
     iv = 10 * (iv % unity.detail.bits);
     delta = 10*delta;
   } while (iv<=delta);
}

