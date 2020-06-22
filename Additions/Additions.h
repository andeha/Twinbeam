/*
 *  Additions.h to Twinbeam: Includes the IEEE754 `double` type.
 *  C++2a to clang to x86_64 and Mips.
 *  Version 10.0.0 to Mips.
 *  Xcode Version 10.2.1 (10E1001) to x86_64.
 */

#ifndef __ADDITIONS_H
#define __ADDITIONS_H

void CastᵈᵇˡToText(double value,
  void (^digits)(bool neg, int e, const char *𝟶to𝟿s), 
  void (^zero)(bool neg), void (^inf)(bool neg), void (^nan)()
); /* A․𝘬․a `CastToText`. */

/* The next smallest value after `1`. */
#define DOUBLE_EPS1  1.00000000000000011102230246251565 /* 1+2⁻⁵³ */
#define FLOAT_EPS1   1.0000000119                       /* 1+2⁻²³ …possibly 2⁻²⁴. */
#define HALF_EPS1    1.0009765625                       /* 1+2⁻¹⁰ …maybe 2⁻¹¹. */
#define Q31_EPS1     1.0000000004656612873077392578125  /* 1+2⁻³¹ */
#define Q15_EPS1     1.000030517578125                  /* 1+2⁻¹⁵ */
#define Q7_EPS1      1.0078125                          /* 1+2⁻⁷ */
#define X86FP80_EPS1 1.0000000000000000000542101        /* 1+2⁻⁶⁴ */
#define BINARY128_EPS1 1.000000000000000000000000000000000096296 /* 754-2008 */
/* decimal128/binary128, 𝜀b₂≈log₁₀(2¹¹³)≈34.16 decimal digits, BSM. */

/*
                                                                             
*** 'Big-Endian Ieee 754 Base-2 double with double-Zero (-1)ˢ(1+m*2⁻⁵²)×2ˣ⁻¹⁰²³ ***
                                                                             
Binary64_SGN x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|
            |␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Sign bit               
                                                                             
Binary64_EXP ␣xxx|xxxx|xxxx|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣³²|
            |␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Signed exponent -1024 to 1024 (11 bits)
                                                                             
Binary64_MAN ␣␣␣␣|␣␣␣␣|␣␣␣␣|xxxx|xxxx|xxxx|xxxx|xxxx|
            |xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx|xxxx| Fraction/mantissa/significand (52 bits)
                                                                             
*** IEEE 754 Base-2 single with Double-zero (-1)ˢ(1+m*2⁻²³)×2ˣ⁻¹²⁷ ***
                                                                             
Binary32_SGN x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Sign bit
Binary32_EXP ␣xxx|xxxx|x␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣| Signed exponent -126 to 127 (biased)
Binary32_MAN ␣␣␣␣|␣␣␣␣|␣xxx|xxxx|xxxx|xxxx|xxxx|xxxx| Fraction/mantissa/significand (23 bits)
                                                                             
*/

#define IEEE754BASE2_64BIT_PZERO  0x0000000000000000L /* ⬷ Big endian */
#define IEEE754BASE2_64BIT_NZERO  0x8000000000000000L 
#define IEEE754BASE2_64BIT_SNAN₂  0x7FF0000000000002L /* Signalling */
#define IEEE754BASE2_64BIT_PINF   0x7FF0000000000000L /* Positive */
#define IEEE754BASE2_64BIT_NINF   0xFFF0000000000000L /* Negative */
#define IEEE754BASE2_64BIT_QNAN₂  0x7ff8000000000002L /* Quiet */
#define IEEE754BASE2_32BIT_QNAN₂  0x7FC00002

MACRO bool isinf(double x) { octa o; o.base₂ = x; return o.bits == 
  IEEE754BASE2_64BIT_NINF || o.bits == IEEE754BASE2_64BIT_PINF; }

MACRO bool isnan(double x) { octa o; o.base₂ = x; return (o.binary64.mantissah 
  != 0 || o.binary64.mantissal != 0) && o.binary64.exponent == 0x7ff; } /* Exponent 
 is eleven bits. Sign not relevant; and IEEE 754-2008: MSB is `is_quiet`. */

MACRO bool isexactlyzero(double x) { octa o; o.base₂ = x; return o.bits == 
  IEEE754BASE2_64BIT_PZERO || o.bits == IEEE754BASE2_64BIT_NZERO; }

MACRO double abs64d(double x) { return x < +0.0 ? -x : x; } /* …and for the mathematically inclined '-0.0'. */

namespace Numberformat { enum { Scientific, Monetary }; }
MACRO Argᴾ ﹟F(double f, int format=Numberformat::Scientific) { return Argᴾ { .value.f₁=f, 9 }; }
MACRO Argᴾ ﹟F(float r, int format=Numberformat::Scientific) { return Argᴾ { .value.f₂=r, 8 }; }

#pragma mark 😐🎲

enum GaussianApproximate { AbramowitzStegun, ZogheibHlynka };
int Gaussian(GaussianApproximate approximate, double *out);
int Uniform(double *out); /* *out ∈ [0, 1) */

#pragma mark - In cases of 'high-precision IEEE754'

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

MACRO bool Similar(double x, double y, double eps) { if (isinf(x) &&
  isinf(y)) return true; if (isnan(x) && isnan(y)) return true; if (
  isexactlyzero(x) && isexactlyzero(y)) return true; double diff =
  abs64d(x - y); return diff < eps; }

#pragma mark - Figures in compliance with Mediterranean laws

int Roman(__builtin_int_t n, void (^out)(char numeral));

#pragma mark - Conversions given --<Additions>--<Filesystem.hpp>

#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 __attribute__ ((nonnull))
__builtin_int_t Utf8BytesUntilNull(const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8, __builtin_int_t 
  maxutfbytes); /* Returns `maxutfbytes` in-case NULL is not earlier found. */
__builtin_int_t Utf8BytesIncludingANull(__builtin_int_t ³²bytes, char32_t * 
  𝑙𝑒𝑎𝑑𝑖𝑛𝑔 nativeEndianUnicodes, bool &traversedUndefinedCodepoint);
__builtin_int_t UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳(char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 nativeEndianUnicodes, 
  __builtin_int_t maxtetras𝘖r₋𝟷); /* Actually until 0x0000 or 'passed EOT'. */
__builtin_int_t UnicodesAnd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳(const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8, __builtin_int_t 
  maxutfbytes); /* ...also returns `maxutfbytes` when NULL can not be found. */

#define ⁺⁼UnicodeToUtf8(Buffer,³²B,⁸B,T,UCS)                                \
auto unicodeToUtf8 = ^(char buffer[], __builtin_int_t& ³²b,                 \
  __builtin_int_t& ⁸b, int tetras, char32_t * ucs) {                        \
again:                                                                      \
   char32_t uc = *(ucs + ³²b);                                              \
   if (uc == 0x0000 || uc == END_OF_TRANSMISSION) { goto unagain; }         \
   if (UnicodeToUtf8(uc, ^(const uint8_t *p, int bytes) {                   \
      *(buffer + ⁸b) = *p;                                                  \
      if (bytes >= 2) { *(buffer + ⁸b + 1) = *(p + 1); }                    \
      if (bytes >= 3) { *(buffer + ⁸b + 2) = *(p + 2); }                    \
      if (bytes >= 4) { *(buffer + ⁸b + 3) = *(p + 3); }                    \
      ⁸b += bytes; })) { return -1; }                                       \
   if (++³²b < tetras) goto again;                                          \
unagain:                                                                    \
   *(buffer + ⁸b) = '\0';                                                   \
   return 0;                                                                \
}(Buffer,³²B,⁸B,T,UCS) /* Implicits in block expression: none. */

#define ⁺⁼Utf8ToUnicode(U8,UCS,T,MAX,TETRA)                                 \
auto utf8ToUnicode = ^(const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8, char32_t unicodes[],        \
  bool prune, __builtin_int_t maxUCs, __builtin_int_t * tetra) {            \
   __builtin_int_t followers, incr, ⁸b=0, Ɀtetra; char32_t uc;              \
  *tetra /* 𝘈․𝘬․a ³²b */ = 0;                                               \
again:                                                                      \
   const uint8_t * leadOr8Bit = (const uint8_t *)utf8 + ⁸b;                 \
   if (*leadOr8Bit == 0x0) { goto unagain; }                                \
   Ɀtetra = *tetra; /* ⬷ Sampled tetra! (A․𝘬․a `⁑deref`, `𐂚` , `𝛶`, `⏘deref`, and `🥉tetra`) */  \
   if (!prune && maxUCs < Ɀtetra) { return -1; }                            \
   if (prune && maxUCs < Ɀtetra) { goto unagain; }                          \
   followers = Utf8Followers(*leadOr8Bit);                                  \
   if (followers < 0) { return -2; }                                        \
   incr = followers + 1;                                                    \
   uc = Utf8ToUnicode(leadOr8Bit, incr);                                    \
   if (uc == 0xFFFE || uc == 0xFFFF) { return -3; }                         \
   unicodes[Ɀtetra] = uc; *tetra = Ɀtetra + 1; ⁸b += incr;                  \
   goto again;                                                              \
unagain:                                                                    \
   unicodes[Ɀtetra] = END_OF_TRANSMISSION;                                  \
   return 0;                                                                \
}(U8,UCS,T,MAX,TETRA) /* Implicits in block statement: none. */

inline
int
Utf8ToUnicode(
  const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8,
  __builtin_int_t maxutfbytes, 
  void (^out)(char32_t * uc, __builtin_int_t tetras)
) {  __builtin_int_t maxUCs=UnicodesAnd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳(utf8,maxutfbytes);
   if (maxUCs == maxutfbytes) { return 1; }
   __builtin_int_t tetra; char32_t unicodes[maxUCs]; bool trim=false;
   if (⁺⁼Utf8ToUnicode(utf8,unicodes,trim,maxUCs,&tetra)) { return -1; }
   out(unicodes,tetra);
   return 0;
}

inline
int
UnicodeToUtf8(
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳,
  __builtin_int_t maxtetras,
  void (^out)(const char * utf8, __builtin_int_t tetras, __builtin_int_t ᵇutf8)
) {  __builtin_int_t tetras=UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳(ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳,maxtetras);
   bool invalid=false; __builtin_int_t ᵇutf8 = 
     Utf8BytesIncludingANull(tetras<<2,ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳,invalid);
   if (invalid) return -2;
   char utf8[ᵇutf8]; __builtin_int_t ³²idx=0, ⁸idx=0;
   if (⁺⁼UnicodeToUtf8(utf8,³²idx,⁸idx,tetras,ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳)) { return -1; }
   out(utf8,³²idx,⁸idx);
   return 0;
}

inline
int
UnicodeToUtf8(Unicodes ucs,
  void (^out)(const char * utf8, __builtin_int_t ᵇutf8)
) {
   __builtin_int_t ᵇutf8 = 4*ucs.tetras; /* Closed under 4 times and less. */
   char utf8[ᵇutf8]; __builtin_int_t ³²idx=0, ⁸idx=0;
   if (⁺⁼UnicodeToUtf8(utf8,³²idx,⁸idx,ucs.tetras,ucs.unicodes)) { return -1; }
   out(utf8,ᵇutf8); return 0;
}

MACRO Unicodes ᵊ(const char32_t * ucs) { char32_t * uc=Critic(ucs); 
  int t = UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳(uc,~0>>1); return Unicodes { t, uc }; }

MACRO int ᵊ(const char * utf8, void (^sometimes)(Unicodes uc)) {
  if (Utf8ToUnicode(utf8, ~0>>1, 
    ^(char32_t * uc, __builtin_int_t tetras) {
      Unicodes unicode { tetras, uc };
      sometimes(unicode);
    }
  )) { return -1; }
  return 0;
}

#pragma mark Fine print for well-versed readers a․𝘬․a 'intervals and dots'

typedef struct UnicodeIntervalAnd𝑂rLocation {
  __builtin_int_t tetrasRelativeFirst, tetrasRelativeLast;
} UnicodeSelection; /* See also --<Preserves.h>{Utf8Interval|Sourcelocation} */

typedef struct UnicodeBlock {
  __builtin_int_t linesOffsetFirst, linesOffsetLast, col₁, col₂;
} UnicodeBlock;

typedef struct UnicodeBlock⁻¹ {
  __builtin_int_t colL𝟷, colL𝟸, linesOffsetFirst, linesOffsetLast;
} UnicodeColBlock; /* See again --<Preserves.h>{Utf8Interval|Sourcelocation} */

#include <Additions/Knot.h>

FINAL struct Ornaments { /* A․𝘬․a `Intervallic`, `SpatialIntervals`, …       
                                                                             
         ⎡      😐≅       ⎤                                                  
        ♢⎢    😐?😐≅😐    ⎥                                                  
         ⎣ 😐?😐≅😐?😐?😐?⎦, `Spatsitemporal₋relative`, */
    
    Ornaments(const char32_t *nativeEndianUnicodes, 
      __builtin_int_t tetras, bool readonly);
    
    Ornaments() = delete;
    
    struct {
      
      Knots¹ᵈ<Utf8Symbol> original;
      
      Knots¹ᵈ<UnicodeIntervalAnd𝑂rLocation> parsed;
      
      Knots¹ᵈ<UnicodeBlock> rendered;
      
      /* typedef __builtin_int_t Parsedᴵᵈˣ; */
      
      void * namedruns₁; /* A․𝘬․a Map<const char32_t *, Parsedᴵᵈˣ>. */
      
      void * namedruns₂; /* A․𝘬․a Map<const char *, Parsedᴵᵈˣ>. */
      
      struct {
        
        /* 𝟺𝚔𝚋Quadtreenode * quadtrees; */
        
      } exegesis;
      
    } cache;
    
    enum Errorcode { unableToEncompass };
    
    MACRO static void Error(Errorcode code) { /* ⭐️ */ Sheriff(); }
    
    int text(void (^zero𝘖rMany)(__builtin_int_t tetras, char32_t * unicodes, 
     bool& stop)) const; /* See also [github.com]>--<fmtlib>--<fmt>. */
    
😐; /* …, `DecoratedString` and `Recording`. */

template <typename T> struct rectangle { T height, width; int /* Unit */ unit; };
template <typename T> struct measure { T value; int /* Unit */ unit; };

#if __has_include(<Additions/Impressions.hpp>)
#include <Additions/Impressions.hpp>
#endif

#if __has_include(<Additions/Typeset.hpp>) && __has_include(<Additions/Color.hpp>)
/* #include <Additions/Color.hpp>
#include <Additions/Typeset.hpp> */
#endif

namespace Unit { enum { thou, mm, in, pc, pt, px, 𝑜𝑝𝑡lp }; }
/* int Width(const Ornaments& o, Unit unit, double &width, double &kerning) WESTERN;
int Width(const Unicodes& uc, Unit unit, double &width, double &kerning) WESTERN; */
/* 1/log²(2) 'pavoni'=distance between copy and its header. */
/* 1 thou = 1/100'th inch; 1pc=1/6 inch, 1/12pc=1pt. */
/* 1 shilling ⟷ 1/12 pound ∧ 1 shilling ⟷ 12 pence. (DE-MORGAN's law) */
/* Hydrogen a․𝘬․a ²H: 0 0 0, 1 2 1. (a․𝘬․a 'toggling isotopes'.) */
/* Intevals and dots: 0 0, 0 1, 1 2, 3 3, ﹇ 4.  See also OEIS. */
namespace Raster { enum { mm, lines, nonuniform₋mm, none }; }

#pragma mark - Sequences and series

/**  Retrieves a unique value in a 'strict monotonically increasing' serie. 
 Wraps (𝄇) at `BUILTIN_INT_MAX`. */

struct Chronology₋peg { __builtin_int_t soon=0; };  /* A․𝘬․a `Sequent` and 'Stilistic chronology'. */

__builtin_int_t Ordinal(bool * didwrap, Chronology₋peg * act); 

#pragma mark - The Terminal

namespace Inputctrl { enum { Stopped=1, Timedout, Keyboard₋terminated, Indication₋terminated }; }

struct Utf8Terminal {
    
    Utf8Terminal();
    
    ~Utf8Terminal();
    
    int /* Inputctrl */ 
    interaction( /* See also --<Fossilate.h|cpp>{TerminalIn ∧ WaitTerminal}. */
      int periods𝘖rZero,
      int 𝟷𝟶ᵗʰ₋seconds,
      void (^ping𝘖r𝖭𝖴𝖫𝖫)(bool &stop), /* Cyclically whilst time passes. */
      void (^input)(char32_t unicode, bool &stop) /* After a key press. */
    ) const; /* 𝘊․𝘧 `readOne𝘖rManylines`, password`, `getc`/`ungetc` and `readline`. */
    
    int write(const uint8_t * utf8s, __builtin_int_t bytes) const; /* ⬷ Optionally NULL-termination included. */
    
    void (^format)(double x, Utf8Terminal &stream);
    
#if __has_include(<Additions/photo-d3.cxx>) && __has_include(<Additions/VT99.cxx>)
#include <Additions/VT99.cxx>
#endif
    
😐;

namespace NumberformatCatalogue { 
 void Scientific(double, void (^out)(char32_t uc));
 void Monetary(double, void (^out)(char32_t uc));
 void Regional(double ℝ, void (^out)(char32_t uc));
 void Interval(double ℝ₁, double ℝ₂, bool openend, void (^out)(char32_t uc));
 void Percentile(double ₋𝟹𝜎, double ₋𝟸𝜎, double ₋𝜎, double 𝟶, double 𝜎, 
   double 𝟸𝜎, double 𝟹𝜎, __builtin_int_t * 𝟷𝟶ⁱ, void (^out)(char32_t uc)); /* See also `Quantile`. */
 void Normal(double μ, double σ, void (^out)(char32_t uc));
 /* log-normal distribution = draped `logₑ` is N(μ,σ²). */
 extern void (^Default)(double, Utf8Terminal&); }
enum class Base { dec, hex, oct, bin };
void Present(Utf8Terminal &term, __builtin_int_t z);
void Present(Utf8Terminal &term, __builtin_uint_t n, Base base);
void Present(Utf8Terminal &term, double value);
void Present(Utf8Terminal &term, char32_t unicode);
void Present(Utf8Terminal &term, const char * utf8, __builtin_int_t maxbytes=BUILTIN_INT_MAX);
/* Struct assignment ⟶ Memory (shallow) copy. */
void Present(Utf8Terminal &term, const Ornaments & ds);
/* void Present(Utf8Terminal &term, UnicodeBlock location); */
/* enum Register { rtcc, dma0, … }; void Present(Utf8Terminal &term, Register reg); */
void Present(Utf8Terminal &term, const AnnotatedRegister& ar, uint32_t value, bool 𝟷𝟼bits=false);
void Presentᵧ(Utf8Terminal &term, double value);
void Presentᵧ(Utf8Terminal &term, float value);

#pragma mark - Conveniences

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_int_t z)
{ Present(term,z); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_uint_t n)
{ Present(term, n, Base::hex); return term; }

/* MACRO Utf8Terminal & operator<<(Utf8Terminal &term, double x)
{ Present(term,x); return term; } */

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char32_t unicode)
{ Present(term,unicode); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char * utf8)
{ Present(term,utf8); return term; }

/* MACRO LONGTOOTH Utf8Terminal & operator<<(Utf8Terminal &term, char c)
{ Present(term,(char32_t)c); return term; } A․𝘬․a `ascii7ToUnicode`.

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, float x)
{ Present(term,(double)x); return term; } */

MACRO
Utf8Terminal &
operator<<(
  Utf8Terminal &term,
  const char32_t * ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳
)
{ if (!ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳) { return term; }
  char32_t uc; int i=0;
again:
  uc = *(ucs𝘈nd𝟶𝚡𝟶𝟶𝟶𝟶𝘖r𝖤𝖮𝖳+i);
  if (uc == 0x0000) { return term; }
  if (uc == END_OF_TRANSMISSION) { return term; }
  Present(term,uc);
  i++; goto again;
}

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
struct 𝗣𝒂𝒈𝒆 { bool versoNotRecto; }; /* A․𝘬․a `formfeed` and U+0x000c. */
𝗣𝒂𝒈𝒆 ᵖ𝗴(bool); 𝘃fill vfill(double, /* Unit */ int); 𝗵fill hfill();
/* A․𝘬․a the Unicodes `␋` , `␉` and `␌`. */
Utf8Terminal & operator<<(Utf8Terminal&,𝗵fill);
Utf8Terminal & operator<<(Utf8Terminal&,𝘃fill);
Utf8Terminal & operator<<(Utf8Terminal&, 𝗣𝒂𝒈𝒆);

extern "C" { extern const char *tab, *eol, *sep; } /* Also: ↹ ↩︎ ¶ and hfill: ⎓ alt. ﹇. */

extern Utf8Terminal _myTerminal, _myTracelog;

#define Termlog _myTerminal

#pragma mark - Guids

typedef sexdeca Guid;

Guid NewGuid();

void GuidToText(const Guid& guid, void (^out)(char digit𝘖rHyphen));

void Present(Utf8Terminal &term, const Guid& mp);
/* …not: MACRO Argᴾ ﹟Ref(Guid& g) { ⟶⟵ } */

#pragma mark - Input feeding in practice

enum class CastToIntOpinion { accept, rejecting, negate, commit, annul };

Opt<__builtin_int_t>
CastTˣᵗToInt(
  CastToIntOpinion (^feeder)(unsigned short &digit)
); /* 𝘈․𝘬․a `CastToInt`. Includes also 'Swap 𝑣𝑠․ ♚♜ and X'. */

enum class Inputcontrol { ok, quit };

enum class Readlineopinion { accept, rejecting, commit, quit };

int ReadUtf8(Readlineopinion (^feeder)(char &utf8), Inputcontrol (^line)
  (char * line)); int ReadUnicode(Readlineopinion (^feeder)(char32_t &unicode),
  Inputcontrol (^line)(char32_t * line)); /* Count symbols with __block inside `feeder`. */

#pragma mark Tri-cameral tokenizer

enum class Tokenizefact { fragment, rejecting, separator, error, eol };

int
Tokenize(
  Tokenizefact (^feeder)(char32_t &unicode),
  Inputcontrol (^ahead)(char32_t * unicodes, __builtin_int_t count),
  Inputcontrol (^token)(char32_t * unicodes, __builtin_int_t count)
); /* `Tokenize` - `ReadUnicode` = Opt<𝑓𝑢𝑡𝑢𝑟𝑒 𝑡𝑒𝑛𝑠𝑒> */

#pragma mark - F̲irst i̲n f̲irst o̲ut: Zero, one or two halves are always returned`(FIFO)

extern void Include(int elems, int * brk, int * count);
extern int Physical(unsigned nowdelta, int brk, int elems);

template <typename E>
struct Fifo { int count=0, brk=0, elems; E * base; 
   int init(int elems, E * base) { this->elems=elems; this->base=base; return 0; }
   /* The parameter `nowdelta` is a․𝘬․a `δ` and `previous-relative-head`. */
   E * include() { if (count == elems) return NULL; E * Ɀ=brk+base; Include(elems,&brk,&count); return Ɀ; }
   int shiftout() { if (count == 0) { return -1; } count--; return 0; }
   enum Flavor { allinorder, latest /* 𝘊․𝘧 `randomized`. */ };
};  /* 𝘈․𝘬․a Fifoʳᵉf and not Fifoⁱⁿcorp.  Note also that three areas where 
  one 'precomputed 'area always separates the 'producer' from the 'consumer' 
  enables a 'stable external projection' without visible fluctuations a․𝘬․a 
  'flickering'; whereas two areas lead to the need to induce 'lock' as well as
  the other contratranquistimulantic constraints. 'efterhandskonstruktion'/hack. 
  (ret-ro-spect = [stimulu-tranqui-jello]). 
  
  Integration using the trapezoid rule is a recursive filter:
    
    yᵢ₊₁ = yᵢ + h (uᵢ₊₁ + uᵢ)/2
    
  as well as Simpsons rule:
    
    yᵢ₊₁ = yᵢ₋₁ + h (uᵢ₊₁ + 4uᵢ + uᵢ₋₁)/3
    
  See --<🥽 Romberg.cpp> for a ∫-method that is not on-line.
  
 */

template <typename E> bool Empty(const Fifo<E>& q) { return q.count == 0; }
template <typename E> E * Deref(unsigned δ, const Fifo<E>& q) { return q.base+Physical(δ,q.brk,q.elems); }
template <typename E> E * Youngest(const Fifo<E>& q) { return Empty(q) ? NULL : Deref(0,q); }
template <typename E> E * Oldest(const Fifo<E>& q) { return Empty(q) ? NULL : Deref(q.count-1,q); }

template <typename E> void Incorporate(const Fifo<E>& q, void (^location)(E * elem))
{ if (q.count==q.elems) { q.shiftout(); } E * elem = q.include(); location(elem); }

template <typename E>
int Retrospect(typename Fifo<E>::Flavor f, const Fifo<E>& q, E * t, E * t₋₁)
{
    switch (q.count) { case 0: return -1; 
      case 1: *t₋₁=*t=Deref(0,q); return 0;
      default: switch (f) { 
        case Fifo<E>::allinorder: *t₋₁=Deref(q.count-1,q); *t=Deref(q.count-2,q); break;
        case Fifo<E>::latest: *t=Deref(0,q); *t₋₁=Deref(1,q); break;
    } } return 0;
} /* Consider `𝟹₋Retrospect` where the derivate may appear to be continous. See 
  also --<System.h>{Actual} where two queues and interpolation results in a 
  `simd_tᵦ` and irreversibly 'momentan-retrospectiv'. See also 'man mkfifo' and 'man mknod'. */

#pragma mark - Recollection and associativity

struct Bitsetˢᵘᵖ { /* A․𝘬․a `Capped-ET-Bitset`. */
  
  __builtin_uint_t state;
  
  void toggle(short pos) { state ^= 1<<pos; } /* Xor₁: 'different' between two and 
    toggles one; I․𝘦 'abstract` ⟷ Xor. A․𝘬․a `alternate`. */
  
  __builtin_int_t anset() { /* Xor₂: Toggles ∧ identifies 'change' simultaneously. */
     short cnt = (short)TrailingZeros(state);
     toggle(cnt);
     return cnt;
  } /* Toggles a `non-toggled` bit. */
  
}; /* For --<🥽 Memclone.cpp> ∧ --<🥽 Bookshelf.cpp>. */

#pragma mark - Volatile memory copying (asynchronous)

int
OptimisticAsync8Copy(
  void * noncachable₋dst,
  void * noncachable₋src,
  int bytes,
  bool ᵗᵍᵍˡendian,
  void (^ping)(int bytes, bool &reset, bool &suspend),
  void (^error)(), void (^complete)()
); /* 𝘈․𝘬․a `Copy8Async` and `BasicTransfer`. */

#pragma mark - Dispatch, priorities and interrupts

typedef void (^Async₋job)(); /* A․𝘬․a 𝐶𝑂𝑀𝑃𝑈𝑇𝐴𝑇𝐼𝑈𝑀 and `CHandler`. */

typedef int (^TransformAndResolve)(Unicodes pathᵚᵍ, void (^final)(const char * regular𝘖rLinkpath));

int Reflect(Unicodes pathᵚᵍ, TransformAndResolve tr, __builtin_int_t * totalbytes, 
  void (^zero𝘖rSeveral)(__builtin_int_t byteOffset, int count, char32_t unicodes[], 
  bool& stop)); /* A․𝘬․a `TextualReflect` and `RadioReflect`. */
int Reflect(Unicodes pathᵚᵍ, unsigned expeditionary, __builtin_int_t bytesOffset, 
 __builtin_int_t pages𝘖𝘳Zero, __builtin_int_t bytesAugment, __builtin_int_t * totalbytes, 
 TransformAndResolve tr, void (^pages)(__builtin_int_t count, uint8_t **𝟺kbframes, 
 __builtin_int_t lastunusedbytes));

/* int Pamphlet(unsigned expeditionary, __builtin_int_t bytes, Ensemble &details);
int Branch(Unicodes pathᵚᵍ, TransformAndResolve tr, 
  void (^ping)(double⁺ʳ 𝟬₋𝟭percent, bool& stop), 
  AsyncJob stopped, Ensemble &ensemble, AsyncJob completed);
int Reconcile(Opt<Unicodes> pathᵚᵍ, TransformAndResolve tr, 
  void (^ping)(double⁺ʳ 𝟬₋𝟭percent, bool& stop), 
  AsyncJob repented, Ensemble& branch, AsyncJob completed); */ /* --<Ensemble.h>. */

#pragma mark - Language translation --<Automata.cpp>

enum ProbedSemanticContext { Inexplainatoria, Informal, Formal };

/* int Parse(const char *utf8, void (^untangle)(char32_t unicode, 
  const Knots¹ᵈ<int>& ss, void * / * a․𝘬․a Map<char32_t *, __builtin_uint_t>& * / stab,
  __builtin_int_t byteoffset, bool edge₁, bool& stop)); */

int TokenizeUtf8ToUnicode(uint8_t * material, short bytes, void (^zero𝘖rSeveral)
  (__builtin_int_t byteOffset, char32_t unicode, __builtin_int_t utf8bytes, bool& stop));

enum class Encoding { utf8, unicode };

/* int TokenizeUtf8OrUnicode(Encoding encoding, Memoryview content, __builtin_int_t& beam, 
  void (^zero𝘖rSeveral)(char32_t unicode, __builtin_int_t byteOffset, bool& stop)); */

struct Jagged { Jagged(); ~Jagged(); 
  int include(__builtin_int_t tetraidx, __builtin_int_t δ₋count);
  __builtin_int_t count() const;
  int 𝟺kbtile(__builtin_int_t ﹟, __builtin_int_t &tetraidx, __builtin_int_t &δ₋count);
😐; /* A․𝘬․a `Linebreaks`. */

enum class Arrangement { 𝟾, 𝟷𝟼, 𝟹𝟸, 𝟼𝟺, lo𝟼𝟺, hi𝟼𝟺, lo𝟷𝟸𝟾, hi𝟷𝟸𝟾, utf8 };

Opt<Chronology::Instant>
TS( /* E․𝘨 2012-01-24 12:00:00.125, 2018-05-18 15:58:36 and 2012-01-24 12:00:00.000000000232. */
  Encoding encoding,
  Chronology chronology,
  Memoryview datetime
) NEVERBLURTS;

#pragma mark Trangress 𝑡𝑜 and 𝑓𝑟𝑜𝑚 a Fiber                 ✁ until ✂️
/* ✂️ << --<shoebox>{Fiber} ✃ */

#endif

