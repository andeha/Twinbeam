/*  final-muldiv.incl.h | that is what we get. */

#if defined usage₋synthetic₋𝟷𝟸𝟾₋bit₋integer
struct 𝟷𝟸𝟾₋bit₋integer { uint64_t lo; int64_t hi; };
struct 𝟷𝟸𝟾₋bit₋unsigned { uint64_t lo,hi; };
typedef struct 𝟷𝟸𝟾₋bit₋integer __int128_t;
typedef struct 𝟷𝟸𝟾₋bit₋unsigned __uint128_t;

inline int divide(__uint128_t numerator, __uint128_t denominator, __uint128_t * residue, __uint128_t * integer)
{
   return 0;
}

inline int multiply(__uint128_t left, __uint128_t right, __uint128_t * low, __uint128_t * high)
{
   return 0;
}

inline int subtract(__int128_t left, __int128_t right, __int128_t * subtrahend) ⓣ
{
   return 0;
}

inline int subtract(__uint128_t left, __uint128_t right, __uint128_t * subtrahend) ⓣ
{
   return 0;
}

inline int add(__uint128_t left, __uint128_t right, __uint128_t * addend)
{
   return 0;
}

#endif

