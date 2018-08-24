//
//  Present2.cpp
//  pdb
//

#include <Twinbeam.h>
#include <Additions.h>
#include <Formatting.hpp>
#include "pdb.h"

const char *bright = "\x1B[1m", *dim = "\x1B[2m", *fgBlue = "\x1B[34m",
  *fgRed = "\x1B[31m", *reset = "\x1B[0m", *reverse  = "\x1B[7m";

INNER_FUNCTION
void
Present(
  Utf8Terminal &term,
  const Bitfield& field,
  __builtin_uint_t value,
  __builtin_uint_t init,
  __builtin_int_t maxWidth
)
{
    unsigned spaces = maxWidth - UnicodesUntilNull(field.ident, BUILTIN_INT_MAX);
    while (spaces--) { Putch(' '); }
    Termlog << field.ident << " ";
    
    __block bool masking = false;
    Base((__builtin_uint_t)(field.mask), 2, 32, ^(char utf8) {
        
        if (utf8 == '1' && !masking) { masking = true; }
        
        if (masking && utf8 == '0') { masking = false; }
        
        if (masking) { if (value & field.mask) Putch('1'); else Putch('0'); } else { Put(U'␣'); }
        
    });
    
    Termlog <<  " " << field.text << eol;
}

INNER_FUNCTION
void
Present(
  Utf8Terminal &term,
  const Register& r,
  __builtin_uint_t value,
  __builtin_uint_t init
)
{
    PresentTable(Termlog, r,
      ^(Utf8Terminal &os) { /* header */ },
      ^(const Bitfield& bf1, const Bitfield& bf2) { return UnicodesUntilNull(bf1.ident, BUILTIN_INT_MAX) < UnicodesUntilNull(bf2.ident, BUILTIN_INT_MAX); },
      ^(const Bitfield& bf) { return UnicodesUntilNull(bf.ident, BUILTIN_INT_MAX); },
      ^(Utf8Terminal &os, const Bitfield& bf, __builtin_int_t maxwidth) { Present(os, bf, value, init, maxwidth); },
      ^(Utf8Terminal &os) { /* footer */ }
    );
}

FOCAL
void
Present(
  Utf8Terminal &term,
  const AnnotatedRegister& r,
  __builtin_uint_t value
)
{
    Termlog << bright << r.header << reset << " = " << reverse << "0x";
    Base(value, 16, 8, ^(char c) { Putch(c); }); // Termlog << (__builtin_uint_t)value;
    Termlog << reset << eol;
    Present(term, r.r, value, r.init);
    Termlog << r.footer << sep;
}
