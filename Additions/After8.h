/*  After8.cpp | detail and two 'processes' a․𝘬․a 'expressive Timeserie'. */

#if defined __x86_64__

#include <vector>
#include <map>

template <typename K, typename V> struct Map { std::map<K,V> inner; 
  
  int exists(K key) { return inner.contains(key); }
  int include(K key, V val, bool * refresh) { 
    std::pair<typename std::map<K,V>::iterator, bool> y = inner.insert_or_assign(key,val);
    *refresh = !y.second;
  }
  int assoc(K key, void (^seek)(V * agent)) { auto it = inner.find(key); 
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

#endif /* ⬷ all 'man' pages unwritten, instead http://cppreference.com and cached versions of the latter. */

