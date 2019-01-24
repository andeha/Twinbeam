//
//  Headalong.h
//  Additions
//

struct String {
    
    /**
     
     Given a traditional null-terminated utf-8 character sequence, create
     an owning read-only `String` instance.
     
     */
    
    static Opt<String> Literal(const char *utf8, ...);
    
    /**  Copy a 𝑏𝑙𝑜𝑐𝑘 of unicodes and create an owning `String`. */
    
    static
    String
    PossiblyMeasuredLiteral(
      const char32_t *nativeEndianUnicodes,
      __builtin_int_t tetrasOrMinusOne, // -1 indicates loop until NULL. (Still?)
      bool readonly,
      void * (^alloc)(__builtin_int_t bytes) /* = ^(__builtin_int_t bytes)
        { return Alloc(bytes); } */
    );
    
    /**  Creates an already measured or truncated @c String. */
    
    static
    Opt<String>
    PossiblyMeasuredLiteral(
      const char *utf8,
      __builtin_int_t bytesOrMinusOne, // -1 indicates loop until NULL.
      bool readonly,
      __builtin_va_list arg,
      void (^fallow)(void * p) /* = ^(void * p) { Fallow(p); } */,
      void * (^alloc)(__builtin_int_t bytes) /* = ^(__builtin_int_t bytes)
        { return Alloc(bytes); } */
    );
    
    /**  As String::Literal, but creates an owning writable instance. */
    
    static Opt<String> FluctuantLiteral(const char *utf8, ...);
    
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
      __builtin_int_t count, void *(^alloc)(__builtin_int_t bytes) = ^(
      __builtin_int_t bytes) { return Alloc(bytes); } );
    
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
ONLY_FOR_SOFT_REALTIME
MACRO
String
Concaternate(
  const String& l, const String& r,
  void *(^alloc)(__builtin_int_t bytes) = Alloc
)
{
    __builtin_int_t bl = l.unicodeCount() << 2, br = r.unicodeCount() << 2;
    const char32_t *nativeEndianUnicodes = (char32_t *)alloc(bl + br);
    Copy8Memory((ByteAlignedRef)nativeEndianUnicodes, (ByteAlignedRef)((*l).
      region->pointer(0).pointer), bl);
    Copy8Memory((ByteAlignedRef)(nativeEndianUnicodes + bl),
      (ByteAlignedRef)((*r).region->pointer(0).pointer), br);
    return String::PossiblyMeasuredLiteral(nativeEndianUnicodes, (bl + br)>>2, 
      true, alloc);
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
    *)&c, 1, Alloc);
}

ONLY_FOR_SOFT_REALTIME MACRO String operator+(const String& l, const String& r)
{ return Concaternate(l, r, Alloc); }

__builtin_int_t UnicodesUntilNull(const char *utf8, __builtin_int_t max);
__builtin_int_t UnicodesUntilNull(const char32_t *nativeEndianUnicodes,
  __builtin_int_t max);
__builtin_int_t Utf8BytesUntilNull(const char *utf8, __builtin_int_t max);

#pragma mark - ”𝑇ℎ𝑒 𝑉𝑒𝑐𝑡𝑜𝑟” 🤲

template <typename T> struct Sequence { // Consider `confess`.
    virtual __builtin_int_t count() const = 0;
    virtual int dereference(__builtin_int_t idx, void (^touchbase)(SemanticPointer<T *> elem)) const = 0;
    MACRO int /* ∀ */ forall(void (^block)(SemanticPointer<T *> tranquil,
      bool first, bool last)) const { __builtin_int_t sz=count(), idx=0;
    again:
        if (idx < itemCount) {
            __block bool innerStop;
            if (dereference(idx, ^(SemanticPointer<T *> elem) {
                block(tranquil, idx == 0, idx == sz - 1, idx, innerStop);
            }))
            {
                return -2;
            }
            if (innerStop) { return -1; }
            idx++; goto again;
        }
        return 0;
    }
};

template <typename T, typename C = Sequence<T>> struct Mitigate : public Sequence<T> { };
    
template <typename T>
struct Vector : public Mitigate<T, Vector<T>> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Vector(std::initializer_list<T> l) :
    Vector(l.size()/sizeof(T), Alloc) { const T * i = l.begin(); const T *
    const end = l.end(); for (; i != end; ++i) push(*i); }
    
    Vector() : Vector(0, Alloc) { }
    
    Vector(__builtin_int_t count, void * (^alloc)(__builtin_int_t) /* = ^(
      __builtin_int_t bytes) { return Alloc(bytes); } */ ) { allocate = alloc;
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

// Vector2D with row,cols and `bleed`

#pragma mark - 🗺 ”𝑇ℎ𝑒 𝑀𝑎𝑝”

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
    
    V * find(__builtin_treeint_t mask) const { void * x = Lookup(opaque, mask);
      return (V *)x; }
    
    void dfs(void (^visit)(V& value, bool& stop, void * node)) { Forall(opaque,
      ^(void * ref, bool& stop, __builtin_treeint_t mask, void * node) { visit((
      V&)ref, stop, node); }); }
    
    void *opaque = NULL; void * (^allocate)(__builtin_int_t);
};

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
    
    Map() : SharedMap<V>(Alloc) { }
    
    Map(const Map<K, V>& other) : SharedMap<V>(Alloc) {
        Forall(other.opaque, ^(void * ref, bool& stop, __builtin_treeint_t
          mask, void * node) {
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
      __builtin_treeint_t mask, V * found) { exists = found; }); return exists; }
    
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
            } else { SharedMap<V>::treeInsert(mask, value);
                keys.push(key); // ⬷ Currently unsorted and not inserted into a tree consisting of keys.
            }
        });
        
        return y ? Opt<V&>(*y) : Opt<V&>::no();
    }
    
    /**  Removes a value and returns a reference to that value. */
    
    // Opt<V&> remove(const K& key) {} // TODO: Mark as yellow.
    
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

template<typename V> struct Map<const char *, V> : public SharedMap<V> {
    
  /* ⚠️ IMPLIES_DOING_HARDTIME */ Map(std::initializer_list<Tuple<const char *,
    V>> l) : Map() { const Tuple<const char *, V> *i = l.begin(); auto end =
    l.end(); for (; i != end; ++i) include(get<0>(*(Tuple<const char *, V> *)i),
    get<1>(*(Tuple<const char *, V> *)i), true); }
    
    Map() : SharedMap<V>(Alloc) { }
    
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
    
    /* Opt<V&> remove(const char * key) { } */
    
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
    
    Map() : SharedMap<V>(Alloc) { }
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
    
    // Opt<V&> remove(const char32_t *key) { }
    
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
    
    Map() : SharedMap<V>(Alloc) { }
    
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
    
    /* Opt<V&> remove(__builtin_int_t key) { } */
    
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
