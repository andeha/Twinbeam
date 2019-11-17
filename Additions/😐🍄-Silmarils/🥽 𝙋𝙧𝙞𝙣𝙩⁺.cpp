/*  𝙋𝙧𝙞𝙣𝙩⁺.cpp | 🗞 - Printing and no escapes. */

#include <Twinbeam.h>

/* Compile with xcrun clang @ccargs_macosᵧ -o Print⁺                       \
    ../../Source/llvmʳᵗ³.cpp '🥽 ᷣ𝙋𝙧𝙞𝙣𝙩⁺.cpp' */

/* clang++ -g -o Print⁺ -I ../../ -fno-rtti -fblocks -fno-exceptions       \
    -std=c++2a  ../../Source/Utf8.cpp ../../Source/Memory.cpp              \
    ../../Source/macOS.cpp ../../Source/System.cpp ../../Source/bignum.cpp \
    ../../Source/llvmʳᵗ³.cpp '🥽 ᷣ𝙋𝙧𝙞𝙣𝙩⁺.cpp'  */

DISORDERABLE extern void CastᵈᵇˡToText(double value, void (^digits)(bool neg, 
  int e, const char *𝟶to𝟿s), void (^zero)(), void (^inf)(), void (^nan)()) { 
  zero(); }

DISORDERABLE extern void Anfang(char32_t prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, uint8_t * img) { }

DISORDERABLE extern void ReᵍsPrint(__builtin_uint_t mask) { } /* Print at 
  least 0 to 31 non-high-volatile registers. */

DISORDERABLE extern void Format(double ℝ, void (^out)(char32_t uc)) { 
  CastᵈᵇˡToText(ℝ, ^(bool neg, int e, const char *𝟶to𝟿s) { }, ^{ }, ^{ }, ^{ }); }

int print⁺⁺(void (^out)(uint8_t * utf8s, short unsigned bytes), const char * 
  utf8format, ...);

#define ⁺⁼PrintArgAndPop /* DISORDERABLE */                                 \
  const Argᴾ a = __builtin_va_arg(arg, Argᴾ);                               \
  switch (a.kind) {                                                         \
  case 1: out𝕫(a.value.d); break;                                           \
  case 2: out𝕟(a.value.x); break;                                           \
  case 3: ¹⁰¹¹⁰out(a.value.b); break;                                       \
  case 4: streamout_utf8(a.value.utf8); break;                              \
  case 5: streamout_unicodes(a.value.ucs.tetras, a.value.ucs.unicodes); break; \
  case 6: streamout_char(a.value.c); break;                                 \
  case 7: streamout_unicode(a.value.uc); break;                             \
  case 8: out𝕕(double(a.value.f₂)); break;                                  \
  case 9: out𝕕(a.value.f₁); break;                                          \
  case 10: { Argᴾ::Unicode set = ^(bool anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, \
    void * context) { if (!anfang) { print⁺⁺(out, "⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); } \
    else { Anfang(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, NULL); } }; a.value.λ.scalar(set,       \
    a.value.λ.context); break; }                                            \
  case 11: out¹²⁸𝕟(a.value.U); break;                                       \
  case 12: out¹²⁸𝕫(a.value.I); break;                                       \
  case 13: ReᵍsPrint(a.value.x); break;                                     \
  default: /* if (a.kind >= 0) imprint[a.kind](a); else */                  \
    streamout_unicode(U'?'); break; }

Argᴾ ﹟d(__builtin_int_t d) { return Argᴾ { .value.d=d, 1 }; }
Argᴾ ﹟x(__builtin_uint_t x) { return Argᴾ { .value.x=x, 2 }; }
Argᴾ ﹟b(__builtin_uint_t b) { return Argᴾ { .value.b=b, 3 }; }
Argᴾ ﹟s(const char * utf8) { return Argᴾ { .value.utf8=utf8, 4 }; }
Argᴾ ﹟S(int tetras, char32_t * uc) { return Argᴾ { .value.ucs={uc,tetras}, 5 }; }
Argᴾ ﹟S(int tetras, const char32_t * uc) { return Argᴾ { .value.ucs={Critic(uc),tetras}, 5 }; }
Argᴾ ﹟c(char c) { return Argᴾ { .value.c=c, 6 }; }
Argᴾ ﹟C(char32_t C) { return Argᴾ { .value.uc=C, 7 }; }
Argᴾ ﹟U(__uint128_t U) { return Argᴾ { .value.U=U, 11 }; }
Argᴾ ﹟I(__int128_t I) { return Argᴾ { .value.I=I, 12 }; }
Argᴾ ﹟reᵍs(__builtin_uint_t mask) { return Argᴾ { .value.x=mask, 13 }; }
Argᴾ ﹟λ(Argᴾ::Output scalar, void * context) { return Argᴾ { .value.λ={ scalar, context }, 10 }; }

/* …and for the IEEE754's in --<Additions.h> */
MACRO Argᴾ ﹟F(double f) { return Argᴾ { .value.f₁=f, 9 }; }
MACRO Argᴾ ﹟F(float r) { return Argᴾ { .value.f₂=r, 8 }; }
typedef long double ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾;
typedef ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾 maxprec;
Argᴾ ﹟F(maxprec rᵋ) { union Shim { ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾 f; uint64_t 
  pair[2]; } rᵋ₂ = { .f=rᵋ }; return Argᴾ { .value.pair = { rᵋ₂.pair[0],
  rᵋ₂.pair[1] }, 17 }; }

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
int /* Returns the number of emitted bytes, not the number of emitted frames. */
print⁺⁺(
  void (^out)(uint8_t * utf8s, short unsigned bytes),
  const char * utf8format,
  __builtin_va_list arg
)
{  __builtin_int_t i=0, incr; short followers; char32_t uc;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0; /* bool may𝘖𝘳DidEscape=false; */
    auto out₂ = ^(const char * utf8s, uint16_t bytes) { out((uint8_t *)utf8s, bytes); printedBytesExcept0 += bytes; };
    auto out𝕫 = ^(__builtin_int_t x) { Base𝕫(x, 10, 0, ^(char s) { out₂(&s, 1);  }); };
    auto out𝕟 = ^(__builtin_uint_t x) { Base𝕟(x, 16,
#ifdef __x86_64__
      16
#elif defined __mips__
       8
#endif
      , ^(char s) { out₂(&s, 1); }); };
    auto ¹⁰¹¹⁰out = ^(__builtin_uint_t b) { Base𝕟(b, 2,
#ifdef __x86_64__
       64
#elif defined __mips__
       32
#endif
      , ^(char s) { out₂(&s, 1); }); };
    auto streamout_char = ^(char c) { out₂(&c, 1); };
    auto streamout_utf8 = ^(const char * utf8) { char *p=(char *)(utf8); while (*p) { out₂(p++, 1); } }; /* for (char * p=(char *)utf8; *p; p++) { out₂(p, 1); } */
    auto streamout_unicode = ^(char32_t u) { UnicodeToUtf8(u, ^(const uint8_t *p, 
      int bytes) { out₂((const char *)p, bytes); }); };
    /* #ifndef AVOID_IEEE754 */
    auto out𝕕 = ^(double ℝ) { Format(ℝ, ^(char32_t uc) { streamout_unicode(uc); }); };
    /* #endif */
#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 __attribute__ ((nonnull))
    auto streamout_unicodes = ^(int tetras, char32_t 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32_t uc = *(unicodes + beam); streamout_unicode(uc); 
      ++beam; } }; /* { int, (bytes, symbols) } */
    auto out¹²⁸𝕫 = ^(__int128_t I) { Base𝕫(I, 10, 0, ^(char 𝟶to𝟿) { out₂(&𝟶to𝟿, 1); }); };
    auto out¹²⁸𝕟 = ^(__uint128_t U) { Base𝕟(U, 16, 0, ^(char 𝟶to𝟿and₋) { out₂(&𝟶to𝟿and₋, 1); }); };
again:
    auto leadOr8Bit = (uint8_t *)utf8format + i;
    if (*leadOr8Bit == 0x0) { goto unagain; }
    followers = Utf8Followers(*leadOr8Bit);
    if (followers < 0) { return -1; }
    incr = followers + 1;
    uc = Utf8ToUnicode(leadOr8Bit, incr);
    if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }
    else if (uc != U'⬚') { streamout_unicode(uc); /* may𝘖𝘳DidEscape = (uc == U'/'); */ }
    else { ⁺⁼PrintArgAndPop }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

FOCAL
int
print⁺⁺(const char * utf8format, ...) /* Here all variable args are of the type `Arg`. */
{  int y;
    va_prologue(utf8format);
    extern void (^Putₒ)(uint8_t * utf8s, uint16_t bytes);
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
auto Putₒ2 = ^(uint8_t * utf8s, uint16_t bytes) { write(1, (const void *)utf8s, bytes); };

auto setBignum = ^(Argᴾ::Unicode set, void * context) {
  bignum *bn = (bignum *)context;
  print_bignum(bn, ^(char c) { print⁺⁺("⬚", ﹟c(c)); });
};

int
main(
  int argc,
  const char * argv[]
)
{
    /* Here with the introduction of Unicode `%` becomes redundant, 
      formatting is on the outside and types are checked by the compiler 
      instead of 'reported' at runtime. */
    print⁺⁺("Welcome to print: ⬚ ⬚ ⬚\n", ﹟d(12), ﹟x(12), ﹟F(12.1));
    
    __uint128_t x₁=0x4321432143214321; __int128_t x₂=-100;
    print⁺⁺("Size of x₁ is ⬚ value is 0x⬚\n", ﹟d(sizeof(x₁)), ﹟U(x₁));
    print⁺⁺("Size of x₂ is ⬚ value is ⬚\n", ﹟d(sizeof(x₂)), ﹟I(x₂));
    print⁺⁺("An ⬚ escaped\n", ﹟s("argument ⬚"));
    print⁺⁺("A unicode ⬚ is escaped\n", ﹟S(1, U"⬚"));
    Unicodes uc₁ { 1, Critic(U"⬚") };
    print⁺⁺("A unicode ⬚ is escaped\n", ﹟S(uc₁.tetras, uc₁.unicodes));
    print⁺⁺(Putₒ2, "A character ⬚ has landed\n", ﹟c('x'));
    
    /* And user-defined types: */ bignum X₁;
    int_to_bignum(17, &X₁);
    print⁺⁺("Bignum: ⬚\n", ﹟λ(setBignum,&X₁));
    return 0;
}

#pragma mark - Custom types

/* Copy in --<Fossilate.h> */
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
/* Copy in --<Fossilate.h> */
