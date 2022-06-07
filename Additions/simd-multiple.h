/*  simd-multiple.h | single instruction in several renditions. */

#if defined Ieee754₋ARITHMETICS₋KEY
#if defined NON₋SIMD && !defined __MM__
inline simd_tᵦ simd_initᵦ(double x) { union β₋simd y = { .dbls={x,x} }; return y; }
inline simd_tᵦ __builtin_simd_addᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) { union β₋simd z = 
 { .dbls={ 𝒙.dbls[0]+𝒚.dbls[0], 𝒙.dbls[1]+𝒚.dbls[1] } }; return z; }
inline simd_tᵦ __builtin_simd_subᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) { union β₋simd z = 
 { .dbls={ 𝒙.dbls[0]-𝒚.dbls[0], 𝒙.dbls[1]-𝒚.dbls[1] } }; return z; }
inline simd_tᵦ __builtin_simd_mulᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) { union β₋simd z = 
 { .dbls={ 𝒙.dbls[0]*𝒚.dbls[0], 𝒙.dbls[1]*𝒚.dbls[1] } }; return z; }
inline simd_tᵦ __builtin_simd_divᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) { union β₋simd z = 
 { .dbls={ 𝒙.dbls[0]/𝒚.dbls[0], 𝒙.dbls[1]/𝒚.dbls[1] } }; return z; }
inline simd_tᵦ __builtin_simd_minᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) { union β₋simd z = 
 { .dbls={ min(𝒙.dbls[0],𝒚.dbls[0]), min(𝒙.dbls[1],𝒚.dbls[1]) } }; return z; }
inline simd_tᵦ __builtin_simd_maxᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) { union β₋simd z = 
 { .dbls={ max(𝒙.dbls[0],𝒚.dbls[0]), max(𝒙.dbls[1],𝒚.dbls[1]) } }; return z; }
extern double sqrt(double) ⓣ;
inline simd_tᵦ __builtin_simd_rsqrtᵦ(simd_tᵦ 𝒙) { union β₋simd z = 
 { .dbls={1/sqrt(𝒙.dbls[0]),1/sqrt(𝒙.dbls[0])} }; return z; }
inline simd_tᵦ __builtin_simd_sqrtᵦ(simd_tᵦ 𝒙) { union β₋simd z = 
 { .dbls={sqrt(𝒙.dbls[0]),sqrt(𝒙.dbls[1])} }; return z; }
inline simd_tᵦ __builtin_simd_rcpᵦ(simd_tᵦ 𝒙) { union β₋simd z = 
 { .dbls={1/𝒙.dbls[0],1/𝒙.dbls[1]} }; return z; }
#elif defined __armv8a__
#define simd_initᵦ vmovq_n_f64
#define __builtin_simd_addᵦ vaddq_f64
#define __builtin_simd_subᵦ vsubq_f64
#define __builtin_simd_mulᵦ vmulq_f64
#define __builtin_simd_divᵦ vdivq_f64
#define __builtin_simd_minᵦ vminq_f64
#define __builtin_simd_maxᵦ vmaxq_f64
#define __builtin_simd_rsqrtᵦ vrsqrteq_f64
#define __builtin_simd_sqrtᵦ vsqrtq_f64
#define __builtin_simd_rcpᵦ vrecpeq_f64
#elif defined __x86_64__
__m128d _mm_rcp_pd(__m128d);
__m128d _mm_rsqrt_pd(__m128d);
#define simd_initᵦ _mm_set1_pd
#define __builtin_simd_addᵦ _mm_add_pd
#define __builtin_simd_subᵦ _mm_sub_pd
#define __builtin_simd_mulᵦ _mm_mul_pd
#define __builtin_simd_divᵦ _mm_div_pd
#define __builtin_simd_minᵦ _mm_min_pd
#define __builtin_simd_maxᵦ _mm_max_pd
#define __builtin_simd_rsqrtᵦ _mm_rsqrt_pd
#define __builtin_simd_sqrtᵦ _mm_sqrt_pd
#define __builtin_simd_rcpᵦ _mm_rcp_pd
/* inline__m128d _mm_rcp_pd(__m128d) { __m128d one=simd_initᵦ(1.0); return _mm_div_pd(one,x); } */
/* inline __m128d _mm_rsqrt_pd(__m128d x) { __m128d one=simd_initᵦ(1.0); return _mm_div_pd(one,_mm_sqrt_pd(x)); } */
#elif defined __mips__ && !defined NON₋SIMD
extern v2f64 __builtin_msa_cast_to_vector_double(double);
#define simd_initᵦ __builtin_msa_cast_to_vector_double
#define __builtin_simd_addᵦ __builtin_msa_fadd_d
#define __builtin_simd_subᵦ __builtin_msa_fsub_d
#define __builtin_simd_mulᵦ __builtin_msa_fmul_d
#define __builtin_simd_divᵦ __builtin_msa_fdiv_d
#define __builtin_simd_minᵦ __builtin_msa_fmin_d
#define __builtin_simd_maxᵦ __builtin_msa_fmax_d
#define __builtin_simd_rsqrtᵦ __builtin_msa_frsqrt_d
#define __builtin_simd_sqrtᵦ __builtin_msa_fsqrt_d
#define __builtin_simd_rcpᵦ __builtin_msa_frcp_d
#endif

inline double simd_scalarᵦ(simd_tᵦ 𝒙)
{
#if defined NON₋SIMD
  return 𝒙.doubles[0];
#elif defined __x86_64__ || defined __armv8a__
  return 𝒙[0];
#elif defined __mips__ && defined __mips_msa
  extern double __builtin_msa_cast_to_scalar_double(v2f64);
  return __builtin_msa_cast_to_scalar_double(𝒙);
#endif
}

#endif
