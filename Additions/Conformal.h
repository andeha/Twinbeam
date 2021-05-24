/*  Conformal.h | slices from --<System.h>. */

enum Variation { Rasterized, FunctionalD, FunctionalS };

namespace Cartesian3d { typedef floatʳ type; typedef type (^Hilbert)(Chronology
  ::instant t); struct Ħ { Hilbert x, y, z; }; struct 𝗣 { type x, y, z; }; struct
  Variat { union { Cartesian3d::𝗣 p; Cartesian3d::Ħ ħ; }; Variation v; }; }

namespace Modulation { typedef double type; /* kludge */ typedef struct { type value₁; type value₂; } typepair;
  typedef typepair (^HilbertS)(Chronology::relative t); /* ^🎲 */
  typedef type (^HilbertD)(Chronology::relative t);     /* ^🕯 */
  struct ĦD { HilbertD ampl, angular, phase; };         /* Ħ🕯 (Determinstic Hilbert triple) */
  struct ĦS { HilbertS ampl, angular, phase; };         /* Ħ🎲 (Stochastic Hilbert triple) */
  struct 𝗣 { type ampl, angular, phase; };              /* (Sampled Hilbert triple) */
  struct Variat { union { 𝗣 p; ĦD ħd; ĦS ħs; }; Variation v; }; } /* TODO: Validate sizeof HilbertS == sizeof HilbertD == 32,64 */

namespace Celestial { typedef double type; typedef type (^Hilbert)(Chronology🚀
  ::instant t); struct Ħ { Hilbert r, 𝛳, 𝜑; }; struct 𝗣 { type r, 𝛳, 𝜑; };
  struct Variat { union { Celestial::𝗣 p; Celestial::Ħ ħ; }; Variation v; }; }

/**  Angles continue in a clockwise direction, rather than counter-clockwise. */

namespace Eulerangles { typedef double type;
  typedef Opt<int> (^HilbertH)(Chronology🦠::instant t, simd_t 𝛳𝛹𝛷ᵖʳᵉᵛ, float &ᵒᵘᵗ); /* Hilbert 𝘏𝘰𝘣𝘣𝘺𝘪𝘴𝘵 */
  typedef Opt<int> (^HilbertP)(Chronology🦠::instant t, simd_t 𝛳𝛹𝛷ᵖʳᵉᵛ, double &ᵒᵘᵗ); /* Hilbert 𝘗𝘳𝘰 */
  struct ĦH { HilbertH 𝛳ᴴ, 𝛹ᴴ, 𝛷ᴴ; }; struct ĦP { HilbertP 𝛳ᴾ, 𝛹ᴾ, 𝛷ᴾ; }; struct 𝗣 { type 𝛳, 𝛹, 𝛷; };
  struct Variat { union { Eulerangles::𝗣 p; Eulerangles::ĦH ħ; }; Variation v; }; }

enum class Earthcompass { Nᵀᴿᵁᴱ, /* Nᴹᴬᴳ, */ Sᵀᴿᵁᴱ, E, W }; /* 𝑵 𝙽 𝐸 𝑆 𝑊: magnetic field required. */

typedef struct EarthbasedSpatial {
   double degrees, arcminutes, arcseconds; /* Relatively calm. */
   Earthcompass compass;
} Sexagesimal; /* For 𝑝𝑎𝑟𝑎𝑙𝑙𝑒𝑙𝑠 and 𝑚𝑒𝑟𝑖𝑑𝑖𝑎𝑛𝑠. */

/* #define EarthBasedSpatialTemporalHeading 360 == 0 degrees */

