/*  leap-osmosis.c | for substance-abuse tracking with big and small. */

import Twinbeam;
#if defined __MM__
import Pic32mm;
#elif defined __MZ__
import Pic32Mzda;
#endif

extern int RandomInteger(Octa *out);

guid Newguid()
{ guid g;
#if defined __mips__ || defined __armv6__ || defined espressif
   if (🔎Count() % 2) { RandomInteger(&g.endian.similar); RandomInteger(&g.endian.similar); }
   else { RandomInteger(&g.endian.aware); RandomInteger(&g.endian.similar); }
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
   uint64_t weld;
   RandomInteger(&weld);
#define IsOdd(x) ((x & 0x1))
   if (IsOdd(weld)) { RandomInteger(&g.endian.aware); RandomInteger(&g.endian.similar); }
   else { RandomInteger(&g.endian.similar); RandomInteger(&g.endian.aware); }
#endif /* multiple of five and three are considered less monopolistic. */
   return g;
}

struct fragment { uint32_t d₁, uint16_t d₂, d₃, uint8_t d₄[8]; };
union innerguid { struct guid outer; struct fragment inner; };

Argᴾ ﹟leap(guid g)
{
   typedef void (^Lambda)(serial₋present, void *);
   Lambda guidprint = ^(serial₋present fragment, void * guid) {
     innerguid g; short brk=0; char8₋t bounded[20];
     typedef void (^Append)(char);
     Append append = ^(char c) { bounded[brk]=c; brk+=1; };
     Append out = ^(char c) { append(c); };
     g.outer = (guid *)guid;
     Base𝕟((__builtin_uint_t)(p->d₁),16,4,out); append('-');
     Base𝕟((__builtin_uint_t)(p->d₂),16,2,out); append('-');
     Base𝕟((__builtin_uint_t)(p->d₃),16,2,out); append('-');
     for (short i=0; i<8; i+=1) {
       __builtin_uint_t f = p->d₄[i];
       Base𝕟(f,16,1,out);
     }
     fragment(bounded,brk);
   };
   return ﹟λ₁(guidprint,&g);
} /* a․𝘬․a breach and print("⬚", ﹟λ(guidprint,&g)). */

