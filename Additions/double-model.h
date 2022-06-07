/*  double-model.h | Gordon finished his 80-bit project. */

#if defined __MM__

union β₋simd
{
  Sequenta dbls[2]; Sequenta doubles[2];
};

typedef union β₋simd simd_tᵦ;

union 𝟸₋double
{
  union β₋simd array;
  simd_tᵦ multiple;
};

inline simd_tᵦ simd_initᵦ(double x) { /* ... */ }
inline simd_tᵦ __builtin_simd_addᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) {
 Sequenta l=__builtin_fixpoint_add(𝒙.dbls[0],𝒚.dbls[0]), 
  r=__builtin_fixpoint_add(𝒙.dbls[1],𝒚.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_subᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) {
 Sequenta l=__builtin_fixpoint_sub(𝒙.dbls[0],𝒚.dbls[0]), 
  r=__builtin_fixpoint_sub(𝒙.dbls[1],𝒚.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_mulᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) {
 Sequenta l=__builtin_fixpoint_mul(𝒙.dbls[0],𝒚.dbls[0]), 
  r=__builtin_fixpoint_mul(𝒙.dbls[1],𝒚.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_divᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) {
 Sequenta l=__builtin_fixpoint_div(𝒙.dbls[0],𝒚.dbls[0]), 
  r=__builtin_fixpoint_div(𝒙.dbls[1],𝒚.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_minᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) {
 Sequenta l=__builtin_fixpoint_min(𝒙.dbls[0],𝒚.dbls[0]), 
  r=__builtin_fixpoint_min(𝒙.dbls[1],𝒚.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_maxᵦ(simd_tᵦ 𝒙, simd_tᵦ 𝒚) {
 Sequenta l=__builtin_fixpoint_max(𝒙.dbls[0],𝒚.dbls[0]), 
  r=__builtin_fixpoint_max(𝒙.dbls[1],𝒚.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_sqrtᵦ(simd_tᵦ 𝒙) {
 Sequenta l=__builtin_fixpoint_sqrt(𝒙.dbls[0]), 
  r=__builtin_fixpoint_sqrt(𝒙.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_rsqrtᵦ(simd_tᵦ 𝒙) {
 Sequenta l=__builtin_fixpoint_rsqrt(𝒙.dbls[0]), 
  r=__builtin_fixpoint_rsqrt(𝒙.dbls[1]);
 union β₋simd z = { .dbls={l,r} }; return z; }
inline simd_tᵦ __builtin_simd_rcpᵦ(simd_tᵦ 𝒙) {
 Sequenta l=__builtin_fixpoint_rcp(𝒙.dbls[0]), 
  r=__builtin_fixpoint_rcp(𝒙.dbls[1]);
 union β₋simd z = { .dbls={l.r} }; return z; }
#endif

