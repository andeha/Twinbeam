/*  IEEE₁₂₈ | The Ieee754²⁰⁰⁸ high-precision type. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/*
  
  Compile with './artᵐⁱᵖˢ.ksh IEEE₁₂₈' or to run on host:
  
  xcrun clang @ccargs_macᵧ² -o IEEE₁₂₈ '🥽 IEEE₁₂₈.cpp' ../../Source/llvmʳᵗ³.cpp
  
 */

typedef union {
  struct { octa lso; octa mso; } little_endian;
  struct { octa mso; octa lso; } big_endian;
  struct {
     unsigned mantissa₀₋₃₁   : 32;
     unsigned mantissa₃₂₋₆₃  : 32;
     unsigned mantissa₆₄₋₉₄  : 32;
     unsigned mantissa₉₅₋₁₁₂ : 16;
     unsigned exponent       : 15;
     unsigned sign           :  1;
  } binary128; /* A․𝘬․a `ieee754_2008₂`. */
  /* struct { … } decimal128; */
  __uint128_t bits;
} sexdeca₂;

int
main(
  int argc,
  const char * argv[]
)
{
    maxprec x₁ = 101.0; double x₂ = 201.0;
    print("sizeof x₁ is ⬚\n", ﹟d(sizeof(x₁)));
    sexdeca₂ x₃ { .binary128 = { 0x1, 0x2, 0x3, 0x4, 0x5, 0b1 } };
    print("sizeof x₃ is ⬚ value is ⬚\n", ﹟d(sizeof(x₃)), ﹟U(x₃.bits));
    print("sizeof x₂ is ⬚ value is ⬚\n", ﹟d(sizeof(x₂)), ﹟F(x₂));
    
    /* long long double x₄ = 101.0; and not `long double` is invalid
    print("sizeof x₄ is ⬚ value is ⬚\n", sizeof(x₄), ﹟F(x₄)); */
    
    /*
      
      Attempt 1: Illustrate cancellation with 𝘦․𝘨 `1 - sin(x)/x` in `maxprec` 
        and `float`.
      Attempt 2: Subtract two 'almost equal' values. Note its inexactness 
        despite the size of the floating point.
      
     */
     
    return 0;
}

