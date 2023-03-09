/*  ❩† pool.c | storing idnetifiers and strings in a pool. */

import Twinbeam;

CORRECT(pool_amend)
{ struct collection H;
   char32̄_t * quotes1 = U"this is an example text", 
    *quotes2 = U" and a second sample";
   if (init₋regularpool(&H)) return;
   Nonabsolute start = collection₋count(&H);
   if (copy₋prepare₋datum(&H,Alloc)) ENSURE(false,"datum");
   if (copy₋append₋onto₋regular(&H,23,quotes1,Alloc)) ENSURE(false,"copy-append1");
   if (copy₋append₋onto₋regular(&H,20,quotes2,Alloc)) ENSURE(false,"copy-append2");
   if (regularpool₋datum₋text(&H,43,start)) ENSURE(false,"datum");
   if (regularpool₋at(&H, start, ^(short symbols₋total, short fragments, 
   	 short symbols[ᐧ], char32̄_t * ᐧ segments[ᐧ]) {
   	print("text is '");
    for (int i=0; i<fragments; i+=1) print("⬚",﹟S(symbols[i],segments[i]));
    print("'.\n");
   })) return;
}

