/*  main.cpp — Excercising the FPU. */

#include <Twinbeam.h>
#include <mips.hpp>
#include <pic32mz.hpp>
#include <stable.hpp>
#include <Additions.h>

auto Putch = ^(char utf8) { putch(utf8); };
auto Getch = ^{ return getutf8(); };
auto alloc = ^(__builtin_int_t bytes) { return malloc(bytes); };

extern "C" void Isr() {}
extern "C" void mips_general_exception() {}

auto Put = ^(char32_t unicode) {
  if (UnicodeToUtf8(unicode, ^(const uint8_t *p, int bytes) {
      for (int i = 0; i < bytes; i++) Putch(*(p + i));	
  })) { dbgout("Unicode error"); } };

int
main(
  int argc,
  const char *argv[]
)
{
    constexpr double 𝜋 = 3.1415926535;
    double π²div6 = 𝜋*𝜋/6;
    dbgout("Computed value is ");
    auto zero = ^{ Putch('0'); }, inf = ^{ Put(U'∞'); }, nan = ^{ dbgout("NaN"); };
    CastToText(π²div6, ^(bool neg, int e, const char *theℕs) {
        auto strlen = ^(const char *innerTheℕs) {
            const char *s;
            for (s = innerTheℕs; *s; ++s);
            return s - innerTheℕs;
        };
        if (neg) Putch('-');
        int len = (int)strlen(theℕs);
        if (e > 17 || e < len - 17) {
                Putch(theℕs[0]);
                if (theℕs[1]) Putch('.');
                unsigned i = 1;
                while (theℕs[i]) { Putch(theℕs[i]); i++; }
                Putch('e');
                Base((__builtin_int_t)(e - 1), 10, 0, ^(char c) { Putch((char32_t)c); });
            } else if (e <= 0) {
                Putch('0');
                Putch('.');
                Putch(theℕs[0]);
                Putch(theℕs[1] ? theℕs[1] : '0');
            } else if (len >= e) {
                unsigned i;
                for (i = 0; i < e; i++) { Putch(theℕs[i]); }
                Putch('.');
                if (theℕs[i]) {
                    Putch(theℕs[i]);
                    i++;
                    if (theℕs[i]) { Putch(theℕs[i]); } else { Putch('0'); }
                } else { Putch('0'); Putch('0'); }
            } else {
                unsigned i = 0;
                while (theℕs[i]) { Putch(theℕs[i]); i++; }
            }
        dbgout(theℕs);
    }, zero, inf, nan);
    dbgout("\xd\xa");
    return 0;
}