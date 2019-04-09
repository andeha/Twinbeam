//
//  harness.cpp
//  Running Twinbeam unit tests on a macOS machine.
//

#include <Twinbeam.h>
#include <Additions/Additions.h>

#define BUILDINFO_COPYRIGHT_MESSAGE "Copyright " PROGRESS_START_YEAR "—"   \
  PROGRESS_BUILD_YEAR " " BUILDINFO_BRAND
#define BUILDINFO_BRAND "Sublimates Experimentally 🎲"
#define PROGRESS_START_YEAR __STRING(2016)
#define PROGRESS_BUILD_YEAR __STRING(2019)

inexorable
void
printGreetings()
{
    Termlog << "\nTest harness or 𝘌𝘯𝘤𝘭𝘢𝘷𝘦 𝘤𝘰𝘭𝘭𝘦𝘤𝘵𝘪𝘰𝘯 for "
      << "Twinbeam, release " << SHA1GIT                      << eol
   /* << "Log file (\u0001F648) at: '" << TestlogPath << "'"  << eol */
      << BUILDINFO_COPYRIGHT_MESSAGE                          << sep;
    
    /* Termlog << "Give regex followed by optional list of "
      << "exclusion regexes to this command to limit scope or "
      << "flag -l to list available unit tests."
      << eol; */
}

inexorable
void
runUnitTest(
  void *addr,
  const char *symbol,
  void (^completion)(const char *symbol, uint64_t dt)
)
{
    typedef void (*Testcase)(); void (*testcase)() = (Testcase)addr;
    uint64_t startInstant = __rdtsc(); testcase();
    uint64_t dt = __rdtsc() - startInstant;
    completion(symbol, dt);
}

inexorable
void
lastChance()
{
#if _DEBUG
    Termlog << eol << "The binary is a debug build" << eol;
#else
    Termlog << eol << "The binary is a release build" << eol;
#endif
}

#pragma mark Glue and Boilerplate

extern void (^Putₒ)(char utf8);

__builtin_int_t
RunUnitTests₂(
  const char * execfilePath,
  const char32_t * regex,
  const char32_t * blacklist,
  bool doNotRun,
  int64_t * timetotal
)
{
    __block __builtin_int_t count = 0;
    
    extern void Symbols(const char * utf8exepath, void (^callback)(const
      char *, uint64_t, bool&));
    Symbols(execfilePath, ^(const char * sym, uint64_t addr, bool& stop) {
        
        if (addr && IsPrefixOrEqual((char *)sym, (char *)"_Unittest_")) {
            
            Termlog << "\nRunning " << sym << " from 0x" << (__builtin_uint_t)addr << sep;
            
            runUnitTest((void *)addr, sym, ^(const char *symbol, uint64_t dt) {
                Termlog << "\n\nEND ";
                Base(dt, 10, 0,^(char digit) { Putₒ(digit); });
                Termlog << " ns when running " << symbol << eol;
                *timetotal += dt;
            });
            
            count++;
        }
    });
    
    return count;
}

int
main(
  int argc,
  const char * argv[]
)
{
    printGreetings();
    
    int64_t nanosecs = 0;
    __builtin_int_t units = RunUnitTests₂(argv[0], U"", U"", false, &nanosecs);
    /* extern void RunUnitTests(const char * filepath, void (^output)(const char *s));
    RunUnitTests(argv[0], ^(const char *s) { printf("%s", s); }); */
    
    atexit(lastChance);
    
    Termlog << eol
      << "Unit(s): " << units << eol
      << "Total: " << nanosecs << " 𝑛s" << sep;
    
    Termlog << "'𝙰𝚞𝚝𝚘𝚖𝚊𝚝𝚎𝚍 𝚞𝚗𝚒𝚝 𝚝𝚎𝚜𝚝𝚜 𝚍𝚒𝚍 𝚗𝚘𝚝 𝚏𝚒𝚗𝚍 𝚊𝚗𝚢 𝚎𝚛𝚛𝚘𝚛𝚜' 😐 " << sep;
    
    return 0;
}
