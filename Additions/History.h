/*  History.h | 'At last the state snapshot, executive summary styled'. */

#ifndef __HISTORY_H
#define __HISTORY_H

#include <Additions/Timeserie.hpp>
#include <Additions/Kiddle.hpp>
#if __has_include(<Additions/One-eps.h>)
#include <Additions/One-eps.h>
#endif

struct History { /* ⬷ consideration success! */
    
    explicit History(Version & revision) noexcept;
    
    enum Kind { machineunsigned, single₋ℝ, double₋ℝ, 𝟺₋𝗵𝗮𝗹𝗳s=4, 𝟾Q7=3, 𝟺Q15=5, 
      𝟸Q31=8, 𝛥𝘵=9, Q79=10, Temporalˡ=11, /* ⟤⟥ */ machinesigned=23, 
      ChronoUQ32²=24 };
    
    union Pod {
      __builtin_uint_t machineunsigned;                               /*  0 */
      double single₋real;                                             /*  1 */
      struct { float starboard; float port; } double₋real;            /*  2 */
      half pythagoreans[4];                                           /*  4 */
#if __has_include(<Additions/One-eps.h>)
      union { Q7 q7s[8]; Q15 q15s[4]; Q31 q31s[2]; } relatives;       /*  3 */
#endif
      __builtin_int_t machinesigned;                                  /* 23 */
#ifdef __x86_64__
      /* ✠ ditriaconta avx𝟸machine;                                       6
      ditriaconta avx𝟻𝟷𝟸machine[2];                                       7 */
#endif
      Chronology::Interval relative₋retrospectat                      /*  9 */
      /* typedef bignum * Bignum; Bignum big;                            11
      struct { Bignum right; Bignum left; } doublebig;                   12 */
      struct Mixedradix { float small; int32_t 𝟷𝟶ᵐ; }; /* ⬷ alt. double and __builtin_int_t. */
      struct { Mixedradix right; Mixedradix left; } detail;           /* 17 */
      struct Small₋schoolbook { int32_t ℤ; uint16_t modula, denom; }; /* see --<Twinbeam.h>{Schoolbook} for a traditional schoolbook. */
      struct { Small₋schoolbook starboard, port; } financials;        /* 19 */
      struct { Chronology::UQ32 starboard, port; } maxmin₋latency;    /* 24 */
    };
    
    n₋tile₋fifo 𝟽bit₋pool; Kiddle Unicode₋pool; /* ⬷ compares to 
     compulsive cases of 'Alloc' and 'Fallow`. */
    
    typedef __builtin_int_t 𝟽₋bit₋ref;
    typedef Kiddle::Nonabsolute Unicode₋ref;
    
    Timeserie<Unicode₋ref, Pod, 𝟽₋bit₋ref> serie; /* see also --<Kiddie.hpp>. */
    
    History::Pod add(History::Pod& left, History::Pod& right, 𝟽bit₋string ref, Kind kind);
    
    History::Pod add(History::Pod&, 𝟽bit₋string ref, Kind kind);
    /* ⬷ a․𝘬․a 'bias' for mixed single and left/right series. */
    
#pragma mark - Querying
    
    void hypothesis(History::Pod probe, void (^evaluable)()); 
    /* ⬷ a․𝘬․a `man` and --<Projects>--<🥽⋆UQL.cpp>. */
    
#pragma mark Implicits
    
    History(const History& other) = delete; /* ⬷ see `Snapshot` below. */
    
    History() = delete;
    
};

struct ComputationalIndex {
    
    explicit ComputationalIndex() noexcept;
    
    typedef 𝟽bit₋text Serie; /* a․𝘬․a `Name`. */
    
    typedef Fossilate Arguments[4];
    
#pragma mark Transactions
    
    void peek(void (^entry)(Serie key, Operation op, const Arguments& e, 
      bool& stop));
    
    bool commit(Chronology::Instant instant, void (^detail)(const char * 
      ref, const History::Pod& value, void * ctx, Version revision, const 
      Chronology::Instant& instant));
    
    void rollback();
    
#pragma mark Implicits
    
    ComputationalIndex(const ComputationalIndex& other) = delete;
    
#pragma mark - Refreshing a non-volatile memory
  
  FOCAL int
    reconcile(
      Opt<Unicodes> pathᵚ, /* a․𝘬․a `primary𝘖𝘳𝑆econd` and `similar`. */
      void (^ping)(double⁺ʳ percent, bool& stop), 
      int (^completion)(__builtin_int_t bytes, bool& no₋go)
    ); /* a․𝘬․a `preserve` and `syncronize`; 𝖼․𝘧 `msync` and `Snapshot`. */
    
#pragma mark Time and space
    
    /* Subgraph<Seriekey> organization; */
    
    void * series; /* a․𝘬․a Map<Serie, History>; with `succumb` and `branch`. */
    
😐;

extern History::Pod (^__machineunsigned)(__builtin_uint_t scalar);
extern History::Pod (^__doubleℝ)(float left, float right);
extern History::Pod (^__singleℝ)(double scalar);

void Present(Utf8Terminal &term, const History& history);
void Present(Utf8Terminal &term, const History::Pod& pod, 
  const History::Kind kind);

union Twinpod {                                                            
  simd_tᵦ double₋double;                                             /* 1 */
  simd_t quad₋float;                                                 /* 2 */
  simd_tᵥ sixteen₋video;                                             /* 3 */
  simd_tₐ eight₋audio;                                               /* 4 */
  simd_tᵢₐ four₋thirtytwo;                                           /* 5 */
  simd_tₒ two₋sixtyfour;                                             /* 6 */
#if __has_include(<Additions/One-eps.h>)                                    
  Q79 eight₋fixed[8];                                               /* 10 */
  Q1516 four₋interval[4]                                            /* 11 */
#endif                                                                      
}; /* ⬷ requires physical to unlock after storage. Notice pod possibly 
  locally colored. */

#pragma mark Volatile memory copying and not 'copy-constructor'

int Snapshot(const ComputationalIndex& original, ComputationalIndex& pristine);

#pragma mark The Scandinavian words 'förlupen', 'upplupen' and 'interim'

FOCAL
int /* Opt<ComputationalIndex> requires copy-constructible object. */
ᵟBranch(Unicodes primary𝘖𝘳𝑆econd, ComputationalIndex &pristine, 
  void (^ping₁)(double⁺ʳ percent, bool& stop), 
  int (^modernize)(Memoryregion original, ComputationalIndex & shoot), 
  void (^ping₂)(double⁺ʳ percent, bool& stop), 
  void (^completion)(__builtin_int_t bytes, bool& no₋go)
); /* a․𝘬․a `clone₋unpack` and `Reflect`. */

#endif

