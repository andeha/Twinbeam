/* 
 * Twinbeam.h (and libTwinbeam_pic32mz|macos.a)                              
 * C23 and C++20 for clang to x86_64, Arm/AAPL M1-M2, Esp32 and Mips.        
 * Mips compiled using clang version 12.0.0 and x86_64 compiled on AAPL's    
 *'Command-line tools' (not Xcode) version 13.1.6 (21C46).
 */

#define inexorable static __attribute__ ((internal_linkage))
#define MACRO inline __attribute__((always_inline))
#define structᵢ struct /* __attribute__((internal_linkage)) */
#define unionᵢ union /* __attribute__ ((internal_linkage)) */
/*  see '𝗇𝗆' for details. */
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
#define TriboolUninit 0xFFFFFFFE
#define TriboolUnarbitrated 0xFFFFFFFD
#define ΨΛΩ (0)
#elif defined __armv8a__ || defined __x86_64__ || defined Kirkbridge
typedef unsigned int        uint32_t;
typedef int                 int32_t; /* ≢'long'. */
typedef uint64_t            __builtin_uint_t;
typedef int64_t             __builtin_int_t; /*  a․𝘬․a 'sequenta'. */
#define ΨΛΩ (0)
#define TriboolUnknown 0xFFFFFFFFFFFFFFFF
#define TriboolUninit 0xFFFFFFFFFFFFFFFE
#define TriboolUnarbitrated 0xFFFFFFFFFFFFFFFD
#endif
typedef unsigned short      uint16_t; /*  c𝘧․ Q16. */
typedef short               int16_t; /* ≡ ᵐⁱᵖˢint. */
typedef __builtin_uint_t Tribool; /*  c𝘧․ 'obekant' and 'embargo ₍im₎material'. */
/* TREEALTERNAT 
  ◻︎ ◻︎ ◻︎ ◼︎  ◻︎ ◻︎ ◼︎ ◻︎
  ◻︎ ◼︎ ◻ ◻︎  ◼ ◻ ◻ ◼
  ◼︎ ◻︎ ◼︎ ◼︎  ◻︎ ◼︎ ◼︎ ◼︎
  ◻ ◼︎ ◼ ◻︎  ◼︎ ◼︎ ◻︎ ◼︎ */
#define BITMASK(type) enum : type
#define Mips __asm__ __volatile__ (/* ".set noat   \n" */ ".set noreorder  \n" ".set nomacro    \n"
#define Intel👈 __asm { .intel_syntax noprefix /* Requires -fms-extensions */
#define IntelPlusATT👉 asm { .att_syntax .text
#define ArmDS1S1 asm {
#define ⓣ __attribute__((overloadable))
#define APPEND_PIMPL                                                         \
  struct Internals;                                                          \
  Internals * impl_;
#define 😐 APPEND_PIMPL }
#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 _Nonnull
#define Salt(sym) extern void sym(); sym(); /* 'No params' ∧ 'no #include' ⟵ 'Local decl' + ftn-call. */
#define Pult💡(x) ++x /*  todo: Add atomic enclosure-history to 'non-advertised locality-preserving margin-note'. */
#define CORRECT(symbol) EXT₋C void Unittest_##symbol() /* No # ∨ ␣ 'at end' ⟵ 'Token pasting' */
#define Panic(log,s) { print("\n\n'⬚'\nPanicking at ⬚ in ⬚:⬚\n",            \
  ﹟s7(s), ﹟s7((char *)__FUNCTION__), ﹟s7(__FILE__), ﹟d(__LINE__)); exit(-1); }
#define ENSURE(c,s) { if (!(c)) { Panic(Testlog,s); } }
#define FOCAL /* repoussé inexorable. */
#define ENCLAVED
#define MENTATIVE void /*  a․𝘬․a 'ONLY₋FOR₋SOFT₋REALTIME' and ARGUMENTATIVE. */
#if defined __cplusplus
#define EXT₋C extern "C"
#else
#define EXT₋C
#endif
#define false 0
#define true (! false)
#if defined __armv8a__ || defined __x86_64__ || defined Kirkbridge
#define 𝟷𝟸𝟾₋bit₋integer₋available
#define Native₋𝟷𝟸𝟾₋bit₋integers
#define Ieee754₋ARITHMETICS₋KEY
#undef OPTIMIZED₋NONGENERAL
#undef UNEXISTING₋IEEE754
#elif defined __MM__
#define 𝟷𝟸𝟾₋bit₋integer₋available
#define Synthetic₋𝟷𝟸𝟾₋bit₋integers /* this case encaged 128-bit integer and no 'overloading'. */
#undef Ieee754₋ARITHMETICS₋KEY /* we use the `struct sequent` type instead of the built-in `double` type. */
#undef OPTIMIZED₋NONGENERAL
#define NON₋SIMD /* nonavailable `double` type means we 'do not have a simd_tᵦ type'. */
#define NON₋SIMD₋YET₋DOUBLE
#define NON₋SIMD₋AND₋NO₋DOUBLE
#define UNEXISTING₋IEEE754
#elif defined __MZ__
#define 𝟷𝟸𝟾₋bit₋integer₋available
#define Native₋𝟷𝟸𝟾₋bit₋integers /* flag -fforce-enable-int128 is set from 'pic32nda' when on Mips. */
#define Ieee754₋ARITHMETICS₋KEY
#undef OPTIMIZED₋NONGENERAL
#define NON₋SIMD
#undef UNEXISTING₋IEEE754
#elif defined __armv6__ || defined espressif
#undef 𝟷𝟸𝟾₋bit₋integer₋available
#define Ieee754₋ARITHMETICS₋KEY
#undef OPTIMIZED₋NONGENERAL
#define NON₋SIMD
#undef UNEXISTING₋IEEE754
#endif /*  Tensilica Lx6 is Ieee754 single-precision only. */
#if defined Synthetic₋𝟷𝟸𝟾₋bit₋integers
struct 𝟷𝟸𝟾₋bit₋integer { int64_t hi; uint64_t lo; };
struct 𝟷𝟸𝟾₋bit₋unsigned { uint64_t hi, lo; };
typedef struct 𝟷𝟸𝟾₋bit₋integer __int128_t;
typedef struct 𝟷𝟸𝟾₋bit₋unsigned __uint128_t;
#endif
#if defined __mips_msa /* we have included pic32nda in pic32mzflags. */
/* #undef NON₋SIMD */
#endif
#if !defined Ieee754₋ARITHMETICS₋KEY
/* Here we create — based on `struct sequent` — the type similar to `double`. */
/* union sequent₋xs { uint64_t pattern; octa bits; }; */
#endif
#if defined __mips__
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
EXT₋C int setjmp2(jmp_buf2 env);
EXT₋C void longjmp2(jmp_buf2 env, __builtin_int_t val);
/* `__builtin_longjmp` requires last arg to be const and bounded by `int`. 
 Determined 𝑎₋𝑝𝑟𝑖𝑜𝑟𝑖 to be 𝙞𝙣𝙩. */
#if defined __armv6__ || defined __mips__ || defined espressif
#define BLURT(str) { tetra t; t.bits = (uint32_t)(const char *)str;          \
 longjmp2(*JmpBuf(), int(t.unsigned_little_endian.lsh)); }
#elif defined __x86_64__ || defined __armv8a__
#define BLURT(str) { octa o; o.bits = (uint64_t)(const char *)str;           \
 longjmp2(*JmpBuf(), int(o.unsigned_little_endian.lst)); }
#endif
#define BLURTS /* mandatory-unimplemented. */
#define NEVERBLURTS /* fortunately-optional. */
#define FALLIBLE /* unfortunately not mandatory in constructor-blurt. */
#define TRY { int __e = setjmp2(*JmpBuf()); if (!__e) {
#define CATCH } else {
#define END_TRY } }
EXT₋C jmp_buf2 * /* volatile */ JmpBuf(); /*  a great symbol for a project break! */
#define ᶿ﹡ const *

#if defined  __mips__ || defined __armv6__ || defined espressif
typedef unsigned int size_t;
#if defined __cplusplus
void * operator new(unsigned int size, void * here) noexcept;
#endif
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
typedef unsigned long size_t;
#if defined __cplusplus
void * operator new(unsigned long size, void * here) noexcept;
#endif
#endif /* on `Opt` minus `void *`: See 𝐶𝑟𝑎𝑠ℎ 𝑓𝑟𝑒𝑞𝑢𝑒𝑛𝑐𝑦, 𝑐𝑜𝑝𝑦/𝑝𝑎𝑠𝑡𝑒 and 𝑒𝑥𝑝𝑙𝑜𝑖𝑡𝑖𝚤𝑛𝑔 𝑢𝑛𝑖𝑛𝑖𝑡𝑖𝑎𝑙𝑖𝑧𝑒𝑑. */
/* ☜😐: 🔅  earlier remark still valid? */
MACRO __builtin_uint_t 🔎(__builtin_uint_t var) { return *((__builtin_uint_t 
 /* volatile */ *) var); } /* see --<after-eight.hpp> for write-not-read. */
MACRO __builtin_uint_t Trailing₋non₋ones(__builtin_uint_t x) { if (x == 0) { 
 return sizeof(x)*8; } x=(x^(x-1))>>1; int c=0; for (; x; c++) { x >>= 1; } return c; }
/*  not `__builtin_clzl` for Mips and `__builtin_clz` for Intel.  And for 
  contemplative consumption of abstraction, 𝑃𝑖𝑛𝑐𝑒 𝑎𝑏𝑠𝑡𝑟𝑎𝑖𝑡: */
MACRO void Envelop(__builtin_uint_t * x) { *x=(*x^(*x-1)); }

typedef uint8_t char8₋t;
typedef unsigned int char32̄_t;
#define KEYPUTS(x) ((signed char *)(x))
#define UNICODES(x) ((char32̄_t *)(U##x))
#define UTF8TEXT(x) ((char8₋t *)(u8##x))
/*  integer types char8_t and char32_t are both unsigned and unused in this project. */
typedef struct { char digits[628]; int signbit, lastdigit; } bigint;
typedef /* 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 */ bigint 𝓵₋bigint; /* arbitrary positioned decimal symbol. */
EXT₋C void ieee754₋Scientific₋Rendition(double ℝ, char * fiftysix₋ten₋base, int * letters);
EXT₋C void ieee754₋Saturn₋Rendition(double ℝ, char * fiftysix₋ten₋base, int * letters);
EXT₋C void ieee754₋Monetary₋Rendition(double ℝ, char * fiftysix₋ten₋base, int * letters);
EXT₋C void ieee754₋Scandinavian₋Monetary₋Rendition(double ℝ, char * fiftysix₋ten₋base, int * letters);
EXT₋C void int₋and₋bigint(int64_t ℤ, 𝓵₋bigint * 𝓫);
EXT₋C int digits₋and₋bigint(char * digits, 𝓵₋bigint * 𝓫);
EXT₋C void bcd₋bigint₋add(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * 𝓫);
EXT₋C void bcd₋bigint₋subtract(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * 𝓫);
EXT₋C void bcd₋bigint₋multiply(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * 𝓫);
EXT₋C void bcd₋bigint₋divide(𝓵₋bigint * x₁, 𝓵₋bigint * x₂, 𝓵₋bigint * 𝓫);
EXT₋C void bcd₋bigint₋shift(𝓵₋bigint * z, __builtin_int_t I); /* = multiplies 10^I */
EXT₋C int bcd₋bigint₋compare(𝓵₋bigint * x₁, 𝓵₋bigint * x₂);
EXT₋C int print(const char * sevenbit₋utf8format,...) ⓣ;
EXT₋C int mfprint(const char * sevenbit₋utf8format,...);
EXT₋C int print(void (^out)(char8₋t * u8s, __builtin_int_t bytes), const char * 
 sevenbit₋utf8format, ...) ⓣ;

#if defined 𝟷𝟸𝟾₋bit₋integer₋available
union Q6364 { __int128_t frac; __uint128_t bits; };
#endif
struct sequent { union Q6364 detail; int valid; };
typedef struct sequent Sequenta;
typedef Sequenta (^computational)(Sequenta x);
enum Newtoncontrol { Newton₋ok, Newton₋abort, Newton₋done };
struct sevenbit₋text { __builtin_int_t count; char * keyputs; };
struct utf8₋text { __builtin_int_t bytes; char8₋t * u8s; };
struct Unicodes { __builtin_int_t tetras; char32̄_t * unicodes; };
struct 𝟽₋bitPath𝘖rBytes { __builtin_int_t bytes; char * text; }; 
/*  type 'char' C implementation dependent whether signed/unsigned. 
 See '-fno-signed-char'. */

typedef void (^primary₋present)(__builtin_int_t count, char32̄_t * symbols);
typedef void (^serial₋present)(char8₋t * u8s, __builtin_int_t bytes);
/* a pointer is not marked 'indirect' alternatively 'direct' but with an -out suffix. */
typedef void (^Fragment1)(serial₋present, void *);
typedef void (^Fragment2)(primary₋present, void *);

typedef struct 𝓟 {
  union {
    __builtin_int_t d;
    __builtin_uint_t x, b;
    struct {
      char8₋t * utf8;
      __builtin_int_t bytes;
    } encoded;
    struct {
      char32̄_t * unicodes;
      __builtin_int_t tetras;
    } ucs;
    char possibly₋signed₋c;
    char32̄_t uc;
    struct {
      union { double f₁; float f₂; } material;
      int numberformat;
    } non₋fixpoint;
    uint8_t fullwidth[16];
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
    __uint128_t U; __int128_t I;
#endif
    struct { void * ctxt; Fragment1 block; } λ₁;
    struct { void * ctxt; Fragment2 block; } λ₂;
  } value;
  int kind;
} Argᴾ;

EXT₋C Argᴾ ﹟d(__builtin_int_t d);
EXT₋C Argᴾ ﹟x(__builtin_uint_t x);
EXT₋C Argᴾ ﹟b(__builtin_uint_t b);
EXT₋C Argᴾ ﹟S(__builtin_int_t tetras, char32̄_t * unterminated₋uc) ⓣ;
EXT₋C Argᴾ ﹟S(char32̄_t * zero₋terminated₋uc) ⓣ;
EXT₋C Argᴾ ﹟S(struct Unicodes ucs) ⓣ;
EXT₋C Argᴾ ﹟s7(char * sevenbit₋utf8) /* ⓣ */;
/* EXT₋C Argᴾ ﹟s7(const char * sevenbit₋utf8) ⓣ; */
EXT₋C Argᴾ ﹟s8(char8₋t * zero₋terminated₋u8s) ⓣ;
EXT₋C Argᴾ ﹟s8(__builtin_int_t bytes, char8₋t * unterminated₋u8s) ⓣ;
EXT₋C Argᴾ ﹟c7(char c);
EXT₋C Argᴾ ﹟C(char32̄_t C);
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
EXT₋C Argᴾ ﹟U(__uint128_t U); Argᴾ ﹟I(__int128_t I);
#endif
EXT₋C Argᴾ ﹟regs(__builtin_uint_t mask); /* cached at printout. */
EXT₋C Argᴾ ﹟plat(__builtin_uint_t mask); /* non-cached at primtout. */
EXT₋C Argᴾ ﹟λ₁(void (^fragment)(serial₋present,void *),void *);
EXT₋C Argᴾ ﹟λ₂(void (^fragment)(primary₋present,void *),void *);
#if !defined UNEXISTING₋IEEE754
EXT₋C Argᴾ ﹟F(double f, int method) ⓣ;
EXT₋C Argᴾ ﹟F(float f, int method) ⓣ;
#endif

EXT₋C void int₋to₋sequent(int64_t integer, Sequenta * real);
EXT₋C void fraction₋to₋sequent(int count, short zeroToNines[], 
 Sequenta * real); /* see TeX 102 §. */
EXT₋C Sequenta add_sequent(Sequenta x₁, Sequenta x₂);
EXT₋C Sequenta subtract_sequent(Sequenta x₁, Sequenta x₂);
EXT₋C Sequenta multiply_sequent(Sequenta x₁, Sequenta x₂);
EXT₋C Sequenta divide_sequent(Sequenta x₁, Sequenta x₂);
EXT₋C Sequenta absolute_sequent(Sequenta x₁, Sequenta x₂);
EXT₋C Sequenta negate_sequent(Sequenta x);
EXT₋C Sequenta floor_sequent(Sequenta x);
EXT₋C Sequenta modulo_sequent(Sequenta x₁, Sequenta x₂);
EXT₋C Sequenta product₋abelian(); /* a․𝘬․a `1`. */
EXT₋C Sequenta accumulative₋zero(); /* a․𝘬․a `0`. */
EXT₋C Sequenta piano₋ten(); /* a․𝘬․a `10`. */
EXT₋C Sequenta negative₋infinity(); /* a․𝘬․a -Inf. */
EXT₋C Sequenta positive₋infinity();
EXT₋C Sequenta redundant₋many(); /* a․𝘬․a two. */
EXT₋C int Newton(computational f, computational f₋prim, Sequenta * x₀, 
 void (^ping)(enum Newtoncontrol * ctrl));
EXT₋C Sequenta full₋atan(Sequenta y, Sequenta x);
EXT₋C int trapezoid(Sequenta (^f)(Sequenta), Sequenta delta₋t, 
 Sequenta min, void (^memory)(Sequenta integrale, Sequenta t₋acc, 
 int * stop));
typedef void (Numerics)(int count, char zeroAndNine[], int zero);
EXT₋C void natural₋sequent(Sequenta positive, Numerics out); /* TeX 103 §. */
EXT₋C void fractional₋sequent(Sequenta positive, Numerics out);

#define __builtin_fixpoint_add add_sequent
#define __builtin_fixpoint_sub subtract_sequent
#define __builtin_fixpoint_mul multiply_sequent
#define __builtin_fixpoint_div divide_sequent
#define __builtin_fixpoint_negate negate_sequent
#define __builtin_fixpoint_modulo modulo_sequent
#define __builtin_fixpoint_floor floor_sequent

inline Sequenta __builtin_fixpoint_min(Sequenta x₁, Sequenta x₂)
{
#if defined Native₋𝟷𝟸𝟾₋bit₋integers
  return x₁.detail.frac < x₂.detail.frac ? x₁ : x₂;
#elif defined Synthetic₋𝟷𝟸𝟾₋bit₋integers
  if (x₁.detail.frac.hi == x₂.detail.frac.hi) { return x₁.detail.frac.lo < x₂.detail.frac.lo ? x₁ : x₂; }
  else { return x₁.detail.frac.hi < x₂.detail.frac.hi ? x₁ : x₂; }
#endif
}

inline Sequenta __builtin_fixpoint_max(Sequenta x₁, Sequenta x₂)
{
#if defined Native₋𝟷𝟸𝟾₋bit₋integers
  return x₁.detail.frac < x₂.detail.frac ? x₂ : x₁;
#elif defined Synthetic₋𝟷𝟸𝟾₋bit₋integers
  if (x₁.detail.frac.hi == x₂.detail.frac.hi) { return x₁.detail.frac.lo < x₂.detail.frac.lo ? x₂ : x₁; }
  else { return x₁.detail.frac.hi < x₂.detail.frac.hi ? x₂ : x₁; }
#endif
}

extern Sequenta sqrt(Sequenta,int) ⓣ;
extern Sequenta reciproc(Sequenta) ⓣ;
inline Sequenta __builtin_fixpoint_sqrt(Sequenta x) { return sqrt(x,0); }
inline Sequenta __builtin_fixpoint_rsqrt(Sequenta x) { return sqrt(x,1); }
inline Sequenta __builtin_fixpoint_rcp(Sequenta x) { return reciproc(x); }

typedef int (^INIT)(void * uninited);
EXT₋C void * Alloc(__builtin_int_t);
EXT₋C void Fallow(void *) ⓣ;
typedef void * (*ALLOC)(__builtin_int_t);
typedef void (*FALLOW)(void *);
EXT₋C void * Heap₋alloc(__builtin_int_t);
EXT₋C __builtin_int_t Heap₋object₋size(void *);
EXT₋C void Heap₋unalloc(void *);
EXT₋C int Fallow(unsigned expeditionary, void *𝟺kbframes[], __builtin_int_t ﹟) ⓣ;
EXT₋C int ContiguousAcquire(unsigned expeditionary, void **fourkilobytespace, __builtin_int_t ﹟);
EXT₋C int CoalescingAcquire(unsigned expeditionary, void * fourkilobytes[], __builtin_int_t ﹟);
struct Expeditionary { __builtin_int_t pagecount; __builtin_uint_t * pagesbase, *overview; };
EXT₋C void Setupframelibrary(int count, struct Expeditionary *);
EXT₋C void * malloc(size_t bytes); EXT₋C void free(void *); 
EXT₋C int atexit(void(*func)(void)); EXT₋C void exit(int);

/* Pointer arithmetics and the pointers inner intrinsics implicits. */
typedef __builtin_uint_t * WordAlignedRef; typedef uint8_t * ByteAlignedRef;
EXT₋C ByteAlignedRef Copy8Memory(ByteAlignedRef dst, ByteAlignedRef src, __builtin_int_t bytes);
EXT₋C int Compare8Memory(ByteAlignedRef p₁, ByteAlignedRef p₂, __builtin_int_t bytes);
EXT₋C ByteAlignedRef Overwrite8Memory(ByteAlignedRef src, uint8_t val, __builtin_int_t bytes);
EXT₋C ByteAlignedRef Clear8Memory(ByteAlignedRef mem, __builtin_int_t bytes);

#pragma recto ⏱😐🏁

#define MEASURE_START(prefix) uint64_t prefix##Start = cycles();
#define MEASURE_END(prefix)                                                  \
 uint64_t prefix##End = cycles();                                            \
 uint64_t prefix##Nanos = prefix##End - prefix##Start;                       \
 print(#prefix " measures ⬚ ns\n", ﹟d((int64_t)(prefix##Nanos)));
#if defined __x86_64__
#define cycles __rdtsc
#elif defined __armv8a__
inline uint32_t cycles() { return *(unsigned *)0xe001004; }
/* ArmDS1S1  } 'mrs x0, CNTFRQ_EL0' and 'mrs x0, CNTPCT_EL0' and 'return 1000000*pct/frq'. */
#endif

#if defined __mips__
/* #define PIC32SYMBOL(serie,symbol,vaddr) */
#define PIC32SYMBOL(serie,symbol,vaddr)                                      \
 consteval uint32_t PIC32##serie##_##symbol = vaddr;                         \
 consteval uint32_t PIC32##serie##_##symbol##CLR = (vaddr + 0x4);            \
 consteval uint32_t PIC32##serie##_##symbol##SET = (vaddr + 0x8);            \
 consteval uint32_t PIC32##serie##_##symbol##INV = (vaddr + 0xc);
#define PortRectifyAsOutputs(serie,X,tris) (*((uint32_t *)PIC32##serie##_##TRIS##X##CLR) = (uint16_t)(tris))
#define 🔎🎭𝑀𝑋(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__) 
#define 🔎🎭𝑀𝑍𝐷𝐴(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
#define 🔎🎭𝑀𝑍(symval,msk,...) 🎭((__builtin_uint_t *)(symval), msk __VA_OPT__(,) __VA_ARGS__)
MACRO uint32_t AsUncached(uint32_t vaddr) { return vaddr | 0x20000000; } /*  a․𝘬․a `KSEG0ToKSEG1`. */
MACRO uint32_t AsPhysical(uint32_t vaddr) { return vaddr & 0x1FFFFFFF; } /*  a․𝘬․a `VToP`. */
#elif defined __x86_64__
#define 🎭𝑋𝟾𝟼(storage,symmsk,...) 🎭((__builtin_uint_t *)(storage), INTEL_##symmsk __VA_OPT__(,) __VA_ARGS__)
#endif

#pragma recto block and not function pointer

#define copy₋block(...) ((__typeof(__VA_ARGS__))_Block₋copy((const void *)(__VA_ARGS__)))
#define release₋block(...) _Block₋release((const void *)(__VA_ARGS__))
struct Block₋descriptor { unsigned long int reserved; unsigned long int size;
 void (*copy)(void *dst, void *src); void (*dispose)(void *); };
struct Block₋layout { void * isa; int flags; int reserved; void (*invoke)(void *, 
 ...); struct Block₋descriptor * descriptor; };
inline void * _Block₋copy(const void * arg) { struct Block₋layout * block = (struct 
 Block₋layout *)arg; struct Block₋layout * y = (struct Block₋layout *)Heap₋alloc(
 block->descriptor->size); Copy8Memory((ByteAlignedRef)y, (ByteAlignedRef)
 block, block->descriptor->size); return y; }
inline void _Block₋release(const void *arg) { Heap₋unalloc((void *)arg); }
typedef __builtin_uint_t BinaryChoice; BITMASK(BinaryChoice) {
  BinaryChoiceToLeft = 0b0, BinaryChoiceToRight = 0b1 };
#define NEVERBLURTS /* Fortunately undefined for script, kiddies. */

#pragma recto reading direction, planning and endianess

EXT₋C FOCAL void Base𝕟(/* TeX §64, §65 and §67 */ __builtin_uint_t ℕ, unsigned 
 short base, unsigned short digitsOr0, /* Not more than 32 alt. 64 digits 
 depending on word size! (Or set to `0` to skip leading zeros.) */ void
 (^out)(char 𝟶to𝟿)) ⓣ;
EXT₋C void Base𝕫(__builtin_int_t ℤ, unsigned short base, unsigned short digitsOr0, 
 void (^out)(char 𝟶to𝟿and₋)) ⓣ;
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
EXT₋C void Base𝕫(__int128_t ℤ, unsigned short base, unsigned short digitsOr0, 
 void (^out)(char 𝟶to𝟿and₋)) ⓣ;
EXT₋C void Base𝕟(__uint128_t ℕ, unsigned short base, unsigned short digitsOr0, 
 void (^out)(char 𝟶to𝟿)) ⓣ;
#endif

#pragma recto miscellaneous

#define SIGNBIT_INT32 0x80000000
#define SIGNBIT_INT64 0x8000000000000000
/*  a․𝘬․a INT₋MIN and '0b1<<31alt63'. */
#define MOMENTED /*  attribute-at-end for method declarations a․𝘬․a 'LEAF' and 'do not follow'. */
#define moment /*  initial attribute for function definitions and declarations a․𝘬․a 'leaf'. */
#define intrinsic₋leaf /*  a․𝘬․a 'half₋leaf'; multiple attempts-w(as)-silicon-based. */
#define leaf₋function /*  ...except intrinsic functions! */
#define /* PROVOCATIVE */ ASSEMBLERONLY __attribute__((naked))
#if defined __x86_64__
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
#define Sourpatch(sym,msg) /*  a․𝘬․a 'link-forget' and 'retrospective-invisible' . */
#define IsOdd(x) ((x) & 0b1) /*  simultaneously int32_t ∧ int64_t. 
 H: x & 0b010 ⟷̸ ◻️⃞. See --<math>--<erf.cpp>{⁽₋1⁾ᵏ|alt}. */
/*  also: 'odd' is closed under multiplication. */
#define NOT_EVERYTIME const static
#define CARDINALS(...) enum Cardinal { __🄦hole=0, __VA_ARGS__ };            \
  static jmp_buf2 __snapshot;                                                \
  typedef void (^CSession)(enum Cardinal sin);                               \
  CSession confess = ^(enum Cardinal sin) { longjmp2(__snapshot, (__builtin_int_t)sin); };
#define NEARBYCROSS                                                          \
  int __ctrl = setjmp2(__snapshot);                                          \
  switch (__ctrl)
#define 🧵(...) /* ✠ */ CARDINALS(__VA_ARGS__) NEARBYCROSS
#define 🥇 NOT_EVERYTIME
#define 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 __attribute__ ((__blocks__(byref))) /*  a․𝘬․a '__block', 
 𝚊𝚏𝚏𝚎𝚌𝚝𝚊𝚋𝚕𝚎 and 𝒎𝒆𝒄𝒉𝒂𝒏𝒊𝒔𝒎; 𝘤𝘧․ 'jurid' and 'förekomst'. Also 'machinal'. */
__builtin_int_t least₋possible₋residue(__builtin_int_t dividend, __builtin_int_t divisor);
/*  see --<Wiki>--<Essays>--<On clocks and time> and 'circular reasoning'. */
#define auto₋rollback(variable) decltype(variable)
typedef __builtin_uint_t Cross;
BITMASK(Cross) { CrossLeftToRight = 0b0001, CrossRightToLeft = 0b0010, 
 CrossTopToBottom = 0b0100, CrossBottomToTop = 0b1000
};

#pragma recto utf-8 keyput and file, seven-bit and sequence of symbols

EXT₋C int Utf8ToUnicode(__builtin_int_t u8bytes, char8₋t * encoded, char32̄_t * 
 prealloc₋out, __builtin_int_t * tetras) ⓣ;
EXT₋C int UnicodeToUtf8(__builtin_int_t u32count, char32̄_t * decoded, char8₋t * 
 prealloc₋out, __builtin_int_t * u8bytes) ⓣ;
EXT₋C char8₋t * retranscript(char8₋t * u8s, __builtin_int_t maxu8bytes𝘖rZero);

EXT₋C int UnicodeToUtf8(char32̄_t Ξ, void (^sometime₋valid)(char8₋t * ξ, short 
 bytes)) ⓣ;
EXT₋C short Utf8Followers(char8₋t lead𝘖r8Bit);
EXT₋C char32̄_t Utf8ToUnicode(char8₋t * ξ, __builtin_int_t bytes) ⓣ;

enum Encoding { encoding₋utf8, encoding₋unicode };

EXT₋C int ReflectUtf8AlternativelyUnicode(enum Encoding type, __builtin_int_t bytes, 
 uint8_t * material, char32̄_t * decoded, __builtin_int_t * tetras);

EXT₋C __builtin_int_t ExactTetras(char8₋t * u8s, __builtin_int_t maxutf8bytes);
/*  the 'ExactTetras' may return less than zero and 'ExactTetras' may 
 traverse undefined code points to return '-1'. */

EXT₋C __builtin_int_t ExactUtf8bytes(char32̄_t * ucs, __builtin_int_t maxtetras);
/*  a․𝘬․a 'Utf8bytesExceptZero'. */

EXT₋C __builtin_int_t Utf8BytesUntilZero(char8₋t * u8s, __builtin_int_t maxbytes𝘖rZero);
/*  non-equivalent to Unix-header and strlen and returns 'maxbytes' in case end-marker is 
 not earlier found. */

EXT₋C __builtin_int_t TetrasUntilZero(char32̄_t * ucs, __builtin_int_t maxtetras𝘖rZero);
/*  iterates until zero alternatively 'passed EOT'. */

#pragma recto Si, sand and sunblock

typedef union octa {
   double base﹟𝟸; /* captures 2⁻¹⁰²² and 2¹⁰²³ or in engineering: 2․23×10⁻³⁰⁸ to 1․79×10³⁰⁸. */
   struct { uint32_t lst; int32_t mst; } signed_little_endian;
   struct { int32_t mst; uint32_t lst; } signed_big_endian;
   struct { uint32_t lst; uint32_t mst; } unsigned_little_endian;
   struct { uint32_t mst; uint32_t lst; } unsigned_big_endian;
   struct {
      unsigned mantissal : 32;
      unsigned mantissah : 20;
      unsigned exponent  : 11;
      unsigned sign      :  1;
   } binary64; /*  a․𝘬․a 'ieee754b﹟𝟸'. */
   /* struct { … } ieee754b﹟𝟷𝟶; a․𝘬․a 'decimal64'. */
   /* struct { 
      unsigned absolute  : 31;
      unsigned sign      :  1;
   } sgned; */
   int64_t sgned;
   uint64_t bits;
} octa;

struct Octa { uint32_t l, h; };

inline EXT₋C double ConvertAndCast(int64_t measure, int reciproc)
{
#if !defined OPTIMIZED₋NONGENERAL
  octa y;
   int neg = measure<0;
   int64_t z = measure < 0 ? -measure : measure;
   int64_t buffer = __builtin_clzll(z);
   z = measure >> (64 - buffer); /* a․𝘬․a fiftysix₋bits. */
   y.binary64.mantissal = z;
   y.binary64.mantissah = z >> 32;
   y.binary64.exponent = 1022 + buffer; /* a․𝘬․a biased₋2ⁿexp. */
   y.binary64.sign = neg ? 1u : 0u;
   if (neg) { y.base﹟𝟸 = -y.base﹟𝟸; }
   return reciproc ? 1/y.base﹟𝟸 : y.base﹟𝟸;
#elif defined __mips__ && defined OPTIMIZED₋NONGENERAL
   Mips                                                                      
     "                                                        \n"            
     "  mtc1       $a1, $f0                                   \n"            
     "  mthc1      $a2, $f0                                   \n"            
     "  cvt.d.l    $f0, $f0                                   \n"            
     "  mfc1       $v0, $f0                                   \n"            
     "                                                        \n"            
   );                                                                        
#elif defined __x86_64__ && defined OPTIMIZED₋NONGENERAL
   asm {                                                                     
     fild rdi                   /*  see Intel.FBLD and Intel.FBSTP. */     
     fstp xmm0                                                               
   } /*  enabled by '-fms-extension'. */                                   
#endif
} OPT_Si_FOCAL /*  a․𝘬․a 'Cast' and 'Convert'. */

inline EXT₋C int64_t Nearest(double measure, int * reciproc)
{
  if (measure == +0.0 || measure == -0.0) { return 0; }
  int denominate = -1.0 < measure && measure < 1.0;
  if (denominate) { measure = 1/measure; }
  *reciproc = denominate;
  double y = (measure < +0.0) ? measure + 0.5 : measure + 1.5;
  return (int64_t)y; /*  adds 0.5 before scissor for 'nearest' as 'rounds towards 
   zero'. When negative and 1.5 and 'round towards -inf' a․𝘬․a ROUND_DOWNWARD. */
}

#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
union Treeint { struct { int64_t key; uint64_t val; } keyvalue; __uint128_t bits; };
#elif defined __mips__ || defined __armv6__ || defined espressif
union Treeint { struct { int32_t key; uint32_t val; } keyvalue; uint64_t bits; };
#endif /*  a․𝘬․a 'Autumn' and 'Treeℤ'. */

EXT₋C void * Insert(void * opaque, union Treeint valkey, ALLOC alloc);
EXT₋C void Forall(void ᶿ﹡ opaque, void (^dfs)(union Treeint valkey, int * stop));
EXT₋C union Treeint * Lookup(void ᶿ﹡ opaque, union Treeint leafkey);

#pragma - big endian ⟷ 'most signif. first', little endian ⟷ 'least sigif. first'

typedef union sexdeca {
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
  __uint128_t bits;
#endif
  struct { union octa lso, mso; } little₋endian;
  struct { union octa mso, lso; } big₋endian;
  struct { struct Octa l, h; } parts;
#if defined __x86_64__
  /* __m128 intel; /​*  'sixteen - possibly unaligned - divided into 𝙛𝙡𝙤𝙖𝙩 slots'. */
#endif
} sexdeca; /*  a․𝘬․a denary. */

typedef union ditriaconta {
#if defined __x86_64__
  /* __m256 intel; /​*  'thirty-two - possibly unaligned - bytes divided into 𝗳𝗹𝗼𝗮𝘁 slots'. */
#endif
  uint32_t eight₋tetra[8];
  uint8_t thirtytwo₋bytes[32];
  struct { union sexdeca lss, mss; } little₋endian;
  struct { union sexdeca mss, lss; } big₋endian;
} ditriaconta; /*  a․𝘬․a 'senidenary' alternatively 'sedenary'. */

/**  Computes a cryptographic hash value similar to NIST FIPS PUB 180-4: 
  "Secure Hash Standard (SHS)", August 2015. */

EXT₋C int Hash(uint8_t * material, __builtin_int_t bytes, void (^ping𝘖r𝖭𝖴𝖫𝖫)(int 
 * stop), void (^complete)(ditriaconta digest)); /*  a․𝘬․a 'fineprint'. */

#if defined  __mips__ || defined __armv6__ || defined espressif
#define BUILTIN₋INT₋MAX 2147483647
#elif defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
#define BUILTIN₋INT₋MAX 0x7FFFFFFFFFFFFFFF
#endif /* ~0b0>>1 */
/*  the constant INT₋MAX is an odd number. */

typedef union {
   float base﹟𝟸; /* for 2⁻¹²⁶ to 2¹²⁷ or 1․18×10⁻³⁸ to 3․40×10³⁸. */
   struct { uint16_t lsh; int16_t msh; } signed_little_endian;
   struct { int16_t msh; uint16_t lsh; } signed_big_endian;
   struct { uint16_t lsh; uint16_t msh; } unsigned_little_endian;
   struct { uint16_t msh; uint16_t lsh; } unsigned_big_endian;
   struct {
     unsigned mantissa : 23;
     unsigned exponent :  8;
     unsigned sign     :  1;
   } binary32; /*  a․𝘬․a 'ieee754base₋2'. */
   struct { /* for ±1×10⁻⁹⁵ to ±9.999999×10⁹⁶. */
     unsigned combination : 5; /* msb-exp */
     unsigned exponent    : 6; /* ×10ⁱ⁻¹⁰¹ */
     unsigned mantissa    : 20;
     unsigned sign        : 1;
   } decimal32; /*  a․𝘬․a 'ieee754_2008₋base₋10'. */
   uint32_t bits;
} tetra;

typedef uint32_t Tetra;

enum Endianness { endian₋native, endian₋network };

#pragma recto  📖😐 ”𝑈𝑛𝑖𝑐𝑜𝑑𝑒 length known once read”

EXT₋C int Utf8Sync(char8₋t **p); /*  backs at most 3 bytes to regain sync. */

inline EXT₋C char32̄_t Superscript(short 𝟶to𝟿) { return U'⁰'+𝟶to𝟿; } /* ⁰¹⋯⁹ */

inline EXT₋C char32̄_t Subscript(short 𝟶to𝟿) { return U'₀'+𝟶to𝟿; } /* ₀₁…₉;  For the computational chemistry inclined. */

EXT₋C int TransformAndResolve(struct Unicodes pathᵚᵍ, void (^final)(char 
 * regular𝘖rLinkpath));

#define END_OF_TRANSMISSION U'\x0004'

EXT₋C inline struct Unicodes Run(char32̄_t * ucsAndNULL)
{ __builtin_int_t count = TetrasUntilZero(ucsAndNULL,BUILTIN₋INT₋MAX);
   struct Unicodes text = { count, ucsAndNULL };
   return text;
}

EXT₋C inline int Lease(char8₋t * u8s, void (^sometime)(struct Unicodes uc))
{ __builtin_int_t u8bytes = Utf8BytesUntilZero(u8s,BUILTIN₋INT₋MAX);
   char32̄_t ucs[4*u8bytes]; __builtin_int_t tetras;
   if (Utf8ToUnicode(u8bytes,u8s,ucs,&tetras)) { return -1; }
   struct Unicodes text = { tetras, ucs };
   sometime(text);
   return 0;
}

EXT₋C int Play(void (^composition)(struct Unicodes serial), 
 char32̄_t * text, ...) ⓣ;

EXT₋C int Play(char32̄_t * text, __builtin_va_list params, void 
 (^composition)(struct Unicodes serial)) ⓣ;

#pragma recto 8, 16, ...,  32, 64, lo64, hi64, 128, utf8

/* for 𝑝𝑖𝑔𝑒𝑜𝑛 𝑟𝑒𝑐𝑜𝑛𝑛𝑎𝑖𝑠𝑠𝑎𝑛𝑐𝑒, 𝑠𝑐𝑜𝑢𝑡𝑖𝑛𝑔 and other missions */
/* still images, timeseries and language analysis */
/* c𝘧. Scandinavian 'by₋tes' a․𝘬․a '✠✠' */
/* touting strong radio (🦠) */
/* BUFFERTOCHICKEFORBUD */

struct collection {
  struct middle { uint8_t * palms[8192]; } *myrtles[4096];
  __builtin_int_t item₋count, palm₋count;
  unsigned bytes₋per₋item, bytes₋per₋palm;
}; /* olive, myrtle and palm. */

EXT₋C int collection₋init(unsigned bytes₋per₋item, unsigned 
 bytes₋per₋tile, struct collection * 🅰);
EXT₋C int copy₋append₋items(__builtin_int_t count₋not₋bytes, void * 
 bytes₋objects, struct collection * 🅰, ALLOC alloc);
EXT₋C uint8_t * collection₋relative(__builtin_int_t idx, struct collection * 🅰);
/*  a․𝘬․a 'collection₋at'. */
EXT₋C __builtin_int_t collection₋count(struct collection * 🅰);
EXT₋C int deinit₋collection(struct collection * 🅰, FALLOW fallow);
typedef struct collection Casette;

EXT₋C int init₋convoj(struct collection * 🅵₁, struct collection * 🅵₂);
EXT₋C int copy₋include₋convoj(ALLOC alloc, struct collection * 🅵₁, struct 
 collection * 🅵₂, __builtin_int_t count, __builtin_int_t bytes[], ...);
EXT₋C __builtin_int_t convoj₋count(struct collection * 🅵₁, struct collection * 🅵₂);
EXT₋C uint8_t * convoj₋relative(__builtin_int_t idx, struct collection * 🅵₁, 
 struct collection * 🅵₂); /*  a․𝘬․a 'sequence'. */

EXT₋C int Snapshot(const struct collection original, struct collection * pristine);
EXT₋C int ToggleNetworkAndNative(struct collection region, __builtin_int_t 
 bytes₋skip, __builtin_int_t bytes, void (^ping)(int * stop), void (^completion)
 (__builtin_int_t bytes)); 

enum Sentinel { sentinel₋cyclic, sentinel₋last, /*, linear, bilinear, */ 
 sentinel₋crash, sentinel₋bound };
inline EXT₋C uint64_t /* a․𝘬․a 'ieee754dbl₋pattern' */ intel(uint32_t ˡᵒword, 
 uint32_t wordʰⁱ) { return ((uint64_t)wordʰⁱ)<<32 | ˡᵒword; }

/* When 'change', 'delete' and 'type', see --<2ᵈ-𝔣ow.hpp> and --<arabic-edit.c>. */

inline uint32_t EXT₋C ᵗᵍᵍˡendian(uint32_t x) ⓣ { return __builtin_bswap32(x); }
inline uint64_t EXT₋C ᵗᵍᵍˡendian(uint64_t x) ⓣ { return __builtin_bswap64(x); }
/*  a․𝘬․a 'toggleNetworkAndNative'. */

EXT₋C void * ExactSeek₂(const void *key, const void *base, size_t num, 
 size_t size, int (^cmp)(const void *key, const void *elt));

EXT₋C int IsPrefixOrEqual(const char *𝟽alt𝟾₋bitstring, const char *𝟽alt𝟾₋bitprefix);
/*  returns `int` indicating difference at branch, -1 if equal and `0` when 
 string contains neither prefix nor is equal. */

typedef struct Textsearch { __builtin_int_t text₋offset₋bytes; } Borderedsearch;
EXT₋C int AssociativelyEqual(enum Encoding encoded, __builtin_int_t bytes, 
 uint8_t * material, struct sevenbit₋text recollection, Borderedsearch * ctxt);
/*  find referenced bandit with context when right-to-left and vague recoll-
 ection. A number indicating the number of tokens required to recollect is 
 computed. Note that pre-indexed search does not operate properly given 'vague 
 recollection' due to the swedish sentence 'falla mellan stolar'. */

typedef struct Unicodeblock {
  __builtin_int_t linesOffsetFirst, linesOffsetLast, column₁, column₂;
  __builtin_int_t tetrasRelativeFirst, tetrasRelativeLast;
} UnicodeInterval;

typedef struct PresentativeErrorUnicode { __builtin_int_t line1ˢᵗ, bytesOffset1ˢᵗ, lineLast, 
 bytesOffsetInclLast; } Utf8Interval; /*  e․𝘨 wrongly coded utf-8. */

union Reference { struct PresentativeErrorUnicode byteserie; struct Unicodeblock volatile₋primary; };

#pragma -  😐🎤💀 ”𝑇ℎ𝑒 ⚰️”

#define va_epilogue __builtin_va_end(__various);
#define va_prologue(symbol)                                                 \
 __builtin_va_list __various;                                               \
 __builtin_va_start(__various, symbol);
#define QUOTE(str) #str
#if defined __x86_64__ || defined __mips__
EXT₋C void ASSEMBLERONLY Sheriff();
#elif defined __armv8a__
#define Sheriff __builtin_debugtrap
#endif
/* #define ⭐️ Sheriff();  after delivery, a non-inquisitorial system is assumed. */
enum Impediment { MustBeOrdered, JustSwap };
EXT₋C int OptimisticSwap(__builtin_int_t * p₁, __builtin_int_t * p₂, enum 
 Impediment it);
/*  non-atomic, yet consistent and gracefully failing indicated through a 
 non-zero return value. */
/* struct Peekey { __builtin_int_t 🥈 ⬚=2, 🗝=1; __builtin_int_t board₁, palm₂; }; */
#define 🔒(situ,error) if (OptimisticSwap(&situ.board₁, &situ.palm₂, MustBeOrdered)) { confess(error); }
#define 🔓(situ,error) if (OptimisticSwap(&situ.board₁, &situ.palm₂, JustSwap)) { confess(error); }
struct Bitfield { const char32̄_t * regular; uint32_t mask; const char32̄_t * text; };
struct AnnotatedRegister { const char32̄_t * header; int regcnt; struct 
 Bitfield * regs; uint32_t init; const char32̄_t * footnote; };
typedef struct Bitfield Bitfield;

#pragma - blue, white and yellow collection and time series

struct Act { __builtin_int_t memory; };
EXT₋C __builtin_int_t monoton₋ordinal(int * wrapped, struct Act * ❶);
EXT₋C void init₋monoton(struct Act * ❶, __builtin_int_t oldest);
/*  retrieve a unique value in a 'strict monotonic increasing serie. Wraps (𝄇) at 
 BUILTIN₋INT₋MAX. */

#pragma recto two non-accurates and concurrent with 52-bit significands

#if defined Ieee754₋ARITHMETICS₋KEY

union β₋simd
{
  double dbls[2]; double doubles[2];
#if defined 𝟷𝟸𝟾₋bit₋integer₋available
  __uint128_t bits;
#endif
};

#if defined NON₋SIMD
typedef union β₋simd simd_tᵦ;
/* typedef double simd_tᵦ[2]; */
#elif defined __armv8a__
typedef __attribute__ ((neon_vector_type(2))) double float64x2_t;
typedef float64x2_t simd_tᵦ;
#elif defined __x86_64__
typedef double __attribute__ ((__vector_size__(16), __aligned__(16))) __m128d;
typedef __m128d simd_tᵦ;
#elif defined __mips__ && !defined NON₋SIMD
typedef double v2f64 __attribute__ ((vector_size(16),aligned(16)));
#endif

union 𝟸₋double
{
  union β₋simd array;
  simd_tᵦ multiple;
#if defined __x86_64__
  __m128d intel128;
#elif defined __armv8a__
  float64x2_t arm128;
#elif defined __mips__ && !defined NON₋SIMD
  v2f64 mips128;
#endif
};

union historypod
{
  __uint128_t machineunsigned;
  simd_tᵦ tworeal;
  union Q6364 fixed;
};

#endif

#pragma recto  😐😇 and 1/1/1900 0am

/**  The NTP defines epoch starting at the year 1900 at midnight before 
 sunrise January the 1ˢᵗ and with a 32-bit unsigned  integer track 0 to 
 2³² - 1 = 4.294,967,295 seconds (approximately 136 earth years) until 
 a wrap occurs.
 
 A correct abbreviation for the unit of time and also the measurements 
 of duration is 's'. It is not 'S' which stands for Siemens and 
 admittance.
 
 One minute of geographic latitude per hour = 1 kn = 1852.0 m/h. (Knot). */

typedef uint64_t chronology₋instant; /* seconds passed since beginning of previous century. */
typedef uint32_t chronology₋UQ32; /* e․𝘨 0.101₂ = 1×1/2 + 0×1/4 + 1×1/8 = 5/8. */
struct chronology₋day { int32_t y,M,d; }; /* 1-12 and 1-31. */
struct chronology₋time { int32_t h,m,s; chronology₋UQ32 partial; }; /* 0-23, 0-59 and fractionals since midnight. */
EXT₋C struct chronology₋day calendric(chronology₋instant v);
EXT₋C int reveille(chronology₋instant v, int32_t * h, int32_t * m, int32_t * s, chronology₋UQ32 * frac);
EXT₋C int form₋instant(int32_t parts[], chronology₋UQ32 frac, chronology₋instant * v);
/* year, month (1-12), day (1-31), hour (0-23), minutes (0-59) and seconds (0-59). 
 And the number of 1/2³² second ticks (=232.82 ps) to add.*/
EXT₋C int chronology₋dayofweek(chronology₋instant v, int * wd);
/** return weekday assuming a week starts on a Wednesday. (Encoded as 0.) 
  may return ≠0 ⟷ 'divergent methods recognized'. */
EXT₋C chronology₋instant add₋seconds(chronology₋instant relative, uint32_t 
 seconds, chronology₋UQ32 augment₋frac);
EXT₋C chronology₋instant subtract₋seconds(chronology₋instant relative, 
 uint32_t seconds, chronology₋UQ32 deduction₋frac);
/**  only for unperturbed chronologies. For non-reversable 
 chronologies, subtract throws an error. */

/*  One martian sol: 24h, 39 min and 35 sec. (Sundial time.)
  668 sols ≈ 1.88 Earth years. (approx. 687 Earth days.)

  Mars got five days a week and five seasons per year:
   enum Veneuveteuean { Again, trout, loo, master, shoRt };
   …and also a longer relative of unknown periodicity.
  */

#if defined AWARENESS₋OF₋INTERPLANETARY₋MATTERS
typedef Chronology Chronology🚀; /*  i․𝘦 'celestial fractional' with 'identical' epoc. */
typedef Chronology Chronology🦠; /*  with an 2⁻⁶⁵ a․𝘬․a 'UQ65'; light
  travels approximately 8.126 pm ('pico meter') per increment. */
#endif

/**  The unperturbed — yet based on ¹³³Caesium — chronology. */

#define ComputationalChronology 2 /*  𝖤․𝘨 for chronometers; a․𝘬․a 
 `GMT` (therefore 60×60×24 seconds per day), without leap seconds/years 
 and no summertime correction. */

/**  The chronology of the users' choice: a․𝘬․a 'UTC' (therefore an exact 
 multiple of SI seconds, with leap seconds as well as summertime). */

#define SystemCalendricChronology 1

enum Consequence { thus, totient /* a․𝘬․a Ɣ */ };

/**  Translate an instant between a particular time zone and Unix UTC. */

EXT₋C chronology₋instant Timezone(chronology₋instant v, 
 short quarters₋of₋hours₋offset);

EXT₋C int Worldclock₋fractographic(chronology₋instant utc);
/**  for priestmobile useful when relatives live tectronically dispersive lifes. */

/**  Relative-time interval when running from instant t₁ to instant t₂ given 
 preferable according to the 'ComputationalChronology'. */

typedef int32_t chronology₋Q31;
typedef int32_t short₋chronology₋relative; /* a․𝘬․a Q1615 captures ±65535.9999694822. */
struct chronology₋relative { int32_t seconds; chronology₋Q31 frac; };
EXT₋C short₋chronology₋relative duration(chronology₋instant t₁, chronology₋instant t₂);
/*  a․𝘬․a 'Interval', 'relative' and 'seconds₋and₋frac' and is calendric alternatively 
 monotonically increasing non-rooting temporal relative. */

EXT₋C void present₋instant(chronology₋instant v, int incl₋frac, void (^out)(
 char digitHyphenColonPeriod𝘖rSpace));

EXT₋C int Timestamp(enum Encoding encoded, int bytes, uint8_t * material, 
 chronology₋instant * v); /* e․𝘨 '1959-07-13 12:00.00.000000000232' and '2012-01-24 12:00:00'. */

typedef struct __coro_t coro_t;
typedef int (*coro_function_t)(coro_t *);
typedef struct __coro_t * ϵ₋int₁;
typedef int (*Coroutine)(ϵ₋int₁ coro);

EXT₋C coro_t * coro_await(Coroutine coroutine);
EXT₋C int coro_resume(coro_t * coro);
EXT₋C void coro_feedback(coro_t * coro, int value);
EXT₋C void coro_free(coro_t * coro);

#if defined 𝟷𝟸𝟾₋bit₋integer₋available
typedef __builtin_int_t version₋ts;
struct timeserie { struct collection pendings; void * currents, *uncommits;
 Casette points, versions, events, temporals; version₋ts *revision, earliest; 
 unsigned short checkpoint₋modulo; };
struct timeserie₋entry { struct Unicodes key; union historypod entry; 
 struct sevenbit₋text reference; };
typedef union historypod (*timeserie₋summation)(union historypod x₁, union historypod x₂);
enum timeserie₋operation { ts₋create, ts₋update, ts₋delta, ts₋remove };
EXT₋C int timeserie₋init(version₋ts * revision, version₋ts earliest, 
 unsigned int snapshot₋cycle, struct timeserie * 🅹);
EXT₋C void timeserie₋uninit(struct timeserie * 🅹);
typedef void (^line₋completed)(struct timeserie₋entry row, version₋ts revision);
EXT₋C int timeserie₋commit(version₋ts * revision, line₋completed persisted, 
 struct timeserie * 🅙, timeserie₋summation addition);
EXT₋C int timeserie₋rollback(struct timeserie * 🅙);
EXT₋C int timeserie₋remove(struct Unicodes key, struct timeserie * 🅙);
EXT₋C int timeserie₋create(struct timeserie₋entry * initial, struct timeserie * 🅙);
EXT₋C int timeserie₋update(struct timeserie₋entry * absolut, struct timeserie * 🅙);
EXT₋C int timeserie₋delta(struct timeserie₋entry * toggle, union historypod * 
 alterificate, struct timeserie * 🅙, timeserie₋summation addition);
EXT₋C void state₋before(int count, struct Unicodes keys[], version₋ts ordin, void 
 (^retrieve)(int count, union historypod artstate[], struct Unicodes key[]), 
 struct timeserie * 🅙);
EXT₋C void state₋after(int count, struct Unicodes keys[], version₋ts ordin, void 
 (^retrieve)(int count, union historypod artstate[], struct Unicodes key[]), 
 struct timeserie * 🅙);
typedef void (^Timeserie₋row)(int count, struct timeserie₋entry row[], int permanent[]);
typedef void (^Timeserie₋pod)(int count, union historypod artstate[], struct Unicodes key[]);
EXT₋C int Present₋timeserie₋transacts(__builtin_int_t retrospect₋offset, 
 __builtin_int_t retrospect₋count, struct timeserie * 🅙, Timeserie₋row out);
EXT₋C int Present₋timeserie₋overview(struct timeserie * 🅙, Timeserie₋pod out);
#endif

struct guid { struct endian { uint64_t aware; uint64_t similar; } endian; };
struct guid Guid();
Argᴾ ﹟leap(struct guid g);

/**  correlative-relative, 𝘦․𝘨 xʳ∈[-1/2₋𝜀, +1/2₊𝜀] and xʳ∈[-π₊𝜀, +π₋𝜀]. */

typedef float floatʳ; typedef double doubleʳ;

/**  subtractive-relative, 𝘦․𝘨 x⁺ʳ∈[0₋𝜀, 1₊𝜀) and x⁺ʳ∈[0₊𝜀, π₋𝜀). */

typedef float float⁺ʳ; typedef double double⁺ʳ;

/**  relative-fixative types. */

typedef char8₋t uchar; typedef uint32_t uint32; typedef uint8_t byte;

#define min(x₁, x₂) ((x₂) < (x₁) ? (x₂) : (x₁))
#define max(x₁, x₂) ((x₁) < (x₂) ? (x₂) : (x₁))

EXT₋C void Gitidentity(const char ** text);

