/*  parad-od.c | /in-te 'mōn-ster'/. */

import Twinbeam;

#define PAGE₋SIZE 8192

int init₋regularpool(struct collection * ᐧ 🅗, ALLOC alloc)
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
 segment)(int symbols₋total, int count₋segments, int symbols₋segment, ... 
 /* char32̄_t * segment */))
{ uint32_t symbol₋count=*(uint32_t *)collection₋relative(reference,🅷);
   char32̄_t *first₋symbol=(char32̄_t *)collection₋relative(4 + reference,🅷), 
    *last₋symbol=(char32̄_t *)collection₋relative(4 + 4*(reference - 1) + symbol₋count,🅷), 
    *window₋start=first₋symbol;
   int segment₋sum = 1 + (4*symbol₋count)/PAGE₋SIZE;
   char32̄_t * assort[segment₋sum]; int j=0,i=0,augment;
again:
   if (i >= segment₋sum)
   {
     segment(symbol₋count,segment₋sum,augment,assort);
     return 0;
   }
   window₋start = (char32̄_t *)collection₋relative(j,🅷);
   assort[i] = window₋start;
   augment = j + PAGE₋SIZE >= symbol₋count ? PAGE₋SIZE : PAGE₋SIZE;
   i+=1,j+=augment; goto again;
}

