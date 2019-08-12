/* Swaphot.cpp */

#include <Twinbeam.h>
#include <Additions/Additions.h>
#include <pic32rt/mips.hpp>
#include <pic32rt/pic32mz.hpp>
#include <pic32rt/pic32mzda.hpp>

/* The Pic32Mzda has two (unfortunately not three) program areas we can swap between. */

int
main(
  int argc,
  const char * argv[]
)
{
    __builtin_uint_t nvmcon = 🔎𝑀𝑍𝐷𝐴(NVMCON);
    
    if (🐛𝑀𝑍𝐷𝐴(nvmcon,PFSWAP)) { print("lower='Program Flash Bank 2', upper='Program Flash Bank 1'\n"); }
    else { print("lower='Program Flash Bank 1', upper='Program Flash Bank 2'\n"); }
    
	🔧0𝑀𝑍𝐷𝐴(NVMCON,WREN);
    SwapProgram1And2();
    
    return 0;
}

/* See also --<🥽 GotOr¬Got.cpp> */