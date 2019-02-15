
#include <Twinbeam.h>

struct µProcˢ { Octa aux, acc; bool overflow; };

/* Programmer-facing abstractions are below given in monospace. */

enum { 𝚣𝚎𝚛𝚘, 𝚛𝟷, 𝚛𝟸, 𝚛𝟹, 𝚛𝟺, 𝚛𝟻, 𝚛𝟼, 𝚛𝚊𝚡, 𝚌𝚜𝟶, 𝚌𝚜𝟷, 𝚌𝚜𝟸, 𝚌𝚜𝟹,
  𝚊𝚌𝚌𝟹𝚑𝚒, 𝚊𝚌𝚌𝟹𝚕𝚘, 𝚊𝚌𝚌𝟸𝚑𝚒, 𝚊𝚌𝚌𝟸𝚕𝚘, 𝚊𝚌𝚌𝟷𝚑𝚒, 𝚊𝚌𝚌𝟷𝚕𝚘, 𝚊𝚌𝚌𝟶𝚑𝚒, 𝚊𝚌𝚌𝟶𝚕𝚘 };

BITMASK (uint8_t) { 𝚛𝚎𝚐𝚜_𝚘𝚟𝚎𝚛𝚏𝚕𝚘𝚠 = 0b1<<3, 𝚛𝚎𝚐𝚜_𝚌𝚊𝚛𝚛𝚢ₒ = 0b1<<2, 𝚛𝚎𝚐𝚜_𝚌𝚊𝚛𝚛𝚢ᵢ =
  0b1<<1, 𝚛𝚎𝚐𝚜_𝚣𝚎𝚛𝚘 = 0b1<<0 };

union Register { __uint128_t u; __int128_t s; uint64_t o[2]; uint32_t
  t[4]; uint16_t h[8]; uint8_t b[16]; };

struct Registerset { uint64_t 𝚏𝚙, 𝚜𝚙; Register gprs[𝚊𝚌𝚌𝟶𝚕𝚘+1], 𝚏𝚕𝚊𝚐𝚜; };

BITMASK (uint8_t) { 𝚝𝚊𝚙_𝚘𝚗 = 0b1<<3, 𝚝𝚛𝚊𝚌𝚎_𝚘𝚗 = 0b1<<1, 𝚜𝚝𝚎𝚙_𝚘𝚗 = 0b1<<0 };

struct µProcᵖ { uint64_t 𝚙𝚌; void (*irq)(); uint32_t 𝚍𝚎𝚋𝚞𝚐; uint8_t set;
  Registerset regs[7]; };

typedef short gpr;

enum 𝙵𝚕𝚊𝚟𝚘𝚛 { 𝙽𝙴𝚀, 𝙴𝚀, 𝙻𝚃𝙴𝚀, 𝙶𝚃𝙴𝚀, 𝙶𝚃, 𝙻𝚃 };
enum 𝙶𝚛𝚊𝚗𝚞𝚕 { 𝟷𝟸𝟾, 𝟼𝟺, 𝟹𝟸, 𝟷𝟼, 𝟾 };

namespace Op {

extern void (^𝚒𝚖𝚖𝚎𝚍𝚒𝚊𝚝𝚎)(__uint128_t imm, gpr r₌);
extern void (^👉)(gpr r, gpr r₌);
extern void (^👉𝚕𝚛𝚒)(int16_t r_offset, gpr r, gpr r₌);
extern void (^👉𝚜𝚛𝚒)(gpr r, gpr r₌, int16_t r₌_offset);
extern void (^𝙽𝙾𝚃)(gpr r, gpr r₌);
extern void (^𝙰𝙽𝙳)(gpr r₁, gpr r₂, gpr r₌);
extern void (^𝙾𝚁)(gpr r₁, gpr r₂, gpr r₌);
extern void (^𝚇𝙾𝚁)(gpr r₁, gpr r₂, gpr r₌);
extern void (^𝛥𝚗𝚘𝚠)(int16_t offset);
extern void (^𝚋𝚛𝚊𝚗𝚌𝚑)(gpr r₁, gpr r₂, int16_t offset, 𝙵𝚕𝚊𝚟𝚘𝚛 f);
extern void (^𝚗𝚘𝚠)(int64_t loc);
extern void (^𝚛𝚎𝚙𝚕𝚒𝚌𝚊𝚝𝚎₁₆)(uint8_t eightbits, gpr r₌);
extern void (^𝚍𝚎𝚛𝚎𝚏₁₆)(const uint8_t *p, gpr r_idx, bool downwards, gpr r₌);
extern void (^𝚋𝚒𝚝𝚜𝚎𝚕𝚎𝚌𝚝)(gpr T, gpr F, gpr mask, gpr r₌);
extern void (^𝚙𝚒𝚌𝚔)(gpr T, gpr F, gpr cond, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚜𝚑𝚒𝚏𝚝_𝚕)(gpr x, gpr n, 𝙶𝚛𝚊𝚗𝚞𝚕 g);
extern void (^𝚜𝚑𝚒𝚏𝚝_𝚛)(gpr x, gpr n, bool arith, 𝙶𝚛𝚊𝚗𝚞𝚕 g);
extern void (^𝟸𝚌𝚘𝚖𝚙𝚕)(gpr r, 𝙶𝚛𝚊𝚗𝚞𝚕 g);
extern void (^𝚏𝚖̲𝚊𝚄ℚ𝟽)(gpr r₁, gpr r₂, gpr r₌, void (^𝚍𝚒𝚍𝙾𝚟𝚎𝚛𝚏𝚕𝚘𝚠)()); /* 0 ≤ x ≤ (2ⁿ - 1)/2ⁿ */
extern void (^𝚑𝚜𝚞𝚖𝚄ℚ7)(gpr r₁, gpr r₌); // [ x0y0 + x1y1, x2y2 + x3y3, x4y4 + x5y5, x6y6 + x7y7 ]
extern void (^𝚏𝚖̲𝚊ℚ𝟷𝟻)(gpr r₁, gpr r₂, gpr r₌, void (^𝚍𝚒𝚍𝙾𝚟𝚎𝚛𝚏𝚕𝚘𝚠)()); /* -1 ≤ x ≤ 1 - 1/2¹⁵ */
extern void (^𝚏𝚖̲𝚊ℤ₆₄₍𝚖𝚘𝚍𝟸⁶³₎except𝚄𝙼𝙰𝚇)(gpr 𝚛₁, gpr 𝚛₂, gpr rʰ, gpr rˡ, void (^𝚍𝚒𝚍𝙾𝚟𝚎𝚛𝚏𝚕𝚘𝚠)());
extern void (^𝚗𝚎𝚐𝚊𝚝𝚎)(gpr r, gpr neg, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚛𝚎𝚌𝚒𝚙𝚛𝚘𝚌)(gpr r, gpr inv, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌, void (^𝚍𝚒𝚍𝙾𝚟𝚎𝚛𝚏𝚕𝚘𝚠)()); /* IEEE-754, i.e simd_tᵦ. */
extern void (^𝚌𝚝𝚣)(gpr r, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚌𝚕𝚣)(gpr r, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚎𝚡𝚝)(gpr r, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚒𝚗𝚜)(gpr r, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚙𝚒𝚗𝚌𝚎)(gpr r, 𝙶𝚛𝚊𝚗𝚞𝚕 g, gpr r₌);
extern void (^𝚛𝚍𝚙𝚐𝚙𝚛)(gpr r_src_prev, gpr r_dst_curr);
extern void (^𝚜𝚝𝚊𝚛𝚝)();
extern void (^𝚌𝚘𝚖𝚖𝚒𝚝)();
extern void (^𝚊𝚋𝚘𝚛𝚝)();
extern void (^𝚛𝚎𝚐𝚜𝚗𝚊𝚙)(gpr r);
extern void (^𝚖𝚍𝚌)(); /* Enable debugging */
extern void (^𝚖𝚊𝚌)(); /* Disable debugging */
extern void (^𝚜𝚑𝚊𝚍𝚘𝚠)(uint8_t number);

}
