/**  simd².hpp - Two accurate 52-bit significands concurrently. */

#ifdef __x86_64__
typedef __m128d simd_tᵦ;
#elif defined __mips__
typedef unsigned char v16u8 __attribute__((vector_size(16), aligned(16)));
typedef double v2f64 __attribute__ ((vector_size(16), aligned(16)));
typedef long long v2i64 __attribute__((vector_size(16), aligned(16)));
typedef v2f64 simd_tᵦ;
#endif

#ifdef __mips__
extern v2f64 __builtin_msa_cast_to_vector_double(double);
/* … */
#elif defined __x86_64__
/* … */
#include <Additions/math/𝚏⟷𝚒.hpp>

inline
__m128d
intel_fexp2_pd(
  __m128d i
)
{ /* 2ⁱ where i∈ℕ */
  __m128i ipart = double_to_uint64(i);
  __m128i 🥇 𝟷𝟶𝟸𝟹 = _mm_set1_epi32(1023); /* { 1023, 1023 } 0b1111 1111 11 */
  __m128i ipart_plus_1023 = _mm_add_epi32(ipart, 𝟷𝟶𝟸𝟹);
  __m128i shifted = _mm_slli_epi64(ipart_plus_1023, 52); /* Mantissa is 52 bits on IEEE754, 64 bits. */
  return  _mm_castsi128_pd(shifted); /* Cast 128-bit integer to double² */
}

#endif

MACRO double simd_scalarᵦ(simd_tᵦ 𝒙) {
   union Shim { long long bits; double base₂; };
#ifdef __mips__
   extern double __builtin_msa_cast_to_scalar_double(v2f64);
   return __builtin_msa_cast_to_scalar_double(𝒙);
#elif defined __x86_64__
   Shim 𝒙₂ { .bits = _mm_extract_epi64(𝒙, 0) }; /* VPEXTRQ / PEXTRQ */
   /* return 𝒙[0]; */
   return 𝒙₂.base₂;
#endif
}

union double² {
  double doubles[2];
  simd_tᵦ simd;
  __uint128_t llvm;
#ifdef __mips__
  v2f64 mips;
#elif defined __x86_64__
  __m128d intel;
#endif
  short unsigned 🥈 count = 2;
};

union double⁴ {
  double doubles[4];
  struct { double² left; double² right; } two;
#ifdef __x86_64__
  __m256d intel;
#endif
  short unsigned 🥈 count = 4;
}; /* See also --<Additions>--<Esoterics.h>{`Q31ToFloat`}. */


