//
//  Present.cpp
//  pdb
//

#include <Twinbeam.h>
#include <Additions.h>
#include "pdb.h"

extern void (^Putch)(char utf8);
const char *bright = "<ESC>[1m", *dim = "<ESC>[2m", *fgBlue = "<ESC>[34m", 
  *fgRed = "<ESC>[31m", *reset = "<ESC>[0m", *reverse  = "<ESC>[7m";
  
bool color = false;
    
INNER_FUNCTION
void 
Present(
    Utf8Terminal &term,
    const Bitfield& field,
    __builtin_uint_t value,
    __builtin_uint_t init
)
{    
    Termlog << field.ident << tab << "= " << (color ? fgBlue : "") << "0b"; 
    
    __block bool masking = false;
    Base((__builtin_uint_t)(field.mask), 2, 32, ^(char utf8) {
        
        if (utf8 == '1' && !masking) { masking = true; Termlog << (color ? reverse : ""); }
        
        if (masking && utf8 == '0') { masking = false; Termlog << (color ? reverse : ""); }
        
        if (masking) { if (value & field.mask) Putch('1'); else Putch('0'); } else { Putch('x'); }
        
    });
    
    Termlog << (color ? reset : "") << (color ? dim : "") << " " << field.text << (color ? reset : "") << eol;
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
    r.forall(^(SemanticPointer<Bitfield *> field, bool first, bool last,
      __builtin_int_t idx, bool& stop) { Present(term, *(field.pointer),
      value, init); });
}

FOCAL
void
Present(
    Utf8Terminal &term,
    const AnnotatedRegister& r,
    __builtin_uint_t value
)
{
    Termlog << r.header << eol;
    Present(term, r.r, value, r.init);
    Termlog << r.footer << sep;
}
