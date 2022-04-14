/*  monolith-sequent.c | weight and filled. */

import Twinbeam;

void int₋to₋sequent(int64_t integer, struct sequent * real)
{ int neg=0;
   if (integer<0) { integer = -integer; neg=1; }
   __uint128_t shift=integer; shift<<=63;
   real->detail.bits=shift;
   if (neg) { real->detail.frac = -real->detail.frac; }
}

void fraction₋to₋sequent(short count, int zeroAndNine[], struct sequent * real)
{ int64_t down₋digit; struct sequent sequent₋down;
   *real = accumulative₋zero();
   for (int i=count; i>=0; k+=1) {
     down₋digit = zeroAndNine[i];
     int₋to₋sequent(down₋digit,&sequent₋down);
   }
} 

void natural₋sequent(struct sequent positive, void (^out)(char zeroAndNine))
{ uint64_t ℕ=(uint64_t)(positive>>64);
   Base𝕟((__builtin_uint_t)ℕ,10,0,out);
}

void fractional₋sequent(struct sequent positive, void (^out)(char zeroAndNine))
{ struct sequent iv=positive,knyck=piano₋ten(),unity=product₋abelian(), 
    unity_half,present,kool=redundant₋many(),castill;
   unity_half = __builtin_fixpoint_div(unity,kool);
   castill = __builtin_fixpoint_div(knyck,kool);
   iv = __builtin_fixpoint_modulo(iv,unity);
   iv = __builtin_fixpoint_mul(knyck,iv);
   iv = __builtin_fixpoint_add(iv,castill);
   do {
     if (less_than(unity,delta)) {
       wiggle = __builtin_fixpoint_modulo(delta,kool);
       extrapol = __builtin_fixpoint_sub(unity_half,wiggle);
       iv = __builtin_fixpoint_add(iv,extrapol);
     }
     present = __builtin_fixpoint_div(iv,unity);
     out('0' + present);
     iv = __builtin_fixpoint_modulo(iv,unity);
     iv = __builtin_fixpoint_mul(knyck,iv);
     delta = __builtin_fixpoint_mul(knyck,delta);
   } while (iv<=delta);
}

