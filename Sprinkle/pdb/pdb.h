//
//  pdb.h
//  pdb
//

struct Bitfield { const char32_t * ident; __builtin_uint_t mask; 
  const char32_t * text; };

typedef Bitfield Register[];

struct AnnotatedRegister { const char32_t * header; int regcnt;
  const Bitfield * regs; __builtin_uint_t init; const char32_t * footnote; };


