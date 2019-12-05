/*  Markovᵢᵢ.cpp | Interpreting double-fixative statics. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/mathˢ.hpp>

/* Compile with xcrun clang @ccargs_macᵧ² -o Markov₂ '🥽 Markovᵢᵢ.cpp' */

typedef struct { Tuple<simd_tᵦ, simd_tᵦ> 𝟷𝘈𝘯𝘥Not𝟷; } Edge;
typedef struct { char32_t * ident; Knot¹ᵈ<Edge> ctx; } Vertex;
typedef template <typename T> Knot¹ᵈ<T> Stack<T>;

namespace Samples { enum { 𝟶𝟶,𝟶𝟷,𝟷𝟶,𝟷𝟷 }; }

#define 🎲(sides) ({ uint64_t value; SlowRandom rnd(&value, SlowRandom::Solution::RAND); rnd.update(); (value % sides) + 1; });

Knot¹ᵈ<Vertex> machine = {
  { U"idle", { { }, { } } },
  { U"fwd",  {   { } } },          /* 𝟶,cw,ccw,𝟄 */
  { U"bwd",  {   { } } },
  { U"err",  { {},{},{} } }
};

int
Interpret(
  void (^head)(int symbol, bool& stop),
  void (^cone)(void (^𝐶𝑂𝑀𝑃𝑈𝑇𝐴𝑇𝐼𝑈𝑀)())
)
{  double turtle;
    Stack<int> memory; /* ⬷ Recollection ∧ Mealy/Moore. */
    while (1) {
      if (memory.empty()) { return -1; }
      int op = memory.pop();
      if (Uniform(&turtle)) { return -2; }
      switch (op) {
      case 
      }
    }
    return 0;
}

#pragma mark - Main entry point

int
main(
  int argc,
  const char * argv[]
)
{
    auto head = ^(int symbol, bool& stop) { };
    auto cone = ^() { };
    if (Interpret(head,cone)) { return 1; }
    return 0;
}


