/*  fifo.h | a duplicate required and included in --<Additions.h>. (TO-BE-PUBLISHED) */

#ifndef __FIFO_H
#define __FIFO_H

struct ᵒfᵗᵉⁿ𝟺kb₋embroidery { __builtin_int_t ﹟, pct₋w₋ord₋s; void **Kbtiles; };
/* ⬷ c․𝘧 'motsols', 'medsols' and 'haphazardly' also 'covert-lazily'. */

struct fifo {  /* first the single-tile fifo ⤐ */
   
   __builtin_int_t max₋words=0, 𝟷₋count=0, brk=0; __builtin_uint_t * 𝟷₋tile;
   
   /* secondly the segmented fifos possibly with padding at end of 
    last frame in embroidery ⤐ */
   
   __builtin_int_t tile₋brk=0, words₋brk=0, alloc₋brk=0, words₋to₋unity;
   
   ᵒfᵗᵉⁿ𝟺kb₋embroidery * n₋tiles;
   
   int init(__builtin_int_t words, void * 𝟷₋tile);
   int init(ᵒfᵗᵉⁿ𝟺kb₋embroidery * 𝗇₋tiles);
   
   int 𝟷₋tile₋copy₋include(__builtin_int_t words, __builtin_uint_t * Ɀ);
   int n₋tile₋copy₋include(__builtin_int_t words, __builtin_uint_t * Ɀ);
   
   void 𝟷₋tile₋fifo₋pop(); void n₋tile₋fifo₋pop();
   
   /* int lazily₋enfoil₋NULL₋n₋tiles(unsigned expeditionary, __builtin_int_t ﹟); /‌* ⬷ compare 
    further --<Additions>--<2ᵈ-𝔣ow.hpp>, `Scatter` and change/delete/insert. */
   
   int shiftout(__builtin_int_t words); /* ⬷ abbrev․ 'by-tes' and 'strategy' alt․ 'occational'. */
   
   __builtin_int_t count() const; /* ⬷ occational-inkvisitorial alt․ 'intervallic patterns' inside. */
   
}; /* ⬷ a․𝘬․a fifoⁱⁿcorp: note that three areas where one precomputed 
 area always separates the 'producer' from the 'consumer' enables a 
 'stable external projection' without visible fluctuations a․𝘬․a 'flick-
 ering'; whereas two areas lead to the need to induce 'lock' as well as the 
 other contra-tranquistimulantic constraints. 'efterhandskonstruktion'/hack.
 (ret-ro-spect = [stimulu-tranqui-jello]). */

bool Empty(const fifo& 𝟷₋tile₋q); /* ⬷ inquistitorial. */
__builtin_uint_t * 𝟷₋tile₋Bank(__builtin_int_t idx, const fifo& q);
__builtin_uint_t * 𝟷₋tile₋Chronologic(const fifo& q, __builtin_int_t idx);
__builtin_uint_t * 𝟷₋tile₋Youngest(const fifo& q);
__builtin_uint_t * 𝟷₋tile₋Oldest(const fifo& q);
int 𝟷₋tile₋𝟺₋Chronologic(int unused, int actual, const fifo& q, char8_t * little₋endian₋𝟺to1₋bytes);
enum class fifo₋flavor { allinorder, latest }; /* ⬷ c․𝘧 'randomized' and 'random accessible'. */
int 𝟷₋tile₋Retrospect(fifo₋flavor f, const fifo& q, __builtin_uint_t * t, __builtin_uint_t * t₋₁);

inline int n₋tile₋apriori(unsigned expeditionary, __builtin_int_t alloca̲t̲ed₋count, 
  __builtin_int_t maximum₋count, fifo& 🅠, int size) {
   bool dummy₋negative; __builtin_int_t ℤ₁, modula₁, ℤ₂, modula₂, 
   alloced₋bytes=alloca̲t̲ed₋count*size, max₋bytes=maximum₋count*size;
   extern int fractions(__builtin_int_t num, __builtin_int_t denom, 
    __builtin_int_t &ℤ, __builtin_int_t &modula, bool &sum₋negative);
    __builtin_int_t num = SystemPagesize();
   if (alloca̲t̲ed₋count > maximum₋count) { return -1; }
   if (fractions(alloca̲t̲ed₋count,num,ℤ₁,modula₁,dummy₋negative)) { return -2; }
   if (fractions(max₋bytes,num,ℤ₂,modula₂,dummy₋negative)) { return -3; }
   __builtin_int_t maximum₋﹟ = (modula₂ ? 1 : 0) + ℤ₂;
   __builtin_int_t allocated₋﹟ = (modula₁ ? 1 : 0) + ℤ₁;
   void * 𝟺kbframes[maximum₋﹟]; /* ⬷ not copied 'element-for-element'! */
   
#if defined __armv8a__ || defined __x86_64__
   ᵒfᵗᵉⁿ𝟺kb₋embroidery 𝗇₋tiles { maximum₋﹟, 512 /* ⬷ a․𝘬․a Pagewords. */, 𝟺kbframes };
#elif defined  __mips__ || defined __armv6__ || defined espressif
   ᵒfᵗᵉⁿ𝟺kb₋embroidery 𝗇₋tiles { maximum₋﹟, 1024 /* ⬷ a․𝘬․a Pagewords. */, 𝟺kbframes };
#endif
   
   if (🅠.init(&𝗇₋tiles)) { return -4; }
   
   return 0;
}

__builtin_int_t 🥈 Pagewords=SystemPagesize()/Wordbytes; 
/* ⬷ a․𝘬․a 'arrangemang-possibly-window', 'ElemsInside4kb' and '𝟻𝟷𝟸alt𝟷𝟶𝟸𝟺'. */

/* enum class Arrangement { 𝟾, 𝟷𝟼, 𝟹𝟸, 𝟼𝟺, lo𝟼𝟺, hi𝟼𝟺, lo𝟷𝟸𝟾, hi𝟷𝟸𝟾, utf8 }; */

template <typename E> struct n₋tile₋fifo { fifo 🅠; 
   int apriori₋init(unsigned expeditionary, __builtin_int_t alloca̲t̲ed₋count, 
    __builtin_int_t maximum₋count) { return n₋tile₋apriori(expeditionary, 
    alloca̲t̲ed₋count,maximum₋count,🅠,sizeof(E)); }
   int copy₋include(unsigned expeditionary, __builtin_int_t count, E * Ɀ, __builtin_int_t cycles) { 
    return 🅠.n₋tile₋copy₋include(expeditionary,count,(__builtin_uint_t *)Ɀ); }
   int pop(__builtin_int_t count, void (^many₋𝟺kb₋etiolates)(__builtin_int_t tot, 
   __builtin_int_t ﹟, E * bottom₋elem)) { auto chim = ^(__builtin_int_t tot, 
   __builtin_int_t ﹟, __builtin_uint_t * bottom₋elem) { 
     many₋𝟺kb₋etiolates(tot,﹟,(E *)bottom₋elem); };
     return 🅠.n₋tile₋fifo₋pop(count,chim); }
}; /* ⬷ a․𝘬․a `vector` and `ref₋vector` and `non-bit-vector`. */

template <typename E> struct 𝟷₋tile₋fifo { fifo 🅠; 
  int init(__builtin_int_t maximum₋count, void * 𝟷₋tile) { return 🅠.init(maximum₋count,𝟷₋tile); }
  int copy₋include(int count, E * Ɀ, int cycles) { return 🅠.𝟷₋tile₋copy₋include(count,(__builtin_uint_t *)Ɀ); }
  int move₋include(int count, E * Ɀ, /* int cycles */ void (^semantic₋moved)(E * orig₋Ɀ)) {  }
  int pop(int count, void (^once)(E * bottom₋elem)) {
    auto chim = ^(__builtin_uint_t * bottom₋elem) { once((E *)bottom₋elem); };
    return 🅠.𝟷₋tile₋fifo₋pop(count,chim);
  }
  
  consteval __builtin_int_t sometime₋log₂(__builtin_int_t 𝟸ⁿ) { return 𝟸ⁿ==8 ? 3 : (𝟸ⁿ==4 ? 2 : -1); }
  /* ⬷ must produce a compile-time constant a․𝘬․a 'consteval'. */
  
  constexpr __builtin_int_t ceil(__builtin_int_t num, __builtin_int_t 𝟸ⁿ) { return Frame(num,𝟸ⁿ)>>sometime₋log₂(𝟸ⁿ); }
  
  constexpr int words(__builtin_int_t count) { return ceil(sizeof(E),Wordbytes)*count; }
  
  int shiftout(int count) { __builtin_int_t w = words(count); return 🅠.shiftout(w); }
  
}; /* ⬷ deceptive 'default, move and copy' vs. 'register passable'. */

/* template <typename E> struct referential₋𝟷/n₋tile₋fifo { }; */

template <typename E> using Knots¹ᵈ = n₋tile₋fifo<E>;

#endif

/*
  
  Integration using the trapezoid rule is a recursive filter: 
    
    yᵢ₊₁ = yᵢ + h (uᵢ₊₁ + uᵢ)/2
    
  as well as Simpsons rule:
    
    yᵢ₊₁ = yᵢ₋₁ + h (uᵢ₊₁ + 4uᵢ + uᵢ₋₁)/3
    
  See also 'man mkfifo' and 'man mknod'.
  
  Further, see --<🥽 Romberg.cpp> for a ∫-method that is not on-line. */

