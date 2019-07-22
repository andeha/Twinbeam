//
//  Additions.h to Twinbeam.
//  C++2a to clang to x86_64 and MIPS.
//  Version 8.0.0 to MIPS.
//  Xcode Version 10.2.1 (10E1001) to x86_64.
//

#ifndef __ADDITIONS_H
#define __ADDITIONS_H

void
CastᵈᵇˡToText(
  double value,
  void (^digits)(bool 𝚗𝚎𝚐, int e, const char *𝟶to𝟿s),
  void (^𝚣𝚎𝚛𝚘)(), void (^𝚒𝚗𝚏)(), void (^𝚗𝚊𝚗)()
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
/* decimal128/binary128, 𝜀b₂≈log₁₀(2¹¹³)≈34.16 decimal digits, BSM */

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
  != 0 || o.ieee754b2₂.mantissal != 0) && o.ieee754b2₂.exponent == 0x7ff; } /* Exponent 
 is eleven bits. Sign not relevant; and IEEE 754-2008: MSB is `is_quiet`. */

MACRO bool isexactlyzero(double x) { octa o; o.base₂ = x; return o.bits == 
  IEEE754BASE2_64BIT_PZERO || o.bits == IEEE754BASE2_64BIT_NZERO; }

MACRO double abs64d(double x) { octa o; o.base₂ = x; o.bits &= ~SIGNBIT_INT64; 
  return o.base₂; }

MACRO Argᴾ ﹟F(double f) { return Argᴾ { .value.f₁=f, 9 }; }
MACRO Argᴾ ﹟F(float r) { return Argᴾ { .value.f₂=r, 8 }; }

#pragma mark - In-cases of an high-precision IEEE754

typedef long double ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾; /* 2⁻¹⁶³⁸² ≈ 
  3.3621 × 10⁻⁴⁹³² - 2⁻¹⁶³⁸⁴ − 2⁻¹⁶²⁷¹ ≈ 1.1897 × 10⁻⁴⁹³² */
#ifdef __x86_64__ /* ¬x86_fp80; */
typedef ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾 maxprec;
#elif defined __mips__
typedef double maxprec; /* typedef ieee754₂₀₀₈𝚋𝚒𝚗𝚊𝚛𝚢𝟷𝟸𝟾 maxprec; */
#endif

enum GaussianApproximate { AbramowitzStegun, ZogheibHlynka };
int Gaussian(GaussianApproximate approximate, double *out);
int Uniform(double *out); /* *out ∈ [0, 1) */

/* Gauss' K𝑒𝑡𝑡𝑒𝑛𝑏𝑟𝑢𝑐ℎ */
/* MACRO void Khinchin(double * A, int count, double &acc) { for (int i=count-1;
  i >= 0; i--) { acc = 1/(A[i] + acc); } } */
/* MACRO void Khinchin(double (^A)(double k), double (^B)(double k), int count,
  double &acc) { for (int i=count-1; i >= 1; i--) { acc = A(i)/(B(i) + acc); } } */
MACRO void Khinchin(double z, double (^A)(double k, double z), double (^B)(
  double k, double z), int count, double &acc) { for (int i=count-1; i >= 1;
  i--) { acc = A(i,z)/(B(i,z) + acc); } }
/* auto A𝜋 = ^(double k) { return (2*k-1)*(2*k-1); }, B𝜋 = ^(double k) { return 6.0; }; */
/* To retrieve coefficients for continued fractions, see Hardy and Wright. */

MACRO bool Similar(double x, double y, double 𝜀) { if (isinf(x) &&
  isinf(y)) return true; if (isnan(x) && isnan(y)) return true; if (
  isexactlyzero(x) && isexactlyzero(y)) return true; double diff =
  abs64d(x - y); return diff < 𝜀; }

/**  Output integer possibly in compliance with Mediterranean laws. */

int Roman(__builtin_int_t n, void (^out)(char numeral));

#pragma mark Conversions for --<Filesystem.hpp>

#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 __attribute__ ((nonnull))
__builtin_uint_t Utf8BytesUntilNull(const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8, __builtin_int_t 
  maxᵘᵗfbytes); /* Returns `maxᵘᵗfbytes` in-case NULL is not earlier found. */
__builtin_uint_t Utf8BytesIncludingANull(__builtin_int_t ³²bytes, const 
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 nativeEndianUnicodes, bool &traversedUndefinedCodepoint);
__builtin_uint_t UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶(const char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 nativeEndianUnicodes,
  __builtin_int_t maxtetras);
__builtin_uint_t UnicodesAnd𝟶𝚡𝟶𝟶𝟶𝟶(const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8, __builtin_int_t 
  maxᵘᵗfbytes); /* ...also returns `maxᵘᵗfbytes` when NULL can not be found. */

#define ⁺⁼UnicodeToUtf8(Buffer,³²B,⁸B)                                      \
auto unicodeToUtf8 = ^(char buffer[], int& ³²b, int& ⁸b) {                  \
again:                                                                      \
   if (UnicodeToUtf8(*(𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ + ³²b), ^(const uint8_t *p, int bytes) {     \
      *(buffer + ⁸b) = *p;                                                  \
      if (bytes >= 2) { *(buffer + ⁸b + 1) = *(p + 1); }                    \
      if (bytes >= 3) { *(buffer + ⁸b + 2) = *(p + 2); }                    \
      if (bytes >= 4) { *(buffer + ⁸b + 3) = *(p + 3); }                    \
      ⁸b += bytes; })) { return -1; }                                       \
   if (++³²b < 𝘁𝗲𝘁𝗿𝗮𝘀) goto again;                                            \
   *(buffer + ⁸b) = '\0';                                                   \
   return 0;                                                                \
}(Buffer, ³²B, ⁸B) /* Implicits in lambda expression: `canonicalᵚ` and `tetras`. */

#define ⁺⁼Utf8ToUnicode(U8,UCS)                                             \
auto utf8ToUnicode = ^(const char * utf8, char32_t unicodes[]) {            \
   __builtin_int_t followers, incr; int ⁸b=0, tetra /* 𝘈․𝘬․a ³²b */ = 0;    \
   char32_t uc;                                                             \
again:                                                                      \
   const char * leadOr8Bit = (const char *)utf8 + ⁸b;                       \
   if (*leadOr8Bit == 0x0) { goto unagain; }                                \
   followers = Utf8Followers(*leadOr8Bit);                                  \
   if (followers < 0) { return -2; }                                        \
   incr = followers + 1;                                                    \
   uc = Utf8ToUnicode(leadOr8Bit, incr);                                    \
   if (uc == 0xFFFE || uc == 0xFFFF) { return -3; }                         \
   /* else if (uc != U'🔗' && uc != U'@') { // streamout_unicode(uc):       \
      pathᵤC[tetra] = uc; tetra++ } else { PrintArgAndPop(uc,               \
      printedSymbolsExcept0, __arg); } */ pathᵤC₂[tetra] = uc; tetra++;     \
   ⁸b += incr; goto again;                                                  \
unagain:                                                                    \
   unicodes[tetra] = END_OF_TRANSMISSION; /* …when `ᵘᵗf⁸path` is to be      \
     parsed by machine. */ /* ⬷ Always assumed, remember to pathᵤC₂[+1] */ \
   return 0;                                                                \
}(U8,UCS) /* Implicits in lambda statement: None. */

#pragma mark Fine print for well-versed readers:

typedef struct UnicodeIntervalAnd𝑂𝑟Location {
  __builtin_int_t tetrasRelativeFirst, tetrasRelativeLast;
} UnicodeArtifact; /* See also --<Preserves.h>{Utf8Interval} */

typedef struct UnicodeBlock {
  __builtin_int_t linesOffsetFirst, linesOffsetLast;
} UnicodeBlock; /* See also --<Preserves.h>{Utf8Interval} */

#include <Additions/Knot₂.hpp>
#include <Additions/Map.hpp>

FINAL struct Ornaments { /* A․𝘬․a 'Spatialintervals' and `Intervallic`. ⇜ Also 
  suffixially pitch-associative in music. */
    /*   ⎡      😐≅        ⎤
        ♢⎢    😐?😐≅😐    ⎥
         ⎣ 😐?😐≅😐?😐?😐?⎦   */
    
    Ornaments(const char32_t *nativeEndianUnicodes,
      __builtin_int_t tetras, bool readonly);
    
    Ornaments() = delete;
    
    struct {
      
      Knot¹ᵈ<Utf8Artifact> original;
      
      Knot¹ᵈ<UnicodeIntervalAnd𝑂𝑟Location> parsed;
      
      Knot¹ᵈ<UnicodeBlock> rendered;
      
      typedef __builtin_int_t Parsedᴵᵈˣ;
      
      Map<const char32_t *, Parsedᴵᵈˣ> namedruns₁;
      
      Map<const char *, Parsedᴵᵈˣ> namedruns₂;
      
      struct {
        
        /* 𝟺𝚔𝚋Quadtreenode * quadtrees; */
        
      } elucidation;
      
    } cache;
    
    Unicodes unicodes() const;
    
😐; /* A․𝘬․a `SpatialIntervals`, `DecoratedString` and `Recording`. */

/* #include <Additions/Color.hpp>
#include <Additions/Typesetting.hpp> */

#pragma mark - The Terminal

struct Utf8Terminal {
    
    Utf8Terminal();
    
    ~Utf8Terminal();
    
    enum Inputctrl { Terminated, Timedout, Error };
    
    virtual
    Inputctrl
    interaction(
      int periods𝘖𝘳Zero,
      int ᵗᵉⁿᵗʰseconds,
      void (^ping)(bool &stop), /* Cyclically whilst time passes. */
      void (^touchbase)(char32_t unicode, bool &stop) /* After a key press. */
    ) const; /* 𝘈․k․a `interact`, `read` and `password`. */
    
    virtual int write(const uint8_t * utf8s, __builtin_int_t bytes) const;
    
    void (^scientificFormat)(double x, Utf8Terminal &stream);
    
😐;

enum class PresentBase { dec, hex, oct, bin };
namespace NumberformatCatalogue { extern void (^Default)(double, Utf8Terminal&);
  extern void (^Monetary)(double, Utf8Terminal &); }
void Present(Utf8Terminal &term, __builtin_int_t z);
void Present(Utf8Terminal &term, __builtin_uint_t n, PresentBase base);
void Present(Utf8Terminal &term, double value);
void Present(Utf8Terminal &term, char32_t unicode);
void Present(Utf8Terminal &term, const char * utf8, __builtin_int_t maxbytes=BUILTIN_INT_MAX);
/* Struct assignment ⟶ Memory copy. */
void Present(Utf8Terminal &term, const Ornaments & ds);
/* void Present(Utf8Terminal &term, UnicodeBlock location); */
/* enum Register { rtcc, dma0, … }; void Present(Utf8Terminal &term, Register reg); */
void Present(Utf8Terminal &term, const AnnotatedRegister& ar, __builtin_uint_t value);

#pragma mark - Conveniences for Small Clients

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_int_t z)
{ Present(term, z); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_uint_t n)
{ Present(term, n, PresentBase::hex); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, double x)
{ Present(term, x); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char32_t unicode)
{ Present(term, unicode); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char * utf8)
{ Present(term, utf8); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char c)
{ Present(term, (char32_t)c); return term; } /* A․𝘬․a `ascii7ToUnicode`. */

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, float x)
{ Present(term, (double)x); return term; }

MACRO
Utf8Terminal &
operator<<(
  Utf8Terminal &term,
  const char32_t * unicodesAnd𝟶𝚡𝟶𝟶𝟶𝟶
)
{ if (!unicodesAnd𝟶𝚡𝟶𝟶𝟶𝟶) { return term; }
  char32_t uc; int i=0;
again:
  uc = *(unicodesAnd𝟶𝚡𝟶𝟶𝟶𝟶 + i);
  if (uc == 0x0000) { return term; }
  Present(term, uc);
  i++; goto again;
}

/* MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const String& s) {
  __builtin_int_t tetras = s.unicodeCount(); for (int i = 0; i < tetras; i++)
  { s.unicode(i, ^(SemanticPointer<char *> prev, char32_t elem,
  SemanticPointer<char *> next) { term.write(elem); }); } return term; }
MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const Intervallic& s) 
  { Present(term, s); return term; }
template <typename T> Utf8Terminal& operator<<(Utf8Terminal &term, 
  Vector<T> &v) { Present(v, term); return v; }
Utf8Terminal & operator<<(Utf8Terminal &u8os, Utf8Terminal present) 
  { return u8os; } */

extern "C" { extern const char *tab; extern const char *eol; extern const char
  *sep; } /* ↹ ↩︎ ¶ */

extern Utf8Terminal _myTerminal;

#define Termlog _myTerminal

#pragma mark - Guids

typedef sexdeca Guid;

Guid NewGuid();

void GuidToText(const Guid& guid, void (^out)(char digitOrHyphen));

void Present(Utf8Terminal &term, const Guid& ds);
/* …and not MACRO Argᴾ ﹟Ref(Guid& g) { ⟶⟵ } */

#pragma mark - Input Feeding in Practice

enum class CastToIntOpinion { accept, rejecting, negate, commit, annul };

Opt<__builtin_int_t>
CastᵗˣᵗToInt(
  CastToIntOpinion (^feeder)(unsigned short &digit)
); /* 𝘈․𝘬․a `CastToInt`. */

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

#pragma mark F̲irst i̲n f̲irst o̲ut: Easy-bounded `Vector` …ancient: `VM-realloc`

template <typename E>
struct Fifo { /* 𝘈․𝘬․a Fifoʳᵉf and not Fifoⁱⁿcorp. */
   /* Fifo(int depth, void * base, int bytes) { content = *base; } */
   int count=0, brk=0/*𝘈․𝘬․a ⬚-idx*/, depth=10; int 🥈ᵢ MAX=100; E * content[MAX];
   void include(E * ref) { content[brk] = ref; extern void Include(int depth, 
     int * brk, int * count); Include(depth, &brk, &count); }
 /* private */ int physical(unsigned 𝛥) const { extern int Physical(unsigned 
     nowdelta /* A․𝘬․𝘢 `prevrelativehead` */, int brk, int depth);
    return Physical(𝛥, brk, depth); }
   enum Flavor { allinorder, latest };
}; /* Note also that three areas where one 'precomputed 'area always separates the 
  'producer' from the 'consumer' enables a 'stable external projection' without 
  visible fluctuations a.k.a 'flickering'; whereas two areas lead to the need 
  to induce 'lock' as well as the other contratranquistimulantic constraints. 
  'efterhandskonstruktion'/hack. (ret-ro-spect = [stimulu-tranqui-jello]). */

/*
 
 Integration using the trapezoid rule is a recursive filter: 
 
  yᵢ₊₁ = yᵢ + h (uᵢ₊₁ + uᵢ)/2
 
 as well as Simpsons rule 
 
  yᵢ₊₁ = yᵢ₋₁ + h (uᵢ₊₁ + 4uᵢ + uᵢ₋₁)/3
 
 See --<🥽 Romberg.cpp> for a ∫-method that is not on-line.
 
 */

template <typename E> bool Empty(const Fifo<E>& s) { return s.count == 0; }
template <typename E> Opt<E&> Youngest(const Fifo<E>& s) { if (s.count == 0) return 
  Opt<E&>::no(); int idx = s.physical(0); E * e = s.content[idx]; return Opt<E&>(e); }
template <typename E> Opt<E&> Oldest(const Fifo<E>& s) { if (s.count == 0) return 
  Opt<E&>::no(); int idx = s.physical(s.count - 1); E * e = s.content[idx]; 
  return Opt<E&>(e); }

template <typename E>
int Retrospect²(typename Fifo<E>::Flavor f, const Fifo<E>& fifo, E &t, E &t₋₁)
{  if (fifo.count < 2) { return -1; } int idxᵢ, idxᵢ₋₁;
    switch (f) {
    case Fifo<E>::allinorder: idxᵢ₋₁=fifo.physical(fifo.count - 1), 
      idxᵢ=fifo.physical(fifo.count - 2); break;
    case Fifo<E>::latest: idxᵢ=fifo.physical(0), idxᵢ₋₁= 
      fifo.physical(1); break;
    } t = fifo.content[idxᵢ]; t₋₁ = fifo.content[idxᵢ₋₁];
    return 0;
} /* Zero, one or two halves are always returned: struct Half { E * f,l; }; int 
  retrospect(unsigned youngs, Half &h, Half &h₋₁) { } */

#pragma mark Recollection and Associativity

struct Bitsetˢᵘᵖ { /* A․𝘬․a `Capped-ET-Bitset`. */
  
  __builtin_uint_t state;
  
  void toggle(int pos) { state ^= 1<<pos; } /* Xor₁: 'different' between two and 
    toggles one; I․𝘦 'abstract` ⟷ Xor. */
  
  __builtin_uint_t anset() { /* Xor₂: Toggles ∧ identifies 'change' simultaneously. */
     __builtin_uint_t cnt = TrailingZeros(state);
     toggle((int)cnt);
     return cnt;
  } /* Toggles a `non-toggled` bit. */
  
}; /* For --<🥽 Memclone.cpp> ∧ --<🥽 Bookshelf.cpp>. */

#pragma mark Asynchronous File Copying

int
OptimisticAsync8Copy(
  void * noncachabledst,
  void * noncachablesrc,
  int bytes,
  bool ᵗᵍᵍˡendian,
  void (^ping)(int bytes, bool &reset, bool &suspend),
  void (^error)(), void (^complete)()
); /* 𝘈․𝘬․a `Copy8Async`, `BasicTransfer`. */

#pragma mark Dispatch, Priorities and Interrupts

typedef void (^AsyncJob)(); /* A․𝘬․a `CHandler` and 𝐶𝑂𝑀𝑃𝑈𝑇𝐴𝑇𝐼𝑈𝑀. */

#pragma mark Language Translation

enum ProbedSemanticContext { Inexplainatoria, Informal, Formal };

/* int Parse(const char *utf8, void (^untangle)(char32_t unicode, 
  const Vector<int>& ss, Map<char32_t *, __builtin_uint_t>& stab,
  __builtin_int_t byteoffset, bool edge₁, bool& stop)); */

#pragma mark Trangress 𝑡𝑜 and 𝑓𝑟𝑜𝑚 a Fiber                 ✁ until ✂️
/* ✂️ << --<shoebox>{Fiber} ✃ */

#endif

