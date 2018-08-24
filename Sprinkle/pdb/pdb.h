//
//  pdb.h
//  pdb
//

struct Bitfield { const char32_t * ident; __builtin_uint_t mask; const char32_t
  * text; }; typedef Vector<Bitfield> Register; struct AnnotatedRegister {
  const char32_t * header; const Register& r; __builtin_uint_t init; const
  char32_t * footer; };

extern void (^Putch)(char utf8);
extern void (^Put)(char32_t unicode);

inline bool EightBitIsPrefixOrEqual(const char *eightbitString, const char * eightbitPrefix)
{ if (!*eightbitString) { return false; } while (*eightbitString && *eightbitPrefix) {
  if(*eightbitString++ != *eightbitPrefix++) return false; } return true; }

