/*  History.h | At last, a state snapshot. */

#ifndef __HISTORY_H
#define __HISTORY_H

#include <Twinbeam.h>
#include <Additions/Timeserie.hpp>
#if __has_include(<Additions/Esoteric.h>)
#include <Additions/Esoteric.h>
#endif

struct History { /* Consideration */
    
    explicit History(Version& revision) noexcept;
    
    enum Kind { machineunsigned, singleReal, doubleReal, 𝟺𝗵𝗮𝗹𝗳s=4, 𝟾Q7=3, 
      𝟺Q15=5, 𝟸Q31=8, 𝛥𝘵=9, Q79=10, Temporalˡ=11, /* ⟤⟥ */ machinesigned=23 };
    
    union Pod {
      __builtin_uint_t machineunsigned;                              /*  0 */
      double singleReal;                                             /*  1 */
      struct { float starboard; float port; } doubleReal;            /*  2 */
      half pythagoreans[4];                                          /*  4 */
#if __has_include(<Additions/Esoteric.h>)
      union { Q7 q7s[8]; Q15 q15s[4]; Q31 q31s[2]; } relatives;      /*  3 */
#endif
      __builtin_int_t machinesigned;                                 /* 23 */
#ifdef __x86_64__
      /* ✠ ditriaconta avx₂machine;                                      6
      ditriaconta avx512machine[2];                                      7 */
#endif
      Chronology::UQ32 relativretrospectat                           /*  9 */
      /* typedef bignum * Bignum; Bignum big;                           11
      struct { Bignum right; Bignum left; } doublebig;                  12 */
      struct Mixedradix { double small; __builtin_int_t 𝟷𝟶ᵐ; };
      struct { Mixedradix right; Mixedradix left; } detail;          /* 17 */
    }; /* Sometimes 64 bits, sometimes 2*32 bits. See --<Arith⁺⁺.cpp>. */
    
    typedef const char * ⁸Bitref; typedef Unicodes Key;
    Timeserie<Key, Pod, ⁸Bitref> serie;
    Kind kind;
    
    static History::Pod (^add)(History::Pod& left, History::Pod& right, 
      void *ctx); /* History::Kind */
    
#pragma mark - Querying
    
    void hypothesis(History::Pod probe, void (^evaluable)());
    
#pragma mark Implicits
    
    /* History(const History& other); */
    
    History() = delete;
    
};

struct ComputationalIndex {
    
    explicit ComputationalIndex() noexcept;
    
    typedef Unicodes Serie; /* A․𝘬․a `Name`. */
    
    typedef Fossilate Arguments[4];
    
#pragma mark Transactions
    
    void peek(void (^entry)(Serie key, Operation op, const Arguments& e, 
      bool& stop));
    
    bool commit(Chronology::Instant instant, void (^detail)(const char * 
      ref, const History::Pod& value, void * ctx, Version revision, const 
      Chronology::Instant& instant));
    
    void rollback();
    
#pragma mark - Refreshing the non-volatiles
  
  FOCAL int
    reconcile(
      Opt<Unicodes> pathᵚ,
      void (^ping)(double⁺ʳ percent, bool& stop),
      void (^completion)(int bytes)
    ); /* A․𝘬․a `preserve`. */
    
#pragma mark Time and Space
    
    /* Subgraph<Seriekey> organization; */
    
    void * series; /* A․𝘬․a Map<Serie, History>; With `succumb` and `branch`. */
    
😐;

extern History::Pod (^__machineunsigned)(__builtin_uint_t scalar);
extern History::Pod (^__doubleReal)(float left, float right);
extern History::Pod (^__singleReal)(double scalar);

void Present(Utf8Terminal &term, const History& history);
void Present(Utf8Terminal &term, const History::Pod& pod, 
  const History::Kind kind);

union Twinpod {                                                             
  simd_tᵦ doubleDouble;                                              /* 1 */
  simd_t quadFloat;                                                  /* 2 */
  simd_tᵥ sixteenVideo;                                              /* 3 */
  simd_tₐ eightAudio;                                                /* 4 */
  simd_tᵢₐ fourThirtytwo;                                            /* 5 */
  simd_tₒ twoSixtyfour;                                              /* 6 */
#if __has_include(<Additions/Esoteric.h>)
  Q79 eightfixed[8];                                                /* 10 */
  Q1516 fourinterval[4]                                             /* 11 */
#endif
}; /* ⬷ Requires physical to unlock after storage. Notice pod possibly 
  locally colored. */

#pragma mark - Preserves

FOCAL
Opt<ComputationalIndex>
ᵟBranch(
  Unicodes pathᵚ, 
  int (^modernize)(Memoryview view, ComputationalIndex & y), 
  void (^ping)(double⁺ʳ percent, bool& stop), 
  void (^completion)(int bytes)
); /* A․𝘬․a `Reflect`/`Abduct`, reconcile, preserve, syncronize, succumb, branch, cloneAndPersist. */

#endif /* C𝘧. Scandinavian 'förlupen', 'upplupen' and anglosaxon 'puzzle'/`lapsus𝘖rMUX`. */

