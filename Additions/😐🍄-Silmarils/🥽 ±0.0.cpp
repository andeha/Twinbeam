/*  ±0.0.cpp - More fun to compute. */

#include <Twinbeam.h>

/* xcrun clang @ccargs_macᵧ² -o ±0.0 ../../Source/llvmʳᵗ³.cpp '🥽 ±0.0.cpp' */

int
main(
  int argc,
  const char * argv[]
)
{
    octa y₁ { .binary64 = {0,0,0,1} }, y₂ { .base₂ = -0.0 }, y₃ { .base₂ = 0.0 };
    if (y₁.base₂ == y₂.base₂) { print("equal\n"); } else { print("not equal\n"); }
    if (y₁.base₂ == y₃.base₂) { print("equal\n"); } else { print("not equal\n"); }
    return 0;
}

