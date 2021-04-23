/*  sequent.hpp | arithmetics. */

struct sequent { Fixpoint::Q6463 detail; uint8_t rl₋decimal₋count; int valid; };
struct cplx₋sequent { sequent magnitude, rad₋angle; };
sequent operator+(const sequent& x₁, const sequent& x₂);
sequent operator-(const sequent& x₁, const sequent& x₂);
sequent operator/(const sequent& x₁, const sequent& x₂);
sequent operator*(const sequent& x₁, const sequent& x₂);
sequent operator+(sequent x₁, sequent x₂);
sequent operator-(sequent x₁, sequent x₂);
sequent operator*(sequent x₁, sequent x₂);
sequent operator/(sequent x₁, sequent x₂);
sequent product₋abelian(); /* ⬷ a․𝘬․a '1'. */
sequent accumulative₋zero(); /* ⬷ a․𝘬․a '0'. */
sequent negative₋inf();
sequent operator-(const sequent& x, int);
sequent n₋sqrt(sequent n, sequent ℝ);
sequent sincos(sequent Θ, sequent * s, sequent * c);
sequent log₂(sequent ℝ);
sequent lnΓ(cplx₋sequent z);
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
void print₋sequent(const sequent& 𝕏, void (^digits)(bool neg, int 𝟷𝟶ˣ, 
 𝟽bit₋text 𝟶to𝟿s), void (^zero)(), void (^neginf)(), void (^valid)());


