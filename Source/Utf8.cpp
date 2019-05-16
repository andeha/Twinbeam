//
//  Utf8.cpp
//  Twinbeam
//

#include <Twinbeam.h>

FOCAL
__builtin_int_t
Utf8Followers(uint8_t leadOr8Bit)
{
    if (leadOr8Bit < 128) { return 0; }
    if (128 <= leadOr8Bit && leadOr8Bit < 192) return -1;
    if (248 <= leadOr8Bit) return -1;
    
#ifdef __mips__ /* clz $a0, $v0,   ⃨  possibly clo. */
    __builtin_int_t onesUntilZero = __builtin_clz(~((uint32_t)leadOr8Bit<<24));
#elif defined __x86_64__ /* BSF, BSR, LZCNT, TZCNT, __lzcnt64 on Win64 */
    __builtin_int_t onesUntilZero = __builtin_clzll(~((uint64_t)leadOr8Bit<<56));
#else
    auto clz = ^(uint8_t x) {
      uint8_t 🥈ᵢ lookup[16] = { 4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0 }, upper = x >> 4, lower = x & 0x0F;
      return upper ? lookup[upper] : 4 + lookup[lower];
    };
    __builtin_int_t onesUntilZero = clz(~leadOr8Bit);
#endif
    
    return onesUntilZero - 1;
}

FOCAL
char32_t
Utf8ToUnicode(
  const char *p,
  __builtin_int_t bytes
)
{
    uint8_t first = *p;
    if (248 <= first || (128 <= first && first < 192)) return 0xFFFF;
    switch (bytes) { case 1: return (char32_t)(uint8_t)*p; case 2: return
    (0b11111&*p) << 6 | (0b111111&(*(p + 1))); case 3: return (0b1111&*p) <<
    12 | (0b111111&(*(p + 1))) << 6 | (0b111111&(*(p + 2))); case 4: return
    (0b111&*p) << 18 | (0b111111&(*(p + 1))) << 12 | (0b111111&(*(p + 2))) <<
    6 | (0b111111&(*(p + 3))); } return 0xFFFE;
}

FOCAL
int
TokenizeUtf8OrUnicode(
  Encoding encoding,
  Memoryview content,
  __builtin_int_t& beam,
  void (^/*several-*/character)(char32_t unicode, __builtin_int_t byteOffset, bool& stop)
)
{
    __builtin_int_t bytes = content.byteCount, i = beam;
    SemanticPointer<void *> base = content.region->start();
    while (i < bytes) {
        SemanticPointer<void *> p = content.region->relative(i + content.bytesOffset, base);
        __builtin_int_t charBytes = 4; bool stop = false;
        if (encoding == Encoding::utf8) {
            const char *c = (const char *)p.pointer;
            charBytes = Utf8Followers(*(uint8_t *)c) + 1;
            if (charBytes == -1) return 1; /* Possibly non-utf8 byte. */
            char32_t unicode = Utf8ToUnicode(c, charBytes);
            if (unicode == 0) return 1;
            character(unicode, i, stop);
        } else { character(*(char32_t *)(p.pointer), i, stop); }
        i += charBytes; beam = i;
        if (stop) break;
    }
    return 0;
}

FOCAL
int
Utf8Sync(
  uint8_t **p
) /* Backs at most 3 bytes to regain sync. */
{
    __builtin_int_t i = 3;
#define Utf8IsLead(x) (((x)&0b11000000)==0xD0) // Ensure argument is `uint8_t` or equivalent.
#define Utf8Is8Bit(x) ((x) <= 0x7f)
#define Utf8IsPointerToFollower(p) (((*p)&0b11000000)==0xC0)
    while (i && Utf8IsPointerToFollower(*p)) { (*p)--; i--; }
    return i == 0 || !(Utf8IsLead(**p) || Utf8Is8Bit(**p));
}

FOCAL
int
UnicodeToUtf8(
  char32_t u,
  void (^/*sometimes-*/completion)(const uint8_t *p, int bytes)
)
{
    unsigned char 🥈ᵢ firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0,
      0xF8, 0xFC };
    
    char32_t 🥈ᵢ byteMask = 0xBF, byteMark = 0x80;
    
    unsigned short bytesToWrite = 0;
    
    if (u < (char32_t)0x80) { bytesToWrite = 1; }
    else if (u < (char32_t)0x800) { bytesToWrite = 2; }
    else if (u < (char32_t)0x10000) { bytesToWrite = 3; }
    else if (u <= (char32_t)0x0010FFFF) { bytesToWrite = 4; }
    else { return 1; }
    
    uint8_t target[4];
    
    switch (bytesToWrite) {
        case 4: target[3] = (uint8_t)((u | byteMark) & byteMask); u >>= 6;
        case 3: target[2] = (uint8_t)((u | byteMark) & byteMask); u >>= 6;
        case 2: target[1] = (uint8_t)((u | byteMark) & byteMask); u >>= 6;
        case 1: target[0] = (uint8_t) (u | firstByteMark[bytesToWrite]);
    }
    
    completion(target, bytesToWrite);
    
    return 0;
}
