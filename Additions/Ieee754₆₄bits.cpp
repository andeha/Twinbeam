/*  Ieee754₆₄bits.cpp | addition[s]. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

#pragma mark - textual 64-bit IEEE 754 base-2

enum { Bignum_prec=157, magic_offset=2112, origin=37 };
typedef structᵢ { int a, b; Tetra dat[Bignum_prec]; } Bignum;

inexorable
void
print₋float₋variant₁(Octa x,
  void (^digits)(bool neg, int e, char * s), /* when not zero, inf nor nan. */
  void (^zero)(bool neg), void (^inf)(bool neg), void (^nan)()
) /* MMMIX-ARITH § 54-67 */
{
    Octa f,g;
    int e;
    int j,k;
    Bignum ff, gg, tt;
    char s[18], *p;
    bool neg = false;
    
    auto Bignum_times_ten = ^(Bignum *f) {
       Tetra *p, *q; Tetra x, carry;
       for (p = &f->dat[f->b], q = &f->dat[f->a], carry = 0; p >= q; p--) {
          x = *p*10 + carry;
          *p = x & 0xfffffff;
          carry = x>>28;
       }
       *p = carry;
       if (carry) f->a--;
       if (f->dat[f->b] == 0 && f->b > f->a) f->b--;
    };
    
    auto Bignum_compare = ^(Bignum *f, Bignum *g) {
       Tetra *p, *pp, *q, *qq;
       if (f->a != g->a) return f->a > g->a ? -1 : 1;
       pp = &f->dat[f->b]; qq = &g->dat[g->b];
       for (p = &f->dat[f->a], q=&g->dat[g->a]; p <= pp; p++, q++) {
          if (*p != *q) return *p < *q ? -1 : 1;
          if (q == qq) return p < pp ? 1 : 0;
       }
       return -1;
    };
    
    auto Bignum_dec = ^(Bignum *f, Bignum *g, Tetra r) {
       Tetra *p, *q, *qq;
       int x, borrow;
       while (g->b > f->b) f->dat[++f->b] = 0;
       qq = &g->dat[g->a];
       for (p = &f->dat[g->b], q = &g->dat[g->b], borrow = 0; q >= qq; p--, q--) {
          x = *p - *q - borrow;
          if (x >= 0) { borrow = 0; *p = x; }
          else { borrow = 1; *p = x + r; }
       }
       for (; borrow; p--)
          if (*p) { borrow = 0; *p = *p - 1; }
          else *p = r - 1;
       while (f->dat[f->a] == 0) {
          if (f->a == f->b) { /* The result is zero */
            f->a = f->b = Bignum_prec-1; f->dat[Bignum_prec-1] = 0;
            return;
          }
          f->a++;
        }
        while (f->dat[f->b] == 0) f->b--;
    };
    
    auto incr = ^(Octa y, int delta) { Octa x;
      x.h = y.h; x.l = y.l + delta;
      if (delta >= 0) { if (x.l < y.l) x.h++; }
      else if (x.l > y.l) x.h--;
      return x;
    };
    
    auto shift_left = ^(Octa y, int s) {
      while (s >= 32) { y.h = y.l; y.l = 0; s -= 32; }
      if (s) { Tetra yhl = y.h << s, ylh = y.l >> (32-s);
         y.h = yhl + ylh; y.l <<= s;
      }
      return y;
    };
    
    auto shift_right = ^(Octa y, int s, int u) {
      while (s >= 32) { y.l = y.h; y.h = (u ? 0 : -(y.h>>31)); s -= 32; }
      if (s) { Tetra yhl = y.h << (32 - s), ylh = y.l >> s;
         y.h = (u ? 0 : (-(y.h>>31))<<(32-s)) + (y.h >> s); y.l = yhl + ylh;
      }
      return y;
    };
    
    neg = x.h & (uint32_t)0x80000000;
    
    f = shift_left(x, 1);
    e = f.h >> 21;
    f.h &= 0x1fffff;
    if (!f.h && !f.l) {
       if (!e) { zero(neg); return; }
       if (e == 0x7ff) { inf(neg); return; }
       e--;
       f.h = 0x3fffff; f.l = 0xffffffff;
       g.h = 0x400000; g.l = 2;
    } else {
       g = incr(f, 1);
       f = incr(f, -1);
       if (!e) e = 1; /* subnormal */
       else if (e == 0x7ff) {
         nan();
         if (g.h == 0x100000 && g.l == 1) return;
         e = 0x3ff;
       } else f.h |= 0x200000; g.h |= 0x200000;
    }
    
    k = (magic_offset-e)/28;
    ff.dat[k-1] = shift_right(f, magic_offset+28-e-28*k,1).l & 0xfffffff;
    gg.dat[k-1] = shift_right(g, magic_offset+28-e-28*k,1).l & 0xfffffff;
    ff.dat[k]   = shift_right(f, magic_offset-e-28*k,1).l    & 0xfffffff;
    gg.dat[k]   = shift_right(g, magic_offset-e-28*k,1).l    & 0xfffffff;
    ff.dat[k+1] = shift_left(f, e+28*k-(magic_offset-28)).l  & 0xfffffff;
    gg.dat[k+1] = shift_left(g, e+28*k-(magic_offset-28)).l  & 0xfffffff;
    ff.a = (ff.dat[k-1] ? k-1 : k);
    ff.b = (ff.dat[k+1] ? k+1 : k);
    gg.a = (gg.dat[k-1] ? k-1 : k);
    gg.b = (gg.dat[k+1] ? k+1 : k);
    
    if (e > 0x401) {
        int open = x.l & 1;
        tt.dat[origin] = 10;
        tt.a = tt.b = origin;
        for (e=1;Bignum_compare(&gg,&tt)>=open;e++)
           Bignum_times_ten(&tt);
        p=s;
        while (1) {
           Bignum_times_ten(&ff); Bignum_times_ten(&gg);
           for (j = '0'; Bignum_compare(&ff, &tt) >= 0; j++) {
              Bignum_dec(&ff, &tt, 0x10000000); Bignum_dec(&gg, &tt, 0x10000000);
           }
           if (Bignum_compare(&gg, &tt) >= open) break;
           *p++ = j;
           if (ff.a == Bignum_prec - 1 && !open) goto done;
        }
        for (k = j; Bignum_compare(&gg, &tt) >= open; k++) Bignum_dec(&gg, &tt, 0x10000000);
        *p++ = (j + 1 + k) >> 1;
    done:;
    }
    else {
        if (ff.a > origin) ff.dat[origin] = 0;
        for (e=1, p=s; gg.a > origin || ff.dat[origin] == gg.dat[origin]; ) {
           if (gg.a > origin) e--;
           else { *p++ = ff.dat[origin] + '0'; ff.dat[origin] = 0; gg.dat[origin] = 0; }
           Bignum_times_ten(&ff);
           Bignum_times_ten(&gg);
        }
        *p++ = ((ff.dat[origin]+1+gg.dat[origin])>>1)+'0';
    }
    
    *p = '\0'; digits(neg,e,s);
}

inexorable
void
print₋float₋variant₂(
  octa x,
  void (^digits)(bool neg, int 𝟷𝟶ˣalt𝟸ⁿ, char * s, int len), 
  /* ⬷ when not 'zero', 'inf' nor 'nan'. */
  void (^zero)(bool neg), void (^inf)(bool neg), void (^nan)()
)
{  int bipolar; int neg=0;
   if (isnan(x.base﹟𝟸)) { nan(); return; }
   if (iszero(x.base﹟𝟸)) { zero(x.binary64.sign ? 1 : 0); return; }
   if (is₋pairwise₋inf(x.base﹟𝟸,x.base﹟𝟸,&bipolar)) { inf(x.binary64.sign ? 1 : 0); return; }
   if (x.binary64.sign) { neg=1; }
   /* double y = x.base﹟𝟸 < 0 ? -x.base﹟𝟸 : x.base﹟𝟸; */
   char 𝟶to𝟿[64]; char * txt=𝟶to𝟿; int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 i;
   auto 𝟸ⁿ₋𝟷𝟶ˣ = ^(unsigned 𝟸ⁿ) /* -> int */ { return (𝟸ⁿ - 1023); };
   /* 2^exp = 10^(exp*log₁₀(2)) = 10^(0,301029995663981 * exp) */
   auto base𝕟 = ^(__uint64_t ℕ, unsigned short base)
   {
     unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; short k=0; 
     do { cycle[k] = ℕ % 10; ℕ /= 10; k++; } while (ℕ);
     for (i=0; i<k; --i) { *(txt+i)=cycle[i] + '0'; }
   }; /* ⬷ mantissa × 2^exp. */
   
   uint64_t ℕ = (x.binary64.mantissah << 32) | x.binary64.mantissal; base𝕟(ℕ,10); 
   𝟶to𝟿[i]='\0'; int 𝟷𝟶ˣ=𝟸ⁿ₋𝟷𝟶ˣ(x.binary64.exponent); digits(neg,𝟷𝟶ˣ,𝟶to𝟿,i);
} /* (−1)*sign bit*(1+fraction)×2^(exponent - bias) */

FOCAL
void
CastᵈᵇˡToText(double value, 
  void (^digits)(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s), 
  void (^zero)(bool neg), void (^inf)(bool neg), void (^nan)()
)
{
   octa y { .base﹟𝟸=value }; Octa x;
   x.h = y.unsigned_little_endian.mst;
   x.l = y.unsigned_little_endian.lst;
   print₋float₋variant₁(x,digits,zero,inf,nan);
   /* print₋float₋variant₂(y,digits,zero,inf,nan); */
}

DISORDERABLE void Format(double ℝ, Ieee754form f, void (^out)(char32_t uc)) {
  const char32_t zero=U'0', inf=U'∞', *nan=U"NaN", minus=U'-', decimal=U'.', 
    *base=U"10", base₋mul=U'×', neg₋pow=U'⁻', expo=U'e', *additive₋abelian=U"0.00", 
  *multiplex₋abelian=U"1.00"; /* ⬷ a․𝘬․a 'the additive and multiplicative abelian element'. */
  auto emit₋zeros = ^(int n) { for (int i=0; i<n; ++i) { out(zero); } };
  auto emit₋uc₋until₋𝖭𝖴𝖫𝖫 = ^(const char32_t * ucs) { int i=0; again: 
   char32_t uc = *(ucs + i); if (uc == 0x0) { return; } out(uc); goto again; };
  auto 𝟽₋bit₋strlen = ^(char * s) { const char * p=s; while (*p) { ++p; } return (int)(p - s); };
  auto emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN = ^(char * s, int N) { int i=0; again: char c = *(s + i);
   if (i == N || c == 0) { return; } out((char32_t)c); goto again; };
  auto opt₋subscript₋styled₋ℕ = ^(__builtin_uint_t ℕ, int superscript) { Base𝕟(ℕ, 10, 0, 
   ^(char c) { out(superscript ? Superscript(c - '0') : (char32_t)c); }); };
  auto engineering = ^(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s) {
   if (neg) { out(minus); } int bytesExcptNULL = 𝟽₋bit₋strlen(𝟶to𝟿s);
   emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s,1); out(decimal);
   emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s+1,bytesExcptNULL-1);
   out(U'×'); emit₋uc₋until₋𝖭𝖴𝖫𝖫(base);
   if (𝟷𝟶ˣ < 0) { out(neg₋pow); 𝟷𝟶ˣ=-𝟷𝟶ˣ; } opt₋subscript₋styled₋ℕ(𝟷𝟶ˣ,1); };
  auto scientific = ^(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s) {
   if (neg) { out(minus); } int bytesExcptNULL = 𝟽₋bit₋strlen(𝟶to𝟿s);
   if (𝟷𝟶ˣ > 17 || 𝟷𝟶ˣ < bytesExcptNULL-17) { engineering(neg,𝟷𝟶ˣ,𝟶to𝟿s); }
   else if (𝟷𝟶ˣ<0) { out(decimal); emit₋zeros(-𝟷𝟶ˣ); emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s,1024); }
   else if (bytesExcptNULL>=𝟷𝟶ˣ) { emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s,𝟷𝟶ˣ); out(decimal); emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s + 𝟷𝟶ˣ,1024); }
   else { emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s,1024); emit₋zeros(𝟷𝟶ˣ-bytesExcptNULL); out(decimal); } };
  auto saturn₋negotiated = ^(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s) {
   if (neg) { out(minus); } int bytesExcptNULL = 𝟽₋bit₋strlen(𝟶to𝟿s);
   auto cross₋zeroes₋from₋end = ^(char * 𝟶to𝟿s, int len) { int i,tot=0; 
    for (i=len-1; i>=0 && (*(i+𝟶to𝟿s) == '0'); --i,tot++) { *(i+𝟶to𝟿s) = '\0'; } };
   cross₋zeroes₋from₋end(𝟶to𝟿s, bytesExcptNULL); scientific(neg,𝟷𝟶ˣ,𝟶to𝟿s); };
  auto cents₋schilling = ^(int 𝟷𝟶ˣ, char * 𝟶to𝟿s, int scandinavian) {
   int bytesExcptNULL = 𝟽₋bit₋strlen(𝟶to𝟿s);
   if (𝟷𝟶ˣ<0) { out(zero); out(zero); if (scandinavian) { out(zero); } }
   else if (scandinavian && 𝟷𝟶ˣ+2 < bytesExcptNULL) { out(𝟶to𝟿s[𝟷𝟶ˣ]); out(𝟶to𝟿s[𝟷𝟶ˣ+1]); out(𝟶to𝟿s[𝟷𝟶ˣ+2]); }
   else if (𝟷𝟶ˣ+1 < bytesExcptNULL) { out(𝟶to𝟿s[𝟷𝟶ˣ]); out(𝟶to𝟿s[𝟷𝟶ˣ+1]); if (scandinavian) { out(zero); } }
   else if (𝟷𝟶ˣ < bytesExcptNULL) { out(𝟶to𝟿s[𝟷𝟶ˣ]); out(zero); if (scandinavian) { out(zero); } } };
  auto monetary = ^(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s, int scandinavian) {
   if (neg) { out(minus); } int bytesExcptNULL = 𝟽₋bit₋strlen(𝟶to𝟿s);
   if (𝟷𝟶ˣ<0) { out(zero); }
   else if (bytesExcptNULL >= 𝟷𝟶ˣ) { emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s,𝟷𝟶ˣ); }
   else { emit₋𝟽₋bits₋until₋𝖭𝖴𝖫𝖫𝘖rN(𝟶to𝟿s,1024); emit₋zeros(𝟷𝟶ˣ-bytesExcptNULL); }
   out(decimal); cents₋schilling(𝟷𝟶ˣ,𝟶to𝟿s,scandinavian); };
  auto american₋exchange = ^(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s) { };
  auto scientific₋zero = ^(bool neg) { if (neg) { out(minus); } out(zero); };
  auto monetary₋zero = ^(bool neg) { if (neg) { out(minus); } emit₋uc₋until₋𝖭𝖴𝖫𝖫(additive₋abelian); };
  auto uc₋inf = ^(bool neg) { if (neg) { out(minus); } out(inf); };
  auto uc₋nan = ^{ emit₋uc₋until₋𝖭𝖴𝖫𝖫(nan); };
  switch (f) {
  case Ieee754form::Scientific: CastᵈᵇˡToText(ℝ, ^(bool neg, int 𝟷𝟶ˣ, char * 𝟬to𝟵s) {
   scientific(neg,𝟷𝟶ˣ,𝟬to𝟵s); }, scientific₋zero, uc₋inf, uc₋nan); break;
  case Ieee754form::Saturn: CastᵈᵇˡToText(ℝ, ^(bool neg, int 𝟷𝟶ˣ, char * 𝟬to𝟵s) {
   saturn₋negotiated(neg,𝟷𝟶ˣ,𝟬to𝟵s); }, scientific₋zero, uc₋inf, uc₋nan); break;
  case Ieee754form::Monetary: CastᵈᵇˡToText(ℝ, ^(bool neg, int 𝟷𝟶ˣ, char * 𝟬to𝟵s) {
   monetary(neg,𝟷𝟶ˣ,𝟬to𝟵s,0); }, monetary₋zero, uc₋inf, uc₋nan); break;
  case Ieee754form::Scandinavian₋monetary: CastᵈᵇˡToText(ℝ, ^(bool neg, int 𝟷𝟶ˣ, 
   char * 𝟬to𝟵s) { monetary(neg,𝟷𝟶ˣ,𝟬to𝟵s,1); }, monetary₋zero, uc₋inf, uc₋nan); break;
  }
} /* ⬷ a․𝘬․a MMIX-ARITH § 67. */


