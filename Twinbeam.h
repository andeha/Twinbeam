/*  Twinbeam.h (libTwinbeam_X_cdcdc7f.a)
    C++20 for clang to x86_64 and MIPS
    MIPS compiled using clang version 9.0.0
    x86_64 compiled using Xcode Version 10.2.1 (10E1001) */

#ifndef __TWINBEAM_H
#define __TWINBEAM_H

#define NULL 0
#define INLINED __attribute__((always_inline))
#define MACRO inline INLINED
#define structᵢ struct __attribute__((internal_linkage))
#define unionᵢ union __attribute__ ((internal_linkage))
#define inexorable static __attribute__ ((internal_linkage)) /* embedded */
/* Line above replaces `INNER_DATA` ∧ `INNER_FUNCTION`. 'See 𝚗𝚖 for details'. */
#define DISORDERABLE __attribute__((weak))
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
typedef int                 int32_t; /* ≡`long` */
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t; /* 𝘈․𝘬․a `sequential`. */
#define TriboolUnknown 0xFFFFFFFFFFFFFFFF
#endif /* ⬷ Consider 32- alt. 64-bits with an extra sign bit for `Frame`, `leqAndPowerOfTwo`, `geqAndPowerOfTwo` and `isPowerOfTwo`. */
typedef unsigned short      uint16_t;
typedef short               int16_t; /* ≡`ᵐⁱᵖˢint` */
typedef __builtin_uint_t Tribool;

typedef struct bignum { /* Artificial */
  constexpr static int maxdigits = 100; /* To not: Templates, … */
  char digits[maxdigits]; /* Binary coded decimals. */
  int signbit; /* Indicates with 𝟷 if positive and with -𝟷 if negative. */
  int lastdigit; /* High-order digit index. */
} bignum;
void print_bignum(bignum *n, void (^output)(char c));
void int_to_bignum(__builtin_int_t s, bignum *n);
void initialize_bignum(bignum *n);
void add_bignum(bignum *a, bignum *b, bignum *c);
void subtract_bignum(bignum *a, bignum *b, bignum *c);
int compare_bignum(bignum *a, bignum *b);
void digit_shift(bignum *n, __builtin_int_t d); /* Multiply n by 10ᵈ. */
void multiply_bignum(bignum *a, bignum *b, bignum *c);
void divide_bignum(bignum *a, bignum *b, bignum *c);

#define BITMASK(type) enum : type
#ifdef  __mips__
#define Mips __asm__ __volatile__ (/* ".set noat   \n" */ ".set noreorder  \n" ".set nomacro    \n"
#elif defined __x86_64__
#define Intel👈 __asm { .intel_syntax noprefix /* Requires -fms-extensions */
#define IntelPlusATT👉 asm { .att_syntax .text
#endif
/* template<typename T>
struct InnerFrame {
  InnerFrame<T>() { } T * ref_;
  // ~InnerFrame() { / * Delete `ref_` in outer class destructor. * / }
  T * operator->() const { return ref_; }
  InnerFrame(T * ref) { ref_ = ref; }
}; */
#define APPEND_PIMPL                                                         \
  struct Internals;                                                          \
  Internals * impl_;
#define 😐 APPEND_PIMPL }
template <typename T> struct SemanticPointer { T pointer; }; /* 𝘈․𝘬․a `DisjunctPointer` and `OptionalIntervallicPointer`. */
#define VISITISR(sym) extern void sym(); sym(); /* 'No params' ∧ 'no #include' ⟵ 'Local decl' + call */
#define UNITTEST(symbol) extern "C" void Unittest_##symbol() /* No # ∨ ␣ 'at end' ⟵ 'Token pasting' */
#define Panic(log,s) { print("\n\n'⬚'\nPanicking at ⬚ in ⬚:⬚\n",          \
  ﹟s(s), ﹟s(__FUNCTION__), ﹟s(__FILE__), ﹟d(__LINE__)); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog, s); } }
#define FINAL /*  …or DO_NOT_DESTABBILIZE */
#define LONGTOOTH /* __attribute__ ((deprecated("Marked LONGTOOTH."))) */
#define FOCAL
#define Si_FOCAL
#define OPT_Si_FOCAL
#define ENCLAVED
/* #define ⚠️_IMPLICATIONS_WHILE_HARDTIMES */
#define ARGUMENTATIVE /* A․𝘬․a `ONLY_FOR_SOFT_REALTIME`. */
#define MAY_CONTAIN_TRACES_OF_FIRM_REALTIME
#define INFLATABBLE
#define SYNTESIZABLE /* I.𝘦 no loops, … */
#define FOSSILATED
#define CONTEMPLATE
#define 🚫🔌 ARGUMENTATIVE /* ⏲ */
#define PLUSKVAMCOMPLETE
#define CHRONOLOGICAL
#define SPATIALPERTUBAL
#define EVENTUALRETROSPECTIVE
#define ROTATIONAL
#define IRREVERSIb /* IRREVERSI♭ */
#define TRAJECTORAL /* Also: TRAJECTORAL🝑 */
#define INITIALPROJECTIVE
#define IRREPABEL /* In German: 'reparierbar'. */
#define AMBIVALENT /* Native: 'contra-polarisative'. */
#define DEFLECTIVE /* E․𝘨 `Auntie`. */
#define ANTIPOLARISATIVE
#define DUALREFLECTIVE
#define CEDILLEPOSITIVE
#define CEDILLEINDUCTIVE
#define EVENTUALMACHINAL
#define REINTEGRATIVE
#define REFLECTIVEATTRACTIONAL
#define VERYLOGARITHMIC
#define PROCESSACCUSATIVE
#define BOOGIEABLATIVE
#ifdef  __mips__
typedef uint32_t mips32_context[32]; //  ∎: mx=11 ∧ mz=23!
typedef mips32_context jmp_buf2;     // 🔎: 32. ⛅️rax!
#elif defined __x86_64__
typedef int64_t x86_64_context[37];
typedef x86_64_context jmp_buf2;
#endif
extern "C" { int setjmp2(jmp_buf2 env); void longjmp2(jmp_buf2 env,
  __builtin_int_t val); /* `__builtin_longjmp` requires last arg to be 
  const and bounded by `int`. Determined 𝑎₋𝑝𝑟𝑖𝑜𝑟𝑖 to be 𝙞𝙣𝙩. */ }
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
#define PULT💡(x) ++x /* ⬷ todo: Add atomic enclosure. */
extern "C" jmp_buf2 * /* volatile */ JmpBuf(); /* ⬷ A great symbol for a project break! */
structᵢ SharedOptional { bool populated; explicit SharedOptional() : populated(
  false) { } explicit operator bool() const { return populated; } };
#ifdef  __mips__
typedef unsigned int size_t;
void * operator new(unsigned int size, void * here) noexcept;
#elif defined __x86_64__
typedef unsigned long size_t;
void * operator new(unsigned long size, void * here) noexcept;
#endif /* On `Opt` minus `void *`: See 𝐶𝑟𝑎𝑠ℎ 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑛𝑐𝑦, 𝑐𝑜𝑝𝑦/𝑝𝑎𝑠𝑡𝑒 and 𝑒𝑥𝑝𝑙𝑜𝑖𝑡𝑖𝚤𝑛𝑔 𝑢𝑛𝑖𝑛𝑖𝑡𝑖𝑎𝑙𝑖𝑧𝑒𝑑. */
template <typename T> struct Opt : public SharedOptional { explicit Opt() = 
  default; template <typename...A> constexpr Opt(A&&... args) { new (content) 
  T(args...); populated = true; } Opt(const Opt<T>& other) { populated = other.
  populated; if (populated) { new (content) T((const T&)(other.content)); } }
  ~Opt() { ((T *)content)->~T(); } alignas(T) uint8_t content[sizeof(T)]; T& 
  operator*() const { return (T&)content; } static Opt no() { return Opt(); } };
template <typename T> struct Opt<T&> : public SharedOptional { explicit Opt() 
  = default; template <typename...A> constexpr Opt(A&&... args) { new (content) 
  T(args...); populated = true; } Opt(const Opt<T>& other) { populated = 
  other.populated; if (populated) { new (content) T((const T&)(other.content)); 
  } } ~Opt() { ((T *)content)->~T(); } alignas(T) uint8_t content[sizeof(T)]; T& 
  operator*() const { return (T&)content; } static Opt no() { return Opt(); } };
template <class... Ts> struct Tuple {}; template <class T, class... Ts>
  struct Tuple<T, Ts...> : Tuple<Ts...> { Tuple(T t, Ts... ts) : Tuple<Ts...>
  (ts...), tail(t) {} T tail; }; template <__builtin_uint_t, class> struct 
  elem_type_holder; template <class T, class... Ts> struct elem_type_holder<0, 
  Tuple<T, Ts...>> { typedef T type; }; template <__builtin_uint_t k, class T, 
  class... Ts> struct elem_type_holder<k, Tuple<T, Ts...>> { typedef typename
  elem_type_holder <k - 1, Tuple<Ts...>>::type type; }; template <bool, 
  typename T = void> struct std__enable_if { }; template <typename T> struct 
  std__enable_if<true, T> { typedef T type; }; template <__builtin_uint_t k, 
  class... Ts> typename std__enable_if<k == 0, typename elem_type_holder<0, 
  Tuple<Ts...>>::type&>::type get(Tuple<Ts...>& t) { return t.tail; }
  template <__builtin_uint_t k, class T, class... Ts> typename std__enable_if<
  k != 0, typename elem_type_holder<k, Tuple<T, Ts...>>::type&>::type
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
  bytesOffset; __builtin_int_t byteCount; };
MACRO __builtin_uint_t 🔎(__builtin_uint_t var) { return *((__builtin_uint_t
  /* volatile */ *) var); }
MACRO __builtin_uint_t&  🔧(__builtin_uint_t var) { return (__builtin_uint_t&)
  *(__builtin_uint_t /* volatile */ *)var; }
MACRO __builtin_uint_t TrailingZeros(__builtin_uint_t x) { if (x == 0) { return
  8*sizeof(x); } x=(x^(x-1))>>1; int c=0; for (; x; c++) { x >>= 1; } return c; }
/* ⬷ Not `__builtin_clzl` for Mips and `__builtin_clz` for Intel.  And for 
  contemplative consumption of abstraction, 𝑃𝑖𝑛𝑐𝑒 𝑎𝑏𝑠𝑡𝑟𝑎𝑖𝑡: */
MACRO __builtin_uint_t 🎭(__builtin_uint_t * symbol, __builtin_uint_t mask,
  void (^update)(__builtin_uint_t& shifted) = ^(__builtin_uint_t&) { } ) {
  __builtin_uint_t word = *symbol, shift = TrailingZeros(mask), orig = mask & word,
  shifted = orig>>shift; if (update) update(shifted); __builtin_uint_t fresh =
  (shifted<<shift)&mask; *symbol = (word & ~mask) | fresh; return orig>>shift; } OPT_Si_FOCAL
enum class Ieee754Form { Scientific, Monetary };
DISORDERABLE void Format(double ℝ, Ieee754Form f, void (^out)(char32_t uc)); 
int print(const char *utf8format, ...); int print(void (^out)(uint8_t * utf8s, 
short unsigned bytes), const char *utf8format, ...);
struct Argᴾ { typedef void (^Unicode)(bool anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, void * context); 
  typedef void (^Output)(Unicode set, void * context); union { __builtin_int_t d; 
  __builtin_uint_t x, b; const char * utf8; struct /* Unicodes */ { char32_t * 
  unicodes; int tetras; } ucs; char c; char32_t uc; double f₁; float f₂; uint8_t 
  bytes[16]; __uint128_t U; __int128_t I; uint64_t pair[2]; struct { Output scalar; 
  void * context; } λ; } value; int kind; };
Argᴾ ﹟d(__builtin_int_t d); Argᴾ ﹟x(__builtin_uint_t x); Argᴾ ﹟b(__builtin_uint_t 
b); Argᴾ ﹟s(const char * utf8); Argᴾ ﹟S(int tetras, char32_t * uc); Argᴾ ﹟c(
char c); Argᴾ ﹟C(char32_t C); Argᴾ ﹟U(__uint128_t U); Argᴾ ﹟I(__int128_t I);
Argᴾ ﹟reᵍs(__builtin_uint_t mask); Argᴾ ﹟λ(Argᴾ::Output scalar, void * context);
extern "C" { int atexit(void(*func)(void)); void exit(int); } 
extern "C" void * (^Alloc)(__builtin_int_t); extern "C" void (^Fallow)(void *);
__builtin_int_t ﹟Frames(__builtin_int_t bytes, __builtin_int_t * modula);
int Acquire𝟷ᵈ(__builtin_int_t ﹟, __builtin_int_t 𝑙𝑜𝑔₂Pages, __builtin_uint_t 
  pages[], __builtin_uint_t avails[], void (^every)(void * 𝟸ⁿframe, bool& stop));
int Release𝟷ᵈ(void * 𝟸ⁿframe, __builtin_int_t 𝑙𝑜𝑔₂Pages, __builtin_uint_t pages[], 
  __builtin_uint_t avails[], bool secure);
extern "C" { void * malloc(size_t); void free(void *); }
typedef __builtin_uint_t * WordAlignedRef; typedef uint8_t * ByteAlignedRef;
#ifdef __x86_64__
FOCAL MACRO ByteAlignedRef /* µA("x86_64", "haswell", x₁, x₂) */ Copy8Memory(
  ByteAlignedRef dst, /* const */ ByteAlignedRef src, __builtin_int_t bytes) {
  ByteAlignedRef org = dst; __asm__ __volatile__ ("rep movsb" : "+D"(dst),
  "+S"(src), "+c"(bytes) : : "memory"); return org; }  /* A․𝘬․a `memcopy`. */
FOCAL int /* µA("Compare", "x86_64", "haswell", x₁, x₂) */ Compare8Memory(
  ByteAlignedRef p₁, ByteAlignedRef p₂, __builtin_uint_t bytes); /* ⏱😐🏁 */
#define MEASURE_START(prefix) int64_t prefix##Start = __rdtsc(); /* 𝚜𝚒𝚐𝚗𝚎𝚍 ⟵ Comparision */
#define MEASURE_END(prefix)                                                  \
  int64_t prefix##End = (int64_t)__rdtsc();                                  \
  int64_t prefix##Nanos = prefix##End - prefix##Start;                       \
  print(#prefix " measures ⬚ ns\n", ﹟d(prefix##Nanos));
#define 🎭𝑋𝟾𝟼(storage,symmsk,...) 🎭((__builtin_uint_t *)(storage), INTEL_##symmsk __VA_OPT__(,) __VA_ARGS__)
#elif defined __mips__
FOCAL ByteAlignedRef /* µA("mips", "r2", x₃, x₄) */ Copy8Memory(ByteAlignedRef
  dst, ByteAlignedRef src, __builtin_int_t bytes);
FOCAL int /* µA("mips", "r2", x₃, x₄) */ Compare8Memory(ByteAlignedRef p₁,
  ByteAlignedRef p₂, __builtin_uint_t bytes); /* A․𝘬․a `memcmp`. */
#define PIC32SYMBOL(serie,symbol,vaddr)                                      \
  constexpr uint32_t PIC32##serie##_##symbol = vaddr;                        \
  constexpr uint32_t PIC32##serie##_##symbol##CLR = (vaddr + 0x4);           \
  constexpr uint32_t PIC32##serie##_##symbol##SET = (vaddr + 0x8);           \
  constexpr uint32_t PIC32##serie##_##symbol##INV = (vaddr + 0xc);
#define PortRectifyAsOutputs(serie,X,tris) (*((uint32_t *)PIC32##serie##_##TRIS##X##CLR) = (uint16_t)(tris))
#define 🔎🎭𝑀𝑋(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__) 
#define 🔎🎭𝑀𝑍𝐷𝐴(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
#define 🔎🎭𝑀𝑍(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
MACRO uint32_t AsUncached(uint32_t vaddr) { return vaddr | 0x20000000; } /* A․𝘬․a `KSEG0ToKSEG1`. */
MACRO uint32_t AsPhysical(uint32_t vaddr) { return vaddr & 0x1FFFFFFF; } /* A․𝘬․a `VToP`. */
#endif
ByteAlignedRef Clear8Memory(ByteAlignedRef mem, __builtin_int_t bytes);
ByteAlignedRef Overwrite8Memory(ByteAlignedRef src, uint8_t val,
  __builtin_int_t bytes);
MACRO __builtin_int_t Frame(__builtin_uint_t size, __builtin_uint_t framesize) {
  return __builtin_int_t((size + framesize - 1) & ~(framesize - 1)); }
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
__builtin_int_t constexpr SystemInfoPagesize() { return 4096; } /* One definition of 𝘮𝘢𝘯𝘺 ∧ ¬𝘴𝘤𝘢𝘭𝘢𝘳 (especially when NAND vs. NOR.) */
#define NEVERBLURTS /* Fortunately undefined for script, kiddies. */
#ifdef  __mips__
typedef uint32_t mips32_context[32];
typedef mips32_context jmp_buf2;
#elif defined __x86_64__
typedef int64_t x86_64_context[(9 * 2) + 3 + 16];
typedef x86_64_context jmp_buf2;
#endif
FOCAL void Base𝕟(/* TeX §64, §65 and §67 */ __builtin_uint_t ℕ, unsigned
  short base, unsigned short digitsOr0, /* Not more than 32 or 64 digits
  depending on word size! (Or set to `0` to skip leading zeros.) */ void
  (^out)(char 𝟶to𝟿)); /* See --<Print.cpp> for a 128-bit version. */
FOCAL void Base𝕫(__builtin_int_t ℤ, unsigned short base, unsigned short
  digitsOr0, void (^out)(char 𝟶to𝟿and₋));
#define OVERLOADABLE __attribute__ ((overloadable))
#define SIGNBIT_INT32 0x80000000
#define SIGNBIT_INT64 0x8000000000000000
MACRO int64_t abs64i(int64_t x) { return x & ~SIGNBIT_INT64; }
MACRO int32_t abs32i(int32_t x) { return x & ~SIGNBIT_INT32; }
/* template <typename T> T abs(T x) { return x < -0 ? -x : x; } yet (specialization, ±0.0, ±0 and optimization). */
#define /* PROVOCATIVE */ ASSEMBLERONLY __attribute__((naked)) /* A․𝘬․a INTERFERENT, ABELIAN, TOTALITARIAN, NEITHER_PROLOGUE_NOR_EPILOGUE. */
/* #define indisponible(D) __attribute__((diagnose_if(!__is_identifier(D), "Indisponible function call", "error"))) */
/* #define STRANGE_MAIN void _Noreturn main */
#define LEAF
#define /* Do not follow. (That sometimes occurs…) */ LEAFLING
#ifdef __x86_64__
#define READONLY __attribute__ ((section(".rodata,.rodata")))
#elif defined __mips__
#define READONLY __attribute__ ((section(".rodata")))
#endif
#define IsOdd(x) ((x) & 0b1) /* For int32_t|int64_t. H: x & 0b010 ⟷̸ ◻️⃞. See also --<math>--<erf.cpp>{⁽₋1⁾ᵏ|alt}. */
template <typename T> T max(T x₁, T x₂) { return x₁ < x₂ ? x₂ : x₁; }
template <typename T> T min(T x₁, T x₂) { return x₂ < x₁ ? x₂ : x₁; }
namespace Relative {
template <typename T> T arithmetic(T x₁, T x₂) { return (x₁ + x₂) / 2; }
/* template <typename T> T geometric(T x₁, T acc) { return ⁿ√(x₁ * acc) = ⁿ√x₁ * ⁿ√acc) = (x₁ * acc)^(1/n); } 𝘚𝘦𝘦: 𝚂𝚎𝚊𝚛𝚌𝚑. 😐: MMCLXVII, XXX, ⅳ. */
/* template <typename T> T harmonic(T x₁, T acc) { return 1/(1/x₁ + … + 1/xₒ₊𝜀); } 𝘚𝘦𝘦: 𝑃𝑎𝑑é (acute). 😐: 🐚. */
template <typename T> T ˡᵊfᵗChange(T x₁, T x₂) { return (x₁ - x₂) / x₂; } /* ∈[0,1] */
template <typename T> T ʳⁱℊʰᵗChange(T x₁, T x₂) { return (x₂ - x₁) / x₁; } /* ∉[0,1] */
/* Norm == Sequence<T>|AccumulativeSequence<T> S, AlgebraicCategory<T> C */
template <typename T> T diff(T x₁, T x₂) { return x₁ - x₂; }
template <typename T> T dist(T x₁, T x₂, T (^N)(T x, T y)) { return N(x₁, x₂); }
template <typename T> bool eqrel(T x₁, T x₂) { return !(x₁ < x₂ || x₂ < x₁); }
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
#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /* 𝘈․𝘬․a `__block`, 𝚊𝚏𝚏𝚎𝚌𝚝𝚊𝚋𝚕𝚎 and 𝒎𝒆𝒄𝒉𝒂𝒏𝒊𝒔𝒎; 𝘤𝘧. Scandinavian 'jurid' and 'förekomst'. Also machinal. */
template <typename T> T * Critic(const T * x) { return const_cast<T *>(x); } /* A․𝘬․a "away 𝙘𝙤𝙣𝙨𝙩 evil". */
#define ᶿ﹡ const * /* #define *⥃ const char *, a․𝘬․𝘢 `*⥆` and `*⫩`. */

#pragma mark Utf-8

int UnicodeToUtf8(char32_t uc, void (^sometimes)(const uint8_t *p, int bytes));

short Utf8Followers(uint8_t leadOr8Bit); /*  See also modern `char8_t` and a later `uchar`. */

char32_t Utf8ToUnicode(const uint8_t *p, __builtin_int_t bytes);

struct Utf8Interval { __builtin_int_t line1ˢᵗ, bytesOffset1ˢᵗ, lineLast, 
  bytesOffsetInclLast; };

struct Utf8Symbol { __builtin_int_t line, bytesOffset, count; };

#pragma mark - 🌱

typedef union {
   double base₂; /* Captures 2⁻¹⁰²² and 2¹⁰²³ or in engineering: 2․23×10⁻³⁰⁸ to 1․79×10³⁰⁸. */
   struct { uint32_t lst; int32_t mst; } signed_little_endian;
   struct { int32_t mst; uint32_t lst; } signed_big_endian;
   struct { uint32_t lst; uint32_t mst; } unsigned_little_endian;
   struct { uint32_t mst; uint32_t lst; } unsigned_big_endian;
   struct {
      unsigned mantissal : 32;
      unsigned mantissah : 20;
      unsigned exponent  : 11;
      unsigned sign      :  1;
   } binary64; /* A․𝘬․a `ieee754b₂`. */
   /* struct { … } ieee754b₁₀; A․𝘬․a `decimal64`. */
   /* struct { 
      unsigned absolute  : 31;
      unsigned sign      :  1;
   } sgned; */
   int64_t sgned;
   uint64_t bits;
} octa;

struct Octa { uint32_t l, h; };

#ifdef __x86_64__
union Treeint { struct { int64_t key; uint64_t val; } keyvalue; __uint128_t bits; };
#include <xmmintrin.h>  /* ≥ SSE 4.2 */
#include <immintrin.h>  /* The `blend` intrinsic in smmintrin.h and AVX/AVX2 from avxintrin.h and avx2intrin.h */
#elif defined __mips__
union Treeint { struct { int32_t key; uint32_t val; } keyvalue; uint64_t bits; };
#endif /* A․𝘬․a `Autumn` and `Treeℤ`. */

void * Insert(void * opaque, Treeint valkey, void * (^alloc)(int bytes));
void Forall(void ᶿ﹡ opaque, void (^dfs)(Treeint valkey, bool& stop));
void * Lookup(void ᶿ﹡ opaque, Treeint target);

/*  Big endian ⟷ 'most significant first', little endian ⟷ 'least sigificant first'. */

typedef union {
#ifdef __x86_64__
  __m128 intel; /* Sixteen (possibly unaligned) bytes divided into `float` slots. */
#elif defined __mips__
#endif
  __uint128_t bits;
  struct { octa lso, mso; } little_endian;
  struct { octa mso, lso; } big_endian;
  struct { Octa l, h; } parts;
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
#endif /* ~0b0>>1 */

typedef union {
   float base₂; /* For 2⁻¹²⁶ to 2¹²⁷ or 1․18×10⁻³⁸ to 3․40×10³⁸. */
   struct { uint16_t lsh; int16_t msh; } signed_little_endian;
   struct { int16_t msh; uint16_t lsh; } signed_big_endian;
   struct { uint16_t lsh; uint16_t msh; } unsigned_little_endian;
   struct { uint16_t msh; uint16_t lsh; } unsigned_big_endian;
   struct {
     unsigned mantissa : 23;
     unsigned exponent :  8;
     unsigned sign     :  1;
   } binary32; /* A․𝘬․a `ieee754₂`. */
   struct { /* For ±1×10⁻⁹⁵ to ±9.999999×10⁹⁶. */
     /* ⫝ */
   } decimal32; /* A․𝘬․a `ieee754_2008₁₀`. */
   uint32_t bits;
} tetra;

typedef uint32_t Tetra;

enum class Endianness { Native, Network };

#pragma mark - 📖😐 ”𝑈𝑛𝑖𝑐𝑜𝑑𝑒”

int Utf8Sync(uint8_t **p); /* Backs at most 3 bytes to regain sync. */

inline char32_t Superscript(short 𝟶to𝟿) { return U'⁰'+𝟶to𝟿; } /* ⁰¹⋯⁹ */

inline char32_t Subscript(short 𝟶to𝟿) { return U'₀'+𝟶to𝟿; } /* ₀₁…₉; ⬷ For the computational chemistry inclined. */

struct Unicodes { __builtin_int_t tetras; char32_t * unicodes; };
/* For const, see `ᵊ` in --<Additions.h>. */

typedef Unicodes Unicodes⁺ᵃ⁻ᵚ; /*  To use when a sequence of symbols, 
  yet neither the length of the sequence nor its start element, are 
  read from inside an 'erase-first-before-you-program' area (such as 
  𝘦․𝘨 a NOR-flash). Further, keep in mind that a `const struct` must 
  not - after initialization - programmatically change framed variables. 
  See also: --<🥽 Cordal.cpp>. */ typedef Unicodes Unicodes⁻ᵃ⁻ᵚ;

enum { END_OF_TRANSMISSION = U'\u0004' }; /* ⬷ hex ∧ dec; Also A․|incorrectly/𝘬․a '\x4', '\x41', '\x42', … */

#pragma mark - For 𝑝𝑖𝑔𝑒𝑜𝑛 𝑟𝑒𝑐𝑜𝑛𝑛𝑎𝑖𝑠𝑠𝑎𝑛𝑐𝑒, 𝑠𝑐𝑜𝑢𝑡𝑖𝑛𝑔 and other missions

typedef __builtin_uint_t virtuaddr;

typedef SemanticPointer<virtuaddr> byteaddress; /* A․𝘬․a `metaaddress`. */

struct Memorydelegate {
  virtual void statistics(Memoryregion * r, char32_t unicode) = 0;
  virtual void issue(Memoryregion * r, byteaddress start, int nº) = 0;
};

/* void Reservoir(__builtin_int_t *𝑙𝑜𝑔₂Pages, __builtin_uint_t **pages, __builtin_uint_t 
  **avails); */

struct Memoryregion; struct µProc; struct Memoryaccess;

struct Memoryregion { /* See also --<🥽 Bounds.cpp>{Intervallic}. */
   
   Memoryregion(Memorydelegate * delegate);
      
   Memoryregion(void * 𝟺kbPages[], __builtin_int_t count, __builtin_int_t lastpageBytes, Memorydelegate * delegate);
   
   ~Memoryregion(); /* Exercises `Release𝟷ᵈ`. */
   
   int incorporate(__builtin_int_t bytesToTail, __builtin_int_t bytes, 
     void (^once𝘖rMultiple)(short bytes, uint8_t * partial𝘈𝘯𝘥𝘖𝘳𝟺kbPage)); /* May exercise `Acquire𝟷ᵈ`. */
   
   /* int incorporate(__builtin_int_t bytesToTail, __builtin_int_t bytes, 
     void (^once𝘖rMultiple)(short bytes, const Intervallic & virtue)); */
   
   int shiftout(__builtin_int_t bytes, void (^notin)(short bytes, uint8_t * partial𝘈𝘯𝘥𝘖r𝟺kbPage)); /* C․𝘧 Scandinavian `utrangera`. */
   
#pragma mark Easy: 'Consecutive', 'bounded' and 'disjunct'
   
   byteaddress relative(__builtin_int_t byteoffset) const;
   
   __builtin_uint_t& word(byteaddress unaligned, short &lshbits, void (^issue)(int nº)) const;
   
   uint8_t& operator[](__builtin_int_t idx);
   
   int keep(byteaddress unaligned, __builtin_uint_t word) const;
   
#pragma mark The Haitian wrap
   
   enum Sentinel { cyclic, last, /*, linear, bilinear, */ crash, bound }; /* Does not define e.g `⁸𝟷ᵈ` also for idx < 0. */
   
   uint8_t ⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, Sentinel wrap, __builtin_int_t totbytes, void (^keep)(uint8_t &shifted) = ^(uint8_t &) { });
   
   uint32_t mips𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥mips, Sentinel wrap, __builtin_int_t totmips, void (^keep)(uint32_t &shifted) = ^(uint32_t &) { });
   
   /* enum class Arrangement { 𝟾, 𝟷𝟼, 𝟹𝟸, 𝟼𝟺, lo𝟼𝟺, hi𝟼𝟺, lo𝟷𝟸𝟾, hi𝟷𝟸𝟾 }; */
   
   inline uint64_t intel(uint32_t ˡᵒword, uint32_t wordʰⁱ) { return uint64_t(wordʰⁱ)<<32 | ˡᵒword; }
   
#pragma mark Miscellaneous tasks and generalizations
   
   µProc * µP() const; /* A․𝘬․a 'processor'. */
   
   Memoryaccess * access() const; /* 𝘊․𝘧 --<🥽 Access.cpp> and --<Memaccess.h|cpp>. */
   
   __builtin_int_t bytes() const; __builtin_int_t bytesLeft() const; /* A․𝘬․a `debris` and `ᵇʸᵗᵉresidue`. */
   
   int alsoAtDealloc(void (^deferral)()); /* ☜😐: 🛵𝜆 */
   
   int foreach(void (^frame)(uint8_t *start, __builtin_int_t bytes, bool& stop));
   
#pragma mark Little and Big-endians
   
   /**  TODO: Measure energy consumption while 𝑝𝑢𝑚𝑝𝑖𝑛' 𝑛𝑒𝑡𝑤𝑜𝑟𝑘/𝑛𝑎𝑡𝑖𝑣𝑒. */
   
   int toggleNetworkAndNative(__builtin_int_t bytesSkip, __builtin_int_t bytes, 
     void (^ping)(bool &stop), void (^completion)(__builtin_int_t bytes)); 
     /*  REQ: O(1). See also `ᵗᵍᵍˡendian` defined below and 
         --<Additions.h>{OptimisticAsync8Copy}. */
   
#pragma mark Fields of Capacitors on Two-gates/feedbacked-inverters
   
   static void sediment(__builtin_int_t bytes, void (^once𝘖rNever)(Memoryregion& region),
     Memorydelegate * delegate = NULL); /* A․𝘬․a `scratch`, `cradle` and `nest`. */
   
   static int abduct(__builtin_int_t bytes, Memorydelegate * delegate, Memoryregion& region);
   
   static int reflect⁻ᵚ(Unicodes regular𝘖rLinkpath, 
     __builtin_int_t pagesOffset /*=0*/, __builtin_int_t pagesLength /*=0*/, 
     int (^transformAndResolve)(Unicodes path, void (^final)(const char * utf8)),
     Memoryregion& serpent, bool append𝙴𝙾𝚃at𝙴𝙾𝙵); /* ⬷ WORM = '𝑊𝑟𝑖𝑡𝑒₋𝑜𝑛𝑐𝑒₋read₋𝑚𝑎𝑛𝑦'. */
   
   static int reflectʳᵚ(Unicodes regularpath, 
     __builtin_int_t pagesOffset /*=0*/, __builtin_int_t pagesLength /*=0*/, 
     int (^transform)(Unicodes path, void (^final)(const char * utf8)), 
     Memoryregion& serpent, bool append𝙴𝙾𝚃at𝙴𝙾𝙵);
   
   /* Old document vs. 'editableOrAppend' a․𝘬․a --<🥽 i-node.cpp>{camera₋ready}. */
   
#pragma mark Toggling implicits
   
   Memoryregion(); /* ⬷ Required when in nested structures. See --<Ornaments.cpp>. */
   
   Memoryregion(const Memoryregion& other); /* ⬷ Required by `abduct₁`. */
   
😐; /* Idiom optional because of opaque, mandatory since `alsoAtDealloc`. */

#if __has_include(<Additions/Kirkbridge/911.h>)
#include <Additions/Kirkbridge/911.h>
#endif

void * ExactSeek₂(const void *key, const void *base, size_t num, size_t size,
  __builtin_int_t (^cmp)(const void *key, const void *elt));

template <typename T> T * ᵟBranch(Memoryview * stem, void * (^alloc)(int bytes), int 
  (^dyncast)(Memoryview shoot)) { struct X { Memoryview * stem; void * (^alloc)(
  int bytes); int (^dyncast)(Memoryview shoot); } x = { stem, alloc, dyncast }; 
  extern void * 💫(void *); return (T *)💫((void *)&x); } /* A․𝘬․a `Materialize`, 
  `Fullcircle`, `SymbolicPrint`, `Snapshot`, `Xerox` and `∂ranch`; E․𝘨 Unicodes uc = 
  Snapshot(myView); Also --<History.h> and --<ˢᵚCache.cpp>{CachedFile}. */

int IsPrefixOrEqual(const char *eightbitString, const char *eightbitPrefix);
/* Returns `int` indicating difference at branch, -1 if equal and `0` when string 
    contains neither prefix nor is equal. */

#pragma mark - 😐🎤💀 ”𝑇ℎ𝑒 ⚰️”

#define va_epilogue __builtin_va_end(__arg);
extern "C" void ASSEMBLERONLY Sheriff();
/* #define ⭐️ Sheriff();  After delivery, a non-inquisitorial system is assumed. */
enum Impediment { MustBeOrdered, JustSwap };
int OptimisticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, Impediment it); /* Non-
atomic, yet consistent and gracefully failing indicated through a non-zero return value. */
/* struct Peekey { __builtin_int_t 🥈 ⬚=2, 🗝=1; __builtin_int_t board₁, palm₂; }; */
#define 🔒(situ) OptimisticSwap(&situ.board₁, &situ.palm₂, MustBeOrdered)
#define 🔓(situ) OptimisticSwap(&situ.board₁, &situ.palm₂, JustSwap);
struct Bitfield { const char32_t * ident; uint32_t mask; 
  const char32_t * text; }; typedef Bitfield Register[];
struct AnnotatedRegister { const char32_t * header; int regcnt; const 
  Bitfield * regs; uint32_t init; const char32_t * footnote; };
inline uint32_t ᵗᵍᵍˡendian(uint32_t x) { return __builtin_bswap32(x); }
#ifdef __x86_64__ /* ⇇ A․𝘬․a `toggleNetworkAndNative`. */
inline uint64_t ᵗᵍᵍˡendian(uint64_t x) { return __builtin_bswap64(x); }
#define POSIX_FIBER
#elif defined __mips__
#define MIPS_VIRTUAL_MULTITHREADED
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
    struct Peel { /* Consider `Orbital` and `Principia`. */
      ucontext_t ctx;
      int 🥈 bytes = sizeof(ucontext_t);
      uint8_t alcoda[bytes]; /* ⌖ */
    };
    int Snapshot(Peel *ucp) LEAF;
    int Recall(const Peel *ucp) LEAFLING;
    void Incubate(Peel *ucp, void (*ufnc)(...), int argc, ...);
#ifdef __x86_64__
    register __builtin_uint_t rsp asm("rsp"), rbp asm("rbp");
#endif
    
    typedef Peel fiber_t;
    
    /* __attribute__ ((callback (ufnc, uctx))) */
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
    
    /* __attribute__ ((callback (ufnc, fib))) */
    inline void create(Fiber::fiber_t& fib, void (*ufnc)(Fiber::fiber_t *),
      void *(^alloc)(__builtin_int_t bytes) = Alloc) {
        Fiber::create(fib, (void (*)(void *))ufnc, (void *)&fib, alloc);
    }
    
    MACRO void swap(fiber_t& nxt, fiber_t& prv)
    { if (Snapshot(&prv) == 0) Recall(&nxt); }
    
    MACRO void start(fiber_t& nxt) { Recall(&nxt); }
    
}

#define STRINGIFY(str) #str
#define va_prologue(symbol)                                                 \
  __builtin_va_list __arg;                                                  \
  __builtin_va_start(__arg, symbol);

#pragma mark - 😐😇

struct Chronology {
    
    typedef octa Instant; typedef uint32_t UQ32; /* E.𝘨 0.101₂ = 1×1/2 + 0×1/4 + 1×1/8 = 5/8․ */
    
    /**  Given a timestamp, return year, month (1-12) and day (1-31). */
    
    Tuple<int32_t, int32_t, int32_t> date(Instant timestamp) const;
    
    /**
     
     Return hour (0-23), minute (0-59), seconds (0-59) and fractionals
     since midnight.
     
     */
    
    Tuple<int32_t, int32_t, int32_t, uint32_t> sinceMidnight(Instant ts) const;
    
    /**
     
     Create a timestamp from a date and a time.
     
     @param parts  Contains year, month (1-12), day (1-31), hour (0-23),
       minutes (0-59) and seconds (0-59)
     
     @param frac  The number of ≈232.83 ps intervals to add
     
     Epoch for the modified Julian day is 03/23/1955 at 15.00: When Saab J29 
     travels in 900.660 km/h.
     
     A correct abbreviation for the unit of time and also the measurements of 
     duration is 's'. It is not 'S' which stands for Siemens and admittance.
     
     One minute of geographic lattitude per hour = 1 kn = 1852.0 m/h. (Knot)
     
     */
    
    Opt<Chronology::Instant> timestamp(int32_t parts[6], UQ32 frac = 0) const;
    
    /**  Return a future instant.  The NTP defines epoch starting at the year 
      1900 at midnight before sunrise January the 1ˢᵗ and with a 32-bit unsigned 
      integer track 0 to 2³² - 1 = 4.294,967,295 seconds (approximately 136 earth 
      years) until a wrap occurs. */
    
    Instant
    addSeconds(
      Instant instant,
      uint32_t seconds,
      UQ32 frac
    ) const;
    
    /**  Only for unperturbed chronologies. For non-reversable chronologies,
      subtract throws an error. */
    
    Instant subtractSeconds(Instant instant, uint32_t seconds) const BLURTS;
    
    /**  Retrieve a - since the program started and given a chronology - unique 
      value in a 'strict monotonically increasing' serie. */
    
    __builtin_int_t ordinal(bool& didwrap) const; /* Wraps (𝄇) at `BUILTIN_INT_MAX`. */
    
    /**  Return weekday assuming a week starts on a Wednesday. (Encoded as 0.) */
    
    int dayofweek(Instant instant, int &wd) const; /* May return ≠0 ⟷ 'divergent methods recognized'. */
    
};

int
InstantToText(
  Chronology chronology,
  Chronology::Instant ts, bool inclFrac,
  void (^out)(char digitHyphenColonPeriodOrSpace)
);

 /*
  
  Mars got five days a week and five seasons per year:
  
   enum Veneuveteuean { Again, trout, loo, master, shoRt };
  
   …and also a longer relative of unknown periodicity.
  
  */
 
typedef Chronology Chronology🚀; /* I.𝘦 'Celestial fractional' with 'identical' epoc. */

typedef Chronology Chronology🦠; /* With 2⁻⁶⁵ 𝘢․𝘬․𝘢 `UQ65`; light
  travels approximately 8.126 𝑝m ('pico meter') per increment. */

/**  The unperturbed — yet based on ¹³³Caesium — chronology. */

Chronology& ComputationalChronology(); /* 𝖤․𝘨 for chronometers. A․𝘬․a `GMT` (therefore 
  60×60×24 seconds per day), without leap seconds/years and no summertime correction. */

/**  The chronology of the users' choice. A․𝘬․a `UTC` (therefore an exact multiple of 
  SI seconds, with leap seconds as well as summertime). */

Chronology& SystemCalendricChronology();

/* See --<Additions>--<Framewrk.h> for details on `Trap` and `Indicate`. */

/**  Correlative-relative, 𝘦․𝘨 xʳ∈[-1/2₋𝜀, +1/2₊𝜀] and xʳ∈[-π₊𝜀, +π₋𝜀]. */

typedef float floatʳ; typedef double doubleʳ;

/**  Subtractive-relative, 𝘦․𝘨 x⁺ʳ∈[0₋𝜀, 1₊𝜀) and x⁺ʳ∈[0₊𝜀, π₋𝜀). */

typedef float float⁺ʳ; typedef double double⁺ʳ;

typedef uint8_t uchar; typedef uint32_t uint32; typedef uint8_t byte;

#endif
