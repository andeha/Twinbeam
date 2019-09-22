/*  ¹²⁸int.cpp | At least once thought as %I and %U. */

#include <Twinbeam.h>

/*
 
 Compile with:
 
 alias mips-cc='../../../../mips-tools/8.0.0/clang-8'
 alias mips-ld='../../../../mips-tools/8.0.0/ld.lld'
 mips-cc @ccargs_mzsim -o ¹²⁸int.o -c '🥽 ¹²⁸int.cpp'
 mips-ld -T ../../pic32rt/pic32.ld -o ¹²⁸int_pic32mzda ¹²⁸int.o
 
 and theoretically:
 
 xcrun clang @ccargs_macosᵧ -o ¹²⁸int_mojave '🥽 ¹²⁸int.cpp'    \
   ../../Source/llvmʳᵗ³.cpp
 
 versus in practice:
 
 xcrun clang @ccargs_macᵧ² -o ¹²⁸int_mojave '🥽 ¹²⁸int.cpp'    \
   ../../Source/llvmʳᵗ³.cpp
 
 */

int
main(
  int argc,
  const char * argv[]
)
{
    __uint128_t x₁ =  0x1234; __int128_t x₂ = -100;
    print("Size of x₁ is ⬚ value is 0x⬚\n", ﹟d(sizeof(x₁)), ﹟U(x₁));
    print("Size of x₂ is ⬚ value is ⬚\n", ﹟d(sizeof(x₂)), ﹟I(x₂));
    return 0;
}