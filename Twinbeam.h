/*  twinbeam.h | terminal fun and libTown.a mathematical functions. */

#if defined __SSE2__
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/emmintrin.h"
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/xmmintrin.h"
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/immintrin.h"
#elif defined __NEON__
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/arm_acle.h"
#include "/Library/Developer/CommandLineTools/usr/lib/clang/14.0.3/include/arm_neon.h"
#endif
#include "twinbeam-inner.h"
#include "Additions/model-wide.h"
#include "Source/fifo-slow.h"
#include "Additions/optional-double.h"
#include "Additions/double-model.h"
#include "Additions/simd-multiple.h"
#if defined __cplusplus
#include "Source/after-eight.hpp"
#endif

simd_tᵦ tan(simd_tᵦ x, int arc) ⓣ;
Sequenta tan(Sequenta, int arc) ⓣ;

simd_tᵦ tanh(simd_tᵦ x, int arc) ⓣ;
Sequenta tanh(Sequenta x, int arc) ⓣ;

simd_tᵦ logₑ(simd_tᵦ x) ⓣ;
Sequenta logₑ(Sequenta x) ⓣ;

simd_tᵦ exponential(simd_tᵦ x) ⓣ;
Sequenta exponential(Sequenta) ⓣ;

simd_tᵦ sin(simd_tᵦ x, int arc) ⓣ;
Sequenta sin(Sequenta x, int arc) ⓣ;
simd_tᵦ cos(simd_tᵦ x, int arc) ⓣ;
Sequenta cos(Sequenta x, int arc) ⓣ;
simd_tᵦ tan(simd_tᵦ x, int arc) ⓣ;
Sequenta tan(Sequenta x, int arc) ⓣ;
simd_tᵦ sqrt(simd_tᵦ x, int invert, simd_tᵦ * NoNthRootOrΨΛΩ) ⓣ;
Sequenta sqrt(Sequenta x, int invert, Sequenta * NoNthRootOrΨΛΩ) ⓣ;
simd_tᵦ power(simd_tᵦ x, int y₋equals₋10, int and₋inverted, simd_tᵦ y) ⓣ;
Sequenta power(Sequenta x, int y₋equals₋10, int and₋inverted, Sequenta y) ⓣ;
simd_tᵦ reciproc₋interval(simd_tᵦ x, int no₋exponential, int ₋and₋again₋inverted);
Sequenta reciproc_sequent(Sequenta x, int no₋exponential, int ₋and₋again₋inverted);

struct mathart
{
  Sequenta operation₋cordic[64];
  double machine₋cordic[64];
};

extern struct mathart Mathart₋segment;

void Init_math();

