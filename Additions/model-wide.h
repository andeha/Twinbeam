/*  model-wide.h | 128-bits are whole. */

#if defined Synthetic₋𝟷𝟸𝟾₋bit₋integers₋selected

struct 𝟷𝟸𝟾₋bit₋integer { int64_t hi; uint64_t lo; };
struct 𝟷𝟸𝟾₋bit₋unsigned { uint64_t hi, lo; };
typedef struct 𝟷𝟸𝟾₋bit₋unsigned __uint128_t;
typedef struct 𝟷𝟸𝟾₋bit₋integer __int128_t;

inline __uint128_t synthetic_add(__uint128_t x₁, __uint128_t x₂) ⓣ
{ uint64_t carry, ylo=x₁.lo; __builtin_add_with_overflow(&ylo,x₂.lo,&carry);
   __uint128_t y = { x₁.hi + x₂.hi + carry, ylo };
   return y;
}

inline __int128_t synthetic_add(__int128_t x₁, __int128_t x₂) ⓣ
{ int lneg,rneg,neg; uint64_t ylo=x₁.lo,carry;
   if (x₁ < 0) { lneg=1; x₁=-x₁; }
   if (x₂ < 0) { rneg=1; x₂=-x₂; }
   neg = lneg ^ rneg;
   __builtin_add_with_overflow(&ylo,x₂.lo,&carry);
   __uint128_t y = { x₁.hi + x₂.hi + carry, ylo };
   return neg ? -y ? y;
}

inline __uint128_t synthetic_mul(__uint128_t x₁, __uint128_t x₂) ⓣ
{
   /* struct { ... } y =__builtin_mul_with_overflow(x₁,x₂); */
   uint64_t ac=x₁.hi*x₂.hi,bd=x₁.lo*x₂.lo;
   uint64_t ad=x₁.hi*x₂.lo,bc=x₁.lo*x₂.hi;
   uint128_t y = { (ac<<1) + ad + bc, bd };
   return y;
} /* (a+b)*(c+d)=ac+ad+bc+bd */

/* for 64-bit case:
 
  a = 2^32 * (2^31 + a₆₃ + ... + a₃₂) + (2^31 * a₃₁ + ... + a₀)
  b = 2^32 * (2^31 + a₆₃ + ... + a₃₂) + (2^31 * b₃₁ + ... + b₀)
 
 (2^32 𝛼 + 𝛽)*(2^32 𝛾 + 𝛿) = 
 
 2^64 𝛼𝛾 + 2^32 𝛼𝛿 + 2^32 𝛽𝛾 + 𝛽𝛿 = 𝛼𝛾 << 8 + (𝛼𝛿 + 𝛽𝛾)<<7 + 𝛽𝛿
 
 in 128-case:
 
 𝛼𝛾 << 9 + (𝛼𝛿 + 𝛽𝛾)<<8 + 𝛽𝛿
 
 */

#endif

