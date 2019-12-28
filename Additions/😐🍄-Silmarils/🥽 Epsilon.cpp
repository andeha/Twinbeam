/*  Epsilon.cpp | Magnetic on/to 'err'. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/* To compile: xcrun clang @ccargs_macᵧ² -o Epsilon ../../Source/llvmʳᵗ³.cpp \
   ../Ieee754₆₄bits.cpp ../Automata.cpp '🥽 Epsilon.cpp' */

int
main(
  int argc, 
  const char * argv[]
)
{ 
    Unicodes text = ᵊ(U"2012-01-24 12:00:00.125");
    Memoryregion region { (void *)text.unicodes, text.tetras<<2 };
    Memoryview datetime { &region, 0, region.bytes() };
    Chronology chronology = SystemCalendricChronology();
    Opt<Chronology::Instant> t = TS(Encoding::unicode, chronology, datetime);
    if (t) { print("⬚\n", ﹟x(__builtin_uint_t((*t).bits))); }
    return 0;
}

