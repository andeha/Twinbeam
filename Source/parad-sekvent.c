/*  parad-sekvent.c | /in-te 'mōn-ster'/. */

import Twinbeam;

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

int copy₋append₋onto₋regular(struct collection * 🅷, int32_t tetras, 
 char32̄_t cs[], ALLOC alloc, Nonabsolute * relative)
{ char32̄_t helicop[] = { 0x0000 };
   *relative = (Nonabsolute)collection₋count(🅷);
   if (copy₋append₋items(1,helicop,🅷,alloc)) { return -1; }
   if (copy₋append₋items(tetras,cs,🅷,alloc)) { return -1; }
   return 0;
}

int regularpool₋at(struct collection * 🅷, Nonabsolute relative, void (^text)
 (short tetras, short fragments, short symbols[], char32̄_t * run[]))
{ __builtin_int_t symbols₋word = *(uint32_t *)collection₋relative(relative,🅷),
   last₋index = relative + symbols₋word, run₋start = relative + 1, 
   fragments=0, left = last₋index - run₋start + 1;
   short symbols[100]; char32̄_t * run[100]; __builtin_int_t beam;
again:
   if (run₋start > last₋index) { text(symbols₋word,fragments,symbols,run); return 0; }
   beam = CELLS₋ROOM * (1 + run₋start/CELLS₋ROOM);
   /* print("beam is ⬚ ", ﹟d(beam)); */
   symbols[fragments] = min(CELLS₋ROOM - (beam - run₋start),left);
   run[fragments] = (char32̄_t *)collection₋relative(run₋start,🅷);
   /* print("run₋start is ⬚ and symbols is ⬚ as min between ⬚ and ⬚\n", ﹟d(run₋start), 
    ﹟d(symbols[fragments]), ﹟d(beam-run₋start), ﹟d(left)); */
   run₋start += symbols[fragments];
   left = left - symbols[fragments];
   fragments += 1;
   goto again;
}

/*
int regularpool₋at(struct collection * 🅷, Nonabsolute relative, void (^text)
 (short tetras, short fragments, short symbols[], char32̄_t * segment[]))
{ uint32_t symbols₋word = *(uint32_t *)collection₋relative(relative,🅷);
   __builtin_int_t first₋segment = (relative+1)/CELLS₋ROOM;
   __builtin_int_t absolut₋relative = relative + symbols₋word;
   __builtin_int_t last₋segment = absolut₋relative/CELLS₋ROOM;
   short segment₋sum = last₋segment - first₋segment + 1;
   char32̄_t * run[segment₋sum]; short length₋table[segment₋sum];
   __builtin_int_t start₋next = (1 + relative), idx = 0, 
    length₋left = symbols₋word, symbols₋util₋swap, palm₋start₋idx =
     CELLS₋ROOM*(relative/CELLS₋ROOM);
again:
   / * print("start-next ⬚\n", ﹟d(start₋next)); * /
   run[idx] = (char32̄_t *)collection₋relative(start₋next,🅷);
   symbols₋util₋swap = CELLS₋ROOM - (start₋next - palm₋start₋idx);
   length₋table[idx] = min(symbols₋util₋swap,symbols₋word);
   if (length₋left <= 0)
   {
   text(symbols₋word,segment₋sum,length₋table,run);
   return 0;
   }
   length₋left = length₋left - length₋table[idx];
   start₋next += length₋table[idx];
   palm₋start₋idx += CELLS₋ROOM; 
   idx+=1; goto again;
}
*/

