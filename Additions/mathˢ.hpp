/*  mathˢ.hpp | Simd and originally from --<Additions>--<System.h>. */

#include <Additions/math/cherry.h>

simd_tᵦ atan¹²³⁴(simd_tᵦ 𝒚, simd_tᵦ 𝒙); /* ≈atan(𝒚/𝒙) */
leaf simd_tᵦ arctan(simd_tᵦ 𝒙); /* simd_t arctan(simd_t 𝒙); */
simd_tᵦ mod(simd_tᵦ 𝒙, simd_tᵦ 𝒚); /* 𝒙 𝑚𝑜𝑑 𝒚 = 𝒙 - 𝒚 ⌊𝒙/𝒚⌋ */
/* Eulers' formula: ℯˣⁱ = cos x + 𝓲 sin x (= 𝑧) */
void sincos(simd_tᵦ 𝜃, simd_tᵦ &𝒔, simd_tᵦ &𝒄); /* 𝒔,𝒄 ∈ [-1, 1] */
leaf simd_tᵦ floor(simd_tᵦ 𝒙); int32² nearest(simd_tᵦ 𝒙);
/* simd_t 🎞ℯ(simd_t 𝒙); Fastest, but inaccurate with 𝟄 ≤ 0.000391475.
simd_t 🎨ℯᵋˣ(simd_t 𝒙); simd_tᵦ 🔭ℯᵋˣ(simd_tᵦ 𝒙); Only for |𝑥| ≤ 1.
simd_t 🎨ℯ(simd_t 𝒙); ⬷ Four concurrent 𝚏𝚕𝚘𝚊𝚝's. */
leaf simd_tᵦ tanh⁻¹(simd_tᵦ 𝒙); leaf simd_tᵦ tanh(simd_tᵦ 𝜃); /* -1 < tanh(𝜃) < 1 */
leaf simd_tᵦ tan(simd_tᵦ 𝜃); /* -∞ < tan(𝜃) < ∞ */
/* simd_tᵦ 𝟸ˣ(simd_tᵦ 𝒙), 𝟸ⁱ(simd_t²₆₄ 𝒊) simd_tᵦ log₂(simd_tᵦ 𝒙) */
simd_tᵦ ℯ🔭²(simd_tᵦ 𝒙); simd_tᵦ half₋leaf logₑ(simd_tᵦ 𝒙);

#pragma mark 'With that special competitive edge' (Formerly in file named --<Additions>--<Watts.hpp>)

MACRO simd_tᵦ 𝚙𝚘𝚠(simd_tᵦ 𝒃, simd_tᵦ 𝒙) { simd_tᵦ acc=logₑ(𝒃); 
  acc = __builtin_simd_mulᵦ(𝒙,acc);
  return ℯ🔭²(acc);
} /* todo: `int pow(simd_tᵦ 𝒃, simd_tᵦ 𝒙, v2i64 &𝟷𝟶ᵐ, simd_tᵦ &significand)`. */

MACRO simd_tᵦ logₓ(simd_tᵦ 𝒘, simd_tᵦ 𝒙) { /* logₓ w = ln w / ln x */
  simd_tᵦ acc₁=logₑ(𝒘), acc₂=logₑ(𝒙);
  simd_tᵦ acc = __builtin_simd_divᵦ(acc₁,acc₂);
  return acc; }

MACRO simd_tᵦ abs(simd_tᵦ 𝒙) { /* |x| */
#ifdef NON₋SIMD
  auto 𝒙₂ = 𝛽₋simd { .simd=𝒙 };
  𝒙₂.doubles[1] = abs(𝒙₂.doubles[1]); 𝒙₂.doubles[0] = abs(𝒙₂.doubles[0]);
  return 𝒙₂.simd;
#elif defined __mips__ && !defined(NON₋SIMD)
  simd_tᵦ 🥈 sign = simd_tᵦ { 31, 31 };
  return __builtin_msa_bclr_d(𝒙,sign); /* Also: Shim { .mips=__builtin_msa_and_v(a₂.mips, b₂.mips) }.llvm */
#elif defined __x86_64__ && !defined(NON₋SIMD) /*  Exercise~X: Validate |x| for ₋0.0 and ₊0.0. */
  __uint128_t 𝗻𝗲𝗴ᵦ = Cherry::ltz₊(𝒙);
  return Cherry::negate(𝒙,𝗻𝗲𝗴ᵦ);
  /* union intel₋simd { double doubles[2]; simd_tᵦ simd; __m128d intelᵈ; __m128i intelⁱ; }; */
#endif
}

MACRO simd_tᵦ sign(simd_tᵦ 𝒙) { /* Sometimes erroneously called `sgn`. */
  simd_tᵦ 🥇 ₊𝟷=simd_initᵦ(1.0), ₋𝟷=simd_initᵦ(-1.0);
  __uint128_t 𝗰𝗼𝗻𝗱ᵦ = Cherry::ltz₋(𝒙);
  return Cherry::pick(₋𝟷, ₊𝟷, 𝗰𝗼𝗻𝗱ᵦ);
}

MACRO simd_tᵦ sin(simd_tᵦ 𝒙) { simd_tᵦ s,c; sincos(𝒙,s,c); return s; }
MACRO simd_tᵦ cos(simd_tᵦ 𝒙) { simd_tᵦ s,c; sincos(𝒙,s,c); return c; }

MACRO simd_tᵦ asin(simd_tᵦ 𝒙) { /* asin(x) = 2 arctan(x/(1 + √(1-x²))), where x≤1 leads to complex later. */
  simd_tᵦ 🥇 𝟷=simd_initᵦ(1.0), 𝟸=simd_initᵦ(2.0);
  simd_tᵦ x² = __builtin_simd_mulᵦ(𝒙,𝒙);
  simd_tᵦ 𝟷⁻x² = __builtin_simd_subᵦ(𝟷,x²);
  simd_tᵦ ₍𝟷⁻x²₎⁰⁵ = __builtin_simd_sqrtᵦ(𝟷⁻x²);
  simd_tᵦ denom = __builtin_simd_addᵦ(𝟷, ₍𝟷⁻x²₎⁰⁵);
  simd_tᵦ param = __builtin_simd_divᵦ(𝒙, denom);
  simd_tᵦ 𝖺𝗍𝖺𝗇 = arctan(param);
  return __builtin_simd_mulᵦ(𝟸, 𝖺𝗍𝖺𝗇);
} /* Also: arcsin(x) = π/2 - sqrt(1 - x)(a₀ + a₁*x + a₂*x² + a₃*x³),
   a₀=1.5707288, a₁=-0.2121144, a₂=0.0742610, a₃=-0.0187293 */

MACRO simd_tᵦ acos(simd_tᵦ 𝒙) { /* acos(x) = 2 arctan(√(1-x²) / (1+x)) */
  simd_tᵦ 🥇 𝟷=simd_initᵦ(1.0), 𝟸=simd_initᵦ(2.0);
  simd_tᵦ x² = __builtin_simd_mulᵦ(𝒙,𝒙);
  simd_tᵦ 𝟷⁻x² = __builtin_simd_subᵦ(𝟷,x²);
  simd_tᵦ num = __builtin_simd_sqrtᵦ(𝟷⁻x²);
  simd_tᵦ denom = __builtin_simd_addᵦ(𝟷,𝒙);
  simd_tᵦ param = __builtin_simd_divᵦ(num, denom);
  simd_tᵦ 𝖺𝗍𝖺𝗇 = arctan(param);
  return __builtin_simd_mulᵦ(𝟸, 𝖺𝗍𝖺𝗇);
} /* See also --<khinchin.cpp>: double khinchin_arccos(double x) { return π/2 - khinchin_arcsin(x); } */

MACRO simd_tᵦ frac(simd_tᵦ 𝒙) { simd_tᵦ 🥇 𝟷=simd_initᵦ(1.0); return mod(𝒙,𝟷); }

#pragma mark 'Primititives for a single `double` type' (--<Additions>--<Stirlings.hpp>)

MACRO double abs(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = abs(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double 𝚙𝚘𝚠(double b, double x) { simd_tᵦ 𝒃 = simd_initᵦ(b), 𝒙 = simd_initᵦ(x), 𝒚 = 𝚙𝚘𝚠(𝒃, 𝒙); return simd_scalarᵦ(𝒚); } LONGTOOTH
// MACRO int pow(double b, double x, __builtin_int_t &𝟷𝟶ᵐ, double &significand) { 
// /* wᵗ = eᵗˡⁿʷ and eˣ=𝟷𝟶ᵐ×eʸ ⟶ No Horner. */ }
MACRO double sqrt(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = __builtin_simd_sqrtᵦ(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double ℯ(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = ℯ🔭²(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double logₑ(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = logₑ(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double sin(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = sin(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double cos(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = cos(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double tan(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = tan(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double arctan(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = arctan(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double asin(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = asin(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double acos(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = acos(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double tanh(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = tanh(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double tanh⁻¹(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = tanh⁻¹(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double atan¹²³⁴(double y, double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = simd_initᵦ(y), 𝒓 = atan¹²³⁴(𝒚,𝒙); return simd_scalarᵦ(𝒓); } /* ⬷ Requires 'Compose' button when `²₃atan₄¹`. */
MACRO double mod(double x, double y) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = simd_initᵦ(y), 𝒓 = mod(𝒙,𝒚); return simd_scalarᵦ(𝒓); }
MACRO double floor(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = floor(𝒙); return simd_scalarᵦ(𝒚); }
MACRO int32_t nearest(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x); int32² 𝒚 = nearest(𝒙); return 𝒚.ints[0]; }
MACRO double sign(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = sign(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double frac(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = frac(𝒙); return simd_scalarᵦ(𝒚); }
