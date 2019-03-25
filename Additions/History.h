//
//  History.h
//  Additions
//

#ifndef __HISTORY_H
#define __HISTORY_H

#include <Additions/System.h>
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
      union { Q7 q7s[8]; Q15 q15s[4]; } relatives;                   /*  3 */
      __builtin_int_t machinesigned;                                 /* 13 */
#ifdef __x86_64__
      /* 💊 ditriaconta avx2machine;                                     6
      ditriaconta avx512machine[2];                                      7 */
#endif
      typedef bignum * Bignum; Bignum big;                           /* 11 */
      struct { Bignum right; Bignum left; } doublebig;               /* 12 */
    }; /* Sometimes 64 bits, sometimes 2*32 bits. */
    
    typedef const char32_t * Key;
    typedef const char * Reference;
    Timeserie<Key, Pod, Reference> serie;
    Kind kind;
    
    static History::Pod (^add)(History::Pod& left, History::Pod& right,
      void *ctx); /* History::Kind */
    
    int cloneAndPersist(const char *utf8path, void(^completion)());
    void hypothesis(History::Pod probe, void (^evaluable)());
    static Opt<History> reflect(const char * utf8path);
    
#pragma mark Implicits
    
    History() = delete;
    
    History(const History& other) = default;
    
};

struct ComputationalIndex {
    
    explicit ComputationalIndex() noexcept;
    
    typedef const char32_t * Serie;
    
    typedef Fossilate Arguments[4];
    
#pragma mark Transactions
    
    void peek(void (^entry)(Serie key, Operation op, const Arguments& e,
      bool& stop));
    
    bool commit(Chronology::Instant instant, void (^touchbase)(const char *
      ref, const History::Pod& value, void * ctx, Version revision, const
      Chronology::Instant& instant));
    
    void rollback();
    
#pragma mark Preservation
    
    int cloneAndPersist(const char *utf8path, void(^completion)());
    
    static Opt<ComputationalIndex> reflect(const char * utf8path);
    
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
  simd_tᵦ doubleDouble;                                           /* 1 */
  simd_t quadFloat;                                               /* 2 */
  simd_tᵥ sixteenVideo;                                           /* 3 */
  simd_tₐ eightAudio;                                             /* 4 */
  simd_tᵢₐ fourThirtytwo;                                         /* 5 */
  simd_tₒ twoSixtyfour;                                           /* 6 */
};

#endif
