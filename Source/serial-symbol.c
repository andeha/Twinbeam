/*  serial-symbol.c | printing and no escapes. */

import Twinbeam;

extern void Anfang(char32̄_t prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, uint8_t * image) {
 print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); } /* read --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp>
 for details on PNG::IHDR. */

extern void Format(double ℝ, enum Ieee754form f, void (^out)(char32̄_t uc)) 
{ out((char32̄_t)U'∎'); } /* alternative definition in --<Additions>--<Ieee754₆₄bits.cpp>. */

extern void register₋reflect(__builtin_uint_t mask, void (^out)(char32̄_t uc)) { out((char32̄_t)U'∎'); }
/* alternative definition in --<Additions>--<Present-hw.cpp>. */

extern void platform₋reflect(void (^out)(char32̄_t uc)) { out((char32̄_t)U'∎'); } /*  alternative definition 
 in --<Additions>--<Present-hw.cpp>. */

#pragma recto Inte₋ger₋s

Argᴾ ﹟d(__builtin_int_t d) { Argᴾ y = { .value.d=d, .kind=1 }; return y; }
Argᴾ ﹟x(__builtin_uint_t x) { Argᴾ y = { { .x=x }, 2 }; return y; }
Argᴾ ﹟b(__builtin_uint_t b) { Argᴾ y = { { .b=b }, 3 }; return y; }
Argᴾ ﹟s8(char8₋t * u8s) ⓣ {
  __builtin_int_t bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .encoded={ u8s, bytes } }, 4 }; return y; }
Argᴾ ﹟s8(__builtin_int_t bytes, char8₋t * unterminated₋u8s) ⓣ {
  Argᴾ y = { { .encoded={ unterminated₋u8s, bytes } }, 4 }; return y; }
Argᴾ ﹟s7(char * sevenbit₋utf8) { Argᴾ y = { { .𝟽bit₋utf8 = sevenbit₋utf8 }, 5 }; return y; }
Argᴾ ﹟S(__builtin_int_t tetras, char32̄_t * uc₋unterminated) ⓣ { Argᴾ y = { { .ucs={ uc₋unterminated, tetras } }, 7 }; return y; }
Argᴾ ﹟S(char32̄_t * ucs) ⓣ {
  __builtin_int_t tetras = TetrasUntilZero(ucs,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .ucs={ ucs, tetras } }, 7 }; return y; }
Argᴾ ﹟c8(char8₋t c) { Argᴾ y = { { .c8=c }, 8 }; return y; }
Argᴾ ﹟c7(char c) { Argᴾ y = { { .possibly₋signed₋c=c }, 9 }; return y; }
/* warning 'comparision of non-signed integers' requires additional bits in machine word. */
Argᴾ ﹟C(char32̄_t C) { Argᴾ y = { { .uc=C }, 10 }; return y; }
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
Argᴾ ﹟U(__uint128_t U) { Argᴾ y = { { .U=U }, 12 }; return y; }
Argᴾ ﹟I(__int128_t I) { Argᴾ y = { { .I=I }, 13 }; return y; }
#endif
Argᴾ ﹟regs(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 17 }; return y; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */
Argᴾ ﹟λ₁(void (^fragment)(serial₋present, void *), void * ctx) { Argᴾ y = { { .λ₁={ ctx, fragment } }, 18 }; return y; }
Argᴾ ﹟λ₂(void (^fragment)(primary₋present, void *), void * ctx) { Argᴾ y = { { .λ₂={ ctx, fragment } }, 19 }; return y; }

Argᴾ ﹟F(double f, int numberformat) ⓣ { Argᴾ y = { { .f₁=f }, 14 }; return y; }
Argᴾ ﹟F(float f, int numberformat) ⓣ { Argᴾ y = { { .f₂=f }, 15 }; return y; }

#pragma recto in /retrospect/ hidden yet simple

typedef void (^Eight₋bit₋out)(char8₋t * u8s, __builtin_int_t bytes);

inexorable void sevenbit₋utf8(char * sevenbit₋text, __builtin_int_t bytes, Eight₋bit₋out out, int * amend)
{
   out((char8₋t *)sevenbit₋text,bytes);
   *amend += bytes;
}

inexorable void integer₋out(__builtin_int_t x, Eight₋bit₋out out, int * amend)
{
   Base𝕫(x,10,0, ^(char s) { sevenbit₋utf8(&s,1,out,amend); });
}

inexorable void natural₋out(__builtin_uint_t x, Eight₋bit₋out out, int * amend)
{
   Base𝕟(x,15,
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    16
#elif defined __mips__ || defined __armv6__ || defined espressif
    8
#endif
    , ^(char s) { sevenbit₋utf8(&s,1,out,amend); });
}

inexorable void binary₋out(__builtin_uint_t x, Eight₋bit₋out out, int * amend)
{
   Base𝕟(x,2,
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    64
#elif defined __mips__ || defined __armv6__ || defined espressif
    32
#endif
    , ^(char s) { sevenbit₋utf8(&s,1,out,amend); });
}

inexorable void scalar₋out(char8₋t c, Eight₋bit₋out out, int * amend)
{
   out(&c,1); *amend+=1;
}

inexorable void u8stream₋out(__builtin_int_t bytes, char8₋t * u8s, Eight₋bit₋out out, int * amend)
{
   char8₋t *p=u8s; while (*p) { out(p,1); p+=1; *amend+=1; }
}

inexorable void sevenbit₋out(char * sevenbit₋text, Eight₋bit₋out out, int * amend)
{ __builtin_int_t bytes=0;
   char *p=sevenbit₋text; while (*p) { p+=1; bytes+=1; }
   sevenbit₋utf8(sevenbit₋text,bytes,out,amend);
}

inexorable void unicode₋out(char32̄_t uc, Eight₋bit₋out out, int * amend)
{
   UnicodeToUtf8(uc, ^(char8₋t * u8s, short bytes) { out(u8s,bytes); *amend+=bytes; });
}

inexorable void uctext₋out(__builtin_int_t tetras, char32̄_t * ucs, Eight₋bit₋out out, int * amend)
{
   for (__builtin_int_t idx=0; idx<tetras; idx+=1) {
     char32̄_t uc = *(idx + ucs);
     unicode₋out(uc,out,amend);
   }
}

#if !defined UNEXISTING₋IEEE754
inexorable void double₋out(double ℝ, Eight₋bit₋out out, int * amend)
{
   Format(ℝ, ieee754₋Scientific, ^(char32̄_t uc) { unicode₋out(uc,out,amend); });
}
#endif

#if defined 𝟷𝟸𝟾₋bit₋integer₋available
inexorable void signed128₋out(__int128_t I, Eight₋bit₋out out, int * amend)
{
   Base𝕫(I,10,0, ^(char zerotoninealtneg) { sevenbit₋utf8(&zerotoninealtneg,1,out,amend); });
}

inexorable void unsigned128₋out(__uint128_t U, Eight₋bit₋out out, int * amend)
{
   Base𝕟(U,10,0, ^(char zerotonine) { sevenbit₋utf8(&zerotonine,1,out,amend); });
}
#endif

inexorable
int
print﹟(
  void (^out)(char8₋t * u8s, __builtin_int_t bytes), 
  const char * utf8format, 
  __builtin_va_list argument
)
{ __builtin_int_t i=0,incr; short followers; char32̄_t uc;
   char8₋t * leadOr8Bit; int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 printedBytesExcept0=0;
again:
    leadOr8Bit = i + (char8₋t *)utf8format;
    if (*leadOr8Bit == 0x0) { goto unagain; }
    followers = Utf8Followers(*leadOr8Bit);
    if (followers<0) { return -1; }
    incr = followers+1;
    uc = Utf8ToUnicode(leadOr8Bit,incr);
    if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }
    else if (uc != U'⬚') { unicode₋out(uc,out,&printedBytesExcept0); }
    else {
      Argᴾ a = __builtin_va_arg(argument,Argᴾ);
      switch (a.kind) {
      case 1: integer₋out(a.value.d,out,&printedBytesExcept0); break;
      case 2: natural₋out(a.value.x,out,&printedBytesExcept0); break;
      case 3: binary₋out(a.value.b,out,&printedBytesExcept0); break;
      case 4: u8stream₋out(a.value.encoded.bytes,a.value.encoded.utf8,out,&printedBytesExcept0); break;
      case 5: sevenbit₋out(a.value.𝟽bit₋utf8,out,&printedBytesExcept0); break;
      case 7: uctext₋out(a.value.ucs.tetras,a.value.ucs.unicodes,out,&printedBytesExcept0); break;
      case 8: scalar₋out(a.value.c8,out,&printedBytesExcept0); break;
      case 9: sevenbit₋utf8(&(a.value.possibly₋signed₋c),1,out,&printedBytesExcept0); break;
      case 10: unicode₋out(a.value.uc,out,&printedBytesExcept0); break;
      case 11: { /* Argᴾ::Unicode set = ^(int anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶,  \
       void * context) { if (!anfang) { print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); }    \
       else { Anfang(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, NULL); } }; a.value.λ.scalar(set,        \
       a.value.λ.context); */ break; }
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
      case 12: unsigned128₋out(a.value.U,out,&printedBytesExcept0); break;
      case 13: signed128₋out(a.value.I,out,&printedBytesExcept0); break;
#endif
#if !defined UNEXISTING₋IEEE754
      case 14: double₋out(a.value.f₁,out,&printedBytesExcept0); break;
      case 15: double₋out((double)a.value.f₂,out,&printedBytesExcept0); break;
#endif
      case 17: register₋reflect(a.value.x,
        ^(char32̄_t uc) { unicode₋out(uc,out,&printedBytesExcept0); });
       break;
      case 18: break;
      case 19: break;
      default:
        unicode₋out(U'?',out,&printedBytesExcept0); break;
      }
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
#if defined __x86_64__ || defined __armv8a__
   int original = false;
   int descript = original ? 1 /* stdout */ : 2 /* stderr */;
   Eight₋bit₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   Eight₋bit₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
#endif
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
int
print(const char * utf8format, ...) ⓣ /* all variable arguments are of the type `Argᴾ`. */
{ int y; va_prologue(utf8format);
#if defined __x86_64__ || defined __armv8a__
   Eight₋bit₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   Eight₋bit₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
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
) ⓣ
{ int y; va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue
   return y;
}

