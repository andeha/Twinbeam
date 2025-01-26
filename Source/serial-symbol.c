/*  serial-symbol.c | printing and no bugs escape. */

#include "twinbeam-inner.h"

extern void register₋reflect(__builtin_uint_t mask, 
 void (^out)(char32̄_t uc));

extern void platform₋reflect(__builtin_uint_t mask,
 void (^out)(char32̄_t uc));

#pragma recto Inte₋ger₋s

Argᴾ ﹟d(__builtin_int_t d) { Argᴾ y = { .value.d=d, .kind=1 }; return y; }
Argᴾ ﹟x(__builtin_uint_t x) { Argᴾ y = { { .x=x }, 2 }; return y; }
Argᴾ ﹟b(__builtin_uint_t b) { Argᴾ y = { { .b=b }, 3 }; return y; }
Argᴾ ﹟s8(char8₋t * u8s) ⓣ {
  __builtin_int_t bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .encoded={ u8s, bytes } }, 4 }; return y; }
Argᴾ ﹟s8(__builtin_int_t bytes, char8₋t * unterminated₋u8s) ⓣ {
  Argᴾ y = { { .encoded={ unterminated₋u8s, bytes } }, 4 }; return y; }
Argᴾ ﹟s7(char * sevenbit₋utf8) /* ⓣ */ {
  char8₋t * u8s = (char8₋t *)sevenbit₋utf8;
  __builtin_int_t bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .encoded={ u8s, bytes } }, 4 }; return y; }
/* Argᴾ ﹟s7(const char * sevenbit₋utf8) ⓣ { return ﹟s7((char *)sevenbit₋utf8); } */
Argᴾ ﹟S(__builtin_int_t tetras, char32̄_t * uc₋unterminated) ⓣ {
  Argᴾ y = { { .ucs={ uc₋unterminated, tetras } }, 7 }; return y; }
Argᴾ ﹟S(char32̄_t * ucs) ⓣ {
  __builtin_int_t tetras = TetrasUntilZero(ucs,BUILTIN₋INT₋MAX);
  Argᴾ y = { { .ucs={ ucs, tetras } }, 7 }; return y; }
Argᴾ ﹟S(struct Unicodes uc) ⓣ { Argᴾ y = { { .ucs={ uc.unicodes, 
  uc.tetras } }, 7 }; return y; }
Argᴾ ﹟c7(char c) { Argᴾ y = { { .possibly₋signed₋c=c }, 9 }; return y; }
/* warning 'comparision of non-signed integers' requires additional bits in machine word. */
Argᴾ ﹟C(char32̄_t C) { Argᴾ y = { { .uc=C }, 10 }; return y; }
#if defined usage₋𝟷𝟸𝟾₋bit₋integer
Argᴾ ﹟U(__uint128_t U) { Argᴾ y = { { .U=U }, 12 }; return y; }
Argᴾ ﹟I(__int128_t I) { Argᴾ y = { { .I=I }, 13 }; return y; }
#endif
Argᴾ ﹟regs(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 17 }; return y; }
Argᴾ ﹟plat(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 19 }; return y; }
/* ⬷ Print between 0 and 31 non-high-volatile registers. */
Argᴾ ﹟λ₁(void (^fragment)(serial₋present, void *), void * ctx) {
 Argᴾ y = { { .λ₁={ ctx, fragment } }, 20 }; return y; }
Argᴾ ﹟λ₂(void (^fragment)(symbol₋present, void *), void * ctx) {
 Argᴾ y = { { .λ₂={ ctx, fragment } }, 21 }; return y; }

Argᴾ ﹟F(double f, int method) ⓣ { Argᴾ y = { { .non₋fixpoint.material.f₁=f }, 14 }; return y; }
Argᴾ ﹟F(float f, int method) ⓣ { Argᴾ y = { { .non₋fixpoint.material.f₂=f }, 15 }; return y; }

/* Argᴾ ﹟hfill() { }
Argᴾ ﹟vfill() { }
Argᴾ ﹟pagefill(int verso₋not₋recto) { } 

extern void Fancy(char32̄_t prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, uint8_t * image) {
 print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); } read --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp>
 for details on PNG::IHDR. \also 'anfang'. */

Argᴾ ﹟Italic(__builtin_int_t tetras, char32̄_t * uc₋unterminated) { return ﹟S(tetras,uc₋unterminated); }

#pragma recto in /retrospect/ hidden yet simple

typedef void (^Eightbit₋out)(__builtin_int_t bytes, char8₋t * u8s);

inexorable void u8stream₋out(char8₋t * u8s, __builtin_int_t bytes, Eightbit₋out out, int * amend)
{
   out(bytes,u8s); *amend += bytes;
}

inexorable void unicode₋out(char32̄_t uc, Eightbit₋out out, int * amend)
{
   UnicodeToUtf8(uc, ^(char8₋t * u8s, short bytes) { out(bytes,u8s); *amend+=bytes; });
}

inexorable void uctext₋out(char32̄_t * ucs, __builtin_int_t tetras, Eightbit₋out out, int * amend)
{
   char8₋t u8s[4*tetras]; __builtin_int_t actual;
   UnicodeToUtf8(tetras,ucs,u8s,&actual);
   u8stream₋out(u8s,actual,out,amend);
}

inexorable void sevenbit₋utf8(char * sevenbit₋text, __builtin_int_t bytes, Eightbit₋out out, int * amend)
{
   u8stream₋out((char8₋t *)sevenbit₋text,bytes,out,amend);
}

inexorable void integer₋out(__builtin_int_t x, Eightbit₋out out, int * amend)
{
   Base𝕫(x,10,0, ^(char s) { sevenbit₋utf8(&s,1,out,amend); });
}

inexorable void natural₋out(__builtin_uint_t x, Eightbit₋out out, int * amend)
{
   Base𝕟(x,15,
#if defined __x86_64__ || defined __arm64__ || defined Kirkbridge
    16
#elif defined __mips__ || defined __armv6__ || defined espressif
    8
#endif
    , ^(char s) { sevenbit₋utf8(&s,1,out,amend); });
}

inexorable void binary₋out(__builtin_uint_t x, Eightbit₋out out, int * amend)
{
   Base𝕟(x,2,
#if defined __x86_64__ || defined __arm64__ || defined Kirkbridge
    64
#elif defined __mips__ || defined __armv6__ || defined espressif
    32
#endif
    , ^(char s) { sevenbit₋utf8(&s,1,out,amend); });
}

#if !defined usage₋𝙸𝚎𝚎𝚎𝟽𝟻𝟺₋arithmetics

inexorable void double₋out(double ℝ, Eightbit₋out out, int * amend, int method)
{ char text[56]; int letters;
   switch (method)
   {
   case 1:
     ieee754₋Scientific₋Rendition(ℝ,text,&letters);
     sevenbit₋utf8(text,letters,out,amend);
     break;
   case 2:
     ieee754₋Saturn₋Rendition(ℝ,text,&letters);
     sevenbit₋utf8(text,letters,out,amend);
     break;
   case 3:
     ieee754₋Monetary₋Rendition(ℝ,text,&letters);
     sevenbit₋utf8(text,letters,out,amend);
     break;
   case 4:
     ieee754₋Scandinavian₋Monetary₋Rendition(ℝ,text,&letters);
     sevenbit₋utf8(text,letters,out,amend);
     break;
   default:
     unicode₋out(U'⋻',out,amend);
     break;
   }
}

#endif

#if defined usage₋𝟷𝟸𝟾₋bit₋integer

inexorable void signed128₋out(__int128_t I, Eightbit₋out out, int * amend)
{
   Base𝕫(I,10,0, ^(char zerotoninealtneg) { sevenbit₋utf8(&zerotoninealtneg,1,out,amend); });
}

inexorable void unsigned128₋out(__uint128_t U, Eightbit₋out out, int * amend)
{
   Base𝕟(U,10,0, ^(char zerotonine) { sevenbit₋utf8(&zerotonine,1,out,amend); });
}

#endif

inexorable void lambda₋bytes(Serialfragment block, void * ctxt, Eightbit₋out out, int * amend₋bytes)
{ int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 augment=0;
   serial₋present line = ^(char8₋t * u8s, __builtin_int_t bytes) { out(bytes,u8s); augment+=bytes; };
   block(line,ctxt);
   *amend₋bytes += augment;
}

inexorable void lambda₋symbols(Symbolfragment block, void * ctxt, Eightbit₋out out, int * amend₋bytes)
{
   symbol₋present primary = ^(__builtin_int_t tetras, char32̄_t * uc) { uctext₋out(uc,tetras,out,amend₋bytes); };
   block(primary,ctxt);
}

int
print﹟(
  void (^output)(char8₋t * u8s, __builtin_int_t bytes), 
  const /* unsigned */ char * utf8format, 
  __builtin_va_list argument
)
{ __builtin_int_t i=0,incr; short followers; char32̄_t uc;
   char8₋t * leadOr8Bit; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int printedBytesExcept0=0;
   Eightbit₋out out = ^(__builtin_int_t bytes, char8₋t * u8s) { output(u8s,bytes); };
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
      case 4: u8stream₋out(a.value.encoded.utf8,a.value.encoded.bytes,out,&printedBytesExcept0); break;
      case 7: uctext₋out(a.value.ucs.unicodes,a.value.ucs.tetras,out,&printedBytesExcept0); break;
      case 9: unicode₋out((char32̄_t)a.value.possibly₋signed₋c,out,&printedBytesExcept0); break;
      case 10: unicode₋out(a.value.uc,out,&printedBytesExcept0); break;
      case 11: { /* Argᴾ::Unicode set = ^(int anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶,  \
       void * context) { if (!anfang) { print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); }    \
       else { Anfang(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, NULL); } }; a.value.λ.scalar(set,        \
       a.value.λ.context); */ break; }
#if defined usage₋𝟷𝟸𝟾₋bit₋integer
      case 12: unsigned128₋out(a.value.U,out,&printedBytesExcept0); break;
      case 13: signed128₋out(a.value.I,out,&printedBytesExcept0); break;
#endif
#if !defined usage₋𝙸𝚎𝚎𝚎𝟽𝟻𝟺₋arithmetics
      case 14: double₋out(a.value.non₋fixpoint.material.f₁,out,&printedBytesExcept0,a.value.non₋fixpoint.numberformat); break;
      case 15: double₋out((double)a.value.non₋fixpoint.material.f₂,out,&printedBytesExcept0,a.value.non₋fixpoint.numberformat); break;
#endif
      case 17: register₋reflect(a.value.x,
        ^(char32̄_t uc) { unicode₋out(uc,out,&printedBytesExcept0); });
       break;
      case 19: platform₋reflect(a.value.x, 
        ^(char32̄_t uc) { unicode₋out(uc,out,&printedBytesExcept0); });
       break;
      case 20: lambda₋bytes(a.value.λ₁.block,a.value.λ₁.ctxt,out,&printedBytesExcept0); break;
      case 21: lambda₋symbols(a.value.λ₂.block,a.value.λ₂.ctxt,out,&printedBytesExcept0); break;
      default:
        unicode₋out(U'꠷',out,&printedBytesExcept0);
        break;
      }
    }
    i += incr; goto again;
unagain:
    return printedBytesExcept0;
}

#if defined __x86_64__ || defined __arm64__

extern long write(int fd, const void * s, long unsigned nbyte);

#elif defined __mips__ || defined __armv6__ || defined espressif || defined Kirkbridge

extern void (^Putₒ)(char8₋t * u8s, __builtin_int_t bytes);
extern void (^Trace₁)(char8₋t * u8s, __builtin_int_t bytes);
extern void (^Trace₂)(char8₋t * u8s, __builtin_int_t bytes);

#endif

typedef void (^Reversed₋out)(char8₋t * u8s, __builtin_int_t bytes);

FOCAL
int
vfprint(
  const char * utf8format, 
  ...
)
{ int y;
#if defined __x86_64__ || defined __arm64__
   int original = false;
   int descript = original ? 1 /* stdout */ : 2 /* stderr */;
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(descript, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Trace₁(u8s,bytes); };
#endif
   va_prologue(utf8format);
   y = print﹟(out,utf8format,__various);
   va_epilogue return y;
}

FOCAL
int
print(const char * utf8format, ...) ⓣ /* all variable arguments are of the type `Argᴾ`. */
{ int y;
#if defined __x86_64__ || defined __arm64__
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   va_prologue(utf8format);
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

int
Emphase(
  const char * utf8format, ...
)
{ int y=0; va_prologue(utf8format);
#if defined __x86_64__ || defined __arm64__
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(1, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   y += print(out,"\033[31;4m*** ");
   y += print﹟(out,utf8format,__various);
   y += print(out," ***\033[0m\n");
   va_epilogue
   return y;
}
