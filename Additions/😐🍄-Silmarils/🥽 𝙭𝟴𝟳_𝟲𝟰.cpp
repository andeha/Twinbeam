/*  𝙭𝟴𝟳_𝟲𝟰.cpp | Reverse-polish notation in 𝙃𝙒. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/* Compile with:
  
  xcrun clang @ccargs_macosᵧ -fms-extensions -o x87_64                   \
    ../../Source/llvmʳᵗ³.cpp '🥽 𝙭𝟴𝟳_𝟲𝟰.cpp'
  
  and
  
  ~/Projects/mips-tools/8.0.0/clang-8 @ccargs_mz -o x87_64_mips -c '🥽 𝙭𝟴𝟳_𝟲𝟰.cpp'
  
 */

double sqrt(double x)
{
#ifdef  __mips__
    double x₂=x;
    double y;
#elif defined __x86_64__
    double y;
    asm {
       FLD   x
       FSQRT
       FSTP  y
    };
#endif
    return y;
}

double arithmetic(double x₁, double x₂)
{
#ifdef  __mips__
    /* See --<🥽 Report⁹.cpp> for details. */
    return 0;
#elif defined __x86_64__
    double two = 2.0;
    double y;
    asm {
       FLD   x₁
       FLD   x₂
       FADD
       FLD two /* ⬷ Unable to `𝟸`. */
       FDIV
       FSTP  y
    };
    return y;
#endif
}

#ifdef __x86_64__
#include <stdio.h>
extern "C" ssize_t write(int fd, const void *s, size_t b); /* ⬷ Signed `size_t`. */
DISORDERABLE auto Putₒ = ^(uint8_t * utf8s, uint16_t bytes) {
  write(1, (const void *)utf8s, bytes); };
#include <wchar.h>
#elif defined __mips__
#include <pic32rt/mips.hpp>
#include <pic32rt/pic32mz.hpp>
#include <pic32rt/pic32mzda.hpp>
#include <pic32rt/stable.hpp>
auto Putₒ = ^(uint8_t * utf8s, uint16_t bytes) {
  for (int i = 0; i < bytes; i++) putch(*(utf8s+i)); };
#endif

int
main(
  int argc,
  const char * argv[]
)
{
    double s = sqrt(3.0);
    /* printf("Sqrt is %f\n", s); */
    print("Sqrt is ⬚\n", ﹟d(s));
    double y₃ = arithmetic(1.2, 5.5);
    /* printf("arithmetic is %f\n", y₃); */
    print("Arithmetic is ⬚\n", ﹟d(y₃));
    return 0;
}


