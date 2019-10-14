/*  Filesystem.hpp | Files with Unix. */

#include <sys/stat.h>

MACRO
int
FileSystemItemExists(
  int 𝘁𝗲𝘁𝗿𝗮𝘀,
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* A․k․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingANull(𝘁𝗲𝘁𝗿𝗮𝘀<<2, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return false; }
    return stat((const char *)buffer, &st) == 0;
}

MACRO
int
IsRegularFile(
  int 𝘁𝗲𝘁𝗿𝗮𝘀,
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingANull(𝘁𝗲𝘁𝗿𝗮𝘀<<2, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISREG(st.st_mode);
}

__builtin_int_t
RegularOrLinkFileLength(
  int 𝘁𝗲𝘁𝗿𝗮𝘀,
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ =
    Utf8BytesIncludingANull(𝘁𝗲𝘁𝗿𝗮𝘀<<2, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ, invalid);
    if (invalid) return -1;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return -2; }
    if (stat((const char *)buffer, &st)) { return -3; }
    return st.st_size;
} /* A․𝘬․a `RegularFileLength`. */

MACRO
int
IsDirectory(
  int 𝘁𝗲𝘁𝗿𝗮𝘀,
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingANull(𝘁𝗲𝘁𝗿𝗮𝘀<<2, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISDIR(st.st_mode);
}

MACRO
int
IsSymbolicLink(
  int 𝘁𝗲𝘁𝗿𝗮𝘀,
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* A․𝘬․a `pathᵚ` */
)
{  struct stat st; bool invalid=false; __builtin_uint_t Maxpathᴮʸᵗᵉˢ = 
      Utf8BytesIncludingANull(𝘁𝗲𝘁𝗿𝗮𝘀<<2, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ, invalid);
    if (invalid) return false;
    char buffer[Maxpathᴮʸᵗᵉˢ]; int ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return false; }
    if (stat((const char *)buffer, &st)) { return false; }
    return S_ISLNK(st.st_mode);
}

/* Also 𝘥𝘪𝘴𝘫𝘶𝘯𝘤𝘵𝘪𝘰𝘯: `IsHardlink`, `MayIntroduceInconsistencyAtRemoval` and `IsDisjunct`. */

