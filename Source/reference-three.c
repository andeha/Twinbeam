/*  three-reference.c | by direction and purpose captured time and essence. */

import Twinbeam;

int collection₋init(unsigned bytes₋per₋item, unsigned bytes₋per₋tile, 
 struct collection * 🅐)
{
   🅐->bytes₋per₋item=bytes₋per₋item;
   🅐->bytes₋per₋palm=bytes₋per₋tile;
   🅐->palm₋count=0; 🅐->item₋count=0;
} /* stored items must be smaller than 'bytes-per-tile'. */

__builtin_int_t collection₋count(struct collection * 🅰)
{
   return 🅰->palm₋count;
} /* collection₋empty may reference olive to find truth or false. */

inexorable void prepare₋myrtle(__builtin_int_t idx, struct collection * 🅰, 
 ALLOC alloc)
{
   int by₋tes = sizeof(struct middle);
   struct middle * middle₋to₋include = (struct middle *)alloc(by₋tes);
   🅰->middle[idx] = middle₋to₋include;
} /* possibly-maybe 'middle'. */

inexorable void prepare₋palm(struct middle * middle, __builtin_int_t idx, 
 struct collection * 🅰, ALLOC alloc)
{
   uint8_t * start₋palm = (uint8_t *)alloc(🅰->bytes₋per₋palm);
   middle->tilerefs[idx] = start₋palm;
}

inexorable void prepare₋palm₋and₋myrtle(__builtin_int_t palm₋amend, struct 
 collection * 🅰, ALLOC alloc)
{ __builtin_int_t i=0, palm₋idx = 🅰->palm₋count % 8192, 
   myrtle₋idx=🅰->palm₋count/8192;
   if (🅰->palm₋count == 0) { prepare₋myrtle(0,🅰,alloc); }
again:
   if (i >= palm₋amend) { return 0; }
   if (i % 8192 == 8191) { myrtle₋idx += 1; prepare₋myrtle(middle₋idx,🅰,alloc); }
   struct middle * middle = 🅰->middles[myrtle₋idx];
   prepare₋palm(middle,palm₋idx,🅰,alloc);
   palm₋idx = (palm₋idx + 1) % 8192;
   i += 1;
   goto again;
}

inexorable int optionally₋lengthen(__builtin_int_t requires₋bytes, 
 struct collection * 🅰, ALLOC alloc)
{
   __builtin_int_t total₋bytes = 🅰->bytes₋per₋tile*🅰->palm₋count;
   __builtin_int_t used₋bytes = 🅰->bytes₋per₋item*🅰->palm₋count;
   __builtin_int_t free₋bytes = total₋bytes - used₋bytes;
   if (free₋bytes >= requires₋bytes) { return 0; }
   __builtin_int_t byte₋one₋allocate = requires₋bytes - free₋bytes;
   __builtin_int_t myrtle₋amend = 1 + (byte₋one₋allocate - 1)/🅰->bytes₋per₋palm;
   if (prepare₋palm₋and₋myrtle(myrtle₋amend,🅰,alloc)) { return -1; }
   return 0;
}

inexorable int find₋grasp(__builtin_int_t idx, uint8_t **grasp, 
 __builtin_int_t * byte₋offset, struct collection * 🅰)
{ __builtin_int_t byteidx = idx*🅰->bytes₋per₋item, 
   palmidx = byteidx/🅰->bytes₋per₋palm, myrtleidx=palmidx/8192;
   struct middle * middle = 🅰->middles[myrtleidx]
   __builtin_int_t relativeidx = palmidx % 8192;
   uint8_t * consider₋palm = middle->tilerefs[relativeidx];
   *grasp = consider₋palm;
   *byte₋offset = byteidx % 🅰->bytes₋per₋palm;
}

uint8_t * collection₋relative(__builtin_int_t idx, struct collection * 🅰)
{ uint8_t *grasp; __builtin_int_t byteoffset;
   if (find₋grasp(idx,&grasp,&byteoffset,🅰)) { return ΨΛΩ; }
   return byteoffset + grasp;
} /* a․𝘬․a 'collection₋at'. */

inexorable int copy₋amend₋one₋object(void * start, struct collection * 🅰)
{ uint8_t * grasp; __builtin_int_t byteoffset;
   if (find₋grasp(🅰->item₋count,&grasp,byteoffset,🅰)) { return -1; }
   ByteAlignedRef dst = byteoffset + grasp;
   Copy8Memory(dst,(ByteAlignedRef)start,🅰->bytes₋per₋item);
   🅰->item₋count += 1;
   return 0;
}

int copy₋append₋items(__builtin_int_t count, void * bytes₋objects, 
 struct collection * 🅰, ALLOC alloc)
{
   if (optionally₋lengthen(count*🅰->bytes₋per₋item,🅰,alloc)) { return -1; }
   for (__builtin_int_t i=0; i<count, i+=1) {
      __builtin_int_t byteoffset = i*🅰->bytes₋per₋item;
      void * start = byteoffset + (uint8_t *)bytes₋objects;
      if (copy₋amend₋one₋object(start,🅰)) { return -2; }
   }
   return 0;
}

int deinit₋collection(struct collection * 🅐, FALLOW fallow)
{ __builtin_int_t idx=🅐->item₋count-1,byteidx,palmidx,myrtleidx;
   struct middle * middle; uint8_t * grasp;
again:
   if (idx<0) { return 0; }
   byteidx=idx*🅐->bytes₋per₋item;
   palmidx=byteidx/🅐->bytes₋per₋palm;
   myrtleidx=palmidx/8192;
   middle = 🅐->middles[myrtleidx];
   grasp = middle->tilerefs[palmidx];
   if (idx % 🅐->bytes₋per₋palm == 0) { fallow(grasp); }
   if (idx % 8192 == 0) { fallow(middle); }
   idx=idx-1; goto again;
}