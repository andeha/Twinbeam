/*  𝙋𝙧𝙞𝙣𝙩⁺.cpp | 🗞 - Printing and no escapes. */

#include <Twinbeam.h>

/* Compile with xcrun clang @ccargs_macosᵧ -o Print⁺ '🥽 ᷣ𝙋𝙧𝙞𝙣𝙩⁺.cpp'   \
  ../../Source/Releases/libTwinbeam_macOS.a ../../Source/llvmʳᵗ³.cpp */

/* clang++ -g -o Print⁺ -I ../../ -fno-rtti -fblocks -fno-exceptions   \
    -std=c++2a '🥽 ᷣ𝙋𝙧𝙞𝙣𝙩⁺.cpp' ../../Source/llvmʳᵗ³.cpp ../../Source/Utf8.cpp \
    ../../Source/System.cpp */

DISORDERABLE extern void CastᵈᵇˡToText(double value,
  void (^digits)(bool neg, int e, const char *𝟶to𝟿s),
  void (^zero)(), void (^inf)(), void (^nan)()) { zero(); }

#define ⁺⁼PrintArgAndPop(C,ARG)                                             \
/* DISORDERABLE */ auto printArgAndPop = ^(char32_t c,                      \
      __builtin_va_list arg) {                                              \
    const Argᴾ a = __builtin_va_arg(arg, Argᴾ);                             \
    switch (a.kind) {                                                       \
    case 1: out𝕫(a.value.d); break;                                         \
    case 2: out𝕟(a.value.x); break;                                         \
    case 3: ᵇⁱⁿᵃʳʸout(a.value.b); break;                                      \
    case 4: streamout_utf8(a.value.utf8); break;                            \
    case 5: streamout_unicodes(a.value.ucs.tetras, a.value.ucs.unicodes); break; \
    case 6: out₂((const char *)&(a.value.c), 1); break;                     \
    case 7: streamout_unicode(a.value.uc); break;                           \
    case 9: out𝕕(a.value.f₁); break;                                        \
    case 8: out𝕕(double(a.value.f₂)); break;                                \
    case 11: out¹²⁸𝕫(a.value.d); break;                                     \
    case 12: out¹²⁸𝕟(a.value.d); break;                                     \
    case 13: out𝕫(a.value.d); break;                                        \
    default: /* if (a.kind >= 0) imprint[a.kind](a); else */                \
      streamout_unicode(U'?'); break;                                       \
    }                                                                       \
}; printArgAndPop(C,ARG) /* Lexical lambda implicits: `out𝕫`, `out𝕟`, 
  `ᵇⁱⁿᵃʳʸout`, `streamout_utf8`, `streamout_unicodes`, `out₂`, 
  `streamout_unicode`, `out𝕕`, `out¹²⁸𝕫` and `out¹²⁸𝕟`. */

Argᴾ ﹟d(__builtin_int_t d) { return Argᴾ { .value.d=d, 1 }; }
Argᴾ ﹟x(__builtin_uint_t x) { return Argᴾ { .value.x=x, 2 }; }
Argᴾ ﹟b(__builtin_uint_t b) { return Argᴾ { .value.b=b, 3 }; }
Argᴾ ﹟s(const char * utf8) { return Argᴾ { .value.utf8=utf8, 4 }; }
Argᴾ ﹟S(int tetras, const char32_t * uc) { return Argᴾ { .value.ucs={uc,tetras}, 5 }; }
Argᴾ ﹟c(char c) { return Argᴾ { .value.c=c, 6 }; }
Argᴾ ﹟C(char32_t C) { return Argᴾ { .value.uc=C, 7 }; }
Argᴾ ﹟U(__uint128_t U) { return Argᴾ { .value.U=U, 11 }; }
Argᴾ ﹟I(__int128_t I) { return Argᴾ { .value.I=I, 12 }; }
Argᴾ ﹟reᵍ(__builtin_int_t r) { return Argᴾ { .value.d=r, 13 }; } /* Print register 0-31. */

/* …and for the IEEE754's in --<Additions.h> */
MACRO Argᴾ ﹟F(double f) { return Argᴾ { .value.f₁=f, 9 }; }
MACRO Argᴾ ﹟F(float r) { return Argᴾ { .value.f₂=r, 8 }; }
typedef long double ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾;
typedef ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾 maxprec;
Argᴾ ﹟F(maxprec rᵋ) { union Shim { ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾 f; uint64_t 
  pair[2]; } rᵋ₂ = { .f=rᵋ }; return Argᴾ { .value.pair = { rᵋ₂.pair[0],
  rᵋ₂.pair[1] }, 10 }; }

#pragma mark - …and the actual code

inexorable
void
Base𝕟(
  __uint128_t ℕ, 
  unsigned short base, 
  unsigned short digitsOr0, 
  void (^out)(char 𝟶to𝟿)
)
{
    auto 𝟶to𝖥 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[128] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 
      𝟶to𝖥(cycle[k], out); } }
    else { k = 127; while (cycle[k] == 0 && k > 0) { k--; }
       for (; k >= 0; k--) { 𝟶to𝖥(cycle[k], out); }
    }
}

inexorable void Base𝕫(__int128_t ℤ, unsigned short base, unsigned short 
  digitsOr0, void (^out)(char 𝟶to𝟿and₋)) { if (ℤ < 0) { out('-'); ℤ = -ℤ; }
  Base𝕟((__builtin_uint_t)ℤ, base, digitsOr0, out); };

inexorable
int 
print⁺⁺(
  void (^out)(uint8_t * utf8s, short unsigned bytes),
  const char * utf8format,
  __builtin_va_list arg
)
{  __builtin_int_t i=0, incr; short followers; char32_t uc;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedSymbolsExcept0=0;
    auto out₂ = ^(const char * utf8s, uint16_t bytes) { out((uint8_t *)utf8s, bytes); printedSymbolsExcept0 += bytes; };
    auto out𝕫 = ^(__builtin_int_t x) { Base𝕫(x, 10, 0, ^(char s) { out₂(&s, 1);  }); };
    auto out𝕟 = ^(__builtin_uint_t x) { Base𝕟(x, 16,
#ifdef __x86_64__
      16
#elif defined __mips__
       8
#endif
      , ^(char s) { out₂(&s, 1); }); };
    auto ᵇⁱⁿᵃʳʸout = ^(__builtin_uint_t b) { Base𝕟(b, 2,
#ifdef __x86_64__
       64
#elif defined __mips__
       32
#endif
      , ^(char s) { out₂(&s, 1); }); };
    auto streamout_utf8 = ^(const char * utf8) { char * p=(char *)utf8; while (*p++) { out₂(p, 1); } };
    /* #ifndef AVOID_IEEE754 */
    auto out𝕕 = ^(double ℝ) { const char *zero="0", *inf="∞", *nan="NaN", 
      *minus="-", *decimal="."; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int count=0;
      CastᵈᵇˡToText(ℝ, ^(bool neg, int e, const char * 𝟶to𝟿s) {
         auto strlen⁷ᵇⁱᵗ = ^(const char * s) { const char * p; 
           for (p = s; *p; ++p) { } return p - s; };
         if (neg) { out₂(minus, 1); }
         if (count == e) { out₂(decimal, 1); }
         int bytes = strlen⁷ᵇⁱᵗ(𝟶to𝟿s); out₂(𝟶to𝟿s, bytes); count++; }, 
      ^{ out₂(zero, 1); }, ^{ out₂(inf, 3); }, ^{ out₂(nan, 3); });
    }; /* #endif */
    auto streamout_unicode = ^(char32_t u) { UnicodeToUtf8(u, ^(const uint8_t *p, 
      int bytes) { out₂((const char *)p, bytes); }); };
#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 __attribute__ ((nonnull))
    auto streamout_unicodes = ^(int tetras, const char32_t 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32_t uc = *(unicodes + beam); streamout_unicode(uc); 
      ++beam; } }; /* { int, (bytes, symbols) } */
    auto out¹²⁸𝕫 = ^(__int128_t I) { Base𝕫(I, 10, 0, ^(char 𝟶to𝟿) { out₂(&𝟶to𝟿, 1); }); };
    auto out¹²⁸𝕟 = ^(__uint128_t U) { Base𝕟(U, 10, 0, ^(char 𝟶to𝟿and₋) { out₂(&𝟶to𝟿and₋, 1); }); };
again:
    auto leadOr8Bit = (uint8_t *)utf8format + i;
    if (*leadOr8Bit == 0x0) { goto unagain; }
    followers = Utf8Followers(*leadOr8Bit);
    if (followers < 0) { return -1; }
    incr = followers + 1;
    uc = Utf8ToUnicode(leadOr8Bit, incr);
    if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }
    else if (uc != U'⬚') { streamout_unicode(uc); }
    else { ⁺⁼PrintArgAndPop(uc, arg); }
    i += incr; goto again;
unagain:
    return printedSymbolsExcept0;
}

FOCAL
int
print⁺⁺(const char * utf8format, ...) /* Here all variable args are of the type `Arg`. */
{  int y;
    va_prologue(utf8format);
    extern void (*Putₒ)(uint8_t * utf8s, uint16_t bytes);
    auto out = ^(uint8_t * utf8s, uint16_t bytes) { Putₒ(utf8s, bytes); };
    y = print⁺⁺(out, utf8format, __arg);
    va_epilogue
    return y;
} /* 𝘈․𝘬․a `print`. */

/* FOCAL int 
print⁺⁺(
  void (^out)(uint8_t * utf8s, short unsigned bytes),
  const char32_t *oneblockFormat,
  __builtin_va_list arg
) { } */

FOCAL
int
print⁺⁺(
  void (^out)(uint8_t * utf8s, short unsigned bytes),
  const char * utf8format,
  ...
)
{ int y;
    va_prologue(utf8format);
    y = print⁺⁺(out, utf8format, __arg);
    va_epilogue
    return y;
}

#pragma mark - Main entry point

extern "C" int write(int fd, const void *s, short unsigned b);

int
main(
  int argc,
  const char * argv[]
)
{
    /* Here with the introduction of Unicode `%` becomes redundant, formatting is on the 
        outside and types are checked instead of 'reported' at runtime. */
    
    auto Putₒ2 = ^(uint8_t * utf8s, uint16_t bytes) { write(1, (const void *)utf8s, bytes); };
    print⁺⁺(Putₒ2, "Welcome to print: ⬚ ⬚ ⬚\n", ﹟d(12), ﹟x(12), ﹟F(12.1));
    
    __uint128_t x₁ = 100; __int128_t x₂ = -100;
    print⁺⁺(Putₒ2, "Size of x₁ is ⬚ value is 0x⬚\n", ﹟d(sizeof(x₁)), ﹟U(x₁));
    print⁺⁺(Putₒ2, "Size of x₂ is ⬚ value is ⬚\n", ﹟d(sizeof(x₂)), ﹟I(x₂));
    
    return 0;
}

#pragma mark - Custom types

/* Copy in --<Fossilate.h> 
Argᴾ ﹟🔗ᵘᵗf⁸(int tetras, const char32_t * pathFileCanonicalᵚ) { 
  return AArgᴾ { .value.ucs={pathFileCanonicalᵚ,tetras}, 13 }; }
#include <Additions/😐🍄-Silmarils/💸.hpp>
Argᴾ ﹟💰(Q567 q) { return Argᴾ { .value.q567=q, 14 }; }
#include <Additions/Fractions.hpp>
Argᴾ ﹟Q31(Q31 q) { return Argᴾ { .value.q31=q, 15 }; }
Argᴾ ﹟Q15(Q15 q) { return Argᴾ { .value.q15=q, 16 }; }
Argᴾ ﹟Q7(Q7 q) { return Argᴾ { .value.q7=q, 17 }; }
#include <Additions/Half.hpp>
Argᴾ ﹟h(half h) { return Argᴾ { .value.h=h, 18 }; }
#include <Additions/temporal.hpp>
Argᴾ ﹟U(Q79 U) { return Argᴾ { .value.U=U, 19 }; }
Argᴾ ﹟U(Q1516 U) { return Argᴾ { .value.U=U, 20 }; }
Argᴾ ﹟🔗ᵚ(int tetras, const char32_t * pathFileCanonicalᵚ) { 
  return Argᴾ { .value.ucs={pathFileCanonicalᵚ,tetras}, 21 }; }
 Copy in --<Fossilate.h> */


