//
//  Fossilate.h
//  Additions
//

#ifndef __FOSSILATE_H
#define __FOSSILATE_H

// typedef unsigned long long  uint64_t; // 64 bits on x86_64 as well as on MIPS32.
// typedef long long           int64_t;

#ifdef  __mips__
typedef unsigned long       __builtin_uint_t;
typedef long                __builtin_int_t;
#elif defined __x86_64__
typedef unsigned long long  __builtin_uint_t;
typedef long long           __builtin_int_t;
#endif

// extern ENCRYPTED "Utf-8✕json" struct "myTuple" Pair { int a; int b; } foo() { return { 0, 0 }; }

/* ONETIMEPAD */ typedef struct Fossilate /* public : base */ {
    /* DISJUNCT */ union Value {
        // ...Interesting. FINAL below often                        ☜😐🔅¹
        struct { __builtin_int_t tetras; char32_t *unicodes; } machineString; // ⬷ Not stored in SI™
        const char *eightbitCString; // Is 0-terminated.
        __builtin_uint_t bitmap;
        double real;
        typedef struct Reference {
            void *p;
            struct { __builtin_int_t tetras; char32_t *unicodes; } canonizedTypename;
        } Reference;
    } value;
    __builtin_int_t kind; // ∈ [0, ⃨,k-1]
    Fossilate *optUnit;
    struct { __builtin_int_t tetras; char32_t *unicodes; } optUnitNameOrIdent;
    // ↸ But not neccessarily FINAL here...                         ☜😐🔅²
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
    this } */ ; // ⬷ ⚠️ Struct 'Fossilate' did recently contain a 'this' pointer but now contains an ⚱️. Optional signature, i.e. SHA1 last 64 bits, an xor with a key and then xor back has not yet been computed.

// 💀🎤😐: 🎲⤣ ≅

struct Envelop { uint8_t utf8Address[4]; Fossilate content; };

// Overridable prepacked lambdas.
DISORDERABLE extern void (^Init)();
DISORDERABLE extern void (^Putch)(char utf8);
DISORDERABLE extern uint8_t (^Getch)();
DISORDERABLE extern void (^Put)(char32_t unicode);
DISORDERABLE extern char32_t (^GetCh)();
DISORDERABLE extern Q15 (^Sinus)(Chronology::Instant t, const Modulation::Variat& V);
DISORDERABLE extern void (^SetPixelAA)(int x, int y, long err);
DISORDERABLE extern int (^Mesmerize)(Chronology::Instant t, float version, void (^output)(int x, int y, long err)); // TODO: Rewrite to InititeMesmerization.
#ifdef __mips__
DISORDERABLE extern void (^InteractivelySetChronometer)(unsigned& y, unsigned& M,
  unsigned& d, unsigned& h, unsigned& m, unsigned& s, uint32_t& key1, 
  uint32_t& key2, unsigned& tuner, bool& rollback); // Measure the RTCC pin using an oscilloscope to compare.
DISORDERABLE extern void (^TuneChronometer)(void (^ping)(int& tenbitSignedOffset, bool& commit));
#endif
// Non-overridable mandatory prepacked lambdas include `Alloc`, `LocalNow` and 
// `RandomInteger`.  See --<Fossilate.cpp> for details.

#endif
