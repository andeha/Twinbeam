/*  cherry.h - Conditionals on multiple elements. */

#include <Additions/math/simd².hpp>
#include <Additions/math/simdⁱ.hpp>
#if __has_include(<Additions/math/simd⁴.hpp>)
#include <Additions/math/simd⁴.hpp>
#endif
#include <Additions/math/logic.hpp>

namespace Cherry { /* Enable with `using namespace 🍒=Cherry;` */

extern __uint128_t (^simd𝙰𝙽𝙳)(simd_tᵦ 𝒂, __uint128_t 𝒃);
extern __uint128_t (^simd𝙾𝚁)(simd_tᵦ 𝒂, __uint128_t 𝒃);
extern __uint128_t (^is𝙽𝚎𝚐)(simd_tᵦ 𝒙);
extern __uint128_t (^lt)(simd_tᵦ 𝒂, simd_tᵦ 𝒃);
extern __uint128_t (^gt)(simd_tᵦ 𝒂, simd_tᵦ 𝒃);
extern __uint128_t (^ltz₊)(simd_tᵦ 𝒙);
extern __uint128_t (^ltz₋)(simd_tᵦ 𝒙);
extern __uint128_t (^lto)(simd_tᵦ 𝒙);
extern __uint128_t (^eq)(simd_tᵦ 𝒂, simd_tᵦ 𝒃);
extern __uint128_t (^eqz₊)(simd_tᵦ 𝒙);
extern __uint128_t (^eqz₋)(simd_tᵦ 𝒙);
extern __uint128_t (^similar)(simd_tᵦ 𝒂, simd_tᵦ 𝒃, double 𝜀);

/**
 
 Retrospectively pick values stored in 𝗧 ∨ 𝗙 where the signbits are sampled;
 a 𝟶 gives the value in 𝗙 and 𝟷 gives the value in 𝗧.
 
 */

simd_tᵦ pick(simd_tᵦ 𝗧, simd_tᵦ 𝗙, __uint128_t 𝗰𝗼𝗻𝗱ᵦ);
simd_t pick(simd_t 𝗧, simd_t 𝗙, __uint128_t 𝗰𝗼𝗻𝗱);
simd_tₐ pickₐ(simd_tₐ 𝗧, simd_tₐ 𝗙, __uint128_t 𝗰𝗼𝗻𝗱ₐ);
simd_tᵥ pickᵥ(simd_tᵥ 𝗧, simd_tᵥ 𝗙, __uint128_t 𝗰𝗼𝗻𝗱ᵥ);

#define BOTH_SELECTEDᵦ (__uint128_t(0b1)<<127 | __uint128_t(0b1)<<63)
#define ALL_SELECTED (_uint128_t(0b1)<<127 | __uint128_t(0b1)<<95 |            \
  __uint128_t(0b1)<<63 | __uint128_t(0b1)<<31)
#define EIGHT_SELECTEDₐ (__uint128_t(0b1)<<127 | __uint128_t(0b1)<<111 |       \
  __uint128_t(0b1)<<95  | __uint128_t(0b1)<<79 | __uint128_t(0b1)<<63  |       \
  __uint128_t(0b1)<<47  | __uint128_t(0b1)<<31 | __uint128_t(0b1)<<15)
#define SIXTEEN_SELECTEDᵥ (__uint128_t(0b1)<<127 | __uint128_t(0b1)<<119 |     \
  __uint128_t(0b1)<<111 | __uint128_t(0b1)<<103  | __uint128_t(0b1)<<95  |     \
  __uint128_t(0b1)<<87  | __uint128_t(0b1)<<79   | __uint128_t(0b1)<<71  |     \
  __uint128_t(0b1)<<63  | __uint128_t(0b1)<<55   | __uint128_t(0b1)<<47  |     \
  __uint128_t(0b1)<<39  | __uint128_t(0b1)<<31   | __uint128_t(0b1)<<23  |     \
  __uint128_t(0b1)<<15  | __uint128_t(0b1)<<7)

/* Conditional reciprocal i.e $x ∨ x⁻¹$ where all signbits are sampled; a 
  `0` gives x and `1` gives x⁻¹. */
MACRO simd_tᵦ reciprocal(simd_tᵦ 𝒙, __uint128_t 𝗶𝗻𝘃𝗲𝗿𝘁ᵦ) { simd_tᵦ 𝒙⁻¹ =
  __builtin_simd_rcpᵦ(𝒙); return pick(𝒙⁻¹, 𝒙, 𝗶𝗻𝘃𝗲𝗿𝘁ᵦ); } /* x⁻¹ = 1/x */
MACRO simd_tᵦ negate(simd_tᵦ 𝒙, __uint128_t 𝗻𝗲𝗴ᵦ) { simd_tᵦ 🥇 ₊𝟶 = simd_initᵦ(+
  0.0); simd_tᵦ ₋𝒙 = __builtin_simd_subᵦ(₊𝟶, 𝒙); return pick(₋𝒙, 𝒙, 𝗻𝗲𝗴ᵦ); }
  /* Exercise: Investigate faster ways to toggle a floating point: x^(0x80...0|~x) */
}

