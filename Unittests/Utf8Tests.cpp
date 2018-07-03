//
//  Utf8Tests.cpp
//  Twinbeam Tests
//

#include <Twinbeam/Twinbeam.h>

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
        ENSURE(p[2] == 0x8d, "Utf8_UnicodeToUtf8_1 1");
        ENSURE(p[3] == 0x88, "Utf8_UnicodeToUtf8_1 2");
    }))
    { ENSURE(false, "Utf8_UnicodeToUtf8_1 failed"); }
}

UNITTEST(Utf8_TokenizeUtf8OrUnicode_1)
{
    const char32_t *text = U"alias \n";
    __builtin_int_t tetras = UnicodesUntilNull(text, BUILTIN_INT_MAX);
    Memoryregion region { (void *)text, tetras<<2 };
    Memoryview view { &region, 0, region.bytes() };
    __builtin_int_t beam = 0;
    int x = TokenizeUtf8OrUnicode(Encoding::unicode, view, beam,
      ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) {
          const char *name = UnicodePrimaryName(unicode);
          printf("%s\n", name);
      });
    ENSURE(x == 0, "Utf8_TokenizeUtf8OrUnicode_1 failed");
}

UNITTEST(Utf8_TokenizeUtf8OrUnicode_2)
{
    const char *utf8text = "alias \n";
    __builtin_int_t bytes = Utf8BytesUntilNull(utf8text, BUILTIN_INT_MAX);
    Memoryregion region { (void *)utf8text, bytes };
    Memoryview view { &region, 0, region.bytes() };
    __builtin_int_t beam = 0;
    int x = TokenizeUtf8OrUnicode(Encoding::utf8, view, beam,
      ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) {
          const char *name = UnicodePrimaryName(unicode);
          printf("%s\n", name);
      });
    ENSURE(x == 0, "Utf8_TokenizeUtf8OrUnicode_2 failed");
}
