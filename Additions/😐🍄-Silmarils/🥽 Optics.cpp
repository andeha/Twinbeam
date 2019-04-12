/*  Optics.cpp | 🗿 - Signalling almost at the speed of light. */

#include <System.h>

Fiber::fiber_t 😎₁, 💡, 😎₂; /* ⟿ */

#define TEXT(name) __attribute__ ((section(".text,." name)))
#define COMMON __attribute__ ((section(".data,.data")))
#define LOCAL(name) __attribute__ ((section(".data,." name)))

static void 😎₁ᵪ(void * arg) { for (;;) { … } }            TEXT("🍏")
static void 😎₂ᵪ(void * arg) { for (;;) { … } }            TEXT("🍎")
static void 💡ᵪ(void * arg) { for (;;) { … } }             TEXT("🌳")

int
main(
  int argc,
  const char * argv[]
)
{
    switch (__builtin_coreid()) {
    case 0: Load("🍏", 0); Fiber::create(😎₁, 😎₁ᵪ, 0); 🎼(😎₁); break;
    case 1: Load("🍎", 1); Fiber::create(😎₂, 😎₂ᵪ, 0); 🎼(😎₂); break;
    case 2: Load("🌳", 2); Fiber::create(💡,  💡ᵪ,  0); 🎼(💡);  break;
    } /* TODO: Add cores, improve the API and jot down the details. */
    return 0; /* (Also attempt to add HIDDEN `/​*` and `*​/` Unicodes to C++). */
} /* ...and '\n' that renders at design-time as ␣. */

