/*  sqrt-simd-0.cpp | two variants computing sqrt. (DO-NOT-DISTRIBUTE.) */

#include <Twinbeam.h>
#include <Additions/Additions.h>

double sqrtᵥ1(double ℝ)
{
   if (ℝ <= -0.0) { return __builtin_qnan(); }
   double prev=__builtin_qnan(), half=ℝ/2, both;
again:
   both = half*half;
   if (abs(prev - both) < 1e-20) { return prev; }
   prev = both;
   if (both > ℝ) { half = half/2; }
   else if (both < ℝ) { half = half + half/2; }
   goto again;
}

#pragma mark - three examples on Newton iteration below:

/* Evaluating 𝘦․𝘨 the example sqrt(x) by observing x² = ℝ ⟷ x² - ℝ = 0. */
double n₋sqrtᵥ₂(double ℝ, double n)
{
   if (ℝ <= -0.0) { return __builtin_qnan(); }
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=ℝ; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10; /* ⬷ todo: analyze ﹟-steps. */
   Computational f = ^(double x) { return substandard₋pow(x,n) - ℝ; }, /* ⬷ 𝘦․𝘨 x*x - ℝ, in the general case: 'Power(n,x) - ℝ'. */
    f₋prime = ^(double x) { return n*substandard₋pow(x,n-1); /* ⬷ 𝘦․𝘨 2*x, in the general case: 'n*x^(n-1)'. */ };
   if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) {
     /* print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀)); */
     if (!step--) { ctrl=Newtoncontrol::done; }
   })) { /* print("aborted\n"); */ } else { /* print("Solution is ⬚\n", ﹟F(x₀)); */ }
   return x₀;
} /* ⬷ equal sides given a squared area S. */

/* and here evaluating 𝘦․𝘨 the example ln(x) by iterating 2ˣ = ℝ ⟷ 2ˣ - ℝ = 0. */
double log₂ᵥ1(double ℝ)
{
   if (ℝ <= -0.0) { return __builtin_qnan(); }
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=ℝ; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10; /* ⬷ todo: analyze ﹟-steps. */
   Computational f = ^(double x) { return substandard₋pow(2,x) - ℝ; }, /* ⬷ 𝘦․𝘨 2ˣ - ℝ */
     f₋prime = ^(double x) { return x*substandard₋pow(2,x-1); /* ⬷ 𝘦․𝘨 x*2ˣ⁻¹ */ };
   if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) {
     /* print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀)); */
     if (!step--) { ctrl=Newtoncontrol::done; }
   })) { /* print("aborted\n"); */ } else { /* print("Solution is ⬚\n", ﹟F(x₀)); */ }
   return x₀;
} /* ⬷ a․𝘬․a __builtin_msa_flog2_d. */

/* and now evaluating 𝘦․𝘨 the example wd = ws*2ᵚᵗ a․𝘬․a x₁*2ˣ² = ℝ ⟷ x₁*2ˣ² - ℝ = 0. */
double exp2ᵥ₁(double ℝ, int ℤ)
{
   if (ℤ == 0) { return ℝ; }
   if (ℝ <= -0.0) { return __builtin_qnan(); }
   𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=ℝ; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10; /* ⬷ todo: analyze ﹟-steps. */
   Computational f = ^(double x) { return ℝ*substandard₋pow(2,double(ℤ)) - x₀; }, /* ⬷ 𝘦․𝘨 x₁*2ˣ² - ℝ */
     f₋prime = ^(double x) { return x*substandard₋pow(2,x-1); /* ⬷ 𝘦․𝘨 x*2ˣ⁻¹ */ };
   if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) {
     /* print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀)); */
     if (!step--) { ctrl=Newtoncontrol::done; }
   })) { /* print("aborted\n"); */ } else { /* print("Solution is ⬚\n", ﹟F(x₀)); */ }
   return x₀;
} /* ⬷ a․𝘬․a intel_fexp2_pd and __builtin_msa_fexp2_d. */

/* later: also recursive Newtons and the const-expressive Newton machine. */

#pragma mark - a versatile analog Si-Newton solver also for logₑ, log₁₀, 'reciproc' and other functions

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

/* note that a generic Newton solver for simdᵦ often does not simultaneously converge. */

