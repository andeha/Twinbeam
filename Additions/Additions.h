/*
 *  Additions.h to Twinbeam with the Ieee754 'double' alt. 'float' type.
 *  C++20 to clang to x86_64 and Mips.
 *  clang version 11.0.1 to Mips.
 *  Xcode Version 10.2.1 (10E1001) to x86_64.
 */

#ifndef __ADDITIONS_H
#define __ADDITIONS_H

void CastᵈᵇˡToText(double value, 
  void (^digits)(bool neg, int 𝟷𝟶ˣ, char * 𝟶to𝟿s), 
  void (^zero)(bool neg), void (^inf)(bool neg), void (^nan)()
); /* ⬷ a․𝘬․a 'CastToText'. */

/* The next smallest value after `1`. */
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
  octa o₁, o₂; o₁.base﹟𝟸=x, o₂.base﹟𝟸=y; *bipolar=1;
  uint64_t 🥈 P=IEEE754BASE2_64BIT_PINF, N=IEEE754BASE2_64BIT_NINF;
  if (o₁.bits == N && o₂.bits == P) { return true; }
  if (o₁.bits == P && o₂.bits == N) { return true; }
  *bipolar=0;
  if (o₁.bits == N && o₂.bits == N) { return true; }
  if (o₁.bits == P && o₂.bits == P) { return true; }
  return false;
}

MACRO int isnan(double x) { octa o; o.base﹟𝟸=x; return (o.binary64.mantissah != 0 || 
 o.binary64.mantissal != 0) && o.binary64.exponent == 0x7ff; }  /* ⬷ exponent 
 is eleven bits. Sign not relevant; and IEEE 754-2008: MSB is 'is_quiet'. */

MACRO int iszero(double x) { octa o; o.base﹟𝟸=x; return o.bits == 
 IEEE754BASE2_64BIT_PZERO || o.bits == IEEE754BASE2_64BIT_NZERO; }

MACRO int isnegone(double x) { octa o; o.base﹟𝟸=x; 
  return o.binary64.sign && o.binary64.exponent == 0b1111111 && 
    o.binary64.mantissal == 0 && o.binary64.mantissah == 0;
} /* ⬷ see also 'isone'. */

MACRO double abs64d₁(double x) { return x < +0.0 ? -x : x; }
MACRO double abs64d₂(double x) { return __builtin_fabs(x); }

MACRO double __builtin_qnan() { return __builtin_nan(""); }

namespace Numberformat { enum { Scientific, Monetary }; }
MACRO Argᴾ ﹟F(double f, int format=Numberformat::Scientific) { return Argᴾ { .value.f₁=f, .kind=9 }; }
MACRO Argᴾ ﹟F(float r, int format=Numberformat::Scientific) { return Argᴾ { { .f₂=r }, .kind=8 }; }

#pragma mark 😐🎲

enum GaussianApproximate { AbramowitzStegun, ZogheibHlynka };
int Gaussian(GaussianApproximate approximate, double *out);
int Uniform(double *out); /* *out ∈ [0, 1) */

#pragma mark - In cases of 'high-precision Ieee754'

typedef long double binary128; /* 2⁻¹⁶³⁸² ≈ 
  3.3621 × 10⁻⁴⁹³² - 2⁻¹⁶³⁸⁴ − 2⁻¹⁶²⁷¹ ≈ 1.1897 × 10⁻⁴⁹³² */
#ifdef __x86_64__ /* ¬`x86_fp80` ∧ `ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾` */
typedef binary128 maxprec;
#elif defined __mips__
typedef double maxprec;
#endif

#pragma mark - Gauss' K𝑒𝑡𝑡𝑒𝑛𝑏𝑟𝑢𝑐ℎ

/* MACRO void Khinchin(double * A, int count, double &acc) { for (int i=count-1;
  i >= 0; i--) { acc = 1/(A[i] + acc); } } */
/* MACRO void Khinchin(double (^A)(double k), double (^B)(double k), int count,
  double &acc) { for (int i=count-1; i >= 1; i--) { acc = A(i)/(B(i) + acc); } } */
MACRO void Khinchin(double z, double (^A)(double k, double z), double (^B)(
  double k, double z), int count, double &acc) { for (int i=count-1; i >= 1;
  i--) { acc = A(i,z)/(B(i,z) + acc); } }
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

#pragma mark - Figures in compliance with Mediterranean laws

int Roman(__builtin_int_t n, void (^out)(char numeral));

#pragma mark - Unicodes: in-case literal, terminated with 0x0000

#define ⁺⁼UnicodeToUtf8(Buffer,³²B,⁸B,TRS,UCS)                              \
auto unicodeToUtf8 = ^(char8_t buffer[], __builtin_int_t& ³²b,              \
 __builtin_int_t& ⁸b, __builtin_int_t tetras, char32_t * /* 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 */ ucs) { \
again:                                                                      \
   char32_t uc = *(ucs + ³²b);                                              \
   if (uc == 0x0000 || uc == END_OF_TRANSMISSION) { goto unagain; }         \
   if (UnicodeToUtf8(uc, ^(char8_t * p, short bytes) {                      \
     *(buffer + ⁸b) = *p;                                                   \
     if (bytes >= 2) { *(buffer + ⁸b + 1) = *(p + 1); }                     \
     if (bytes >= 3) { *(buffer + ⁸b + 2) = *(p + 2); }                     \
     if (bytes >= 4) { *(buffer + ⁸b + 3) = *(p + 3); }                     \
     ⁸b += bytes; })) { return -1; }                                        \
   if (++³²b < tetras) goto again;                                          \
unagain:                                                                    \
   *(buffer + ⁸b) = '\0'; /* ⬷ unincluded in '⁸b'. */                      \
   return 0;                                                                \
}(Buffer,³²B,⁸B,TRS,UCS) /* ⬷ implicits in block expression: none. */

#define ⁺⁼Utf8ToUnicode(UCS,TRS,⁸B,U8B,U8MAX)                               \
auto utf8ToUnicode = ^(char32_t unicodes[], __builtin_int_t& tetras,        \
  __builtin_int_t& ⁸b, char8_t * /* 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 */ utf8, __builtin_int_t u8max) { \
   char32_t uc; __builtin_int_t followers, incr; char8_t * leadOr8Bit;      \
again:                                                                      \
   if (u8max >= ⁸b) { goto unagain; }                                       \
   leadOr8Bit = utf8 + ⁸b;                                                  \
   if (*leadOr8Bit == 0x0) { goto unagain; }                                \
   followers = Utf8Followers(*leadOr8Bit);                                  \
   if (followers < 0) { return -1; }                                        \
   incr = followers + 1;                                                    \
   uc = Utf8ToUnicode(leadOr8Bit,incr);                                     \
   if (uc == 0xFFFE || uc == 0xFFFF) { return -2; }                         \
   unicodes[tetras] = uc; ++tetras; ⁸b += incr;                             \
   goto again;                                                              \
unagain:                                                                    \
   return 0;                                                                \
}(UCS,TRS,⁸B,U8B,U8MAX) /* ⬷ implicits in block statement: none. */

__builtin_int_t Utf8BytesUntilNull(char8_t * u8s, __builtin_int_t maxutf8bytes);
/* ⬷ non-equivalent to 'strlen' and returns 'maxutf8bytes' in case NULL is not 
  earlier found. */

__builtin_int_t TetrasUntilNull(char32_t * ucs, __builtin_int_t maxtetras);
/* ⬷ actually until 0x0000 or 'passed EOT'. */

inline
int
Utf8ToUnicode(
  char8_t * u8s, __builtin_int_t maxutf8bytes𝘖rZero, 
  void (^out)(__builtin_int_t tetras, char32_t * ucs, __builtin_int_t utf8bytes)
)
{
  __builtin_int_t bytes = maxutf8bytes𝘖rZero ? maxutf8bytes𝘖rZero : 
    Utf8BytesUntilNull(u8s,BUILTIN₋INT₋MAX);
   if (bytes < 0) { return -1; }
   __builtin_int_t tetras=0,⁸b=0; char32_t ucs[bytes+1];
   if (⁺⁼Utf8ToUnicode(ucs,tetras,⁸b,u8s,bytes)) { return -2; }
   out(tetras,ucs,⁸b);
   return 0;
}

inline
int
UnicodeToUtf8(
  char32_t * ucs, /* ⬷ in-case literal, terminated with 0x0000. */
  __builtin_int_t maxtetras𝘖rZero, 
  void (^out)(__builtin_int_t utf8bytes, char8_t * u8s, __builtin_int_t tetras)
)
{
  __builtin_int_t tetras = maxtetras𝘖rZero ? maxtetras𝘖rZero : 
    TetrasUntilNull(ucs,BUILTIN₋INT₋MAX), ᵇutf8 = 4*tetras;
   char8_t u8s[1+ᵇutf8]; __builtin_int_t ⁸idx=0, ³²idx=0;
   if (⁺⁼UnicodeToUtf8(u8s,³²idx,⁸idx,tetras,ucs)) { return -1; }
   out(⁸idx,u8s,³²idx);
   return 0;
}

/* when toggling representation, the symbols are traversed at least twice ⤐ */
__builtin_int_t ExactUtf8bytes(char32_t * ucs, __builtin_int_t maxtetras);
/* ⬷ a․𝘬․a 'Utf8bytesExceptNULL'. */
__builtin_int_t ExactTetras(char8_t * u8s, __builtin_int_t maxutf8bytes); 
/* ⬷ the 'ExactTetras' may return less than zero and 'ExactTetras' may 
 traverse undefined code points and return '-1'. */

MACRO Unicodes ᵊ(const char32_t * literal) { char32_t * ucs = Critic(literal); 
 __builtin_int_t count = TetrasUntilNull(ucs, BUILTIN₋INT₋MAX); 
 return Unicodes { count, ucs }; }

MACRO int ᵊ(const char8_t * literal, void (^sometime)(Unicodes uc)) {
  char8_t * u8s = Critic(literal);
  if (Utf8ToUnicode(u8s, BUILTIN₋INT₋MAX, 
    ^(__builtin_int_t tetras, char32_t * ucs, __builtin_int_t utf8bytes) {
      Unicodes unicode { tetras, ucs };
      sometime(unicode);
    }
  )) { return -1; }
  return 0;
}

#pragma mark fine print for well-versed readers a․𝘬․a 'intervals and dots'

typedef struct UnicodeIntervalAnd𝑂rLocation {
  __builtin_int_t tetrasRelativeFirst, tetrasRelativeLast;
} UnicodeSelection; /* ⬷ see also --<Preserves.h>{Utf8Interval|Sourcelocation}. */

typedef struct Unicodeblock {
  __builtin_int_t linesOffsetFirst, linesOffsetLast, col₁, col₂;
} Unicodeblock;

typedef struct Unicodeblock⁻¹ {
  __builtin_int_t colL𝟷, colL𝟸, linesOffsetFirst, linesOffsetLast;
} UnicodeColBlock; /* ⬷ see again --<Preserves.h>{Utf8Interval|Sourcelocation}. */

FINAL struct Ornaments { /* ⬷ a․𝘬․a 'Intervallic' …                         
                                                                             
         ⎡      😐≅       ⎤                                                  
        ♢⎢    😐?😐≅😐    ⎥                                                 
         ⎣ 😐?😐≅😐?😐?😐?⎦                                                 
                                                                            */
    
    Ornaments(Unicodes native₋temp₋endians, bool readonly₋eg₋non₋striped);
    
    Ornaments() = delete;
    
    struct { ˢKnots𝟷ᵈ<char32_t> unicodes; /* ⬷ alt. 'Kiddle 𝟷₋fragment'. */
      
      Knots𝟷ᵈ utf8₋symbol₋original; /* ⬷ alt. ˢKnots𝟷ᵈ<Utf8Symbol> original. */
      
      ˢKnots𝟷ᵈ<UnicodeIntervalAnd𝑂rLocation> parsed; /* alt. 'void * lines'. */
      
      ˢKnots𝟷ᵈ<Unicodeblock> rendered;
      
      /* typedef __builtin_int_t ParsedIdx; */
      
      void * namedruns₁; /* ⬷ a․𝘬․a Map<const char32_t *, ParsedIdx>. */
      
      void * namedruns₂; /* ⬷ a․𝘬․a Map<const char *, ParsedIdx>. */
      
      struct {
        
        /* 𝟺𝚔𝚋Quadtreenode quadtrees[2]; */
        
      } exegesis;
      
    } cache;
    
    enum Errorcode { unableToEncompass };
    
    MACRO static void Error(Errorcode code) { /* ⭐️ */ Sheriff(); }
    
    int text(void (^none𝘖rMany)(__builtin_int_t tetras, char32_t * unicodes, 
     bool& stop)); /* ⬷ see also [github.com]>--<fmtlib>--<fmt>. */
    
😐; /* … 'decorated₋string' and 'recording', 𝖼𝖿. 'insert', 'update' and 'delete'. */

template <typename T> struct rectangle { T height, width; int /* Unit */ unit; };
template <typename T> struct measure { T value; int /* Unit */ unit; };

#define INCLUDE₋TYPESET __has_include(<Additions/Typeset.hpp>)
#define INCLUDE₋COLOR __has_include(<Additions/Color.hpp>)
#define INCLUDE₋KIDDLE __has_include(<Additions/Kiddle.hpp>)

namespace Directions { typedef __builtin_uint_t Cross; 
  BITMASK(Cross) { CrossLeftToRight = 0b0001, CrossRightToLeft = 0b0010, 
   CrossTopToBottom = 0b0100, CrossBottomToTop = 0b1000 };
}

#if INCLUDE₋TYPESET && INCLUDE₋COLOR && INCLUDE₋KIDDLE
#include <Additions/Kiddle.hpp>
#include <Additions/Color.hpp>
#include <Additions/Typeset.hpp>
#endif

#if __has_include(<Additions/Impressions.hpp>)
#include <Additions/Impressions.hpp>
#endif

namespace Unit { enum { thou, mm, in, pc, pt, px, 𝑜𝑝tlp }; }
/* int Width(const Ornaments& o, Unit unit, double &width, double &kerning) WESTERN;
int Width(const Unicodes& uc, Unit unit, double &width, double &kerning) WESTERN; */
/* 1/log²(2) 'pavoni'=distance between copy and its header. */
/* 1 thou = 1/100'th inch; 1pc=1/6 inch, 1/12pc=1pt. */
/* 1 shilling ⟷ 1/12 pound ∧ 1 shilling ⟷ 12 pence. (DE-MORGAN's law) */
/* Hydrogen a․𝘬․a ²H: 0 0 0, 1 2 1. ⬷ a․𝘬․a 'toggling isotopes'. */
/* Intervals and dots: 0 0, 0 1, 1 2, 3 3, ﹇ 4.  ⬷ see OEIS. */
namespace Raster { enum { mm, lines, nonuniform₋mm, none }; }

#pragma mark - The scientists' terminal

namespace 𝟾x𝟾₋matrix₋AAPL {
  
  BITMASK (uint32_t) { Left = 0b1<<9, Up = 0b1<<7, Down = 0b1<<6, 
   Right = 0b1<<8, Return = 0b1<<5, Shift = 0b1<<4, Fn = 0b1<<3, 
   Control = 0b1<<2, Option = 0b1<<1, Command = 0b1<<0 };
  
}

namespace Inputctrl {
 
  enum /* Inputctrl */ { user₋stopped=1, timedout, keyboard₋terminated, 
   indication₋terminated, material₋terminated };
  
  int 🥈 ﹟inf₋periods = 0; /* ⬷ for 'periods𝘖rZero' below. */
 
}

#include <Additions/maths.hpp>
#if __has_include(<Additions/grün-d3.cxx>)
#include <Additions/grün-d3.cxx>
#endif /* ⬷ text₋image, infographics, UI and perception. */

struct Utf8Terminal {
    
    Utf8Terminal();
    
    ~Utf8Terminal();
    
   𝟄₋int₁ /* Inputctrl */ 
    corout₋Symbols( /* ⬷ see also --<Fossilate.h|cpp>{TerminalIn ∧ WaitTerminal}. */
      int periods𝘖rZero, 
      int 𝟷𝟶ᵗʰ₋seconds, 
      void (^ping𝘖r𝖭𝖴𝖫𝖫)(bool &stop), /* ⬷ cyclically whilst time passes. */
      void (^keyput𝘖rRecieved)(char32_t unicode, bool &stop) /* ⬷ a․𝘬․a 'after₋a₋keypress'. */
    ) const; /* ⬷ c𝘧․ 'readOne𝘖rManylines', 'interaction', 'password', 'getc'/'ungetc' and 'readline'. */
    
    int write(char8_t * serie, __builtin_int_t bytes) const;
    
    void (^format)(double ℝ, Utf8Terminal &stream);
    
#if __has_include(<Additions/VT99.cxx>)
#include <Additions/Vt99.cxx>
#endif
    
😐; /* ⬷ for rendering sediment, isaritm and discrete dissection. */

namespace NumberformatCatalogue { 
void Scientific(double ℝ, void (^out)(char32_t uc));
void Monetary(double ℝ, void (^out)(char32_t uc));
void Regional(double ℝ, void (^out)(char32_t uc));
void Interval(double ℝ₁, double ℝ₂, bool openend, void (^out)(char32_t uc));
void Percentile(double ₋𝟯σ, double ₋𝟮σ, double ₋σ, double 𝟶, double σ, 
 double 𝟮σ, double 𝟯σ, __builtin_int_t * 𝟭𝟬ⁱ, void (^out)(char32_t uc));
/* ⬷ See also 'Quantile'. */
void Normal(double μ, double σ, void (^out)(char32_t uc));
/* log-normal distribution = draped 'logₑ' is N(μ,σ²). */
extern void (^Default)(double, Utf8Terminal&); } /* ⬷ NumberformatCatalogue. */
enum class Base { dec, hex, oct, bin };
void Present(Utf8Terminal &term, __builtin_int_t ℤ);
void Present(Utf8Terminal &term, __builtin_uint_t ℕ, Base base);
void Present(Utf8Terminal &term, double ℝ);
void Present(Utf8Terminal &term, char32_t uc);
void Present(Utf8Terminal &term, char8_t * u8s, __builtin_int_t maxbytes=BUILTIN₋INT₋MAX);
/* Struct assignment ⟶ Memory (shallow) copy. */
void Present(Utf8Terminal &term, Ornaments& o);
/* void Present(Utf8Terminal &term, Unicodeblock location); */
/* enum Register { rtcc, dma0, … }; void Present(Utf8Terminal &term, Register reg); */
void Present(Utf8Terminal &term, AnnotatedRegister& ar, uint32_t value, bool 𝟷𝟼₋bits=false);
void Presentᵧ(Utf8Terminal &term, double 𝕏);
void Presentᵧ(Utf8Terminal &term, float 𝕏);

struct statistics { double min, q1, mean, q3, max; };
DISORDERABLE void Present(Utf8Terminal &term, statistics& details, 
 Ieee754form f, Unicodes separator);

enum class Simdformᵦ { normal₋distribution, approximation₋follow₋accuracy, 
 max₋to₋min, complex, cartesian2ᵈ, polar2ᵈ, polar₋and₋contracyclicity };
/* ⬷ angular components always within [-pi/2, pi/2]. */
void Present(Utf8Terminal &term, simd_tᵦ 𝕏, Simdformᵦ semantic);

#pragma mark - Conveniences

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_int_t ℤ)
{ Present(term,ℤ); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_uint_t ℕ)
{ Present(term, ℕ, Base::hex); return term; }

/* MACRO Utf8Terminal & operator<<(Utf8Terminal &term, double x)
{ Present(term,x); return term; } */

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char32_t uc)
{ Present(term,uc); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char8_t * u8s)
{ Present(term,u8s); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char * 𝟽bit₋literal)
{ Present(term,(char8_t *)𝟽bit₋literal); return term; }

/* MACRO LONGTOOTH Utf8Terminal & operator<<(Utf8Terminal &term, char c)
{ Present(term,(char32_t)c); return term; } ⬷ a․𝘬․a 'ascii7ToUnicode'.

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, float x)
{ Present(term,(double)x); return term; } */

inline void Present(Utf8Terminal &term, 
  char32_t * ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳, bool emit𝖤𝖮𝖳=true
)
{  char32_t uc; __builtin_int_t i=0;
   if (ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳 == NULL) { return; }
again:
   uc = *(ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳 + i);
   if (uc == 0x0000) { return; }
   if (emit𝖤𝖮𝖳 == 0 && uc == END_OF_TRANSMISSION) { return; }
   Present(term,uc);
   i++; goto again;
}

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char32_t * ucs)
{ Present(term,ucs,true); return term; }

/* Utf8Terminal & operator<<(Utf8Terminal &term, const String& s) {
  __builtin_int_t tetras = s.﹟unicodes(); for (int i=0; i<tetras; i++)
  { s.unicode(i, ^(byteaddress prev, char32_t elem, byteaddress next) { 
    term.write(elem); }); } return term; }
Utf8Terminal & operator<<(Utf8Terminal &term, const Ornaments& s) 
  { Present(term, s); return term; }
template <typename T> Utf8Terminal& operator<<(Utf8Terminal &term, 
  Vector<T> &v) { Present(v,term); return v; }
Utf8Terminal & operator<<(Utf8Terminal &u8os, Utf8Terminal present) 
  { return u8os; } */

struct 𝗵fill { }; struct 𝘃fill { double val; int /* Unit */ unit; };
struct 𝗣𝒂𝒈𝒆 { bool versoNotRecto; }; /* ⬷ a․𝘬․a 'formfeed' and U+0x000c. */
𝗣𝒂𝒈𝒆 ᵖ𝗴(bool); 𝘃fill vfill(double, /* Unit */ int); 𝗵fill hfill();
/* ⬷ a․𝘬․a the Unicodes `␋` , `␉` and `␌`. */
Utf8Terminal & operator<<(Utf8Terminal&,𝗵fill);
Utf8Terminal & operator<<(Utf8Terminal&,𝘃fill);
Utf8Terminal & operator<<(Utf8Terminal&, 𝗣𝒂𝒈𝒆);

extern "C" { extern const char *tab, *eol, *sep; } /* later possibly-maybe: ↹ ↩︎ ¶ and hfill: ⎓ alt. ﹇. */

rt₋namespace Terminal { extern Utf8Terminal myOutput, myTrace₁, myTrace₂; }
rt₋namespace Vt100 { const char * bright, *dim, *fgBlue, *fgRed, *reset, *reverse; }

#define Termlog Terminal::myTrace₂
#define Termtail Terminal::myTrace₁

#pragma mark - A globally unique identifier for small and big

typedef sexdeca Guid;

Guid Newguid();

#pragma mark - Chronological sequences

/**  Retrieves a unique value in a 'strict monotonically increasing' serie. ⤐ */

struct Chronology₋peg { __builtin_int_t soon=0; }; /* ⬷ a․𝘬․a 'Sequent'. */

__builtin_int_t Pression(Chronology₋peg * act, bool * wrapped); /* ⬷ a․𝘬․a 'I₋m₋print' and 'Ordinal'. */

namespace Messaging { /* ⬷ a․𝘬․a Transceiver, /lear-n-i-n-g/, static-telluric and after₋Retrospectives. */
   
   int Init(void * sw₋signals, /* recall --<Twinbeam.h>{Scheduler::hw₋collection}. */
     void * (^node₋alloc)(int bytes)
   );
   
   int Informed(Guid signal, 𝟄₋int₁ * 𝟷₋coroutineToInfluence, 
     void * (^node₋alloc)(int bytes)); /* Formerly 'with₋Indicate' and 'Trap'. */
   
   int Entrust(Guid signal, void * ctx = NULL); /* ⬷ a․𝘬․a 'Stifta', 'Mature', 
     'Scribble', 'Pierce', 'Drive₋lead', 'Fuel' and not 'Indicate'. */
   
} /* ⬷ a․𝘬․a 'messaging', 'Victorian', 'jurisprudence', 
 'coroutines₋required', 'ʰᵚcollection₋required', 'Unix-signal', 
 'sw-interrupt', 'notification', e₋v₋en₋t and /v-ote/. */

void GuidToText(const Guid& guid, void (^out)(char digit𝘖rHyphen));

void Present(Utf8Terminal &term, const Guid& mp);
/* …not: MACRO Argᴾ ﹟Ref(Guid& g) { ⟶⟵ } */

#pragma mark - Input feeding in practice

enum class CastToIntOpinion { accept, rejecting, negate, commit, annul };

Opt<__builtin_int_t>
CastTˣᵗToInt(
  CastToIntOpinion (^feeder)(unsigned short &digit)
); /* ⬷ a․𝘬․a 'CastToInt'. Incorp. also 'Swap 𝑣𝑠․ ♚♜ and X', '±2021-01-17 09:56' and '2021-01-07--2021-01-09'. */

enum class Inputcontrol { ok, quit };

enum class Readlineopinion { accept, rejecting, commit, quit };

int ReadUtf8(Readlineopinion (^feeder)(char &utf8), Inputcontrol (^line)(char * line));

int ReadUnicode(Readlineopinion (^feeder)(char32_t &unicode), Inputcontrol (^line)(char32_t * line)); 
/* count symbols with 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 inside 'feeder'. */

#pragma mark tri-cameral tokenizer

enum class Tokenizefact { fragment, rejecting, separator, error, eol };

int
Tokenize(
  Tokenizefact (^feeder)(char32_t &unicode), 
  Inputcontrol (^ahead)(char32_t * unicodes, __builtin_int_t count), 
  Inputcontrol (^token)(char32_t * unicodes, __builtin_int_t count)
); /* 'tokenize' - 'readUnicode' = Opt<𝑓𝑢𝑡𝑢𝑟𝑒 𝑡𝑒𝑛𝑠𝑒> */

#pragma mark - Recollection and associativity

struct Bitset₋suprenum { /* ⬷ a․𝘬․a 'Capped-ET-bitset'. */
  
  __builtin_uint_t state;
  
  void toggle(short pos) { state ^= 1<<pos; } /* xor₁: 'different' between two and 
    toggles one; i․𝘦 'abstract' ⟷ xor; a․𝘬․a 'alternate'. */
  
  __builtin_int_t anset() { /* xor₂: toggles ∧ identifies 'change' simultaneously. */
     short cnt = (short)TrailingZeros(state);
     toggle(cnt);
     return cnt;
  } /* ⬷ toggles a 'non-toggled' bit. */
  
}; /* ⬷ for --<🥽 Memclone.cpp> ∧ --<🥽 Bookshelf.cpp>. */

#pragma mark - Volatile memory copying (asynchronous)

int
OptimisticAsync8Copy(
  void * noncachable₋dst,
  void * noncachable₋src,
  int bytes,
  bool ᵗᵍᵍˡendian,
  void (^ping)(int bytes, bool &reset, bool &suspend),
  void (^error)(), void (^complete)()
); /* ⬷ a․𝘬․a Copy8Async and Basictransfer. */

#pragma mark - Dispatch, priorities and interrupts

typedef void (^Async₋job)(); /* ⬷ a․𝘬․a 𝐶𝑂𝑀𝑃𝑈𝑇𝐴𝑇𝐼𝑈𝑀 and 'CHandler'. */

typedef int (^TransformAndResolve)(Unicodes pathᵚᵍ, void (^final)(const char * regular𝘖rLinkpath));

int Reflect(Unicodes primary𝘖𝘳𝑆econd, TransformAndResolve tr, __builtin_int_t * 
  totalbytes, void (^zero𝘖rSeveral)(__builtin_int_t byteOffset, int count, 
  char32_t unicodes[], bool& stop)); /* ⬷ a․𝘬․a 'TextualReflect' and 'RadioReflect'. */
int Reflect(Unicodes primary𝘖𝘳𝑆econd, unsigned expeditionary, __builtin_int_t bytesOffset, 
 __builtin_int_t pages𝘖𝘳Zero, __builtin_int_t bytesAugment, __builtin_int_t * totalbytes, 
 TransformAndResolve tr, void (^pages)(__builtin_int_t count, uint8_t **𝟺kbframes, 
 __builtin_int_t lastunusedbytes)); /* ⬷ a․k․a 'Unspecified₋reflect'. */

/* int Pamphlet(unsigned expeditionary, __builtin_int_t bytes, Ensemble &details);
int Branch(Unicodes primary𝘖𝘳𝑆econd, TransformAndResolve tr, 
  void (^ping)(double⁺ʳ 𝟬₋𝟭percent, bool& stop), 
  AsyncJob stopped, Ensemble &ensemble, AsyncJob completed);
int Reconcile(Opt<Unicodes> primary𝘖𝘳𝑆econd, TransformAndResolve tr, 
  void (^ping)(double⁺ʳ 𝟬₋𝟭percent, bool& stop), 
  AsyncJob repented, Ensemble& branch, AsyncJob completed); */ /* --<Ensemble.h>. */

#pragma mark - Language translation --<Automata.cpp>

enum ProbedSemanticContext { Inexplainatoria, Informal, Formal };

/* int Parse(const char *utf8, void (^untangle)(char32_t unicode, 
  const Knots¹ᵈ<int>& ss, void * / * a․𝘬․a Map<char32_t *, __builtin_uint_t>& * / stab,
  __builtin_int_t byteoffset, bool edge₁, bool& stop)); */

int TokenizeUtf8ToUnicode(char8_t * material, short bytes, void (^none𝘖rSeveral)(
 __builtin_int_t byteOffset, char32_t unicode, __builtin_int_t utf8bytes, bool& stop));

enum class Encoding { utf8, unicode };

/* int TokenizeUtf8OrUnicode(Encoding encoding, Memoryview content, __builtin_int_t& beam, 
  void (^zero𝘖rSeveral)(char32_t unicode, __builtin_int_t byteOffset, bool& stop)); */

struct Jagged { Jagged(); ~Jagged(); 
  int include(__builtin_int_t tetra₋idx, __builtin_int_t δ₋tetracount);
  __builtin_int_t count() const;
  int 𝟺kbtile(__builtin_int_t ﹟, __builtin_int_t &tetra₋idx, __builtin_int_t &δ₋tetracount);
😐; /* ⬷ a․𝘬․a Linebreaks. */

Opt<Chronology::instant>
TS( /* ⬷ e․𝘨 2012-01-24 12:00:00.125, 2018-05-18 15:58:36 and 2012-01-24 12:00:00.000000000232. */
  Encoding encoding,
  Chronology chronology,
  memoryview datetime
) NEVERBLURTS;

#pragma mark Trangress 𝑡𝑜 and 𝑓𝑟𝑜𝑚 a Fiber                 ✁ until ✂️
/* ✂️ << --<shoebox>{Fiber} ✃ */

#endif

