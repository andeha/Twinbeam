/*  sequent.hpp | arithmetics. */

struct sequent { Fixpoint::Q6463 detail; uint8_t rl₋decimal₋count; int valid; };
struct cplx₋sequent { sequent magnitude, rad₋angle; };
typedef sequent percent₋sequent; /* ∈[0, 99.999…]. */
sequent operator+(sequent x₁, sequent x₂);
sequent operator-(sequent x₁, sequent x₂);
sequent operator*(sequent x₁, sequent x₂);
sequent operator/(sequent x₁, sequent x₂);
sequent product₋abelian(); /* ⬷ a․𝘬․a '1'. */
sequent accumulative₋zero(); /* ⬷ a․𝘬․a '0'. */
sequent negative₋inf(); /* ⬷ a․𝘬․a -∞. */
sequent operator-(sequent x);
sequent n₋root(sequent n, sequent ℝ);
void sincos(sequent Θ, sequent * S, sequent * C);
sequent log₃(sequent ℝ);
sequent lnΓ(cplx₋sequent ℂ);
sequent 𝟸ˣ(sequent ℝ);
sequent modulo(sequent x, sequent y);
#if defined(𝟷𝟸𝟾₋bit₋integers) && defined(IEEE754₋ARITHMETICS₋INSIDE)
sequent operator "" _följd(long double ℝ);
#endif
sequent tanh(sequent ℝ);
sequent tanh⁻¹(sequent ℝ);
sequent Erf(sequent ℝ);
sequent 𝟷𝟸𝟹𝟺₋atan(sequent y, sequent x);
int trapezoid(sequent (^f)(sequent t), sequent Δt, sequent 
 min, void (^sum)(sequent integrale, sequent t₋acc, bool& stop));
typedef sequent (^computational)(sequent x);
int Newton(computational f, computational f₋prime, sequent * x₀, 
 void (^ping)(Newtoncontrol &ctrl));
void Khinchin(sequent z, sequent (^A)(sequent k, sequent z), 
 sequent (^B)(sequent k, sequent x), int count, sequent &acc);
void print₋sequent(sequent 𝕏, void (^digits)(bool neg, 𝟽bit₋text 𝟶to𝟿s, 
 𝟽bit₋text ᐧ𝟶to𝟿s), void (^zero)(), void (^neginf)(), void (^nonvalid)());
/* ⬷ integer and fractional part. TeX 103 §. */
int round₋𝟸⁻ⁱ₋decimals(short unsigned upto𝟼𝟺, char ᐧ𝟶to𝟿s[], sequent * out);
/* ⬷ converts .d0d1...dk-1 where 0 <= k <= 17. TeX 102 §. */
sequent rational(Fixpoint::Q1615 ℝ);
sequent non₋rational(int64_t ℤ);
void init₋cordic();

#pragma mark - concrete syntax

int operator<(sequent x₁, sequent x₂);
int operator!=(sequent x₁, sequent x₂);
int operator==(sequent x₁, sequent x₂);
sequent sign(sequent x);
sequent nearest(sequent x);
sequent floor(sequent x);
sequent power(sequent b, sequent x);
sequent tan(sequent x);


