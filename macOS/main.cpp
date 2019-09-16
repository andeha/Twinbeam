/*  Harness.cpp | Running unit tests on a macOS machine. */

#include <Twinbeam.h>

#define BUILDINFO_COPYRIGHT_MESSAGE "Copyright " PROGRESS_START_YEAR "—"  \
  PROGRESS_BUILD_YEAR " " BUILDINFO_BRAND
#define BUILDINFO_BRAND "Sublimates Experimentally 🎲"
#define PROGRESS_START_YEAR __STRING(2016)
#define PROGRESS_BUILD_YEAR __STRING(2019)

inexorable
void
printGreetings()
{
    print("\nTest harness and Enclave collection for Twinbeam, release "
      "⬚\n⬚\n\n", ﹟s(SHA1GIT), ﹟s(BUILDINFO_COPYRIGHT_MESSAGE));
   /* << "Log file (\u0001F648) at: '" << TestlogPath << "'"  << eol */
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
    print("\nThe binary is a debug build.\n\n");
#else
    print("\nThe binary is a release build.\n\n");
#endif
}

#pragma mark Glue and Boilerplate

__builtin_int_t
RunUnitTests(
  const char * execfilePath,
  const char32_t * regex,
  const char32_t * blacklist,
  bool doNotRun,
  int64_t * timetotal
)
{
    __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 count = 0;
    
    extern void Symbols(const char * utf8exepath, void (^callback)(const
      char *, uint64_t, bool&));
    Symbols(execfilePath, ^(const char * sym, uint64_t addr, bool& stop) {
        
        if (addr && IsPrefixOrEqual((char *)sym, (char *)"_Unittest_")) {
            
            print("\nRunning ⬚ from 0x⬚\n\n", ﹟s(sym), ﹟x((__builtin_uint_t)addr));
            
            runUnitTest((void *)addr, sym, ^(const char * symbol, uint64_t dt) {
                print("\n\nEND ");
                Base𝕟(dt, 10, 0,^(char 𝟶to𝟿) { print("⬚", ﹟c(𝟶to𝟿)); });
                print(" ns when running ⬚\n", ﹟s(symbol));
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
    __builtin_int_t units = RunUnitTests(argv[0], U"", U"", false, &nanosecs);
    
    atexit(lastChance);
    
    print("\nUnit(s): ⬚\nTotal: ⬚ ns\n\n", ﹟d(units), ﹟d(nanosecs));
    
    print("𝐴𝑢𝑡𝑜𝑚𝑎𝑡𝑒𝑑 𝑡𝑒𝑠𝑡𝑠 𝑑𝑖𝑑 𝑛𝑜𝑡 𝑓𝑖𝑛𝑑 𝑎𝑛𝑦 𝑒𝑟𝑟𝑜𝑟𝑠 😐 \n");
    
    return 0;
}

