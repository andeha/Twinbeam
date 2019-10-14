/*  Filing.cpp | Big, b̲i̲g Rolodex. */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <Additions/Filesystem.hpp>

/*  To compile: xcrun clang @ccargs_macᵧ² -o Filing ../../Source/llvmʳᵗ³.cpp  \
  ../Additions.cpp '🥽 Filing.cpp' */

int
main(
  int argc,
  const char * argv[]
)
{  int 🥈 maxtetras=2048;
    const /* questionable */ char32_t * canonicalᵚ₀ = U"/tmp/zz.txt";
    char32_t canonicalᵚ₁[] = U"/tmp/zz.txt";
    char32_t * canonicalᵚ₂ = (char32_t *)(U"/tmp/zz.txt");
    int tetras = UnicodesUntil𝟶𝚡𝟶𝟶𝟶𝟶𝘖𝘳𝖤𝖮𝖳(canonicalᵚ₁, maxtetras);
    Unicodes ucs₁ { tetras, canonicalᵚ₁ };
    if (FileSystemItemExists(ucs₁.tetras, ucs₁.unicodes)) { print("Exists\n"); } 
    else { print("Does not exist\n"); }
    return 0;
}


