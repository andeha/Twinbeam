/* Harmonic.hpp - Flavored Rationals. */

/* International Jazz-festival day: 'Sixth of June'. */

/* ⟪ 1, ♭2/♯1, 2, … ⟫ */

/* ⟪ 1, 2, 3, 4, 5, 6, ♭7, 8/1, 9/2, 10/3, 11/4, 12/5, 13/6 ⟫ */

#include <Additions/Fractions.hpp>

#pragma mark - Exercise: Tuning G-string

enum Intervalᴴ { quinte, terz, quarte, sexte, septime, oktave, sekunde, dezime };
enum Alterificate { flat, natural, sharp };
enum ArtisticDirectionᴴ { }; /* Harmonically speaking, actually. */

namespace ᴴInterval { /* Compute 𝞮 when 88 keys and Q4.12 compared to when in `x86_fp80`. */
constexpr auto purePerfectFifth        = Tuple<float, float>(0.75000, 1.50000); /* 3/2=1+1/2, 3/4 */
constexpr auto consonantMajorthird     = Tuple<float, float>(0.62500, 1.25000); /* 5/4=1+1/4, 5/8 */
constexpr auto compactPerfectfourth    = Tuple<float, float>(1.33333, 0.66667); /* 4/3=1+1/3, 2/3 */
constexpr auto contemplativeMajorsixth = Tuple<float, float>(1.66666, 0.83333); /* 5/3=1+2/3, 5/6 */
constexpr auto wholestep               = Tuple<float, float>(1.12500, 0.56250); /* 9/8=1+1/8, 9/16 */
constexpr auto halfstep                = Tuple<float, float>(1.06667, 0.53333); /* 16/15=1+1/15, 16/30 */
constexpr auto leadingMinorThird       = Tuple<float, float>(1.20000, 0.60000); /* 6/5=1+1/5, 3/5 */
constexpr auto augmentedFourth         = Tuple<float, float>(1.40625, 0.70313); /* 45/32=1+13/32, 45/64 */
constexpr auto octave                  = Tuple<float, float>(2.00000, 0.50000); /* 2=😐+😐/😐, 1/2 */
constexpr auto itchysMinorsixth        = Tuple<float, float>(1.60000, 0.80000); /* 8/5=1+3/5 4/5 */
constexpr auto sizzlingMinorseventh    = Tuple<float, float>(1.80000, 0.90000); /* 9/5=1+4/5, 9/10 */
constexpr auto concernedMajorseventh   = Tuple<float, float>(1.87500, 0.93750); /* 15/8=1+7/8, 15/16 */
/* Ptolemy: 1/1 16/15 9/8 6/5 5/4 4/3 45/32 3/2 8/5 5/3 9/5 15/8 2/1 */
/* Scandianvian delight: ⟪ 1 ♯2 ♭3, 4, 5, ♭6, 7 ⟫ */
/* constexpr auto scandinavianseventh = Tuple<float, float>(19/17, 17/34); */
}

/* Instrumentally_ */ FOCAL
inline 
Tuple<float, float>
Interval(
  Intervalᴴ i,
  Alterificate a,
  float cpsOrHz /* unison */,
  float 𝞮
)
{
    Tuple<float, float> 🥈ᵢ resolvation = {
      { ᴴInterval::augmentedFourth, ᴴInterval::purePerfectFifth, ᴴInterval::itchysMinorsixth },
      { ᴴInterval::leadingMinorThird, ᴴInterval::consonantMajorthird, ᴴInterval::compactPerfectfourth },
      { ᴴInterval::consonantMajorthird, ᴴInterval::compactPerfectfourth, ᴴInterval::augmentedFourth },
      { ᴴInterval::itchysMinorsixth, ᴴInterval::contemplativeMajorsixth, ᴴInterval::sizzlingMinorseventh /* 🌶⤣ */ },
      { ᴴInterval::sizzlingMinorseventh, ᴴInterval::concernedMajorseventh, ᴴInterval::octave },
      { ᴴInterval::concernedMajorseventh, ᴴInterval::octave, ᴴInterval::halfstep },
      { ᴴInterval::halfstep, ᴴInterval::wholestep, ᴴInterval::leadingMinorThird },
      { (2+𝞮)*ᴴInterval::itchysMinorsixth, (2+𝞮)*ᴴInterval::contemplativeMajorsixth, (2+𝞮)*ᴴInterval::sizzlingMinorseventh }
    };
    return resolvation[(int)i][((int)a)]*cpsOrHz;
}

inline float AngularFrequency(float cpsOrHz) { return 2*Naturals::π*cpsOrHz; } /* 𝜔 = 2*π*f [rad/s]. */

Intervalᴴ Flagolett(Intervalᴴ point); /* Do not consider `Abalone`. */

/* 1/(2/3 + 4/5) = (15/22)⁻¹ = 1 + ⁷/₁₅ */
/* 1/(1/3 + 1/5) = (8/15)⁻¹ = (2³/(3*5))⁻¹ = 1 + ⁷/₈ */
/* 𝜑 = ⁷/₈ ∨ ⁷/₁₅ = ⁷/₂³ ∨ ⁷/₃*₂ ⟶ 𝜑₂: Base-3 ∧ Base-2 𝘢․𝘬․𝘢 
    'Sin relative superposition/commutativity and time'. */
/* Geometric approximation: ∑ (1/x)ᵏ = 1, where 1 ≤ k < 12. */
/* ∴ ∵ Consonant */

/* See also FM/AM Carrier and --<Fossilate.h>. */

/*
  
  How `change` and `actuals` are related:
  
 1) Vibrating string: 𝜓(x, t) = 1/2; I․𝘦 'Displacement from equilibrium'.
  
 2) Newtons second law: F = m*a.
  
 3) One-dimensional wave equation: ∂²/∂x² 𝜓(x, t) = k*∂²/∂t² 𝜓(x, t), where k = 𝜌/F(x).
  
 */

/* Compare to λ and f = 1/T. */

#pragma mark - Distorsion

/* See also: 'Pid-regulated clamping'. */

#pragma mark - Interference and Reflections

/*
    ----
    ----  ⬷ ⎲⎳ + compose.
    ----
    ----
    ----
    ----
 */

/* TODO: Reconsider ♮ */

/* Emaj13/D — C♯7 — D — Dsus2 — Gdim7/E */

