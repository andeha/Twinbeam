/*  type-unset.h | well-set auditions of two-and-control and separate-channels-and-control. */

typedef uint32_t TypefaceAnatomy;

BITMASK(Typecase₋TypefaceAnatomy) {
  Bold        = 0b000000000000000000000000001,
  Italic      = 0b000000000000000000000000010,
  Slant       = 0b000000000000000000000000100,
  SansSerif   = 0b000000000000000000000001000,
  Monospace   = 0b000000000000000000000010000,
  Number      = 0b000000000000000000000100000, /* complementary set of numbers. */
  Stillistic  = 0b000000000000000000001000000, /* a․𝘬․a script or calligraphy. */
  Blackletter = 0b000000000000000000010000000, /* early typeface 𝘦․𝘨 fraktur. */
  Greek       = 0b000000000000000001000000000,
  Symbolic    = 0b000000000000000010000000000, /* non-character. */
  Cultural    = 0b000000000000000100000000000, /* Emojs. */
  Musical     = 0b000000000000001000000000000,
  Ornamental  = 0b000000000000010000000000000, /* often used in unison with other ornamentals. */
  Mathdisplay = 0b000000000000100000000000000,
  Display     = 0b000000000001000000000000000, /* math and/or ≅30 pt or larger. */
  Smallprint  = 0b000000000010000000000000000, /* math and/or ≅30 pt or larger. */
  Demo        = 0b000000000100000000000000000, /* for pangram and samples. */
  Combining   = 0b000000001000000000000000000,
  Mergable    = 0b000000010000000000000000000,
  Bundable    = 0b000000100000000000000000000, /* can be included in for instance a file. */
  Overlay     = 0b000001000000000000000000000,
  Revcontrast = 0b000010000000000000000000000, /* reverse contrast. (Horizontal lines are the thicker than verical.) */
  Effect      = 0b111100000000000000000000000  /* interior of glyph in background 𝘦․𝘨 inline, block, outline or shadow. */
};

typedef double Fontsize;

struct TypedExpression {
  TypefaceAnatomy anatomy;
  Fontsize pointsAndQNan;
  sevenbit₋text skufaceAndEpsilon;
  Color colorAndEpsilonedName;
}; /* create two instances 'default' and 'current-after-modification'. */

#define typedIn(anatomy) TypedExpression { anatomy, Opt<Fontsize>::no(), Opt<const char *>::no(), Opt<Color>::no() }

struct Ornaments; /* list with line-no, col-no and idx in utf8 and unicode. */

int Composingstick₋compose₁(char8₋t * temp₋u8s, TypedExpression expr, 
 void * first, void * last, Ornaments * run);

int Composingstick₋compose₂(char32̄_t * temp₋ucs, TypedExpression expr, 
 void * additive, void * subtractive, Ornaments * run);

typedef UnicodeIntervalAnd𝑂rLocation Intervallic;

Intervallic Composingstick₋mergeWith(Intervallic applicant, int temporary, Unicodes * fold, 
 TypedExpression expr);

TypedExpression Composingstick₋probe(Utf8Symbol here, int temporary, Unicodes * text);

TypedExpression Composingstick₋probe(Intervallic here, int temporary, Unicodes * text);

Intervallic Composingstick₋updateTo(Intervallic current, int temporary, Unicodes * amorphic, 
 TypedExpression expr);

Intervallic Composingstick₋clear(Intervallic subtractive, int temporary, Unicodes * amorphic);

/* 'Virtual Manhattan and physical Manhattan later' /‌/ ☜😐📖 */
MACRO Intervallic Composingstick₋clear(Intervallic substractive, Directions::Cross reading₋mass, 
  int temporary, Unicodes * amorphic) { /* 😐😐: >  ✜𒀽 ⏱🏁 */
    return UnicodeIntervalAnd𝑂rLocation { }; }

#pragma recto from bezier-oil.c

fostrat₋defi { simd_tᵦ z₁,z₂,z₃,z₄ } Bezier;

fostrat₋defi { simd_tᵦ p₋₁,xy₋p,cromin₋and₋lumin; } Bezier₋rendition;

EXT₋C int Render(doubleʳ t, Bezier C, Bezier₋rendition * memory);

