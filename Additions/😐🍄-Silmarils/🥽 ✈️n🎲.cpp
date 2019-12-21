/*  ✈️n🎲.cpp (flies₋N₋dice) | Wheat becomes operational and on-shirt. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/* xcrun clang @ccargs_macᵧ² -o fliesNdice ../../Source/llvmʳᵗ³.cpp '🥽 ✈️n🎲.cpp' */

struct Event { enum Act { tollgate } event; Chronology::Instant ts; };
auto radio₁ = ^(void (^sometimes)(Event e, void * ctx)) { };
auto radio₂ = ^(void (^sometimes)(Event e, void * ctx)) { };
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
{
    while (1) {
      radio₁(^(Event e, void * ctx) { law(e,ctx); });
      radio₂(^(Event e, void * ctx) { law(e,ctx); });
    }
    return 0;
}

