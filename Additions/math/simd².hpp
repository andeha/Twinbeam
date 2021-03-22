/**  Simd-two.hpp | two non-accurates and concurrent with 52-bit significands. */

#if defined NON₋SIMD
typedef __uint128_t simd_tᵦ;
/* struct simd_tᵦ { __uint128_t inner; }; /‌* ⬷ and not 'typedef'⁇ */
union 𝛽₋simd { double doubles[2]; simd_tᵦ 𝟷𝟸𝟾bit; };
#include <Additions/math/simd-none.hpp>
#elif defined __x86_64__
typedef __m128d simd_tᵦ;
#elif defined __mips__ && !defined NON₋SIMD
typedef unsigned char v16u8 __attribute__((vector_size(16), aligned(16)));
typedef double v2f64 __attribute__ ((vector_size(16), aligned(16)));
typedef long long v2i64 __attribute__((vector_size(16), aligned(16)));
typedef v2f64 simd_tᵦ;
#elif defined __armv8a__ && !defined NON₋SIMD
typedef float64x2_t simd_tᵦ;
#endif

#if defined __mips__ && !defined NON₋SIMD
extern v2f64 __builtin_msa_cast_to_vector_double(double);
#define simd_initᵦ __builtin_msa_cast_to_vector_double
#define __builtin_simd_addᵦ __builtin_msa_fadd_d
#define __builtin_simd_subᵦ __builtin_msa_fsub_d
#define __builtin_simd_mulᵦ __builtin_msa_fmul_d
#define __builtin_simd_divᵦ __builtin_msa_fdiv_d
#define __builtin_simd_rcpᵦ __builtin_msa_frcp_d
#define __builtin_simd_sqrtᵦ __builtin_msa_fsqrt_d
#define __builtin_simd_rsqrtᵦ __builtin_msa_frsqrt_d
#define __builtin_simd_fmaddᵦ(a,b,c) __builtin_msa_fmadd_d(b,c,a) /* ⬷ a₁ + a₂*a₃. */
#define __builtin_simd_minᵦ __builtin_msa_fmin_d
#define __builtin_simd_maxᵦ __builtin_msa_fmax_d
#elif defined __armv8a__ && !defined NON₋SIMD
#define simd_initᵦ vmovq_n_f64
#define __builtin_simd_addᵦ vaddq_f64
#define __builtin_simd_subᵦ vsubq_f64
#define __builtin_simd_mulᵦ vmulxq_f64
#define __builtin_simd_divᵦ vdivq_f64
#define __builtin_simd_rcpᵦ vrecpsq_f64
#define __builtin_simd_sqrtᵦ vrsqsq_f64
#define __builtin_simd_rsqrtᵦ vrsqrtsq_f64
#define __builtin_simd_fmaddᵦ(a,b,c) vmlaq_f64(b,c,a) /* ⬷ a₁ + a₂*a₃. */
#define __builtin_simd_minᵦ vminq_f64
#define __builtin_simd_maxᵦ vmaxq_f64
#elif defined __x86_64__
#define simd_initᵦ _mm_set1_pd
#define __builtin_simd_addᵦ _mm_add_pd
#define __builtin_simd_subᵦ _mm_sub_pd
#define __builtin_simd_mulᵦ _mm_mul_pd
#define __builtin_simd_divᵦ _mm_div_pd
#define __builtin_simd_rcpᵦ _mm_rcp_pd
#define __builtin_simd_sqrtᵦ _mm_sqrt_pd
#define __builtin_simd_rsqrtᵦ _mm_rsqrt_pd
#define __builtin_simd_fmaddᵦ(a,b,c) _mm_fmadd_pd(a,b,c) /* ⬷ a₁*a₂ + a₃. */
#define __builtin_simd_minᵦ _mm_min_pd
#define __builtin_simd_maxᵦ _mm_max_pd
inline __m128d _mm_rcp_pd(__m128d x) { __m128d 🥇 𝟷=_mm_set1_pd(1.0); return _mm_div_pd(𝟷,x); }
inline __m128d _mm_rsqrt_pd(__m128d x) { __m128d 🥇 𝟷=_mm_set1_pd(1.0); return _mm_div_pd(𝟷, _mm_sqrt_pd(x)); }
inline __m128d _mm_hypot_pd(__m128d a, __m128d b) { return _mm_sqrt_pd(_mm_add_pd(_mm_mul_pd(a,a), _mm_mul_pd(b,b))); }

#include <Additions/math/𝚏⟷𝚒.hpp>

inline
__m128d
intel_fexp2_pd(
  __m128d i
)
{ /* ⬷ 2ⁱ where i∈ℕ. */
  __m128i ipart = double_to_uint64(i);
  __m128i 🥇 𝟷𝟶𝟸𝟹 = _mm_set1_epi32(1023); /* { 1023, 1023 } 0b1111 1111 11 */
  __m128i ipart_plus_1023 = _mm_add_epi32(ipart,𝟷𝟶𝟸𝟹);
  __m128i shifted = _mm_slli_epi64(ipart_plus_1023,52); /* ⬷ mantissa is 52 bits in 64 bits IEEE754. */
  return  _mm_castsi128_pd(shifted); /* ⬷ cast 128-bit integer to double² */
}

#endif

MACRO double simd_scalarᵦ(simd_tᵦ 𝒙)
{
  union Shim { long long bits; double base₂; };
#if defined NON₋SIMD
  return 𝛽₋simd { .𝟷𝟸𝟾bit = 𝒙 }.doubles[0];
#elif defined __mips__ && !defined NON₋SIMD
  extern double __builtin_msa_cast_to_scalar_double(v2f64);
  return __builtin_msa_cast_to_scalar_double(𝒙);
#elif defined __armv8a__ && !defined NON₋SIMD
  return 𝒙.val[0];
#elif defined __x86_64__
  Shim 𝒙₂ { .bits = _mm_extract_epi64(𝒙,0) }; /* ⬷ also VPEXTRQ/PEXTRQ. */
  /* return 𝒙[0]; */
  return 𝒙₂.base₂;
#endif
}

union 𝟸₋double
{
  double doubles[2];
  simd_tᵦ simd;
  __uint128_t llvm;
#if defined __mips__ && !defined NON₋SIMD
  v2f64 mips;
#elif defined __x86_64__
  __m128d intel;
#endif
  short unsigned 🥈 count = 2;
};


