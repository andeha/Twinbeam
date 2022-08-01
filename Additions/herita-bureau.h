/*  herita-bureau.h | f‌olders and files with Unix. */

inline
int
FileSystemItemExists(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32̄_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ
)
{ struct stat st; char8₋t buffer[4*𝘁𝗲𝘁𝗿𝗮𝘀]; __builtin_int_t ⁸b=0;
   if (UnicodeToUtf8(𝘁𝗲𝘁𝗿𝗮𝘀,𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,buffer,⁸b)) { return 0; }
   return stat((const char *)buffer, &st) == 0;
}

inline
int
IsRegularFile(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32̄_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ
)
{ struct stat st; char8₋t buffer[4*𝘁𝗲𝘁𝗿𝗮𝘀]; __builtin_int_t ⁸b=0;
   if (UnicodeToUtf8(𝘁𝗲𝘁𝗿𝗮𝘀,𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,buffer,⁸b)) { return 0; }
   if (stat((const char *)buffer, &st)) { return 0; }
   return S_ISREG(st.st_mode);
}

inline
__builtin_int_t
RegularOrLinkFileLength(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32̄_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ
)
{ struct stat st; char8₋t buffer[4*𝘁𝗲𝘁𝗿𝗮𝘀]; __builtin_int_t ⁸b=0;
   if (UnicodeToUtf8(𝘁𝗲𝘁𝗿𝗮𝘀,𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,buffer,⁸b)) { return -1; }
   if (stat((const char *)buffer, &st)) { return -2; }
   return st.st_size;
} /*  formerly 'RegularFileLength'. */

inline
int
IsDirectory(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32̄_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ
)
{ struct stat st; char8₋t buffer[4*𝘁𝗲𝘁𝗿𝗮𝘀]; __builtin_int_t ⁸b=0;
   if (UnicodeToUtf8(𝘁𝗲𝘁𝗿𝗮𝘀,𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,buffer,⁸b)) { return 0; }
   if (stat((const char *)buffer, &st)) { return 0; }
   return S_ISDIR(st.st_mode);
}

inline
int
IsSymbolicLink(
  int 𝘁𝗲𝘁𝗿𝗮𝘀, 
  char32̄_t * 𝑙𝑒𝑎𝑑𝑖𝑛𝑔 𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ
)
{ struct stat st; char8₋t buffer[4*𝘁𝗲𝘁𝗿𝗮𝘀]; __builtin_int_t ⁸b=0;
   if (UnicodeToUtf8(𝘁𝗲𝘁𝗿𝗮𝘀,𝗰𝗮𝗻𝗼𝗻𝗶𝗰𝗮𝗹ᵚ,buffer,⁸b)) { return 0; }
   if (stat((const char *)buffer, &st)) { return 0; }
  return S_ISLNK(st.st_mode);
}

/*  also 𝘥𝘪𝘴𝘫𝘶𝘯𝘤𝘵𝘪𝘰𝘯: 'IsHardlink', 'MayIntroduceInconsistencyAtRemoval' and 'ContentisDisjunct'. */

inline int Follow(struct Unicodes optlinkᵚ, 
  void (^sometime)(const char * nonlinkpath)
)
{
   if (TransformAndResolve(optlinkᵚ, ^(char * regularOrLinkpath) {
     expansion₂
     struct stat st; int is₋symbolic = S_ISLNK(st.st_mode);
     if (is₋symbolic) { char8₋t nonlink[PATH_MAX+1];
       size_t bytes=readlink(regularOrLinkpath,nonlink,PATH_MAX);
       if (bytes<0) { return; }
       nonlink[bytes]='\0';
       sometime(nonlink);
     } else { sometimes(regularOrLinkpath); }
   })) { return -1; }
   return 0;
}


