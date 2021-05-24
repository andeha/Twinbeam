/*  Fossilate.h | persisted and not preserved. */

#ifndef __FOSSILATE_H
#define __FOSSILATE_H

/* 64 bits on x86_64 as well as on Mips32.
typedef unsigned long long  uint64_t;
typedef long long           int64_t; */

#ifdef  __mips__
typedef unsigned long       __builtin_uint_t;
typedef long                __builtin_int_t;
#elif defined __x86_64__
typedef unsigned long long  __builtin_uint_t;
typedef long long           __builtin_int_t;
#endif

/* extern ENCRYPTED "Utf-8✕json" struct "myTuple" Pair { int a; int b; } foo() { return { 0, 0 }; } */

/* ONETIMEPAD */ typedef struct Fossilate FINAL {
    /* DISJUNCT */ union Value {
        /* ...Interesting. FINAL below often                        ☜😐🔅¹ */
        struct { __builtin_int_t tetras; char32_t * unicodes; } machineString; /* ⬷ Not stored in SI™. */
        const char *eightbitCString; /* ⬷ still zero-terminated. */
        __builtin_uint_t bitmap;
        double real;
        typedef struct Reference {
            void *p;
            struct { __builtin_int_t tetras; char32_t *unicodes; } canonizedTypename;
        } Reference;
    } value;
    __builtin_int_t kind; /* ∈ [0, ⃨,k-1] */
    Fossilate *optUnit;
    struct { __builtin_int_t tetras; char32_t *unicodes; } optUnitNameOrIdent;
    /* ↸ But not neccessarily FINAL here...                         ☜😐🔅² */
} Fossilate /* == {
  Content {
    machineString,
    eightbitCString,
    base,
    bitmap,
    value,
    {
        canonizedTypename,
        p
    },
    kind,
    optUnit,
    nameOrIdent,
    this } */ ; /* ⬷ ⚠️ Struct 'Fossilate' did recently contain a 'this' pointer but now 
      contains an ⚱️. Optional signature, i.e. SHA1 last 64 bits, an xor with a key and 
      then xor back has not yet been computed. */

/* 💀🎤😐: 🎲⤣ ≅ */

struct Envelop { uint8_t utf8Address[4]; Fossilate content; };

/* Overridable prepacked lambdas: */
DISORDERABLE extern void (^ᵗᵚⁱⁿᵝᵉᵃᵐInit)();
DISORDERABLE extern void (^Putₒ)(char8_t * u8s, __builtin_int_t bytes);
DISORDERABLE extern void (^Trace₁)(char8_t * u8s, __builtin_int_t bytes);
DISORDERABLE extern void (^Trace₂)(char8_t * u8s, __builtin_int_t bytes);
extern 𝟄₋int₁ Reciever(int program₋frequency, void (^effect₋regulation₋done)(
 char32_t unicode, bool &stop)); /* ⬷ a․𝘬․a Viterbi and Capital. */
/* DISORDERABLE extern void (^Reciever)(void (*isr)(Fiber::fiber_t * self)); */
/* DISORDERABLE extern void (^📡 /​*♬*​/)(Chronology::relative t, const 
 Modulation::Variat& V, Fixpoint::Q1615 * fc, Fixpoint::Q1615 * fs); */
DISORDERABLE extern void (^SetPixelAA)(int x, int y, long err);
/* DISORDERABLE extern int (^InitiateMesmerization)(Chronology::instant t, float 
 version, void (^videoᵐᵒᵈ¹⁻³)(int x, int y, long err), void (^audio)(Q79 latency, 
 int chnls, uint16_t * RtoL)); */
#ifdef __mips__
DISORDERABLE extern void (^TuneOscillator)(int8_t signandfivebits);
DISORDERABLE extern void (^InteractivelySetChronometer)(unsigned& y, unsigned& M,
  unsigned& d, unsigned& h, unsigned& m, unsigned& s, uint32_t& key1,
  uint32_t& key2, unsigned& tuner, bool& rollback); 
/* ⬷ using an oscilloscope, measure the RTCC pin. */
DISORDERABLE extern void (^AdjustChronometer)(int16_t signAndNinebits);
#endif
DISORDERABLE extern int (^Resolve𝟷Or𝙽Reflectionᴸ)(Unicodes pathᵚ, void (^final)(
  const char * canonicalUtf8Regular𝘖rLinkpath)) /* -> int */;
/* ⬷ non-overridable mandatory prepacked lambdas include `Alloc`, `LocalNow`, `RandomInteger` 
 and `Fallow`.  See --<Fossilate.cpp> and --<llvm-rt3.cpp> for details. */
#endif
