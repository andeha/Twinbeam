//
//  Fossilate.cpp
//  Twinbeam Additions
//

#ifndef __FOSSILATE_H
#define __FOSSILATE_H

typedef unsigned long long    __builtin_uint_t;
typedef long long             __builtin_int_t;

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

#endif
