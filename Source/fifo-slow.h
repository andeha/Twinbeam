/*  fifo-slow.h | interrupt may fill and coroutine consume. */

struct fifo { __builtin_uint_t * 𝟷₋tile; 
 __builtin_int_t brk, count, words₋to₋unity; /* ⬷ a․𝘬․a max₋words. */
}; /* ⬷ a․𝘬․a fifoⁱⁿcorp. Three areas where one precomputed area always 
 separates the 'producer' from the 'consumer' enables a - without visual
 fluctuation - 'stable external projection', whereas two areas leads to 
 the need to introduce 'lock' as well as the other contra-tranquistimulantic
 constrains. 'efterhandskonstruktion'/hack. (ret-ro-spect = [stimulu-tranqui-
 jello]). */

EXT₋C int init₋fifo(struct fifo * 🅵, __builtin_int_t words, 
 void * one₋tile);
EXT₋C void one₋tile₋pop(struct fifo * 🅵);
EXT₋C void one₋tile₋shiftout(struct fifo * 🅵, __builtin_int_t words);
/* ⬷ abbrev. 'by-tes' and 'strategy' alt. 'occational'. */
EXT₋C int one₋tile₋empty(struct fifo * 🅵);
EXT₋C int one₋tile₋copy₋include(struct fifo * 🅵, __builtin_int_t ﹟, 
 __builtin_uint_t * words);
EXT₋C __builtin_uint_t * one₋tile₋bank(__builtin_int_t idx, struct fifo * 🅵);
EXT₋C __builtin_uint_t * one₋tile₋chronologic(struct fifo * 🅵, __builtin_int_t idx);
EXT₋C __builtin_uint_t * one₋tile₋youngest(struct fifo * 🅵);
EXT₋C __builtin_uint_t * one₋tile₋oldest(struct fifo * 🅵);
enum fifo₋flavor { fifo₋flavor₋allinorder, fifo₋flavor₋latest };
/* ⬷ 𝘤𝘧. 'random accessible' and randomized. */
EXT₋C int one₋tile₋retrospect(enum fifo₋flavor f, struct fifo * 🅵, 
 __builtin_uint_t * t, __builtin_uint_t * t₋₁);

