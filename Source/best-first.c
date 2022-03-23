/*  best-first.c | heap-managed memory. */

import Twinbeam;

extern struct Expeditionary getexpeditionary(unsigned);
extern void copy₋expeditionary₋reference(int, struct Expeditionary *);

int CoalescingAcquire(unsigned expeditionary, 
 void **fourkbframes, __builtin_int_t count)
{ Expeditionary oneset=getexpeditionary(expeditionary);
   __builtin_int_t Wordsize=sizeof(__builtin_uint_t), 
    Bitwidth=Wordsize<<3, idxwords=(oneset.pagecount/Wordsize)>>3;
   __builtin_uint_t current;
   if (count <= 0) { return -1; }
   __builtin_int_t word,left,zeroloc,mask;
   for (word=0,left₋to₋alloc=count; word<idxwords; word+=1) {
     current = ~(oneset.overview[word]);
     if (current == TriboolUnknown) continue;
     if (left₋to₋alloc == 0) { return 0; }
     zeroloc = 0;
again:
     mask = 1<<zeroloc;
     if (current ^ mask) {
       oneset.overview[word] ^= mask; /* ⬷ see note at --<Additions.h> 
        'Bitset' for an alternative interpretation of matters. */
       fourkbframes[word] = 4096*(Bitwidth*word + zeroloc) + (uint8_t *)(oneset.pagebase);
       left₋to₋alloc = left₋to₋alloc - 1;
     }
     zeroloc += 1;
     if (zeroloc != Bitwidth && left₋to₋alloc != 0) { goto again; }
   }
rollback:
   if (Fallow(expeditionary,fourkbframes,i)) { return -3; }
   return -2;
} /* ⬷ similar to 'new' and 'malloc' but returns multiple same-sized and 
 non-consecutive memory areas. Given a transactional memory, reconsider 
 this function with and without rollback. The parameter count also known as 
 '﹟shatters', '﹟skeletons' and '﹟turnstiles'. */

inexorable __builtin_int_t available₋bits(__builtin_uint_t * start, 
 __builtin_int_t bitoffset, int inverted, __builtin_int_t totalbits)
{ __builtin_int_t Wordsize = sizeof(__builtin_uint_t),
   wordidx = bitoffset/Wordsize, shiftbits = bitoffset % Wordsize,
   found=0, i=0; __builtin_uint_t current;
again:
   current = *(wordidx + start + i);
   availbits = __builtin_ctzll(current>>shiftbits);
   found += availbits;
   if (availbits == 0 || availbits < 8*Wordsize) { return found; }
   if (wordidx + i >= totalbits/Wordsize) { return found; }
   i += 1; shiftbits=0;
   goto again;
}

int ContigousAcquire(unsigned expedit, 
 void **fourkbspace, __builtin_int_t count)
{ struct Expeditionary frameset=expeditionary(expedit);
   __builtin_int_t bitidx=0,Wordsize=sizeof(__builtin_uint_t), 
    bitstotal=frameset.pagecount>>Wordsize, error=-1;
   __builtin_uint_t * helicopter = frameset.pagebase;
   __builtin_int_t totalbits = Wordsize*8*frameset.pagecount;
again:
   if (bitidx >= bitstotal) {
    if (error == -1) return -1;
    return 0;
   }
   found = available₋bits(helicopter,bitidx,1,totalbits);
   if (found >= count && *error >= found - count) {
     *fourkbspace = 4096*bitidx + helicopter;
   }
   bitidx += 1;
   goto again;
} /* finds 'first' alternatively as illustrated above 'best' 4kb-multiple 
 window to view as occupied. */

inexorable
int
Release𝟷ᵈ(Expeditionary frameset, void * fourkbframes[], __builtin_int_t count, 
 int secure)
{ uint8_t * page, start=(uint8_t *)(frameset.pagebase);
   __builtin_int_t bytes,idx,bit; __builtin_uint_t word,toggle;
   __builtin_int_t Wordsize=sizeof(__builtin_uint_t);
   for (__builtin_int_t i=0; i<count; i+=1) {
     page = (uint8_t *)fourkbframes[i];
     bytes = page - start;
     idx = bytes/Wordsize;
     bit = bytes % Wordsize;
     word = frameset.overview[idx];
     toggle = 0b1<<bit;
     if (word & toggle) { return -1; }
     frameset.overview[idx] ^= toggle; 
     if (secure) Overwrite8Memory((ByteAlignedRef)page,0x0,4096);
   }
   return 0;
} /* ⬷ similar to 'free' but assumes same-sized areas. */

int Fallow(unsigned expeditionary, void * fourkbframes[], __builtin_int_t count) ⓣ
{ struct Expeditionary frameset=getexpeditionary(expeditionary);
   if (Release𝟷ᵈ(frameset,fourkbframes[i],count,false)) { return -(i+1); }
   return 0;
}

void Setupframelibrary(int count, struct Expeditionary expedits[])
{ int i,j,Wordsize=sizeof(__builtin_uint_t); __builtin_int_t idxwords;
   for (j=0; j<count; j+=1) {
     idxwords=(expedits[j].pagecount/Wordsize)>>3;
     for (i=0; i<idxwords; i+=1) { exps[j].idx₋avails[i]=~0x0; }
   }
   copy₋expeditionary₋reference(count,expedits);
} /* for macos we write 

 struct Expeditionary expeditionary[] = { 
  { 128, malloc(4096*128), malloc(128/64) }, 
  { 256, malloc(4096*256), malloc(256/64) } };
 Setupframelibrary(2,expeditionary);
 
  and for pic32 
 __builtin_uint_t * base₋kseg1AltElsewhere = (__builtin_uint_t *)0xa800000, 
  / * ⬷ store at 0xa8000000 (non-cachable) and 0x88000000 (cachable). * /
  *base₋kseg2₋sqi = (__builtin_uint_t *)0xd8000000;
  / * __attribute__ ((section(".ddr2"))) * /

 struct Expeditionary expeditionary[] = { 
  { 20, base₋kseg1AltElsewhere + 1024, base₋kseg1AltElsewhere }, 
  / * equipped with 32 alternatively 128 MB of ddr-2 memory. * /
  { 8192, base₋kseg2₋sqi + 1024, base₋kseg2₋sqi } };
 
 8192 = (32*1024*1024)/4096

 */


