//
//  Additions.h to Twinbeam.
//  C++2a to clang to x86_64 annd MIPS.
//  Version 6.0.0 to MIPS. (tags/RELEASE_600/final.)
//  Xcode Version 9.4 beta (9Q1019a) to x86_64.
//

#ifndef __ADDITIONS_H
#define __ADDITIONS_H

void
CastToText(
    double value,
    void (^digits)(bool neg, int e, const char *zerosToNines),
    void (^zero)(), void (^inf)(), void (^nan)()
);

double arctan(double x);
double pinecone_floor(double x);
double exp(double x);
double ln(double val);
double sqrt(double x);

#define IEEE754BASE2_64BIT_NINF   0xfff0000000000000L
#define IEEE754BASE2_32BIT_QNAN   0x7fc00000

double sin(double x); double asin(double x);
double cos(double x); double acos(double x);

int IntegerRandom(octa *x);
enum GaussianApproximate { AbramowitzStegun, ZogheibHlynka };
int Gaussian(GaussianApproximate approximate, double *out);
int Uniform(double *out); // *out ∈ [0, 1)

#pragma mark - Decorated String in Procrastinative Style

typedef struct UnicodeIntervalAndOrLocation {
    Memoryregion *region;
    Opt<__builtin_int_t> tetrasRelativeOffsetFirst;
    Opt<__builtin_int_t> tetrasRelativeOffsetLast;
} UnicodeInterval;

typedef struct UnicodeBlock {
    Memoryregion *region;
    __builtin_int_t linesOffsetFirst;
    __builtin_int_t linesOffsetLast;
} UnicodeBlock;

FINAL struct DecoratedString {
    //   ⎡      😐≅        ⎤
    //  ♢⎢    😐?😐≅😐     ⎥
    //   ⎣ 😐?😐≅😐?😐?😐?⎦
    
    DecoratedString(const char32_t *nativeEndianUnicodes, __builtin_int_t
      tetras, bool readonly);
    
    DecoratedString() = delete;
    
    Memoryview unicodes();
    
    Map<const char *, UnicodeIntervalAndOrLocation> namedRuns;
    
    // kdTreeMap<UnicodeInterval...
    
    Map<const char *, UnicodeBlock> formatting;
    
😐;

// #include <Color.hpp>
// #include <Typesetting.hpp>

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
         void (^touchbase)(uint8_t *utf8, __builtin_int_t bytes)
    ) const;
    
    virtual
    int
    password(
        __builtin_int_t periods,
        __builtin_int_t seconds,
        void (^ping)(bool &stop),
        void (^touchbase)(uint8_t *utf8, __builtin_int_t bytes)
    ) const;
    
    virtual void write(char32_t unicode) const;
    
    void (^scientificFormat)(double x, Utf8Terminal &stream);
    
😐;

enum class PresentBase { dec, hex, oct, bin };
namespace NumberFormatCatalogue { extern void (^Default)(double, Utf8Terminal&);
  extern void (^Monetary)(double, Utf8Terminal &); }
void Present(Utf8Terminal &term, __builtin_int_t z);
void Present(Utf8Terminal &term, __builtin_uint_t n, PresentBase base = PresentBase::dec);
void Present(Utf8Terminal &term, double value);
void Present(Utf8Terminal &term, char32_t unicode);
void Present(Utf8Terminal &term, DecoratedString ds);
// void Present(Utf8Terminal &term, SourceLocation location); // ☜😐: ?

#pragma mark - Conveniences for Small Clients

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_int_t z)
{ Present(term, z); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, __builtin_uint_t n)
{ Present(term, n, PresentBase::hex); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, double x)
{ Present(term, x); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, char32_t unicode)
{ Present(term, unicode); return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char *utf8) {
    __builtin_int_t bytes = Utf8BytesUntilNull(utf8, BUILTIN_INT_MAX);
    Memoryregion region { (void *)utf8, bytes };
    Memoryview content { &region, 0, region.bytes() };
    __builtin_int_t beam = 0;
    if (TokenizeUtf8OrUnicode(Encoding::utf8, content, beam,
      ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) {
          term.write(unicode);
      })) { } return term; }

MACRO Utf8Terminal & operator<<(Utf8Terminal &term, const char32_t *unicodes) {
    __builtin_int_t tetras = UnicodesUntilNull(unicodes, BUILTIN_INT_MAX);
    Memoryregion region { (void *)unicodes, tetras<<2 };
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

// MACRO Utf8Terminal & operator<<(Utf8Terminal &term, DecoratedString s)
// { Present(term, s); return term; }
// template <typename T> Utf8Terminal& operator<<(Utf8Terminal &term,
//  Vector<T> &v) { Present(v, term); return v; }
// Utf8Terminal & operator<<(Utf8Terminal &u8os, Utf8Terminal present) { return u8os; }

extern "C" { extern const char *tab; extern const char *eol; extern const char
  *sep; } // ↹ ↩︎ ¶

extern Utf8Terminal _myTerminal;

#define Termlog _myTerminal

#pragma mark - Footprint

struct AdditionsContext { volatile bool _trngInited; };

#pragma mark - Guid

typedef sexdeca Guid;

int NewGuid(void (^touchbase)(Guid *guid));

String GuidToString(Guid *guid);

String GUID();

#endif
