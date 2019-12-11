/*  Knot.h | Tape ≡ Chunk.  (I․𝘦 pseudo-randomly constructed sequences.) */

namespace Knot { /* … */ }

template <typename E>
struct Knot¹ᵈ { /* A․𝘬․a `Relative+Irreversib`, `Radio`, `Sequence`, `Desk` and `Crow`. */
  
  MAY_CONTAIN_TRACES_OF_FIRM_REALTIME int pushc₊₊(const E& elem, bool push﹠﹠) { return Knot::pushc₊₊(sizeof(E), (void *)elem, push﹠﹠); }
  
  MAY_CONTAIN_TRACES_OF_FIRM_REALTIME int pushc(const E& elem) { return Knot::pushc(sizeof(E), (void *)elem); }
  
  MAY_CONTAIN_TRACES_OF_FIRM_REALTIME int pushᵣₑf(const E& elem) { return Knot::pushᵣₑf(sizeof(E), (void *)elem); }
  
  MAY_CONTAIN_TRACES_OF_FIRM_REALTIME int pushᵟ(const E& elem) { return Knot::pushᵟ(sizeof(E), (void *)elem); }
  
  /* also `...chronologically` and `...retrospectly` arranged sequences. */
  
  int pop(__builtin_int_t count, E elems[]) { return Knot::pop(sizeof(E)*count, (void *)elems); }
  
  short 🥈 Bytes = SystemInfoPagesize() - (sizeof(uint16_t) + 2*sizeof(void *));
  
  struct Tape {
    uint8_t content[Bytes];
    Tape *next, *prev;
    uint16_t brk=0; /* For content deletion (from block-end) in O(1) time. */
    __builtin_int_t ordinal; bool wrapped; /* See --<Twinbeam>{Chronology}. */
  };
  
  typename Knot¹ᵈ<E>::Tape *first, *last;
  
  __builtin_int_t occupied, avail;
  
  static Tape tapes[16]; static bool didwrap; static __builtin_int_t ordinal, ⁱᵈˣunused;
  
  static Tape& tape(short unsigned nᵒ) { return tapes[nᵒ]; } /* 𝖤․𝘨 for time series. */
  
  static short lru() { bool didwrap;
  
    Chronology chronology = ComputationalChronology();
    __builtin_int_t ordinal = chronology.ordinal(didwrap);
   
  } /* See also --<source>--<Memory.cpp>. */
  
  enum Extra { cyclicend, lastatend, crash, bound }; /* The cyclic and last defined also for idx < 0. */
  
  int deref(Extra e, __builtin_int_t idx, void (^found)(void * first, void * 
    elem, void * last)) const { return Knot::deref((int)e, idx, found); } /* All pointers, with a 2¹²-bit align. */
  
  int interval(Extra e, __builtin_int_t nᵒ, void (^found₁)(void * first, void * 
    elem, void * last), void (^found₂)(void * first, void * elem, void * 
    last)) const { return Knot::interval((int)e, nᵒ, found₁, found₂); }
  
  int /*∀*/ forall(void (^block)(SemanticPointer<E *> elem, bool& stop)) const { return Knot::forall(block); }
  
  enum class Errorcode { unableToWrite, unableToGrow, unableToDeref, unableToTape };
  
  MACRO static void Error(Errorcode code) { /* ⭐️ */ Sheriff(); }
  
  enum Dynamic { c₊₊, c, ᵣₑf, δ };
  
  int swap(__builtin_int_t idx₁, __builtin_int_t idx₂, Dynamic d) { return Knot::swap(sizeof(E), idx₁, idx₂, (int)d); }
  
  int refresh(__builtin_int_t count, E& unit, Dynamic d) { return Knot::refresh(count, (void *)unit, sizeof(E), (int)d); }
  
}; /* ⬷ WORM-safe container. A․𝘬․a 𝑅𝑎⃛𝑡𝑡𝑠ℎ𝑎𝑛𝑙𝑖𝑛𝑔𝑎𝑟. For `Knot¹ᵈ₋ᵥᵥ`, 
  see --<🥽 Cordal.cpp>. */

struct Knot2½d { __builtin_int_t k; void * c; 
    
    Knot2½d(void * base, __builtin_int_t bytes, int cols) { k=bytes; c=base; }
    
};

/* --<Knot₋₁.hpp>, --<🥽 Ckllipbookʰⁱ.cpp>, --<🥽 Ckllipbookˡᵒ.cpp>, 
   --<CachedFile.cpp>, --<🥽 Hockey.cpp> and --<🥽 RoloX.cpp>. */

/* unsigned MaxFrames(); int Acquire(unsigned ﹟frames, void (^each)(void * frame)); int Release(void * frame); */

/* --<🥽 Frames.cpp>, --<🥽 Author.cpp>, --<🥽 Virtualᵒˡᵈ.cpp> and --<volatile>--<ˢᵚPaging.h> */
