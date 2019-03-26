/* 💸.hpp – A signbit followed by 63 bits where decimal point 
  is in seven figures. */

union Q567 { uint64_t bits; int64_t frac; };
MACRO float /* double */ Q567ToFloat(Q567 q) { return float(q.frac)/128.0; }
MACRO Q567 FloatToQ567(float x) { return Q567 { .frac = int64_t(x*128.0) }; }
inline Q567 operator "" _💵(long double x) { return FloatToQ567(x); } /* Literal-monetary indication is Q567 x = 2.01_💵. */
MACRO void Present(Utf8Terminal &term, Q567 q) { Present(term, (double)Q567ToFloat(q)); }
auto 🥈 MAX_Q567 = Q567 { .bits=0x7FFFFFFFffffffff }, /* 2⁵⁵-1 + ∑ 2⁻ᵏ, where 1 ≤ k < 8 */
  MIN_Q567 = Q567 { .bits=0x8000000000000000 }; /* -2⁻⁵⁵ */
constexpr maxprec Q567_EPS1 = 1.0078125; /* 1+2⁻⁷ */
/* 0x7FFFFFFFf_fffffff */
