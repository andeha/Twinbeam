/*  Markov.cpp | Subtle, yet statistically correct. */

#include <Twinbeam.h>

/* Compile with xcrun clang @ccargs_macos -o Markov '🥽 Markov.cpp' 
  .././Source/Releases/libTwinbeam_macOS.a */

#define 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 __attribute__ ((nonnull))
__builtin_uint_t UnicodesUntilNull(const char * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 utf8, 
    __builtin_int_t maxbytes);
__builtin_uint_t Utf8BytesIncludingNull(__builtin_int_t bytes, 
    const char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 nativeEndianUnicodes);

// ✁ until ✂️

#define UnicodeToUtf8(Buffer,³²B,⁸B)                                        \
auto unicodeToUtf8 = ^(char buffer[], int& ³²b, int& ⁸b) {                  \
again:                                                                      \
   if (UnicodeToUtf8(*(nameᵚ + ³²b), ^(const uint8_t *p, int bytes) {       \
      Copy8Memory((ByteAlignedRef)(buffer + ⁸b), (ByteAlignedRef)p, bytes); \
      ⁸b += bytes; })) { return -1; }                                       \
   if (++³²b < tetras) goto again;                                          \
   return 0;                                                                \
}(Buffer, ³²B, ⁸B)

#include <sys/stat.h>

MACRO
bool
FileSystemItemExists(
  int tetras,
  const char32_t * nameᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; 
    __builtin_uint_t Maxpathᴮʸᵗᵉˢ = Utf8BytesIncludingNull(tetras<<2, nameᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    return stat((const char *)buffer, &st) == 0;
}

MACRO
bool
IsRegularFile(
  int tetras,
  const char32_t * nameᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, nameᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISREG(st.st_mode);
}

MACRO
__builtin_int_t
RegularFileLength(
  int tetras,
  const char32_t * nameᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, nameᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (UnicodeToUtf8(buffer, ³²b, ⁸b)) { return -1; }
    if (stat((const char *)buffer, &st)) { return -2; }
    return st.st_size;
}

MACRO
bool
IsDirectory(
  int tetras,
  const char32_t * nameᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, nameᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISDIR(st.st_mode);
}

MACRO
bool
IsSymbolicLink(
  int tetras,
  const char32_t * nameᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, nameᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISLNK(st.st_mode);
}

// ✂️ >> --[Additions]>--<Filesystem.hpp>

enum class Inputcontrol { ok, quit };
enum class Tokenizefact { fragment, rejecting, separator, error, eol };

int
Tokenize(
  Tokenizefact (^feeder)(char32_t &unicode),
  Inputcontrol (^ahead)(char32_t * unicodes, __builtin_int_t count),
  Inputcontrol (^token)(char32_t * unicodes, __builtin_int_t count)
);

int Tokenize₁(uint8_t * base, __builtin_int_t bytes) {
  auto feeder = ^(char32_t &unicode) { return Tokenizefact::error; };
  auto ahead = ^(char32_t * unicodes, __builtin_int_t count) { return Inputcontrol::ok; };
  auto token = ^(char32_t * unicodes, __builtin_int_t count) { return Inputcontrol::ok; };
  if (Tokenize(feeder, ahead, token)) { return -5; }
  return 0;
}

enum class Readlineopinion { accept, rejecting, commit, quit };

int ReadUtf8(Readlineopinion (^feeder)(char &utf8byte), Inputcontrol (^line)
  (char * line));

int Tokenize₂(uint8_t * base, __builtin_int_t bytes) { 
    auto feeder = ^(char &utf8byte) { return Readlineopinion::quit; };
    auto line = ^(char * line) { return Inputcontrol::quit; };
    if (ReadUtf8(feeder, line)) { return -1; }
    return 0;
} /* Also available: `ReadUnicode`. */

int Tokenize₃(uint8_t * base, __builtin_int_t bytes) {
    Memoryregion region { base, bytes, NULL };
    Memoryview content { &region, 0, region.bytes() };
    __builtin_int_t beam;
    if (TokenizeUtf8OrUnicode(Encoding::utf8, content, beam,
       ^(char32_t unicode, __builtin_int_t byteOffset, bool& stop) { 
       }
    )) { return -1; }
    
    return 0;
}

#pragma mark - Main Entry Point

int
main(
  int argc,
  const char * argv[]
)
{
    if (argc < 2) { return -1; } const char * ᵘᵗf⁸path = argv[1]; 
    __builtin_int_t 🥈ᵢ Maxbytesᵒˢᵖᵃᵗʰ = 1024;
    __builtin_uint_t tetrasᵗᵒᵗ = UnicodesUntilNull(ᵘᵗf⁸path, Maxbytesᵒˢᵖᵃᵗʰ);
    char32_t pathᵤC[tetrasᵗᵒᵗ+1], 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 * pathᵤC₂=pathᵤC;
    
    auto utf8ToUnicode = ^(const char * utf8, char32_t unicodes[]) {
      __builtin_int_t followers, incr; int ⁸b=0, tetra/*a.k.a ³²b*/=0; char32_t uc;
again:
      const char *leadOr8Bit = (const char *)utf8 + ⁸b;
      if (*leadOr8Bit == 0x0) { goto not_again; }
      followers = Utf8Followers(*leadOr8Bit);
      if (followers < 0) { return -2; }
      incr = followers + 1;
      uc = Utf8ToUnicode(leadOr8Bit, incr);
      if (uc == 0xFFFE || uc == 0xFFFF) { return -3; }
      /* else if (uc != U'🔗' && uc != U'@') { // streamout_unicode(uc): 
        pathᵤC[tetra] = uc; tetra++ } else { PrintArgAndPop(uc, 
        printedSymbolsExcept0, __arg); } */ pathᵤC₂[tetra] = uc; tetra++;
      ⁸b += incr; goto again;
not_again:
      pathᵤC₂[tetra] = END_OF_TRANSMISSION; /* …when `ᵘᵗf⁸path` is to be 
        parsed by machine. */
      return 0;
    };
    
    utf8ToUnicode(ᵘᵗf⁸path, pathᵤC);
    
    if (FileSystemItemExists(tetrasᵗᵒᵗ, pathᵤC) && IsRegularFile(tetrasᵗᵒᵗ, pathᵤC)) {
        __builtin_int_t bytes = RegularFileLength(tetrasᵗᵒᵗ, pathᵤC);
        __builtin_int_t pagesOffset=0, pagesCountOrZero=0, bytesActual;
        extern void * mapfile(const char * utf8Filepath, __builtin_int_t 
          pagesOffset, __builtin_int_t pagesCountOrZero, __builtin_int_t * 
          bytesActual);
        uint8_t * base = (uint8_t *)mapfile(ᵘᵗf⁸path, pagesOffset, 
          pagesCountOrZero, &bytesActual);
        if (!base) return -4;
        if (Tokenize₁(base, bytesActual)) { return -5; }
        if (Tokenize₂(base, bytesActual)) { return -6; }
        if (Tokenize₃(base, bytesActual)) { return -7; }
    }
    
    return 0;
}

/* TODO: Consider storing path length in inode. */

