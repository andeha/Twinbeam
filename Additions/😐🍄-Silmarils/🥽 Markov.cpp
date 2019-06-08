/*  Markov.cpp | Subtle, yet statistically correct. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/Filesystem.hpp>

/* Compile with xcrun clang @ccargs_macos -o Markov '🥽 Markov.cpp'        \
  ../../Source/Releases/libTwinbeam_macOS.a ../../Source/llvmʳᵗ³.cpp */

int Tokenize₁(uint8_t * base, __builtin_int_t bytes) {
  auto feeder = ^(char32_t &unicode) { return Tokenizefact::error; };
  auto ahead = ^(char32_t * unicodes, __builtin_int_t count) { return Inputcontrol::ok; };
  auto token = ^(char32_t * unicodes, __builtin_int_t count) { return Inputcontrol::ok; };
  if (Tokenize(feeder, ahead, token)) { return -5; }
  return 0;
}

int Tokenize₂(uint8_t * base, __builtin_int_t bytes) { 
    auto feeder = ^(char &utf8byte) { return Readlineopinion::quit; };
    auto line = ^(char * line) { return Inputcontrol::quit; };
    if (ReadUtf8(feeder, line)) { return -1; }
    return 0;
} /* Also available: `ReadUnicode`. */

int Tokenize₃(Encoding encoding, uint8_t * base, __builtin_int_t bytes) {
    Memoryregion region { base, bytes, NULL };
    Memoryview content { &region, 0, region.bytes() }; int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 line=1;
    enum { PARAGRAPH_SEPARATOR=U'\u2029', LINE_SEPARATOR=U'\u2028' };
    // struct Utf8Artifact { __builtin_int_t line, bytesOffset, count; };
    struct Artifacts { Utf8Artifact tokens[1000]; Artifacts *prev, next; } art;
    auto isSeparator = ^(char32_t uc) { return uc == U'\n' || uc == PARAGRAPH_SEPARATOR || uc == LINE_SEPARATOR };
    __builtin_int_t beam=0; if (TokenizeUtf8OrUnicode(encoding, content, beam,
       ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) {
         if (isSeparator(unicode)) line++;
       }
    )) { return -1; }
    
    return 0;
}

int Process(const char * ᵘᵗf⁸path, void (^open)(uint8_t * base, int bytes))
{ int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 y=0;
    __builtin_int_t 🥈ᵢ Maxbytesᵒˢᵖᵃᵗʰ = 1024;
    __builtin_uint_t tetrasᵗᵒᵗ = UnicodesUntilNull(ᵘᵗf⁸path, Maxbytesᵒˢᵖᵃᵗʰ);
    if (tetrasᵗᵒᵗ > Maxbytesᵒˢᵖᵃᵗʰ) { return -2; }
    char32_t pathᵤC[tetrasᵗᵒᵗ+1], 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 * pathᵤC₂=pathᵤC;
    ⁺⁼Utf8ToUnicode(ᵘᵗf⁸path, pathᵤC);
    
    if (FileSystemItemExists(tetrasᵗᵒᵗ, pathᵤC) && IsRegularFile(tetrasᵗᵒᵗ, pathᵤC)) {
        __builtin_int_t bytes = RegularFileLength(tetrasᵗᵒᵗ, pathᵤC);
        __builtin_int_t pagesOffset=0, pagesCountOrZero=0, bytesActual;
        extern void * mapfileʳᵚ(const char * utf8Filepath, __builtin_int_t 
          pagesOffset, __builtin_int_t pagesCountOrZero, __builtin_int_t * 
          bytesActual);
        uint8_t * base = (uint8_t *)mapfileʳᵚ(ᵘᵗf⁸path, pagesOffset, 
          pagesCountOrZero, &bytesActual); /* ☜😐 */
        y = open(base, bytes);
   }
   
   return y;
}

#pragma mark - Main entry point

int
main(
  int argc,
  const char * argv[]
)
{
    if (argc < 2) { return -1; } const char * ᵘᵗf⁸path = argv[1];
    __builtin_int_t 🥈ᵢ Maxbytesᵒˢᵖᵃᵗʰ = 1024;
    __builtin_uint_t tetrasᵗᵒᵗ = UnicodesUntilNull(ᵘᵗf⁸path, Maxbytesᵒˢᵖᵃᵗʰ);
    if (tetrasᵗᵒᵗ > Maxbytesᵒˢᵖᵃᵗʰ) { return -2; }
    char32_t pathᵤC[tetrasᵗᵒᵗ+1], 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 * pathᵤC₂=pathᵤC;
    ⁺⁼Utf8ToUnicode(ᵘᵗf⁸path, pathᵤC);
    int y = Process(ᵘᵗf⁸path. ^(uint8_t * base, int bytes) { 
        if (!base) return -4;
        if (Tokenize₁(base, bytesActual)) { return -5; }
        if (Tokenize₂(base, bytesActual)) { return -6; }
        if (Tokenize₃(Encoding::utf8, base, bytesActual)) { return -7; }
    });
    if (y) { return y; }
    return 0;
}

/* Consider storing path length in --<🥽 i-node.cpp>. */

