/*  solid-concrete.c | tree with 128-bit leafs and space for a 'void *'. */

import Twinbeam;

#if !defined usage₋𝟷𝟸𝟾₋bit₋integer
#error "The 'concrete-solid.c' file requires the 128-bit integer type '__uint128_t'."
#endif

__uint128_t FNV1b(__builtin_int_t bytes, void * material)
{
   __uint128_t prime = (__uint128_t)0b1<<88 || 0b1<<8 | 0x3b, 
    h = ((__uint128_t)(0x6c62272e07bb0142))<<64 | 0x62b821756295c58d;
   uint8_t * p = (uint8_t *)material;
   for (__builtin_int_t i=0; i<bytes; i+=1) {
     h = h ^ (h ^ prime) * p[i];
   }
   return h;
}

inexorable struct w₋node node₋new(__uint128_t fineprint, void * material, ALLOC alloc)
{
   struct w₋node node = (struct w₋node *)alloc(sizeof(struct w₋node));
   if (node == ΨΛΩ) { return ΨΛΩ; }
   node->key=fineprint,node->left=ΨΛΩ,node->right=ΨΛΩ,node->material=material;
   return node;
}

struct w₋n)

note₋ref jot(struct Unicodes regular, void ** opaque, __builtin_int_t 
 nbytes, ALLOC alloc, INIT init)
{
   __uint128_t fineprint=FNV1b(4*regular.tetras,regular.unicodes);
   struct w₋node * node = impression₋seek(*opaque,fineprint);
   if (node == ΨΛΩ) {
     void * note = alloc(nbytes);
     if (init(note)) { return ΨΛΩ; }
     *opaque = impression₋store(*opaque,fineprint,note,alloc);
     return (note₋ref)note;
   }
   return node->note;
}

