//  
//  Twinbeam.h (libTwinbeam_X_cdcdc7f.a)
//  Twinbeam (C++20 for clang to x86_64 or MIPS.)
//  MIPS compiled using clang version 7.0.0
//  x86_64 compiled using Xcode Version 10.1 (10B61)
//  

#ifndef __TWINBEAM_H
#define __TWINBEAM_H

#define NULL 0
#define INLINED __attribute__((always_inline))
#define MACRO inline INLINED
#define structᵢ struct __attribute__((internal_linkage))
#define unionᵢ union __attribute__ ((internal_linkage))
#define inexorable static __attribute__ ((internal_linkage)) /* embedded */
/* Line above replaces `INNER_DATA` ∧ `INNER_FUNCTION`. 'See 𝚗𝚖 for details'. */
#define DISORDERABLE __attribute__((weak)) // Artificial
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
#ifdef  __mips__
typedef unsigned long       uint32_t;
typedef long                int32_t;
typedef uint32_t            __builtin_uint_t;
typedef int32_t             __builtin_int_t;
#define TriboolUnknown 0xFFFFFFFF
#elif defined __x86_64__
typedef unsigned int        uint32_t;
typedef int                 int32_t;
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t; /* 𝘈․𝘬․𝘢 sequential */
#define TriboolUnknown 0xFFFFFFFFFFFFFFFF
#endif
typedef unsigned short     uint16_t;
typedef short              int16_t;
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
void digit_shift(bignum *n, int d); /* multiply `n` by 10ᵈ */
void multiply_bignum(bignum *a, bignum *b, bignum *c);
void divide_bignum(bignum *a, bignum *b, bignum *c);

#define BITMASK(type) enum : type
#ifdef  __mips__
#define Mips __asm__ __volatile__ (/* ".set noat   \n" */ ".set noreorder  \n" ".set nomacro    \n"
#elif defined __x86_64__
#define Intel👈 __asm { .intel_syntax noprefix
#define IntelPlusATT👉 asm { .att_syntax .text
#endif
template<typename T>
struct InnerFrame {
  InnerFrame<T>() {} T * ref_;
  // ~InnerFrame() { /* Delete `ref_` in outer class destructor. */ }
  T * operator->() const { return ref_; }
  InnerFrame(T * ref) { ref_ = ref; }
};
#define APPEND_PIMPL                                                         \
  struct Internals;                                                          \
  InnerFrame<Internals> impl_;
#define 😐 APPEND_PIMPL }
template <typename T> struct SemanticPointer { T pointer; };
#define VISITISR(sym) extern void sym(); sym(); /* 'No params' ∧ 'no #include' ⟵ 'Local decl' + call */
#define UNITTEST(symbol) extern "C" void Unittest_##symbol() /* No # ∨ ␣ 'at end' ⟵ 'Token pasting' */
#define Panic(log,s) { printf("'%s'\nPanicking at %s in %s:%d\n",            \
  s, __FUNCTION__, __FILE__, __LINE__); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog, s); } }
#define FINAL /*   ⃨ or DO_NOT_DESTABBILIZE */
#define LONGTOOTH /* __attribute__((deprecated("Marked LONGTOOTH."))) */
#define FOCAL
#define Si_FOCAL
#define OPT_Si_FOCAL
#define ENCLAVED
// #define ⚠️_IMPLIES_DOING_HARDTIME
#define ARGUMENTATIVE /* 𝘢․𝘬․𝘢 `ONLY_FOR_SOFT_REALTIME`. */
#define MAY_CONTAIN_TRACES_OF_FIRM_REALTIME
#define INFLATABBLE
#define SYNTESIZABLE /* 𝘪.𝘦 no loops, ... */
#define FOSSILATED
#define CONTEMPLATE
#define 🚫🔌 ARGUMENTATIVE // ⏲
#ifdef  __mips__
typedef uint32_t mips32_context[32]; //  ∎: mx=11 ∧ mz=23!
typedef mips32_context jmp_buf2;     // 🔎: 32. ⛅️rax!
#elif defined __x86_64__
typedef int64_t x86_64_context[37];
typedef x86_64_context jmp_buf2;
#endif
extern "C" { int setjmp2(jmp_buf2 env); void longjmp2(jmp_buf2 env,
  __builtin_int_t val); /* `__builtin_longjmp` requires last arg to be 
  const and bounded by `int`. */ }
#ifdef  __mips__
#define BLURT(str) { tetra t; t.bits = (uint32_t)(const char *)str;          \
  longjmp2(*JmpBuf(), int(t.unsigned_little_endian.lsh)); }
#elif defined __x86_64__
#define BLURT(str) { octa o; o.bits = (uint64_t)(const char *)str;           \
  longjmp2(*JmpBuf(), int(o.unsigned_little_endian.lst)); }
#endif
#define BLURTS /* Mandatory */
#define NEVERBLURTS /* Fortunately optional. */
#define FALLIBLE /* Unfortunately not mandatory while the constructor gently blurts. */
#define TRY { int __e = setjmp2(*JmpBuf()); if (!__e) {
#define CATCH } else {
#define END_TRY } }
extern "C" jmp_buf2 * /* volatile */ JmpBuf(); /* ⬷ A great symbol for a project break! */
struct SharedOptional { bool populated; explicit SharedOptional() : populated(
  false) { } explicit operator bool() const { return populated; } };
#ifdef  __mips__
typedef unsigned int size_t;
void * operator new(unsigned int size, void * here) noexcept;
#elif defined __x86_64__
typedef unsigned long size_t;
void * operator new(unsigned long size, void * here) noexcept;
#endif /* On `Opt` minus `void *`: See 𝐶𝑟𝑎𝑠ℎ 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑛𝑐𝑦, 𝑐𝑜𝑝𝑦/𝑝𝑎𝑠𝑡𝑒 and 𝑒𝑥𝑝𝑙𝑜𝑖𝑡𝑖𝚤𝑛𝑔 𝑢𝑛𝑖𝑛𝑖𝑡𝑖𝑎𝑙𝑖𝑧𝑒𝑑. */
template <typename T> struct Opt : public SharedOptional { explicit Opt(const
  T& v) { new (content) T(v); populated = true; } explicit Opt() = default; Opt(
  const Opt<T>& other) { populated = other.populated; if (populated) { new
  (content) T((const T&)(other.content)); } } ~Opt() { reinterpret_cast<T *>(
  content)->~T(); } alignas(T) uint8_t content[sizeof(T)]; T& operator*() const
  { return (T&)content; } T * operator->() const { return &(**this); } static Opt no() { return Opt(); } };
template <typename T> struct Opt<T&> : public SharedOptional { explicit Opt(
  const T& v) { new (content) T(v); populated = true; } explicit Opt() = default;
  Opt(const Opt<T>& other) { populated = other.populated; if (populated) { new
  (content) T((const T&)(other.content)); } } ~Opt() { reinterpret_cast<T *>(
  content)->~T(); } alignas(T) uint8_t content[sizeof(T)]; T& operator*() const
  { return (T&)content; } T * operator->() const { return &(**this); } static Opt no() { return Opt(); } };
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
template <class ...T> Tuple<T...> Tie(T... t) { return Tuple<T...>(t...); }      /* ☜😐: 🔅 ⬷ 𝘋𝘰 𝑛𝑜𝑡 move sun. (146) */
namespace std { /* The Standard Residual */ typedef ::size_t size_t;
  template<class T> class initializer_list { const T *beg; size_t sz;
  initializer_list(const T * b, size_t s) : beg(b), sz(s) { } public: typedef
  T value_type; typedef const T& reference; typedef const T& const_reference;
  typedef size_t size_type; typedef const T * iterator; typedef const T *
  const_iterator; initializer_list() : beg(0), sz(0) {} size_t size() const {
  return sz; } const T * begin() const { return beg; } const T * end() const {
  return beg + sz; } }; template<class T> inline const T * begin(
  std::initializer_list<T> i) { return i.begin(); } template<class T> inline
  const T * end(std::initializer_list<T> i) { return i.end(); } }
/* ☜😐: 🔅 ⬷ Earlier remark still valid? */
struct Memoryregion; struct Memoryview { Memoryregion * region; __builtin_int_t
  bytesOffset; __builtin_int_t byteCount; }; /* Intervallic behavior. */
MACRO __builtin_uint_t 🔎(__builtin_uint_t var) { return *((__builtin_uint_t
  /* volatile */ *) var); }
MACRO __builtin_uint_t&  🔧(__builtin_uint_t var) { return (__builtin_uint_t&)
  *(__builtin_uint_t /* volatile */ *)var; }
MACRO __builtin_uint_t TrailingZeros(__builtin_uint_t x) { if (x == 0) { return
  8*sizeof(x); } return ((x-1)^x)-1; /* dst=(a-1) xor a (or on x64 `_blsmsk_u64`) */ }
// And for contemplative consumption of abstraction, 𝑃𝑖𝑛𝑐𝑒 𝑎𝑏𝑠𝑡𝑟𝑎𝑖𝑡:
MACRO __builtin_uint_t 🎭(__builtin_uint_t * symbol, __builtin_uint_t mask,
  void (^update)(__builtin_uint_t& shifted) = ^(__builtin_uint_t&) { } ) {
  __builtin_uint_t word = *symbol, shift = TrailingZeros(mask), orig = mask & word,
  shifted = orig>>shift; if (update) update(shifted); __builtin_uint_t fresh =
  (shifted<<shift)&mask; *symbol = (word & ~mask) | fresh; return orig>>shift; } OPT_Si_FOCAL
#define PRINTF_ATTRS __attribute__((__format__ (__printf__, 1, 2)))
extern "C" { int printf(const char *utf8format, ...) PRINTF_ATTRS /* Note that
  a character literal prefixed with the letter `U` does not neccessarily ends 
  with for example `NULL` */; int atexit(void(*func)(void)); void exit(int); }
extern "C" void * (^Alloc)(__builtin_int_t); extern "C" void (^Fallow)(void *);
extern "C" { void * malloc(size_t); void free(void *); }
int
bprintf_utf8(
  unsigned short (^utf8)(char *p, short unsigned bytes),
  const char *utf8Format,
  __builtin_va_list arg
);
int // Tuple<int, int, int>, 𝘪․𝘦 user-percieved characters, Unicodes and utf-8.
bprintf_unicode(
  unsigned short (^utf8)(char *p, short unsigned bytes),
  const char32_t *unicodeFormatWithExplicitEOTTermination,
  __builtin_va_list arg
);
typedef __builtin_uint_t * WordAlignedRef; typedef uint8_t * ByteAlignedRef;
#ifdef __x86_64__
FOCAL MACRO ByteAlignedRef /* µA("x86_64", "haswell", x₁, x₂) */ Copy8Memory(
  ByteAlignedRef dst, /* const */ ByteAlignedRef src, __builtin_int_t bytes) {
  ByteAlignedRef org = dst; __asm__ __volatile__ ("rep movsb" : "+D"(dst),
  "+S"(src), "+c"(bytes) : : "memory"); return org; }  // 𝘪․𝘦 𝚖𝚎𝚖𝚌𝚙𝚢
  #include <xmmintrin.h>  // ≥ SSE 4.2
  #include <immintrin.h>  // `blend` from smmintrin.h and AVX/AVX2 from avxintrin.h and avx2intrin.h
FOCAL int  /* µA("Compare", "x86_64", "haswell", x₁, x₂) */ __attribute__((
  target("sse4.2"))) Compare8Memory(ByteAlignedRef l, ByteAlignedRef r,
  __builtin_uint_t bytes);
#define MEASURE_START(prefix) int64_t prefix##Start = __rdtsc(); /* 𝚜𝚒𝚐𝚗𝚎𝚍 ⟵ Comparision */
#define MEASURE_END(prefix)                                                  \
  int64_t prefix##End = __rdtsc();                                           \
  int64_t prefix##Nanos = prefix##End - prefix##Start;                       \
  printf(#prefix " measures %lld ns\n",  prefix##Nanos);
#elif defined __mips__
FOCAL ByteAlignedRef /* µA("mips", "r2", x₃, x₄) */ Copy8Memory(ByteAlignedRef
  dst, ByteAlignedRef src, __builtin_int_t bytes);
FOCAL int /* µA("mips", "r2", x₃, x₄) */ Compare8Memory(ByteAlignedRef l,
  ByteAlignedRef r, __builtin_uint_t bytes); // 𝘪․𝘦 𝚖𝚎𝚖𝚌𝚖𝚙
#define PIC32SYMBOL(serie,symbol,vaddr)                                      \
  constexpr uint32_t PIC32##serie##_##symbol = vaddr;                        \
  constexpr uint32_t PIC32##serie##_##symbol##CLR = (vaddr + 0x4);           \
  constexpr uint32_t PIC32##serie##_##symbol##SET = (vaddr + 0x8);           \
  constexpr uint32_t PIC32##serie##_##symbol##INV = (vaddr + 0xc);
#define PortRectifyAsOutputs(serie,X,tris) (*((uint32_t *)PIC32##serie##_##TRIS##X##CLR) = (uint16_t)(tris))
#define 🔎🎭𝑀𝑋(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__) 
#define 🔎🎭𝑀𝑍𝐷𝐴(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
#define 🔎🎭𝑀𝑍(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
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
  Block_layout *)arg; struct Block_layout *res = (struct Block_layout *)Alloc(
  block->descriptor->size); Copy8Memory((ByteAlignedRef)res, (ByteAlignedRef)
  block, block->descriptor->size); return res; }
MACRO void _Block_release(const void *arg) { Fallow((void *)arg); }
typedef __builtin_uint_t BinaryChoice; BITMASK(BinaryChoice) {
  BinaryChoiceToLeft = 0b0, BinaryChoiceToRight = 0b1 };
MACRO __builtin_int_t SystemInfoPagesize() { return 8192; } /* One definition of 𝘮𝘢𝘯𝘺 ∧ ¬𝘴𝘤𝘢𝘭𝘢𝘳 (especially when NAND vs. NOR.) */
#define NEVERBLURTS /* Fortunately undefined for script, kiddies. */
#ifdef  __mips__
typedef uint32_t mips32_context[32];
typedef mips32_context jmp_buf2;
#elif defined __x86_64__
typedef int64_t x86_64_context[(9 * 2) + 3 + 16];
typedef x86_64_context jmp_buf2;
#endif
FOCAL void Base(/* TeX §64, §65 and §67 */ __builtin_uint_t ℕ, unsigned
  short base, unsigned short digitsOr0, /* Not more than 32 or 64 digits
  depending on word size! (Or set to `0` to skip leading zeros.) */ void
  (^out)(char 𝟶to𝟿));
FOCAL void Base(__builtin_int_t ℤ, unsigned short base, unsigned short
  digitsOr0, void (^out)(char 𝟶to𝟿));
#define SIGNBIT_INT32 0x80000000
#define SIGNBIT_INT64 0x8000000000000000
MACRO double abs64i(int64_t x) { return x & ~SIGNBIT_INT64; }
MACRO double abs32i(int32_t x) { return x & ~SIGNBIT_INT32; }
/* template <typename T> T abs(T x) { return x < 0 ? -x : x; } */
#define indisponible(D) __attribute__((diagnose_if(!__is_identifier(D), "Indisponible function call", "error")))
#define STRANGE_MAIN void _Noreturn main
#ifdef __x86_64__
#define LEAF __attribute__ ((no_caller_saved_registers))
/* #define BEFORE_CTXSWITCH __attribute__ ((preserve_all))
#define HOT_PATH  __attribute__ ((preserve_most)) */
#elif defined __mips__
// void __attribute__ ((interrupt, leaf)) v1 ();
#define LEAF
#endif
#define IsOdd(x) ((x) & 0b1) /* For int32_t|int64_t. */
template <typename T> T max(T x₁, T x₂) { return x₁ < x₂ ? x₂ : x₁; }
template <typename T> T min(T x₁, T x₂) { return x₂ < x₁ ? x₂ : x₁; }
namespace Relative {
template <typename T> T arithmeticBetween(T x₁, T x₂) { return (x₁ + x₂) / 2; }
// template <typename T> T geometricBetween(T x₁, T acc) { return sqrt(x₁ * acc); } // 𝘚𝘦𝘦: Search ☜😐: ⌨️ MMXVII, XXX, ⅳ
// template <typename T>  T harmonicBetween(T x₁, T acc) { return 1 / sqrt(x₁ * acc); } // 𝘚𝘦𝘦: Padé ☜😐: ⌨️ 🐚, 🐇,
template <typename T> T leftChange(T x₁, T x₂) { return (x₁ - x₂) / x₂; } // ∈ [0, 1]
template <typename T> T rightChange(T x₁, T x₂) { return (x₂ - x₁) / x₁; } // ∉ [0, 1]
// Norm == Sequence<T>|AccumulativeSequence<T> S, AlgebraicCategory<T> C
template <typename T> T diff(T x₁, T x₂) { return x₁ - x₂; }
template <typename T> T dist(T x₁, T x₂, T (^N)(T x, T y)) { return N(x₁, x₂); }
template <typename T> bool eqrel(T x₁, T x₂) { return !(x₁ < x₂ || x₂ < x₁); };
template <typename T> bool eqeql(T x₁, T x₂) { return x₁ == x₂; }; }
#define WHEN_COMPILING constexpr static
#define NOT_EVERYTIME const static
#define CARDINALS(...) enum Cardinal { __hole=0, __VA_ARGS__ };              \
  static jmp_buf2 __snapshot;                                                \
  auto confess = ^(Cardinal sin) { longjmp2(__snapshot, (__builtin_int_t)sin); };
#define NEARBYCROSS                                                          \
  int __ctrl = setjmp2(__snapshot);                                          \
  switch (__ctrl)
#define 🧵(...) /* ✠ */ CARDINALS(__VA_ARGS__) NEARBYCROSS
#define 🥇 NOT_EVERYTIME
#define 🥈ᵢ WHEN_COMPILING __attribute__ ((internal_linkage))
#define 🥈 WHEN_COMPILING /* Must be assigned to a `const` and no inline assembler. */
/* #define fluctuant __block */

#pragma mark Utf-8

int UnicodeToUtf8(char32_t uc, void (^completion)(const uint8_t *p, int bytes));

__builtin_int_t Utf8Followers(uint8_t leadOr8Bit);

char32_t Utf8ToUnicode(const char *p, __builtin_int_t bytes);

struct Utf8Artifact { __builtin_int_t line, bytesOffset, count; };

enum { END_OF_TRANSMISSION = U'\x4' };

#pragma mark - 🌱

typedef union {
   double base2; // Captures 2⁻¹⁰²² and 2¹⁰²³ or in engineering: 2․23×10⁻³⁰⁸ to 1․79×10³⁰⁸
   struct { uint32_t lst; int32_t mst; } signed_little_endian;
   struct { int32_t mst; uint32_t lst; } signed_big_endian;
   struct { uint32_t lst; uint32_t mst; } unsigned_little_endian;
   struct { uint32_t mst; uint32_t lst; } unsigned_big_endian;
   struct {
      unsigned mantissal : 32;
      unsigned mantissah : 20;
      unsigned exponent  : 11;
      unsigned sign      :  1;
   } ieee754b2;
   struct {
      unsigned sign      :  1; // ⫝
   } ieee754b10;
   /* struct {
      unsigned absolute  : 31;
      unsigned sign      :  1;
   } sgned; */
   int64_t sgned;
   uint64_t bits;
} octa;

struct Octa { uint32_t h, l; };

#ifdef __x86_64__
typedef __int128_t __builtin_treeint_t;
#elif defined __mips__
typedef int64_t __builtin_treeint_t; /* Note: Is signed! */
#endif

void * Insert(void *opaque, __builtin_treeint_t data, void * ref); /* Consider
  __builtin_treeint_t as ref. See 𝚄𝚗𝚒𝚝𝚝𝚎𝚜𝚝𝚜 for details. */
void Forall(void *opaque, void (^dfs)(void * ref, bool& stop,
  __builtin_treeint_t mask, void *node));
void * Lookup(const void *opaque, const __builtin_treeint_t target);

/* Big endian=most significant first, little endian=least sigificant first. */

typedef union {
#ifdef __x86_64__
  __m128 intel; /* Sixteen (possibly unaligned) bytes divided into `float` slots. */
#elif defined __mips__
#endif
  __uint128_t bits;
  struct { octa lso; octa mso; } little_endian;
  struct { octa mso; octa lso; } big_endian;
} sexdeca;

typedef union {
#ifdef __x86_64__
  __m256 intel; /* Thirty-two (possibly unaligned) bytes divided into `float` slots. */
#elif defined __mips__
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

#ifdef  __mips__
#define BUILTIN_INT_MAX 2147483647
#elif defined __x86_64__
#define BUILTIN_INT_MAX 0x7FFFFFFFFFFFFFFF
#endif

typedef union {
   float base2; // For 2⁻¹²⁶ to 2¹²⁷ or 1․18×10⁻³⁸ to 3․40×10³⁸․
   struct { uint16_t lsh; int16_t msh; } signed_little_endian;
   struct { int16_t msh; uint16_t lsh; } signed_big_endian;
   struct { uint16_t lsh; uint16_t msh; } unsigned_little_endian;
   struct { uint16_t msh; uint16_t lsh; } unsigned_big_endian;
   struct {
     unsigned mantissa : 23;
     unsigned exponent :  8;
     unsigned sign     :  1;
   } ieee754;
   uint32_t bits;
   int32_t sgned;
} tetra;

typedef uint32_t Tetra;

enum class Endianness { Native, Network };

#pragma mark - 📖😐 ”𝑈𝑛𝑖𝑐𝑜𝑑𝑒”

enum class Encoding { utf8, unicode };

int TokenizeUtf8OrUnicode(Encoding encoding, Memoryview content,
  __builtin_int_t& beam, void (^character)(char32_t unicode, __builtin_int_t
  byteOffset, bool& stop));

int Utf8Sync(uint8_t **p); /* Backs at most 3 bytes to regain sync. */

#pragma mark - ”𝑇ℎ𝑒 🧠🧠” 🔍😐

typedef __builtin_uint_t metaaddress;

struct MemoryDelegate { struct Memoryregion; virtual void statistics() = 0; };

struct Memoryregion {
    
    Memoryregion(MemoryDelegate * delegate);
    
    Memoryregion(void *p, __builtin_int_t bytes, MemoryDelegate * delegate = NULL);
    
    ~Memoryregion();
    
    void incorporate(void *virtue, __builtin_int_t bytes, metaaddress loc);
    
    int inject(__builtin_int_t index, const Memoryregion& src, void *(^alloc)
      (__builtin_int_t bytes) = Alloc);
    
    int exclude(metaaddress start, __builtin_int_t bytes);
    
    int takeover(Memoryregion& virtue, metaaddress loc);
    
    SemanticPointer<void *> start() const;
    
    SemanticPointer<void *> relative(__builtin_int_t byte, SemanticPointer<void *> base) const;
    
    __builtin_int_t bytes() const;
    
    void alsoAtDealloc(void (^deferral)()); /* ☜😐: 🛵𝜆 */
    
#pragma mark Little and Big Endians
    
    /**  TODO: Measure energy consumption while 𝑝𝑢𝑚𝑝𝑖𝑛' 𝑛𝑒𝑡𝑤𝑜𝑟𝑘/𝑛𝑎𝑡𝑖𝑣𝑒. */
    
    INLINED void toggleNetworkAndNative(void (^ping)(bool &stop), void
      (^completion)(__builtin_int_t bytes)); // REQ: O(1)
    
#pragma mark Fields of Capacitors on Two-gates/feedbacked-inverters
    
    static Opt<Memoryregion> abduct(__builtin_int_t bytes, MemoryDelegate *
      delegate = NULL, bool allowWrites = true, void *(^alloc)(
      __builtin_int_t bytes) = Alloc);
    
    static Opt<Memoryregion> reflect(const char * utf8Filepath,
      __builtin_int_t pagesOffset = 0, __builtin_int_t pagesLength = 0,
      MemoryDelegate *delegate = NULL, bool allowWrites = false,
      void *(^alloc)(__builtin_int_t bytes) = Alloc);
    
#pragma mark Memory Mangement
    
    Memoryregion() = delete;
    
    Memoryregion(const Memoryregion& other);
    
😐; /* Pimpl optional because of opaque, mandatory since `alsoAtDealloc`. */

void * ExactSeek(const void *key, const void *base, size_t num, size_t size,
  __builtin_int_t (^cmp)(const void *key, const void *elt));

template <typename T> T * materialize(Memoryview * view) {
  extern void * 💫(void *); return (T *)💫((void *)view); } // ...may require 𝙰𝚕𝚕𝚘𝚌․

// template <> Unicodestring materialize(Memoryview * view) {
//   return Unicodestring(Endianness::Native, 💫(view), view.bytesCount,
//   true); }

bool IsPrefixOrEqual(const char *eightbitString, const char *eightbitPrefix);

#pragma mark - 😐🎤💀 ”𝑇ℎ𝑒 ⚰️”

#define va_epilogue __builtin_va_end(__arg);
extern "C" void Sheriff();
// #define ⭐️ Sheriff();
enum Impediment { MustBeOrdered, JustSwap };
int OptimisticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, Impediment it); /* Non-
atomic, yet consistent and gracefully failing indicated through a non-zero return value. */
/* struct Peekey { __builtin_int_t 🥈 ⬚=2, 🗝=1; __builtin_int_t board₁, palm₂; }; */
#define 🔒(situ) OptimisticSwap(&situ.board₁, &situ.palm₂, MustBeOrdered)
#define 🔓(situ) OptimisticSwap(&situ.board₁, &situ.palm₂, JustSwap);
#ifdef __x86_64__
#define POSIX_FIBER
#elif defined __mips__
#define MIPS_MCU_AUTOMATIC_PROLOG_EPILOG_IRQ
#endif
#include <Source/osXFiber.hpp>
namespace Fiber {
    
    int 🥈 Bytes =
 #ifdef __x86_64__
        160
 #elif defined __mips__
        128
 #endif
        ;
    
#ifndef POSIX_FIBER
    struct ucontext_t {
      union {
        struct { uint8_t bytes[Bytes]; } generic;
        struct { __builtin_uint_t regs[1+15+4], rip, rsp; } intel;
        struct { __builtin_uint_t gprs[Bytes/4]; } mips;
      } cpu;
      __builtin_int_t bytesStk; uint8_t * rtstk;
      uint8_t alcoda[Bytes]; /* ⌖ */
    };
#endif
    struct fuContext {
      ucontext_t ctx;
      int 🥈 bytes = sizeof(ucontext_t);
      uint8_t alcoda[bytes]; /* ⌖ */
    };
    int Snapshot(fuContext *ucp) LEAF;
    int Recall(const fuContext *ucp) LEAF;
    void Incubate(fuContext *ucp, void (*ufnc)(...), int argc, ...);
#ifdef __x86_64__
    register __builtin_uint_t rsp asm("rsp"), rbp asm("rbp");
#endif
    typedef fuContext fiber_t;
    
    // __attribute__((callback (ufnc, uctx)))
    inline void create(fiber_t& fib, void (*ufnc)(void *), void * uctx,
      void *(^alloc)(__builtin_int_t bytes) = Alloc) {
        Snapshot(&fib);
        __builtin_uint_t 🥈ᵢ bytesStack = 131072;
#ifdef POSIX_FIBER
        fib.ctx.uc_stack.ss_sp = alloc(bytesStack);
        fib.ctx.uc_stack.ss_size = bytesStack;
        fib.ctx.uc_link = 0;
#else
        fib.ctx.rtstk = (uint8_t *)alloc(bytesStack);
        fib.ctx.bytesStk = bytesStack;
#endif
        Incubate(&fib, (void (*)(...))ufnc, 1, uctx);
    }
    
    // __attribute__((callback (ufnc, fib)))
    inline void create(Fiber::fiber_t& fib, void (*ufnc)(Fiber::fiber_t *),
      void *(^alloc)(__builtin_int_t bytes) = Alloc) {
        Fiber::create(fib, (void (*)(void *))ufnc, (void *)&fib, alloc);
    }
    
    MACRO void swap(fiber_t& nxt, fiber_t& prv)
    { if (Snapshot(&prv) == 0) Recall(&nxt); }
    
    MACRO void start(fiber_t& nxt) { Recall(&nxt); }
    
}

#define va_prologue(symbol)                                                 \
  __builtin_va_list __arg;                                                  \
  __builtin_va_start(__arg, symbol);

#pragma mark - 😐😇

struct Chronology {
    
    typedef octa Instant; typedef uint32_t UQ32; /* E.𝘨 0.101₂ = 1×1/2 + 0×1/4 + 1×1/8 = 5/8․ */
    
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
     
     @param fract  The number of 232 ps intervals to add. Note TS(.../
     
     */
    
    Opt<Chronology::Instant> timestamp(int32_t parts[6], UQ32 fract = 0) const;
    
    /**  Return a future instant. */
    
    Instant
    addSeconds(
      Instant instant,
      uint32_t seconds
    ) const;
    
    /**  Only for unperturbed chronologies. For non-reversable chronologies,
      subtract throws an error. */
    
    Instant subtractSeconds(Instant instant, uint32_t seconds) const BLURTS;
    
    /**  Retrieve a - since the program started and given a chronology - unique 
      value in a 'strict monotonically increasing' serie. */
    
    __builtin_uint_t ordinal() const;
    
    /**  Return weekday assuming a week starts on a Sunday. (Encoded as 0.) */
    
    int dayofweek(Instant instant) const;
    
};

int
InstantToText(
  Chronology chronology,
   Chronology::Instant ts,
   bool fractionalsToo,
  void (^out)(char digitHyphenColonPeriodOrSpace)
);
  
Opt<Chronology::Instant>
TS( /* E.𝘨 2012-01-24 12:00:00.125, 2018-05-18 15:58:36 and 2012-01-24 12:00:00.000000000232 */
  Encoding encoding,
  Chronology chronology,
  Memoryview datetime
) NEVERBLURTS;

 /*
  
  Mars got five days a week and five seasons per year:
  
   enum class Veneuveteuean { Again, trout, loo, master, shoRt };
  
  ...and also a longer relative of unknown periodicity.
  
  */
 
typedef Chronology Chronology🚀; /* I․𝘦 'Celestial fractional' with 'identical' epoc. */

typedef Chronology Chronology🦠; /* With 2⁻⁶⁵ 𝘢․𝘬․𝘢 `UQ65`; light
  travels approximately 8.126 𝑝m ('pico meter') per increment. */

/**  The unperturbed — yet based on ¹³³Caesium — chronology. */

Chronology& ComputationalChronology(); /* 𝖤.𝘨 for chronometers. */

/**  The chronology of the users' choice. */

Chronology& SystemCalendricChronology(); /* Irreversible, conclusive mass; Consider 𝑒𝑎𝑠𝑒-𝑖𝑛․ */

#endif
