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

/* ... */

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
