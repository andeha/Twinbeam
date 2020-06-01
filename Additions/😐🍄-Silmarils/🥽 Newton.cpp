/*  Newton.cpp | ∂ - Finding root approximations with an analytically and/ 
  or numerically interest in 'change'.  (EXERCISE-CAREFULLY.) */

#include <Twinbeam.h>
#include <Additions/Additions.h>

/*  Compile with xcrun clang @ccargs_macᵧ² -o Newton '🥽 Newton.cpp' */

typedef double (^Computational)(double x);

enum class Newtoncontrol { ok, done, abort };

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
} /* Since y = f'(xᵢ)(x - xᵢ) + f(xᵢ) */

double Power(double S, __builtin_int_t N) { if (N<+0.0) { return 1/Power(S,-N); } 
  else { return N==0 ? 1 : N*Power(S,N-1); } }

extern double ℝ₋root(/* __builting_int_t r, */ double x); /* ⬷ A․k․a ʳ√x */
extern double log₂(double x); /* ⬷ Simpler to compute, therefore 'computer'. */
extern double reciproc(double x) Si_FOCAL;
extern double generic₋ℝ₋root(int count, double xᵣ[], complex λᵣ[]);
/* ⬷ A․k․a c_{n}*xⁿ + c_{n-1} * xⁿ⁻¹ + ... + c_0 == 0.  Number of solutions are $n-1$. When 
 odd degree at least one real root. Returns even and odd complex . Analytical solution when 
 up to a degree four. */

/*
 
 Also: double log₃(double x) { double 🥈 ... } 
 
 𝘊․𝘧 0*3^0=1, 0*3^1, 1*3^2, 2*3^3. ⬷ Linear-combine.
 
 */

#pragma mark - O(log n): with √x = √2 * √(x/2) and logᵣ x = logᵣ2 + logᵣ(x/2)

/*
 
 First spatial damping, 𝘪․𝘦 solving: xᵇ = s 𝘦․𝘨 x² = s ⟷ x² - S = 0
 
 */

double ℝ₋root(/* __builting_int_t r, */ double x)
{
   auto ℝ₋root₋fine = ^(/* __builtin_int_t r, */ double ϵ) /* -> double */
   {  𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=ϵ; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10; /* ⬷ todo: Analyze integer. */
       Computational f = ^(double x) { return x*x - ϵ; }, /* In the general case: 'Power(n,x) - ϵ'. */
         f₋prime = ^(double x) { return 2*x; /* In the general case: 'n*x^(n-1)'. */ };
       if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) { 
         print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀));
         if (!step--) { ctrl=Newtoncontrol::done; }
       })) { print("aborted\n"); } else { print("Solution is ⬚\n", ﹟F(x₀)); }
       return x₀;
   }; /*  Equal sides given a squared area S. */
   
   auto ℝ₋root₋coarse = ^(/* __builtin_int_t r, */ double S, __builtin_int_t * 𝗇th₋root, double * modula) /* -> int */
   {
      if (x == -0.0) { *modula=-0.0; *𝗇th₋root=0; return 0; }
      if (x < +0.0) { *modula = octa { .bits=IEEE754BASE2_64BIT_SNAN₂ }.base₂; *𝗇th₋root=0; return -1; }
      *𝗇th₋root=0; double epsilon=S; while (epsilon > 4.0) { epsilon /= 2; *𝗇th₋root += 1; }
      *modula = ℝ₋root₋fine(/* __builtin_int_t r, */ epsilon); return 0;
   };
   
   __builtin_int_t 𝗇th₋root; double modula;
   /* int ok = */ ℝ₋root₋coarse(/* __builtin_int_t r, */ x, &𝗇th₋root, &modula);
   double 🥈 ²root𝟸=1.414213562373095, ³root𝟸=1.259921049894873;
   return Power(²root𝟸,𝗇th₋root)*modula;
}

/*  Also algebraic: ⁿ√(x₁/x₂) = ⁿ√x₁ / ⁿ√x₂ (...applying 'nth-root' on a quotient.) */

/*
  
  ...and now a second 'type of damping': the logarithm.
  
 */

double log₂(double x)
{
   auto ᵋlog₂ = ^(double S) /* -> double ⬷ thread relative 'constraints' on: S > 0. */
   {  𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=S; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10; double 🥈 ln₍2₎=0.693147180559945; 
       typedef __builtin_int_t (^P)(__builtin_int_t n);
       P 𝟸ⁿ = ^(__builtin_int_t n) { return n==0 ? 1 : 2*𝟸ⁿ(n-1); };
       Computational f = ^(double x) { return 𝟸ⁿ(x) - S; }, /* todo: write log₂ for `double` instead. */
         f₋prime = ^(double x) { return ln₍2₎ * 1/x; }; /* todo: Investigate periodicity of `log`. */
       if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) { /* f(x) = k*ln x -> f'(x) = k*1/x */
         print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀));
         if (!step--) { ctrl=Newtoncontrol::done; }
       })) { print("aborted\n"); } else { print("Solution is ⬚\n", ﹟F(x₀)); }
       return x₀;
   }; /* Solving 2ˣ = s ⟷ x - log₂(s) = 0.0. 𝘊․𝘧 `log₃` and `logₑ`. */
   
   auto log₂ = ^(double S, __builtin_int_t * log₂₍𝟸₎₋count, double * modula) /* -> int */
   {
      if (S == -0.0) { *modula=-0.0; *log₂₍𝟸₎₋count=0; return 0; }
      if (S < +0.0) { *modula = octa { .bits=IEEE754BASE2_64BIT_SNAN₂ }.base₂; *log₂₍𝟸₎₋count=0; return -1; }
      *log₂₍𝟸₎₋count=0; double epsilon=S; while (epsilon > 4.0) { epsilon /= 2; *log₂₍𝟸₎₋count += 1; }
      *modula = ᵋlog₂(epsilon); return 0;
   };
   
   double 🥈 log₂₍𝟸₎=1.0; /* ...'the canonical 2' = log_e(2)/log_e(2). */
   __builtin_int_t log₂₍𝟸₎₋count; double modula;
   /* int ok = */ log₂(x,&log₂₍𝟸₎₋count,&modula);
   return log₂₍𝟸₎*log₂₍𝟸₎₋count + modula;
}

double logₑ(double x) { double 🥈 log₂₍e₎=1.442695040888963; return log₂(x)/log₂₍e₎; } /* ⬷ Temporal generalization adequate. */
double logₑ(double x) { double 🥈 logₑ₍𝟸₎=0.693147180559945; return logₑ₍𝟸₎*log₂(x); } /* ⬷ Requires structural generalization. */
double log₁₀(double x) { double 🥈 log₂₍𝟷𝟶₎=3.321928094887362; return log₂(x)/log₂₍𝟷𝟶₎; } /* ⬷ Relying on temporal generalization. */

/*
 
 Finding a reciprocal value: 1/x = S ⟷ 1/x - S = 0 ⟷ 1 - xS = 0
 
 */

double reciproc(double S)
{  𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 double x₀=S; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 int step=10;
   Computational f = ^(double x) { return 1.0 - x*S; /* ...and not '1/x' 𝘢․𝘬․𝘢 'x⁻¹'. */ }, 
     f₋prime = ^(double x) { return -S; /* ...and not -x⁻². */ }; /* ⬷ Note optionally circular! Neither temporal nor structural, possibly yet costly to find. */
   if (Newton(f, f₋prime, &x₀, ^(Newtoncontrol &ctrl) {
     print("Iter ⬚: ⬚\n", ﹟d(step), ﹟F(x₀));
     if (!step--) { ctrl=Newtoncontrol::done; }
   })) { print("aborted\n"); } else { print("Solution is ⬚\n", ﹟F(x₀)); }
   return x₀;
} /* See also 'Herons rule' to avoid circularity illustrated in this exercise. */

int
main(
  int argc,
  const char * argv[]
)
{
   print("√2 = ⬚\n", ﹟F(ℝ₋root(2.0)));
   print("log₁₀ 1/8 = ⬚\n", ﹟F(log₂(1.0/8.0))); /* ☜😐🎧: ♫ */
   print("reciproc 16.0 = ⬚\n", ﹟F(reciproc(16.0)));
   return 0;
}

/* The inverse square root function 1/√x is often used in computer graphics such as shading. */

/* ln(e^(5*12)) = e^(ln(5*12)) = 5*12 */

/* --<🥽 Napier.cpp> | Five dozen eggs and a visit to town. */


