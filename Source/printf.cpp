//
//  printf.cpp 
//  The MIPS/PIC32 Monitor
//

#include "Monitor.h"
#include "pic32mx.hpp"
#include "pic32mz.hpp"
#include "stable.hpp"

#define SYMBOL_IS_CHAR_NOT_VARIABLE_BYTE_COUNT_UTF8

INNER_FUNCTION
void
streamout_char(
    Outputstream *stream,
    char c
)
{ stream->write((uint8_t *)&c, (__builtin_uint_t)1); }

INNER_FUNCTION
int
streamout_eightbit(
    Outputstream *stream,
    const char *s
)
{ int printedExcept0 = 0;
    while (char c = *s++) { streamout_char(stream, c); printedExcept0++; }
    return printedExcept0;
}

#ifdef SYMBOL_IS_CHAR_NOT_VARIABLE_BYTE_COUNT_UTF8

INNER_FUNCTION
int
vfprintf_eightbit(
    Outputstream *stream,
    const char *format,
    __builtin_va_list arg
)
{ __block int printedBytesExcept0 = 0;
    while (char c = *format++) {
        if (c != '%' || (c = *format++) == '%') { streamout_char(stream, c); printedBytesExcept0++; }
        else { switch (c) {
            case 'd': {
                const __builtin_int_t d = __builtin_va_arg(arg, __builtin_int_t);
                Base(d, 10, 0, ^(char s) { streamout_char(stream, s); printedBytesExcept0++; });
                break; }
            case 'x': {
                const __builtin_uint_t x = __builtin_va_arg(arg, __builtin_uint_t);
                Base(x, 16,
#ifdef __x86_64__
                    16
#elif defined __mips__
                     8
#endif
                , ^(char s) { streamout_char(stream, s); printedBytesExcept0++; });
                break; }
            case 'b': {
                const __builtin_uint_t b = __builtin_va_arg(arg, __builtin_uint_t);
                Base(b, 2,
#ifdef __x86_64__
                     64
#elif defined __mips__
                     32
#endif
                , ^(char s) { streamout_char(stream, s); printedBytesExcept0++; });
                break; }
            case 's': {
                const char *s = __builtin_va_arg(arg, const char *);
                printedBytesExcept0 += streamout_eightbit(stream, s);
                break; }
#ifdef VARIABLE_BYTE_COUNT_UTF8
            case 'S': {
                const char32_t *s = __builtin_va_arg(arg, const char32_t *);
                printedBytesExcept0 += streamout_unicodes(stream, s);
                break; }
#endif
        } }
    }
    return printedBytesExcept0;
}

FOCAL extern "C"
int printf(const char *eightBitFormat, ...)
{
    int result;
    va_prologue(eightBitFormat)
    result = vfprintf_eightbit(&ctx.io, eightBitFormat, arg);
    va_epilogue
    return result;
}

#else

INNER_FUNCTION
int
streamout_unicode(
    Outputstream *stream,
    char32_t u
)
{ __block int bytesStreamed = 0;
    UnicodeToUtf8(u, ^(const uint8_t *p, int bytes) { // On a Microchip PIC32, the fifo is 4 or 8 levels deep.
        bytesStreamed += stream->write((uint8_t *)p, bytes);
    });
    return bytesStreamed;
}

INNER_FUNCTION
int // bytes, symbols
streamout_unicodes(
    Outputstream *stream,
    Memoryview *view
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
          streamout_unicode(stream, unicode); /* symbolsExcept0++; tetras--; */
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
    Outputstream *stream,
    const char32_t *oneblockFormat,
    __builtin_va_list arg
)
{
    __block int printedSymbolsExcept0 = 0;
    while (char32_t c = *oneblockFormat++) {
        if (c != '%' || (c = *oneblockFormat++) == '%') { streamout_unicode(stream, c); printedSymbolsExcept0++; }
        else { switch (c) {
            case 'd': {
                const __builtin_int_t d = __builtin_va_arg(arg, __builtin_int_t);
                Base(d, 10, 0, ^(char s) { streamout_char(stream, s); printedSymbolsExcept0++; });
                break; }
            case 'x': {
                const __builtin_uint_t x = __builtin_va_arg(arg, __builtin_uint_t);
                Base(x, 16,
#ifdef __x86_64__
                16
#elif defined __mips__
                8
#endif
                , ^(char s) { streamout_char(stream, s); printedSymbolsExcept0++; });
                break; }
            case 'b': {
                const __builtin_uint_t b = __builtin_va_arg(arg, __builtin_uint_t);
                Base(b, 2,
#ifdef __x86_64__
                64
#elif defined __mips__
                32
#endif
                , ^(char s) { streamout_char(stream, s); printedSymbolsExcept0++; });
                break; }
            case 's': {
                const char *s = __builtin_va_arg(arg, const char *);
                printedSymbolsExcept0 += streamout_eightbit(stream, s);
                break; }
            case 'S': {
                Memoryview *view = __builtin_va_arg(arg, Memoryview *);
                printedSymbolsExcept0 += streamout_unicodes(stream, view);
                break; }
        } }
    }
    return printedSymbolsExcept0;
}

int
vfprintf_utf8(
    Outputstream *stream,
    const char *utf8Format,
    __builtin_va_list arg
)
{
    String s = StringLiteral(utf8Format); // Requires that INLINED static String Literal(const char *utf8, ...) creates a one-block Unicode string, which the method does.
    int result = vfprintf_unicode(stream, (const char32_t *)(*s).region->pointer(0).pointer, arg); // ☜😐 TODO: Consider adding a user-defined Unicode for next block address.
    return result;
}

FOCAL extern "C"
int printf(const char *utf8Format, ...)
{
    int result;
    va_prologue(utf8Format)
    result = vfprintf_utf8(_myTerminal.outputstream(), utf8Format, arg);
    va_epilogue
    return result;
}

#endif

