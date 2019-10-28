/**  simdⁱ.hpp - Byte-sized and `short`/32-bit integer SIMD. */

#ifdef __x86_64__
typedef __m128i simd_tᵥ; typedef __m128i simd_tₐ; typedef __m128i simd_tᵢₐ; 
/* typedef __m128i simd_tₒ; */
#elif defined __mips__
typedef signed char v16i8 __attribute__((vector_size(16), aligned(16)));
typedef unsigned char v16u8 __attribute__((vector_size(16), aligned(16)));
typedef short v8i16 __attribute__((vector_size(16), aligned(16)));
typedef unsigned short v8u16 __attribute__((vector_size(16), aligned(16)));
typedef int v4i32 __attribute__((vector_size(16), aligned(16)));
typedef v16i8 simd_tᵥ; /* 🎞/🎨/📖¹⁶ */
typedef v8i16 simd_tₐ; /* ♫♬ */ typedef v4i32 simd_tᵢₐ; /* typedef v2i64 simd_tₒ; */
#endif /* …later specializations: simd_init📏, simd_init📏ᵟ simd_init📜, simd_init🗺. */

MACRO uint8_t simd_scalarᵥ(simd_tᵥ 𝒙) {
#ifdef __mips__
   return __builtin_msa_copy_s_b(𝒙, 0); /* __builtin_msa_copy_u_b */
#elif defined __x86_64__
   return _mm_extract_epi8(𝒙, 0); /* VPEXTRB/PEXTRB */
#endif
}

#ifdef __mips__
MACRO v16u8 clz(v16u8 x) {
   return __builtin_msa_nlzc_b(x);
} /* Vector element count of leading bits set to `0`. */
#endif

MACRO simd_tₐ Shift𝚁ₐᵣᵢ(simd_tₐ 𝒙, simd_tₐ 𝒏) {
#ifdef __mips__
   return __builtin_msa_sra_h(𝒙, 𝒏);
#elif defined __x86_64__
   return _mm_sra_epi16(𝒙, 𝒏);
#endif
}; /* I․𝘦 'Arithmetic right shift'. */

union int32² {
  int32_t ints[2];
#ifdef __mips__
  uint64_t mips;
#elif defined __x86_64__
  __m64 intel;
#endif
  short unsigned 🥈 count = 2;
};

