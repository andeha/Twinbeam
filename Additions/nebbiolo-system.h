/*  *
 *  System.h ('Nature tells us life is')
   sometimes cognized inside 𝐵𝐿𝑈𝐸 𝑈𝑁𝐼𝐶𝑂𝑅𝑁 𝑂𝐹 𝑆𝑇𝐸𝐸𝐿.
 *  (A․𝘬․a 'while on the ferromagnetic ellipsoid'.)
    *                                                      (DO-NOT-CIRCULATE) ❡ */

#ifndef __SYSTEM_H
#define __SYSTEM_H

namespace Naturals {
  constexpr auto π = 3.1415926535897932384626433832795028841971693993751058209749;
  /* double acc=0.0, A[] = { 1, 2,1,  1,4,1,1,6,1,1,8, 1,1,10,1,1,12,1,1,14, 1,1,16,1, 1,18, 1}; … 2+e with great precision. */
  /* double acc=0.0, A[] = { 7,15,1,292,1,1,1,2,1,3,1,14,2, 1,1,2, 2,2,2, 1,84,2, 1,1,15, 3,13}; … and 3+𝜋. */
  constexpr auto ℯ = 2.7182818284590452353602874713526624977572470936999595749669;
  constexpr auto φ = 1.6180339887498948482045868343656381177203091798057628621354;
} /* Also Eulers' Ɣ. Realization see ❡+EOT. */

#pragma mark Coordinate Systems and Functionals (also in --<Conformal.h>)

#include <Twinbeam.h> /* Partial order, convention and hypothesis. */

enum Variation { Rasterized, FunctionalD, FunctionalS };

#include <Additions/math/cherry.h>

namespace Cartesian3d { typedef floatʳ type; typedef type (^Hilbert)(Chronology
  ::Instant t); struct Ħ { Hilbert x, y, z; }; struct 𝗣 { type x, y, z; }; struct
  Variat { union { Cartesian3d::𝗣 p; Cartesian3d::Ħ ħ; }; Variation v; }; }

namespace Modulation { typedef float half; /* kludge */ typedef struct { half value₁; half value₂; } halfpair;
  typedef halfpair (^HilbertS)(Chronology::Instant t); /* ^🎲 */
  typedef float (^HilbertD)(Chronology::Instant t);    /* ^🕯 */
  struct ĦD { HilbertD ampl, angular, phase; };        /* Ħ🕯 (Determinstic Hilbert triple) */
  struct ĦS { HilbertS ampl, angular, phase; };        /* Ħ🎲 (Stochastic Hilbert triple) */
  struct 𝗣 { half ampl, angular, phase; };             /* (Sampled Hilbert triple) */
  struct Variat { union { 𝗣 p; ĦD ħd; ĦS ħs; }; Variation v; }; } /* TODO: Validate sizeof HilbertS == sizeof HilbertD == 32,64 */

namespace Celestial { typedef double type; typedef type (^Hilbert)(Chronology🚀
  ::Instant t); struct Ħ { Hilbert r, 𝛳, 𝜑; }; struct 𝗣 { type r, 𝛳, 𝜑; };
  struct Variat { union { Celestial::𝗣 p; Celestial::Ħ ħ; }; Variation v; }; }

/**  Angles continue in a clockwise direction, rather than counter-clockwise. */

namespace Eulerangles { typedef double type;
  typedef Opt<int> (^HilbertH)(Chronology🦠::Instant t, float⁴ 𝛳𝛹𝛷ᵖʳᵉᵛ, float &ᵒᵘᵗ); /* Hilbert 𝘏𝘰𝘣𝘣𝘺𝘪𝘴𝘵 */
  typedef Opt<int> (^HilbertP)(Chronology🦠::Instant t, double⁴ 𝛳𝛹𝛷ᵖʳᵉᵛ, double &ᵒᵘᵗ); /* Hilbert 𝘗𝘳𝘰 */
  struct ĦH { HilbertH 𝛳ᴴ, 𝛹ᴴ, 𝛷ᴴ; }; struct ĦP { HilbertP 𝛳ᴾ, 𝛹ᴾ, 𝛷ᴾ; }; struct 𝗣 { type 𝛳, 𝛹, 𝛷; };
  struct Variat { union { Eulerangles::𝗣 p; Eulerangles::ĦH ħ; }; Variation v; }; }

enum class Earthcompass { Nᵀᴿᵁᴱ, /* Nᴹᴬᴳ, */ S, E, W }; /* 𝑵 𝙽 𝐸 𝑆 𝑊: magnetic field required. */

typedef struct EarthbasedSpatial {
   double degrees, arcminutes, arcseconds; /* Relatively calm. */
   Earthcompass compass;
} Sexagesimal; /* For 𝑝𝑎𝑟𝑎𝑙𝑙𝑒𝑙𝑠 and 𝑚𝑒𝑟𝑖𝑑𝑖𝑎𝑛𝑠. */

/* #define EarthBasedSpatialTemporalHeading 360 == 0 degrees */

struct Rasterized2d { typedef __builtin_int_t type; type x, y; };

namespace Cylindrical { typedef double type; typedef type (^Hilbert)(Chronology
  ::Instant t); struct Ħ { Hilbert h, 𝜑; }; struct 𝗣 { type h, 𝜑; }; struct
  Variat { union { Cylindrical::𝗣 p; Cylindrical::Ħ ħ; }; Variation v; }; }

namespace Polar { typedef double type; typedef type (^Hilbert)(Chronology
  ::Instant t); struct Ħ { Hilbert r, 𝜑; }; struct 𝗣 { type r, 𝜑; }; struct
  Variat { union { Polar::𝗣 p; Polar::Ħ ħ; }; Variation v; }; }

struct Cartesian2d { typedef floatʳ type; type x, y;
   
   Cartesian2d(floatʳ x, floatʳ y) : x(x), y(y) { }
   
   Cartesian2d(const Cartesian2d &p) : x(p.x), y(p.y) { }
   
};

void Mercator⁻¹(simd_tᵦ 𝒑𝑥, simd_tᵦ 𝒑𝑦, simd_tᵦ 𝜃₀, double R₁₂,
  simd_tᵦ& 𝜃ᵒᵘᵗ, simd_tᵦ& 𝜑ᵒᵘᵗ);
/* See --<Geologics.hpp> for a generalization of the parameter `R₁₂`. */

FOSSILATED MACRO float mutual₂(float v₀, float v₁, float t /*∈[0…1)*/) {
  return v₀ + t * (v₁ - v₀); } /* H₁: Compiles to 𝙼𝙰𝙳𝙳 and 𝙼𝚂𝚄𝙱. */
FOSSILATED MACRO float mutual₃(float v₀, float v₁, float t /*∈[0…1)*/) {
  return (1.0 - t) * v₀ + t * v₁; } /* H₁: Compiles to 𝙼𝚄𝙻 and 𝙵𝙼𝙰𝙳𝙳. */
MACRO simd_t mutual(simd_t 𝒗₀, simd_t 𝒗₁, simd_t 𝒕) { simd_t acc =
  __builtin_simd_sub(𝒗₁, 𝒗₀); return __builtin_simd_fmadd(𝒕, acc, 𝒗₀); }
MACRO simd_tᵦ mutual(simd_tᵦ 𝒗₀, simd_tᵦ 𝒗₁, simd_tᵦ 𝒕) { simd_tᵦ acc =
  __builtin_simd_subᵦ(𝒗₁, 𝒗₀); return __builtin_simd_fmaddᵦ(𝒕, acc, 𝒗₀); }
/* In Sᵢ `mutual` may a\ᵇᵉ/․𝘬․a `lerp`. */

#pragma mark - Pumpin' 𝗳𝗹𝗼𝗮𝘁'𝙨 (Branched from --<Additions>--<mathˢ.h>)

simd_tᵦ atan¹²³⁴(simd_tᵦ 𝒚, simd_tᵦ 𝒙); /* ≈atan(𝒚/𝒙) */
simd_tᵦ leaf arctan(simd_tᵦ 𝒙); simd_t leaf arctan(simd_t 𝒙);
simd_tᵦ mod(simd_tᵦ 𝒙, simd_tᵦ 𝒚); /* 𝒙 𝑚𝑜𝑑 𝒚 = 𝒙 - 𝒚 ⌊𝒙/𝒚⌋ */
/* Eulers' formula: ℯⁱˣ = cos x + 𝓲 sin x (= 𝑧) */
void sincos(simd_tᵦ 𝜃, simd_tᵦ &𝒔, simd_tᵦ &𝒄); /* 𝒔,𝒄 ∈[-1, 1] */
simd_tᵦ leaf floor(simd_tᵦ 𝒙); int32² nearest(simd_tᵦ 𝒙);
/* simd_t 🎞ℯ(simd_t 𝒙); Fastest, but inaccurate with 𝜀 ≤ 0.000391475.
simd_t 🎨ℯᵋˣ(simd_t 𝒙); simd_tᵦ 🔭ℯᵋˣ(simd_tᵦ 𝒙); Only for |𝑥| ≤ 1.
simd_t 🎨ℯ(simd_t 𝒙); ⬷ Four concurrent 𝚏𝚕𝚘𝚊𝚝's. */
simd_tᵦ leaf tanh⁻¹(simd_tᵦ 𝒙); simd_tᵦ leaf tanh(simd_tᵦ 𝜃); /* -1 < tanh(𝜃) < 1 */
simd_tᵦ leaf tan(simd_tᵦ 𝜃); /* -∞ < tan(𝜃) < ∞ */
/* simd_tᵦ 𝟸ˣ(simd_tᵦ 𝒙), 𝟸ⁱ(simd_t²₆₄ 𝒊) simd_tᵦ log₂(simd_tᵦ 𝒙) */
simd_tᵦ ℯ🔭²(simd_tᵦ 𝒙); simd_tᵦ half₋leaf logₑ(simd_tᵦ 𝒙);

#include <Additions/mathˢ.hpp>

/*  Default 𝚏𝚕𝚘𝚊𝚝/𝗳𝗹𝗼𝗮𝘁 ∨ 𝗱𝗼𝘂𝗯𝗹𝗲/𝚍𝚘𝚞𝚋𝚕𝚎 to integer conversion in the C language is 
  𝘛𝘳𝘶𝘯𝘤𝘢𝘵𝘦. (E.𝘨 also consider replacing 'Add License' with Jazzmaster bold=abstractions, 
  keyword, changed, tested, ...) */

/* template <typename T> struct LeftclosedInterval { T closedBeginning; T openEnd; };
template <typename T> struct ClosedInterval { T closedBeginning; T closedEnd; }; */

namespace Naturals {
   constexpr auto degreesPerRadian = 57.296; /* 🕛 ∧ asin(√3/2) ∧ acos(0.5) */
   constexpr auto π² = 9.86960440108935861883449099987615113531369940724079062641334; /* 😐: ≅ 10 */
   constexpr auto π²div6 = 1.6449340668482264364724151666460251892189499012067984377; /* 😐: ≅ ∑ 1/k², k ∈ [1…∞) */
/* constexpr auto √5 = 2.23606797749978969640917366873127623544061835961152572427089; 🕛: 𝜖 = 10³ @w N[Sqrt[5], 70]
   constexpr auto πᵉ = 22.45915771836104547342715220454373502758931513399669224920;
   constexpr auto φ² = 2.618033988749894848204586834365638117720309179805762862135; 😐: ≅ φ¹ + φ⁰ */
}

#pragma mark - Directions

typedef __builtin_uint_t Positano; enum : Positano { /* Movements on an 
   approximately spherical surface while responding to 𝑜𝑛𝑒 gravitational field. */
  PositanoUpLeftwards     = 0b00000001, PositanoLeftToRight = 0b00000010,
  PositanoDownLeftwards   = 0b00000100, PositanoRightToLeft = 0b00001000,
  PositanoDownRighttwards = 0b00010000, PositanoTopToBottom = 0b00100000,
  PositanoUpRighttwards   = 0b01000000, PositanoBottomToTop = 0b10000000 };

typedef __builtin_uint_t Turtle; enum : Turtle {
  TurtleLeft = 0b00000001, TurtleRight = 0b00000010, TurtleForward = 0b00000011, 
  TurtleReverse = 0b00000100, TurtleUp = 0b00000101, TurtleDown = 0b00000110,
  TurtleAccelerate = 0b00001000, TurtleDeccelerate = 0b00010000 };

typedef __builtin_uint_t Strider; enum : Strider { /* ☜😐: 🔅 */
  StriderPort = 0b00000001, StriderStarboard = 0b00000010, 
  StriderForward = 0b00000101, StriderAdrift = 0b00000110, 
  StriderAnchored = 0b00000100 };

typedef __builtin_uint_t RelationalStrider; enum : RelationalStrider { 
  RelationalStriderAbaft = 0b00000001, RelationalStriderLeeward = 0b00000010,
        RelationalStriderAboard = 0b00000011,
  RelationalStriderAthwartships = 0b00000100,
    RelationalStriderBelowdecks = 0b00000101,
     RelationalStriderAmidships = 0b00000110,
      RelationalStriderOutboard = 0b00000111,
          RelationalStriderAlee = 0b000001000 };

typedef __builtin_uint_t Manhattan; enum : Manhattan {
  ManhattanLeftToRight = 0b0001, ManhattanRightToLeft = 0b0010,
  ManhattanTopToBottom = 0b0100, ManhattanBottomToTop = 0b1000 };

#include <Additions/Additions.h>
#include <Additions/Esoterics.h>

/*  The correlative- and subtractive-relative duals: */
typedef simd_tᵦ simd_tᵦʳ ; typedef simd_tᵦ simd_tᵦ⁺ʳ;

/* template <typename E>
simd_tᵦ
Actual(
  typename Fifo<E>::Flavour f,
  Fifo<E> * twofifos,
  simd_tᵦ⁺ʳ t
) //  A․𝘬․a 'Bilinear interpolation'.
{ float⁴ xᵢ, xᵢ₋₁;
    fifo[0].retrospect(0, f, xᵢ.doubles[0], xᵢ₋₁.doubles[0]);
    fifo[1].retrospect(0, f, xᵢ.doubles[1], xᵢ₋₁.doubles[1]);
    return mutual(xᵢ₋₁, xᵢ, t);
} */

/*  The correlative- and subtractive-relative dual-pairs: (E․𝘨 x, y and 
  the 'shadow x and y'.) */

typedef simd_t simd_tʳ; typedef simd_t simd_t⁺ʳ;

Rasterized2d Rasterize(Cartesian2d &c, Opt<Cartesian2d> &prevOpt);

struct Visual { simd_t⁺ʳ 𝑥, 𝑢₂, 𝑣₁; }; /* 0 — 1.625 V, 
 Visual ⌏, Visual ⌎ , Visual ⌍ ll, Visual ⌌ lr */

union Cartesian2d² { simd_t simd; Cartesian2d 𝟸[2]; };

#include <Additions/fold/interval.hpp>
#include <Additions/fold/normal.hpp>
#include <Additions/fold/cyclicity.hpp>

/* 2𝜋 rad = 360 deg ⟷ 1 rad = 360/(2𝜋) deg */
MACRO double ˚2ᴿ(double 𝑑𝑒𝑔) { return (Naturals::π/180)*𝑑𝑒𝑔; }
MACRO double ᴿ2˚(double 𝑟𝑎𝑑) { return (180/Naturals::π)*𝑟𝑎𝑑; }
/* 400 𝑛𝑦𝑔𝑟𝑎𝑑 = 2𝜋 radians; 1 𝚐𝚛𝚊𝚍 = 9/10˚ */

typedef double (^Computational)(double x); /* Not auto A = ^(int n, double z) { … */

MACRO Computational Chebyshevᵀ(int n) {
   switch (n) {
     case 0: return ^(double x) { return 0.0; };
     case 1: return ^(double x) { return x; };
     default: return Block_copy(^(double x) { return 2*x*Chebyshevᵀ(n-1)(x) -
        Chebyshevᵀ(n-2)(x); }); /* 1998 to 9;th of april 2019, 10:10. */
    }
}

/* 𝖫․ 𝖤𝗎𝗅𝖾𝗋: '…𝘯𝘦𝘪𝘵𝘩𝘦𝘳 𝘨𝘳𝘦𝘢𝘵𝘦𝘳 𝘵𝘩𝘢𝘯 𝘻𝘦𝘳𝘰, 𝘯𝘰𝘳 𝑙𝑒𝑠𝑠 𝑡ℎ𝑎𝑛 𝘻𝘦𝘳𝘰, 𝘯𝘰𝘳 𝑒𝑞𝑢𝑎𝑙 𝑡𝑜 𝘻𝘦𝘳𝘰.' */
#include <Additional/complex.hpp>

MACRO void Presentᴿ(Utf8Terminal &term, complex 𝑧) {
  Present(term, Re(𝑧)); term << ", 𝒊"; Present(term, Im(𝑧)); }
MACRO void Presentᶿ(Utf8Terminal &term, complex 𝑧) {
  Present(term, abs(𝑧)); term << ", ∡"; Present(term, arg(𝑧)); }

typedef double (^Computatium)(); typedef double (^Computational)(double x);
typedef maxprec (^Computational³⁵ᵈ)(maxprec x₁, maxprec x₂, maxprec x₃, maxprec x₄);

/* ... */

#include <Additions/Fossilate.h>

#endif /* ∎ 🥽 */

