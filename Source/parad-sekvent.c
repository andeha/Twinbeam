/*  parad-sekvent.c | /in-te 'mōn-ster'/. */

#include "twinbeam-inner.h"

#define PAGE₋SIZE 16384 /* =bytes per tile. */
#define CELLS₋ROOM 4096 /* =symbols and lengths per tile. */

int init₋regularpool(struct collection * 🅗)
{
   if (collection₋init(4,PAGE₋SIZE,🅗)) { return -1; }
   return 0;
}

int optional₋uninit₋regularpool(struct collection * 🅗, FALLOW fallow)
{
   if (deinit₋collection(🅗,fallow)) { return -1; }
   return 0;
}

int regularpool₋datum₋text(struct collection * 🅷, int32_t tetras, 
 Nonabsolute relative)
{
   uint32_t * ation = (uint32_t *)collection₋relative(relative,🅷);
   if (ation) { *ation=tetras; }
   return 0;
}

int copy₋prepare₋datum(struct collection * 🅷, ALLOC alloc)
{
   char32̄_t helicop[] = { 0x0000 };
   if (copy₋append₋items(1,helicop,🅷,alloc)) { return -1; }
   return 0;
}/* find relative with '*relative = (Nonabsolute)collection₋count(🅷)'' */

int copy₋append₋onto₋regular(struct collection * 🅷, int32_t tetras, 
 char32̄_t cs[], ALLOC alloc)
{
   if (copy₋append₋items(tetras,cs,🅷,alloc)) { return -1; }
   return 0;
}

int regularpool₋at(struct collection * 🅷, Nonabsolute relative, void (^text)
 (short tetras, short fragments, short symbols[], char32̄_t * run[]))
{ __builtin_int_t symbols₋word = *(uint32_t *)collection₋relative(relative,🅷),
   last₋index = relative + symbols₋word, run₋start = relative + 1, 
   fragments=0, left = last₋index - run₋start + 1, beam;
   __builtin_int_t fragment₋count = 2 + symbols₋word/CELLS₋ROOM;
   /* print("fragment₋count is ⬚.\n", ﹟d(fragment₋count)); */
   /* __builtin_int_t first₋segment = (relative+1)/CELLS₋ROOM;
   __builtin_int_t absolut₋relative = relative + symbols₋word;
   __builtin_int_t last₋segment = absolut₋relative/CELLS₋ROOM;
   short segment₋sum = last₋segment - first₋segment + 1; */
   short symbols[100]; char32̄_t * run[100];
again:
   if (run₋start > last₋index) { text(symbols₋word,fragments,symbols,run); return 0; }
   beam = CELLS₋ROOM * (1 + run₋start/CELLS₋ROOM);
   /* print("beam is ⬚ ", ﹟d(beam)); */
   symbols[fragments] = min(CELLS₋ROOM - (beam - run₋start),left);
   run[fragments] = (char32̄_t *)collection₋relative(run₋start,🅷);
   /* print("run₋start is ⬚ and symbols is ⬚ as min between ⬚ and ⬚\n", ﹟d(run₋start), 
    ﹟d(symbols[fragments]), ﹟d(beam-run₋start), ﹟d(left)); */
   run₋start += symbols[fragments];
   left -= symbols[fragments];
   fragments += 1;
   goto again;
}


