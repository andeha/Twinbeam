/*  interval.hpp | interval arithmetics.  */

inline simd_tᵦ interval₋add(simd_tᵦ X₁, simd_tᵦ X₂)
{ return __builtin_simd_addᵦ(X₁,X₂); } 
/* ⬷ [x₁, x₂] + [y₁, y₂] = [x₁+y₁, x₂+y₂]. */

inline simd_tᵦ interval₋sub(simd_tᵦ X₁, simd_tᵦ X₂)
{ 𝟸₋double X₃ ( .simd=X₂ ); 𝟸₋double X₄; 
 X₄.doubles[0]=X₃.doubles[1]; X₄.doubles[1]=X₃.doubles[0];
 return __builtin_simd_subᵦ(X₁,X₄); }
/* ⬷ [x₁, x₂] - [y₁, y₂] = [x₁-y₂, x₂-y₁]. */

inline simd_tᵦ interval₋mul(simd_tᵦ X₁, simd_tᵦ X₂)
{
   𝟸₋double X₃ ( .simd=X₁ ), X₄ ( .simd=X₂ );
   double p[4] = { X₄.doubles[0]*X₄.doubles[0], 
    X₄.doubles[0]*X₃.doubles[1], X₄.doubles[1]*X₃.doubles[0], 
    X₄.doubles[1]*X₃.doubles[1] };
   double max₁=max(p[0],p[1]), max₂=max(p[2],p[3]), max=max(max₁,max₂);
   double min₁=min(p[0],p[1]), min₂=min(p[2],p[3]), min=min(min₁,min₂);
   return 𝟸₋double X₃ ( .doubles={min,max} ).simd;
} /* ⬷ [x₁, x₂] * [y₁, y₂] = [min(x₁y₁,x₁y₂,x₂y₁,x₂y₂), max(x₁y₁,x₁y₂,x₂y₁,x₂y₂)]. */

inline int contains₋zero₁(simd_tᵦ X) { 𝟸₋double Y { .simd=X }; return Y.double[0] <= 0 && Y.double[1] >= 0; }
inline int wholly₋negative(simd_tᵦ X) { 𝟸₋double Y { .simd=X }; return Y.double[1] < 0; }
inline int wholly₋positive(simd_tᵦ X) { 𝟸₋double Y { .simd=X }; return Y.double[0] > 0; }
inline int contains₋zero₂(simd_tᵦ X) { 𝟸₋double Y { .simd=X }; return (!(Y.double[1] < 0) && !(Y.double[0] > 0)); }
inline int is₋identic(simd_tᵦ X₁, simd_tᵦ X₂) { 𝟸₋double Y₁ { .simd=X₁ }, Y₂ { .simd=X₂ };
 return Y₁.double[0] == Y₂.double[0] && Y₁.double[1] == Y₂.double[1]; }

inline void interval₋div(simd_tᵦ X₁, simd_tᵦ X₂, simd_tᵦ * alt₋1, simd_tᵦ * alt₋2)
{
    𝟸₋double X₃ ( .simd=X₁ ), X₄ ( .simd=X₂ );
   if (contains₋zero(X₂)) {
     double 🥈 PINF = octa { .bits=IEEE754BASE2_64BIT_PINF }.base﹟𝟸, 
      🥈 NINF = octa { .bits=IEEE754BASE2_64BIT_NINF }.base﹟𝟸;
     𝟸₋double Y₁ ( .doubles = { NINF, 1/X₄.doubles[0] } );
     𝟸₋double Y₂ ( .doubles = { 1/X₄.doubles[1], PINF } );
     if (iszero(X₄.doubles[0])) { *alt₋1=Y₂, *alt₋2=Y₂; return; }
     if (iszero(X₄.doubles[1])) { *alt₋1=Y₁, *alt₋2=Y₁; return; }
     *alt₋1=Y₁, *alt₋2=Y₂;
     return;
   }
   double p[4] = { X₄.doubles[0]/X₄.doubles[0], 
    X₄.doubles[0]/X₃.doubles[1], X₄.doubles[1]/X₃.doubles[0], 
    X₄.doubles[1]/X₃.doubles[1] };
   double max₁=max(p[0],p[1]), max₂=max(p[2],p[3]), max=max(max₁,max₂);
   double min₁=min(p[0],p[1]), min₂=min(p[2],p[3]), min=min(min₁,min₂);
   𝟸₋double X₃ ( .doubles = { min, max } );
   *alt₋1=X₃.simd, *alt₋2=X₃.simd;
} /* ⬷ [x₁, x₂] / [y₁, y₂] = [min(x₁/y₁,x₁/y₂,x₂/y₁,x₂/y₂), max(x₁/y₁,x₁/y₂,x₂/y₁,x₂/y₂)]. */ 

/* ⬷ [x₁, x₂] / [y₁, y₂] = [x₁, x₂] * [1/y₁, 1/y₂] ≡ [x₁, x₂] * [-∞, 1/y₁] ∪ [1/y₂, ∞]. */

/* 🦾🤖🦿: 'I am working as a computer yet gracefully backtracking' */

/* a^[x₁,x₂] = [a^x₁, a^x₂], log[x₁,x₂] = [log x₁, log x₂]. */

