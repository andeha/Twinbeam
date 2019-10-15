/*  Presentᵃᵘˣ.cpp | Printing an assorted selection of types. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

const char *bright="\x1B[1m", *dim="\x1B[2m", *fgBlue="\x1B[34m", 
  *fgRed="\x1B[31m", *reset="\x1B[0m", *reverse="\x1B[7m";

DISORDERABLE extern void (^Putₒ)(uint8_t * utf8s, uint16_t bytes);
#ifdef __x86_64__
extern "C" ssize_t write(int fd, const void *s, size_t b);
#endif
extern int print﹟(void (^out)(uint8_t * utf8s, short unsigned bytes), const 
  char * utf8format, __builtin_va_list arg);

int
mfprint(
  const char *utf8format,
  ...
)
{  int y = 0;
    va_prologue(utf8format)
#ifdef __x86_64__
    bool original = false;
    /* FILE 🥇 * restrict stream = original ? stderr : stdout;
      y = vfprintf(stream, utf8format, __arg); */
    int 🥇 descript = original ? 1 /* stdout */ : 2 /* stderr */;
    auto Putₒ₂ = ^(uint8_t * utf8s, uint16_t bytes) { write(descript, (const void *)utf8s, bytes); };
    auto out = ^(uint8_t * utf8s, uint16_t bytes) { Putₒ₂(utf8s, bytes); };
 #elif defined __mips__
    auto out = ^(uint8_t * utf8s, uint16_t bytes) { Putₒ(utf8s, bytes); };
#endif
    y = print﹟(out, utf8format, __arg);
    va_epilogue
    return y;
}

auto emitUnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶 = ^(const char32_t * unicodes) {
  int i=0;
again:
    char32_t uc = *(unicodes + i);
    if (uc == 0x0000) { return; }
    if (UnicodeToUtf8(uc, ^(const uint8_t *p, int bytes) {
      if (bytes >= 1) mfprint("⬚", ﹟c((char)*(p + 0)));
      if (bytes >= 2) mfprint("⬚", ﹟c((char)*(p + 1)));
      if (bytes >= 3) mfprint("⬚", ﹟c((char)*(p + 2)));
      if (bytes >= 4) mfprint("⬚", ﹟c((char)*(p + 3)));
   } )) { /* Empty */ }
   i++; goto again;
};

#pragma mark - ...and the platform independent part

inexorable
void
Present(
  Utf8Terminal &term,
  const Bitfield& field,
  uint32_t value,
  uint32_t init,
  bool 𝟷𝟼bits,
  int maxwidth
)
{
    unsigned spaces = maxwidth - UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(field.ident, BUILTIN_INT_MAX);
    while (spaces--) { mfprint(" "); }
    
    emitUnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(field.ident);
    mfprint(" ");
    
    __block bool masking = false; __block unsigned pos = 31;
    Base𝕟((__builtin_uint_t)(field.mask), 2, 32, ^(char 𝟶to𝟿) {
        
        if (𝟷𝟼bits && pos > 15) { mfprint("⌗"); }
        
        if (!𝟷𝟼bits && 𝟶to𝟿 == '1' && !masking) { masking = true; }
        
        if (!𝟷𝟼bits && masking && 𝟶to𝟿 == '0') { masking = false; }
        
        if (!𝟷𝟼bits && masking) { mfprint(value & (0b1<<pos) ? "1" : "0"); }
        
        if (!𝟷𝟼bits && !masking) { mfprint("␣"); }
        
        if (pos % 4 == 0) mfprint("|"); pos--;
        
    });
    
    emitUnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(field.text);
    mfprint("\n");
}

FOCAL
void
Present(
  Utf8Terminal &term,
  const AnnotatedRegister& ar,
  uint32_t value,
  bool 𝟷𝟼bits
)
{
    auto present = ^(int count, const Bitfield * regs, uint32_t val, 
         uint32_t init) { int maxwidth=0;
       for (int i = 0; i < count; i++) {
          const Bitfield * reg = regs + i; maxwidth = max(maxwidth, 
           (int)UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(reg->ident, BUILTIN_INT_MAX));
       }
       for (int i = 0; i < count; i++) {
          Present(term, *(regs + i), val, init, 𝟷𝟼bits, maxwidth);
       }
    };
    mfprint("⬚\n", ﹟s(bright));
    emitUnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(ar.header);
    mfprint("⬚ = ⬚ 0x", ﹟s(reset), ﹟s(reverse));
    Base𝕟(value, 16, 8, ^(char 𝟶to𝟿) { mfprint("⬚", ﹟c(𝟶to𝟿)); });
    mfprint("⬚\n\n", ﹟s(reset));
    present(ar.regcnt, ar.regs, value, ar.init);
    emitUnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(ar.footnote);
    mfprint("\n\n");
}

#pragma mark - Visualizing `float` and `double's

BITMASK (uint32_t) { /* The `float`. */
  Binary32_SGN = 0x80000000, /* Sign bit */
  Binary32_EXP = 0b11111111<<23, /* Signed exponent -126 to 127. */
  Binary32_MAN = 0x7fffff, /* Fraction/mantissa/significand */
};

Register Binary32 = {
  { U"Binary32_SGN", Binary32_SGN, U"Sign bit" },
  { U"Binary32_EXP", Binary32_EXP, U"Signed exponent -126 to 127" },
  { U"Binary32_MAN", Binary32_MAN, U"Fraction/mantissa/significand" }
};

AnnotatedRegister AR_Binary32 = {
  U"Binary32: The IEEE 754 single precision type",
  3, Binary32, 0x00000000,
  U""
};

#pragma mark ...and the 64-bit double type:

BITMASK (uint32_t) { /* IEEE754 hi-`double`. */
  Binary64_SGN = 0x80000000, /* Sign bit */
  Binary64_EXP = 0b11111111111<<20, /* Signed exponent -1024 to 1023. */
  Binary64_MANʰⁱ = 0xFffff, /* MSB's fraction/mantissa/significand */
};

BITMASK (uint32_t) { /* IEEE754 lo-`double`. */
  Binary64_MANˡᵒ = 0xFFFFffff, /* LSB's fraction/mantissa/significand */
};

Register Binary64ʰⁱ = {
  { U"Binary64_SGN", Binary64_SGN, U"Sign bit" },
  { U"Binary64_EXP", Binary64_EXP, U"Signed exponent -1024 to 1023" },
  { U"Binary64_MANʰⁱ", Binary64_MANʰⁱ, U"MSB's fract/mantissa/significand" }
};

Register Binary64ˡᵒ = {
  { U"Binary64_MANˡᵒ", Binary64_MANˡᵒ, U"LSB's fract/mantissa/significand" }
};

AnnotatedRegister AR_Binary64ʰⁱ = {
  U"Binary64ʰⁱ: The IEEE 754 double precision type",
  3, Binary64ʰⁱ, 0x00000000,
  U""
};

AnnotatedRegister AR_Binary64ˡᵒ = {
  U"Binary64ˡᵒ: The IEEE 754 double precision type",
  1, Binary64ˡᵒ, 0x00000000,
  U""
};

void 
Presentᵧ(
  Utf8Terminal &term,
  double val
)
{  octa o = octa { .base₂=val };
    Present(term, AR_Binary64ʰⁱ, o.unsigned_little_endian.mst);
    Present(term, AR_Binary64ˡᵒ, o.unsigned_little_endian.lst);
}

void
Presentᵧ(
  Utf8Terminal &term,
  float val
)
{  uint32_t bits = tetra { .base₂=val }.bits;
    Present(term, AR_Binary32, bits);
}

#pragma mark - Introspection

DISORDERABLE extern void reᵍsPrint(__builtin_uint_t mask)
{
#ifdef __x86_64__
#elif defined __mips__
#endif
} /* Print at least 0 to 31 non high-volatile registers. */

