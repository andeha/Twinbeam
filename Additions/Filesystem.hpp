/*  Filesystem.hpp */

#include <sys/stat.h>

MACRO
bool
FileSystemItemExists(
  int tetras,
  const char32_t * canonicalᵚ /* A․k․a `pathᵚ` */
)
{  struct stat st; bool invalid=false;
    __builtin_uint_t Maxpathᴮʸᵗᵉˢ = Utf8BytesIncludingNull(tetras<<2, canonicalᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    return stat((const char *)buffer, &st) == 0;
}

MACRO
bool
IsRegularFile(
  int tetras,
  const char32_t * canonicalᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISREG(st.st_mode);
}

__builtin_int_t
RegularOrLinkFileLength(
  int tetras,
  const char32_t * canonicalᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ =
    Utf8BytesIncludingNull(tetras<<2, canonicalᵚ, invalid);
    if (invalid) return -1;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return -2; }
    if (stat((const char *)buffer, &st)) { return -3; }
    return st.st_size;
} /* A․𝘬․a `RegularFileLength`. */

MACRO
bool
IsDirectory(
  int tetras,
  const char32_t * canonicalᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISDIR(st.st_mode);
}

MACRO
bool
IsSymbolicLink(
  int tetras,
  const char32_t * canonicalᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISLNK(st.st_mode);
}

