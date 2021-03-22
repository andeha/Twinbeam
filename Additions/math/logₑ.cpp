/*  logₑ.cpp | Napiers logarithm. */

#include <Twinbeam.h>
#include <Additions/math/simd².hpp>

extern leaf₋function simd_tᵦ tanh⁻¹(simd_tᵦ ℝ);
extern intrinsic₋leaf double log₂ᵥ1(double ℝ);

simd_tᵦ logₑ(simd_tᵦ x) { /* logₑ(x) = log₂(x)/log₂(e) = log₂(x)*logₑ(2) */
#if defined NON₋SIMD
    double 🥈ᵢ ln2 = 0.69314718055994530941;
    simd_tᵦ c = simd_initᵦ(ln2);
    auto unbuiltin_flog2_d = ^(simd_tᵦ x) {
     𝛽₋simd ℕ { .𝟷𝟸𝟾bit=x };
     double x₁=log₂ᵥ1(ℕ.doubles[0]), x₂=log₂ᵥ1(ℕ.doubles[1]);
     return 𝛽₋simd { .doubles = { x₁, x₂ } }.𝟷𝟸𝟾bit; }; /* <- 'simd_tᵦ'. */
    simd_tᵦ y = unbuiltin_flog2_d(x);
    y = __builtin_simd_mulᵦ(c,y);
    return y;
#elif defined __mips__ && !defined NON₋SIMD
    double 🥈ᵢ ln2 = 0.69314718055994530941;
    simd_tᵦ c = simd_initᵦ(ln2);
    simd_tᵦ y = __builtin_msa_flog2_d(x); /* d = log₂(s) */
    y = __builtin_simd_mulᵦ(c,y);
    return y;
#elif defined __x86_64__ /* ln(x)=2*tanh⁻¹((x-1)/(x+1)) */
    simd_tᵦ 🥇 𝟷=simd_initᵦ(1.0), 𝟸=simd_initᵦ(2.0);
    simd_tᵦ n = __builtin_simd_subᵦ(x,𝟷);
    simd_tᵦ d = __builtin_simd_addᵦ(x,𝟷);
    return __builtin_simd_mulᵦ(𝟸, tanh⁻¹(__builtin_simd_divᵦ(n,d)));
#endif
}


