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
{ struct sequent one=product₋abelian(),two=redundant₋many(),unity_half = 
    __builtin_fixpoint_div(one,two); __int128_t a=0;
   for (int j=count-1; j>=0; j=j-1) { /* ␏ compute bits⁻¹₋mul(zeroAndNine,two) ␎ */
     __int128_t down₋digit = zeroAndNine[j];
     a = (a + down₋digit * two.detail.frac) / 10; /* ␏ two-sequent is shifted 64 to the left. ␎ */
   }
   a = a + 1; /* ␏ least significant 128-bit toggles by addition and 'rounds to nearest'. ␎ */
   real->detail.frac = unity_half.detail.frac * a;
}

void natural₋sequent(struct sequent positive, 
 void (^out)(int count, char zeroAndNine[], int is₋zero))
{ uint64_t cycle[64] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   char text[64]; uint64_t x=positive.detail.bits>>64,i=0,j=0;
   if (x==0) { out(0,text,1); return; }
   do { cycle[i]=x%10,i+=1,x/=10; } while (x!=0);
   for (j=0; j<i; j+=1) { text[j]=cycle[i-j-1]; }
   out(j,text,0);
}

void fractional₋sequent(struct sequent positive, 
 void (^out)(int count, char zeroAndNine[], int is₋zero))
{ __uint128_t iv=positive.detail.bits,delta=10; int j;
   struct sequent unity=product₋abelian(),unity_half,present,kool=redundant₋many();
   unity_half = __builtin_fixpoint_div(unity,kool); char text[64];
   iv = iv % unity.detail.bits;
   iv = 10 * iv + 5;
   if (iv == 5) { out(0,text,1); return; }
   do {
     if (unity.detail.bits<delta) {
       iv = iv + unity_half.detail.bits - (delta / 2);
     }
     present.detail.frac = iv/unity.detail.bits;
     text[j] = '0' + present.detail.frac;
     iv = 10 * (iv % unity.detail.bits);
     delta = 10*delta; j+=1;
   } while (iv<=delta); /* --<icati-irrevers.c>, present-instant. */
   out(j,text,0);
}

