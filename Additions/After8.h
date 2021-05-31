/*  after8.cpp | detail and two 'processes' a․𝘬․a 'expressive timeserie'. */

#ifdef ADDITIONAL_LINKERSYMBOLS

template <typename K, typename V> struct Map { std::map<K,V> inner;
  
  int exists(K key) { return inner.contains(key); }
  int include(K key, V val, bool * didrefresh) {
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

#pragma mark in Unix named 'time.h' with 'time_t time()-time()' alt. 'difftime()'

typedef time_t Unix₋instant; /* ⬷ epoch is 00:00:00 UTC Jan 1, 1970. */

inline Tuple<int32_t, int32_t, int32_t> chronology₋Date(Unix₋instant I)
{
   struct tm * y = gmtime(&I);
   return Tuple<int32_t(y->tm_hour /* 0 - 23 */), int32_t(y->tm_min /* 0 - 59 */), 
    int32_t(y->tm_sec /* 0 - 60 */)>();
} /* seconds-to-calendric in prematurely 'set' time-zone: 'struct tm * localtime(const time_t *)'. */

inline Opt<Unix₋instant> chronology₋Timestamp(int32_t parts[6] /*, Chronology::UQ32 fract */)
{ /* ⬷ year, month (1-12), day (1-31), hour (0-23), minutes (0-59) and seconds (0-59) */
   int tm_sec=(int)parts[5], tm_min=(int)parts[4], tm_hour=(int)parts[3], 
    tm_mday=(int)parts[2], tm_mon=(int)parts[1], tm_year=(int)parts[0];
   struct tm t₁ { tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, 0, 0, 0, 0, 0 };
   time_t t₂ = timegm(&t₁);
   return Opt<Unix₋instant>(t₂);
} /* calendric-to-seconds in prematurely 'set' time-zone: 'time_t timelocal(struct tm * const)'. */

inline char * chronology₋InstantToText(Unix₋instant I) { return ctime(I); } /* ⬷ time2posix/posix2time. */

#else

template <typename K, typename V> struct Map { void * inner; 
  /* ⬷ a․𝘬․a std::map<K,V> inner. */
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
  
}; /* ⬷ sometime referential map such as std::map<const char *, Unicodes>. */

template <typename E> struct Vector { ˢConvoj<E> inner;
  
  void push(E elem) { inner.copy₋include(1, { elem }); }
  int pop() { if (inner.count == 0) { return -1; }
    inner.pop(); return 0; }
  int relative(__builtin_int_t idx, E ** reference) {
    if (idx >= inner.count) { return -1; }
    *reference = &inner[idx]; return 0;
  }
  
}; /* ⬷ similar to std::vector and not c++11's std::array in <array>. */

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
  
}; /* ⬷ bitsets grows in steps of pages and in wordbits steps. */

#endif /* ⬷ all 'man' pages unwritten, instead http://cppreference.com and 
 cached versions of the latter. */


