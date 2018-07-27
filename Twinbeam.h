//
//  Twinbeam.h (libTwinbeam_X_6c78989_2.a)
//  Twinbeam (C++17 for clang to x86_64 or MIPS.)
//  MIPS compiled using clang version 6.0.0 (tags/RELEASE_600/final)
//  x86_64 compiled using Xcode Version 9.4 beta (9Q1019a)
//

#ifndef __TWINBEAM_H
#define __TWINBEAM_H

#define NULL 0
#define INLINED __attribute__((always_inline))
#define MACRO inline INLINED
#define INNER_STRUCT struct __attribute__((internal_linkage))
#define INNER_UNION union __attribute__ ((internal_linkage))
#define INNER_DATA static __attribute__ ((internal_linkage))
#define INNER_FUNCTION static __attribute__ ((internal_linkage))
typedef unsigned char       uint8_t;
#ifdef  __mips__
typedef unsigned long       uint32_t;
typedef long                int32_t;
typedef uint32_t            __builtin_uint_t;
typedef int32_t             __builtin_int_t;
#define TriboolUnknown 0xFFFFFFFF
#elif defined __x86_64__
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t;
#define TriboolUnknown 0xFFFFFFFFFFFFFFFFULL
#endif
typedef unsigned short      uint16_t;
typedef short               int16_t;
typedef __builtin_uint_t Tribool;

typedef struct bignum {
  static const int maxdigits = 100; // TO AVOID: Templates, ... T
  char digits[maxdigits];         /* represent the number */
  int signbit;            /* 1 if positive, -1 if negative */
  int lastdigit;            /* index of high-order digit */
} bignum;
void print_bignum(bignum *n, void (^output)(char c));
void int_to_bignum(int s, bignum *n);
void initialize_bignum(bignum *n);
void add_bignum(bignum *a, bignum *b, bignum *c);
void subtract_bignum(bignum *a, bignum *b, bignum *c);
int compare_bignum(bignum *a, bignum *b);
void digit_shift(bignum *n, int d); /* multiply n by 10^d */
void multiply_bignum(bignum *a, bignum *b, bignum *c);
void divide_bignum(bignum *a, bignum *b, bignum *c);

#define BITMASK(type) enum : type
#ifdef  __mips__
#define mips __asm { .set noreorder; .set noat;
#elif defined __x86_64__
#define intel __asm { .intel_syntax noprefix /* Requires -fms-extensions when on llvm. */
#endif
template<typename T>
struct InnerFrame {
  InnerFrame<T>() {} T * ref_;
  // ~InnerFrame() { /* Delete ref_ in outer class destructor. */ }
  T * operator->() const { return ref_; }
  InnerFrame(T * ref) { ref_ = ref; }
};
#define APPEND_PIMPL                                                         \
  struct Implementation;                                                     \
  InnerFrame<Implementation> impl_;
#define 😐 APPEND_PIMPL }
#define VISITISR(sym) void sym(); sym();
#define UNITTEST(symbol) extern "C" void UnitTest_##symbol()
#define Panic(log,s) { printf("'%s'\nPanicking at %s in %s:%d\n",            \
  s, __FUNCTION__, __FILE__, __LINE__); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog, s); } }
extern void RunUnitTests(const char * filepath);
#define FINAL //   ⃨ or DO_NOT_DESTABBILIZE
#define LONGTOOTH
#define FOCAL
#define Si_FOCAL
#define OPT_Si_FOCAL
// #define ⚠️_IMPLIES_DOING_HARDTIME
#define ONLY_FOR_SOFT_REALTIME
#define MAY_CONTAIN_TRACES_OF_FIRM_REALTIME
#define INFLATABBLE
#ifdef  __mips__
typedef uint32_t mips32_context[32]; //  ∎: mx=11 ∧ mz=23!
typedef mips32_context jmp_buf2;     // 🔎: 32. ⛅️rax!
#elif defined __x86_64__
typedef int64_t x86_64_context[37];
typedef x86_64_context jmp_buf2;
#endif
extern "C" { int setjmp2(jmp_buf2 env); void longjmp2(void **env,
  __builtin_int_t val); /* __builtin_longjmp requires last arg to be const and is not longer than `int`. */ }
#ifdef  __mips__
#define BLURT(str) { tetra t; t.tetra = (uint32_t)(const char *)str;         \
  longjmp2((void **)*JmpBuf(), int(t.unsigned_little_endian.lsh)); }
#elif defined __x86_64__
#define BLURT(str) { octa o; o.octa = (uint64_t)(const char *)str;           \
  longjmp2((void **)*JmpBuf(), int(o.unsigned_little_endian.lst)); }
#endif
#define BLURTS /* Mandatory */
#define NEVERBLURTS /* Fortunately optional. */
#define FALLIBLE /* Unfortunately not mandatory while the constructor gently blurts. */
#define TRY { int __e = setjmp2(*JmpBuf()); if (!__e) {
#define CATCH } else {
#define END_TRY } }
extern "C" jmp_buf2 * /* volatile */ JmpBuf(); /* ⬷ A great symbol for a break! */
struct SharedOptional { bool populated; explicit SharedOptional() : populated(
  false) { } explicit operator bool() const { return populated; } };
#ifdef  __mips__
typedef unsigned int size_t;
void * operator new(unsigned int size, void * here) noexcept;
#elif defined __x86_64__
typedef unsigned long size_t;
void * operator new(unsigned long size, void * here) noexcept;
#endif
template <typename T> struct Opt : public SharedOptional { explicit Opt(const
  T& v) { new (content) T(v); populated = true; } explicit Opt() = default; Opt(
  const Opt<T>& other) { populated = other.populated; if (populated) { new
  (content) T((const T&)(other.content)); } } ~Opt() { reinterpret_cast<T *>(
  content)->~T(); } alignas(T) uint8_t content[sizeof(T)]; T& operator*() const;
  T * operator->() const { return &(**this); } static Opt no() { return Opt(); } };
template <typename T> struct Opt<T&> : public SharedOptional { explicit Opt(
  const T& v) { new (content) T(v); populated = true; } explicit Opt() = default;
  Opt(const Opt<T>& other) { populated = other.populated; if (populated) { new
  (content) T((const T&)(other.content)); } } ~Opt() { reinterpret_cast<T *>(
  content)->~T(); } alignas(T) uint8_t content[sizeof(T)]; T& operator*() const;
  T * operator->() const { return &(**this); } static Opt no() { return Opt(); } };
template <class... Ts> struct Tuple {}; template <class T, class... Ts>
  struct Tuple<T, Ts...> : Tuple<Ts...> { Tuple(T t, Ts... ts) : Tuple<Ts...>
  (ts...), tail(t) {} T tail; };
  template <__builtin_uint_t, class> struct elem_type_holder; template <class T,
  class... Ts> struct elem_type_holder<0, Tuple<T, Ts...>> { typedef T type; };
  template <__builtin_uint_t k, class T, class... Ts>
  struct elem_type_holder<k, Tuple<T, Ts...>> { typedef typename
  elem_type_holder <k - 1, Tuple<Ts...>>::type type; };
  template <bool, typename T = void> struct std__enable_if {};
  template <typename T> struct std__enable_if<true, T> { typedef T type; };
  template <__builtin_uint_t k, class... Ts>
  typename std__enable_if<k == 0, typename elem_type_holder<0, Tuple<Ts...>>::
  type&>::type get(Tuple<Ts...>& t) { return t.tail; }
  template <__builtin_uint_t k, class T, class... Ts> typename std__enable_if<k
  != 0, typename elem_type_holder<k, Tuple<T, Ts...>>::type&>::type
  get(Tuple<T, Ts...>& t) { Tuple<Ts...> &base = t; return get<k-1>(base); }
template <class ...T> Tuple<T...> Tie(T... t) { return Tuple<T...>(t...); }      /* ☜😐: 🔅 ⬷ 𝘋𝘰 𝑛𝑜𝑡 move sun. */
namespace std { // The Standard Residual
  typedef ::size_t size_t; template<class T> class initializer_list {
  const T *beg; size_t sz; initializer_list(const T * b, size_t s) : beg(b),
  sz(s) {} public: typedef T value_type; typedef const T& reference; typedef
  const T& const_reference; typedef size_t size_type; typedef const T *
  iterator; typedef const T * const_iterator; initializer_list() : beg(0), sz(0)
  {} size_t size() const { return sz; } const T * begin() const { return beg; }
  const T * end() const { return beg + sz; } }; template<class T> inline const T
  * begin(std::initializer_list<T> i) { return i.begin(); } template<class T>
  inline const T * end(std::initializer_list<T> i) { return i.end(); } }
// template <typename T> struct SemanticPointer { T * pointer; };
// template <> struct SemanticPointer<const char32_t *> { const char32_t ** pointer; const char32_t * dereference() { return *pointer; } };
template <typename T> struct SemanticPointer { T pointer; };
/* ☜😐: 🔅 ⬷ Earlier remark still valid? */
/* ☜😐: 🔅 ⬷ Earlier remark still valid? */
struct Memoryregion; struct Memoryview { Memoryregion *
  region; __builtin_int_t bytesOffset; __builtin_int_t byteCount; };
MACRO __builtin_uint_t 🔎(__builtin_uint_t var) { return *((__builtin_uint_t
  /* volatile */ *) var); }
MACRO __builtin_uint_t&  🔧(__builtin_uint_t var) { return (__builtin_uint_t&)
  *(__builtin_uint_t /* volatile */ *)var; }
MACRO __builtin_uint_t TrailingZeros(__builtin_uint_t x) { if (x == 0) { return
  8*sizeof(x); } __builtin_uint_t zeros = 0, mask = 1; while (!(x&mask)) {
  zeros++; mask<<=1; } return zeros; }
inline __builtin_uint_t MaskAndShift(__builtin_uint_t value, __builtin_uint_t
  mask) { __builtin_uint_t shift = TrailingZeros(mask); return (mask&value) >>
  shift; }
MACRO __builtin_uint_t 🔎MaskandShift(__builtin_uint_t var, __builtin_uint_t
  mask) { return MaskAndShift(🔎(var), mask); }
MACRO void 🔧(__builtin_uint_t var, __builtin_uint_t mask, __builtin_uint_t
  value) { __builtin_uint_t shift = TrailingZeros(mask); __builtin_uint_t
  secured = value & (mask>>shift); *(__builtin_uint_t *)var &= ~mask;
  *(__builtin_uint_t *)var |= secured<<shift; }
MACRO void 🔧Toggle(__builtin_uint_t var, __builtin_uint_t mask) {
  __builtin_uint_t shift = TrailingZeros(mask); __builtin_uint_t secured =
  mask>>shift; *(__builtin_uint_t *)var ^= secured<<shift; }
extern "C" { void * malloc(size_t); void free(void *); int printf(const char
  *utf8format, ...); int atexit(void (*func) (void)); void exit(int); }
int
bprintf_utf8(
    unsigned short (^utf8)(char *p, short unsigned bytes),
    const char *utf8Format,
    __builtin_va_list arg
);
int // Tuple<int, int, int> i.e user-percieved characters, unicodes and utf-8.
bprintf_unicode(
    unsigned short (^utf8)(char *p, short unsigned bytes),
    const char32_t *unicodeFormat,
    __builtin_va_list arg
);			
typedef __builtin_uint_t * WordAlignedRef; typedef uint8_t * ByteAlignedRef;
#ifdef __x86_64__
FOCAL MACRO ByteAlignedRef /* µA("x86_64", "haswell", x₁, x₂) */ Copy8Memory(
  ByteAlignedRef dst, /* const */ ByteAlignedRef src, __builtin_int_t bytes) {
  ByteAlignedRef org = dst; __asm__ __volatile__ ("rep movsb" : "+D"(dst),
  "+S"(src), "+c"(bytes) : : "memory"); return org; }  // i.e `memcpy`
  #include <xmmintrin.h>  // ≥ SSE 4.2
  #include <immintrin.h>  // AVX and AVX2 from avxintrin.h and avx2intrin.h
FOCAL int  /* µA("Compare", "x86_64", "haswell", x₁, x₂) */ __attribute__((
  target("sse4.2"))) Compare8Memory(ByteAlignedRef l, ByteAlignedRef r,
  __builtin_uint_t bytes);
#define MEASURE_START(prefix) int64_t prefix##Start = __rdtsc();
#define MEASURE_END(prefix)                                                  \
  int64_t prefix##End = __rdtsc();                                           \
  int64_t prefix##Nanos = prefix##End - prefix##Start;                       \
  printf(#prefix " measures %lld ns\n",  prefix##Nanos);
#elif defined __mips__
FOCAL ByteAlignedRef /* µA("mips", "r2", x₃, x₄) */ Copy8Memory(ByteAlignedRef
  dst, ByteAlignedRef src, __builtin_int_t bytes);
FOCAL int /* µA("mips", "r2", x₃, x₄) */ Compare8Memory(ByteAlignedRef l,
  ByteAlignedRef r, __builtin_uint_t bytes); // i.e `memcmp`
#define PIC32SYMBOL(serie,symbol,vaddr)                                      \
  constexpr uint32_t PIC32##serie##_##symbol = vaddr;                        \
  constexpr uint32_t PIC32##serie##_##symbol##CLR = (vaddr + 0x4);           \
  constexpr uint32_t PIC32##serie##_##symbol##SET = (vaddr + 0x8);           \
  constexpr uint32_t PIC32##serie##_##symbol##INV = (vaddr + 0xC);
#define PortRectifyAsOutputs(serie,X,tris) (*((uint32_t *)PIC32##serie##_##TRIS##X##CLR) = (uint16_t)(tris))
#endif
ByteAlignedRef Clear8Memory(ByteAlignedRef mem, __builtin_int_t bytes);
ByteAlignedRef Overwrite8Memory(ByteAlignedRef src, uint8_t val,
  __builtin_int_t bytes);
MACRO __builtin_int_t Frame(__builtin_uint_t size, __builtin_uint_t framesize) {
  return (size + framesize - 1) & ~(framesize - 1); }
MACRO __builtin_int_t HowMany(__builtin_uint_t index, __builtin_uint_t width) {
  return (index % width == 0) ? index/width : index/width + 1; }
#define Block_copy(...) ((__typeof(__VA_ARGS__))_Block_copy((const void *)(__VA_ARGS__)))
#define Block_release(...) _Block_release((const void *)(__VA_ARGS__))
struct Block_descriptor { unsigned long int reserved; unsigned long int size;
  void (*copy)(void *dst, void *src); void (*dispose)(void *); };
struct Block_layout { void *isa; int flags; int reserved; void (*invoke)(void *,
  ...); struct Block_descriptor *descriptor; /* Imported variables. */ };
MACRO void * _Block_copy(const void *arg) { struct Block_layout *block = (struct
  Block_layout *)arg; struct Block_layout *res = (struct Block_layout *)malloc(
  block->descriptor->size); Copy8Memory((ByteAlignedRef)res, (ByteAlignedRef)
  block, block->descriptor->size); return res; }
MACRO void _Block_release(const void *arg) { free((void *)arg); }
typedef __builtin_uint_t BinaryChoice; BITMASK(BinaryChoice) {
  BinaryChoiceToLeft = 0b0, BinaryChoiceToRight = 0b1 };
MACRO __builtin_int_t SystemInfoPagesize() { return 4096; }
#define NEVERBLURTS /* Fortunately undefined for script, kiddies. */
#ifdef  __mips__
typedef uint32_t mips32_context[32];
typedef mips32_context jmp_buf;
#elif defined __x86_64__
typedef int64_t x86_64_context[(9 * 2) + 3 + 16];
typedef x86_64_context jmp_buf;
#endif
FOCAL void Base(/* TeX §64, §65 and §67 */ __builtin_uint_t n, unsigned
  short base, unsigned short digitsOr0, /* Not more than 32 or 64 digits 
  depending on word size! (Or set to `0` to skip leading zeros.) */ void 
  (^output)(char utf8)); 
FOCAL void Base(__builtin_int_t z, unsigned short base, unsigned short 
  digitsOr0, void (^output)(char utf8));
template <typename T> T abs(T x) { return x < 0 ? -x : x; }
#define SIGNBIT_INT32 0x80000000
#define SIGNBIT_INT64 0x8000000000000000L
#define abs32i(x) int32_t(((uint32_t)(x) & ~SIGNBIT_INT32))
#define abs64i(x) int64_t(((uint64_t)(x) & ~SIGNBIT_INT64))

#pragma mark - 📖😐 ”𝑈𝑛𝑖𝑐𝑜𝑑𝑒”

typedef struct Impression {
  Memoryview unicodes;
  __builtin_int_t tetrasOffset;
  __builtin_int_t tetrasCount;
} Impression; // i.e a grapheme cluster or a user-percieved character.

typedef struct Twinbeam {
  Memoryview unicodes;
  __builtin_int_t tetrasOffset;
  SemanticPointer<char32_t *>
  unicodeLook(
    __builtin_uint_t unicodesAhead,
    BinaryChoice direction
  ) const;
  enum Segmentation { unicode, grapheme, word, sentence, line };
  void
  perceives(
    __builtin_uint_t impressionsAhead,
    Segmentation segmentation, 
    BinaryChoice direction,
    void (^touchbase)(Impression * character)
  ) const;
} Twinbeam;

void TwinbeamInit(Twinbeam *beam, Memoryview unicodes, bool atEnd);

int Next(Twinbeam *beam, Twinbeam::Segmentation segmentation, BinaryChoice
  direction, __builtin_uint_t steps);

#pragma mark Unicode Comparision (i.e compatibility decomposition, followed by canonical composition, a.k.a NFKC.)

bool CaseSensitiveIsEqual(const char32_t *l, const char32_t *r);

INFLATABBLE
int 
UnicodeNonapproximativeCompare(
  const char32_t *l, const char32_t *r,
  __builtin_int_t tetras,
  void (^completion)(Tribool isEqual) /* = ^(bool isEqual) { } */,
  bool (^acceptable)(char32_t l, char32_t r, bool& stop) /* =
    ^(char32_t l, char32_t r, bool& stop) { return false; } */,
  void (^preproc)(char32_t l, char32_t r, void (^out)(char32_t lo, char32_t ro)),
  void (^ping)(bool& stop) /* = ^(bool& stop) { } */); // The roman numerial IV annd U+2164.

#pragma mark Unicode Querying

char32_t SubstituteToAlwaysVisible(char32_t c, bool isString);
bool SeparatesWords(char32_t c);
bool SeparatesSentences(char32_t c);
bool IsWhitespace(char32_t c, bool evenNonBIDL = false);

#pragma mark Unicode Casing

enum class Language { English, Lithuanian, Maltese };
void Titlecase(Language lang, Memoryview row, void (^output)(char32_t out));
void Uppercase(Language lang, char32_t u, void (^output)(char32_t out));
void Lowercase(Language lang, char32_t u, void (^output)(char32_t out));
void Casefold(Language lang, char32_t l, char32_t r, void (^output)(char32_t l,
  char32_t r)); //  ⃨ for caseless matching.
bool CaseInsensitiveIsEqual(Language lang, const char32_t *l, const char32_t *r);

#pragma mark Unicode Collation (Determine sorting order for a sequence-pair.)

Tribool UnicodeLT(Language lang, Memoryview l, Memoryview r);

#pragma mark Characters (i.e. 'Splines 'n Stuff')

struct UnicodeCategory {
  
  enum Symbol { mark, number, punctuation, symbol, separator, uppercase,
    lowercase, titlecase, nonspacing, spacingCombining, enclosing,
    decimalDigit, connector, dash, open, close, initialQuote, finalQuote,
    math, currency, space, line, paragraph, control, format, surrogate,
    privateUse, notAssigned, letter, modifier, other };
  
  Symbol master, subcat;
};

struct CharacterInfo {
  char32_t look;
  const char *names[4];
  UnicodeCategory category;
  short unsigned combiningclass; // (0..254) Only combining marks have a combining class other than zero. I.e non-combining = 0,
  const char *refs; // Sorted sequence of notable chars
};

int UnicodeData(char32_t c, void (^touchbase)(CharacterInfo * info));

MACRO const char * UnicodePrimaryName(char32_t c) {
  __block const char * res;
  if (UnicodeData(c, ^(CharacterInfo * info) {
    res = info->names[0];
  })) { return NULL; }
  return res;
}

#pragma mark Utf-8

enum class Encoding { utf8, unicode };

__builtin_int_t Utf8Followers(uint8_t leadOr8Bit);

char32_t Utf8ToUnicode(uint8_t *p, __builtin_int_t bytes);

int TokenizeUtf8OrUnicode(Encoding encoding, Memoryview content,
  __builtin_int_t& beam, void (^character)(char32_t unicode, __builtin_int_t
  byteOffset, bool& stop));

int Utf8Sync(uint8_t **p); // Backs at most 3 bytes to regain sync.

int UnicodeToUtf8(char32_t u, void (^completion)(const uint8_t *p, int bytes));

#pragma mark - ”𝑇ℎ𝑒 🧠🧠” 🔍😐

typedef __builtin_uint_t metaaddress;

struct MemoryDelegate { struct Memoryregion; virtual void statistics() = 0; };

struct Memoryregion {
    
    Memoryregion(MemoryDelegate * delegate);
    
    Memoryregion(void *p, __builtin_int_t bytes, MemoryDelegate * delegate = NULL);
    
    ~Memoryregion();
    
    void incorporate(void *virtue, __builtin_int_t bytes, metaaddress loc);
    
    int inject(__builtin_int_t index, const Memoryregion& src, void *(^allocate)
      (__builtin_int_t bytes) /* = ^(__builtin_int_t b) { return malloc(b); } */);
    
    int exclude(metaaddress start, __builtin_int_t bytes);
    
    int takeover(Memoryregion& virtue, metaaddress loc);
    
    SemanticPointer<void *> pointer(__builtin_int_t byte) const;
    
    __builtin_int_t bytes() const;
    
    void alsoAtDealloc(void (^deferral)()); // ☜😐: 🛵𝜆
    
#pragma mark Little and Big Endians
    
    /**  TODO: Measure energy consumption while 𝑝𝑢𝑚𝑝𝑖𝑛' 𝑛𝑒𝑡𝑤𝑜𝑟𝑘/𝑛𝑎𝑡𝑖𝑣𝑒. */
    
    INLINED void toggleNetworkAndNative(void (^ping)(bool &stop), void
      (^completion)(__builtin_int_t bytes)); // REQ: O(1)
    
#pragma mark Fields of Capacitors
    
    static Opt<Memoryregion> abduct(__builtin_int_t bytes, MemoryDelegate *
      delegate = NULL, bool allowWrites = true, void *(^allocate)(
      __builtin_int_t bytes) = ^(__builtin_int_t bytes) { return malloc(bytes); });
    
    static Opt<Memoryregion> reflect(const char * utf8Filepath,
      __builtin_int_t pagesOffset = 0, __builtin_int_t pagesLength = 0,
      MemoryDelegate *delegate = NULL, bool allowWrites = false,
      void *(^allocate)(__builtin_int_t bytes) = ^(__builtin_int_t bytes) {
      return malloc(bytes); });
    
#pragma mark Memory Mangement
    
    Memoryregion() = delete;
    
    Memoryregion(const Memoryregion& other);
    
😐; // Pimpl optional because of opaque, mandatory since alsoAtDealloc.

void * ExactSeek(const void *key, const void *base, size_t num, size_t size,
  __builtin_int_t (^cmp)(const void *key, const void *elt));

typedef union {
    double base2; // 2^–1022  2^1023 or 2.23 × 10^–308 to 1.79 × 10^308
    struct { uint32_t lst; int32_t mst; } signed_little_endian;
    struct { int32_t mst; uint32_t lst; } signed_big_endian;
    struct { uint32_t lst; uint32_t mst; } unsigned_little_endian;
    struct { uint32_t mst; uint32_t lst; } unsigned_big_endian;
    struct {
        unsigned mantissal : 32;
        unsigned mantissah : 20;
        unsigned exponent  : 11;
        unsigned sign      :  1;
    } ieee754;
#ifdef __x86_64__
    uint64_t octa;
#endif
} octa;

#ifdef __x86_64__
typedef __m128 __builtin_treeint_t;
#elif defined __mips__
typedef octa uint64_t;
typedef octa int64_t;
typedef int64_t __builtin_treeint_t; // Note: Is signed!
#endif

void * Insert(void *opaque, __builtin_treeint_t data, void * ref); // Consider __builtin_treeint_t as ref. See `Unittests`.
void * Lookup(void *opaque, __builtin_treeint_t target); void Forall(void *
  opaque, void (^dfs)(void * ref, bool& stop, __builtin_treeint_t mask, void * 
  node));

template <typename T> T * materialize(Memoryview * view) {
  extern void * 💫(void *); return (T *)💫((void *)view); }

// template <> Unicodestring materialize(MemoryView * view) { 
//   return Unicodestring(Endianness::Native, 💫(view), view.bytesCount, 
//   true, alloc); }

extern void * (^alloc)(__builtin_int_t); // Since ^ ∧ =alloc sometimes 💥

enum class Endianness { Native, Network };

#pragma mark - 😐🎤💀 ”𝑇ℎ𝑒 ⚰️”

#define va_epilogue __builtin_va_end(arg);
#define va_prologue(symbol)            \
  __builtin_va_list arg;               \
  __builtin_va_start(arg, symbol);

struct String {
    
    /**
     
     Given a traditional null-terminated utf-8 character sequence, create
     an owning read-only `String` instance.
     
     */
    
    static String Literal(const char *utf8, ...);
    
    /**   Copy a 𝑏𝑙𝑜𝑐𝑘 of unicodes and create an owning `String`. */
    
    static
    String
    PossiblyMeasuredLiteral(
        const char32_t *nativeEndianUnicodes,
        __builtin_int_t tetrasOrMinusOne, // -1 indicates loop until NULL.
        bool readonly,
        void * (^allocate)(__builtin_int_t bytes) /* = ^(__builtin_int_t bytes)
          { return malloc(bytes); } */
    );
    
    /**  Creates an already measured or truncated @c String. */
    
    static
    String
    PossiblyMeasuredLiteral(
        const char *utf8,
        __builtin_int_t bytesOrMinusOne, // -1 indicates loop until NULL.
        bool readonly,
        __builtin_va_list arg,
        void * (^allocate)(__builtin_int_t bytes) /* = ^(__builtin_int_t bytes)
          { return malloc(bytes); } */
    );
    
    /**  As String::Literal, but creates an owning writable instance. */
    
    static String FluctuantLiteral(const char *utf8, ...);
    
#pragma Iterators
    
    int
    unicode(
        __builtin_int_t unicodeIndex,
        void (^touchbase)(SemanticPointer<char *> prev, char32_t elem,
          SemanticPointer<char *> next)
    ) const;
    
    int
    utf8(
        __builtin_int_t utf8Index,
        void (^touchbase)(char * elem, unsigned short count) // 1 - 4 bytes.
    );
    
    Memoryview operator*() const; // O(1)
    
    __builtin_int_t unicodeCount() const; __builtin_int_t utf8Count() const;
    
    /**  Return the empty string. */
    
    static String epsilon(bool readonly = false);
    
    bool empty() const;
    
#pragma mark Misc
    
    void alsoAtDealloc(void (^deferral)()); // ☜😐: 🛵𝜆
    
    int replace(Memoryview range, const char32_t *withNativeEndianUnicodes,
      __builtin_int_t count, void *(^allocate)(__builtin_int_t bytes) = ^(
      __builtin_int_t bytes) { return malloc(bytes); } );
    
    ~String();
    
    String(const String& other);
    
    String(
        const char32_t *nativeEndianUnicodes,
        __builtin_int_t tetras,
        bool readonly
    );
    
😐; // Note that NULL must not be a vaild unicode character and in PossiblyMeasuredLiteral does indicate end of string.

#define StringLiteral String::Literal
#define FluctuantLiteral String::FluctuantLiteral

LONGTOOTH
MACRO
String
Concaternate(
    const String& l, const String& r,
    void *(^allocate)(__builtin_int_t bytes) /* = ^(__builtin_int_t bytes) {
      return malloc(bytes); } */
)
{
    __builtin_int_t bl = l.unicodeCount() << 2, br = r.unicodeCount() << 2;
    const char32_t *nativeEndianUnicodes = (char32_t *)allocate(bl + br);
    Copy8Memory((ByteAlignedRef)nativeEndianUnicodes, (ByteAlignedRef)((*l).
      region->pointer(0).pointer), bl);
    Copy8Memory((ByteAlignedRef)(nativeEndianUnicodes + bl),
      (ByteAlignedRef)((*r).region->pointer(0).pointer), br);
    return String::PossiblyMeasuredLiteral(nativeEndianUnicodes, (bl + br)>>2, 
      true, allocate);
}

MACRO
void
Append(
    String& s,
    char32_t c
)
{
    Memoryview view = *s;
    s.replace(Memoryview { view.region, s.unicodeCount(), 0 }, (const char32_t 
    *)&c, 1, alloc);
}

ONLY_FOR_SOFT_REALTIME MACRO String operator+(const String& l, const String& r)
{ return Concaternate(l, r, alloc); }

__builtin_int_t UnicodesUntilNull(const char *utf8, __builtin_int_t max);
__builtin_int_t UnicodesUntilNull(const char32_t *nativeEndianUnicodes,
  __builtin_int_t max);
__builtin_int_t Utf8BytesUntilNull(const char *utf8, __builtin_int_t max);

#pragma mark - ”𝑇ℎ𝑒 𝑉𝑒𝑐𝑡𝑜𝑟” 🤲

template <typename T> struct Sequence {
    virtual __builtin_int_t count() const = 0;
    virtual int dereference(__builtin_int_t idx, void (^touchbase)(SemanticPointer<T *> elem)) const = 0;
    MACRO int forall(void (^block)(SemanticPointer<T *> elem, bool first, bool last,
        __builtin_int_t idx, bool& stop)) const { // TODO: _∀(void ...) ⟷ Touchbar
        __builtin_int_t itemCount = count();
        __builtin_int_t idx = 0;
    again:
        if (idx < itemCount) {
            __block bool innerStop;
            if (dereference(idx, ^(SemanticPointer<T *> elem) {
                block(elem, idx == 0, idx == itemCount - 1, idx, innerStop);
            }))
            {
                return -2;
            }
            if (innerStop) { return -1; }
            idx++;
            goto again;
        }
        return 0;
    }
};

template <typename T, typename C = Sequence<T>> struct Mitigate : public Sequence<T> {};
    
template <typename T>
struct Vector : public Mitigate<T, Vector<T>> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Vector(std::initializer_list<T> l) :
    Vector(l.size()/sizeof(T), alloc) { const T * i = l.begin(); const T *
    const end = l.end(); for (; i != end; ++i) push(*i); }
    
    Vector() : Vector(0, alloc) { }
    
    Vector(__builtin_int_t count, void * (^alloc)(__builtin_int_t) /* = ^(
      __builtin_int_t bytes) { return malloc(bytes); } */ ) { allocate = alloc;
      occupied = 0; plate(count*sizeof(T)); }
    
    Vector(const Vector& other) { for (__builtin_int_t i = 0; i <
      other.count(); i++) { this->operator[](i) = other[i]; } }
    
    MAY_CONTAIN_TRACES_OF_FIRM_REALTIME
    void push(const T& x) {
        __builtin_int_t bytesUsed = sizeof(T) * (1 + occupied);
        if (bytesUsed >= bytesAvailable) plate(bytesUsed - bytesAvailable);
        T& e = at(occupied);
        Copy8Memory((ByteAlignedRef)&e, (ByteAlignedRef)&x, sizeof(T)); // Does not have to e well-defined in case dst ∩ src ≠ ∅ since copying to pristine cells.
        occupied++;
    }
    
    __builtin_int_t occupied; metaaddress bytesAvailable = 0x0000000000000000;
    
    void *opaque = NULL; void * (^allocate)(__builtin_int_t);
    
    void plate(__builtin_int_t bytes);
    
    void pop() { if (occupied > 0) occupied--; }
    
    Opt<T> top() const { if (occupied) { return Opt<T>(this->operator[](
      occupied - 1)); } return Opt<T>::no(); }
    
    int dereference(__builtin_int_t idx, void (^touchbase)(SemanticPointer<T *>
      elem)) const {
        __builtin_int_t pagesize = SystemInfoPagesize();
        __builtin_int_t startIdx = (idx*sizeof(T))/pagesize;
#ifdef __x86_64__
        __builtin_treeint_t mask = _mm_set_epi64x(0x0, (uint64_t)startIdx);
#elif defined __mips__
        __builtin_treeint_t mask; mask.unsigned_little_endian.lst = startIdx;
#endif
        void *x = Lookup(opaque, mask);
        T * plate = (T *)x;
        touchbase(SemanticPointer<T *> { plate + (idx - startIdx)*sizeof(T) });
        return 0;
    }
    
    T& at(__builtin_int_t idx) const {
        __block T * elem = NULL;
        if (dereference(idx, ^(SemanticPointer<T *> e) {
            elem = e.pointer;
        })) {}
        return (T&)(*elem);
    }
    
    T& operator[](__builtin_int_t idx) { return at(idx); }
    
    const T& operator[](__builtin_int_t idx) const { return const_cast<T&>(at(
      idx)); }
    
    __builtin_int_t count() const { return occupied; }
    
    bool empty() const { return count() == 0; }
    
    int elements(void (^block)(SemanticPointer<T *> elem, bool& stop)) const {
      int ret = this->forall(^(SemanticPointer<T *> elem, bool first, bool last,
      __builtin_int_t idx, bool& stop) { block(elem, stop); }); return ret; }

};

ONLY_FOR_SOFT_REALTIME
template <typename T>
void
Vector<T>::plate(__builtin_int_t bytes)
{
    if (bytes == 0) return;
    __builtin_int_t pagesize = SystemInfoPagesize();
    __builtin_int_t plates = HowMany(bytes, pagesize);
    __builtin_int_t totPages = bytesAvailable / pagesize;
    __builtin_int_t objsPerPage = pagesize/sizeof(T);
    // __builtin_int_t drossPerPage = pagesize - sizeof(T)*objsPerPage;
    
    for (__builtin_int_t i = 0; i < plates; i++) {
        T * plate = (T *)allocate(pagesize);
#ifdef __x86_64__
        uint64_t idxFirst = objsPerPage*(totPages + i);
        __builtin_treeint_t mask = _mm_set_epi64x(0x0000000000000000, idxFirst);
#elif defined __mips__
        uint32_t idxFirst = objsPerPage*(totPages + i);
        octa mask; mask.unsigned_little_endian.lst = idxFirst;
#endif
        opaque = Insert(opaque, mask, plate);
        bytesAvailable += Frame(occupied*sizeof(T), pagesize);
    }
}

#pragma mark - 🗺 ”𝑇ℎ𝑒 𝑀𝑎𝑝”

typedef union {
#ifdef __x86_64__
    __m128 sexdeca;
    __m128i twoOcta;
    __m128d twoDoubles;
#endif
    struct { int64_t lso; uint64_t mso; } signed_little_endian;
    struct { int64_t mso; uint64_t lso; } signed_big_endian;
    struct { uint64_t lso; uint64_t mso; } unsigned_little_endian;
    struct { uint64_t mso; uint64_t lso; } unsigned_big_endian;
} sexdeca;

typedef union {
#ifdef __x86_64__
    __m256 ditriaconta;
#endif
    uint32_t eighttetra[8];
    uint8_t thirtytwobytes[32];
    struct { sexdeca lss; sexdeca mss; } little_endian;
    struct { sexdeca mss; sexdeca lss; } big_endian;
} ditriaconta;

/**  Computes a cryptographic hash value similar to NIST FIPS PUB 180-4:
  "Secure Hash Standard (SHS)", August 2015. */

int Hash(uint8_t *p, __builtin_int_t bytes, void (^ping)(bool &stop), void
  (^completion)(ditriaconta digest));

template<typename V>
struct SharedMap {
    
    SharedMap(void * (^alloc)(__builtin_int_t)) { SharedMap<V>::allocate = alloc; }
    
    MAY_CONTAIN_TRACES_OF_FIRM_REALTIME
    void treeInsert(__builtin_treeint_t mask, const V& value) {
        __builtin_int_t bytes = sizeof(value);
        void *content = allocate(bytes);
        Copy8Memory((ByteAlignedRef)content, (ByteAlignedRef)&value, bytes); // As fast as possible or well-defined in-case dst ∩ src ≠ ∅. static_assert if overlapping?
        opaque = Insert(opaque, mask, content); // Consider odd pointer to tree as 'deleted'
    }
    
    V * find(__builtin_treeint_t mask) const { void *x = Lookup(opaque, mask);
      return (V *)x; }
    
    void dfs(void (^visit)(V& value, bool& stop, void * node)) { Forall(opaque,
      ^(void * ref, bool& stop, __builtin_treeint_t mask, void * node) { visit((
      V&)ref, stop, node); }); }
    
    void *opaque = NULL; void * (^allocate)(__builtin_int_t);
};

typedef union {
    float base2; // 2^–126 to 2^127 or 1.18 × 10^–38 to 3.40 × 10^38
    struct { int16_t lsh; uint16_t msh; } signed_little_endian;
    struct { int16_t msh; uint16_t lsh; } signed_big_endian;
    struct { uint16_t lsh; uint16_t msh; } unsigned_little_endian;
    struct { uint16_t msh; uint16_t lsh; } unsigned_big_endian;
    struct {
        unsigned mantissa : 23;
        unsigned exponent :  8;
        unsigned sign     :  1;
    } ieee754;
    struct {
        unsigned value : 31;
        unsigned sign  :  1;
    } signed_tetra;
    uint32_t tetra;
} tetra;

template <typename T> T& Opt<T>::operator*() const { if (populated) return
  (T&)content; BLURT("Bad optional access"); for (;;); }
template <typename T> T& Opt<T&>::operator*() const { if (populated) return
  (T&)content; BLURT("Bad optional access"); for (;;); }

template <typename K, typename V>
struct Map : public SharedMap<V> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Map(std::initializer_list<Tuple<K, V>> l)
      : Map() { const Tuple<K, V> * i = l.begin(); auto end = l.end(); for (;
      i != end; ++i) this->include(get<0>(*(Tuple<K, V> *)i), get<1>(*(Tuple<K,
      V> *)i), true); }
    
    Map() : SharedMap<V>(alloc) { }
    
    Map(const Map<K, V>& other) : SharedMap<V>(alloc) {
        Forall(other.opaque, ^(__builtin_treeint_t mask, void * ref) {
            SharedMap<V>::treeInsert(mask, (V &)ref);
        });
    }
    
    void seek(const K& key, void (^completion)(__builtin_treeint_t mask, V *
      found)) const { if (Hash((uint8_t *)&key, sizeof(key), ^(bool &stop) { },
          ^(ditriaconta digest) {
#ifdef __x86_64__
            __builtin_treeint_t mask = digest.little_endian.lss.sexdeca;
#elif defined __mips__
            __builtin_treeint_t mask = digest.little_endian.lss.
              unsigned_little_endian.lso;
#endif
            void * x = SharedMap<V>::find(mask);
            
            completion(mask, (V *)x);
            
        } )) { }
    }
    
    bool exists(const K& key) { __block V * exists = NULL; seek(key, ^(
      __builtin_treeint_t mask, V *found) { exists = found; }); return exists; }
    
    /**  Returns a reference to the old value if one exists. I.e signals if
      value is non-existing. */
    
    Opt<V&> include(const K& key, const V& value, bool overwriteExisting) {
      __block V * y = NULL; seek(key, ^(__builtin_treeint_t mask, V * x) {
            if (x) {
                if (overwriteExisting) {
                    __builtin_int_t b = sizeof(value);
                    V * t = (V *)SharedMap<V>::allocate(b);
                    Copy8Memory((ByteAlignedRef)t, (ByteAlignedRef)x, b);
                    Copy8Memory((ByteAlignedRef)x, (ByteAlignedRef)&value, b);
                    x = t;
                } else { /* do nothing */ }
            } else  { SharedMap<V>::treeInsert(mask, value);
                keys.push(key); // ⬷ Currently unsorted and not inserted into a tree consisting of keys.
            }
        });
        
        return y ? Opt<V&>(*y) : Opt<V&>::no();
    }
    
    /**  Removes a value and returns a reference to that value. */
    
    // Opt<V&> remove(const K& key) {}
    
    Vector<K> keys;
    
    int elements(void (^touchbase)(const K& key, V& value, bool& stop)) const {
        
        if (keys.elements(^(SemanticPointer<K *> elem, bool& stop) {
            const K& key = *elem.pointer;
            Opt<const V&> value = this->operator[](key);
            // if (!value.populated) { return 1; } // TODO: Add stop to elements.
            touchbase(key, *value, stop);
        })) { }
        
        return 0;
    }
    
    /**  Returns a reference to existing value, does not create new values. */
    
    Opt<V&> operator[](const K& key) const { __block V * y = NULL; seek(key,
      ^(__builtin_treeint_t mask, V * x) { y = x; }); return y ? Opt<V&>(*y) :
      Opt<V&>::no(); }
    
};

#ifdef  __mips__
#define BUILTIN_INT_MAX 2147483647
#elif defined __x86_64__
#define BUILTIN_INT_MAX 0x7FFFFFFFFFFFFFFF
#endif

template<typename V> struct Map<const char *, V> : public SharedMap<V> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Map(std::initializer_list<Tuple<const char *,
    V>> l) : Map() { const Tuple<const char *, V> *i = l.begin(); auto end =
    l.end(); for (; i != end; ++i) include(get<0>(*(Tuple<const char *, V> *)i),
    get<1>(*(Tuple<const char *, V> *)i), true); }
    
    Map() : SharedMap<V>(alloc) { }
    
    void seek(const char * utf8Key, void (^completion)(__builtin_treeint_t mask,
      V * found)) const { __builtin_int_t bytes = Utf8BytesUntilNull(utf8Key,
      BUILTIN_INT_MAX);
        if (Hash((uint8_t *)&utf8Key, bytes, ^(bool &stop) {},
          ^(ditriaconta digest) {
#ifdef __x86_64__
              __builtin_treeint_t mask = digest.little_endian.lss.sexdeca;
#elif defined __mips__
              __builtin_treeint_t mask = digest.little_endian.lss.
                unsigned_little_endian.lso;
#endif
              void * x = SharedMap<V>::find(mask);
              
              completion(mask, (V *)x);
              
        } )) { }
    }
    
    bool exists(const char * key) { __block V * exists = NULL; seek(key, ^(
      __builtin_treeint_t mask, V *found) { exists = found; }); return exists; }
    
    /**  Returns a reference to the old value if one exists. I.e signals if
      value is non-existing. */
    
    Opt<V&> include(const char *utf8Key, const V& value, bool overwriteExisting)
      { __block V * y = NULL; seek(utf8Key, ^(__builtin_treeint_t mask, V * x) {
            if (x) {
                if (overwriteExisting) {
                    __builtin_int_t b = sizeof(value);
                    V * tmp = (V *)SharedMap<V>::allocate(b); // TODO: Add specialization for V&
                    Copy8Memory((ByteAlignedRef)tmp, (ByteAlignedRef)x, b);
                    Copy8Memory((ByteAlignedRef)x, (ByteAlignedRef)&value, b);
                    x = tmp;
                } else { /* do nothing */ }
            } else  { SharedMap<V>::treeInsert(mask, value);
                keys.push(utf8Key); // ⬷ Currently unsorted and not inserted into a tree consisting of keys.
            }
        });
        
        return y ? Opt<V&>(*y) : Opt<V&>::no();
    }
    
    /**  Removes a value and returns a reference to that value. */
    
    // Opt<V&> remove(const char * key) {}
    
    Vector<const char *> keys;
    
    int elements(void (^touchbase)(const char * key, V& value, bool& stop)) const {
        
        if (keys.elements(^(SemanticPointer<const char **> elem, bool& stop) {
            const char * key = *elem.pointer;
            Opt<const V&> value = this->operator[](key);
            // if (!value.populated) { return 1; } // TODO: Add stop to elements.
            touchbase(key, *value, stop);
        })) { }
        
        return 0;
    }
    
    /**  Returns a reference to existing value, does not create new values. */
    
    Opt<V&> operator[](const char * utf8Key) const { __block V * y = NULL;
      seek(utf8Key, ^(__builtin_treeint_t mask, V * x) { y = x; }); return y ?
      Opt<V&>(*y) : Opt<V&>::no(); }
    
};

template<typename V> struct Map<const char32_t *, V> : public SharedMap<V> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Map(std::initializer_list<Tuple<const char32_t
    *, V>> l) : Map() { const Tuple<const char32_t *, V> *i = l.begin(); auto
    end = l.end(); for (; i != end; ++i) include(get<0>(*(Tuple<const char32_t
    *, V> *)i), get<1>(*(Tuple<const char32_t *, V> *)i), true); }
    
    Map() : SharedMap<V>(alloc) { }
    void * finnd(__builtin_treeint_t mask) const { return SharedMap<V>::find(mask); }
    void seek(const char32_t * nativeEndianUnicodeKey, void (^completion)(
      __builtin_treeint_t mask, V * found)) const {
        
        __builtin_int_t tetras = UnicodesUntilNull(nativeEndianUnicodeKey,
          BUILTIN_INT_MAX);
        if (Hash((uint8_t *)nativeEndianUnicodeKey, tetras<<2, ^(bool &stop) {},
          ^(ditriaconta digest) {
#ifdef __x86_64__
              __builtin_treeint_t mask = digest.little_endian.lss.sexdeca;
#elif defined __mips__
              __builtin_treeint_t mask = digest.little_endian.lss.
                unsigned_little_endian.lso;
#endif
              void * x = finnd(mask);
              
              completion(mask, (V *)x);
              
        } )) { }
    }
    
    bool exists(const char32_t * key) { __block V * exists = NULL; seek(key, ^(
      __builtin_treeint_t mask, V *found) { exists = found; }); return exists; }
    
    /**  Returns a reference to the old value if one exists. I.e signals if
     value is non-existing. */
    
    Opt<V&> include(const char32_t *nativeEndianUnicodeKey, const V& value,
      bool overwriteExisting) { __block V * y = NULL;
        seek(nativeEndianUnicodeKey, ^(__builtin_treeint_t mask, V * x) {
            if (x) {
                if (overwriteExisting) {
                    __builtin_int_t b = sizeof(value);
                    V * tmp = (V *)SharedMap<V>::allocate(b);
                    Copy8Memory((ByteAlignedRef)tmp, (ByteAlignedRef)x, b);
                    Copy8Memory((ByteAlignedRef)x, (ByteAlignedRef)&value, b);
                    x = tmp;
                } else { /* do nothing */ }
            } else { SharedMap<V>::treeInsert(mask, value);
                keys.push(nativeEndianUnicodeKey); // ⬷ Currently unsorted and not inserted into a tree consisting of keys.
            }
        });
        
        return y ? Opt<V&>(*y) : Opt<V&>::no();
    }
    
    /**  Removes a value and returns a reference to that value. */
    
    // Opt<V&> remove(const char32_t *key) {}
    
    int elements(void (^touchbase)(const char32_t *key, V& value, bool& stop)) const {
        
        if (keys.elements(^(SemanticPointer<const char32_t **> elem, bool& stop) {
            const char32_t * key = *elem.pointer;
            Opt<V&> value = this->operator[](key);
            // if (!value.populated) { return 1; } // TODO: Add stop to elements.
            touchbase(key, *value, stop);
        })) { }
        
        return 0;
    }
    
    Vector<const char32_t *> keys;
    
    /**  Returns a reference to existing value, does not create new values. */
    
    Opt<V&> operator[](const char32_t * nativeEndianUnicodeKey) const { __block
      V * y = NULL; seek(nativeEndianUnicodeKey, ^(__builtin_treeint_t mask, V *
      x) { y = x; }); return y ? Opt<V&>(*y) : Opt<V&>::no(); }
    
};

template<typename V> struct Map<__builtin_int_t, V> : public SharedMap<V> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Map(std::initializer_list<Tuple<
    __builtin_int_t, V>> l) : Map() { const Tuple<__builtin_int_t, V> *i =
      l.begin(); auto end = l.end(); for (; i != end; ++i) { include(get<0>(
      *(Tuple<__builtin_int_t, V> *)i), get<1>(*(Tuple<__builtin_int_t, V>*)i),
      true); } }
    
    Map() : SharedMap<V>(alloc) { }
    
    void seek(__builtin_int_t key, void (^completion)(__builtin_treeint_t mask,
      V * found)) const {
#ifdef __x86_64__
        __builtin_treeint_t mask = _mm_set_epi64x(0x0, key);
#elif defined __mips__
        octa mask; mask.unsigned_little_endian.lst = key;
#endif
        void * x = SharedMap<V>::find(mask);
        
        completion(mask, (V *)x);
    }
    
    bool exists(__builtin_int_t key) { __block V * exists = NULL; seek(key, ^(
      __builtin_treeint_t mask, V *found) { exists = found; }); return exists; }
    
    /**  Returns a reference to the old value if one exists. I.e signals if
      value is non-existing. */
    
    Opt<V&> include(__builtin_int_t key, const V& value, bool
      overwriteExisting) { __block V * y = NULL;
        seek(key, ^(__builtin_treeint_t mask, V * x) {
            if (x) {
                if (overwriteExisting) {
                    __builtin_int_t b = sizeof(value);
                    V * tmp = (V *)SharedMap<V>::allocate(b);
                    Copy8Memory((ByteAlignedRef)tmp, (ByteAlignedRef)x, b);
                    Copy8Memory((ByteAlignedRef)x, (ByteAlignedRef)&value, b);
                    x = tmp;
                } else { /* do nothing */ }
            } else { SharedMap<V>::treeInsert(mask, value);
                keys.push(key); // ⬷ Currently unsorted and not inserted into a tree consisting of keys.
            }
        });
        
        return y ? Opt<V&>(*y) : Opt<V&>::no();
    }
    
    /**  Removes a value and returns a reference to that value. */
    
    // Opt<V&> remove(__builtin_int_t key) { }
    
    Vector<__builtin_int_t> keys;
    
    int elements(void (^touchbase)(__builtin_int_t key, V& value, bool& stop)) const {
        if (keys.elements(^(SemanticPointer<__builtin_int_t *> elem, bool& stop) {
            __builtin_int_t key = *elem.pointer;
            Opt<const V&> value = this->operator[](key);
            // if (!value.populated) { return 1; } // TODO: Add stop to elements.
            touchbase(key, *value, stop);
        })) { }
        
        return 0;
    }
    
    /**  Returns a reference to existing value, does not create new values. */
    
    Opt<V&> operator[](__builtin_int_t key) const { __block V * y = NULL;
      seek(key, ^(__builtin_treeint_t mask, V * x) { y = x; }); return y ?
      Opt<V&>(*y) : Opt<V&>::no(); }
    
};

#pragma mark - 😐😇

struct Chronology {
    
    typedef octa Instant;
    
    /**  Given a timestamp, return year, month (1-12) and day (1-31). */
    
    Tuple<int32_t, int32_t, int32_t> date(Instant timestamp) const;
    
    /**
     
     Return hour (0-23), minute (0-59), seconds (0-59) and fractional
     precision since midnight.
     
     */
    
    Tuple<int32_t, int32_t, int32_t, uint32_t> sinceMidnight(Instant ts) const;
    
    /**
     
     Create a timestamp from a date and a time.
     
     @param parts  Contains year, month (1-12), day (1-31), hour (0-23),
     minutes (0-59) and seconds (0-59)
     
     @param fracSec  The number of 232 ps intervals.
     
     */
    
    Instant timestamp(int32_t parts[6], uint32_t fracSec) const;
    
    /**  Return a future instant. */
    
    Instant
    addSeconds(
        Instant instant,
        uint32_t seconds
    ) const;
    
    /**  Only for unperturbed chronologies. For non-reversable chronologies,
      subtract throws an error. */
    
    Instant subtractSeconds(Instant instant, uint32_t seconds) const BLURTS;
    
    /**  The time without any NTP correction. */
    
    Instant localNow(uint32_t fracSec) const;
    
    /**  Return weekday assuming a week starts on a Sunday. (Encoded as 0.) */
    
    int dayofweek(Instant instant) const;
    
};

Opt<Chronology::Instant>
TS( // E.g 2012-01-24 12:00:00.125, 2018-05-18 15:58:36 and 2012-01-24 12:00:00.000000000232
   Chronology chronology,
   Memoryview datetime
) NEVERBLURTS;

int
InstantToText(
   Chronology chronology,
   Chronology::Instant ts,
   bool fractionalsToo,
   void (^touchbase)(char c)
);

/**  The unperturbed — yet based on Caesium 133 — chronology. */

Chronology& ComputationalChronology();

/**  The chronology of the users' choice. */

Chronology& SystemCalendricChronology();

#endif
