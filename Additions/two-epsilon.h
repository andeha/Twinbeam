/*  epsilon-two.h | fixpoints and conversion routines. */

#pragma recto fractional fixed point mathematics ∈ [-1,1]

/*  Compute 1/x7FFFFFFF and 1/x8000 and convert the result to base-10. */

union Q31 { uint32_t bits; int32_t frac; };
union Q15 { uint16_t bits; int16_t frac; };
union Q7 { uint8_t bits; int8_t frac; };
/* ⬷ one sign bit followed by the fractionals. */

/* Short temporal-quantitative indication is Q79 x = (1/4+1/8)_♬♫. */
union Q79 { uint16_t bits; int16_t frac; }; /* 0 to ±127.998046875 */

/* Long temporal-quantitative indication is Q1516 x = (1/4+1/8)_♩♬♫. */
union Q1516 { uint32_t bits; int32_t frac; }; /* 0 to ±65535.999969482421875 */

#pragma recto The 'half' (Ieee754-2008, may require compiling with '-mnan=2008')

#ifdef __x86_64__
typedef _Float16 half;
#endif

/*** Ieee 754 base-2 half with double-zero (-1)ˢ(1+m*2⁻¹⁰)×2ˣ⁻¹5 ***
                                                                             
 Binary16_SGN ⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Sign bit
 Binary16_EXP ⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|␣xxx|xx␣␣|␣␣␣␣|␣␣␣␣| Signed ex̳ponent -16 to 16 (biased)
 Binary16_MAN ⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|⌗⌗⌗⌗|␣␣␣␣|␣␣xx|xxxx|xxxx| Fraction/mantissa/significand (10 bits)
                                                                             
 The significand encodes the serie 1 + ∑ k⁻ⁱ where 1 <= k < 11.  (...and not k ∈ [0,9].)
                                                                             
*/

BITMASK (uint32_t) { /* sometime 'half'. */
  Binary16_SGN = 0x8000, /* Sign bit */
  Binary16_EXP = 0b11111<<10, /* Signed exponent -16 to 16 */
  Binary16_MAN = 0x3ff, /* Fraction/mantissa/significand */
};

#define IEEE754BASE2_16BIT_PZERO 0b0000000000000000
#define IEEE754BASE2_16BIT_NZERO 0b1000000000000000
#define IEEE754BASE2_16BIT_ONE   0b0011110000000000
/* IEEE754BASE2_16BIT_SNAN and IEEE754BASE2_16BIT_QNAN n/a. */
#define IEEE754BASE2_16BIT_PINF  0b0111110000000000
#define IEEE754BASE2_16BIT_NINF  0b1111110000000000
#define IEEE754BASE2_16BIT_MAX   0b0111101111111111 /* 𝟲𝟱𝟱𝟬𝟰 (i․𝘦 𝗠𝗔𝗫 when `half` precision.) */
typedef union { /* Encodes values between 2⁻¹⁴ to 2⁻¹⁵ or 3․1×10⁻⁵ to 6․5×10⁴. */
   struct { int8_t lsh; uint8_t msh; } signed_little_endian;
   struct { uint8_t msh; int8_t lsh; } unsigned_big_endian;
   struct {
     unsigned mantissa : 10;
     unsigned exponent :  5;
     unsigned sign     :  1;
   } binary16; /* ⬷ a․𝘬․a `ieee754_2008`. */
   uint16_t bits;
#ifdef __x86_64__
   half loc;
#endif
} pythagorean_double;

#ifdef __mips__
typedef pythagorean_double half;
#endif

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, half x) {
#ifdef __x86_64__
  pythagorean_double y { .loc=x };
#elif defined __mips__
  pythagorean_double y=x;
#endif
  octa y₂ { .binary64={ 0, uint32_t(y.binary16.mantissa)<<10, 
    y.binary16.exponent, y.binary16.sign } };
  Present(term, y₂.base﹟𝟸); return term;
}

#ifdef __mips__
MACRO half FloatToHalf(float x) { tetra x₂ { .base﹟𝟸=x }; 
  pythagorean_double y { .binary16={ uint32_t(x₂.binary32.mantissa>>13), 
  uint32_t(x₂.binary32.exponent>>3), x₂.binary32.sign } }; return y; }
MACRO float HalfToFloat(half h) { tetra y { .binary32={ uint32_t(
  h.binary16.mantissa)>>13, uint32_t(h.binary16.exponent>>3),
  h.binary16.sign } }; return y.base﹟𝟸; }
/* typedef _Float16 v8f16 __attribute__ ((vector_size(16))); */
#elif defined __x86_64__
half FloatToHalf(float value); float HalfToFloat(half value);
#endif

inline 
void Presentᵧ(Utf8Terminal &term, half val) {
#ifdef __mips__
  uint32_t bits = val.bits;
#elif defined __x86_64__
  uint32_t bits = pythagorean_double { .loc=val }.bits;
#endif
  extern AnnotatedRegister AR_Binary16;
  Present(term, AR_Binary16, bits, true);
}

/*
  
 H₁: The symbol `__fp16` is used for computation and storage.
 H₂: The symbol `_Float16` always internally use `__fp16` for storage.
 E․𝘨 `half x[] = { 1.2, 3.0, 3.e4 };` and maybe not
  inline half operator "" _h(float x) { return FloatToHalf(x); }
  
 */

/* The type 'bfloat' is 1 bit sign, 8 bits exponent and 7 bits significand. */

