//
//  Present2.cpp
//  pdb
//

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <stdio.h>

const char *bright = "\x1B[1m", *dim = "\x1B[2m", *fgBlue = "\x1B[34m",
  *fgRed = "\x1B[31m", *reset = "\x1B[0m", *reverse = "\x1B[7m";

auto outᵘcUntil𝟶𝚡𝟶𝟶𝟶𝟶 = ^(const char32_t * unicodes) {
    int i=0;
again:
    char32_t uc = *(unicodes + i);
    if (UnicodeToUtf8(uc, ^(const uint8_t *p, int bytes) {
      if (bytes >= 1) fprintf(stderr, "%c", (char)*(p + 0));
      if (bytes >= 2) fprintf(stderr, "%c", (char)*(p + 1));
      if (bytes >= 3) fprintf(stderr, "%c", (char)*(p + 2));
      if (bytes >= 4) fprintf(stderr, "%c", (char)*(p + 3));
   } )) { /* Empty */ }
   i++; goto again;
};

inexorable
void
Present(
  Utf8Terminal &term,
  const Bitfield& field,
  __builtin_uint_t value,
  __builtin_uint_t init,
  __builtin_int_t maxwidth
)
{
    unsigned spaces = maxwidth - UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(field.ident, BUILTIN_INT_MAX);
    while (spaces--) { fprintf(stderr, " "); }
    
    outᵘcUntil𝟶𝚡𝟶𝟶𝟶𝟶(field.ident);
    fprintf(stderr, " ");
    
    __block bool masking = false; __block unsigned pos = 31;
    Base𝕟((__builtin_uint_t)(field.mask), 2, 32, ^(char 𝟶to𝟿) {
        
        if (𝟶to𝟿 == '1' && !masking) { masking = true; }
        
        if (masking && 𝟶to𝟿 == '0') { masking = false; }
        
        if (masking) { fprintf(stderr, value & field.mask ? "1" : "0"); }
        else { fprintf(stderr, "␣"); }
        
        if (pos % 4 == 0) fprintf(stderr, "|"); pos--;
        
    });
    
    outᵘcUntil𝟶𝚡𝟶𝟶𝟶𝟶(field.text);
    fprintf(stderr, "\n");
}

FOCAL
void
Present(
  Utf8Terminal &term,
  const AnnotatedRegister& ar,
  __builtin_uint_t value
)
{
    auto present = ^(int count, const Bitfield * regs, __builtin_uint_t value, 
         __builtin_uint_t init) { int maxwidth=0;
       for (int i = 0; i < count; i++) {
          const Bitfield * reg = regs + i; maxwidth = max(maxwidth, 
           (int)UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(reg->ident, BUILTIN_INT_MAX));
       }
       for (int i = 0; i < count; i++) {
          Present(term, *(regs + i), value, init, maxwidth);
       }
    };
    fprintf(stderr, "%s\n", bright);
    outᵘcUntil𝟶𝚡𝟶𝟶𝟶𝟶(ar.header);
    fprintf(stderr, "%s\n = %s\n0x", reset, reverse);
    Base𝕟(value, 16, 8, ^(char 𝟶to𝟿) { fprintf(stderr, "%c", 𝟶to𝟿); });
    fprintf(stderr, "%s\n", reset);
    present(ar.regcnt, ar.regs, value, ar.init);
    outᵘcUntil𝟶𝚡𝟶𝟶𝟶𝟶(ar.footnote);
    fprintf(stderr, "\n\n");
}


