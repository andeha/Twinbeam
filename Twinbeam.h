/*  twinbeam.h | terminal fun with mathematical functions. */

#if defined __SSE2__
#include "/Library/Developer/CommandLineTools/usr/lib/clang/16.0.0/include/emmintrin.h"
#include "/Library/Developer/CommandLineTools/usr/lib/clang/16.0.0/include/xmmintrin.h"
#include "/Library/Developer/CommandLineTools/usr/lib/clang/16.0.0/include/immintrin.h"
#elif defined __ARM_NEON__
#include "/Library/Developer/CommandLineTools/usr/lib/clang/16.0.0/include/arm_acle.h"
#include "/Library/Developer/CommandLineTools/usr/lib/clang/16.0.0/include/arm_neon.h"
#endif
#include "twinbeam-inner.h"
#include "Source/simd-multiple.h"

simd_tᵦ tan(simd_tᵦ x, int arc) ⓣ;
Sequent tan(Sequent, int arc) ⓣ;

simd_tᵦ tanh(simd_tᵦ x, int arc) ⓣ;
Sequent tanh(Sequent x, int arc) ⓣ;

simd_tᵦ logₑ(simd_tᵦ x) ⓣ;
Sequent logₑ(Sequent x) ⓣ;

simd_tᵦ exponential(simd_tᵦ x) ⓣ;
Sequent exponential(Sequent) ⓣ;

simd_tᵦ sin(simd_tᵦ x, int arc) ⓣ;
Sequent sin(Sequent x, int arc) ⓣ;
simd_tᵦ cos(simd_tᵦ x, int arc) ⓣ;
Sequent cos(Sequent x, int arc) ⓣ;
simd_tᵦ tan(simd_tᵦ x, int arc) ⓣ;
Sequent tan(Sequent x, int arc) ⓣ;
simd_tᵦ sqrt(simd_tᵦ x, int invert, simd_tᵦ * NoNthRootOrΨΛΩ) ⓣ;
Sequent sqrt(Sequent x, int invert, Sequent * NoNthRootOrΨΛΩ) ⓣ;
simd_tᵦ power(simd_tᵦ x, int y₋equals₋10, int and₋inverted, simd_tᵦ y) ⓣ;
Sequent power(Sequent x, int y₋equals₋10, int and₋inverted, Sequent y) ⓣ;
simd_tᵦ reciproc₋interval(simd_tᵦ x, int no₋exponential, int ₋and₋again₋inverted);
Sequent reciproc_sequent(Sequent x, int no₋exponential, int ₋and₋again₋inverted);

struct mathart
{
  Sequent operation₋cordic[64];
  double machine₋cordic[64];
};

extern struct mathart Mathart₋segment;

void Init_math();

