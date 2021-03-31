/*  𝙋𝙧𝙞𝙣𝙩.cpp | 🗞 - Printing and no escapes. */

#include <Twinbeam.h>

DISORDERABLE extern void CastᵈᵇˡToText(double value, void (^digits)(bool neg, 
  int e, const char8_t *𝟶to𝟿s), void (^zero)(bool neg), void (^inf)(bool neg), 
  void (^nan)()) { zero(true); } /* ⬷ Alt. defintion in --<Additions>--<Ieee754₆₄bits.cpp>-<<--<Impressions.hpp>. */

DISORDERABLE extern void Anfang(char32_t prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, uint8_t * image) {
 print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); } /* See --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp>
 for details on PNG::IHDR. */

DISORDERABLE extern void register₋reflect(__builtin_uint_t mask) { print("∎"); }
/* Alternative definition in --<Additions>--<Presentᵃᵘˣ.cpp>. */

DISORDERABLE extern void Format(double ℝ, Ieee754form f, void (^out)(char32_t uc)) 
{ out(U'∎'); } /* Alternative definition in --<Additions>--<Ieee754₆₄bits.cpp>. */

DISORDERABLE extern void platform₋reflect() { } /* ⬷ Alternative definition 
 in --<Additions>--<Presentᵃᵘˣ.cpp>. */

#pragma mark - Inte₋ger₋s

Argᴾ ﹟d(__builtin_int_t d) { return Argᴾ { .value.d=d, .kind=1 }; }
Argᴾ ﹟x(__builtin_uint_t x) { return Argᴾ { { .x=x }, 2 }; }
Argᴾ ﹟b(__builtin_uint_t b) { return Argᴾ { { .b=b }, 3 }; }
Argᴾ ﹟s(const char8_t * utf8) { return Argᴾ { { .utf8=Critic(utf8) }, 4 }; }
Argᴾ ﹟s(char8_t * utf8) { return Argᴾ { { .utf8=utf8 }, 4 }; }
Argᴾ ﹟s(const char * utf8) { return Argᴾ { { .utf8=(char8_t *)utf8 }, 4 }; }
Argᴾ ﹟S(__builtin_int_t tetras, char32_t * uc) { return Argᴾ { { .ucs={ uc, tetras } }, 5 }; }
Argᴾ ﹟S(__builtin_int_t tetras, const char32_t * uc) { return Argᴾ { { .ucs={ Critic(uc), tetras } }, 5 }; }
Argᴾ ﹟c(char8_t c) { return Argᴾ { { .c=c }, 6 }; }
Argᴾ ﹟c(char c) { return Argᴾ { { .c=(char8_t)c }, 6 }; }
Argᴾ ﹟C(char32_t C) { return Argᴾ { { .uc=C }, 7 }; }
#if defined 𝟷𝟸𝟾₋bit₋integers
Argᴾ ﹟U(__uint128_t U) { return Argᴾ { { .U=U }, 11 }; }
Argᴾ ﹟I(__int128_t I) { return Argᴾ { { .I=I }, 12 }; }
#endif
Argᴾ ﹟regs(__builtin_uint_t mask) { return Argᴾ { { .x=mask }, 13 }; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */
Argᴾ ﹟λ(Argᴾ::Output scalar, void * context) { return Argᴾ { { .λ={ scalar, context } }, 10 }; }

#pragma mark - in /retrospect/, hidden yet simple:

inexorable
int
print﹟(
  void (^out)(char8_t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  __builtin_va_list argument
)
{  __builtin_int_t i=0, incr; short followers; char32_t uc;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0; /* bool may𝘖rDidEscape=false; */
    auto out₂ = ^(const char * 𝟽bit₋utf8, __builtin_int_t bytes) {
      out((char8_t *)𝟽bit₋utf8, bytes); printedBytesExcept0 += bytes; };
    auto out𝕫 = ^(__builtin_int_t x) { Base𝕫(x, 10, 0, ^(char s) { out₂(&s,1); }); };
    auto out𝕟 = ^(__builtin_uint_t x) { Base𝕟(x, 16, 
#if defined __x86_64__ || defined __armv8a__
      16
#elif defined  __mips__ || defined __armv6__ || defined espressif
       8
#endif
      , ^(char s) { out₂(&s,1); }); };
    auto 𝟷𝟶𝟷𝟷𝟶₋out = ^(__builtin_uint_t b) { Base𝕟(b, 2,
#if defined __x86_64__ || defined __armv8a__
       64
#elif defined  __mips__ || defined __armv6__ || defined espressif
       32
#endif
      , ^(char s) { out₂(&s,1); }); };
    auto eight₋bit₋symbol = ^(char8_t c) { out(&c,1); };
    auto u8c₋stream = ^(const char8_t * utf8) { char8_t * p = (char8_t *)utf8; while (*p) { out(p,1); p++; } };
    auto unicode₋symbol = ^(char32_t u) { UnicodeToUtf8(u, ^(char8_t * u8s, 
     short bytes) { out(Critic(u8s),bytes); }); };
/* #ifndef UNEXISTING₋IEEE754 */
    auto out𝕕 = ^(double ℝ) { Format(ℝ, Ieee754form::Scientific, ^(char32_t uc) { unicode₋symbol(uc); }); };
/* #endif */
    auto unicode₋stream = ^(int tetras, char32_t 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32_t uc = *(unicodes + beam); unicode₋symbol(uc); 
      ++beam; } }; /* { int, (bytes, symbols) } */
#ifdef 𝟷𝟸𝟾₋bit₋integers
    auto 𝟷𝟸𝟾₋out𝕫 = ^(__int128_t I) { Base𝕫(I, 10, 0, ^(char 𝟶to𝟿) { out₂(&𝟶to𝟿,1); }); };
    auto 𝟷𝟸𝟾₋out𝕟 = ^(__uint128_t U) { Base𝕟(U, 16, 0, ^(char 𝟶to𝟿and₋) { out₂(&𝟶to𝟿and₋,1); }); };
#endif
again:
    auto leadOr8Bit = i + (char8_t *)utf8format;
    if (*leadOr8Bit == 0x0) { goto unagain; }
    followers = Utf8Followers(*leadOr8Bit);
    if (followers < 0) { return -1; }
    incr = followers + 1;
    uc = Utf8ToUnicode(leadOr8Bit,incr);
    if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }
    else if (uc != U'⬚') { unicode₋symbol(uc); }
    else { /* ⬷ reflecting natives /to/ terminal. */
      const Argᴾ a = __builtin_va_arg(argument, Argᴾ);                          \
      switch (a.kind) {                                                         \
      case 1: out𝕫(a.value.d); break;                                           \
      case 2: out𝕟(a.value.x); break;                                           \
      case 3: 𝟷𝟶𝟷𝟷𝟶₋out(a.value.b); break;                                       \
      case 4: u8c₋stream(a.value.utf8); break;                                  \
      case 5: unicode₋stream(a.value.ucs.tetras, a.value.ucs.unicodes); break;  \
      case 6: eight₋bit₋symbol(a.value.c); break;                               \
      case 7: unicode₋symbol(a.value.uc); break;                                \
      case 8: out𝕕(double(a.value.f₂)); break;                                  \
      case 9: out𝕕(a.value.f₁); break;                                          \
      case 10: { Argᴾ::Unicode set = ^(bool anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, \
       void * context) { if (!anfang) { print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); }    \
       else { Anfang(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, NULL); } }; a.value.λ.scalar(set,        \
       a.value.λ.context); break; }
#ifdef 𝟷𝟸𝟾₋bit₋integers
      case 11: 𝟷𝟸𝟾₋out𝕟(a.value.U); break;                                      \
      case 12: 𝟷𝟸𝟾₋out𝕫(a.value.I); break;
#endif
      case 13: register₋reflect(a.value.x); break;                              \
      default: /* if (a.kind >= 0) imprint[a.kind](a); else */                  \
        unicode₋symbol(U'?'); break; }
    }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

#ifdef __x86_64__
extern "C" long write(int fd, const void * s, long unsigned nbyte);
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
extern void (^Putₒ)(char8_t * u8s, __builtin_int_t bytes);
extern void (^Trace₁)(char8_t * u8s, __builtin_int_t bytes);
extern void (^Trace₂)(char8_t * u8s, __builtin_int_t bytes);
#endif

FOCAL
int
mfprint(
  const char * utf8format, 
  ...
)
{ int y; va_prologue(utf8format);
#ifdef __x86_64__
   bool original = false;
   int 🥇 descript = original ? 1 /* stdout */ : 2 /* stderr */;
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
int
print(const char * utf8format, ...) /* Here all variable args are of the type `Argᴾ`. */
{ int y; va_prologue(utf8format);
#ifdef __x86_64__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif defined __armv8a__ || defined __mips__ || defined espressif || defined __armv6__
   auto out = ^(char8_t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
int
print(
  void (^out)(char8_t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  ...
)
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
} /* ⬷ a․𝘬․a `print⁺⁺`. See --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp> for more details. */

