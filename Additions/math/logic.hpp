/**  logic.hpp | while llvm on x64 and on MIPS generates non-SIMD for __uint128_t. */

MACRO __uint128_t Simd𝖷𝖮𝖱(__uint128_t a, __uint128_t b) {
#if defined __mips__ && !defined(NON₋SIMD)
   union Shim { __uint128_t llvm; v16u8 mips; } a₂={ .llvm=a }, b₂={ .llvm=b };
   return Shim { .mips=__builtin_msa_xor_v(a₂.mips, b₂.mips) }.llvm;
#elif defined __x86_64__ && !defined(NON₋SIMD)
   union Shim { __uint128_t llvm; __m128i intel; } a₂={ .llvm=a }, b₂={ .llvm=b };
   return Shim { .intel=_mm_xor_si128(a₂.intel, b₂.intel) }.llvm;
#elif defined NON₋SIMD
   return a ^ b;
#endif
} /* ⬷ available as __builtin_msa_xori_b. */

MACRO __uint128_t Simd𝖠𝖭𝖣(__uint128_t a, __uint128_t b) {
#if defined __mips__ && !defined(NON₋SIMD)
   union Shim { __uint128_t llvm; v16u8 mips; } a₂={ .llvm=a }, b₂={ .llvm=b };
   return Shim { .mips=__builtin_msa_and_v(a₂.mips, b₂.mips) }.llvm;
#elif defined __x86_64__ && !defined(NON₋SIMD)
   union Shim { __uint128_t llvm; __m128i intel; } a₂={ .llvm=a }, b₂={ .llvm=b };
   return Shim { .intel=_mm_and_si128(a₂.intel, b₂.intel) }.llvm;
#elif defined NON₋SIMD
   return a & b;
#endif
} /* ⬷ available as __builtin_msa_andi_b. */

MACRO __uint128_t Simd𝖮𝖱(__uint128_t a, __uint128_t b) {
#if defined __mips__ && !defined(NON₋SIMD)
   union Shim { __uint128_t llvm; v16u8 mips; } a₂={ .llvm=a }, b₂={ .llvm=b };
   return Shim { .mips=__builtin_msa_or_v(a₂.mips, b₂.mips) }.llvm;
#elif defined __x86_64__ && !defined(NON₋SIMD)
   union Shim { __uint128_t llvm; __m128i intel; } a₂={ .llvm=a }, b₂={ .llvm=b };
   return Shim { .intel=_mm_or_si128(a₂.intel, b₂.intel) }.llvm; 
   /* ⬷ duplicate _mm_or_pd(a₂.intel, b₂.intel); */
#elif defined NON₋SIMD
   return a | b;
#endif
} /* ⬷ available as __builtin_msa_ori_b. */

MACRO __uint128_t Simd𝖭𝖮𝖳(__uint128_t x) {
  __uint128_t 🥈 mask = __uint128_t(0xFFFFFFFFffffffff)<<64 | 0xFFFFFFFFffffffff;
  return Simd𝖷𝖮𝖱(mask, x);
} /* ⬷ available as __builtin_msa_bnegi_b and 'return ~𝒙'. */


