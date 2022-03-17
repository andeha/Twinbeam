/*  arrange-fifo.c | one, zero or two halves are always returned. */

import Twinbeam;

int init₋fifo(struct fifo * 🅵, __builtin_int_t words, void * one₋tile)
{ 🅵->words₋to₋unity=words;
   🅵->𝟷₋tile=(__builtin_uint_t *)one₋tile;
   🅵->brk=0; 🅵->count=0;
   return 0;
}

void one₋tile₋pop(struct fifo * 🅵)
{
   🅵->brk = 🅵->brk - 1;
   if (🅵->brk < 0) { 🅵->brk = 🅵->words₋to₋unity - 1; }
   🅵->count = 🅵->count - 1;
}

void one₋tile₋shiftout(struct fifo * 🅵, __builtin_int_t words)
{
   🅵->count = 🅵->count - words;
}

MACRO int one₋tile₋empty(struct fifo * 🅵) { return 🅵->count == 0; }

inexorable void one₋tile₋include(__builtin_int_t maxelems, __builtin_int_t * brk, 
  __builtin_int_t * count, __builtin_int_t augment₋count)
{
   *brk = (*brk + augment₋count) % maxelems;
   *count = augment₋count + *count;
}

int one₋tile₋copy₋include(struct fifo * 🅵, __builtin_int_t ﹟, 
  __builtin_uint_t * words)
{ __builtin_int_t words₋until₋wrap, sequenced₋words₋to₋write,
   sequenced₋bytes₋to₋write, sequenced₋words₋persisted=0, brk₋after₋wrap, 
   words₋left₋to₋write; int Wordbytes=sizeof(__builtin_uint_t);
again:
   words₋until₋wrap = 🅵->words₋to₋unity - 🅵->brk;
   words₋left₋to₋write = ﹟ - sequenced₋words₋persisted;
   sequenced₋words₋to₋write = min(words₋until₋wrap,words₋left₋to₋write);
   sequenced₋bytes₋to₋write = Wordbytes * sequenced₋words₋to₋write;
   if (sequenced₋bytes₋to₋write <= 0) { return 0; }
   Copy8Memory((ByteAlignedRef)(🅵->brk + 🅵->one₋tile),
    (ByteAlignedRef)(words + sequenced₋words₋persisted), 
    sequenced₋bytes₋to₋write);
   one₋tile₋include(🅵->words₋to₋unity,&(🅵->brk),&(🅵->count),﹟);
   sequenced₋words₋persisted += sequenced₋words₋to₋write;
   goto again;
}

inexorable int one₋tile₋physical(__builtin_int_t nowdelta, __builtin_int_t brk, 
 __builtin_int_t maxelems) 
{
   __builtin_int_t brk₋₁ = (brk == 0) ? (maxelems - 1) : (brk - 1); /* ⬷ cases 'may' and 'may-not' wrap. */
   __builtin_int_t actual = brk₋₁ - nowdelta;
   if (actual < 0) { actual = maxelems - (actual + 1); } /* ⬷ mirror back to interval. */
   return actual;
}

inexorable __builtin_uint_t * one₋tile₋deref(__builtin_int_t δ, struct fifo * 🅵)
{ return one₋tile₋physical(δ,🅵->brk,🅵->count); }

__builtin_uint_t * one₋tile₋bank(__builtin_int_t idx, struct fifo * 🅵)
{ return one₋tile₋empty(🅵) ? ΨΛΩ : one₋tile₋deref(idx,🅵); }

__builtin_uint_t * one₋tile₋chronologic(struct fifo * 🅵, __builtin_int_t idx)
{ return one₋tile₋empty(🅵) ? ΨΛΩ : one₋tile₋deref(🅵->count - 1 + idx,🅵); }

__builtin_uint_t * one₋tile₋youngest(struct fifo * 🅵)
{ return one₋tile₋empty(🅵) ? ΨΛΩ : one₋tile₋bank(0,🅵); }

__builtin_uint_t * one₋tile₋oldest(struct fifo * 🅵)
{ return one₋tile₋empty(🅵) ? ΨΛΩ : one₋tile₋chronologic(🅵,🅵->count - 1); }

/* unfinished computational recollect functions. */

/* int one₋tile₋four₋Chronologic(int unused, int actual, 
 struct fifo * q, char8_t * little₋endian₋𝟺to1₋bytes)
{
   return 0;
} */

int one₋tile₋retrospect(enum fifo₋flavor f, struct fifo * q, 
 __builtin_uint_t * t, __builtin_uint_t * t₋₁
)
{
   switch (q->count) {
   case 0: return -1; 
   case 1: *t₋₁=*t=*one₋tile₋deref(0,q); return 0;
   default: switch (f) {
    case fifo₋flavor₋allinorder:
      *t₋₁ = *one₋tile₋deref(q->count - 1,q);
      *t = *one₋tile₋deref(q->count - 2,q);
      break;
    case fifo₋flavor₋latest:
      *t = *one₋tile₋deref(0,q);
      *t₋₁ = *one₋tile₋deref(1,q);
      break;
   } } return 0;
} /* further  --<System.h>{actual} where two queues and 
 interpolation results in a `simd_tᵦ` and irreversibly 'momentan-
 retrospectiv'. */

/* See also 'man mkfifo' and 'man mknod'. Further, see --<Additions>--<math
 >--<romberg.cpp> for a ∫-method that is not on-line. */




