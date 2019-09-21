/*  Chebyshev.cpp | 🎢 - Rapid convergence. */

#include <Twinbeam.h>

/* Compile with xcrun clang @ccargs_macᵧ² -o Chebyshev '🥽 Chebyshev.cpp'
   ... and NOT xcrun clang @ccargs_macosᵧ -o Chebyshev '🥽 Chebyshev.cpp' */

typedef double (^Computational)(double x);

MACRO Computational Chebyshevᵀ(int n) { switch (n) {
  case 0: return ^(double x) { return 1.0; };
  case 1: return ^(double x) { return x; };
  default: return Block_copy(^(double x) { return 2*x*Chebyshevᵀ(n-1)(x) -
    Chebyshevᵀ(n-2)(x); });
} }

MACRO Computational Chebyshevᵁ(int n) { switch (n) {
  case 0: return ^(double x) { return 1.0; };
  case 1: return ^(double x) { return 2*x; };
  default: return Block_copy(^(double x) { return 2*x*Chebyshevᵁ(n-1)(x) -
    Chebyshevᵁ(n-2)(x); });
} }

auto Alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };
auto Fallow = ^(void * p) { free(p); };
void * __gxx_personality_v0;

#include <stdio.h>

int
main(
  int argc,
  const char * argv[]
)
{
    Computational expr₁ = Chebyshevᵀ(5); /* 16x⁵ - 20x³ + 5x */
    Computational expr₂ = Chebyshevᵀ(3); /* 4x³ - 3x */
    printf("T₅(3) = %f\n", expr₁(3.0)); /* =3363.0 */
    printf("T₃(5) = %f\n", expr₂(5.0)); /* =485.0 */
    Computational expr₃ = Chebyshevᵁ(5); /* 32x⁵ - 32x³ + 6x */
    Computational expr₄ = Chebyshevᵁ(3); /* 8x³ - 4x */
    printf("U₅(3) = %f\n", expr₃(3.0)); /* =6930.0 */
    printf("U₃(5) = %f\n", expr₄(5.0)); /* =980.0 */
    return 0;
}