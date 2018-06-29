//
//  printf.cpp 
//  Twinbeam Additions
//

#include <Twinbeam.h>

// #define SYMBOL_IS_CHAR_NOT_VARIABLE_BYTE_COUNT_UTF8

INNER_FUNCTION
int
streamout_eightbit(
    const char *s,
    void (^output)(char c)
)
{ int printedExcept0 = 0;
    while (char c = *s++) { output(c); printedExcept0++; }
    return printedExcept0;
}

#ifdef SYMBOL_IS_CHAR_NOT_VARIABLE_BYTE_COUNT_UTF8

INNER_FUNCTION
int
vfprintf_eightbit(
    void (^output)(char c),
    const char *format,
    __builtin_va_list arg
)
{ __block int printedBytesExcept0 = 0;
    while (char c = *format++) {
        if (c != '%' || (c = *format++) == '%') { output(c); printedBytesExcept0++; }
        else { switch (c) {
            case 'd': {
                const __builtin_int_t d = __builtin_va_arg(arg, __builtin_int_t);
                Base(d, 10, 0, ^(char s) { output(s); printedBytesExcept0++; });
                break; }
            case 'x': {
                const __builtin_uint_t x = __builtin_va_arg(arg, __builtin_uint_t);
                Base(x, 16,
#ifdef __x86_64__
                     16
#elif defined __mips__
                     8
#endif
                , ^(char s) { output(s); printedBytesExcept0++; });
                break; }
            case 'b': {
                const __builtin_uint_t b = __builtin_va_arg(arg, __builtin_uint_t);
                Base(b, 2,
#ifdef __x86_64__
                     64
#elif defined __mips__
                     32
#endif
                , ^(char s) { output(s); printedBytesExcept0++; });
                break; }
            case 's': {
                const char *s = __builtin_va_arg(arg, const char *);
                printedBytesExcept0 += streamout_eightbit(s, output);
                break; }
 //         case 'S': {
 //             const char32_t *s = __builtin_va_arg(arg, const char32_t *);
 //             printedBytesExcept0 += streamout_unicodes(stream, s);
 //             break; }
        } }
    }
    return printedBytesExcept0;
}

FOCAL extern "C"
int printf(const char *eightbitFormat, ...)
{
    int result;
    va_prologue(eightbitFormat)
    result = vfprintf_eightbit(^(char c) { putch(c); }, eightbitFormat, arg);
    va_epilogue
    return result;
}

#else

INNER_FUNCTION
int
streamout_unicode(
    char32_t u,
    unsigned short (^output)(char *p, short unsigned bytes)
)
{ __block int bytesstreamed = 0;
    UnicodeToUtf8(u, ^(const uint8_t *p, int bytes) { // On a Microchip PIC32, the fifo is 4 or 8 levels deep.
        bytesstreamed += output((char *)p, bytes);
    });
    return bytesstreamed;
}

INNER_FUNCTION
int // bytes, symbols
streamout_unicodes(
    Memoryview *view,
    unsigned short (^output)(char *p, short unsigned bytes)
)
{
    // __block int symbolsExcept0 = 0;
    SemanticPointer<void *> p = view->region->pointer(0);
    const char32_t * unicodes = (const char32_t *)p.pointer;
    __block __builtin_int_t tetras = UnicodesUntilNull(unicodes, BUILTIN_INT_MAX);
    __builtin_int_t beam = 0;
    if (TokenizeUtf8OrUnicode(Encoding::unicode, *view, beam, // Ain't Stoppn' Until/At Dawn
      ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) {
          if (beam == tetras) stop = true;
          streamout_unicode(unicode, output); /* symbolsExcept0++; tetras--; */
      })) { }
    
    // view.region->forall(^(SemanticPointer<uint8_t *> isolative, bool first, bool
    //  last, __builtin_int_t index, signed short * step, bool& stop) {
    //    if (first) { *step = 4; } // We know that the region is sized modulo page size.
    //    char32_t *pu = (char32_t *)isolative.pointer;
    //    streamout_unicode(stream, *pu); symbolsExcept0++; c--;
    // });
    
    return (int)beam; // symbolsExcept0;
}

int // Tuple<int, int, int> i.e user-percieved characters, unicodes and utf-8
vfprintf_unicode(
    unsigned short (^output)(char *p, short unsigned bytes),
    const char32_t *oneblockFormat,
    __builtin_va_list arg
)
{
    __block int printedSymbolsExcept0 = 0;
    while (char32_t c = *oneblockFormat++) {
        if (c != '%' || (c = *oneblockFormat++) == '%') { streamout_unicode(c, output); printedSymbolsExcept0++; }
        else { switch (c) {
            case 'd': {
                const __builtin_int_t d = __builtin_va_arg(arg, __builtin_int_t);
                Base(d, 10, 0, ^(char s) { output(&s, 1); printedSymbolsExcept0++; });
                break; }
            case 'x': {
                const __builtin_uint_t x = __builtin_va_arg(arg, __builtin_uint_t);
                Base(x, 16,
#ifdef __x86_64__
                16
#elif defined __mips__
                8
#endif
                , ^(char s) { output(&s, 1); printedSymbolsExcept0++; });
                break; }
            case 'b': {
                const __builtin_uint_t b = __builtin_va_arg(arg, __builtin_uint_t);
                Base(b, 2,
#ifdef __x86_64__
                64
#elif defined __mips__
                32
#endif
                , ^(char s) { output(&s, 1); printedSymbolsExcept0++; });
                break; }
            case 's': {
                const char *s = __builtin_va_arg(arg, const char *);
                printedSymbolsExcept0 += streamout_eightbit(s, ^(char c) { output(&c, 1); });
                break; }
            case 'S': {
                Memoryview *view = __builtin_va_arg(arg, Memoryview *);
                printedSymbolsExcept0 += streamout_unicodes(view, output);
                break; }
        } }
    }
    return printedSymbolsExcept0;
}

int
vfprintf_utf8(
    unsigned short (^output)(char *p, short unsigned bytes),
    const char *utf8Format,
    __builtin_va_list arg
)
{
    String s = StringLiteral(utf8Format); // Requires that INLINED static String Literal(const char *utf8, ...) creates a one-block Unicode string, which the method does.
    int result = vfprintf_unicode(output, (const char32_t *)(*s).region->pointer(0).pointer, arg); // ☜😐 TODO: Consider adding a user-defined Unicode for next block address.
    return result;
}

FOCAL extern "C"
int printf(const char *utf8Format, ...)
{
    int result;
    va_prologue(utf8Format)
    result = vfprintf_utf8(^(char * utf8, short unsigned bytes) { unsigned short i = bytes; while (i--) { putch(*(utf8 + i)); } return bytes; }, utf8Format, arg);
    va_epilogue
    return result;
}

#endif

