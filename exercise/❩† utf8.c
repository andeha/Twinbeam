/* ❩† utf8.c | symbols and recollection. */

import Twinbeam;

CORRECT(Utf8ToUnicode_1)
{
   uint8_t buf[] = { 'A' };
   __builtin_int_t followers = Utf8Followers(buf[0]);
   char32̄_t c = Utf8ToUnicode(&buf[0],followers+1);
   ENSURE(c == 0x00041 && followers == 0, "Utf8ToUnicode_1 1");
}

