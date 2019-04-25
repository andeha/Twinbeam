//
//  Additions.h to Twinbeam.
//  C++2a to clang to x86_64 and MIPS.
//  Version 7.0.1 to MIPS.
//  Xcode Version 10.2 beta (10E125) to x86_64.
//

#ifndef __ADDITIONS_H
#define __ADDITIONS_H

void
CastToText(
  double value,
  void (^digits)(bool 𝚗𝚎𝚐, int e, const char *𝟶to𝟿s),
  void (^𝚣𝚎𝚛𝚘)(), void (^𝚒𝚗𝚏)(), void (^𝚗𝚊𝚗)()
);

/* The next smallest value after `1`. */
#define DOUBLE_EPS1  1.00000000000000011102230246251565 /* 1+2⁻⁵³ */
#define FLOAT_EPS1   1.0000000119                       /* 1+2⁻²³ …possibly 2⁻²⁴. */
#define HALF_EPS1    1.0009765625                       /* 1+2⁻¹⁰ …maybe 2⁻¹¹. */
#define Q31_EPS1     1.0000000004656612873077392578125  /* 1+2⁻³¹ */
#define Q15_EPS1     1.000030517578125                  /* 1+2⁻¹⁵ */
#define Q7_EPS1      1.0078125                          /* 1+2⁻⁷ */
#define X86FP80_EPS1 1.0000000000000000000542101        /* 1+2⁻⁶⁴ */
#define BINARY128_EPS1 1.000000000000000000000000000000000096296 /* 754-2008 */
/* decimal128/binary128, 𝜀b₂≈log₁₀(2¹¹³)≈34.16 decimal digits, BSM */
#ifdef __x86_64__
typedef long double x86_fp80;
typedef x86_fp80 maxprec;
#elif defined __mips__
typedef double maxprec;
#endif

#define IEEE754BASE2_64BIT_PZERO  0x0000000000000000L
#define IEEE754BASE2_64BIT_NZERO  0x8000000000000000L
#define IEEE754BASE2_64BIT_SNAN   0x7FF0000000000001L /* Signalling */
#define IEEE754BASE2_64BIT_PINF   0x7FF0000000000000L /* Positive */
#define IEEE754BASE2_64BIT_NINF   0xFFF0000000000000L /* Negative */
#define IEEE754BASE2_64BIT_QNAN   0x7ff8000000000000L /* Quiet */
#define IEEE754BASE2_32BIT_QNAN   0x7FC00000

MACRO bool isinf(double x) { octa o; o.base₂ = x; return o.bits ==
  IEEE754BASE2_64BIT_NINF || o.bits == IEEE754BASE2_64BIT_PINF; }

MACRO bool isnan(double x) { octa o; o.base₂ = x; return (o.ieee754b2₂.mantissah
  != 0 || o.ieee754b2₂.mantissal != 0) && o.ieee754b2₂.exponent == 0x7ff; } /* Exponent is eleven bits. Sign not relevant; and IEEE 754-2008: MSB is `is_quiet`. */

MACRO bool isexactlyzero(double x) { octa o; o.base₂ = x; return o.bits ==
  IEEE754BASE2_64BIT_PZERO || o.bits == IEEE754BASE2_64BIT_NZERO; }

MACRO double abs64d(double x) { octa o; o.base₂ = x; o.bits &= ~SIGNBIT_INT64; return o.base₂; }

enum GaussianApproximate { AbramowitzStegun, ZogheibHlynka };
int Gaussian(GaussianApproximate approximate, double *out);
int Uniform(double *out); /* *out ∈ [0, 1) */

/* Gauss' K𝑒𝑡𝑡𝑒𝑛𝑏𝑟𝑢𝑐ℎ */
/* MACRO void Khinchin(double * A, int count, double& acc) { for (int i=count-1;
  i >= 0; i--) { acc = 1/(A[i] + acc); } } */
/* MACRO void Khinchin(double (^A)(double k), double (^B)(double k), int count,
  double& acc) { for (int i=count-1; i >= 1; i--) { acc = A(i)/(B(i) + acc); } } */
MACRO void Khinchin(double z, double (^A)(double k, double z), double (^B)(
  double k, double z), int count, double& acc) { for (int i=count-1; i >= 1;
  i--) { acc = A(i,z)/(B(i,z) + acc); } }
/* auto A𝜋 = ^(double k) { return (2*k-1)*(2*k-1); }, B𝜋 = ^(double k) { return 6.0; }; */
/* To retrieve coefficients for continued fractions, see Hardy and Wright. */

MACRO bool Similar(double x, double y, double 𝜀) { if (isinf(x) &&
  isinf(y)) return true; if (isnan(x) && isnan(y)) return true; if (
  isexactlyzero(x) && isexactlyzero(y)) return true; double diff =
  abs64d(x - y); return diff < 𝜀; }

/**  Output integer possibly in compliance with Mediterranean laws. */

int Roman(__builtin_int_t n, void (^out)(char numeral));

#pragma mark - Decoration in Procrastinative Style

typedef struct UnicodeIntervalAnd𝑂𝑟Location {
  __builtin_int_t tetrasRelativeFirst;
  __builtin_int_t tetrasRelativeLast;
} UnicodeArtifact;

typedef struct UnicodeBlock {
  __builtin_int_t linesOffsetFirst, linesOffsetLast;
} UnicodeBlock;

#include <Additions/Knot.hpp>
__builtin_int_t Utf8BytesUntilNull(const char *utf8, __builtin_int_t max);
/* __builtin_int_t UnicodesUntilNull(const char *utf8, __builtin_int_t max); */
__builtin_int_t UnicodesUntilExplicitEOT(const char32_t *nativeEndianUnicodes, __builtin_int_t max); /* Required by `Map<const char32_t *, V>` */
#include <Additions/Map.hpp>

FINAL struct DecoratedString { /* A․𝘬․𝘢 `IntervallicString`. */
    /*   ⎡      😐≅        ⎤
        ♢⎢    😐?😐≅😐    ⎥
         ⎣ 😐?😐≅😐?😐?😐?⎦   */
    
    DecoratedString(const char32_t *nativeEndianUnicodes,
      __builtin_int_t tetras, bool readonly);
    
    DecoratedString() = delete;
    
    Knot<Utf8Artifact> original;
    
    Knot<UnicodeIntervalAnd𝑂𝑟Location> parsed;
    
    Knot<UnicodeBlock> rendered;
    
    typedef __builtin_int_t Parsedᴵᵈˣ;
    
    Map<const char32_t *, Parsedᴵᵈˣ> namedruns₁;
    
    Map<const char *, Parsedᴵᵈˣ> namedruns₂;
    
    /* kdTreeMap<UnicodeInterval…
      void *namedruns; Hashed const char32_t * × UnicodeArtifact
      void *formatting; Hashed const char32_t * × UnicodeBlock
      Map<const char *, UnicodeBlock> formatting; */
    
    Memoryview unicodes();
    
😐;

/* #include <Additions/Color.hpp>
#include <Additions/Typesetting.hpp> */

#pragma mark - Terminal

struct Utf8Terminal {
    
    Utf8Terminal();
    
    ~Utf8Terminal();
    
    virtual
    int
    read(
      __builtin_int_t periods,
      __builtin_int_t seconds,
      void (^ping)(bool &stop),
      void (^touchbase)(char32_t unicode, bool &stop)
    ) const;
    
    virtual
    int
    password(
      __builtin_int_t periods,
      __builtin_int_t seconds,
      void (^ping)(bool &stop),
      void (^touchbase)(char32_t unicode, bool &stop)
    ) const;
    
    virtual int write(char32_t unicode) const; /* …and not 𝚌𝚑𝚊𝚛 𝚞𝚝𝚏𝟾․ */
    
    void (^scientificFormat)(double x, Utf8Terminal &stream);
    
😐;

enum class PresentBase { dec, hex, oct, bin };
namespace NumberformatCatalogue { extern void (^Default)(double, Utf8Terminal&);
  extern void (^Monetary)(double, Utf8Terminal &); }
void Present(Utf8Terminal &term, __builtin_int_t z);
void Present(Utf8Terminal &term, __builtin_uint_t n, PresentBase base = PresentBase::dec);
void Present(Utf8Terminal &term, double value);
void Present(Utf8Terminal &term, char32_t unicode);
void Present(Utf8Terminal &term, const char * utf8);
void Present(Utf8Terminal &term, const DecoratedString& ds);
/* void Present(Utf8Terminal &term, UnicodeBlock location); */

#pragma mark - Conveniences for Small Clients

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_int_t z)
{ Present(term, z); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_uint_t n)
{ Present(term, n, PresentBase::hex); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, double x)
{ Present(term, x); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char32_t unicode)
{ Present(term, unicode); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char *utf8)
{ Present(term, utf8); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char32_t *unicodesOrEOT) {
  __builtin_int_t tetras = UnicodesUntilExplicitEOT(unicodesOrEOT, BUILTIN_INT_MAX); /* …UnicodesUntilNull may compile without warning. */
  Memoryregion region { (void *)unicodesOrEOT, tetras<<2 };
  Memoryview view { &region, 0, region.bytes() };
  __builtin_int_t beam = 0;
  if (TokenizeUtf8OrUnicode(Encoding::unicode, view, beam,
   ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) {
      term.write(unicode);
  })) { } return term; }

// MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const String& s) {
//  __builtin_int_t tetras = s.unicodeCount(); for (int i = 0; i < tetras; i++)
//  { s.unicode(i, ^(SemanticPointer<char *> prev, char32_t elem,
//  SemanticPointer<char *> next) { term.write(elem); }); } return term; }

// MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const DecoratedString& s)
// { Present(term, s); return term; }
// template <typename T> Utf8Terminal& operator<<(Utf8Terminal &term,
//  Vector<T> &v) { Present(v, term); return v; }
// Utf8Terminal & operator<<(Utf8Terminal &u8os, Utf8Terminal present) { return u8os; }

extern "C" { extern const char *tab; extern const char *eol; extern const char
  *sep; } /* ↹ ↩︎ ¶ */

extern Utf8Terminal _myTerminal;

#define Termlog _myTerminal

#pragma mark - Guid

typedef sexdeca Guid;

Guid NewGuid();

void GuidToText(Guid& guid, void (^out)(char digitOrHyphen));
/* auto ascii7ToUnicode = ^(char c) { return (char32_t)c; }; */

#pragma mark - Input Feeding in Practice

enum class CastToIntOpinion { accept, rejecting, negate, commit, annul };

Opt<__builtin_int_t>
CastToInt(
  CastToIntOpinion (^feeder)(unsigned short& digit)
);

enum class Inputcontrol { ok, quit };

enum class Readlineopinion { accept, rejecting, commit, quit };

int ReadUtf8(Readlineopinion (^feeder)(char &utf8byte), Inputcontrol (^line)
  (char * line)); int ReadUnicode(Readlineopinion (^feeder)(char32_t &unicode),
  Inputcontrol (^line)(char32_t * line)); /* Count symbols with __block inside `feeder`. */

#pragma mark Tri-cameral Tokenizer

enum class Tokenizefact { fragment, rejecting, separator, error, eol };

int
Tokenize(
  Tokenizefact (^feeder)(char32_t &unicode),
  Inputcontrol (^ahead)(char32_t * unicodes, __builtin_int_t count),
  Inputcontrol (^token)(char32_t * unicodes, __builtin_int_t count)
); /* `Tokenize` - `ReadUnicode` = Opt<𝑓𝑢𝑡𝑢𝑟𝑒 𝑡𝑒𝑛𝑠𝑒> */

#pragma mark Language Translation

enum ProbedSemanticContext { Inexplainatoria, Informal, Formal };

/* int Parse(const char *utf8, void (^untangle)(char32_t unicode, const
  Vector<int>& ss, Map<char32_t *, __builtin_uint_t>& stab,
  __builtin_int_t byteoffset, bool edge₁, bool& stop)); */

/* enum { ■ = 1, □ = 0, ⬚ = TriboolUnknown }; */

#pragma mark Trangress 𝑡𝑜 and 𝑓𝑟𝑜𝑚 a Fiber                 ✁ until ✂️

/* ✂️ << --<shoebox>{Fiber} ✃ */

#endif
