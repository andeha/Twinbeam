/*  Filesystem.hpp | files with Unix. */

inline
int
FileSystemItemExists(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* ⬷ a․𝘬․a pathᵚ. */
)
{  struct stat st; __builtin_uint_t bytes = ExactUtf8bytes(𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,𝘁𝗲𝘁𝗿𝗮𝘀);
    char8_t buffer[bytes]; __builtin_int_t ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return 0; }
    return stat((const char *)buffer, &st) == 0;
}

inline
int
IsRegularFile(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* ⬷ a․𝘬․a pathᵚ. */
)
{  struct stat st; __builtin_uint_t bytes = ExactUtf8bytes(𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,𝘁𝗲𝘁𝗿𝗮𝘀);
    char8_t buffer[bytes]; __builtin_int_t ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return 0; }
    if (stat((const char *)buffer, &st)) { return 0; }
    return S_ISREG(st.st_mode);
}

inline
__builtin_int_t
RegularOrLinkFileLength(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* ⬷ a․𝘬․a pathᵚ. */
)
{  struct stat st; __builtin_uint_t bytes = ExactUtf8bytes(𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,𝘁𝗲𝘁𝗿𝗮𝘀);
    char8_t buffer[bytes]; __builtin_int_t ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return -2; }
    if (stat((const char *)buffer, &st)) { return -3; }
    return st.st_size;
} /* ⬷ a․𝘬․a 'RegularFileLength'. */

inline
int
IsDirectory(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* ⬷ a․𝘬․a pathᵚ. */
)
{  struct stat st; __builtin_uint_t bytes = ExactUtf8bytes(𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,𝘁𝗲𝘁𝗿𝗮𝘀);
    char8_t buffer[bytes]; __builtin_int_t ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return 0; }
    if (stat((const char *)buffer, &st)) { return 0; }
    return S_ISDIR(st.st_mode);
}

inline
int
IsSymbolicLink(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ /* ⬷ a․𝘬․a pathᵚ. */
)
{  struct stat st; __builtin_uint_t bytes = ExactUtf8bytes(𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,𝘁𝗲𝘁𝗿𝗮𝘀);
    char8_t buffer[bytes]; __builtin_int_t ³²b=0, ⁸b=0;
    if (⁺⁼UnicodeToUtf8(buffer, ³²b, ⁸b, 𝘁𝗲𝘁𝗿𝗮𝘀, 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ)) { return 0; }
    if (stat((const char *)buffer, &st)) { return 0; }
    return S_ISLNK(st.st_mode);
}

/* ⬷ also 𝘥𝘪𝘴𝘫𝘶𝘯𝘤𝘵𝘪𝘰𝘯: 'IsHardlink', 'MayIntroduceInconsistencyAtRemoval' and 'ContentisDisjunct'. */

