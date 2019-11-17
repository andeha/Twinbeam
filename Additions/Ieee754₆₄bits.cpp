/*  Ieee754₆₄bits.cpp | Addition. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

#pragma mark - Converting a 64-bit IEEE 754 base-2 to text

enum { Bignum_prec=157, magic_offset=2112, origin=37 };
typedef structᵢ { int a; int b; Tetra dat[Bignum_prec]; } Bignum;

inexorable
void
print_float(
  Octa x,
  void (^digits)(bool neg, int e, const char *s),
  void (^zero)(), void (^inf)(), void (^nan)()
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
            if (f->a == f->b) { /* the result is zero */
                f->a = f->b = Bignum_prec - 1; f->dat[Bignum_prec - 1] = 0;
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
        if (!e) { zero(); return; }
        if (e == 0x7ff) { inf(); return; }
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
    
    k = (magic_offset - e) / 28;
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
            Bignum_times_ten(&ff);
            Bignum_times_ten(&gg);
            for (j = '0'; Bignum_compare(&ff, &tt) >= 0; j++) {
                Bignum_dec(&ff, &tt, 0x10000000);
                Bignum_dec(&gg, &tt, 0x10000000); }
            if (Bignum_compare(&gg, &tt) >= open) break;
            *p++ = j;
            if (ff.a == Bignum_prec - 1 && !open)
                goto done;
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
    
    *p = '\0';
    
    digits(neg, e, s);
}

void
CastᵈᵇˡToText( 
  double value,
  void (^digits)(bool neg, int e, const char * 𝟶to𝟿s),
  void (^zero)(), void (^inf)(), void (^nan)()
)
{
    octa y; y.base₂ = value;
    Octa x; x.h = y.unsigned_little_endian.mst; x.l = y.unsigned_little_endian.lst;
    print_float(x, digits, zero, inf, nan);
}

