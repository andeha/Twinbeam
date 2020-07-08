/*  fifo.h | A duplicate required in 'additions'. (TO-BE-PUBLISHED) */

struct ᵐᵃᵡ𝟺kb₋etiolate { __builtin_int_t ﹟; void **𝟺kbtiles; }; /* a․𝘬․a `day-sy`. */

struct fifo { __builtin_int_t E₋max, brk=0, count=0; __builtin_uint_t * 𝟷₋tile; 
   
   /* ...and for segmented fifos possibly with padding at end: */
   ᵐᵃᵡ𝟺kb₋etiolate * 𝗇₋tiles; short tile₋brk=0, elem₋brk=0, alloc₋brk=0;
   
   int init(__builtin_int_t E₋elems, void * 𝟷₋tile);
   int init(ᵐᵃᵡ𝟺kb₋etiolate * 𝗇₋tiles);
   
   int 𝟷₋tile₋copy₋include(__builtin_int_t count, __builtin_uint_t * Ɀ); /* ⬷ for use inside irq 
 when one of two dma buffers are full 𝘦․𝘨 'B-buffer-full-irq' and for oversampled/averaged 
 value on pic32mzda read from ADCFLTRx.FLTRDATA<15:0> 𝘪․𝘦 bit 15 - bit 0. */
   int n₋tile₋copy₋include(unsigned expeditionary, __builtin_int_t count, __builtin_uint_t * Ɀ);
   int shiftout(__builtin_int_t elems);
   int 𝟷₋tile₋fifo₋pop(__builtin_int_t elems, void (^𝟷₋succumb)(__builtin_uint_t * bottom₋elem));
   int etoliate₋enfoil(unsigned expeditionary, __builtin_int_t augment₋﹟);
   int n₋tile₋fifo₋pop(__builtin_int_t elems, void (^many₋𝟺kbetiolates)(__builtin_int_t tot, __builtin_int_t ﹟, void * bottom₋elem));
   /* ⬷ a․𝘬․a `structure-preserving-n₋tile₋fifo₋pop`. */
};

/* template <typename E> struct 𝟷₋tile₋fifo { fifo f; 
  int init(__builtin_int_t E₋elems, void * 𝟷₋tile) { return f.init(E₋elems,𝟷₋tile); }
  int copy₋include(int count, __builtin_uint_t * Ɀ) { return f.𝟷₋tile₋copy₋include(count,Ɀ); }
  int pop(int elems, void (^𝟷₋succumb)(__builtin_uint_t * bottom₋elem)) { return f.𝟷₋tile₋fifo₋pop(elems,𝟷₋succumb); }
}; */

bool Empty(const fifo& q);
__builtin_uint_t * 𝟷₋tile₋Deref(__builtin_int_t δ, const fifo& q);
__builtin_uint_t * n₋tile₋Deref(__builtin_uint_t δ, const fifo& q);
__builtin_uint_t * n₋tile₋Bank(__builtin_int_t idx, const fifo& q);
__builtin_uint_t * n₋tile₋Chronologic(const fifo& q, __builtin_int_t idx);
__builtin_uint_t * n₋tile₋Youngest(const fifo& q);
__builtin_uint_t * n₋tile₋Oldest(const fifo& q);
enum class fifo₋flavor { allinorder, latest /* 𝘤․𝘧 'randomized'. */ };
int 𝟷₋tile₋Retrospect(fifo₋flavor f, const fifo& q, __builtin_uint_t * t, __builtin_uint_t * t₋₁);

template <typename E> struct vector { fifo f; 
  int apriori₋init(unsigned expeditionary, __builtin_int_t alloced₋count, __builtin_int_t max₋count) {
    bool sum₋negative₁, sum₋negative₂; __builtin_int_t ℤ₁, modula₁, ℤ₂, modula₂, 
     alloced₋bytes=alloced₋count*sizeof(E), max₋bytes=max₋count*sizeof(E);
    extern int fractions(__builtin_int_t num, __builtin_int_t denom, 
     __builtin_int_t &ℤ, __builtin_int_t &modula, bool &sum₋negative);
    __builtin_int_t num = SystemInfoPagesize();
    if (alloced₋count > max₋count) { return -1; }
    if (fractions(alloced₋bytes,num,ℤ₁,modula₁,sum₋negative₁)) { return -2; }
    if (fractions(max₋bytes,num,ℤ₂,modula₂,sum₋negative₂)) { return -3; }
    __builtin_int_t max₋﹟₂ = (modula₂ ? 1 : 0) + ℤ₂;
    __builtin_int_t alloced₋﹟₁ = (modula₁ ? 1 : 0) + ℤ₁;
    void * 𝟺kbframes[max₋﹟₂]; /* ⬷ Not copied 'element-for-element'! */
    ᵐᵃᵡ𝟺kb₋etiolate 𝗇₋tiles { max₋﹟₂, 𝟺kbframes };
    if (unassign₋init(&𝗇₋tiles)) { return -4; }
    if (f.etoliate₋enfoil(expeditionary,alloced₋﹟₁)) { return -5; }
    return 0;
  }
  int unassign₋init(ᵐᵃᵡ𝟺kb₋etiolate * 𝗇₋tiles) { return f.init(𝗇₋tiles); }
  int copy₋include(__builtin_int_t count, __builtin_uint_t * Ɀ) { return f.n₋tile₋copy₋include(count,Ɀ); }
  int pop(__builtin_int_t elems, void (^many₋etiolates)(__builtin_int_t tot, __builtin_int_t ﹟, void * bottom₋elem)) 
  { return f.n₋tile₋fifo₋pop(elems, many₋etiolates); }
}; /* a․𝘬․a `n₋tile₋fifo`. */

