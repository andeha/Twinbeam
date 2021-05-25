/*  rt-pdb.cpp | miscellaneous. */

#include <Twinbeam.h>
#include <Additions/Additions.h> /* ⬷ import Twinbeam. */
#include <stdio.h> /* ⬷ 'stdin', 'write' and 'fgetc'/'fgetwc'. */

void
Base𝕟( /* TeX §64, §65 and §67. */
  __builtin_uint_t ℕ,
  unsigned short base,
  unsigned short digitsOr0, /* ⬷ not more than 32 or 64 digits depending on 
    your machines' word size! (Or set to `0` to skip leading zeros.) */
  void (^output)(char 𝟬to𝟵)
)
{
    auto 𝟬to𝗙 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0 }; short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 𝟬to𝗙(cycle[k], 
      output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k--; }
       for (; k >= 0; k--) { 𝟬to𝗙(cycle[k], output); }
    }
} /*  ⬷ note 128-bit duplicate in --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp> and --<Print.cpp>. */

int
IsPrefixOrEqual(
  const char * 𝟽alt𝟾₋bitstring, /* ⬷ possibly 'normalizedUtf8' */
  const char * 𝟽alt𝟾₋bitprefix  /* ⬷ smiley appears when 'prompt> nm'! */
) /* ⬷ consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
{  const char *s=𝟽alt𝟾₋bitstring, *p=𝟽alt𝟾₋bitprefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters 'string' and 'prefix' are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in 'prefix' equal to 'string'. Return first character following 'eightbitPrefix'. */
    /* *p != 0 && *s != 0 */
    char diff = *s - *p;
    if (diff) { return 0; }
    s++, p++;
    goto again;
}

FOCAL
short
Utf8Followers(char8_t leadOr8Bit)
{
    if (leadOr8Bit < 128) { return 0; }
    if (128 <= leadOr8Bit && leadOr8Bit < 192) return -1;
    if (248 <= leadOr8Bit) return -1;
    
#if defined __mips__ || defined __armv6__ || defined __armv8a__
    /* Mips: clz $a0, $v0, Arm: clz r0, r14. */
    __builtin_int_t onesUntilZero = __builtin_clz(~((uint32_t)leadOr8Bit<<24));
#elif defined __x86_64__ /* BSF, BSR, LZCNT, TZCNT, __lzcnt64 on Win64. */
    __builtin_int_t onesUntilZero = __builtin_clzll(~((uint64_t)leadOr8Bit<<56));
#else
    auto clz = ^(uint8_t x) {
      uint8_t 🥈ᵢ lookup[16] = { 4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 
        0, 0, 0 }, upper = x >> 4, lower = x & 0x0F;
      return upper ? lookup[upper] : 4 + lookup[lower];
    };
    __builtin_int_t onesUntilZero = clz(~leadOr8Bit);
#endif
    
    return (short)onesUntilZero - 1;
}

FOCAL
int
UnicodeToUtf8(
  char32_t Ξ,
  void (^sometime₋valid)(char8_t *u8s, short bytes)
)
{
    unsigned char 🥈 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 
      0xF8, 0xFC };
    
    char32_t 🥈 byteMask=0xBF, byteMark=0x80;
    
    short bytesToWrite=0;
    
    if (Ξ < 0x80L) { bytesToWrite=1; }
    else if (Ξ < 0x800L) { bytesToWrite=2; }
    else if (Ξ < 0x10000L) { bytesToWrite=3; }
    else if (Ξ <= 0x0010FFFFL) { bytesToWrite=4; }
    else { return 1; }
    
    char8_t target[4];
    
    switch (bytesToWrite) {
    case 4: target[3] = (char8_t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 3: target[2] = (char8_t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 2: target[1] = (char8_t)((Ξ | byteMark) & byteMask); Ξ >>= 6;
    case 1: target[0] = (char8_t) (Ξ | firstByteMark[bytesToWrite]);
    }
    
    sometime₋valid(target,bytesToWrite);
    
    return 0;
}

Opt<__builtin_int_t>
CastTˣᵗToInt(
  CastToIntOpinion (^feeder)(unsigned short &digit)
)
{ __builtin_int_t val = 0; __block unsigned short zero_to_nine; int sgn = 1;
   while (1) {
      CastToIntOpinion opinion = feeder(zero_to_nine);
      /* C++20 syntax: 'using enum CastToIntOpinion;' */
      switch (opinion) {
       case CastToIntOpinion::accept: val *= 10; val += sgn*zero_to_nine; break;
       case CastToIntOpinion::rejecting: continue;
       case CastToIntOpinion::negate: sgn *= -1; break;
       case CastToIntOpinion::commit: return Opt<__builtin_int_t>(val);
       case CastToIntOpinion::annul: return Opt<__builtin_int_t>::no();
      }
   }
}

__builtin_int_t
Utf8BytesUntilNull(
  char8_t * u8s,
  __builtin_int_t maxbytes
)
{ __builtin_int_t i=0;
again:
   if (i >= maxbytes) { return maxbytes; }
   char8_t * leadOr8Bit = u8s + i;
   if (*leadOr8Bit == 0x0) { return i; }
   __builtin_int_t followers = Utf8Followers(*leadOr8Bit);
   if (followers < 0) { return -1; }
   i += followers + 1;
   goto again;
}

__builtin_int_t TetrasUntilNull(char32_t * ucs, __builtin_int_t maxtetras)
{ __builtin_int_t i=0;
again:
   if (i >= maxtetras) { return maxtetras; }
   char32_t * uc = ucs + i;
   if (*uc == 0x0000) { return i; }
   ++i; goto again;
}


