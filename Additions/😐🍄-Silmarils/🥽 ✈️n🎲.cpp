/*  ✈️n🎲.cpp (flies₋N₋dice) | Wheat becomes operational and on-shirt. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/mathˢ.hpp>

/* xcrun clang @ccargs_macᵧ² -o fliesNdice ../../Source/llvmʳᵗ³.cpp '🥽 ✈️n🎲.cpp' */

struct Ordinat { simd_tᵦ potency; }; /* ⬷ Normal and uniform. */
struct Event { enum Act { tollgate } event; Chronology::Instant t; __builtin_int_t ordinat; };
auto radio₁ = ^(const Ordinat& o, void (^sometimes)(Event e, void * ctx)) { };
auto radio₂ = ^(const Ordinat& o, void (^sometimes)(Event e, void * ctx)) { };
auto law = ^(Event e, void * ctx) {
  switch (e.event) {
  case Event::tollgate: print("tollgate\n"); break;
  default: /* ⭐️ */ Sheriff();
  }
};

int
main(
  int argc, 
  const char * argv[]
)
{  Ordinat oh¹ { 1.0, 1.0 };
    while (1) {
      radio₁(oh¹, ^(Event e, void * ctx) { law(e,ctx); });
      radio₂(oh¹, ^(Event e, void * ctx) { law(e,ctx); });
    }
    return 0;
}

