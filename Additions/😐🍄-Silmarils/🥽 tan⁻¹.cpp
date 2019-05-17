/*  tan⁻¹.cpp | 🗺 — cot⁻¹ u = tan⁻¹ 1/u */

#include <Twinbeam.h>

/* Compile with xcrun clang @ccargs_macos -o tan⁻¹ '🥽 tan⁻¹.cpp' */

MACRO void Khinchin(double z, double (^A)(double k, double z), double (^B)(
  double k, double z), int count, double &acc) { for (int i=count-1; i >= 1;
  i--) { acc = A(i,z)/(B(i,z) + acc); } }
  
double tan⁻¹(double x)
{
    auto A = ^(double k, double z) { return k == 1 ? z : (k-1)*(k-1)*z*z; };
    auto B = ^(double k, double z) { return 2*k - 1; };
    double acc=0.0; Khinchin(x, A, B, 25, acc);
    return acc;
}

double cot⁻¹(double x) {
  auto A = ^(double k, double z) { return k == 1 ? 1 : (k-1)*(k-1); };
  auto B = ^(double k, double z) { return (2*k - 1)*z; };
  double acc=0.0; Khinchin(x, A, B, 25, acc);
  return acc;
}

#ifdef __mips__
#elif defined __x86_64__
typedef __m128d simd_tᵦ;
#define simd_initᵦ _mm_set1_pd
#define __builtin_simd_sqrtᵦ _mm_sqrt_pd
MACRO double simd_scalarᵦ(simd_tᵦ 𝒙) {
  union Shim { long long bits; double base₂; };
  Shim 𝒙₂ { .bits = _mm_extract_epi64(𝒙, 0) };
  return 𝒙₂.base₂; }
MACRO double sqrt(double x) { simd_tᵦ 𝒙 = simd_initᵦ(x), 𝒚 = __builtin_simd_sqrtᵦ(𝒙); return simd_scalarᵦ(𝒚); }
#endif

double
sequential_arctan(
  double x
)
{ // atan x: a₀ = 1/√(1+x²), b₀=1, aᵢ+1=(aᵢ+bᵢ)/2, bᵢ+1=√(aᵢ+1*bᵢ)
  double a = 1/sqrt(1+x*x), b=1;
  for (int i=0; i < 25; i++) { a=0.5*(a+b); b=sqrt(a*b); }
  return x/(a*sqrt(1+x*x));
}

double
atanᵖᵃᵈᵉ(double x)
{ /* For 4-5 digits arctan, try Padé: x + 7/9 x^3 + 64/945 x^5 / (1 + 10/9 x^2 + 5/21 x^4) */
    double 🥈 sn = 7/9, sfnff=64/945, tn=10/9, ftq=5/21;
    double num=x*(1 + x*(sn*x + sfnff*x*x*x)), den=1+x*x*(tn + ftq*x*x);
    return num/den;
}

#pragma mark - Main entry point

int
main(
  int argc,
  const char * argv[]
)
{
    double 🥈 π = 3.1415926535897932384626433832795028841971693993751058209749, 
      πdiv2 = π/2, πdiv4 = π/4;
    
    printf("   0 tan⁻¹ cot⁻¹ seq pade %f %f %f %f\n", tan⁻¹(0),      cot⁻¹(0),      sequential_arctan(0),      atanᵖᵃᵈᵉ(0));
    printf(" π/2 tan⁻¹ cot⁻¹ seq pade %f %f %f %f\n", tan⁻¹(πdiv2),  cot⁻¹(πdiv2),  sequential_arctan(πdiv2),  atanᵖᵃᵈᵉ(πdiv2));
    printf("-π/2 tan⁻¹ cot⁻¹ seq pade %f %f %f %f\n", tan⁻¹(-πdiv2), cot⁻¹(-πdiv2), sequential_arctan(-πdiv2), atanᵖᵃᵈᵉ(-πdiv2));
    printf(" π/4 tan⁻¹ cot⁻¹ seq pade %f %f %f %f\n", tan⁻¹(πdiv4),  cot⁻¹(πdiv4),  sequential_arctan(πdiv4),  atanᵖᵃᵈᵉ(πdiv4));
    printf("-π/4 tan⁻¹ cot⁻¹ seq pade %f %f %f %f\n", tan⁻¹(-πdiv4), cot⁻¹(-πdiv4), sequential_arctan(-πdiv4), atanᵖᵃᵈᵉ(-πdiv4));
    
    double y₁, y₂, y₃;
    MEASURE_START(blocks)
      y₁ = tan⁻¹(-πdiv4);
    MEASURE_END(blocks)
    MEASURE_START(simd)
      y₂ = sequential_arctan(-πdiv4);
    MEASURE_END(simd)
    MEASURE_START(pade)
      y₃ = atanᵖᵃᵈᵉ(-πdiv4);
    MEASURE_END(pade)
    
    printf("Sum is %f\n", y₁+y₂+y₃);
    
    return 0;
}