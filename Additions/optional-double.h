/*
 *  optional-double.h to Twinbeam with the Ieee754 'double' alt. 'float' type.
 *  C++20 to clang to x86_64 and Mips.
 *  clang version 11.0.1 to Mips.
 *  Xcode Version 10.2.1 (10E1001) to x86_64.
 */

void CastConstantToText(double value, 
  void (^digits)(int neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s), 
  void (^zero)(int neg), void (^inf)(int neg), void (^nan)()
); /* ⬷ a․𝘬․a 'CastCoefficientToText'. */

/* The next smallest value after '1'. */
#define DOUBLE_EPS1  1.00000000000000011102230246251565 /* 1+2⁻⁵³ */
#define FLOAT_EPS1   1.0000000119                       /* 1+2⁻²³ …possibly 2⁻²⁴. */
#define HALF_EPS1    1.0009765625                       /* 1+2⁻¹⁰ …maybe 2⁻¹¹. */
#define Q31_EPS1     1.0000000004656612873077392578125  /* 1+2⁻³¹ */
#define Q15_EPS1     1.000030517578125                  /* 1+2⁻¹⁵ */
#define Q7_EPS1      1.0078125                          /* 1+2⁻⁷ */
#define X86FP80_EPS1 1.0000000000000000000542101        /* 1+2⁻⁶⁴ */
#define BINARY128_EPS1 1.000000000000000000000000000000000096296 /* ⬷ Ieee754-2008 
and the occational 'long double', __float128 pair a․𝘬․a decimal128/binary128, 
𝜀b₂≈log₁₀(2¹¹³)≈34.16 decimal digits; BSM = __int256_t. */

/*
                                                                             
*** 'Big-endian Ieee 754 Base-2 double with double-Zero (-1)ˢ(1+m*2⁻⁵²)×2ˣ⁻¹⁰²³ ***
                                                                             
Binary64_SGN x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|
            |␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Sign bit               
                                                                             
Binary64_EXP ␣xxx|xxxx|xxxx|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣³²|
            |␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Signed exponent -1023 to 1024 (biased, not 2's-complement and 11 bits wide)
                                                                             
Binary64_MAN ␣␣␣␣|␣␣␣␣|␣␣␣␣|xxxx|xxxx|xxxx|xxxx|xxxx|
            |xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx| Fraction/mantissa/significand (52 bits)
                                                                             
*** Ieee 754 base-2 single with double-zero (-1)ˢ(1+m*2⁻²³)×2ˣ⁻¹²⁷ ***
                                                                             
Binary32_SGN x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Sign bit
Binary32_EXP ␣xxx|xxxx|x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Signed exponent -126 to 127 (biased, not 2's-complement and 8-bits wide)
Binary32_MAN ␣␣␣␣|␣␣␣␣|␣xxx|xxxx|xxxx|xxxx|xxxx|xxxx| Fraction/mantissa/significand (23 bits)
                                                                             
*/

#define IEEE754BASE2_64BIT_PZERO  0x0000000000000000L /* ⬷ big endian */
#define IEEE754BASE2_64BIT_NZERO  0x8000000000000000L 
#define IEEE754BASE2_64BIT_SNAN₂  0x7FF0000000000002L /* signalling */
#define IEEE754BASE2_64BIT_PINF   0x7FF0000000000000L /* positive */
#define IEEE754BASE2_64BIT_NINF   0xFFF0000000000000L /* negative */
#define IEEE754BASE2_64BIT_QNAN₂  0x7ff8000000000002L /* quiet */
#define IEEE754BASE2_32BIT_QNAN₂  0x7FC00002 /* ⬷ see chapter~50, 12.2.2.2.1 for additional text. */

MACRO int is₋pairwise₋inf(double x, double y, int * bipolar) {
  octa o₁,o₂; o₁.base﹟𝟸=x, o₂.base﹟𝟸=y; *bipolar=1;
  uint64_t P=IEEE754BASE2_64BIT_PINF, N=IEEE754BASE2_64BIT_NINF;
  if (o₁.bits == N && o₂.bits == P) { return true; }
  if (o₁.bits == P && o₂.bits == N) { return true; }
  *bipolar=0;
  if (o₁.bits == N && o₂.bits == N) { return true; }
  if (o₁.bits == P && o₂.bits == P) { return true; }
  return false;
}

MACRO int isnan(double x) { octa o; o.base﹟𝟸=x; return (o.binary64.mantissah != 0 || 
 o.binary64.mantissal != 0) && o.binary64.exponent == 0x7ff; }  /* ⬷ exponent 
 is eleven bits. Sign not relevant; and Ieee 754-2008: MSB is 'is_quiet'. */

MACRO int iszero(double x) { octa o; o.base﹟𝟸=x; return o.bits == 
 IEEE754BASE2_64BIT_PZERO || o.bits == IEEE754BASE2_64BIT_NZERO; }

MACRO int isnegone(double x) { octa o; o.base﹟𝟸=x; 
  return o.binary64.sign && o.binary64.exponent == 0b1111111 && 
    o.binary64.mantissal == 0 && o.binary64.mantissah == 0;
} /* ⬷ see also 'isone'. */

MACRO double abs64d₁(double x) { return x < +0.0 ? -x : x; }
MACRO double abs64d₂(double x) { return __builtin_fabs(x); }

MACRO double __builtin_qnan() { return __builtin_nan(""); }

#pragma recto  😐🎲

enum GaussianApproximate { AbramowitzStegun, ZogheibHlynka };
void Gaussian(enum GaussianApproximate approximate, double *out);
void Uniform(double *out); /* *out ∈ [0, 1) */

#pragma recto in cases of 'high-precision Ieee754'

typedef long double float128; /* 2⁻¹⁶³⁸² ≈ 
  3.3621 × 10⁻⁴⁹³² - 2⁻¹⁶³⁸⁴ − 2⁻¹⁶²⁷¹ ≈ 1.1897 × 10⁻⁴⁹³² */
#if defined __x86_64__ /* ¬`x86_fp80` ∧ `ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾` */
typedef float128 maxprec;
#elif defined __mips__
typedef double maxprec;
#endif

#pragma recto Gauss K𝑒𝑡𝑡𝑒𝑛𝑏𝑟𝑢𝑐ℎ

/* MACRO void Khinchin(double * A, int count, double &acc) { for (int i=count-1;
  i >= 0; i--) { acc = 1/(A[i] + acc); } } */
/* MACRO void Khinchin(double (^A)(double k), double (^B)(double k), int count,
  double &acc) { for (int i=count-1; i >= 1; i--) { acc = A(i)/(B(i) + acc); } } */
MACRO void Khinchin(double z, double (^A)(double k, double z), double (^B)(
  double k, double z), int count, double * acc) { for (int i=count-1; i >= 1;
  i--) { *acc = A(i,z)/(B(i,z) + *acc); } }
/* auto A𝜋 = ^(double k) { return (2*k-1)*(2*k-1); }, B𝜋 = ^(double k) { return 6.0; }; */
/* To retrieve coefficients for continued fractions, see Hardy and Wright. */

MACRO int
Similar(
  double x, double y, double eps
)
{ int bipolar; 
   if (isnan(x) && isnan(y)) { return true; }
   if (is₋pairwise₋inf(x,y,&bipolar) && !bipolar) { return true; }
   if (isnegone(x) && isnegone(y)) { return true; }
   if (iszero(x) && iszero(y)) { return true; }
   double diff = abs64d₁(x-y);
   return diff < eps;
}

