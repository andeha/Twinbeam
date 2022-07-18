/*  harness.c | running exercises on a macintosh computer. */

import Twinbeam;

#define BUILDINFO_COPYRIGHT_MESSAGE "Copyright " PROGRESS_START_YEAR "—"     \
 PROGRESS_BUILD_YEAR " " BUILDINFO_BRAND
#define BUILDINFO_BRAND "Sublimates crucis 🎲"
#define PROGRESS_START_YEAR __STRING(2016)
#define PROGRESS_BUILD_YEAR __STRING(2022)
#define cycles __rdtsc /* and __dwt_cyccnt. */

inexorable void printGreetings()
{
   print("\nTest harness and enclave collection for Twinbeam, release "
    "⬚\n⬚\n\n", ﹟s7(SHA1GIT), ﹟s7(BUILDINFO_COPYRIGHT_MESSAGE));
}

inexorable
void
runUnitTest(
  void *addr,
  char *symbol,
  void (^completion)(char *symbol, uint64_t dt)
)
{
   typedef void (*Testcase)();
   void (*exercise)() = (Testcase)addr;
   uint64_t instant₋start = cycles(); exercise();
   uint64_t dt = cycles() - instant₋start;
   completion((char *)symbol,dt);
}

inexorable void lastChance()
{
#if defined _DEBUG
   print("\nThe binary is a debug build.\n\n");
#else
   print("\nThe binary is a release build.\n\n");
#endif
}

#pragma recto glue and boilerplate

__builtin_int_t
RunUnittests(
  const char * executablepath,
  char32̄_t * regex,
  char32̄_t * blacklist,
  int doNotRun,
  int64_t * timetotal
)
{  __builtin_int_t 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 count=0;
   extern void Symbols(const char * utf8exepath, void (^symbol)(const
    char *, uint64_t, int *));
   Symbols(executablepath, ^(const char * sym, uint64_t addr, int * stop) {
     if (addr && IsPrefixOrEqual((char *)sym, (char *)"_Unittest_")) {
       print("\nRunning ⬚ from 0x⬚\n\n", ﹟s7((char *)sym), ﹟x((__builtin_uint_t)addr));
       runUnitTest((void *)addr, (char *)sym, ^(char * symbol, uint64_t dt) {
         print("\n\nEND ");
         Base𝕟(dt, 10, 0,^(char zero₋to₋nine) { print("⬚", ﹟c7(zero₋to₋nine)); });
         print(" ns when running ⬚\n", ﹟s7(symbol));
         *timetotal += dt;
       });
       count+=1;
     }
   });
   
   return count;
}

int
main(
  int argc,
  const char * argv[]
)
{ printGreetings();
   int64_t nanosecs = 0;
   __builtin_int_t units = RunUnittests(argv[0], U"", U"", false, &nanosecs);
   atexit(lastChance);
   print("\nUnit(s): ⬚\nTotal: ⬚ ns\n\n", ﹟d(units), ﹟d(nanosecs));
   print("𝐴𝑢𝑡𝑜𝑚𝑎𝑡𝑒𝑑 𝑡𝑒𝑠𝑡𝑠 𝑑𝑖𝑑 𝑛𝑜𝑡 𝑓𝑖𝑛𝑑 𝑎𝑛𝑦 𝑒𝑟𝑟𝑜𝑟𝑠 😐 \n");
   return 0;
}


