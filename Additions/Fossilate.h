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
        const char *eightbitCString;
        __builtin_uint_t bitmap;
        double real;
        typedef struct Reference {
            void *p;
            struct { __builtin_int_t tetras; char32_t *unicodes; } canonizedTypename;
        } Reference;
    } value;
    __builtin_int_t kind; // ∈ [0, ⃨,k-1].
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

struct Envelope { uint8_t utf8Address[4]; Fossilate content; };

DISORDERABLE extern void (^Init)();
DISORDERABLE extern void (^Putch)(char utf8);
DISORDERABLE extern uint8_t (^Getch)();
DISORDERABLE extern void (^Put)(char32_t unicode);
DISORDERABLE extern void (^SetPixelAA)(int x, int y, long err);

#endif
