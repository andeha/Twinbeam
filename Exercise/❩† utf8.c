/* ❩† utf8.c | symbols and recollection. */

#include "Twinbeam.h"

CORRECT(Utf8ToUnicode_1)
{
   uint8_t buf[] = { 'A' };
   __builtin_int_t followers = Utf8Followers(buf[0]);
   char32̄_t c = Utf8ToUnicode(&buf[0],followers+1);
   ENSURE(c == 0x00041 && followers == 0, "Utf8ToUnicode_1 1");
}

CORRECT(UnicodeToUtf8_1)
{
   if (UnicodeToUtf8(U'Ξ', ^(char8₋t * ξ, short bytes) {
     ENSURE(bytes == 2 && *(ξ+0) == 0xce && *(ξ+1)==0x9e, "UnicodeToUtf8_1 2");
   })) ENSURE(false, "UnicodeToUtf8_1 1");
}

CORRECT(Utf8ToUnicode_2)
{
   uint8_t buf[] = { 'A', 'B', 'C' };
   char32̄_t prealloc[4*3]; __builtin_int_t tetras;
   if (Utf8ToUnicode(3,buf,prealloc,&tetras)) ENSURE(false, "Utf8ToUnicode_2 1");
   ENSURE(tetras == 3, "Utf8ToUnicode_2 2");
}

CORRECT(UnicodeToUtf8_2)
{
   char32̄_t decoded[] = { U'A', U'B', U'C' };
   char8₋t prealloc[4*3]; __builtin_int_t u8bytes;
   if (UnicodeToUtf8(3,decoded,prealloc,&u8bytes)) ENSURE(false, "UnicodeToUtf8_2 1");
}
