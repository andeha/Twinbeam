/*  Seashore.cpp | Wrapping and non-wrapping arithmetics and base-2. */

#include <Twinbeam.h>

/* xcrun clang @ccargs_macᵧ² -o Seashore '🥽 Seashore.cpp' ../../Source/llvmʳᵗ³.cpp */

template <int 𝑙𝑜𝑔₂Frames>
struct Framestore { __builtin_int_t 🥈 𝑙𝑜𝑔₂Pages=𝑙𝑜𝑔₂Frames, 
   Pages=0b1<<𝑙𝑜𝑔₂Frames, 
   BytesPerWord=sizeof(__builtin_uint_t), 
   Words=Pages*(SystemInfoPagesize()/BytesPerWord), 
   Idxs=(Pages/BytesPerWord)>>3;
   __builtin_uint_t pages[Words], avails[Idxs];
}; Framestore<9> frames₂; /* ⬷ Pages=512. */

void Reservoir(__builtin_int_t *𝑙𝑜𝑔₂Pages, __builtin_uint_t **pages,  __builtin_uint_t **avails)
{ *𝑙𝑜𝑔₂Pages=frames₂.𝑙𝑜𝑔₂Pages; *pages=frames₂.pages; *avails=frames₂.avails; }

inexorable void InitFrames() { for (int i=0; i<frames₂.Idxs; i++) { frames₂.avails[i]=~0x0; } }
inexorable int Acquire(__builtin_int_t ﹟, void (^each)(void * frame, bool& stop)) { return 
  Acquire𝟷ᵈ(﹟,frames₂.𝑙𝑜𝑔₂Pages,frames₂.pages,frames₂.avails,each); }

int
main(
  int argc,
  const char * argv[]
)
{  __builtin_int_t ﹟=1; 𝑓𝑙𝑢𝑐𝑡𝑢𝑎𝑛𝑡 void * 🔬=NULL; InitFrames();
    if (Acquire(﹟, ^(void * frame, bool& stop) { 🔬=frame; })) { return 1; }
    if (Release𝟷ᵈ(🔬, frames₂.𝑙𝑜𝑔₂Pages, frames₂.pages, frames₂.avails, false)) 
    { print("Error when Release𝟷ᵈ₋₁\n"); }
    
    return 0;
}

/* See also --<🥽 Guggenh.cpp>, --<🥽 Tantal.cpp> and --<🥽 Crunchy.cpp>. */

