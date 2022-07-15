/*  after-eight.hpp | modelling in c++20. */

#define bye co_return
#define co₋await co_await
#define feedback co_yield
#define adjö co_return /*  s․a 'självet anser' and jmfr. 'jämför' and a.s. 'almost surely'. */

#if defined __cplusplus && defined ADDITIONAL_LINKERSYMBOLS

template <typename K, typename V> struct Map { std::map<K,V> inner;
  int exists(K key) { return inner.contains(key); }
  int include(K key, V val, int * didrefresh) {
    std::pair<typename std::map<K,V>::iterator, bool> y = 
     inner.insert_or_assign(key,val); *didrefresh = !y.second; }
  void assoc(K key, void (^seek)(V * agent)) { auto it = inner.find(key); 
    if (it != std::map<K,V>::const_iterator.end()) { seek((V *)&*it); } }
};

template <typename E> struct Vector { std::vector<E> inner;
  void push(E elem) { inner.push_back(elem); }
  int pop() { if (inner.size() == 0) { return -1; }
    inner.pop_back(); return 0; }
  int relative(__builtin_int_t n, E ** reference) {
    if (n >= inner.size()) { return -1; }
    *reference = &inner.at(n); return 0;
  }
};

struct Bitset { std::vector<bool> inner; 
  Bitset(__builtin_int_t bits₋initial) { adjust(bits₋initial); }
  void adjust(__builtin_int_t new₋bits₋size) {
    inner.reserve(new₋bits₋size); resize(new₋bits₋size); }
  void set (__builtin_int_t slot, int val) {
    if (slot >= inner.size()) { adjust(slot); }
    inner[slot] = (bool)val; }
  int get (__builtin_int_t slot, int * val) {
    if (slot >= inner.size()) { adjust(slot); }
    *val = (int)inner[slot];
    return 0;
  }
};

/* in Unix named 'time.h' with 'time_t time()-time()' alt. 'difftime()' */

typedef time_t Unix₋instant; /*  epoch is 00:00:00 UTC Jan 1, 1970. */

inline Tuple<int32_t, int32_t, int32_t> chronology₋Date(Unix₋instant I)
{
   struct tm * y = gmtime(&I);
   return Tuple<int32_t(y->tm_hour /* 0 - 23 */), int32_t(y->tm_min /* 0 - 59 */), 
    int32_t(y->tm_sec /* 0 - 60 */)>();
} /* seconds-to-calendric in prematurely 'set' time-zone: 'struct tm * localtime(const time_t *)'. */

inline Opt<Unix₋instant> chronology₋Timestamp(int32_t parts[6] /*, Chronology::UQ32 fract */)
{ /*  year, month (1-12), day (1-31), hour (0-23), minutes (0-59) and seconds (0-59) */
   int tm_sec=(int)parts[5], tm_min=(int)parts[4], tm_hour=(int)parts[3], 
    tm_mday=(int)parts[2], tm_mon=(int)parts[1], tm_year=(int)parts[0];
   struct tm t₁ { tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, 0, 0, 0, 0, 0 };
   time_t t₂ = timegm(&t₁);
   return Opt<Unix₋instant>(t₂);
} /* calendric-to-seconds in prematurely 'set' time-zone: 'time_t timelocal(struct tm * const)'. */

inline char * chronology₋InstantToText(Unix₋instant I) { return ctime(I); } /*  time2posix/posix2time. */

#elif defined __cplusplus

template <typename K, typename V> struct Map { void * inner; 
  /*  a․𝘬․a std::map<K,V> inner. */
  int exists(K key) {
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    Treeint leafkey { .keyvalue = { int64_t(key), 0 } };
#elif defined __mips__ || defined __armv6__ || defined espressif
    Treeint leafkey { .keyvalue = { int32_t(key), 0 } };
#endif
    Treeint * found = Lookup(inner,leafkey);
    return found == NULL; }
  int include(K key, V val, bool * didrefresh) {
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    Treeint leafkey { .keyvalue = { int64_t(key), uint64_t(val) } };
#elif defined __mips__ || defined __armv6__ || defined espressif
    Treeint leafkey { .keyvalue = { int32_t(key), uint32_t(val) } };
#endif
    auto alloc = ^(int bytes) { return Alloc(bytes); };
    void * y = Insert(inner,leafkey,alloc);
    return y != NULL;
  }
  void assoc(K key, void (^seek)(V * agent)) {
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    Treeint leafkey { .keyvalue = { int64_t(key), 0 } };
#elif defined __mips__ || defined __armv6__ || defined espressif
    Treeint leafkey { .keyvalue = { int32_t(key), 0 } };
#endif
    Treeint * found = Lookup(inner,leafkey);
    seek(found);
  }
  
}; /*  sometime referential map such as std::map<const char *, Unicodes>. */

template <typename E> struct Vector { ˢConvoj<E> inner;
  
  void push(E elem) { inner.copy₋include(1, { elem }); }
  int pop() { if (inner.count == 0) { return -1; }
    inner.pop(); return 0; }
  int relative(__builtin_int_t idx, E ** reference) {
    if (idx >= inner.count) { return -1; }
    *reference = &inner[idx]; return 0;
  }
  
}; /*  similar to std::vector and not c++11's std::array in <array>. */

rt₋namespace After₋8 { extern __builtin_int_t bitset₋still₋short, bitset₋noncoalescable; }

struct Bitset { unsigned expeditionary=1; 
  
  __builtin_int_t 🥈 wordbits=Wordbytes*8; structure inner;
  
  Bitset(__builtin_int_t bits₋initial) { adjust₁(bits₋initial); }
  
  void adjust₁(__builtin_int_t encompassing₋bit) {
    auto additional₋﹟₋count = ^(__builtin_int_t bit₋﹟) {
      return 1 + (encompassing₋bit / wordbits); };
    int ﹟ = additional₋﹟₋count(encompassing₋bit); void * 𝟺kbframes[﹟];
    if (CoalescingAcquire(expeditionary,𝟺kbframes,﹟)) { Pult💡(After₋8::bitset₋noncoalescable); }
    if (inner.lengthen(﹟,𝟺kbframes)) { Pult💡(After₋8::bitset₋still₋short); }
  }
  
  void adjust₂(__builtin_int_t deduct₋bits) { inner.unused₋bytes = deduct₋bits; }
  
  __builtin_int_t maxbitcount() { return 8*inner.tile₋count*inner.bytes₋per₋tile; }
  
  int get(__builtin_int_t slot, int * value) {
    __builtin_int_t ﹟ = maxbitcount();
    if (slot >= ﹟) { inner.unused₋bytes=0; adjust₁(slot); }
    else if (slot >= ﹟ - inner.unused₋bytes) { adjust₂(﹟ - slot); }
    __builtin_int_t word = slot / wordbits, bit = slot % wordbits;
    __builtin_int_t byte₋number = word*Wordbytes;
    uint8_t * loc₋𝟾 = inner.relative(byte₋number);
    __builtin_uint_t orig = *(__builtin_uint_t *)loc₋𝟾;
    *value = (orig & (0b1<<bit)) ? 1 : 0;
    return 0;
  }
  
  void set(__builtin_int_t slot, int value) {
    __builtin_int_t ﹟ = maxbitcount();
    if (slot >= ﹟) { inner.unused₋bytes=0; adjust₁(slot); }
    else if (slot >= ﹟ - inner.unused₋bytes) { adjust₂(﹟ - slot); }
    __builtin_int_t word₋number = slot / wordbits, bit = slot % wordbits;
    __builtin_int_t byte₋number = word₋number*Wordbytes;
    uint8_t * loc₋𝟾 = inner.relative(byte₋number);
    __builtin_uint_t * loc₋32 = (__builtin_uint_t *)loc₋𝟾;
    __builtin_uint_t orig = *loc₋32;
    if (value) { *loc₋32 = (orig | (0b1<<bit)); }
    else { *loc₋32 = (orig & ~(0b1<<bit)); }
  }
  
}; /*  bitsets grows in steps of pages and in wordbits steps. */

#endif /*  all 'man' pages unwritten, instead http://cppreference.com and 
 cached versions of the latter. */

#if defined __cplusplus
struct SharedOptional { int populated=false; };
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

#define WHEN_COMPILING constexpr static
#define 🥈ᵢ WHEN_COMPILING __attribute__ ((internal_linkage))
#define 🥈 WHEN_COMPILING /*  must be assigned to a 'const' and no inline assembler. */
/* __builtin_int_t constexpr Syspagesize() { return 4096; } */
/*  one definition of 𝘮𝘢𝘯𝘺 ∧ ¬𝘴𝘤𝘢𝘭𝘢𝘳 (especially when Nand vs. Nor.) */

MACRO __builtin_uint_t& 🔧(__builtin_uint_t var) { return (__builtin_uint_t&) 
 *(__builtin_uint_t *)var; }
MACRO __builtin_uint_t 🎭(__builtin_uint_t * symbol, __builtin_uint_t mask, 
 void (^refreshOrΨΛΩ)(__builtin_uint_t &shifted) = ^(__builtin_uint_t&) { }) {
  __builtin_uint_t word = *symbol, shift=Trailing₋non₋ones(mask), original = 
  mask&word, shifted=original>>shift; if (refreshOrΨΛΩ) { refreshOrΨΛΩ(shifted); }
  __builtin_uint_t updated=mask&(shifted<<shift); *symbol=(word & ~mask) | updated;
  return original>>shift; }
template <typename T> T max(T x₁, T x₂) { return x₁ < x₂ ? x₂ : x₁; }
template <typename T> T min(T x₁, T x₂) { return x₂ < x₁ ? x₂ : x₁; }
namespace Relative {
template <typename T> T relative(T x₁, T x₂) { return x₂/x₁; }
template <typename T> T difference(T x₁, T x₂) { return x₁ - x₂; }
template <typename T> T ˡchange(T x₁, T x₂) { return (x₁ - x₂) / x₂; } /* ∈[0,1]. */
template <typename T> T ʳchange(T x₁, T x₂) { return (x₂ - x₁) / x₁; } /* ∉[0,1]. */
#if (defined __mips__ || defined __armv6__ || defined espressif) && defined __cpp_concepts
#define innominate auto /*  a․𝘬․a 'innominate-type'. */
template <typename T> concept Relative₋accumulative = requires (T x₁, T x₂) {
 x₁ + x₂ /* -> int */; /*{*/ x₁ - x₂ /*} -> Same<bool>*/; Zero(x₂) /* -> T*/; };
 /*  a․𝘬․a 'Turtle' and 'algebraic category'. To instatiate write similar to 
 'template <Relative₋accumulative T>' ... , 
 'template <typename T> requires Relative₋accumulative<T> T operator... and 
 'void foo(Relative₋accumulative innominate & x) { ... }'. */
#endif
template <typename T> int collate₋coalesce(__builtin_int_t count, T xᵣ[], T * acc, 
 int (^port)(T x, T & acc)) { for (__builtin_int_t i=0; i<count; i++) { 
 int ok=port(xᵣ[i],*acc); if (!ok) { return ok; } } } /*  also known as: 'norm', 
 'linear-combine', also 'gaussian₋combination', 'irreversive₋combination' and 
 'permutative₋combination'. */
template <typename ℚ> ℚ arithmetic(ℚ x₁, ℚ x₂) { return (x₁ + x₂) / 2; }
/* template <typename T> T geometric(T x₁, T x₂) { return sqrt(x₁*x₂); }; */
template <typename T> T /* ⤪_ */ * Multiple(short exp𝗔ltNeg, 
  __builtin_int_t count, void (^default𝘖rNull)(T * elem)
)
{ T * base = NULL;
  if (exp𝗔ltNeg == -1) { base = (T *)Alloc(count*sizeof(T)); }
  else {  __builtin_int_t 🥈 𝟺𝟶𝟿𝟼 = Syspagesize();
    __builtin_int_t bytes=sizeof(T)*count,﹟=bytes/𝟺𝟶𝟿𝟼;
    void * 𝟺kbframes[1 + ﹟ + (bytes % 𝟺𝟶𝟿𝟼 ? 0 : 0)]; /*  the variable '﹟' is positive so ⌊⌋. */
    if (ContiguousAcquire(exp𝗔ltNeg,𝟺kbframes,﹟)) { return NULL; }
    base = (T *)𝟺kbframes[0];
  } /*  first-fit, most-recently-used and closest-fit. */
  for (__builtin_int_t i=0; i<count; ++i) { T * elem = new (i + base) T(); 
    if (default𝘖rNull) { for (__builtin_int_t i=0; i<count; ++i) { default𝘖rNull(base+i); } }
  }
  return base;
} /*  a․𝘬․a malloc, Startupalloc and Elements𝘖𝘳Heap. */
template <typename T> T biorythm₋average(T xt) { return sin(xt)*cos(xt); } /*  a․𝘬․a AB*sin(ω*t)*cos(ω*t). */
template <typename T> bool rel₋eq(T x₁, T x₂) { return !(x₁ < x₂ || x₂ < x₁); }
template <typename T> bool eql₋eq(T x₁, T x₂) { return x₁ == x₂; }; }
MACRO int64_t 𝟸₋compl(int64_t x) { x=~x; return ++x; }
MACRO int32_t 𝟸₋compl(int32_t x) { x=~x; return ++x; }
MACRO int64_t abs64i₁(int64_t x) { return x < 0 ? 𝟸₋compl(x) : x; }
MACRO int32_t abs32i₁(int32_t x) { return x < 0 ? 𝟸₋compl(x) : x; }
MACRO int64_t abs64i₂(int64_t x) { return __builtin_llabs(x); }
MACRO int32_t abs32i₂(int32_t x) { return __builtin_abs(x); }
template <typename ℕ> void invert(ℕ & x) { x = ~x; } /* ⬷ a․𝘬․a 'toggle₋all'. */
template <typename ℕ> void 𝟸₋Compl(ℕ & x) { invert(x); ++x; }
template <typename ℤ> ℤ abs₂(ℤ x) { return x < 0 ? 𝟸₋Compl(x) : x; }
/*  When x is set to INT_MIN, the interpretation is not representable as a positive 
 number and maps back to the same bit pattern when 2-complemented. (Two-complementing 
'identity a․𝘬․a zero' wraps and equals 0 when pattern is assumed unsigned.) */
/*  a․𝘬․a INTERFERENT, ABELIAN, TOTALITARIAN and NEITHER_PROLOGUE_NOR_EPILOGUE. */
#define rt₋namespace namespace
template <typename T> struct rectangle { T height, width; int /* Unit */ unit; };
template <typename T> struct measure { T value; int /* Unit */ unit; };

constexpr __builtin_int_t Frame(__builtin_uint_t size, __builtin_uint_t framesize)
{ return __builtin_int_t((size + framesize - 1) & ~(framesize - 1)); } 
/*  may be evaluated at compile-time a․𝘬․a 'constexpr'. */

constexpr __builtin_int_t Ceil(__builtin_int_t num, __builtin_int_t denom) 
{  int num₋neg=num<+0, denom₋neg=denom<+0;
  if (num₋neg) { num = -num; } if (denom₋neg) { denom = -denom; }
  __builtin_uint_t ℕ=num/denom, modula=num%denom; /*  also in sw/hw₋fractions. */
  int negative = denom₋neg ^ num₋neg ? 1 : 0;
  return (ℕ + (modula != 0 ? 1 : 0)) * (negative ? -1 : 1);
} /*  e․𝘨 ceil(sizeof(E)/4) = words, sizeof(E)/4 - 1 < words <= sizeof(E)/4. */

constexpr __builtin_int_t HowMany(__builtin_uint_t index, __builtin_uint_t width) {
  return (index % width == 0) ? index/width : index/width + 1; } 
/*  see all the multiple flavors of 'fraction' in --<System.cpp>. */

/* __builtin_int_t 🥈 Pagewords=Syspagesize()/Wordbytes; */
/*  a․𝘬․a 'arrangemang- possibly-window', 'ElemsInside4kb' and '𝟻𝟷𝟸alt𝟷𝟶𝟸𝟺'. */

/* Consider 32- alternatively 64-bits with an extra sign bit for abstractions 
 such as `Frame`, `isPowerOfTwo` and `geqAndPowerOfTwo`. */

template <typename T> T * Critic(const T * x) { return const_cast<T*>(x); }
template <typename T> T& Critic(const T &x) { return const_cast<T&>(x); } /*  a․𝘬․a "away 𝙘𝙤𝙣𝙨𝙩 evil". */
#endif
