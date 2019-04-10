/*  Cordal.cpp | 📚 — Accessing elements 𝑖𝑛𝑠𝑖𝑑𝑒 a read-only sequence. */

#include <Twinbeam.h>

/* clang++ -I ../.. --std=c++2a -o Cordal -Wl,-map,Cordal.map Cordal.cpp
 objdump -disassemble Cordal
 od -x ./Cordal
 objdump -section-headers Cordal */

template <typename T>
struct Cordal { /* A․𝘬․𝘢 𝚅𝚎𝚌𝚝𝚘𝚛ᵚ⁻. */
   __builtin_int_t bytes; const T * start;
   Cordal(std::initializer_list<T> l) { start = l.begin(); bytes = l.size(); }
   const T& operator[](__builtin_int_t idx) const { return const_cast<T&>(*(start + idx)); }
}; /* 0P: Points into /pertaining/ the .𝚛𝚘𝚍𝚊𝚝𝚊 segment that hypothetically is copied in `start` at startup. */

#define READONLY __attribute__ ((section(".rodata,.rodata")))

int constants₁[] READONLY = { 1, 2, 3 };

/* The symbol `constants₁` references `{ 1,2,3 }` pertaining ․𝚛𝚘𝚍𝚊𝚝𝚊. */

#pragma clang section bss="myBSS" data="myData" rodata="rodata" text="myText"

int constants₂[] READONLY = { 3, 4, 1 };

// See comment above, ≡.

#pragma clang section bss="" data="" text="" rodata=""

int
main(
  int argc,
  const char * argv[]
)
{
    int y₁₁=constants₁[0], y₁₂=constants₁[1], y₁₃=constants₁[2];
    printf("Attribute: %d, %d, %d\n", y₁₁, y₁₂, y₁₃);
    int y₂₁=constants₂[0], y₂₂=constants₂[1], y₂₃=constants₂[2];
    printf("Pragma: %d, %d, %d\n", y₂₁, y₂₂, y₂₃);
    return 0;
}
