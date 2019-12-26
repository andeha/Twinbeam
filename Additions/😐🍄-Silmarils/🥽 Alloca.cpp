/*  Alloca.cpp | Variable-length-array. (PUBLISH-GIVEN-USEFUL-UNICODE) */

#include <Twinbeam.h>
#include <Additions/Additions.h>
/* #include <Additions/Esoterics.h> */
#include <stdlib.h>

/* To compile: xcrun clang @ccargs_macᵧ² -o Alloca ../../Source/llvmʳᵗ³.cpp ../Ieee754₆₄bits.cpp '🥽 Alloca.cpp' */

int Vla(int n, void (^sometimes)(double * vals))
{
    double vals[n]; /* ⬷ Required by --<Additions.h>{Utf8ToUnicode ∧ UnicodeToUtf8}. */
    sometimes(vals);
    return 0;
}

union UQ32 { uint32_t bits; uint32_t frac; };

MACRO UQ32 FloatToUQ32(double /*double*/ x) { return UQ32 { .frac = uint32_t(2*x*2147483648.0) }; }

int Alloca(int n, void (^sometimes)(UQ32 * vals))
{
    UQ32 * vals = (UQ32 *)alloca(sizeof(UQ32)*n); double acc=1./10;
    for (int i=0; i<n; i++) {
       *(vals+i) = FloatToUQ32(acc);
       acc *= 1./10;
    }
    sometimes((UQ32 *)vals);
    return 0;
}

int
main(
  int argc, 
  const char * argv[]
)
{  int count=32;
    auto sometimes = ^(UQ32 * vals) {
       for (int i=0; i<count; i++) {
          uint32_t bits = (vals+i)->bits;
          print("⬚\n", ﹟x(__builtin_uint_t(bits)));
        }
    };
    if (Alloca(32, sometimes)) { return 0; }
    return 0;
}

