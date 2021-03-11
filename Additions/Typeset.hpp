/*  Typeset.hpp | well-set additions. */

namespace Typecase {
    
    typedef uint32_t TypefaceAnatomy;
    
    BITMASK(TypefaceAnatomy) {
      Bold        = 0b000000000000000000000000001,
      Italic      = 0b000000000000000000000000010,
      Slant       = 0b000000000000000000000000100,
      SansSerif   = 0b000000000000000000000001000,
      Monospace   = 0b000000000000000000000010000,
      Number      = 0b000000000000000000000100000, /* complementary set of numbers. */
      Stillistic  = 0b000000000000000000001000000, /* ⬷ a․𝘬․a script or calligraphy. */
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
    
}

/** ⤐ see 'TypedImpression' below for details ⤐ */

typedef double Fontsize;

struct TypedExpression {
  Typecase::TypefaceAnatomy anatomy;
  Opt<Fontsize> points;
  Opt<𝟽bit₋text> sku₋face; /* ⬷ pointer into a typed₋expressionface₋stringpool. */
  Opt<Color> color;
}; /* ⬷ two instances 'default' and 'current-after-modification'. */

#define typedIn(anatomy) TypedExpression { anatomy, Opt<Fontsize>::no(), Opt<const char *>::no(), Opt<Color>::no() }

namespace Composingstick {
   
   int compose₁(int count, char8_t temp₋u8s[], TypedExpression expr, 
    void * first, void * last, Kiddle * kiddle, Unicodes * run);
   
   int compose₂(int count, char32_t temp₋ucs[], TypedExpression expr, 
    void * additive, void * subtractive, Kiddle * kiddle, Unicodes * run);
   
   typedef UnicodeIntervalAnd𝑂rLocation Intervallic;
   
   Intervallic mergeWith(Intervallic applicant, bool temporary, Unicodes * fold, 
    TypedExpression expr);
   
   TypedExpression probe(Utf8Symbol here, bool temporary, Unicodes * text);
   
   TypedExpression probe(Intervallic here, bool temporary, Unicodes * text);
   
   Intervallic updateTo(Intervallic current, bool temporary, Unicodes * amorphic, 
    TypedExpression expr);
   
   Intervallic clear(Intervallic subtractive, bool temporary, Unicodes * amorphic);
   
   /* 'Virtual Manhattan and physical Manhattan later' /‌/ ☜😐📖 */
   MACRO Intervallic clear(Intervallic substractive, Manhattan dirs, 
     bool temporary, Unicodes * amorphic) { /* 😐😐: > 'for' ✜𒀽 ⏱🏁 */
       return UnicodeIntervalAnd𝑂rLocation { }; }
   
}

