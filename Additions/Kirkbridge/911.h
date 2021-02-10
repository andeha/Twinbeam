/*  911.h | A correctly wired processor. */

#include <Twinbeam.h>

#pragma mark - Programmer-facing abstractions

struct serial₋µProc { Octa aux, acc; bool overflow; }; typedef uint32_t vaddr; 

enum { 𝘇𝗲𝗿𝗼₋, 𝘇𝗲𝗿𝗼₊, 𝗿𝟭, 𝗿𝟮, 𝗿𝟯, 𝗿𝟰, 𝗿𝟱, 𝗿𝟲, 𝗿𝗮𝘅, 𝗰𝘀𝟬, 𝗰𝘀𝟭, 𝗰𝘀𝟮, 𝗰𝘀𝟯, 𝗮𝗰𝗰𝟯𝗵𝗶, 
  𝗮𝗰𝗰𝟯𝗹𝗼, 𝗮𝗰𝗰𝟮𝗵𝗶, 𝗮𝗰𝗰𝟮𝗹𝗼, 𝗮𝗰𝗰𝟭𝗵𝗶, 𝗮𝗰𝗰𝟭𝗹𝗼, 𝗮𝗰𝗰𝟬𝗵𝗶, 𝗮𝗰𝗰𝟬𝗹𝗼, 𝗻𝗲𝘃𝗲𝗿 }; /* 𝘇𝗲𝗿𝗼₋ = 𝗭𝗺𝗶𝗻 + 1 = -2^(bits-1). */

BITMASK (uint8_t) { regs₋overflow = 0b1<<3, regs₋carryₒ = 0b1<<2, regs₋carryᵢ =
  0b1<<1, regs₋zero = 0b1<<0 };

union Register { 
  __uint128_t 𝘜nsigned; __int128_t 𝘚igned; uint64_t 𝘖cta[2];
  uint32_t 𝘛etra[4]; uint16_t 𝘏alf[8]; uint8_t 𝘉yte[16];
}; /* ⬷ Type __int128_t solely for Ieee754 a․𝘬․a `double`. */

struct Registers { vaddr 𝗳𝗽, 𝘀𝗽; Register gprs[𝗮𝗰𝗰𝟬𝗹𝗼 + 1], uint8_t 𝗳𝗹𝗮𝗴𝘀; };

#pragma mark - masked from general public:

BITMASK (uint32_t) { 𝚝𝚊𝚙₋𝚘𝚗 = 0b1<<3, 𝚝𝚛𝚊𝚌𝚎₋𝚘𝚗 = 0b1<<1, 𝚜𝚝𝚎𝚙₋𝚘𝚗 = 0b1<<0 }; /* 𝚍𝚎𝚋𝚞𝚐 */

typedef void (*Proc₁)(void *);

struct parallel₋µProc { vaddr pc; Proc₁ irq, nothing𝘖rNull; uint8_t set, prev; 
  Registers regs[7]; uint32_t 𝚍𝚎𝚋𝚞𝚐; Proc₁ 𝘀𝗵𝗲𝗿𝗶𝗳𝗳; }; /* ⬷ a․𝘬․a µProcᵖ. */

typedef short gpr;

enum 𝗚𝗿𝗮𝗻𝘂𝗹 { 𝟷𝟸𝟾, 𝟼𝟺, 𝟹𝟸, 𝟷𝟼, 𝟾 }; /* ⬷ a․𝘬․a One-itis. */
enum 𝗗𝗶𝗳𝗳𝗲𝗿𝗲𝗻𝘁 { 𝖭𝖤𝖰, 𝖤𝖰, 𝖫𝖳𝖤𝖰, 𝖦𝖳𝖤𝖰, 𝖦𝖳, 𝖫𝖳 }; /* ⬷ Given conveniences 'signed', 'unsigned' and 'ieee₋754'. */
enum class 𝗦𝗼𝗿𝘁 { unsigned₋fixed, signed₋fixed, scalar₋ieee754₋aligned₋right, ieee754 };
/* ⬷ Valids: 𝗗𝗶𝗳𝗳𝗲𝗿𝗲𝗻𝘁 × 𝗦𝗼𝗿𝘁, except { 𝖤𝖰, 𝖫𝖳𝖤𝖰, 𝖦𝖳𝖤𝖰 } x 𝖥. */
enum class 𝗦𝗲𝗰𝘁𝗼𝗿𝘀 { 𝟸, 𝟺, 𝟾 }; /* ⬷ a․𝘬․a ccw₋sectors. */

#pragma mark - unbranch 128-bits:

extern void (^𝗂𝗆𝗆𝖾𝖽𝗂𝖺𝗍𝖾)(__uint128_t imm, gpr r₌);
extern void (^👉)(gpr r, gpr r₌);
extern void (^𝖭𝖮𝖳)(gpr r, gpr r₌);
extern void (^𝖠𝖭𝖣)(gpr r₁, gpr r₂, gpr r₌);
extern void (^𝖮𝖱)(gpr r₁, gpr r₂, gpr r₌);
extern void (^𝖷𝖮𝖱)(gpr r₁, gpr r₂, gpr r₌);
extern void (^𝛥𝗇𝗈𝗐)(int32_t offset); /* ⬷ references (af₋ter alt․ /before/) operator + tetra. */
extern void (^𝗌𝗂𝗀𝗇𝖾𝗑𝗍𝗈)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 from, 𝗚𝗿𝗮𝗻𝘂𝗹 to, void (^overflow)(void *) /* = parallel₋µProc::nothing𝘖rNull. */);
extern void (^𝖻𝗋𝖺𝗇𝖼𝗁)(gpr r₁, gpr r₂, int16_t offset, 𝗦𝗼𝗿𝘁 𝗧, 𝗗𝗶𝗳𝗳𝗲𝗿𝗲𝗻𝘁 f, 𝗚𝗿𝗮𝗻𝘂𝗹 g); /* Operation follows by /off₋set/. */
extern void (^𝗀𝗈𝖺𝗍)(vaddr absolute); /* ⬷ Dereferences application base and one tetra. */
extern void (^𝗌𝗂𝗆𝖽₋𝗂𝗇𝗂𝗍₁₆)(uint8_t eightbits, gpr r₌); /* ⬷ 𝘊․𝘧 𝗌𝗂𝗆𝖽₋𝗂𝗇𝗂𝗍₈, 𝗌𝗂𝗆𝖽₋𝗂𝗇𝗂𝗍₄ and 𝗌𝗂𝗆𝖽₋𝗂𝗇𝗂𝗍₂. */

#pragma mark - lookup:

/* ⤐ referencing and dereferencing 'index register' and ∓ alt․ ± tetra ⤐ */
enum class 𝗢𝗿𝗶𝗴𝗼 { upperleft, middle, lowerleft };
extern void (^𝟸ᵈ₋𝖽𝖾𝗋𝖾𝖿)(𝗢𝗿𝗶𝗴𝗼 o, const void * p, 𝗦𝗲𝗰𝘁𝗼𝗿𝘀 s, int dirₓ, gpr signed₋r₋idx, gpr signed₋r₋steps, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r);
extern void (^𝟷ᵈ₋𝖽𝖾𝗋𝖾𝖿)(const void * p, gpr signed₋r₋idx, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r);
extern void (^𝟷ᵈ₋𝗆𝖾𝗆𝗋𝖾𝖿)(const void * p, gpr signed₋r₋offsets, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
extern void (^𝟸ᵈ₋𝗆𝖾𝗆𝗋𝖾𝖿)(𝗢𝗿𝗶𝗴𝗼 o, const void * p, 𝗦𝗲𝗰𝘁𝗼𝗿𝘀 s, int dirₓ, gpr signed₋r₋offsets, gpr signed₋r₋steps, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
/* ⬷ Two memory cells possibly four address decoders. */
/* ⬷ 4k did imply 2³² offset or twice the framebuffer storing img and img⊾. */
/* extern void (^👉𝚕𝚛𝚒)(int16_t r₋offset, gpr r, gpr r₌);
extern void (^👉𝚜𝚛𝚒)(gpr r, gpr r₌, int16_t r₌offset); */
extern void (^𝖻𝗂𝗍𝗌𝖾𝗅𝖾𝖼𝗍)(gpr T, gpr F, gpr mask, gpr r₌);
extern void (^𝗉𝗂𝖼𝗄)(gpr T, gpr F, gpr cond, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
extern void (^𝗅𝖾𝖿𝗍₋𝗌𝗁𝗂𝖿𝗍)(gpr x, gpr n, 𝗚𝗿𝗮𝗻𝘂𝗹 g);
extern void (^𝗋𝗂𝗀𝗁𝗍₋𝗌𝗁𝗂𝖿𝗍)(gpr x, gpr n, int arith, 𝗚𝗿𝗮𝗻𝘂𝗹 g);
extern void (^𝟸₋𝖼𝗈𝗆𝗉𝗅)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 g);
extern void (^𝖿𝗆𝖺₋ℚ𝟽)(gpr r₁, gpr r₂, gpr r₌, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */); /* -1 ≤ x ≤ 1 - 1/2⁷ */
extern void (^𝖿𝗆𝖺₋𝚄ℚ𝟽)(gpr r₁, gpr r₂, gpr r₌, void (^carry₋raised)(void *) /* = µProcᵖ::nothing𝘖rNull */); /* 0 ≤ x ≤ (2ⁿ - 1)/2ⁿ */
extern void (^𝗁𝗌𝗎𝗆₋ℚ7)(gpr r₁, gpr rˡ, gpr rʰ); /* ⬷ [ x0y0 + x1y1, x2y2 + x3y3, x4y4 + x5y5, x6y6 + x7y7 ]. */
/* extern void (^𝚜𝚌𝚊𝚕𝚊𝚛ℚ7)(gpr r₁, gpr r₂, gpr r₌_slot0, void (^overflow)(void *)); */
// TODO: Change arg1 and arg2 to ref and arg3 to r₌_slot0-15
/* extern void (^𝚜𝚌𝚊𝚕𝚊𝚛ℚ16)(gpr r₁, gpr r₂, gpr r₌_slot0, void (^overflow)(void *)); */ 
// TODO: Change arg1 and arg2 to ref and arg3 to r₌_slot0-15
extern void (^𝖿𝗆̲𝖺₋ℚ𝟷𝟻)(gpr r₁, gpr r₂, gpr r₌, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */); /* -1 ≤ x ≤ 1 - 1/2¹⁵ */
extern void (^𝖿𝗆̲𝖺₋ℤ₆₄₍𝚖𝚘𝚍𝟸⁶³₎𝚠𝚒𝚝𝚑𝚘𝚞𝚝𝚄𝙼𝙰𝚇)(gpr 𝚛₁, gpr 𝚛₂, gpr rʰ, gpr rˡ, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝖿𝗆̲𝖺₋ℝ²)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝗋𝖾𝖼𝗂𝗉𝗋𝗈𝖼)(gpr r, gpr inv, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌); /* ⬷ Ieee754 𝘦․𝘨 simd_tᵦ. */
extern void (^𝗇𝖾𝗀𝖺𝗍𝖾)(gpr r, gpr neg, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌); /* ⬷ alternates sign. */
extern void (^𝗎𝗇𝗌𝗂𝗀𝗇𝖾𝖽₋𝖺𝖽𝖽)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^carry₋raised)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝗌𝗂𝗀𝗇𝖾𝖽₋𝖺𝖽𝖽)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
/* extern void (^𝗌𝗂𝗀𝗇𝖾𝖽₋𝗌𝗎𝖻)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^overflow)(void *) /‍* = µProcᵖ::nothing𝘖rNull *‌/); */
extern void (^𝗌𝖺𝗍𝗎𝗋₋𝖺𝖽𝖽₋𝟸𝟺𝖻𝗂𝗍𝗌)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull (5 chnls) */);
extern void (^𝗋𝖾𝖺𝗹₋𝗆𝗎𝗅)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝖿𝗂𝗑₋𝗆𝗎𝗅)(gpr 𝚛₁, gpr 𝚛₂, gpr rʰ, gpr rˡ, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^overflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝖿𝗂𝗑₋𝖽𝗂𝗏)(gpr 𝚛₁, gpr 𝚛₂, gpr modula, gpr ℕ, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^underflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝗋𝖾𝖺𝗹₋𝖽𝗂𝗏)(gpr 𝚛₁, gpr 𝚛₂, gpr r₌, 𝗦𝗼𝗿𝘁 s, 𝗚𝗿𝗮𝗻𝘂𝗹 g, void (^underflow)(void *) /* = µProcᵖ::nothing𝘖rNull */);
extern void (^𝖼𝗍𝗓)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
extern void (^𝖼𝗅𝗓)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
extern void (^𝖾𝗑𝗍)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
extern void (^𝗂𝗇𝗌)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
extern void (^𝗉𝗂𝗇𝖼𝖾)(gpr r, 𝗚𝗿𝗮𝗻𝘂𝗹 g, gpr r₌);
/* extern void (^𝗌𝗍𝖺𝗋𝗍)();extern void (^𝖼𝗈𝗆𝗆𝗂𝗍)(); extern void (^𝖺𝖻𝗈𝗋𝗍)(); */
extern void (^𝖼𝗋𝗈𝗌𝗌)(vaddr ref₁, vaddr ref₂); /* ⬷ a․𝘬․a deref₋and₋swap. */
extern void (^𝖽𝖾𝖻𝖼)(); /* ⬷ enable step₋on. */
extern void (^𝖽𝖺𝖻𝖼)(); /* ⬷ disable step₋on. */
extern void (^𝗋𝖽𝗉𝗀𝗉𝗋)(gpr r₋src₋prev, gpr r₋dst₋curr); /* See 'MIPS', 'shadow' and context. */
extern void (^𝗌𝗁𝖺𝖽𝗈𝗐)(uint8_t number); /* ⬷ set current register set ∈[0-7]. */
extern void (^𝗌𝗇𝖺𝗉𝗌𝗁𝗈𝗍₁)(gpr r₋loc); /* copies registers, context ∨ debug: 𝚝𝚊𝚙_𝚘𝚗 */
/* extern void (^𝗌𝗇𝖺𝗉𝗌𝗁𝗈𝗍₂₁)(gpr r₋src, gpr r₋dst, __builtin_int_t 𝟺₋byte₋count[]); /​* ⬷ superflous-possibly-overlapping-yet. */
/* extern void (^𝗌𝗇𝖺𝗉𝗌𝗁𝗈𝗍₂₂)(vaddr r₋src, vaddr r₋dst, __builtin_int_t bytes); /​* ⬷ often-non-overlapping. */
extern void (^𝖿𝗂𝗇𝖾𝗉𝗋𝗂𝗇𝗍)(void * base, __builtin_int_t bytes, gpr rˡ, gpr rʰ); /* ⬷ Sha-256. */
/* extern void (^𝚎𝚗𝚌𝚕𝚊𝚟𝚎)(Gpr r₋hash, Gpr r₋count);
extern void (^𝚛𝚎𝚎𝚗𝚌𝚕𝚊𝚟𝚎)(Gpr r₋hash, Gpr r₋count); */

struct Context { Registers snapshot; uint8_t set; };
struct Debug { vaddr 𝚙𝚌; uint8_t set; Context ctx; };

extern void (^𝖽𝖻𝗀₋𝖾𝗊)(__uint128_t x, gpr r);

inline unsigned long long operator "" _º(unsigned long long n) { return n; }

/* …and: */

extern void (^𝖾𝗑𝗉𝗂𝗋𝖾𝖽)(void * x509₋rentalToken); /* ⬷ 𝘐․e expiring content. */


