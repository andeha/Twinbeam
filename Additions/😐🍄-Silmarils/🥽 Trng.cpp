/*  Trng.cpp | 🎲 - Same size as RDRAND! */

#include <Twinbeam.h>
#include <Additions/Additions.h>

PIC32SYMBOL(MZDA, RNGVER,   0xBF8E6000)
PIC32SYMBOL(MZDA, RNGCON,   0xBF8E6004)
PIC32SYMBOL(MZDA, RNGPOLY1, 0xBF8E6008)
PIC32SYMBOL(MZDA, RNGPOLY2, 0xBF8E600C)
PIC32SYMBOL(MZDA, RNGNUMGEN1, 0xBF8E6010)
PIC32SYMBOL(MZDA, RNGNUMGEN2, 0xBF8E6014)
PIC32SYMBOL(MZDA, RNGSEED1, 0xBF8E6018)
PIC32SYMBOL(MZDA, RNGSEED2, 0xBF8E601C)
PIC32SYMBOL(MZDA, RNGCNT,   0xBF8E6020)

BITMASK (uint32_t) { /* RNGCON */
  PIC32MZDA_RNGCON_LOAD = 0b1<<12, /* Device select */
  PIC32MZDA_RNGCON_TRNGMODE = 0b1<<11, /* True random number generator mode */
  PIC32MZDA_RNGCON_CONT = 0b1<<10, /* PRNG number shift enable */
  PIC32MZDA_RNGCON_PRNGEN = 0b1<<9, /* PRNG operation enable */
  PIC32MZDA_RNGCON_TRNGEN = 0b1<<8, /* TRNG operation enable */
  PIC32MZDA_RNGCON_PLEN = 0b11111111<<0 /* PRNG polynomial length */
}; /* From --[pdb]>--<mzda.cpp>. */

/* Compile with: ./artᵐⁱᵖˢ.ksh Trng */

#include <pic32rt/mips.hpp>
#include <pic32rt/pic32mz.hpp>
#include <pic32rt/pic32mzda.hpp>
#include <pic32rt/stable.hpp>

int
main(
  int argc,
  const char * argv[]
)
{  InitMZDAStarterBoard();
    
    /* Initial seed */
    🔧𝑀𝑍𝐷𝐴(RNGSEED1) = 0x090a0b0c;
    🔧𝑀𝑍𝐷𝐴(RNGSEED2) = 0x0d0e0f10;
    
    /* pdb: 'w /mx rngcon 0x140'. */
    🔧1𝑀𝑍𝐷𝐴(RNGCON,TRNGEN);
    
    while (🔎𝑀𝑍𝐷𝐴(RNGCNT) < 32) { ; } /* Wait until 32 bits are random. */
    
    /* RNGNUMGEN2 must be read before RNGNUMGEN1. */
    uint32_t n₂ = 🔎𝑀𝑍𝐷𝐴(RNGNUMGEN2), n₁ = 🔎𝑀𝑍𝐷𝐴(RNGNUMGEN1);
    print("Two thermal random numbers are ⬚ and ⬚\n", ﹟x(n₁), ﹟x(n₂));
    while (1) { ; }
    return 0;
}

