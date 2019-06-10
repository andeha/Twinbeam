/*  Filesystem.hpp */

#include <sys/stat.h>

MACRO
bool
FileSystemItemExists(
  int tetras,
  const char32_t * canonicalᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; 
    __builtin_uint_t Maxpathᴮʸᵗᵉˢ = Utf8BytesIncludingNull(tetras<<2, canonicalᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    return stat((const char *)buffer, &st) == 0;
}

MACRO
bool
IsRegularFile(
  int tetras,
  const char32_t * canonicalᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISREG(st.st_mode);
}

MACRO
__builtin_int_t
RegularFileLength(
  int tetras,
  const char32_t * canonicalᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return -1; }
    if (stat((const char *)buffer, &st)) { return -2; }
    return st.st_size;
} /* A.k.a `RegularOrLinkFileLength`. */

MACRO
bool
IsDirectory(
  int tetras,
  const char32_t * canonicalᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISDIR(st.st_mode);
}

MACRO
bool
IsSymbolicLink(
  int tetras,
  const char32_t * canonicalᵚ
) /* A․k․a `pathᵚ` */
{  struct stat st; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingNull(tetras<<2, canonicalᵚ);
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISLNK(st.st_mode);
}

