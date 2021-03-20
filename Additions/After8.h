/*  After8.cpp | detail and two 'processes' a․𝘬․a 'expressive timeserie'. */

/* #define ADDITIONAL₋LINKERSYMBOLS */

#if defined ADDITIONAL₋LINKERSYMBOLS && defined __x86_64__

#include <vector>
#include <map>

template <typename K, typename V> struct Map { std::map<K,V> inner;
  
  int exists(K key) { return inner.contains(key); }
  int include(K key, V val, bool * refresh) {
    std::pair<typename std::map<K,V>::iterator, bool> y = 
     inner.insert_or_assign(key,val); *refresh = !y.second; }
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
  
  Bitset(__builtin_int_t bits₋initial) { inner.reserve(bits₋initial); }
  
  void set (__builtin_int_t slot, int val) {
    if (slot >= inner.size()) { inner.reserve(slot); }
    inner[slot] = (bool)val; }
  int get (__builtin_int_t slot, int * val) {
    if (slot >= inner.size()) { return -1; }
    *val = (int)inner[slot];
    return 0;
  }
  
};

#pragma mark in Unix named 'time.h' with 'time_t time()-time()' alt. 'difftime()'

#include <time.h>

typedef time_t Unix₋instant; /* ⬷ epoc is 00:00:00 UTC Jan 1, 1970. */

Tuple<int32_t, int32_t, int32_t> chronology₋Date(Unix₋instant I)
{
   struct tm * y = gmtime(&I);
   return Tuple<int32_t(y->tm_hour /* 0 - 23 */), int32_t(y->tm_min /* 0 - 59 */), 
    int32_t(y->tm_sec /* 0 - 60 */)>();
} /* seconds-to-calendric in prematurely 'set' time-zone: 'struct tm * localtime(const time_t *)'. */

Opt<Unix₋instant> chronology₋Timestamp(int32_t parts[6] /*, Chronology::UQ32 fract */)
{ /* ⬷ year, month (1-12), day (1-31), hour (0-23), minutes (0-59) and seconds (0-59) */
   int tm_sec=(int)parts[5], tm_min=(int)parts[4], tm_hour=(int)parts[3], 
    tm_mday=(int)parts[2], tm_mon=(int)parts[1], tm_year=(int)parts[0];
   struct tm t₁ { tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, 0, 0, 0, 0, 0 };
   time_t t₂ = timegm(&t₁);
   return Opt<Unix₋instant>(t₂);
} /* calendric-to-seconds in prematurely 'set' time-zone: 'time_t timelocal(struct tm * const)'. */

char * chronology₋InstantToText(Unix₋instant I) { return ctime(I); } /* ⬷ time2posix/posix2time. */

#else

template <typename K, typename V> struct Map { void ᶿ* inner; 
  /* ⬷ a․𝘬․a std::map<K,V> inner. */
  int exists(K key) {
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    Treeint leafkey { .keyvalue = { int64_t key, 0 } };
#elif defined __mips__ || defined __armv6__ || defined espressif
    Treeint leafkey { .keyvalue = { int32_t key, 0 } };
#endif
    Treeint * found = Lookup(inner,leafkey);
    return found == NULL; }
  int include(K key, V val, bool * refresh) {
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    Treeint leafkey { .keyvalue = { int64_t key, int64_t(0) } };
#elif defined __mips__ || defined __armv6__ || defined espressif
    Treeint leafkey { .keyvalue = { int32_t key, int32_t(0) } };
#endif
    auto alloc = ^(int bytes) { return Alloc(bytes); };
    void * y = Insert(inner,leafkey,alloc);
    return y != NULL;
  }
  void assoc(K key, void (^seek)(V * agent)) {
#if defined __x86_64__ || defined __armv8a__ || defined Kirkbridge
    Treeint leafkey { .keyvalue = { int64_t key, 0 } };
#elif defined __mips__ || defined __armv6__ || defined espressif
    Treeint leafkey { .keyvalue = { int32_t key, 0 } };
#endif
    Treeint * found = Lookup(inner,leafkey);
    seek(found);
  }
  
}; /* ⬷ sometime referential map such as map<const char *, Unicodes>. */

template <typename E> struct Vector { ˢConvoj<E> inner;
  
  void push(E elem) { inner.copy₋include(1, { elem }); }
  int pop() { if (inner.count == 0) { return -1; }
    inner.pop(); return 0; }
  int relative(__builtin_int_t n, E ** reference) {
    if (n >= inner.count) { return -1; }
    *reference = &inner[n]; return 0;
  }
  
};

struct Bitset { __builtin_int_t 🥈 wordbits=Wordbytes*8; structure inner; 
  
 /* if (Setup₋shattered(unsigned expeditionary __builtin_int_t ﹟, 
  structure& sequence) * Setup₋initially₋one */
  
  Bitset(__builtin_int_t bits₋initial) { inner.reserve(bits₋initial); }
  
  void set (__builtin_int_t slot, int val) {
    if (slot >= inner.size()) { inner.reserve(slot); }
    /* uint8_t * relative(__builtin_int_t byte₋offset); */
    inner[slot] = (bool)val; }
  
  int get (__builtin_int_t slot, int * val) {
    if (slot >= inner.size()) { return -1; }
    /* uint8_t * relative(__builtin_int_t byte₋offset); */
    __builtin_int_t w = slot / wordbits, b = slot % wordbits;
    *val = inner[w] & (0b1<<b) ? 1 : 0;
    return 0;
  }
  
}; /* bitsets may grow relatively-absolutely and in bits-words steps. */

#endif /* ⬷ all 'man' pages unwritten, instead http://cppreference.com and 
 cached versions of the latter. */


