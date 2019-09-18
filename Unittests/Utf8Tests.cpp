/*  Utf8Tests.cpp | Twinbeam Tests. */

#include <Twinbeam.h>

UNITTEST(Utf8_Utf8ToUnicode_1)
{
   uint8_t buf[] = { 'A' };
MEASURE_START(Utf8ToUnicode_Utf8_Utf8ToUnicode_1)
   __builtin_int_t followers = Utf8Followers(buf[0]);
   char32_t c = Utf8ToUnicode(&buf[0], followers + 1);
MEASURE_END(Utf8ToUnicode_Utf8_Utf8ToUnicode_1)
   ENSURE(c == 0x00041, "Utf8_Utf8ToUnicode_1 1");
}

UNITTEST(Utf8_Utf8ToUnicode_2)
{
   uint8_t buf[] = { 0xC2, 0xA2 };
   __builtin_int_t followers = Utf8Followers(buf[0]);
   char32_t c = Utf8ToUnicode(&buf[0], followers + 1);
   ENSURE(c == 0x000A2, "Utf8_Utf8ToUnicode_2 1");
}

UNITTEST(Utf8_Utf8ToUnicode_3)
{
   uint8_t buf[] = { 0xf0, 0x90, 0x8d, 0x88 };
   __builtin_int_t followers = Utf8Followers(buf[0]);
   char32_t c = Utf8ToUnicode(&buf[0], followers + 1);
   ENSURE(c == 0x10348, "Utf8_Utf8ToUnicode_3 1");
}

UNITTEST(Utf8_UnicodeToUtf8_1)
{
   if (UnicodeToUtf8(0x10348, ^(const uint8_t *p, int bytes) {
     ENSURE(p[0] == 0xf0, "Utf8_UnicodeToUtf8_1 1");
     ENSURE(p[1] == 0x90, "Utf8_UnicodeToUtf8_1 2");
     ENSURE(p[2] == 0x8d, "Utf8_UnicodeToUtf8_1 3");
     ENSURE(p[3] == 0x88, "Utf8_UnicodeToUtf8_1 4");
   }))
   { ENSURE(false, "Utf8_UnicodeToUtf8_1 failed"); }
}

UNITTEST(Utf8_Utf8Sync_1)
{ /* 😅 F0 9F 98 85, 😬 F0 9F 98 AC, 😐 F0 9F 98 90 */
   const char utf8[] = { '\xF0', '\x9F', '\x98', '\x85', '\xF0', '\x9F', 
     '\x98', '\xAC', '\xF0', '\x9F', '\x98', '\x90' };
   uint8_t * p = (uint8_t *)(utf8 + 5);
   if (Utf8Sync(&p)) { print("Utf8Sync failed\n"); }
   ENSURE(*p == 0xF0, "Utf8_Utf8Sync_1");
}

