/*  pamphlet-symbol.c | expands to not more than 'times four'. */

#include "twinbeam-inner.h"

int Utf8ToUnicode(__builtin_int_t u8bytes, char8₋t * encoded, char32̄_t * 
 prealloc₋out, __builtin_int_t * tetras) ⓣ
{ __builtin_int_t i=0,j=0; short bytes; char8₋t *ξ; char32̄_t first, mask=0b111111;
again:
   if (i >= u8bytes) { goto unagain; }
   ξ = i + encoded; first = *ξ;
   if (first < 128) { bytes=0; }
   if (128 <= first && first < 192) { return -1; }
   if (248 <= first) { return -1; }
   bytes = __builtin_clz(~(first<<24));
   switch (bytes) {
    case 0: *(prealloc₋out + j) = first;
     break;
    case 1: *(prealloc₋out + j) = 
      (0b11111 & first)<<6 | (mask & *(ξ+1));
     break;
    case 2: *(prealloc₋out + j) = 
      (0b1111 & first)<<12 | (mask & *(ξ+1))<<6 | (mask & *(ξ+2));
     break;
    case 3: *(prealloc₋out + j) = 
     (0b111 & first)<<18 | (mask & *(ξ+1))<<12 | (mask & *(ξ+2))<<6 | 
     (mask & *(ξ+3));
     break;
    default: return -1;
   }
   i+=bytes+1,j+=1;
   goto again;
unagain:
   *tetras=j;
   return 0;
}

int UnicodeToUtf8(__builtin_int_t u32count, char32̄_t * decoded, char8₋t * 
 prealloc₋out, __builtin_int_t * u8bytes) ⓣ
{ __builtin_int_t i=0,j=0; short bytes, bytesToWrite;
   unsigned char firstByteMark[7] = { 0x00, 0x00, 0xc0, 0xe0, 0xf0,
    0xf8, 0xfc };
   char32̄_t Ξ,bytemask=0xbf,bytemark=0x80;
again:
   if (i >= u32count) { goto unagain; }
   Ξ = *(i + decoded); bytesToWrite=0;
   if (Ξ < 0x80L) { bytesToWrite=1; }
   else if (Ξ < 0x800L) { bytesToWrite=2; }
   else if (Ξ < 0x10000L) { bytesToWrite=3; }
   else if (Ξ <= 0x10ffffL) { bytesToWrite=4; }
   else { return -1; }
   switch (bytesToWrite) {
   case 4: *(prealloc₋out + j + 3) = (char8₋t)((Ξ | bytemark) & bytemask); Ξ >>= 6;
   case 3: *(prealloc₋out + j + 2) = (char8₋t)((Ξ | bytemark) & bytemask); Ξ >>= 6;
   case 2: *(prealloc₋out + j + 1) = (char8₋t)((Ξ | bytemark) & bytemask); Ξ >>= 6;
   case 1: *(prealloc₋out + j + 0) = (char8₋t) (Ξ | firstByteMark[bytesToWrite]);
   }
   j+=bytesToWrite,i+=1;
   goto again;
unagain:
   *u8bytes=j;
   return 0;
}

char8₋t * retranscript(char8₋t * u8s, __builtin_int_t maxu8bytes𝘖rZero)
{
   __builtin_int_t bytes = Utf8BytesUntilZero(u8s,maxu8bytes𝘖rZero);
   void * start = Heap₋alloc(bytes);
   Copy8Memory((ByteAlignedRef)start,(ByteAlignedRef)u8s,bytes);
   return start;
} /*  a․𝘬․a strdup₋for₋utf8, Signal,  u8record and Branch. Note U+8000 in UTF-8 is E0 *) *). */

int ReflectUtf8AlternativelyUnicode(enum Encoding type, __builtin_int_t bytes, 
 uint8_t * material, char32̄_t * decoded, __builtin_int_t * tetras)
{ char32̄_t * text = Heap₋alloc(bytes);
   if (type == encoding₋unicode) {
     Copy8Memory((ByteAlignedRef)decoded,(ByteAlignedRef)material,bytes);
     *tetras = bytes/4;
   } else {
     Utf8ToUnicode(bytes,(char8₋t *)material,decoded,tetras);
   }
   return 0;
}
