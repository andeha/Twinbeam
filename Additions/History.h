/*  History.h | Additions. */

#ifndef __HISTORY_H
#define __HISTORY_H

#include <Twinbeam.h>
#include <Additions/Timeserie.hpp>

struct History { /* Consideration */
    
    explicit History(Version& revision) noexcept;
    
    enum Kind { machineunsigned, singleReal, doubleReal, 𝟺𝚑𝚊𝚕𝚏s=4, 𝟾Q7=3,
      𝟺Q15=5, machinesigned };
    
    union Pod {
      __builtin_uint_t machineunsigned;                              /*  0 */
      double singleReal;                                             /*  1 */
      struct { float starboard; float port; } doubleReal;            /*  2 */
      half pythagoreans[4];                                          /*  4 */
      union { Q7 q7s[8]; Q15 q15s[4]; Q31 q31s[2]; } relatives;      /*  3 */
      __builtin_int_t machinesigned;                                 /* 13 */
#ifdef __x86_64__
      /* 💊 ditriaconta avx2machine;                                     6
      ditriaconta avx512machine[2];                                      7 */
#endif
      Chronology::UQ32 relativretrospectat                           /*  9 */
      /* typedef bignum * Bignum; Bignum big;                           11
      struct { Bignum right; Bignum left; } doublebig;                  12 */
      struct { Mixedradix right; Mixedradix left; } detailing;       /* 17 */
    }; /* Sometimes 64 bits, sometimes 2*32 bits. See --<Arith⁺⁺.cpp>. */
    
    typedef const char * ⁸Bitref; typedef Unicodes Key;
    Timeserie<Key, Pod, ⁸Bitref> serie;
    Kind kind;
    
    static History::Pod (^add)(History::Pod& left, History::Pod& right,
      void *ctx); /* History::Kind */
    
#pragma mark - Querying
    
    void hypothesis(History::Pod probe, void (^evaluable)());
    
#pragma mark Implicits
    
    History() = delete;
    
    History(const History& other) = default;
    
};

struct ComputationalIndex {
    
    explicit ComputationalIndex() noexcept;
    
    typedef Unicodes Serie; /* A․𝘬․a `Name`. */
    
    typedef Fossilate Arguments[4];
    
#pragma mark Transactions
    
    void peek(void (^entry)(Serie key, Operation op, const Arguments& e,
      bool& stop));
    
    bool commit(Chronology::Instant instant, void (^touchbase)(const char *
      ref, const History::Pod& value, void * ctx, Version revision, const
      Chronology::Instant& instant));
    
    void rollback();
    
#pragma mark - Refreshing the non-volatile memory
  
  FOCAL int
    reconcile(
      Opt<Unicodes> pathᵚ, 
      void (^ping)(double⁺ʳ percent, bool& stop), 
      void (^completion)(int bytes)
    ); /* A․𝘬․a `preserve`. */
    
#pragma mark Time and Space
    
    /* Subgraph<Seriekey> organization; */
    
    Map<Serie, History> series;
    
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
};

#pragma mark - Preservation

FOCAL
Opt<ComputationalIndex>
ᵟBranch(
  Unicodes pathᵚ, 
  int (^dyncast)(Memoryview view, ComputationalIndex & y), 
  void (^ping)(double⁺ʳ percent, bool& stop), 
  void (^completion)(int bytes)
); /* A․𝘬․a `Reflect`, `Materialize`. */

#endif
