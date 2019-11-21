/*  Intervallic.cpp | When signals and console is accounted for. */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/*
 
 xcrun clang @ccargs_macᵧ² -o Intervallic ../../Source/llvmʳᵗ³.cpp         \
    '🥽 Intervallic.cpp'
 
 */

auto pad = ^(char32_t uc, int times) { for (int i=0; i<times; i++) print("⬚",﹟C(uc)); };

int
Format(Ieee754Form f, 
  void (^firstUnit)(int 𝟷𝟶ⁱ, int maxlen), 
  void (^out)(int idx, char32_t uc), 
  void (^next)(bool& stop), 
  int count, ... /* doubles' X */
)
{
    /* Two passes: 1) Find magnitude and maxwidth; and 2) output 𝒆𝒂𝒄𝒉 
      floating point. */ int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 maxlen=0; bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 stop=false;
    int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 𝟷𝟶ⁱ=0; /* 2ⁱ ≈ 10^(i*log₁₀2) */
    auto length = ^(double ℝ) { int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 maxlen₂=0;
      Format(ℝ, f, ^(char32_t uc) { maxlen₂++; });
      return maxlen₂; };
    va_prologue(count);
    for (int i=0; i<count; i++) {
      double ℝ = __builtin_va_arg(__arg, double);
      int len = length(ℝ);
      maxlen = max(len,maxlen);
    }
    firstUnit(𝟷𝟶ⁱ,maxlen);
    __builtin_va_start(__arg, count);
    for (int i=0; i<count; i++) { 
      double ℝ = __builtin_va_arg(__arg, double);
      int len = length(ℝ);
      pad(U' ', maxlen-len);
      Format(ℝ, f, ^(char32_t uc) { out(i,uc); /* if (stop) { return 1; } */ });
      next(stop); if (stop) { return 1; }
    }
    va_epilogue
    return 0;
}

int
main(
  int argc,
  const char * argv[]
)
{
    print("Printing the Italian account:\n"); int 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 max=0; bool 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 odd=true;
    auto firstUnit = ^(int 𝟷𝟶ⁱ, int maxlen) { max=maxlen; print("Unit: 10⬚\n", 
      ﹟C(Superscript(𝟷𝟶ⁱ))); int col=maxlen+1; pad(U' ', col); print("|"); 
      pad(U' ', col); print("\n"); pad(U'-', 1+2*col); print("\n"); };
    auto out = ^(int idx, char32_t uc) { print("⬚", ﹟C(uc)); };
    auto next = ^(bool& stop) { if (odd) { print(" | "); } else { print("\n"); } odd=!odd; };
    double vals[] = { 1.2, 2.2, 3.2, 4.2, 5.1, 6.1, 7.1, 8.1, 9.1, 10.01 };
    Format(Ieee754Form::Scientific, firstUnit, out, next, 10, vals);
    print("...and also:\n"); 
    Format(Ieee754Form::Monetary, firstUnit, out, next, 10, vals);
    return 0;
}


