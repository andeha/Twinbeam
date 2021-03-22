/**  Simd-integer.hpp | byte-sized, `short` and 32-bit integer simd. */

#if defined NON₋SIMD
typedef __uint128_t simd_tᵥ; typedef __uint128_t simd_tₐ;
typedef __uint128_t simd_tᵢₐ; typedef __uint128_t simd_tₒ;
union ν₋simd { int8_t integers[16]; simd_tᵥ 𝟷𝟸𝟾bit; };
union α₋simd { int16_t integers[8]; simd_tₐ 𝟷𝟸𝟾bit; };
union ια₋simd { int32_t integers[4]; simd_tᵢₐ 𝟷𝟸𝟾bit; };
MACRO simd_tᵥ simd_initᵥ(int8_t c) { return ν₋simd { .integers={c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c} }.𝟷𝟸𝟾bit; }
MACRO simd_tₐ simd_initₐ(int16_t c) { return α₋simd { .integers={c,c,c,c,c,c,c,c} }.𝟷𝟸𝟾bit; }
MACRO simd_tᵢₐ simd_initᵢₐ(int32_t c) { return ια₋simd { .integers={c,c,c,c} }.𝟷𝟸𝟾bit; }
#elif defined __x86_64__
typedef __m128i simd_tᵥ; typedef __m128i simd_tₐ;
typedef __m128i simd_tᵢₐ; typedef __m128i simd_tₒ;
#elif defined __mips__ && !defined NON₋SIMD
typedef signed char v16i8 __attribute__((vector_size(16), aligned(16)));
typedef unsigned char v16u8 __attribute__((vector_size(16), aligned(16)));
typedef short v8i16 __attribute__((vector_size(16), aligned(16)));
typedef unsigned short v8u16 __attribute__((vector_size(16), aligned(16)));
typedef int v4i32 __attribute__((vector_size(16), aligned(16)));
typedef v16i8 simd_tᵥ; /* 🎞/🎨/📖¹⁶ */ typedef v8i16 simd_tₐ; /* ♫♬ */ 
typedef v4i32 simd_tᵢₐ; typedef v2i64 simd_tₒ;
/* ...later specializations: simd_init📏, simd_init📏ᵟ simd_init📜, simd_init🗺. */
#elif defined __armv8a__ && !defined NON₋SIMD
typedef int16x8_t simd_tₐ; typedef uint8x16_t simd_tᵥ;
typedef int32x4_t simd_tᵢₐ; typedef int64x2_t simd_tₒ;
#endif

#if defined __mips__ && !defined NON₋SIMD
#define simd_initᵥ(x) __builtin_msa_fill_b(x)
#define simd_initₐ(x) __builtin_msa_fill_h(x)
#define simd_initᵢₐ(x) __builtin_msa_fill_w(x)
/* #define simd_initₒ(x) __builtin_msa_fill_d(x) */
#elif defined __x86_64__
MACRO simd_tₐ simd_initₐ(int16_t x) { return _mm_set1_epi16(x); }
MACRO simd_tᵢₐ simd_initᵢₐ(int32_t x) { return _mm_set1_epi32(x); }
MACRO simd_tᵥ simd_initᵥ(int8_t x) { return _mm_set1_epi8(x); }
/* MACRO simd_tₒ simd_initₒ(uint64_t x) { return _mm_set1_epi64((__m64)x); }
MACRO __m128i simd_initᵥ(uint8_t x) { __m128i y; asm { vpbroadcastb y, x }; return y; } */
#endif

MACRO uint8_t simd_scalarᵥ(simd_tᵥ 𝒙)
{
#if defined NON₋SIMD
  return ν₋simd { .𝟷𝟸𝟾bit = 𝒙 }.integers[0];
#elif defined __mips__ && !defined NON₋SIMD
  return __builtin_msa_copy_s_b(𝒙,0); /* __builtin_msa_copy_u_b */
#elif defined __x86_64__
  return _mm_extract_epi8(𝒙,0); /* ⬷ also VPEXTRB/PEXTRB. */
#endif
}

MACRO int16_t simd_scalarₐ(simd_tₐ 𝒙)
{
#if defined NON₋SIMD
  return α₋simd { .𝟷𝟸𝟾bit = 𝒙 }.integers[0];
#elif defined __mips__ && !defined NON₋SIMD
  return __builtin_msa_copy_s_h(𝒙,0);
#elif defined __x86_64__
  return _mm_extract_epi16(𝒙,0); /* ⬷ also VPEXTRW/PEXTRW. */
#endif
}

MACRO int32_t simd_scalarᵢₐ(simd_tᵢₐ 𝒙)
{
#if defined NON₋SIMD
  return ια₋simd { .𝟷𝟸𝟾bit = 𝒙 }.integers[0];
#elif defined __mips__ && !defined NON₋SIMD
  return __builtin_msa_copy_s_w(𝒙,0);
#elif defined __x86_64__
  return _mm_extract_epi32(𝒙,0); /* ⬷ also VPEXTRD/PEXTRD. */
#endif
}


#if defined __mips__ && !defined NON₋SIMD
MACRO v16u8 clz(v16u8 x) { return __builtin_msa_nlzc_b(x); }
/* ⬷ vector element count of leading bits set to `0`. */
#endif

MACRO simd_tₐ Shift𝚁ₐᵣᵢ(simd_tₐ 𝒙, simd_tₐ 𝒏)
{
#if defined NON₋SIMD
  return α₋simd { .𝟷𝟸𝟾bit = 𝒙 }.integers[0]; /* ⬷ error. */
#elif defined __mips__ && !defined NON₋SIMD
  return __builtin_msa_sra_h(𝒙,𝒏);
#elif defined __x86_64__
  return _mm_sra_epi16(𝒙,𝒏);
#endif
}; /* ⬷ I․𝘦 'arithmetic right shift'. */

union 𝟸₋int₋64
{
  int64_t integers[2];
  simd_tₒ simd;
#ifdef __mips__
  uint64_t mips;
#elif defined __x86_64__
  __m64 intel;
#endif
  unsigned short 🥈 count = 2;
};

