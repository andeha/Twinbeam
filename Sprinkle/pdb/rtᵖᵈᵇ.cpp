/* rtᵖᵈᵇ.cpp - Miscellaneous. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

void
Base𝕟( /* TeX §64, §65 and §67. */
  __builtin_uint_t ℕ,
  unsigned short base,
  unsigned short digitsOr0, /* Not more than 32 or 64 digits depending on 
    your machines' word size! (Or set to `0` to skip leading zeros.) */
  void (^output)(char 𝟶to𝟿)
)
{
    auto 𝟶to𝙵 = ^(unsigned short r, void (^out)(char utf8)) { r < 10 ? 
      out('0' + r) : out('a' - 10 + r); };
    
    unsigned short cycle[64] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
      0, 0, 0, 0 }; short k = 0;
    
    do { cycle[k] = ℕ % base; ℕ /= base; k++; } while (ℕ);
    
    if (digitsOr0) { for (k = digitsOr0 - 1; k >= 0; k--) { 𝟶to𝙵(cycle[k], 
      output); } } else { k = 63; while (cycle[k] == 0 && k > 0) { k--; }
       for (; k >= 0; k--) { 𝟶to𝙵(cycle[k], output); }
    }
} /* See also --<🥽 𝙋𝙧𝙞𝙣𝙩⁺.cpp>. */

int
IsPrefixOrEqual(
  const char * eightbitString, /* Possibly `normalizedUtf8` */
  const char * eightbitPrefix  /* Smiley appears when `prompt> nm`! */
) /* Consider changing dwarf-'.elf' to 'trie' instead of 'table'. */
{
    const char *s=eightbitString, *p=eightbitPrefix;
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are both empty therefore equal. */
    if (!*s) { return 0; } /* Non-equal since the string is empty and a prefix exists. */
    if (!*p) { return *s; } /* The prefix is empty but not the string, return dist(0, non-end). */
again:
    if (*s == 0 && *p == 0) { return -1; }  /* Parameters `string` and `prefix` are non-empty and equal. */
    if (*s == 0 && *p != 0) { return 0; }   /* The prefix continues after string. */
    if (*s != 0 && *p == 0) { return *s; }  /* All characters in `prefix` equal to `string`. Return first character following `eightbitPrefix`. */
    /* *p != 0 && *s != 0 */
    char diff = *s - *p;
    if (diff) { return 0; }
    s++, p++;
    goto again;
}

FOCAL
short
Utf8Followers(uint8_t leadOr8Bit)
{
    if (leadOr8Bit < 128) { return 0; }
    if (128 <= leadOr8Bit && leadOr8Bit < 192) return -1;
    if (248 <= leadOr8Bit) return -1;
    
#ifdef __mips__ /* clz $a0, $v0,   ⃨  possibly clo. */
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

Opt<__builtin_int_t>
CastᵗˣᵗToInt(
  CastToIntOpinion (^feeder)(unsigned short &digit)
)
{ __builtin_int_t val = 0; __block unsigned short zero_to_nine; int sgn = 1;
    while (1) {
       CastToIntOpinion opinion = feeder(zero_to_nine);
       switch (opinion) {
         case CastToIntOpinion::accept: val *= 10; val += sgn*zero_to_nine; break;
         case CastToIntOpinion::rejecting: continue;
         case CastToIntOpinion::negate: sgn *= -1; break;
         case CastToIntOpinion::commit: return Opt<__builtin_int_t>(val);
         case CastToIntOpinion::annul: return Opt<__builtin_int_t>::no();
        }
     }
}

__builtin_uint_t
Utf8BytesUntilNull(
  const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8,
  __builtin_int_t maxbytes
)
{  __builtin_int_t i = 0;
again:
    if (i >= maxbytes) { return maxbytes; }
    uint8_t * leadOr8Bit = (uint8_t *)utf8 + i;
    if (*leadOr8Bit == 0x0) { return i; }
    __builtin_int_t followers = Utf8Followers(*leadOr8Bit);
    i += followers + 1;
    goto again;
} /* Note that this function is not equivalent to `strlen`. */

__builtin_int_t
UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶𝘖𝘳𝖤𝖮𝖳(
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 nativeEndianUnicodesOrEOT,
  __builtin_int_t maxtetras𝘖𝘳₋𝟷
)
{  int i = 0;
again:
    if (*(nativeEndianUnicodesOrEOT + i) == END_OF_TRANSMISSION) { return i; }
    if (*(nativeEndianUnicodesOrEOT + i) == 0x0000) { return i; }
    i++; if (maxtetras𝘖𝘳₋𝟷 >= 0 && i >= maxtetras𝘖𝘳₋𝟷) { return maxtetras𝘖𝘳₋𝟷; }
    goto again;
} /* Formerly named `UnicodesUntilExplicit𝙴𝙾𝚃` when comparing against `END_OF_TRANSMISSION`. */

#pragma mark - ...and to set up an `Utf8Terminal` (from --<Utf8Terminal.cpp>) on macOS:

#include <stdio.h> /* For use `stdin`, `write` and `fgetc`/`fgetwc`. */

auto Putₒ = ^(uint8_t * utf8s, uint16_t bytes) {
#ifdef __x86_64__
  write(1, utf8s, bytes);
#elif defined __mips__
  for (int i=0; i < bytes; i++) putch(*(utf8s+i));
#endif
};

DISORDERABLE auto WaitTerminal = ^(int periods𝘖𝘳Zero, int 
  ᵗᵉⁿᵗʰseconds, void (^ping)(bool &stop), char32_t * uc) {
#ifdef __mips__
  return 0;
#elif defined __x86_64__
  *uc = (char32_t)fgetc(stdin); /* For a wider flavor: `fgetwc`. */
  return 0;
#endif
}; /* Locks until keypress. */

Utf8Terminal _myTerminal;

#pragma mark The 𝒊𝒏𝒏𝒆𝒓 Details:

structᵢ Outputstream { virtual int write(const uint8_t * utf8s, __builtin_int_t bytes) = 0; };

structᵢ Utf8Terminal::Internals { /* Requires duplex UART. */
    
    structᵢ output : public Outputstream {
        int write(const uint8_t * utf8s, __builtin_int_t bytes) {
            __builtin_int_t i;
            for (i = 0; i < bytes; i++) Putₒ((uint8_t *)(utf8s + i), 1);
            return 0;
        }
    };
    
    Internals() { }
    
    Utf8Terminal * outer;
    
    Utf8Terminal::Internals::output o;
    
};

#pragma mark Exposed Interface:

Utf8Terminal::Utf8Terminal()
  : impl_ { new Internals() }
{
    impl_->outer = this;
    scientificFormat = ^(double x, Utf8Terminal &stream) { };
}

Utf8Terminal::~Utf8Terminal() { }

Utf8Terminal::Inputctrl
Utf8Terminal::interaction(/* char32_t echo, */
  int periods𝘖𝘳Zero,
  int ᵗᵉⁿᵗʰseconds,
  void (^ping)(bool &stop), /* Consider adding a scheduler and use a timer in the function below. */
  void (^touchbase)(char32_t unicode, bool &stop)
) const
{  char32_t uc; bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 stop=false;
again:
    ping(stop); if (stop) return Terminated;
    int y = WaitTerminal(periods𝘖𝘳Zero, ᵗᵉⁿᵗʰseconds, ping, &uc); /* Timed out, captured a key press, error. */
    if (stop) return Terminated;
    switch (y) {
    case 0: touchbase(uc, stop); if (stop) return Terminated; /* Captured a key press. */
    case 1: return Timedout; /* Timed out */
    default: return Error; /* Error */
    }
    goto again;
}

int Utf8Terminal::write(const uint8_t * utf8s, __builtin_int_t bytes) const /* Note 
  that `interaction` requires tranquility sans `write` to avoid muxing 
  input and output. */
{ return impl_->o.write(utf8s, bytes); }

