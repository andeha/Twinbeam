/* Headalong.h | Additions. */

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
    s.replace(Memoryview { view.region, s.unicodeCount(), 0 }, 
      (const char32_t *)&c, 1, Alloc);
}

ONLY_FOR_SOFT_REALTIME MACRO String operator+(const String& l, const String& r)
{ return Concaternate(l, r, Alloc); }

