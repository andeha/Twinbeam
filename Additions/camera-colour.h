/*  camera-colour.h | reflections and additions, later colorhexa.com. */
 
typedef double 𝟶₋𝟷𝟶𝟶ᐧ𝟶, 𝟶₋𝟷ᐧ𝟶;

struct P3Color { 𝟶₋𝟷𝟶𝟶ᐧ𝟶 red, green, blue; }; /*  for screen. */

struct CMYKColor { 𝟶₋𝟷𝟶𝟶ᐧ𝟶 cyan, mangenta, yellow, black; }; /*  for print. */

fostrat₋defi {
  struct P3 { P3Color p3; 𝟶₋𝟷ᐧ𝟶 transparancy; } crome;
  struct CMYK { CMYKColor cmyk; 𝟶₋𝟷ᐧ𝟶 transparancy; } paper;
  char32̄_t * name; /* epsilon for 'no-color' */
} Color;

typedef struct collection /* Color */ Palettecolors; /*  e․𝘨 'Beginners selection II' with
 'titanium white' to 'cadmium yellow light'. */

#define CadmiumRedDeep  /* Color */ { { { 79.6, 0, 1.2 }, 1.0 }, { { 5.5, 39.2, 39.2, 2.0 }, 1.0 }, UC("cadmium red deep") }
#define CadmiumRedMedium  /* Color */ { { { 80.7, 8.6, 4.7 }, 1.0 }, { { 5.1, 39.2, 39.2, 1.2 }, 1.0 }, UC("cadmium red medium") }
#define CadmiumRedOrange  /* Color */ { { { 95.3, 35.3, 5.5 }, 1.0 }, { { 0, 30.1, 39.2, 0 }, 1.0 }, UC("cadmium red orange") }

inline Color CalibratedWhite(𝟶₋𝟷ᐧ𝟶 white, 𝟶₋𝟷ᐧ𝟶 alpha)
{
  𝟶₋𝟷𝟶𝟶ᐧ𝟶 p3₋gray =  (1.0/3.0) * 100 * white;
  𝟶₋𝟷𝟶𝟶ᐧ𝟶 cmyk₋gray = 100 * white;
  return Color { { { p3₋gray, p3₋gray, p3₋gray }, alpha }, { { 0, 0, 0, cmyk₋gray }, alpha }, U"calibrated white" };
}

inline Color Transparent₋natural(Color * color, 𝟶₋𝟷ᐧ𝟶 nonopaque) { color->crome.transparency=nonopaque; }
inline Color Transparent₋print(Color * color, 𝟶₋𝟷ᐧ𝟶 nonopaque) { color->paper.transparency=nonopaque; }
