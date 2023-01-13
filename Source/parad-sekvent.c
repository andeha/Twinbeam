/*  parad-sekvent.c | /in-te 'mōn-ster'/. */

import Twinbeam;

#define PAGE₋SIZE 8192 /* =bytes per tile. */
#define CELLS₋ROOM 2048 /* =symbols and lengths per tile. */

int init₋regularpool(struct collection * ᐧ 🅗)
{
   if (collection₋init(4,PAGE₋SIZE,🅗)) { return -1; }
   return 0;
}

int optional₋uninit₋regularpool(struct collection * ᐧ 🅗, FALLOW fallow)
{
   if (deinit₋collection(🅗,fallow)) { return -1; }
   return 0;
}

int regularpool₋datum₋text(struct collection * ᐧ 🅷, int32_t tetras, 
 Nonabsolute relative)
{
   uint32_t * ation = (uint32_t *)collection₋relative(relative,🅷);
   if (ation) { *ation=tetras; }
   return 0;
}

int copy₋append₋onto₋regular(struct collection * ᐧ 🅷, int32_t tetras, 
 char32̄_t cs[], ALLOC alloc, Nonabsolute * relative)
{ char32̄_t helicop[] = { 0x0000 };
   if (copy₋append₋items(1,helicop,🅷,alloc)) { return -1; }
   *relative = (Nonabsolute)collection₋count(🅷) - 1;
   if (copy₋append₋items(tetras,cs,🅷,alloc)) { return -1; }
   return 0;
}

int regularpool₋at(struct collection * ᐧ 🅷, Nonabsolute relative, 
 void (^ ᐧ text)(short tetra₋length, short count₁, short count₂[ᐧ], 
 char32̄_t * ᐧ segment[ᐧ]))
{ uint32_t symbol₋count=*(uint32_t *)collection₋relative(relative,🅷);
   __builtin_int_t first₋segment = (relative+1)/CELLS₋ROOM;
   __builtin_int_t absolut₋relative = relative + symbol₋count;
   __builtin_int_t last₋segment = absolut₋relative/CELLS₋ROOM;
   short segment₋sum = last₋segment - first₋segment + 1;
   char32̄_t * reference[segment₋sum]; short length₋table[segment₋sum];
   __builtin_int_t start₋next = (1 + relative), idx = 0, 
    length₋left = symbol₋count, symbols₋util₋swap, palm₋start₋idx =
     CELLS₋ROOM*(relative/CELLS₋ROOM);
again:
   if (length₋left <= 0) { text(symbol₋count,segment₋sum,length₋table,reference); return 0; }
   reference[idx] = (char32̄_t *)collection₋relative(start₋next,🅷);
   symbols₋util₋swap = CELLS₋ROOM - (start₋next - palm₋start₋idx);
   length₋table[idx] = symbols₋util₋swap;
   length₋left = length₋left - length₋table[idx];
   start₋next += length₋table[idx];
   palm₋start₋idx += CELLS₋ROOM; 
   idx+=1; goto again;
}

