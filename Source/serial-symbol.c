/*  serial-symbol.c | printing and no bugs escape. */

#include "twinbeam-inner.h"

extern void register₋reflect(__builtin_uint_t mask, 
 void (^out)(char32̄_t uc));

extern void platform₋reflect(__builtin_uint_t mask,
 void (^out)(char32̄_t uc));

#pragma recto Inte₋ger₋s

Argᴾ ﹟d(__builtin_int_t d)
{
   Serialfragment integer₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
      short 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 brk=0; char8₋t bounded[30],*pb=bounded;
      Base𝕫(d,10,0, ^(char c) { pb[brk]=c; brk+=1; });
      fragment(bounded,brk); *symbol₋amend+=brk;
   };
   return ﹟λ₁(copy₋block(integer₋print),ΨΛΩ);
}

Argᴾ ﹟x(__builtin_uint_t x)
{
   Serialfragment natural₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
      short 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 brk=0; char8₋t bounded[30],*pb=bounded;
      Base𝕟(x,16,
#if defined __x86_64__ || defined __arm64__ || defined Kirkbridge
    16
#elif defined __mips__ || defined __armv6__ || defined espressif
    8
#endif
    , ^(char c) { pb[brk]=c; brk+=1; });
      fragment(bounded,brk); *symbol₋amend+=brk;
   };
   return ﹟λ₁(copy₋block(natural₋print),ΨΛΩ);
}

Argᴾ ﹟b(__builtin_uint_t b)
{
   Serialfragment binary₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
      short 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 brk=0; char8₋t bounded[70],*pb=bounded;
      Base𝕟(b,2,
#if defined __x86_64__ || defined __arm64__ || defined Kirkbridge
    64
#elif defined __mips__ || defined __armv6__ || defined espressif
    32
#endif
    , ^(char c) { pb[brk]=c; brk+=1; });
      fragment(bounded,brk); *symbol₋amend+=brk;
   };
   return ﹟λ₁(copy₋block(binary₋print),ΨΛΩ);
}

Argᴾ ﹟s8(char8₋t * u8s) ⓣ
{
   Serialfragment text₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
       __builtin_int_t bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
       fragment(u8s,bytes); *symbol₋amend+=bytes;
   };
   return ﹟λ₁(copy₋block(text₋print),ΨΛΩ);
}

Argᴾ ﹟s8(__builtin_int_t bytes, char8₋t * u8s) ⓣ
{
   Serialfragment text₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
       fragment(u8s,bytes); *symbol₋amend+=bytes;
   };
   return ﹟λ₁(copy₋block(text₋print),ΨΛΩ);
}

Argᴾ ﹟s7(char * sevenbit₋utf8)
{
   Serialfragment text₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
       char8₋t * u8s = (char8₋t *)sevenbit₋utf8;
       __builtin_int_t bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
       fragment(u8s,bytes); *symbol₋amend+=bytes;
   };
   return ﹟λ₁(copy₋block(text₋print),ΨΛΩ);
}

Argᴾ ﹟S(__builtin_int_t tetras, char32̄_t * uc₋unterminated) ⓣ
{
   Symbolfragment text₋print = ^(symbol₋present fragment, machine * 
    symbol₋amend, void * context) {
      fragment(tetras,uc₋unterminated); *symbol₋amend+=tetras;
   };
   return ﹟λ₂(copy₋block(text₋print),ΨΛΩ);
}

Argᴾ ﹟S(char32̄_t * ucs) ⓣ
{
   Symbolfragment text₋print = ^(symbol₋present fragment, machine * 
    symbol₋amend, void * context) {
     __builtin_int_t tetras = TetrasUntilZero(ucs,BUILTIN₋INT₋MAX);
     fragment(tetras,ucs); *symbol₋amend+=tetras;
   };
   return ﹟λ₂(copy₋block(text₋print),ΨΛΩ);
}

Argᴾ ﹟S(struct Unicodes uc) ⓣ
{
   Symbolfragment text₋print = ^(symbol₋present fragment, machine * 
    symbol₋amend, void * context) {
      fragment(uc.tetras,uc.unicodes); *symbol₋amend+=uc.tetras;
   };
   return ﹟λ₂(copy₋block(text₋print),ΨΛΩ);
}

Argᴾ ﹟c7(char c)
{
   Serialfragment letter₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) { char8₋t letter=(char8₋t)c;
       fragment(&letter,1); *symbol₋amend+=1;
   };
   return ﹟λ₁(copy₋block(letter₋print),ΨΛΩ);
} /* warning 'comparision of non-signed integers' requires additional bits in machine word. */

Argᴾ ﹟C(char32̄_t C)
{
   Symbolfragment letter₋print = ^(symbol₋present fragment, machine * 
    symbol₋amend, void * context) { char32̄_t letter=C; 
      fragment(1,&letter); *symbol₋amend+=1;
   };
   return ﹟λ₂(copy₋block(letter₋print),ΨΛΩ);
}

#if defined usage₋𝟷𝟸𝟾₋bit₋integer

Argᴾ ﹟U(__uint128_t U)
{
   Serialfragment natural₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
      short 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 brk=0; char8₋t bounded[30],*pb=bounded;
      Base𝕟(U,10,0, ^(char c) { pb[brk]=c; brk+=1; });
      fragment(bounded,brk); *symbol₋amend+=brk;
   };
   return ﹟λ₁(copy₋block(natural₋print),ΨΛΩ);
}

Argᴾ ﹟I(__int128_t I)
{
   Serialfragment integer₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) {
      short 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 brk=0; char8₋t bounded[30],*pb=bounded;
      Base𝕫(I,10,0, ^(char c) { pb[brk]=c; brk+=1; });
      fragment(bounded,brk); *symbol₋amend+=brk;
   };
   return ﹟λ₁(copy₋block(integer₋print),ΨΛΩ);
}

#endif

Argᴾ ﹟F(double ℝ, int method) ⓣ
{
   Serialfragment real₋print = ^(serial₋present fragment, machine * 
    symbol₋amend, void * context) { char text[100]; int letters;
      switch (method) {
      case 1: ieee754₋Scientific₋Rendition(ℝ,text,&letters); break;
      case 2: ieee754₋Saturn₋Rendition(ℝ,text,&letters); break;
      case 3: ieee754₋Monetary₋Rendition(ℝ,text,&letters); break;
      case 4: ieee754₋Scandinavian₋Monetary₋Rendition(ℝ,text,&letters); break;
      }
      fragment((char8₋t *)text,letters); *symbol₋amend+=letters;
   };
   return ﹟λ₁(copy₋block(real₋print),ΨΛΩ);
}

Argᴾ ﹟F(float ℝ, int method) ⓣ
{
   return ﹟F((double)ℝ, method);
}

/* Argᴾ ﹟regs(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 17 }; return y; }
Argᴾ ﹟plat(__builtin_uint_t mask) { Argᴾ y = { { .x=mask }, 19 }; return y; } */
/* ⬷ Print between 0 and 31 non-high-volatile registers. */

Argᴾ ﹟λ₁(void (^fragment)(serial₋present, machine *, void *), void * ctx) {
 Argᴾ y = { { .λ₁={ ctx, fragment } }, 20 }; return y; }
Argᴾ ﹟λ₂(void (^fragment)(symbol₋present, machine *, void *), void * ctx) {
 Argᴾ y = { { .λ₂={ ctx, fragment } }, 21 }; return y; }

/* Argᴾ ﹟hfill() { }
Argᴾ ﹟vfill() { }
Argᴾ ﹟pagefill(int verso₋not₋recto) { } 

extern void Fancy(char32̄_t prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, uint8_t * image) {
 print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); } read --<🥢 𝙎𝙪𝙨𝙝𝙞 𝘾𝙝𝙚́𝙛.cpp> and --<Impressions.hpp>
 for details on PNG::IHDR. \also 'anfang'. */

Argᴾ ﹟Italic(__builtin_int_t tetras, char32̄_t * uc₋unterminated) { return ﹟S(tetras,uc₋unterminated); }

#pragma recto in /retrospect/ hidden yet simple */

typedef void (^Eightbit₋out)(__builtin_int_t bytes, char8₋t * u8s);

inexorable void unicode₋out(char32̄_t uc, Eightbit₋out out, machine * amend)
{
   UnicodeToUtf8(uc, ^(char8₋t * u8s, short bytes) { out(bytes,u8s); *amend+=bytes; });
}

inexorable void lambda₋bytes(Serialfragment block, void * ctxt, Eightbit₋out out, machine * amend₋bytes)
{
   serial₋present line = ^(char8₋t * u8s, __builtin_int_t bytes) { out(bytes,u8s); };
   block(line,amend₋bytes,ctxt);
   release₋block(block);
}

inexorable void lambda₋symbols(Symbolfragment block, void * ctxt, Eightbit₋out out, machine * amend₋bytes)
{
   symbol₋present primary = ^(__builtin_int_t tetras, char32̄_t * ucs) {
      char8₋t u8s[4*tetras]; __builtin_int_t actual;
      UnicodeToUtf8(tetras,ucs,u8s,&actual);
      out(actual,u8s); *amend₋bytes += actual;
   };
   block(primary,amend₋bytes,ctxt);
   release₋block(block);
}

int
print﹟(
  void (^output)(char8₋t * u8s, __builtin_int_t bytes), 
  const /* unsigned */ char * utf8format, 
  __builtin_va_list argument
)
{ __builtin_int_t i=0,incr; short followers; char32̄_t uc;
   char8₋t * leadOr8Bit; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 machine printedBytesExcept0=0;
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
      switch (a.kind) { /*
      case 11: { / * Argᴾ::Unicode set = ^(int anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶,  \
       void * context) { if (!anfang) { print("⬚", ﹟C(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶)); }    \
       else { Anfang(prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, NULL); } }; a.value.λ.scalar(set,        \
       a.value.λ.context); * / break; }
      case 17: register₋reflect(a.value.x,
        ^(char32̄_t uc) { unicode₋out(uc,out,&printedBytesExcept0); });
       break;
      case 19: platform₋reflect(a.value.x, 
        ^(char32̄_t uc) { unicode₋out(uc,out,&printedBytesExcept0); });
       break; */
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

extern void (*Putₒ)(char8₋t * u8s, __builtin_int_t bytes);
extern void (*Trace₁)(char8₋t * u8s, __builtin_int_t bytes);
extern void (*Trace₂)(char8₋t * u8s, __builtin_int_t bytes);

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
   const int stderr = 2;
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(stderr, (const void *)u8s, bytes); };
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
   const int stdout = 1;
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(stdout, (const void *)u8s, bytes); };
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
   const int stdout = 1;
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { write(stdout, (const void *)u8s, bytes); };
#elif defined __mips__ || defined espressif || defined __armv6__ || defined Kirkbridge
   Reversed₋out out = ^(char8₋t * u8s, __builtin_int_t bytes) { Putₒ(u8s,bytes); };
#endif
   y += print(out,"\033[31;4m*** ");
   y += print﹟(out,utf8format,__various);
   y += print(out," ***\033[0m\n");
   va_epilogue
   return y;
}
