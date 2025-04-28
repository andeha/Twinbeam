/*  harness.c | unit tests on a macintosh. */

#include "Twinbeam.h"

void greetings()
{
   print("\nTest harness for Twinbeam, release ⬚\n\n", ﹟s7(SHA1GIT));
}

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

#pragma recto glue and boilerplate

__builtin_int_t
RunTests(
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

void * heap₋allocation;

int
main(
  int argc,
  const char * argv[]
)
{ greetings();
   int64_t nanos = 0;
   __builtin_int_t units = RunTests(argv[0], U"", U"", false, &nanos);
   print("\nUnit(s): ⬚\nTotal: ⬚ ns\n\n", ﹟d(units), ﹟d(nanos));
   print("😐 Automated test did not find any errors\n");
#if defined _DEBUG
   print("\nThe binary is a debug build.\n\n");
#else
   print("\nThe binary is a release build.\n\n");
#endif
   return 0;
}


