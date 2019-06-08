/*  Adder.cpp | ₊⁺✚ - Full adder in orthography. */

#include <Twinbeam.h>

/* Compile with xcrun clang @ccargs_macos -o Adder '🥽 Adder.cpp' */

inexorable auto uplus₈ = ^(
  uint8_t cᵢ, uint8_t x₁, uint8_t x₂, uint8_t &y, uint8_t &cₒ
) {
   cₒ = (x₁ & x₂) | (cᵢ & (x₁ ^ x₂)); y = x₁ ^ x₂ ^ (cᵢ | (cₒ<<1));
};

union ¹⁶Wires { uint16_t x; struct { unsigned x₁₅, x₁₄, x₁₃, x₁₂, x₁₁, 
  x₁₀, x₉, x₈, x₇, x₆, x₅, x₄, x₃, x₂, x₁, x₀ : 1; } w; };
union ⁴Wires { short unsigned x; struct { unsigned x₄,x₃,x₂,x₁ : 1; } w; };

auto fulladder₄ = ^(⁴Wires& /* a … cᵢ */ in, ⁴Wires /* y cₒ */ &out) {
  unsigned x = in.w.x₁ ^ in.w.x₂;
  out.w.x₁ = x ^ in.w.x₃;
  out.w.x₂ = (in.w.x₁ & in.w.x₂) | (x & in.w.x₃);
};

#pragma mark - …and the entry point:                                       

int
main(
  int argc,
  const char * argv[]
)
{
    return 0;
}

