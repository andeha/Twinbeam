/*  Twinbeam.h (libTwinbeam_X_cdcdc7f.a)
    c++20 for clang to x86_64, Arm Cortex M0+, AAPL M1, Esp32 and Mips.
    Mips compiled using clang version 11.0.1
    x86_64 compiled using Xcode Version 10.2.1 (10E1001) 
    and/or clang-11.0.1. */

#ifndef __TWINBEAM_H
#define __TWINBEAM_H

#define NULL 0
#define INLINED __attribute__((always_inline))
#define MACRO inline INLINED
#define structᵢ struct __attribute__((internal_linkage))
#define unionᵢ union __attribute__ ((internal_linkage))
#define inexorable static __attribute__ ((internal_linkage)) /* ⬷ see '𝗇𝗆' for details. */
#define DISORDERABLE __attribute__((weak))
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef unsigned long long  uint64_t;
typedef long long           int64_t;
#if defined  __mips__ || defined __armv6__ || defined espressif
typedef unsigned long       uint32_t;
typedef long                int32_t;
typedef uint32_t            __builtin_uint_t;
typedef int32_t             __builtin_int_t;
#define TriboolUnknown 0xFFFFFFFF
#elif defined __armv8a__ || defined __x86_64__
typedef unsigned int        uint32_t;
typedef int                 int32_t; /* ≢'long'. */
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t; /* ⬷ a․𝘬․a 'sequential'. */
#define TriboolUnknown 0xFFFFFFFFFFFFFFFF
#define 𝟷𝟸𝟾₋bit₋integers /* and not '__is_identifier(__uint128_t)' nor __SIZEOF_INT128__. */
#endif
typedef unsigned short      uint16_t;
typedef short               int16_t; /* ≡ ᵐⁱᵖˢint. */
typedef __builtin_uint_t Tribool; /* ⬷ c․𝖿 'obekant', 'icke-lös' and 'embargo ₍im₎material'. (🎿) */
typedef struct bignum { /* Artificial: Scandinavian 'med-vet-ande'. */
  constexpr static int maxdigits = 628; /* To not: 'templates', … */
  char digits[maxdigits]; /* Unpacked binary coded decimals. */
  int signbit; /* Indicates with 𝟷 if positive and with -𝟷 if negative. */
  int lastdigit; /* High-order digit index. */
} bignum; /* ⬷ a very-long integer type. */
#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 __attribute__ ((nonnull))
#define 𝓵₋bignum 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 bignum
void initialize_bignum(𝓵₋bignum * n);
void int_to_bignum(int64_t ℤ, 𝓵₋bignum * n);
int digits_to_bignum(𝓵₋bignum * n, const char * digits);
void add_bignum(𝓵₋bignum * a, 𝓵₋bignum * b, 𝓵₋bignum * c);
void subtract_bignum(𝓵₋bignum * a, 𝓵₋bignum * b, 𝓵₋bignum * c);
void multiply_bignum(𝓵₋bignum * a, 𝓵₋bignum * b, 𝓵₋bignum * c);
void divide_bignum(𝓵₋bignum * a, 𝓵₋bignum * b, 𝓵₋bignum * c);
void digit_shift(𝓵₋bignum * n, __builtin_int_t I); /* ⬷ multiplies n by 10ᵈ. */
int compare_bignum(𝓵₋bignum * a, 𝓵₋bignum * b);
void print_bignum(𝓵₋bignum * n, void (^out)(char c));
struct Schoolbook { int64_t ℤ; int64_t modula, denom; int total₋nonpositive; };
typedef int32_t i32; typedef uint32_t u32; typedef int64_t i64; typedef uint64_t u64;
/* int sw₋fractions(uint64_t num, uint64_t denom, uint64_t &ℕ, uint64_t &modula); */
/* int hw₋fractions₁(uint32_t num, uint32_t denom, uint32_t &ℕ, uint32_t &modula); */
/* int sw₋fractions₂(uint32_t num, uint32_t denom, uint32_t &ℕ, uint32_t &modula); */
int fractions(uint32_t num, uint32_t denom, uint32_t &ℕ, uint32_t &modula); /* ⬷ Requires `sw₋fractions₂` and/or `hw₋fractions₁`. */
#if __has_builtin(__uint128_t) && __has_builtin(__int128_t)
int sw₋fractions(__uint128_t num, __uint128_t denom, __uint128_t &ℕ, __uint128_t &modula);
#endif
int hw₋fractions(int64_t num, int64_t denom, int64_t &ℤ, int64_t &modula, int * sum₋negative);
int hw₋fractions(int32_t num, int32_t denom, int32_t &ℤ, int32_t &modula, int * sum₋negative);
int IADD(short id, int32_t addend, int32_t augend, int32_t &ℕ₋hi, uint32_t &ℕ₋lo, int * sum₋negative);
int IMUL(short id, int32_t multipliand, int32_t multiplier, int32_t &ℕ₋hi, uint32_t &ℕ₋lo, int * product₋negative);
int Fused₋IMUL(short id, int32_t augend, int32_t multiplier, int invMultiplyThenAdd, int32_t &ℕ₋hi, uint32_t &ℕ₋lo, int * accumulator₋negative);
/* FOCAL int Initiate₋Zero(short id, int32_t &ℕ₋hi, uint32_t &ℕ₋lo) { extern uint32_t __ℕ₋🅻[4], __ℕ₋🅷[4]; __ℕ₋🅷[id]=0, __ℕ₋🅻[id]=0; /​* also IMUL(0,0,...). *​/ }
FOCAL int Initiate₋One(short id, int32_t &ℕ₋hi, uint32_t &ℕ₋lo) { extern uint32_t __ℕ₋🅻[4], __ℕ₋🅷[4]; __ℕ₋🅷[id]=0, __ℕ₋🅻[id]=1; /​* also IMUL(1,1,...) } */
#define BITMASK(type) enum : type
#ifdef  __mips__
#define Mips __asm__ __volatile__ (/* ".set noat   \n" */ ".set noreorder  \n" ".set nomacro    \n"
#elif defined __x86_64__
#define Intel👈 __asm { .intel_syntax noprefix /* Requires -fms-extensions */
#define IntelPlusATT👉 asm { .att_syntax .text
#elif defined __armv6__ || defined __armv8a__
#define ArmDS1S2 asm {
#endif
#define APPEND_PIMPL                                                         \
  struct Internals;                                                          \
  Internals * impl_;
#define 😐 APPEND_PIMPL }
template <typename T> struct SemanticPointer { T ref; }; /* ⬷ a․𝘬․a `DisjunctPointer` and `OptionalIntervallicPointer`. */
#define Salt(sym) extern void sym(); sym(); /* 'No params' ∧ 'no #include' ⟵ 'Local decl' + ftn-call. */
#define Pult💡(x) ++x /* ⬷ todo: Add atomic enclosure-history to 'non-advertised locality-preserving margin-note'. */
/* typedef timeserie<char32_t *, int, char *> Error₋timeserie, eps₋serie;
auto didRuckpultCommit = ^(char * ref, const int& error₋code, Version version) { }; */
#define gutter₋return₋init(serie,ref,code,complex) { extern eps₋serie complex; complex.create(serie,code,ref); }
#define gutter₋return₋stamp(serie,ref,code,complex) { extern eps₋serie complex; complex.update(serie,code,ref); }
#define gutter₋return₋close(serie,ref,code,complex) { extern eps₋serie complex; complex.update(serie,code,ref); complex.commit(didRuckpultCommit); }
#define Ruckpult💡(x,r) /* ⬷ a․𝘬․a 'error-gutter', 𝘪․e History with sequence and timestamps. */
#define UNITTEST(symbol) extern "C" void Unittest_##symbol() /* No # ∨ ␣ 'at end' ⟵ 'Token pasting' */
#define Panic(log,s) { print("\n\n'⬚'\nPanicking at ⬚ in ⬚:⬚\n",            \
  ﹟s(s), ﹟s(__FUNCTION__), ﹟s(__FILE__), ﹟d(__LINE__)); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog,s); } }
#define FINAL /*  …or DO₋NOT₋DESTABBILIZE */
#define LONGTOOTH /* __attribute__ ((deprecated("Marked LONGTOOTH."))) */
#define FOCAL
#define Si_FOCAL
#define OPT_Si_FOCAL
#define ENCLAVED
/* #define ⚠️₋IMPLICATIONS₋WHILE₋HARDTIMES */
#define ARGUMENTATIVE /* ⬷ a․𝘬․a 'ONLY₋FOR₋SOFT₋REALTIME'. */
#define MAY_CONTAIN_TRACES_OF_FIRM_REALTIME
#define INFLATABBLE
#define SYNTESIZABLE /* ⬷ i․𝘦 no loops, … */
#define FOSSILATED
#define CONTEMPLATE
#define 🚫🔌 ARGUMENTATIVE /* ⏲ */
#define PLUSKVAMCOMPLETE
#define CHRONOLOGICAL
#define SPATIALPERTUBAL
#define EVENTUALRETROSPECTIVE
#define ROTATIONAL
#define IRREVERSIb /* IRREVERSI♭ alt․ IRREVERSIꙎ. */
#define TRAJECTORAL /* also: TRAJECTORAL🝑 */
#define INITIALPROJECTIVE
#define IRREPABEL /* in German: 'reparierbar'. */
#define AMBIVALENT /* native: 'contra-polarisative'. */
#define DEFLECTIVE /* ⬷ e․𝘨 `Auntie`. */
#define ANTIPOLARISATIVE
#define DUALREFLECTIVE
#define CEDILLEPOSITIVE
#define CEDILLEINDUCTIVE
#define EVENTUALMACHINAL
#define REINTEGRATIVE
#define REFLECTIVEATTRACTIONAL
#define VERYLOGARITHMIC
#define BOOGIEABLATIVE
#define PROCESSACCUSATIVE
#define ALTERNATOPTIONAL
#define PRIMALTRANSLATIVE
#define ALTERNATESCHEDULATIVE
#define OPTIONALSCHEDULATIVE
#define CIRCULATIVE /* ⬷ a․𝘬․a 'averaged' ∧ '␣'. */
#define CONTEXTDESTILLATIVE
#define EUCLIDEANINCOHERENT /* ⬷ c𝖿․ subversive follows incoherence. */
#define NEXUS₋EBBERÖD /* ⬷ abstrakt maskin. */
#define STEERING₋GOLD /* ⬷ Catholic₋gregorian keys. */
#define KONTRA₋REPUDIAT /* ⬷ sensor-bonanza. */
#define APPLIED₋ATTR /* and LEGATO₋SOURCES. */
#define CIRKULATIV₋DEKRET /* ''' alt. 3 🌎. 12 9. */
#ifdef  __mips__
typedef uint32_t mips32_context[32]; /* ∎: mx=11 ∧ mz=23! */
typedef mips32_context jmp_buf2;     /* 🔎: 32. ⛅️rax! */
#elif defined __armv6__
typedef uint32_t arm_context[9];
typedef arm_context jmp_buf2;
#elif defined __armv8a__
typedef int64_t arm_context[9];
typedef arm_context jmp_buf2;
#elif defined espressif
typdef int32_t tensilica_context[9];
typedef tensilica_context jmp_buf2;
#elif defined __x86_64__
typedef int64_t x86_64_context[(9 * 2) + 3 + 16];
typedef x86_64_context jmp_buf2;
#endif
extern "C" { int setjmp2(jmp_buf2 env); void longjmp2(jmp_buf2 env,
 __builtin_int_t val); /* `__builtin_longjmp` requires last arg to be 
 const and bounded by `int`. Determined 𝑎₋𝑝𝑟𝑖𝑜𝑟𝑖 to be 𝙞𝙣𝙩. */ }
#if defined __armv6__ || defined  __mips__ || defined espressif
#define BLURT(str) { tetra t; t.bits = (uint32_t)(const char *)str;          \
 longjmp2(*JmpBuf(), int(t.unsigned_little_endian.lsh)); }
#elif defined __x86_64__ || defined __armv8a__
#define BLURT(str) { octa o; o.bits = (uint64_t)(const char *)str;           \
 longjmp2(*JmpBuf(), int(o.unsigned_little_endian.lst)); }
#endif
#define BLURTS /* Mandatory */
#define NEVERBLURTS /* Fortunately optional. */
#define FALLIBLE /* Unfortunately not mandatory while the constructor gently blurts. */
#define TRY { int __e = setjmp2(*JmpBuf()); if (!__e) {
#define CATCH } else {
#define END_TRY } }
extern "C" jmp_buf2 * /* volatile */ JmpBuf(); /* ⬷ a great symbol for a project break! */
structᵢ SharedOptional { bool populated; explicit SharedOptional() : populated(
  false) { } explicit operator bool() const { return populated; } };
#if defined  __mips__ || defined __armv6__ || defined espressif
typedef unsigned int size_t;
void * operator new(unsigned int size, void * here) noexcept;
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
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
namespace std { /* The standard residual */ typedef ::size_t size_t;
  template<class T> class initializer_list { const T *beg; size_t sz;
  initializer_list(const T * b, size_t s) : beg(b), sz(s) { } public: typedef
  T value_type; typedef const T& reference; typedef const T& const_reference;
  typedef size_t size_type; typedef const T * iterator; typedef const T *
  const_iterator; initializer_list() : beg(0), sz(0) { } size_t size() const {
  return sz; } const T * begin() const { return beg; } const T * end() const {
  return beg + sz; } }; template<class T> inline const T * begin(
  initializer_list<T> i) { return i.begin(); } template<class T> inline
  const T * end(initializer_list<T> i) { return i.end(); } }
/* ☜😐: 🔅 ⬷ Earlier remark still valid? */
MACRO __builtin_uint_t 🔎(__builtin_uint_t var) { return *((__builtin_uint_t 
 /* volatile */ *) var); }
MACRO __builtin_uint_t&  🔧(__builtin_uint_t var) { return (__builtin_uint_t&) 
 *(__builtin_uint_t /* volatile */ *)var; }
MACRO __builtin_uint_t TrailingZeros(__builtin_uint_t x) { if (x == 0) { return 
 sizeof(x)*8; } x=(x^(x-1))>>1; int c=0; for (; x; c++) { x >>= 1; } return c; }
/* ⬷ Not `__builtin_clzl` for Mips and `__builtin_clz` for Intel.  And for 
  contemplative consumption of abstraction, 𝑃𝑖𝑛𝑐𝑒 𝑎𝑏𝑠𝑡𝑟𝑎𝑖𝑡: */
MACRO void Envelop(__builtin_uint_t & x) { x=(x^(x-1)); }
MACRO __builtin_uint_t 🎭(__builtin_uint_t * symbol, __builtin_uint_t mask, 
 void (^update)(__builtin_uint_t& shifted) = ^(__builtin_uint_t&) { } ) {
 __builtin_uint_t word = *symbol, shift=TrailingZeros(mask), orig = mask&word,
 shifted = orig>>shift; if (update) update(shifted); __builtin_uint_t fresh =
 (shifted<<shift)&mask; *symbol = (word & ~mask) | fresh; return orig>>shift; } OPT_Si_FOCAL
/* Integer types char8_t and char32_t are both unsigned ⤐ */
enum class Ieee754form { Scientific, Saturn, Monetary, Scandinavian₋monetary }; /* ⬷ occasionally `intrinsic_and_base₋10`. */
DISORDERABLE void Format(double ℝ, Ieee754form f, void (^out)(char32_t 𝟷𝟶₋base));
int print(const char * utf8format,...); int mfprint(const char * utf8format,...);
int print(void (^out)(char8_t * u8s, __builtin_int_t bytes), const char * utf8format, ...);
struct Argᴾ { typedef void (^Unicode)(bool anfang, char32_t& prvNxt𝖤𝖮𝖳𝘖𝘳𝟶𝚡𝟶𝟶𝟶𝟶, void * context); 
 typedef void (^Output)(Unicode set, void * context); union { __builtin_int_t d; 
 __builtin_uint_t x, b; char8_t * utf8; struct /* Unicodes */ { char32_t * unicodes; 
 __builtin_int_t tetras; } ucs; char8_t c; char32_t uc; double f₁; float f₂; uint8_t bytes[16]; 
#if defined 𝟷𝟸𝟾₋bit₋integers
 __uint128_t U; __int128_t I;
#endif
 uint64_t pair[2]; struct { Output scalar; void * context; } λ; } value; int kind; };
Argᴾ ﹟d(__builtin_int_t d); Argᴾ ﹟x(__builtin_uint_t x); Argᴾ ﹟b(__builtin_uint_t b);
Argᴾ ﹟s(char8_t * utf8); Argᴾ ﹟s(const char8_t * utf8); Argᴾ ﹟s(const char * utf8);
Argᴾ ﹟S(__builtin_int_t tetras, char32_t * uc); Argᴾ ﹟S(__builtin_int_t tetras, const char32_t * uc);
Argᴾ ﹟c(char8_t c); Argᴾ ﹟c(char c); Argᴾ ﹟C(char32_t C);
#ifdef 𝟷𝟸𝟾₋bit₋integers
Argᴾ ﹟U(__uint128_t U); Argᴾ ﹟I(__int128_t I);
#endif
Argᴾ ﹟regs(__builtin_uint_t mask); Argᴾ ﹟λ(Argᴾ::Output scalar, void * context);
extern "C" { int atexit(void(*func)(void)); void exit(int); }
extern "C" void * (^Alloc)(__builtin_int_t); extern "C" void (^Fall⒪⒲)(void *);
/* __builtin_int_t 𝟺𝟶𝟿𝟼₋aligned₋frame(__builtin_int_t byte₋number, __builtin_int_t * modulo); */
struct 𝟺kbframes { __builtin_int_t page₋count; __builtin_uint_t *pages₋base, * idx₋avails; };
/* ⬷ a․𝘬․a expeditionary and 'void * pages[]'/'uint32_t avails[]'. */
int Acquire𝟷ᵈ(__builtin_int_t ﹟, 𝟺kbframes& one₋set, void (^every)(uint8_t 
 * 𝟸ⁿ₋frame, bool& stop));
int Release𝟷ᵈ(void * 𝟸ⁿ₋frame, 𝟺kbframes& one₋set, bool secure);
void Init₋frames(unsigned count, unsigned expeditionaries[]);
int ContiguousAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟);
int CoalescingAcquire(unsigned expeditionary, void **𝟺kbframes, __builtin_int_t ﹟);
int 🄕allo⒲(unsigned expeditionary, void **𝟺kbpages, __builtin_int_t ﹟);
/* void intel₋/mips₋mzda₋Reservoir(unsigned expeditionary, 𝟺kbframes * one₋set, 
 __builtin_int_t * pages₋in₋expedition); */
extern "C" { void * malloc(size_t); void free(void *); }
/* Pointer arithmetics and the pointers inner intrinsics implicits. */
enum class Sentinel { cyclic, last, /*, linear, bilinear, */ crash, bound };
__builtin_int_t Byteoffset⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, 
 Sentinel wrap, __builtin_int_t totbytes);
__builtin_int_t ByteoffsetMips𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥mips, 
 Sentinel wrap, __builtin_int_t totmips);
typedef __builtin_uint_t * WordAlignedRef; typedef uint8_t * ByteAlignedRef;
#ifdef __x86_64__
FOCAL MACRO ByteAlignedRef /* µA("x86_64", "haswell", x₁, x₂) */ Copy8Memory(
 ByteAlignedRef dst, /* const */ ByteAlignedRef src, __builtin_int_t bytes) {
 ByteAlignedRef org = dst; __asm__ __volatile__ ("rep movsb" : "+D"(dst),
 "+S"(src), "+c"(bytes) : : "memory"); return org; }  /* ⬷ a․k․a 'memcopy'. */
FOCAL int /* µA("Compare", "x86_64", "haswell", x₁, x₂) */ Compare8Memory(
 ByteAlignedRef p₁, ByteAlignedRef p₂, __builtin_uint_t bytes); /* ⏱😐🏁 */
#define MEASURE_START(prefix) int64_t prefix##Start = __rdtsc(); /* 𝚜𝚒𝚐𝚗𝚎𝚍 ⟵ Comparision */
#define MEASURE_END(prefix)                                                  \
 int64_t prefix##End = (int64_t)__rdtsc();                                   \
 int64_t prefix##Nanos = prefix##End - prefix##Start;                        \
 print(#prefix " measures ⬚ ns\n", ﹟d(prefix##Nanos));
/* #define PIC32SYMBOL(serie,symbol,vaddr) */
#define 🎭𝑋𝟾𝟼(storage,symmsk,...) 🎭((__builtin_uint_t *)(storage), INTEL_##symmsk __VA_OPT__(,) __VA_ARGS__)
#elif defined __armv6__ || defined __armv8a__
FOCAL ByteAlignedRef Copy8Memory(ByteAlignedRef dst, ByteAlignedRef src, __builtin_int_t bytes);
FOCAL int Compare8Memory(ByteAlignedRef p₁, ByteAlignedRef p₂, __builtin_uint_t bytes);
#elif defined __mips__
FOCAL ByteAlignedRef /* µA("mips", "r2", x₃, x₄) */ Copy8Memory(ByteAlignedRef 
  dst, ByteAlignedRef src, __builtin_int_t bytes);
FOCAL int /* µA("mips", "r2", x₃, x₄) */ Compare8Memory(ByteAlignedRef p₁, 
 ByteAlignedRef p₂, __builtin_uint_t bytes); /* ⬷ a․𝘬․a 'memcmp'. */
#define PIC32SYMBOL(serie,symbol,vaddr)                                      \
 constexpr uint32_t PIC32##serie##_##symbol = vaddr;                         \
 constexpr uint32_t PIC32##serie##_##symbol##CLR = (vaddr + 0x4);            \
 constexpr uint32_t PIC32##serie##_##symbol##SET = (vaddr + 0x8);            \
 constexpr uint32_t PIC32##serie##_##symbol##INV = (vaddr + 0xc);
#define PortRectifyAsOutputs(serie,X,tris) (*((uint32_t *)PIC32##serie##_##TRIS##X##CLR) = (uint16_t)(tris))
#define 🔎🎭𝑀𝑋(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__) 
#define 🔎🎭𝑀𝑍𝐷𝐴(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
#define 🔎🎭𝑀𝑍(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
MACRO uint32_t AsUncached(uint32_t vaddr) { return vaddr | 0x20000000; } /* ⬷ a․𝘬․a `KSEG0ToKSEG1`. */
MACRO uint32_t AsPhysical(uint32_t vaddr) { return vaddr & 0x1FFFFFFF; } /* ⬷ a․𝘬․a `VToP`. */
#endif
ByteAlignedRef Clear8Memory(ByteAlignedRef mem, __builtin_int_t bytes);
ByteAlignedRef Overwrite8Memory(ByteAlignedRef src, uint8_t val,
 __builtin_int_t bytes);
#define WHEN_COMPILING constexpr static
#define 🥈ᵢ WHEN_COMPILING __attribute__ ((internal_linkage))
#define 🥈 WHEN_COMPILING /* ⬷ must be assigned to a 'const' and no inline assembler. */
__builtin_int_t constexpr Syspagesize() { return 4096; }
/* ⬷ one definition of 𝘮𝘢𝘯𝘺 ∧ ¬𝘴𝘤𝘢𝘭𝘢𝘳 (especially when Nand vs. Nor.) */
/** place a type along frame₍consecutives₎ alternatively on heap: */
template <typename T> T /* ⤪_ */ * Multiple(short exp𝗔ltNeg, 
  __builtin_int_t count, void (^default𝘖rNull)(T * elem)
)
{ T * base = NULL;
  if (exp𝗔ltNeg == -1) { base = (T *)Alloc(count*sizeof(T)); }
  else {  __builtin_int_t 🥈 𝟺𝟶𝟿𝟼 = Syspagesize();
    __builtin_int_t bytes=sizeof(T)*count,﹟=bytes/𝟺𝟶𝟿𝟼;
    void * 𝟺kbframes[1 + ﹟ + (bytes % 𝟺𝟶𝟿𝟼 ? 0 : 0)]; /* ⬷ the variable '﹟' is positive so ⌊⌋. */
    if (ContiguousAcquire(exp𝗔ltNeg,𝟺kbframes,﹟)) { return NULL; }
    base = (T *)𝟺kbframes[0];
  } /* ⬷ first-fit, most-recently-used and closest-fit. */
  for (__builtin_int_t i=0; i<count; ++i) { T * elem = new (i + base) T(); 
    if (default𝘖rNull) { for (__builtin_int_t i=0; i<count; ++i) { default𝘖rNull(base+i); } }
  }
  return base;
} /* ⬷ a․𝘬․a malloc, Startupalloc and Elements𝘖𝘳Heap. */
#define copy₋block(...) ((__typeof(__VA_ARGS__))_Block₋copy((const void *)(__VA_ARGS__)))
#define release₋block(...) _Block₋release((const void *)(__VA_ARGS__))
struct Block₋descriptor { unsigned long int reserved; unsigned long int size;
 void (*copy)(void *dst, void *src); void (*dispose)(void *); };
struct Block₋layout { void * isa; int flags; int reserved; void (*invoke)(void *, 
 ...); struct Block₋descriptor * descriptor; /* Imported variables. */ };
MACRO void * _Block₋copy(const void * arg) { struct Block₋layout * block = (struct 
 Block₋layout *)arg; struct Block₋layout * y = (struct Block₋layout *)Alloc(
 block->descriptor->size); Copy8Memory((ByteAlignedRef)y, (ByteAlignedRef)
 block, block->descriptor->size); return y; }
MACRO void _Block₋release(const void *arg) { Fall⒪⒲((void *)arg); }
typedef __builtin_uint_t BinaryChoice; BITMASK(BinaryChoice) {
  BinaryChoiceToLeft = 0b0, BinaryChoiceToRight = 0b1 };
#define NEVERBLURTS /* Fortunately undefined for script, kiddies. */
FOCAL void Base𝕟(/* TeX §64, §65 and §67 */ __builtin_uint_t ℕ, unsigned 
 short base, unsigned short digitsOr0, /* Not more than 32 alt. 64 digits 
 depending on word size! (Or set to `0` to skip leading zeros.) */ void
 (^out)(char 𝟶to𝟿));
void Base𝕫(__builtin_int_t ℤ, unsigned short base, unsigned short digitsOr0, void (^out)(char 𝟶to𝟿and₋));
#ifdef 𝟷𝟸𝟾₋bit₋integers
void Base𝕫(__int128_t ℤ, unsigned short base, unsigned short digitsOr0, void (^out)(char 𝟶to𝟿and₋));
void Base𝕟(__uint128_t ℕ, unsigned short base, unsigned short digitsOr0, void (^out)(char 𝟶to𝟿));
#endif
#define SIGNBIT_INT32 0x80000000
#define SIGNBIT_INT64 0x8000000000000000
/* ⬷ a․𝘬․a INT₋MIN and '0b1<<31alt63'. */
MACRO int64_t 𝟸₋compl(int64_t x) { x=~x; return ++x; }
MACRO int32_t 𝟸₋compl(int32_t x) { x=~x; return ++x; }
MACRO int64_t abs64i₁(int64_t x) { return x < 0 ? 𝟸₋compl(x) : x; }
MACRO int32_t abs32i₁(int32_t x) { return x < 0 ? 𝟸₋compl(x) : x; }
MACRO int64_t abs64i₂(int64_t x) { return __builtin_llabs(x); }
MACRO int32_t abs32i₂(int32_t x) { return __builtin_abs(x); }
template <typename ℕ> void invert(ℕ & x) { x = ~x; } /* ⬷ a․𝘬․a 'toggle₋all'. */
template <typename ℕ> void 𝟸₋Compl(ℕ & x) { invert(x); ++x; }
template <typename ℤ> ℤ abs₂(ℤ x) { return x < 0 ? 𝟸₋Compl(x) : x; }
/* ⬷ When x is set to INT_MIN, the interpretation is not representable as a positive 
 number and maps back to the same bit pattern when 2-complemented. (Two-complementing 
'identity a․𝘬․a zero' wraps and equals 0 when pattern is assumed unsigned.) */
/* ⬷ a․𝘬․a INTERFERENT, ABELIAN, TOTALITARIAN and NEITHER_PROLOGUE_NOR_EPILOGUE. */
#define MOMENT /* ⬷ attribute-at-end for method declarations a․𝘬․a 'LEAF' and 'do not follow'. */
#define moment /* ⬷ initial attribute for function definitions and declarations a․𝘬․a 'leaf'. */
#define intrinsic₋leaf /* ⬷ a․𝘬․a 'half₋leaf'; multiple attempts-w(as)-silicon-based. */
#define leaf₋function /* ⬷ ...except intrinsic functions! */
#define /* PROVOCATIVE */ ASSEMBLERONLY __attribute__((naked)) 
#ifdef __x86_64__
#define READONLY __attribute__ ((section(".rodata,.rodata")))
#elif defined __mips__
#define READONLY __attribute__ ((section(".rodata")))
#define COHERENT __attribute__ ((section(".coherent")))
#elif defined __armv6__ || defined __armv8a__
#define READONLY __attribute__ ((section(".rodata")))
#elif defined espressif
#define READONLY __attribute__ ((section(".rodata")))
#endif
/* #define STRANGE_MAIN void _Noreturn main */
#define Sourpatch(sym,msg) /* ⬷ a․𝘬․a 'link-forget' and 'retrospective-invisible' . */
#define IsOdd(x) ((x) & 0b1) /* ⬷ simultaneously int32_t ∧ int64_t. 
 H: x & 0b010 ⟷̸ ◻️⃞. See --<math>--<erf.cpp>{⁽₋1⁾ᵏ|alt}. */
/* ⬷ also: 'odd' is closed under multiplication. */
template <typename T> T max(T x₁, T x₂) { return x₁ < x₂ ? x₂ : x₁; }
template <typename T> T min(T x₁, T x₂) { return x₂ < x₁ ? x₂ : x₁; }
namespace Relative {
template <typename T> T relative(T x₁, T x₂) { return x₂/x₁; }
template <typename T> T difference(T x₁, T x₂) { return x₁ - x₂; }
template <typename T> T ˡchange(T x₁, T x₂) { return (x₁ - x₂) / x₂; } /* ∈[0,1]. */
template <typename T> T ʳchange(T x₁, T x₂) { return (x₂ - x₁) / x₁; } /* ∉[0,1]. */
#if (defined __mips__ || defined __armv6__ || defined espressif) && defined __cpp_concepts
#define innominate auto /* ⬷ a․𝘬․a 'innominate-type'. */
template <typename T> concept Relative₋accumulative = requires (T x₁, T x₂) {
 x₁ + x₂ /* -> int */; /*{*/ x₁ - x₂ /*} -> Same<bool>*/; Zero(x₂) /* -> T*/; };
 /* ⬷ a․𝘬․a 'Turtle' and 'algebraic category'. To instatiate write similar to 
 'template <Relative₋accumulative T>' ... , 
 'template <typename T> requires Relative₋accumulative<T> T operator... and 
 'void foo(Relative₋accumulative innominate & x) { ... }'. */
#endif
template <typename T> int collate₋coalesce(__builtin_int_t count, T xᵣ[], T * acc, 
 int (^port)(T x, T & acc)) { for (__builtin_int_t i=0; i<count; i++) { 
 int ok=port(xᵣ[i],*acc); if (!ok) { return ok; } } } /* ⬷ also known as: 'norm', 
 'linear-combine', also 'gaussian₋combination', 'irreversive₋combination' and 
 'permutative₋combination'. */
template <typename ℚ> ℚ arithmetic(ℚ x₁, ℚ x₂) { return (x₁ + x₂) / 2; }
/* template <typename T> T geometric(T x₁, T x₂) { return sqrt(x₁*x₂); }; */
template <typename T> T biorythm₋average(T xt) { return sin(xt)*cos(xt); } /* ⬷ a․𝘬․a AB*sin(ω*t)*cos(ω*t). */
template <typename T> bool rel₋eq(T x₁, T x₂) { return !(x₁ < x₂ || x₂ < x₁); }
template <typename T> bool eql₋eq(T x₁, T x₂) { return x₁ == x₂; }; }
#define NOT_EVERYTIME const static
#define CARDINALS(...) enum Cardinal { __🄦hole=0, __VA_ARGS__ };            \
  static jmp_buf2 __snapshot;                                                \
  auto confess = ^(Cardinal sin) { longjmp2(__snapshot, (__builtin_int_t)sin); };
#define NEARBYCROSS                                                          \
  int __ctrl = setjmp2(__snapshot);                                          \
  switch (__ctrl)
#define 🧵(...) /* ✠ */ CARDINALS(__VA_ARGS__) NEARBYCROSS
#define 🥇 NOT_EVERYTIME
#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /* ⬷ a․𝘬․a '__block', 𝚊𝚏𝚏𝚎𝚌𝚝𝚊𝚋𝚕𝚎 and 𝒎𝒆𝒄𝒉𝒂𝒏𝒊𝒔𝒎; 𝘤𝘧․ 🎿 'jurid' and 'förekomst'. Also 'machinal'. */
template <typename T> T * Critic(const T * x) { return const_cast<T*>(x); }
template <typename T> T& Critic(const T &x) { return const_cast<T&>(x); } /* ⬷ a․𝘬․a "away 𝙘𝙤𝙣𝙨𝙩 evil". */
__builtin_int_t least₋possible₋residue(__builtin_int_t dividend, __builtin_int_t divisor);
/* ⬷ see --<Wiki>--<Essays>--<On clocks and time> and 'circular reasoning'. */
#define auto₋rollback(variable) decltype(variable)
#define ᶿ﹡ const * /* #define *⥃ const char * /​* ⬷ a․𝘬․a '*⥆' and '*⫩'. */
#define rt₋namespace namespace

#pragma mark utf-8

int UnicodeToUtf8(char32_t Ξ, void (^sometime₋valid)(char8_t * ξ, short bytes));

short Utf8Followers(char8_t lead𝘖r8Bit); /* ⬷ recognize modern `char8_t` formerly `uint8_t`. */

char32_t Utf8ToUnicode(char8_t * ξ, __builtin_int_t bytes);

struct Utf8Symbol { __builtin_int_t line, bytesOffset, count; }; /* ⬷ a․𝘬․a 'Utf8Location'. */

typedef struct PresentativeErrorUnicode { __builtin_int_t line1ˢᵗ, bytesOffset1ˢᵗ, lineLast, 
  bytesOffsetInclLast; } Utf8Interval; /* ⬷ a․𝘬․a 'Sourcelocation', e․𝘨 wrongly coded utf-8. */

#pragma mark seven-bit keyput/file and utf-8 strings

typedef signed char * 𝟽bit₋pointer;

struct 𝟽bit₋text { __builtin_int_t bytes; signed char * segment; };

struct 𝟽₋bitPath𝘖rBytes { __builtin_int_t bytes; char * segment; }; /* ⬷ type 
 'char' C implementation dependent whether signed/unsigned. See '-fno-signed-char'. */

struct utf8₋text { __builtin_int_t bytes; char8_t * segment; };

typedef union {
   double base﹟𝟸; /* Captures 2⁻¹⁰²² and 2¹⁰²³ or in engineering: 2․23×10⁻³⁰⁸ to 1․79×10³⁰⁸. */
   struct { uint32_t lst; int32_t mst; } signed_little_endian;
   struct { int32_t mst; uint32_t lst; } signed_big_endian;
   struct { uint32_t lst; uint32_t mst; } unsigned_little_endian;
   struct { uint32_t mst; uint32_t lst; } unsigned_big_endian;
   struct {
      unsigned mantissal : 32;
      unsigned mantissah : 20;
      unsigned exponent  : 11;
      unsigned sign      :  1;
   } binary64; /* ⬷ a․𝘬․a 'ieee754b﹟𝟸'. */
   /* struct { … } ieee754b﹟𝟷𝟶; a․𝘬․a 'decimal64'. */
   /* struct { 
      unsigned absolute  : 31;
      unsigned sign      :  1;
   } sgned; */
   int64_t sgned;
   uint64_t bits;
} octa;

struct Octa { uint32_t l, h; };

/*  MACRO double nearest₋naive(int64_t measure) { return (double)measure; }
MACRO int64_t nearest₋naive(double measure) { return (int64_t)measure; } 
 ⬷ incorrect truncation for negative fractions. */

__builtin_int_t 🥈 Wordbytes=sizeof(__builtin_uint_t);

#if !(defined __armv6__ || defined __MM__ || defined espressif)
#define IEEE754₋ARITHMETICS₋INSIDE
#endif /* ⬷ Tensilica Lx6 is Ieee754 single-precision only. */
#define GENERAL

MACRO double Nearest(int64_t measure)
{
#ifdef GENERAL
   uint64_t 🥈 sign₋bit = 0b1LL<<63; uint64_t 🥈 𝟹𝟸₋bits = 0xffffffff;
   int sign = sign₋bit & measure; /* ⬷ inquisitorial again. */
   if (measure<+0) { measure = -measure; } /* ⬷ a․𝘬․a __builtin_absll. */
   int64_t leading₋zeros = __builtin_clzll(measure);
   unsigned biased₋2ⁿexp = Wordbytes*8 - leading₋zeros; /* ⤪ 32 alt. 64 bits wide words. */
   int64_t mantissa = measure << leading₋zeros; mantissa >>= 12;
   Octa man₋bits; man₋bits.l = 𝟹𝟸₋bits & mantissa; man₋bits.h = mantissa>>32;
   octa afloat { .binary64 = { man₋bits.l, man₋bits.h, biased₋2ⁿexp, sign ? 1u : 0u } };
   return afloat.base﹟𝟸;
#elif defined __mips__
   Mips                                                                      
     "                                                        \n"            
     "  mtc1       $a1, $f0                                   \n"            
     "  mthc1      $a2, $f0                                   \n"            
     "  cvt.d.l    $f0, $f0                                   \n"            
     "  mfc1       $v0, $f0                                   \n"            
     "                                                        \n"            
   );                                                                        
#elif defined __x86_64__
   asm {                                                                     
     fild rdi                   /* ⬷ see Intel.FBLD and Intel.FBSTP. */     
     fstp xmm0                                                               
   } /* ⬷ enabled by '-fms-extension'. */                                   
#endif
} OPT_Si_FOCAL /* ⬷ a․𝘬․a 'Cast' and 'Convert'. */

MACRO int64_t Nearest(double measure, int * reciproc)
{
#ifdef GENERAL
#ifdef IEEE754₋ARITHMETICS₋INSIDE
   measure += 0.5; /* Add 0.5 before scissor for 'nearest', otherwise rounds towards zero. */
#endif /* ⬷ and 1.5 when negative and 'round towards -inf'. */
   octa integer { .base﹟𝟸=measure };
   unsigned biased₋exp = integer.binary64.exponent;
   int32_t unbiased₋exp = biased₋exp - 1022;
   *reciproc = biased₋exp < 1022 ? 1 : 0; /* also -0. */
   int64_t shifted = integer.binary64.mantissah; shifted <<= 32;
   shifted |= integer.binary64.mantissal;
   uint64_t 🥈 sign₋bit = 0b1LL<<32;
   if (*reciproc) { shifted <<= (unbiased₋exp & sign₋bit); }
   else { shifted <<= (unbiased₋exp & sign₋bit); }
   int sign = integer.binary64.sign;
   return sign ? -shifted : shifted;
#elif defined __mips__
   Mips                                                                      
     "                                                        \n"            
     "  round.l.d  $f12, $f12                                 \n" /* Rounded towards nearest/even with fixed point in fp-register. */
     "  mfc1       $v1,  $f12                                 \n"            
     "  mfhc1      $v0,  $f12                                 \n" /* Also recip.d. */
     "                                                        \n"            
   );                                                                        
#elif defined __x86_64__
   asm {                                                                     
     fld xmm0                                                                
     fistp rax              /* ⬷ Not Intel.ROUNDSD and not Intel.FRNDINT. */
   }                                                                         
#endif
} /* ⬷ a․𝘬․a 'Cast' and 'Convert'. (Rounded towards -inf: floor.l.d; rounded 
 towards +inf: ceil.l.d) */

/* #undef IEEE754₋ARITHMETICS₋INSIDE */
#undef GENERAL

#if defined __MZ__ || defined __armv6__ || defined espressif
#define NON₋SIMD
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
/* #undef NON₋SIMD */
#endif

#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
#if defined __x86_64__
#include <xmmintrin.h> /* ≥ SSE 4.2 */
#include <immintrin.h> /* ⬷ the 'crc_u32' intrinsic in smmintrin.h. */
#elif defined __armv8a__
#include <arm-neon.h> /* ⬷ on Firestorm (A14/M1): four 128-bit NEON piplines. */
#endif

union Treeint { struct { int64_t key; uint64_t val; } keyvalue; __uint128_t bits; };
#elif defined __mips__ || defined __armv6__ || defined espressif
union Treeint { struct { int32_t key; uint32_t val; } keyvalue; uint64_t bits; };
#endif /* ⬷ a․𝘬․a 'Autumn' and 'Treeℤ'. */

void * Insert(void * opaque, Treeint valkey, void * (^alloc)(int bytes));
void Forall(void ᶿ﹡ opaque, void (^dfs)(Treeint valkey, bool& stop));
Treeint * Lookup(void ᶿ﹡ opaque, Treeint leafkey);

#pragma mark - big endian ⟷ 'most signif. first', little endian ⟷ 'least sigif. first'

typedef union {
#ifdef 𝟷𝟸𝟾₋bit₋integers
  __uint128_t bits;
#endif
  struct { octa lso, mso; } little₋endian;
  struct { octa mso, lso; } big₋endian;
  struct { Octa l, h; } parts;
#ifdef __x86_64__
  __m128 intel; /* ⬷ 'sixteen po̲s̲s̲i̲b̲l̲y ̲u̲n̲a̲l̲i̲gn̲e̲d̲ divided into 𝙛𝙡𝙤𝙖𝙩 slots'. */
#endif
} sexdeca;

typedef union {
#ifdef __x86_64__
  __m256 intel; /* ⬷ 'thirty-two (p߫o߫s߫s߫i߫b߫l߫y߫ ߫u߫n߫a߫l߫i߫g߫n߫e߫d߫) bytes d͟i͟v͟i͟d͟e͟d͟ into 𝗳𝗹𝗼𝗮𝘁 slots'. */
#endif
  uint32_t eight₋tetra[8];
  uint8_t thirtytwo₋bytes[32];
  struct { sexdeca lss; sexdeca mss; } little₋endian;
  struct { sexdeca mss; sexdeca lss; } big₋endian;
} ditriaconta;

/**  Computes a cryptographic hash value similar to NIST FIPS PUB 180-4: 
  "Secure Hash Standard (SHS)", August 2015. */

int Hash(uint8_t * material, __builtin_int_t bytes, void (^ping𝘖r𝖭𝖴𝖫𝖫)(bool &stop), 
  void (^complete)(ditriaconta digest)); /* ⬷ a․𝘬․a 'fineprint'. */

#if defined  __mips__ || defined __armv6__ || defined espressif
#define BUILTIN₋INT₋MAX 2147483647
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
#define BUILTIN₋INT₋MAX 0x7FFFFFFFFFFFFFFF
#endif /* ~0b0>>1 */
/* ⬷ the constant INT₋MAX is an odd number. */

typedef union {
   float base﹟𝟸; /* For 2⁻¹²⁶ to 2¹²⁷ or 1․18×10⁻³⁸ to 3․40×10³⁸. */
   struct { uint16_t lsh; int16_t msh; } signed_little_endian;
   struct { int16_t msh; uint16_t lsh; } signed_big_endian;
   struct { uint16_t lsh; uint16_t msh; } unsigned_little_endian;
   struct { uint16_t msh; uint16_t lsh; } unsigned_big_endian;
   struct {
     unsigned mantissa : 23;
     unsigned exponent :  8;
     unsigned sign     :  1;
   } binary32; /* ⬷ a․𝘬․a 'ieee754base₋2'. */
   struct { /* for ±1×10⁻⁹⁵ to ±9.999999×10⁹⁶. */
     /* … */
   } decimal32; /* ⬷ a․𝘬․a 'ieee754_2008₋base₋10'. */
   uint32_t bits;
} tetra;

typedef uint32_t Tetra;

enum class Endianness { Native, Network };

#pragma mark - 📖😐 ”𝑈𝑛𝑖𝑐𝑜𝑑𝑒”

int Utf8Sync(char8_t **p); /* ⬷ backs at most 3 bytes to regain sync. */

inline char32_t Superscript(short 𝟶to𝟿) { return U'⁰'+𝟶to𝟿; } /* ⁰¹⋯⁹ */

inline char32_t Subscript(short 𝟶to𝟿) { return U'₀'+𝟶to𝟿; } /* ₀₁…₉; ⬷ For the computational chemistry inclined. */

struct Unicodes { __builtin_int_t tetras; char32_t * unicodes; };

enum { END_OF_TRANSMISSION = U'\u0004' };

#pragma mark - for 𝑝𝑖𝑔𝑒𝑜𝑛 𝑟𝑒𝑐𝑜𝑛𝑛𝑎𝑖𝑠𝑠𝑎𝑛𝑐𝑒, 𝑠𝑐𝑜𝑢𝑡𝑖𝑛𝑔 and other missions
#pragma mark - still images, timeseries and language analysis
#pragma mark - c․𝘧 Scandinavian 'by₋tes' a․𝘬․a '✠✠'
#pragma mark - touting strong radio (🦠)

struct structure {
  void * (^leaf₋alloc)(int bytes) = ^(int bytes) { return Alloc(bytes); };
  int lengthen(__builtin_int_t ﹟, void * fixedKbframes[]);
  uint8_t * relative(__builtin_int_t byte₋offset);
  int copy₋append(__builtin_int_t bytes, uint8_t * material, void (^inflate)(
   __builtin_int_t ﹟, bool& cancel)); __builtin_int_t bytes();
  void *treelist=NULL, *cached₋tile; __builtin_int_t cached₋number=-1, 
   tile₋count=0, bytes₋per₋tile, unused₋bytes=0;
  struct Legator { __builtin_int_t tree₋out=0; } leg;
}; /* ⬷ a․𝘬․a 'Sequence', 'Array', '𝟺kbTiles' and 'reflecto₋tiles'. */

inline int Copy₋append₁(unsigned expeditionary, structure& sequence, 
  __builtin_int_t bytes, uint8_t * material
)
{
  auto amend = ^(__builtin_int_t ﹟, bool& cancel) { void * 𝟺kbframes[﹟]; 
   if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { cancel=true; }
   if (sequence.lengthen(﹟,𝟺kbframes)) { cancel=true; } };
  return sequence.copy₋append(bytes,material,amend);
}

inline int Copy₋append₂(structure& sequence, __builtin_int_t bytes, uint8_t * material)
{
  auto amend = ^(__builtin_int_t ﹟, bool& cancel) { void * 𝟺kbpages[﹟]; 
   for (__builtin_int_t i=0; i<﹟; ++i) { 𝟺kbpages[i] = Alloc(sequence.bytes₋per₋tile); }
   if (sequence.lengthen(﹟,𝟺kbpages)) { cancel=true; } };
  return sequence.copy₋append(bytes,material,amend);
}

inline int Setup₋shattered(unsigned expeditionary, __builtin_int_t ﹟, 
 structure& sequence) { void * 𝟺kbpages[﹟]; 
   sequence.bytes₋per₋tile = Syspagesize();
   if (CoalescingAcquire(expeditionary,𝟺kbpages,﹟)) { return -1; }
   if (sequence.lengthen(﹟,𝟺kbpages)) { return -2; }
   return 0;
}

inline int Setup₋initially₋one(__builtin_int_t bytes, structure& sequence)
{  sequence.bytes₋per₋tile = bytes;
   void * fixedKbframes[] = { Alloc(bytes) };
   if (sequence.lengthen(1,fixedKbframes)) { return -1; }
   return 0;
}

struct memoryview { structure * scatter; __builtin_int_t bytesoffset, bytecount; };
  
/* enum { 𝟾, 𝟷𝟼, 𝟹𝟸, 𝟼𝟺, lo𝟼𝟺, hi𝟼𝟺, lo𝟷𝟸𝟾, hi𝟷𝟸𝟾, utf8 } */

struct Convoj { structure material, vitruvi; __builtin_int_t count=0; 
  int init(__builtin_int_t bytes₋material, __builtin_int_t initial₋count);
  uint8_t * at(__builtin_int_t idx, __builtin_int_t * bytes); void pop() { --count; }
  int copy₋include(__builtin_int_t count, __builtin_int_t bytes[], ...);
};

inline uint8_t * Convoj::at(__builtin_int_t idx, __builtin_int_t * bytes)
{ const __builtin_int_t genesis=0; __builtin_int_t & acclast₋₁ = Critic(genesis);
   if (idx > 0) { acclast₋₁ = *(__builtin_int_t *)vitruvi.relative((idx-1)*sizeof(__builtin_int_t)); }
   __builtin_int_t & acclast = *(__builtin_int_t *)vitruvi.relative(idx*sizeof(__builtin_int_t));
   *bytes = acclast - acclast₋₁; return material.relative(acclast₋₁);
}

template <typename G/*riller*/>
struct ˢConvoj { structure inner; __builtin_int_t count=0; 
  ˢConvoj(std::initializer_list<G> lst) { init(lst); } ˢConvoj() { init({}); }
  ˢConvoj& operator=(std::initializer_list<G> lst) { init(lst); return *this; }
  /* Convoj& operator=(G * other) { return *this; } */
  G& operator[](int idx) { return (G &)*(G *)inner.relative(idx*sizeof(G)); }
  void pop() { --count; } int init(std::initializer_list<G> lst);
  int copy₋include(int count, G * Ɀ, int cycles=1);
};

template <typename G>
int ˢConvoj<G>::init(std::initializer_list<G> lst)
{
   /* int Setup₋shattered(unsigned expeditionary, __builtin_int_t ﹟, 
    structure& sequence); */
   const G * b = begin(lst); const G * e = end(lst);
   __builtin_int_t count = e - b;
   if (Setup₋initially₋one(sizeof(G)*count,inner)) { return -1; }
   if (copy₋include(count,Critic(b),1)) { return -2; }
   return 0;
}

template <typename G> 
int ˢConvoj<G>::copy₋include(int count, G * Ɀ, int cycles)
{
   for (int i=0; i<cycles; ++i) { if (Copy₋append₂(inner,sizeof(G)*count,
    (uint8_t *)Ɀ)) { return -1; } } return 0; /* int Copy₋append₁(unsigned 
   expeditionary, structure& sequence, __builtin_int_t bytes, uint8_t * material); */
}

template <typename E> using ˢKnots𝟷ᵈ = ˢConvoj<E>; /* ⬷ a․𝘬․a 'Sequence'. */
using Knots𝟷ᵈ = Convoj; /* ⬷ a․𝘬․a 'Convenient-for-bloodknots'. */

int Snapshot(const structure& original, structure & pristine);
int ToggleNetworkAndNative(structure &region, __builtin_int_t bytes₋skip, __builtin_int_t 
  bytes, void (^ping)(bool &stop), void (^completion)(__builtin_int_t bytes)); 

struct Bits { structure * scatter; uint8_t& operator[](__builtin_int_t idx);
uint8_t ⁸𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥bytes, Sentinel wrap, 
  __builtin_int_t totbytes, uint8_t * towrite𝘖r𝖭𝖴𝖫𝖫=NULL);
uint32_t mips𝟷ᵈ(__builtin_int_t byteNº, __builtin_int_t 𝛥mips, Sentinel wrap, 
  __builtin_int_t totmips, uint32_t * towrite𝘖r𝖭𝖴𝖫𝖫=NULL);
uint64_t /* a․𝘬․a 'ieee754dbl₋pattern' */ intel(uint32_t ˡᵒword, uint32_t wordʰⁱ) 
 { return uint64_t(wordʰⁱ)<<32 | ˡᵒword; }
}; /* ⬷ a․𝘬․a 'Memoryregion'. */

/* When 'change', 'delete' and 'type', see --<2ᵈ-𝔣ow.hpp>. Note that the accessor 
 is not called from 'push' and 'pop'. */

void * ExactSeek₂(const void *key, const void *base, size_t num, 
 size_t size, int (^cmp)(const void *key, const void *elt));

int IsPrefixOrEqual(const char *𝟽alt𝟾₋bitstring, const char *𝟽alt𝟾₋bitprefix);
/* ⬷ returns `int` indicating difference at branch, -1 if equal and `0` when string 
    contains neither prefix nor is equal. */

#pragma mark - 😐🎤💀 ”𝑇ℎ𝑒 ⚰️”

#define va_epilogue __builtin_va_end(__various);
extern "C" void ASSEMBLERONLY Sheriff();
/* #define ⭐️ Sheriff();  After delivery, a non-inquisitorial system is assumed. */
enum Impediment { MustBeOrdered, JustSwap };
int OptimisticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, Impediment it);
/* ⬷ non-atomic, yet consistent and gracefully failing indicated through a 
 non-zero return value. */
/* struct Peekey { __builtin_int_t 🥈 ⬚=2, 🗝=1; __builtin_int_t board₁, palm₂; }; */
#define 🔒(situ) OptimisticSwap(&situ.board₁, &situ.palm₂, MustBeOrdered)
#define 🔓(situ) OptimisticSwap(&situ.board₁, &situ.palm₂, JustSwap)
struct Bitfield { const char32_t * ident; uint32_t mask; const char32_t * text; }; typedef Bitfield Register[];
struct AnnotatedRegister { const char32_t * header; int regcnt; Bitfield * regs; uint32_t init; const char32_t * footnote; };
/* Time series and peg collections ⤐ */
struct Monoton { __builtin_int_t oldest=0; __builtin_int_t ordinal(bool * wrapped); };
/* ⬷ retrieve a unique value in a 'strict monotonic increasing serie. Wraps (𝄇) at 
BUILTIN₋INT₋MAX; a․𝘬․a 'stilistic chronology'. */
inline uint32_t ᵗᵍᵍˡendian(uint32_t x) { return __builtin_bswap32(x); }
inline uint64_t ᵗᵍᵍˡendian(uint64_t x) { return __builtin_bswap64(x); }
/* ⇇ a․𝘬․a 'toggleNetworkAndNative'. */

/* #include <Source/fiber₁> */
#include <Source/coroutine>

rt₋namespace Scheduler {
extern void * hw₋collection; /* ⬷ a․𝘬․a Map<irq₋no, Coroutine₋task>. */
extern struct Necklace *first, *curr, *last;
} /* ⬷ allocated by --<℮ ia64+pic32rt>--<llvm-rt3.cpp>. */

namespace Scheduler { void Init(); 
  
  /* typedef 𝟄₋int₁ (*Coroutine₋1)(void * ctx); /‌* ⬷ and at least one 
    of 'co_await', 'co_yield' and 'co_return'. */
  
  /*  𝟄₋int₁ y = co_await coroutine₋name(ctx);
   auto retrieved = ^(𝟄₋int₁& y) { return y.coroutine.promise().cached; };
   print("y-after-init-and-yield = ⬚\n", ﹟d(retrieved(y))); */
  
  int Incubate(𝟄₋int₁ * coroutine₋err, int32_t ﹟irq, 
   void * (^node₋alloc)(int bytes));
  
  int Process(int32_t ﹟irq, 𝟄₋int₁::Waiver * ref);
  
  struct Necklace { 𝟄₋int₁ & err; Necklace * nxt; };
  
  int Operational(𝟄₋int₁ * coroutine₋err, void * (^pearl₋alloc)(int bytes)); /* ⬷ a․𝘬․a 'Start' and 'Cyclic'. */
  
  MACRO void Proceed() { curr=curr->nxt; Resume(curr->err.coroutine.address()); }
  
  MACRO void Timer₋fired₁() { /* Save-ctx(curr->err) */ Proceed(); }
  
  MACRO void Timer₋fired₂() { /* context_t ctx; int y=getcontext(&ctx); */ Proceed(); /* setcontext(&ctx); */ }
  
}

#define bye co_return
#define co₋await co_await
#define initiera co_await
#define feedback co_yield
#define adjö co_return /* ⬷ s․a 'självet anser' and jmfr. 'jämför'. */
#define STRINGIFY(str) #str
#define va_prologue(symbol)                                                 \
 __builtin_va_list __various;                                               \
 __builtin_va_start(__various, symbol);

constexpr __builtin_int_t Frame(__builtin_uint_t size, __builtin_uint_t framesize)
{ return __builtin_int_t((size + framesize - 1) & ~(framesize - 1)); } 
/* ⬷ may be evaluated at compile-time a․𝘬․a 'constexpr'. */

constexpr __builtin_int_t Ceil(__builtin_int_t num, __builtin_int_t denom) 
{  int num₋neg=num<+0, denom₋neg=denom<+0;
  if (num₋neg) { num = -num; } if (denom₋neg) { denom = -denom; }
  __builtin_uint_t ℕ=num/denom, modula=num%denom; /* ⬷ also in sw/hw₋fractions. */
  int negative = denom₋neg ^ num₋neg ? 1 : 0;
  return (ℕ + (modula != 0 ? 1 : 0)) * (negative ? -1 : 1);
} /* ⬷ e․𝘨 ceil(sizeof(E)/4) = words, sizeof(E)/4 - 1 < words <= sizeof(E)/4. */

constexpr __builtin_int_t HowMany(__builtin_uint_t index, __builtin_uint_t width) {
  return (index % width == 0) ? index/width : index/width + 1; } 
/* ⬷ see all the multiple flavors of 'fraction' in --<System.cpp>. */

__builtin_int_t 🥈 Pagewords=Syspagesize()/Wordbytes; /* ⬷ a․𝘬․a 'arrangemang-
 possibly-window', 'ElemsInside4kb' and '𝟻𝟷𝟸alt𝟷𝟶𝟸𝟺'. */

namespace Fixpoint {
   
   union Q1615 { uint32_t bits; int32_t frac; }; /* ⬷ captures 0 to ±65535.9999694822. */
   union Q4815 { uint64_t bits; int64_t frac; }; /* ⬷ captures 0 to ±281474976710656.9999694822. */
   union Q3231 { uint64_t bits; int64_t frac; }; /* ⬷ captures 0 to ±4294967295.9999999995343387126922607421875. */
   union UQ3232 { uint64_t bits; struct { uint32_t lo, hi; } parts; }; /* ⬷ a․𝘬․a 'Ntp₋stomp', captures 0 to +4294967295.99999999976716935634613037109375. */
#if defined 𝟷𝟸𝟾₋bit₋integers
   union Q6364 { __uint128_t bits; __int128_t frac; }; /* ⬷ a․𝘬․a 'scientific₋sequential₋2'. */
#endif
   
#ifdef IEEE754₋ARITHMETICS₋INSIDE
   
   inline double q1615ToIeee754(Q1615 ℤ) { return double(ℤ.frac)*1.0/16384.0; }
   
   inline Q1615 Ieee754ToQ1615(long double ℤ) { int reciproc; 
      
      int64_t y = Nearest(ℤ*16384.0, &reciproc);
      
      return Fixpoint::Q1615 { .frac = (int32_t)y };
      
    }
   
#endif
   
#if defined 𝟷𝟸𝟾₋bit₋integers
   int suitable₋for₋nitpick(Q6364 ℤ, void (^easy₋read)(int neg, int count, 
    char groups[], char * unit₋name)); /* ⬷ a․𝘬․a Saturn-2. */
#endif
   
}
/* ⬷ type 'Q6364' adequate for measurements and computations for grids as small as 0.5 nm. */
/* ⬷ type 'Q3231' adequate representing 𝘦․𝘨 the 297 m non-linearity of earthly matters. */

#ifdef IEEE754₋ARITHMETICS₋INSIDE
inline Fixpoint::Q1615 operator "" _Q1615(long double ℝ) { return Fixpoint::Ieee754ToQ1615(ℝ); }
#endif

/* ⬷ consider 32- alt. 64-bits with an extra sign bit for abstractions such as 'Frame', 
 'isPowerOfTwo', 'leqAndPowerOfTwo' and 'geqAndPowerOfTwo'. */

#pragma mark - 😐😇

struct Chronology { enum Consequence { thus, totient /* a․𝘬․a Ɣ */ }; 
    
    typedef Octa instant; typedef uint32_t UQ32; /* e․𝘨 0.101₂ = 1×1/2 + 0×1/4 + 1×1/8 = 5/8․ */
    
    typedef Fixpoint::Q1615 relative;
    
    /**  Given a timestamp, return year, month (1-12) and day (1-31). */
    
    Tuple<int32_t, int32_t, int32_t> date(instant timestamp) const;
    
    /**
     
     Return hour (0-23), minute (0-59), seconds (0-59) and fractionals
     since midnight.
     
     */
    
    Tuple<int32_t, int32_t, int32_t, UQ32> sinceMidnight(instant timestamp) const;
    
    /**
     
     Create a timestamp from a date and a time.
     
     @param parts  Contains year, month (1-12), day (1-31), hour (0-23),
       minutes (0-59) and seconds (0-59)
     
     @param frac  The number of 1/2³² second ticks (≈232.83 ps) to add
     
     A correct abbreviation for the unit of time and also the measurements of 
     duration is 's'. It is not 'S' which stands for Siemens and admittance.
     
     One minute of geographic latitude per hour = 1 kn = 1852.0 m/h. (Knot)
     
     */
    
    Opt<Chronology::instant> integers₋encode(int32_t parts[6], UQ32 frac=0) const;
    
    /**  Return a future instant.  The NTP defines epoch starting at the year 
     1900 at midnight before sunrise January the 1ˢᵗ and with a 32-bit unsigned 
     integer track 0 to 2³² - 1 = 4.294,967,295 seconds (approximately 136 earth 
     years) until a wrap occurs. */
    
    instant
    addSeconds(instant relative, 
      uint32_t seconds, UQ32 frac
    ) const;
    
    /**  Only for unperturbed chronologies. For non-reversable chronologies, 
      subtract throws an error. */
    
    instant subtractSeconds(instant relative, uint32_t seconds, UQ32 frac) const BLURTS;
    
    /**  Return weekday assuming a week starts on a Wednesday. (Encoded as 0.) */
    
    int dayofweek(instant timestamp, int &wd) const; /* ⬷ may return ≠0 ⟷ 'divergent 
     methods recognized'. */
    
};

int
InstantToText(
  Chronology chronology,
  Chronology::instant ts, bool incl₋frac,
  void (^out)(char8_t digitHyphenColonPeriod𝘖rSpace)
);

 /*
  
  Mars got five days a week and five seasons per year:
  
   enum Veneuveteuean { Again, trout, loo, master, shoRt };
  
   …and also a longer relative of unknown periodicity.
  
  */
 
typedef Chronology Chronology🚀; /* ⬷ i․𝘦 'celestial fractional' with 'identical' epoc. */

typedef Chronology Chronology🦠; /* ⬷ with an 2⁻⁶⁵ a․𝘬․a 'UQ65'; light
  travels approximately 8.126 pm ('pico meter') per increment. */

/**  The unperturbed — yet based on ¹³³Caesium — chronology. */

Chronology& ComputationalChronology(); /*  𝖤․𝘨 for chronometers; a․𝘬․a 
 `GMT` (therefore 60×60×24 seconds per day), without leap seconds/years 
 and no summertime correction. */

/**  The chronology of the users' choice: a․𝘬․a 'UTC' (therefore an exact 
 multiple of SI seconds, with leap seconds as well as summertime). */

Chronology& SystemCalendricChronology();

/**  Translate an instant between a particular time zone and Unix UTC. */

Chronology::instant Timezone(Chronology chronology, Chronology::instant ts, 
 short quarters₋of₋hours₋offset);

/**  Relative-time interval when running from instant t₁ to instant t₂ given 
 preferable according to the 'ComputationalChronology'. */

Fixpoint::Q1615 Computational₋Δ(Chronology::instant t₁, Chronology::instant t₂);
/* ⬷ a․𝘬․a 'Interval', 'relative' and 'seconds₋and₋frac' and is calendric alt. 
 monotonically increasing non-rooting temporal relative. */

/**  Correlative-relative, 𝘦․𝘨 xʳ∈[-1/2₋𝜀, +1/2₊𝜀] and xʳ∈[-π₊𝜀, +π₋𝜀]. */

typedef float floatʳ; typedef double doubleʳ;

/**  Subtractive-relative, 𝘦․𝘨 x⁺ʳ∈[0₋𝜀, 1₊𝜀) and x⁺ʳ∈[0₊𝜀, π₋𝜀). */

typedef float float⁺ʳ; typedef double double⁺ʳ;

/**  Relative-fixative types: */

typedef char8_t uchar; typedef uint32_t uint32; typedef uint8_t byte;

#endif

