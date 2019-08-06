/*  Restart.cpp | 'Restarting all this?' */

#include <Twinbeam.h>
#include <mips.hpp>
#include <pic32mz.hpp>
#include <pic32mzda.hpp>

/* Compile with './artᵐⁱᵖˢ.ksh Restart' */

int
main(
  int argc,
  const char * argv[]
)
{
    __builtin_uint_t rcon = 🔎𝑀𝑍𝐷𝐴(RCON);
    if (rcon & HVD1V8R) { print("VDDR1V8 (DDR2) High Voltage Detect\n"); }
    if (rcon & BCFGERR) { print("Primary Configuration Registers Error\n"); }
    if (rcon & BCFGFAIL) { print("Primary/Secondary Configuration Registers Error\n"); }
    if (rcon & VBPOR) { print("VBPOR Mode\n"); }
    if (rcon & VBAT) { print("VBAT Mode\n"); }
    if (rcon & DPSLP) { print("Deep Sleep Mode\n"); }
    if (rcon & CMR) { print("Configuration Mismatch Reset\n"); }
    if (rcon & EXTR) { print("External Reset (MCLR) Pin\n"); }
    if (rcon & SWR) { print("Software Reset\n"); }
    if (rcon & DMTO) { print("Deadman Timer Time-out\n"); }
    if (rcon & WDTO) { print("Watchdog Timer Time-out\n"); }
    if (rcon & SLEEP) { print("Wake From Sleep\n"); }
    if (rcon & IDLE) { print("Wake From Idle\n"); }
    if (rcon & BOR) { print("Brown-out Reset\n"); }
    if (rcon & POR) { print("Power-on Reset\n"); }
    
    while (1) { ; }
    
    Reset(KEY1,KEY2); /* Perform a software reset. */
    
    return 0;
}


