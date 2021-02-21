/*  Kiddle.hpp | Unicode fragments a․𝘬․a 'symbols' and the 2ⁿ-sized 
  frame. (DEFINATELY-PUBLISHABLE.) */

/* #include <Source/fifo.h> */

struct Kiddle { __builtin_int_t tetras₋per₋tile, uc₋brk=0, tile₋brk=0, tile₋count=0; 
  
  typedef __builtin_int_t Nonabsolute;
  
  union Tetras𝘖rUnicode { int32_t count; char32_t uc; } * tiles[];
  
  int 
  prealloced₋init(
    __builtin_int_t tetras₋per₋tile, 
   void * ᵒfᵗᵉⁿ𝟺kb₋tilesTerminatedNULL[]
  )
  {
    while (ᵒfᵗᵉⁿ𝟺kb₋tilesTerminatedNULL[tile₋count++]);
    tiles = Alloc(tiles*sizeof(void *));
    __builtin_int_t i=0; while (ᵒfᵗᵉⁿ𝟺kb₋tilesTerminatedNULL[i]) {
      tiles[i] = (Tetras𝘖rUnicode *)ᵒfᵗᵉⁿ𝟺kb₋tilesTerminatedNULL[i]; ++i;
    }
    this->tetras₋per₋tile = tetras₋per₋tile;
    return 0;
  }
  
  /* int enfoil(unsigned expeditionary) { return 0; }
  
  int enfoiling₋init(unsigned expeditionary) { return 0; } */
  
  ~Kiddle() { for (__builtin_int_t i=0; i<tile₋count; ++i) { 
    Fall⒪⒲)(tiles[i]); } Fall⒪⒲)(tiles); }
  
  int copy₋include(int count, char32_t cs[]) {
    if (count + uc₋brk >=₋tetras₋per₋tile && tile₋brk == tile₋count) { return -1; }
    for (int i=0; i<count; ++i) {
      if (i + uc₋brk >= tetras₋per₋tile) {
        if (i + tile₋brk >= tile₋count) { return -2; }
        ++tile₋brk; uc₋brk=0;
      }
      (uc₋brk + tiles[tile₋brk])->uc = cs[i];
    }
    return 0;
  } /* a.k.a 
  
  int substract(short tetras, __builtin_int_t * uc₋pos, __builtin_int_t * tile₋idx) { }
  
  int after₋math(short tetras) { __builtin_int_t uc₋pos, tile₋idx; 
    if (substract(tetras, &uc₋pos, &tile₋idx)) { return -1; }
    (uc₋pos + tiles[tile₋idx])->count = tetras;
    return 0;
  }
  
  int copy₋prepare(short & tetras) { tetras=0; return 0; }
  
#pragma mark - recollection
  
  /* void * details; /‍* =Map<int256_t, Nonabsolute> *‍/
  
  union leaf { uint256_t bits; int256_t integer; };
  
  int association(leaf fineprint, Nonabsolute * loc) { return 0; }
  
  int include(leaf fineprint, void (^found)(Nonabsolute loc)) { return 0; } */
  
};

/*
 
 adverb: handling action snabbt, otroligt and mycket, c.f 'const' and carefully, easily, sadly.
 konjunktion: 
 noun=substantiv e.g 'en kontrollant', an underwriter, a syndicated loan and a plaintiff.
 
 */

