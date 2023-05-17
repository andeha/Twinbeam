/*  symbol-tiles.c | symbol processing helpers. */

#include "twinbeam-inner.h"

typedef void (^Unicode₋out)(__builtin_int_t tetras, char32̄_t * uc);

inexorable void uctext₋out(char32̄_t * ucs, __builtin_int_t tetras, Unicode₋out out, int * amend)
{
   out(tetras,ucs); *amend += tetras;
}

inexorable void u8stream₋out(char8₋t * u8s, __builtin_int_t bytes, Unicode₋out out, int * amend)
{
   char32̄_t unicodes[4*bytes]; __builtin_int_t tetras,i;
   Utf8ToUnicode(bytes,u8s,unicodes,&tetras);
   uctext₋out(unicodes,tetras,out,amend);
}

inexorable void unicode₋out(char32̄_t uc, Unicode₋out out, int * amend)
{
   out(1,&uc); *amend += 1;
}

inexorable void sevenbit₋utf8(char * sevenbit₋text, __builtin_int_t bytes, Unicode₋out out, int * amend)
{
   u8stream₋out((char8₋t *)sevenbit₋text,bytes,out,amend);
}

inexorable void integer₋out(__builtin_int_t x, Unicode₋out out, int * amend)
{
   Base𝕫(x,10,0, ^(char s) { unicode₋out((char32̄_t)s,out,amend); } );
}

inexorable void natural₋out(__builtin_uint_t x, Unicode₋out out, int * amend)
{
   Base𝕟(x,2,
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    16
#elif defined __mips__ || defined __armv6__ || defined espressif
    8
#endif
    , ^(char s) { unicode₋out((char32̄_t)s,out,amend); });
}

inexorable void binary₋out(__builtin_uint_t x, Unicode₋out out, int * amend)
{
   Base𝕟(x,2,
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    64
#elif defined __mips__ || defined __armv6__ || defined espressif
    32
#endif
    , ^(char s) { unicode₋out((char32̄_t)s,out,amend); });
}

#if !defined usage₋𝙸𝚎𝚎𝚎𝟽𝟻𝟺₋arithmetics
inexorable void double₋out(double ℝ, Unicode₋out out, int * amend, int method)
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
     unicode₋out(U'⋼',out,amend);
     break;
   }
}
#endif

#if defined usage₋𝟷𝟸𝟾₋bit₋integer
inexorable void signed128₋out(__int128_t I, Unicode₋out out, int * amend)
{
   Base𝕫(I,10,0,^(char zerotoninealtneg) { sevenbit₋utf8(&zerotoninealtneg,1,out,amend); });
}

inexorable void unsigned128₋out(__uint128_t U, Unicode₋out out, int * amend)
{
   Base𝕟(U,10,0, ^(char zerotonine) { sevenbit₋utf8(&zerotonine,1,out,amend); });
}
#endif

inexorable void lambda₋bytes(Serialfragment block, void * ctxt, Unicode₋out out, int * amend)
{
   serial₋present line = ^(char8₋t * u8s, __builtin_int_t bytes) { u8stream₋out(u8s,bytes,out,amend); };
   block(line,ctxt);
}

inexorable void lambda₋symbols(Symbolfragment block, void * ctxt, Unicode₋out out, int * amend)
{
   symbol₋present primary = ^(__builtin_int_t tetras, char32̄_t * uc) { uctext₋out(uc,tetras,out,amend); };
   block(primary,ctxt);
}

FOCAL
int
Play(
  char32̄_t * text,
  __builtin_va_list params,
  void (^composition)(__builtin_int_t total, char32̄_t * ucs)
) ⓣ
{ struct collection 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 symbols; __builtin_int_t i=0;
    
   Unicode₋out out = ^(__builtin_int_t tetras, char32̄_t * uc) {
     if (copy₋append₋items(tetras,uc,&symbols,Heap₋alloc)) { return; }
     /* for (int j=0; j<tetras; j+=1) {
       *(char32̄_t *)collection₋relative(j,&symbols) = *(j + uc);
     } */
   };
   
   if (collection₋init(4,4096,&symbols)) return -1;
   __builtin_int_t total;
   char32̄_t uc, *consecutive;
   struct Unicodes serial; Argᴾ a;
   int printedSymbolsExcept0=0;
again:
   uc = *(i + text);
   if (uc == 0x0000) goto unagain;
   if (uc != U'⬚') { unicode₋out(uc,out,&printedSymbolsExcept0); }
   else {
     a = __builtin_va_arg(params,Argᴾ);
     switch (a.kind) {
     case 1: integer₋out(a.value.d,out,&printedSymbolsExcept0); break;
     case 2: natural₋out(a.value.x,out,&printedSymbolsExcept0); break;
     case 3: binary₋out(a.value.b,out,&printedSymbolsExcept0); break;
     case 4: u8stream₋out(a.value.encoded.utf8,a.value.encoded.bytes,out,&printedSymbolsExcept0); break;
     case 7: uctext₋out(a.value.ucs.unicodes,a.value.ucs.tetras,out,&printedSymbolsExcept0); break;
     case 9: unicode₋out((char32̄_t)a.value.possibly₋signed₋c,out,&printedSymbolsExcept0); break;
     case 10: unicode₋out(a.value.uc,out,&printedSymbolsExcept0); break;
#if defined usage₋𝟷𝟸𝟾₋bit₋integer
     case 12: unsigned128₋out(a.value.U,out,&printedSymbolsExcept0); break;
     case 13: signed128₋out(a.value.I,out,&printedSymbolsExcept0); break;
#endif
#if !defined usage₋𝙸𝚎𝚎𝚎𝟽𝟻𝟺₋arithmetics
     case 14: double₋out(a.value.non₋fixpoint.material.f₁,out,&printedSymbolsExcept0,a.value.non₋fixpoint.numberformat); break;
     case 15: double₋out((double)a.value.non₋fixpoint.material.f₂,out,&printedSymbolsExcept0,a.value.non₋fixpoint.numberformat); break;
#endif
     case 17: break; /* regs */
     case 19: break; /* plat */
     case 20: lambda₋bytes(a.value.λ₁.block,a.value.λ₁.ctxt,out,&printedSymbolsExcept0); break;
     case 21: lambda₋symbols(a.value.λ₂.block,a.value.λ₂.ctxt,out,&printedSymbolsExcept0); break;
     default:
       unicode₋out(U'꠷',out,&printedSymbolsExcept0);
       break;
     }
   }
   i+=1; goto again;
unagain:
   total = collection₋count(&symbols);
   consecutive = (char32̄_t *)Heap₋alloc(total);
   for (i=0; i<total; i+=1) {
     *(i+consecutive) = *(char32̄_t *)collection₋relative(i,&symbols);
   }
   composition(total,consecutive);
   if (deinit₋collection(&symbols,Heap₋unalloc)) { return -2; }
   Heap₋unalloc(consecutive);
   return printedSymbolsExcept0;
}

FOCAL
int
Play(
  void (^serial)(__builtin_int_t total, char32̄_t * ucs), 
  char32̄_t * text, 
  ...
) ⓣ
{ int y;
   va_prologue(text)
   y = Play(text,__various,serial);
   va_epilogue
   return y;
}

