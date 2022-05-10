/*  serial-symbol.c | 🗞 - printing and no escapes. */

import Twinbeam;

extern void Anfang(char32̄_t prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, uint8_t * image) {
 print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); } /* read --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp>
 for details on PNG::IHDR. */

extern void Format(double ℝ, enum Ieee754form f, void (^out)(char32̄_t uc)) 
{ out(U'∎'); } /* alternative definition in --<Additions>--<Ieee754₆₄bits.cpp>. */

extern void register₋reflect(__builtin_uint_t mask) { print("∎"); }
/* alternative definition in --<Additions>--<Present-hw.cpp>. */

extern void platform₋reflect() { print("∎"); } /*  alternative definition 
 in --<Additions>--<Present-hw.cpp>. */

#pragma recto Inte₋ger₋s

Argᴾ ﹟d(__builtin_int_t d) { Argᴾ y = { .value.d=d, .kind=1 }; return y; }
Argᴾ ﹟x(__builtin_uint_t x) { Argᴾ y = { { .x=x }, 2 }; return y; }
Argᴾ ﹟b(__builtin_uint_t b) { Argᴾ y = { { .b=b }, 3 }; return y; }
Argᴾ ﹟s8(char8₋t * u8s) ⓣ {
  __builtin_int_t bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .u8s={ u8s, bytes } }, 4 }; return y; }
Argᴾ ﹟s8(__builtin_int_t bytes, char8₋t * unterminated₋u8s) ⓣ {
  Argᴾ y = { { .u8s={ unterminated₋u8s, bytes } }, 4 }; return y; }
Argᴾ ﹟s7(char * sevenbit₋utf8) { Argᴾ y = { { .𝟽bit₋utf8 = sevenbit₋utf8 }, 4 }; return y; }
Argᴾ ﹟S(__builtin_int_t tetras, char32̄_t * uc₋unterminated) ⓣ { Argᴾ y = { { .ucs={ uc₋unterminated, tetras } }, 5 }; return y; }
Argᴾ ﹟S(char32̄_t * ucs) ⓣ {
  __builtin_int_t tetras = TetrasUntilZero(ucs,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .ucs={ ucs, tetras } }, 5 }; return y; }
Argᴾ ﹟c8(char8₋t c) { Argᴾ y = { { .c8=c }, 6 }; return y; }
Argᴾ ﹟c7(char c) { Argᴾ y = { { .c=(char8₋t)c }, 6 }; return y; }
Argᴾ ﹟C(char32̄_t C) { Argᴾ y = { { .uc=C }, 7 }; return y; }
#if defined 𝟷𝟸𝟾₋bit₋integers
Argᴾ ﹟U(__uint128_t U) { Argᴾ y = { { .U=U }, 11 }; return y; }
Argᴾ ﹟I(__int128_t I) { Argᴾ y = { { .I=I }, 12 }; return y; }
#endif
Argᴾ ﹟regs(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 13 }; return y; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */
Argᴾ ﹟λ₁(void (^fragment)(serial₋present, void *), void * ctx) { Argᴾ y = { { .λ₁={ ctx, fragment } }, 9 }; return y; }
Argᴾ ﹟λ₂(void (^fragment)(primary₋present, void *), void * ctx) { Argᴾ y = { { .λ₂={ ctx, fragment } }, 8 }; return y; }

#pragma recto in /retrospect/ hidden yet simple

inexorable
int
print﹟(
  void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  __builtin_va_list argument
)
{  __builtin_int_t i=0, incr; short followers; char32̄_t uc;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0; /* int may𝘖rDidEscape=false; */
    auto out₂ = ^(const char * 𝟽bit₋utf8, __builtin_int_t bytes) {
      out((char8₋t *)𝟽bit₋utf8, bytes); printedBytesExcept0 += bytes; };
    auto out𝕫 = ^(__builtin_int_t x) { Base𝕫(x, 10, 0, ^(char s) { out₂(&s,1); }); };
    auto out𝕟 = ^(__builtin_uint_t x) { Base𝕟(x, 16, 
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
      16
#elif defined __mips__ || defined __armv6__ || defined espressif
       8
#endif
      , ^(char s) { out₂(&s,1); }); };
    auto 𝟷𝟶𝟷𝟷𝟶₋out = ^(__builtin_uint_t b) { Base𝕟(b, 2,
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
       64
#elif defined __mips__ || defined __armv6__ || defined espressif
       32
#endif
      , ^(char s) { out₂(&s,1); }); };
    auto eight₋bit₋symbol = ^(char8₋t c) { out(&c,1); };
    auto u8c₋stream = ^(char8₋t * utf8) { char8₋t * p = (char8₋t *)utf8; while (*p) { out(p,1); p+=1; } };
    auto unicode₋symbol = ^(char32̄_t u) { UnicodeToUtf8(u, ^(char8₋t * u8s, 
     short bytes) { out((char8₋t *)u8s,bytes); }); };
#ifndef UNEXISTING₋IEEE754
    auto out𝕕 = ^(double ℝ) { Format(ℝ, ieee754form₋scientific, ^(char32̄_t uc) { unicode₋symbol(uc); }); };
#endif
    auto unicode₋stream = ^(int tetras, char32̄_t * unicodes) { __builtin_int_t 
      beam=0; while (beam < tetras) { char32̄_t uc = *(unicodes + beam); unicode₋symbol(uc); 
      beam+=1; } }; /* { int, (bytes, symbols) } */
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
#ifndef UNEXISTING₋IEEE754
      case 8: out𝕕(double(a.value.f₂)); break;                                  \
      case 9: out𝕕(a.value.f₁); break;                                          \
#endif
      case 10: { Argᴾ::Unicode set = ^(int anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶,  \
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

#if defined __x86_64__ || defined __armv8a__
EXT₋C long write(int fd, const void * s, long unsigned nbyte);
#elif defined __mips__ || defined __armv6__ || defined espressif || defined Kirkbridge
extern void (^Putₒ)(char8₋t * u8s, __builtin_int_t bytes);
extern void (^Trace₁)(char8₋t * u8s, __builtin_int_t bytes);
extern void (^Trace₂)(char8₋t * u8s, __builtin_int_t bytes);
#endif

FOCAL
int
mfprint(
  const char * utf8format, 
  ...
)
{ int y; va_prologue(utf8format);
#ifdef __x86_64__ || defined __armv8a__
   int original = false;
   int 🥇 descript = original ? 1 /* stdout */ : 2 /* stderr */;
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
int
print(const char * utf8format, ...) /* all variable arguments are of the type `Argᴾ`. */
{ int y; va_prologue(utf8format);
#ifdef __x86_64__ || defined __armv8a__
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   auto out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
int
print(
  void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  ...
)
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
}

