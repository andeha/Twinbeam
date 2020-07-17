/*  fifo.h | A duplicate required in 'additions'. (TO-BE-PUBLISHED) */

struct ᵐᵃᵡ𝟺kb₋etiolate { __builtin_int_t ﹟; void **𝟺kbtiles; }; /* a․𝘬․a `day-sy` and 
 `braided-fish-knot'.  See --<Reconcile.cpp> and --<Async-ℱ₂.cpp> for details on persistence. */

struct fifo { __builtin_int_t words₋enfoiled, count=0, brk=0; __builtin_uint_t * 𝟷₋tile; 
   
   /* ...and for segmented fifos possibly with padding at end: */
   ᵐᵃᵡ𝟺kb₋etiolate * 𝗇₋tiles; __builtin_int_t tile₋brk=0, words₋brk=0, 
    alloc₋brk=0, words₋to₋unity;
   
   int init(__builtin_int_t word₋elems, void * 𝟷₋tile);
   int init(ᵐᵃᵡ𝟺kb₋etiolate * 𝗇₋tiles);
   
   int 𝟷₋tile₋copy₋include(__builtin_int_t words, __builtin_uint_t * Ɀ); /* ⬷ for use inside irq 
 when one of two dma buffers are full 𝘦․𝘨 'B-buffer-full-irq' and for oversampled/averaged 
 value on pic32mzda read from ADCFLTRx.FLTRDATA<15:0> 𝘪․𝘦 bit 15 - bit 0. */
   int n₋tile₋copy₋include(unsigned expeditionary, __builtin_int_t words, __builtin_uint_t * Ɀ);
   int shiftout(__builtin_int_t words);
   int 𝟷₋tile₋fifo₋pop(__builtin_int_t words, void (^succumbs₋𝟷)(__builtin_uint_t * bottom₋elem));
   int etoliate₋enfoil(unsigned expeditionary, __builtin_int_t augment₋﹟);
   int n₋tile₋fifo₋pop(__builtin_int_t words, void (^many₋𝟺kb₋etiolates)(__builtin_int_t tot, __builtin_int_t ﹟, __builtin_uint_t * bottom₋elem));
   /* ⬷ a․𝘬․a `structure-preserving-n₋tile₋fifo₋pop`. */
};

bool Empty(const fifo& q);
__builtin_uint_t * 𝟷₋tile₋Deref(__builtin_int_t δ, const fifo& q);
__builtin_uint_t * n₋tile₋Deref(__builtin_int_t δ, const fifo& q);
__builtin_uint_t * n₋tile₋Bank(__builtin_int_t idx, const fifo& q);
__builtin_uint_t * n₋tile₋Chronologic(const fifo& q, __builtin_int_t idx);
__builtin_uint_t * n₋tile₋Youngest(const fifo& q);
__builtin_uint_t * n₋tile₋Oldest(const fifo& q);
enum class fifo₋flavor { allinorder, latest /* 𝘊․𝘧 'randomized' and 'random accessible'. */ };
int 𝟷₋tile₋Retrospect(fifo₋flavor f, const fifo& q, __builtin_uint_t * t, __builtin_uint_t * t₋₁);

/* template <typename E> struct 🅨₋Arrange {
virtual int copy₋include(int count, E * Ɀ) = 0;
virtual int shiftout(int count) = 0; };
template <typename E> struct 🅨₋arrange₋X { virtual int reform(int segments) = 0; / * a․𝘬․a `amend` and `augment`. * / };
enum Tape₋ctrl { stop, reverse, forward }; template struct <typename E, int SEL=3> 🅨₋tape₋N {
int read(int bytes, void (^intervals⁺ʳ⁻ᵚ₋𝟷₋𝘯)(int actual, uint8_t * now₋readable, Tape₋ctrl &next));
int write(int bytes, void (^intervals⁻ʳ⁺ᵚ₋𝟷₋𝘯)(int avail, uint8_t * later₋written, bool last)); }; */ 

inline int n₋tile₋apriori(unsigned expeditionary, __builtin_int_t alloca̲t̲ed₋count, 
  __builtin_int_t maximum₋count, fifo& 🅠, int size) {
   bool dummy₋negative; __builtin_int_t ℤ₁, modula₁, ℤ₂, modula₂, 
   alloced₋bytes=alloca̲t̲ed₋count*size, max₋bytes=maximum₋count*size;
   extern int fractions(__builtin_int_t num, __builtin_int_t denom, 
    __builtin_int_t &ℤ, __builtin_int_t &modula, bool &sum₋negative);
    __builtin_int_t num = SystemInfoPagesize();
   if (alloca̲t̲ed₋count > maximum₋count) { return -1; }
   if (fractions(alloca̲t̲ed₋count,num,ℤ₁,modula₁,dummy₋negative)) { return -2; }
   if (fractions(max₋bytes,num,ℤ₂,modula₂,dummy₋negative)) { return -3; }
   __builtin_int_t maximum₋﹟ = (modula₂ ? 1 : 0) + ℤ₂;
   __builtin_int_t allocated₋﹟ = (modula₁ ? 1 : 0) + ℤ₁;
   void * 𝟺kbframes[maximum₋﹟]; /* ⬷ Not copied 'element-for-element'! */
   ᵐᵃᵡ𝟺kb₋etiolate 𝗇₋tiles { maximum₋﹟, 𝟺kbframes };
   if (🅠.init(&𝗇₋tiles)) { return -4; }
   if (🅠.etoliate₋enfoil(expeditionary,allocated₋﹟)) { return -5; }
   return 0;
}

template <typename E> struct n₋tile₋fifo { fifo 🅠; 
   int apriori₋init(unsigned expeditionary, __builtin_int_t alloca̲t̲ed₋count, 
    __builtin_int_t maximum₋count) { return n₋tile₋apriori(expeditionary, 
    alloca̲t̲ed₋count,maximum₋count,🅠,sizeof(E)); }
   int copy₋include(unsigned expeditionary, __builtin_int_t count, E * Ɀ) { 
    return 🅠.n₋tile₋copy₋include(expeditionary,count,(__builtin_uint_t *)Ɀ); }
   int pop(__builtin_int_t count, void (^many₋𝟺kb₋etiolates)(__builtin_int_t tot, 
   __builtin_int_t ﹟, E * bottom₋elem)) { auto chim = ^(__builtin_int_t tot, 
   __builtin_int_t ﹟, __builtin_uint_t * bottom₋elem) { 
     many₋𝟺kb₋etiolates(tot,﹟,(E *)bottom₋elem); };
     return 🅠.n₋tile₋fifo₋pop(count,chim); }
}; /* a․𝘬․a `vector`. */

template <typename E> struct 𝟷₋tile₋fifo { fifo 🅠; 
  int init(__builtin_int_t count, void * 𝟷₋tile) { return 🅠.init(count,𝟷₋tile); }
  int copy₋include(int count, E * Ɀ) { return 🅠.𝟷₋tile₋copy₋include(count,(__builtin_uint_t *)Ɀ); }
  int pop(int count, void (^𝟷₋succumb)(E * bottom₋elem)) {
    auto chim = ^(__builtin_uint_t * bottom₋elem) { 𝟷₋succumb((E *)bottom₋elem); };
    return 🅠.𝟷₋tile₋fifo₋pop(count,chim);
  }
};

template <typename E> using Knots¹ᵈ = n₋tile₋fifo<E>;

