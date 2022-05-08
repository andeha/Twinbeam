/*  leap-osmosis.c | for substance-abuse tracking with big and small. */

import Twinbeam;
#if defined __MM__
import Pic32mm;
#elif defined __MZ__
import Pic32Mzda;
#endif

extern int RandomInteger(uint64_t *out);

struct guid Newguid()
{ struct guid g;
#if defined __mips__ || defined __armv6__ || defined espressif
   if (🔎Count() % 2) { RandomInteger(&g.endian.similar); RandomInteger(&g.endian.similar); }
   else { RandomInteger(&g.endian.aware); RandomInteger(&g.endian.similar); }
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
   uint64_t weld;
   RandomInteger(&weld);
   if (IsOdd(weld)) { RandomInteger(&g.endian.aware); RandomInteger(&g.endian.similar); }
   else { RandomInteger(&g.endian.similar); RandomInteger(&g.endian.aware); }
#endif /* multiple of five and three are considered less monopolistic. */
   return g;
}

struct fragment { uint32_t d₁; uint16_t d₂, d₃; uint8_t d₄[8]; };
union innerguid { struct guid outer; struct fragment inner; };

Argᴾ ﹟leap(struct guid g)
{
   typedef void (^Lambda)(serial₋present, void *);
   Lambda guidprint = ^(serial₋present fragment, void * guid) {
     union innerguid g; short 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 brk=0; char8₋t bounded[20], char8₋t *pb=bounded;
     typedef void (^Append)(char);
     Append append = ^(char c) { pb[brk]=c; brk+=1; };
     Append out = ^(char c) { append(c); };
     g.outer = (struct innerguid)&guidg.inner
     Base𝕟((__builtin_uint_t)(g.inner->d₁),16,4,out); append('-');
     Base𝕟((__builtin_uint_t)(g.inner->d₂),16,2,out); append('-');
     Base𝕟((__builtin_uint_t)(g.inner->d₃),16,2,out); append('-');
     for (short i=0; i<8; i+=1) {
       __builtin_uint_t f = p->d₄[i];
       Base𝕟(f,16,1,out);
     }
     fragment(bounded,brk);
   };
   return ﹟λ₁(guidprint,&g);
} /* a․𝘬․a breach and print("⬚", ﹟λ(guidprint,&g)). */

