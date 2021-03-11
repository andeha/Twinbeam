/*  fifo.h | a duplicate required and included in --<Additions.h>. */

#ifndef __FIFO_H
#define __FIFO_H

struct ᵒfᵗᵉⁿ𝟺kb₋embroidery { __builtin_int_t ﹟, pct₋w₋ord₋s; void **𝟺kbtiles; };
/* ⬷ a․𝘬․a void * Kbtiles[]. */

struct fifo { __builtin_int_t words₋to₋unity; /* ⬷ a․𝘬․a 'max₋word', 
   
 first the single-tile fifo ⤐ */
   
   __builtin_int_t 𝟷₋count=0, brk=0; __builtin_uint_t * 𝟷₋tile;
   
   int init(__builtin_int_t words, void * 𝟷₋tile);
   
   int 𝟷₋tile₋copy₋include(__builtin_int_t words, __builtin_uint_t * Ɀ);
   
   void 𝟷₋tile₋fifo₋pop();
   
   int 𝟷₋tile₋shiftout(__builtin_int_t words); /* ⬷ abbrev․ 'by-tes' and 'strategy' alt․ 'occational'. */
   
 /* secondly the segmented fifos possibly with padding at end of 
    last frame in embroidery ⤐ */
   
   __builtin_int_t tile₋brk=0, words₋brk=0, alloc₋brk=0, n₋count=0, words₋enfoiled=0;
   
   ᵒfᵗᵉⁿ𝟺kb₋embroidery * n₋tiles;
   
   int init(ᵒfᵗᵉⁿ𝟺kb₋embroidery * 𝗇₋tiles);
   
   int n₋tile₋copy₋include(__builtin_int_t words, __builtin_uint_t * Ɀ);
   
   void n₋tile₋fifo₋pop();
   
   int lazily₋enfoil₋NULL₋n₋tiles(unsigned expeditionary, __builtin_int_t ﹟);
   
   int n₋tile₋append₋in₋middle₋alt₋atend(__builtin_int_t ﹟);
   
   /* ⬷ compare further --<Additions>--<2ᵈ-𝔣ow.hpp>, change/delete/insert and 'Scatter'. */
   
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

template <typename E> struct 𝟷₋tile₋fifo { fifo 🅠; 
  int init(__builtin_int_t maximum₋count, void * 𝟷₋tile) { return 🅠.init(maximum₋count,𝟷₋tile); }
  int copy₋include(int count, E * Ɀ, int cycles) { return 🅠.𝟷₋tile₋copy₋include(count,(__builtin_uint_t *)Ɀ); }
  void pop() { 🅠.𝟷₋tile₋fifo₋pop(); }
  int shiftout(int count) { return 🅠.𝟷₋tile₋shiftout(count); }
}; /* ⬷ deceptive 'default, move and copy' vs. 'register passable'. */

#endif

/*
  
  Integration using the trapezoid rule is a recursive filter: 
    
    yᵢ₊₁ = yᵢ + h (uᵢ₊₁ + uᵢ)/2
    
  as well as Simpsons rule:
    
    yᵢ₊₁ = yᵢ₋₁ + h (uᵢ₊₁ + 4uᵢ + uᵢ₋₁)/3
    
  See also 'man mkfifo' and 'man mknod'.
  
  Further, see --<🥽 Romberg.cpp> for a ∫-method that is not on-line. */

