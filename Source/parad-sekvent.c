/*  parad-sekvent.c | /in-te 'mōn-ster'/. */

import Twinbeam;

#define PAGE₋SIZE 8192

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
   uint32_t * ation = (uint32_t *)collection₋relative(4*relative,🅷);
   if (ation) { *ation=tetras; }
   return 0;
}

int copy₋append₋onto₋regular(struct collection * ᐧ 🅷, int32_t tetras, 
 char32̄_t cs[], ALLOC alloc, Nonabsolute *   relative)
{
   if (copy₋append₋items(4*tetras,cs,🅷,alloc)) { return -1; }
   return 0;
}

int regularpool₋at(struct collection * ᐧ 🅷, Nonabsolute reference, void (^ ᐧ 
 segment)(int symbols₋total, int count₋segments, int symbols₋segment[ᐧ], 
  char32̄_t * ᐧ segment[ᐧ]))
{ uint32_t symbol₋count=*(uint32_t *)collection₋relative(reference,🅷);
   int segment₋sum = 1 + (4*symbol₋count)/PAGE₋SIZE;
   char32̄_t * assort[segment₋sum]; int symbols[segment₋sum];
   __builtin_int_t symbol₋idx=reference,segment₋idx=0,symbol₋augment,symbol₋summand=0;
again:
   if (segment₋idx == 0) {  __builtin_int_t page₋number=(4*reference)/PAGE₋SIZE, 
      symbolslots₋per₋page=PAGE₋SIZE/4, symbols₋until₋end₋of₋page = reference - 
      page₋number*symbolslots₋per₋page;
     symbol₋augment = min(symbols₋until₋end₋of₋page,symbol₋count);
   } else if (segment₋idx == segment₋sum - 1) { symbol₋augment = symbol₋count - symbol₋idx; }
   else { symbol₋augment = PAGE₋SIZE; }
   symbols[segment₋idx] = symbol₋augment;
   assort[segment₋idx] = (char32̄_t *)collection₋relative(4 + 4*symbol₋idx,🅷);
   if (segment₋idx >= segment₋sum)
   {
     segment(symbol₋count,segment₋sum,symbols,assort);
     return 0;
   }
   segment₋idx+=1,symbol₋idx+=symbol₋augment; goto again;
}
