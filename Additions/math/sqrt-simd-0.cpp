/*  sqrt-simd-0.cpp | two variants computing sqrt. (DO-NOT-DISTRIBUTE.) */

#include <Twinbeam.h>
#include <Additions/Additions.h>

double sqrtᵥ1(double ℕ)
{
   if (ℕ <= -0.0) { return __builtin_qnan(); }
   double prev=__builtin_qnan(), half=ℕ/2, both;
again:
   both = half*half;
   if (abs(prev - both) < 1e-20) { return prev; }
   prev = both;
   if (both > ℕ) { half = half/2; }
   else if (both < ℕ) { half = half + half/2; }
   goto again;
}

/* E.g sqrt(x) is solving x² = s ⟷ x² - S = 0 */
double n₋sqrtᵥ₂(double ϵ, double n)
{
   if (ϵ <= -0.0) { return __builtin_qnan(); }
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=ϵ; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10; /* ⬷ todo: Analyze integer. */
   Computational f = ^(double x) { return substandard₋pow(x,n) - ϵ; }, /* e.g x*x - ϵ, in the general case: 'Power(n,x) - ϵ'. */
    f₋prime = ^(double x) { return n*substandard₋pow(x,n-1); /* e.g 2*x, in the general case: 'n*x^(n-1)'. */ };
   if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) { 
     /* print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀)); */
     if (!step--) { ctrl=Newtoncontrol::done; }
   })) { /* print("aborted\n"); */ } else { /* print("Solution is ⬚\n", ﹟F(x₀)); */ }
   return x₀;
} /* ⬷ equal sides given a squared area S. */

#pragma mark - Newton solver for log₂, logₑ, log₁₀, reciproc and other functions

int
Newton(
  Computational f, Computational f₋prime, 
  double * x₀, 
  void (^ping)(Newtoncontrol &ctrl)
)
{  Newtoncontrol ctrl=Newtoncontrol::ok;
again:
    *x₀ -= f(*x₀)/f₋prime(*x₀); /* xᵢ₊₁ = xᵢ - f(xᵢ)/f'(x) */
    ping(ctrl);
    switch (ctrl) {
     case Newtoncontrol::done: return 0;
     case Newtoncontrol::abort: return 1;
     case Newtoncontrol::ok: return 0;
    }
    goto again;
} /* ⬷ since y = f'(xᵢ)(x - xᵢ) + f(xᵢ) */

/* note that a generic Newton solver for simdᵦ does not neccessary converge simultaneously. */

