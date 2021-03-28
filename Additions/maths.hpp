/*  maths.hpp | simds originally from --<Additions>--<System.h>. */

namespace Natural {
  constexpr auto π = 3.1415926535897932384626433832795028841971693993751058209749;
  /* double acc=0.0, A[] = { 1, 2,1,  1,4,1,1,6,1,1,8, 1,1,10,1,1,12,1,1,14, 1,1,16,1, 1,18, 1}; … 2+e with great precision. */
  /* double acc=0.0, A[] = { 7,15,1,292,1,1,1,2,1,3,1,14,2, 1,1,2, 2,2,2, 1,84,2, 1,1,15, 3,13}; … and 3+𝜋. */
  constexpr auto ℯ = 2.7182818284590452353602874713526624977572470936999595749669;
  constexpr auto φ = 1.6180339887498948482045868343656381177203091798057628621354;
} /* also Eulers' Ɣ and ℎ (Plancks constant). Realization see ❡+EOT. */

#include <Additions/math/cherry.h>

simd_tᵦ 𝟷𝟸𝟹𝟺₋atan(simd_tᵦ 𝒚, simd_tᵦ 𝒙); /* ≈ atan(𝒚/𝒙) ∧ is well-defined for x=0. */
leaf₋function simd_tᵦ arctan(simd_tᵦ 𝒙);
leaf₋function simd_t arctan(simd_t 𝒙);
simd_tᵦ modulo(simd_tᵦ 𝒙, simd_tᵦ 𝒚); /* = 𝒙 𝑚𝑜𝑑 𝒚 = 𝒙 - 𝒚 ⌊𝒙/𝒚⌋ ⬷ requires a call to 'floor'. */
leaf₋function void sincos(simd_tᵦ 𝜃, simd_tᵦ * 𝒔, simd_tᵦ * 𝒄); /* s,c ∈ [-1,1]. */
/* ⬷ Eulers' formula: ℯˣⁱ = cos x + 𝓲 sin x (= 𝑧) */
leaf₋function simd_tᵦ floor₋ℝ(simd_tᵦ 𝒙);
leaf₋function simd_tᵢₐ floor₋ℤ(simd_tᵦ 𝒙);
leaf₋function simd_tᵦ tanh⁻¹(simd_tᵦ 𝒙);
leaf₋function simd_tᵦ tanh(simd_tᵦ 𝜃); /* -1 < tanh(𝜃) < 1 */
leaf₋function simd_tᵦ tan(simd_tᵦ 𝜃); /* -∞ < tan(𝜃) < ∞ */
/* simd_tᵦ 𝟸ˣ(simd_tᵦ 𝒙), 𝟸ⁱ(simd_t²₆₄ 𝒊) simd_tᵦ log₂(simd_tᵦ 𝒙) */
leaf₋function simd_tᵦ ℯ🔭²(simd_tᵦ 𝒙);
intrinsic₋leaf simd_tᵦ logₑ(simd_tᵦ 𝒙);
leaf₋function simd_tᵢₐ nearest(simd_tᵦ 𝒙);

#pragma mark formerly in file named --<Additions>--<Watts.hpp>

inline simd_tᵦ substandard₋power(simd_tᵦ 𝒃, simd_tᵦ 𝒙)
{
  simd_tᵦ acc=logₑ(𝒃); acc = __builtin_simd_mulᵦ(𝒙,acc); return ℯ🔭²(acc);
} /* todo: 'int pow(simd_tᵦ 𝒃, simd_tᵦ 𝒙, v2i64 &𝟷𝟶ᵐ, simd_tᵦ &significand)'. 
int pow(double b, double x, __builtin_int_t &𝟷𝟶ᵐ, double &significand) {
wᵗ = eᵗˡⁿʷ and eˣ=𝟷𝟶ᵐ×eʸ ⟶ no Horner. } */

inline simd_tᵦ logₓ(simd_tᵦ 𝒘, simd_tᵦ 𝒙)
{
  simd_tᵦ acc₁=logₑ(𝒘), acc₂=logₑ(𝒙); return __builtin_simd_divᵦ(acc₁,acc₂);
} /* ⬷ logₓ w = ln w / ln x */

inline simd_tᵦ abs(simd_tᵦ 𝒙)
{ /* = |x| */
#if defined NON₋SIMD
  auto 𝒙₂ = 𝛽₋simd { .𝟷𝟸𝟾bit=𝒙 };
  𝒙₂.doubles[1] = abs(𝒙₂.doubles[1]); 𝒙₂.doubles[0] = abs(𝒙₂.doubles[0]);
  return 𝒙₂.𝟷𝟸𝟾bit;
#elif defined __mips__ && !defined(NON₋SIMD)
  simd_tᵦ 🥈 sign = simd_tᵦ { 31, 31 };
  return __builtin_msa_bclr_d(𝒙,sign); /* also: Shim { .mips=__builtin_msa_and_v(a₂.mips, b₂.mips) }.llvm */
#elif defined __x86_64__ && !defined(NON₋SIMD) /*  Exercise~X: Validate |x| for ₋0.0 and ₊0.0. */
  __uint128_t 𝗻𝗲𝗴ᵦ = Cherry::ltz₊(𝒙);
  return Cherry::negateᵦ(𝒙,𝗻𝗲𝗴ᵦ);
  /* union intel₋simd { double doubles[2]; simd_tᵦ simd; __m128d intelᵈ; __m128i intelⁱ; }; */
#endif
} Sourpatch(abs, "See --<Additions>--<Additions.h>{abs64d₁ and abs64d₂}.")

MACRO simd_tᵦ sign(simd_tᵦ 𝒙)
{
  simd_tᵦ 🥇 ₊𝟷=simd_initᵦ(1.0), ₋𝟷=simd_initᵦ(-1.0);
  __uint128_t 𝗰𝗼𝗻𝗱ᵦ = Cherry::ltz₋(𝒙);
  return Cherry::pickᵦ(₋𝟷,₊𝟷,𝗰𝗼𝗻𝗱ᵦ);
} /* ⬷ sometimes in literature called 'sgn'. */

MACRO simd_tᵦ sin(simd_tᵦ 𝒙) { simd_tᵦ s,c; sincos(𝒙,&s,&c); return s; }
MACRO simd_tᵦ cos(simd_tᵦ 𝒙) { simd_tᵦ s,c; sincos(𝒙,&s,&c); return c; }

inline simd_tᵦ asin(simd_tᵦ 𝒙)
{ /* asin(x) = 2 arctan(x/(1 + √(1-x²))), where x≤1 leads to complex later. */
  simd_tᵦ 🥇 𝟷=simd_initᵦ(1.0), 𝟸=simd_initᵦ(2.0);
  simd_tᵦ x² = __builtin_simd_mulᵦ(𝒙,𝒙);
  simd_tᵦ 𝟷⁻x² = __builtin_simd_subᵦ(𝟷,x²);
  simd_tᵦ ₍𝟷⁻x²₎⁰⁵ = __builtin_simd_sqrtᵦ(𝟷⁻x²);
  simd_tᵦ denom = __builtin_simd_addᵦ(𝟷, ₍𝟷⁻x²₎⁰⁵);
  simd_tᵦ param = __builtin_simd_divᵦ(𝒙,denom);
  simd_tᵦ 𝖺𝗍𝖺𝗇 = arctan(param);
  return __builtin_simd_mulᵦ(𝟸,𝖺𝗍𝖺𝗇);
} /* also: arcsin(x) = π/2 - sqrt(1 - x)(a₀ + a₁*x + a₂*x² + a₃*x³), 
  a₀=1.5707288, a₁=-0.2121144, a₂=0.0742610, a₃=-0.0187293 */

inline simd_tᵦ acos(simd_tᵦ 𝒙)
{ /* acos(x) = 2 arctan(√(1-x²) / (1+x)) */
  simd_tᵦ 🥇 𝟷=simd_initᵦ(1.0), 𝟸=simd_initᵦ(2.0);
  simd_tᵦ x² = __builtin_simd_mulᵦ(𝒙,𝒙);
  simd_tᵦ 𝟷⁻x² = __builtin_simd_subᵦ(𝟷,x²);
  simd_tᵦ num = __builtin_simd_sqrtᵦ(𝟷⁻x²);
  simd_tᵦ denom = __builtin_simd_addᵦ(𝟷,𝒙);
  simd_tᵦ param = __builtin_simd_divᵦ(num,denom);
  simd_tᵦ 𝖺𝗍𝖺𝗇 = arctan(param);
  return __builtin_simd_mulᵦ(𝟸,𝖺𝗍𝖺𝗇);
} /* ⬷ see also --<khinchin.cpp>: double khinchin_arccos(double x) { return π/2 - khinchin_arcsin(x); } */

MACRO simd_tᵦ frac(simd_tᵦ 𝒙) { simd_tᵦ 🥇 𝟷 = simd_initᵦ(1.0); return modulo(𝒙,𝟷); }

#pragma mark formerly in --<Additions>--<Stirlings.hpp>, primititives for the single 𝗱𝗼𝘂𝗯𝗹𝗲 type

MACRO double substandard₋power(double b, double x) { simd_tᵦ 𝒃 = simd_initᵦ(b), 𝒙 = simd_initᵦ(x), 
 𝒚 = substandard₋power(𝒃,𝒙); return simd_scalarᵦ(𝒚); }
MACRO double sqrt(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = __builtin_simd_sqrtᵦ(𝒙); 
 return simd_scalarᵦ(𝒚); }
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
MACRO double 𝟷𝟸𝟹𝟺₋atan(double y, double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = simd_initᵦ(y), 
 𝒓 = 𝟷𝟸𝟹𝟺₋atan(𝒚,𝒙); return simd_scalarᵦ(𝒓); }
MACRO double modulo(double x, double y) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = simd_initᵦ(y), 𝒓 = modulo(𝒙,𝒚);
 return simd_scalarᵦ(𝒓); }
MACRO double floor₋ℝ(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = floor₋ℝ(𝒙); return simd_scalarᵦ(𝒚); }
MACRO int64_t nearest(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x); simd_tₒ 𝒚 = nearest(𝒙); return simd_scalarᵢₐ(𝒚); }
MACRO double sign(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = sign(𝒙); return simd_scalarᵦ(𝒚); }
MACRO double frac(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = frac(𝒙); return simd_scalarᵦ(𝒚); }

enum class Newtoncontrol { ok, done, abort };
typedef double (^Computational)(double x);
FOCAL int Newton(Computational f, Computational f₋prime, 
  double * x₀, void (^ping)(Newtoncontrol &ctrl)
);

