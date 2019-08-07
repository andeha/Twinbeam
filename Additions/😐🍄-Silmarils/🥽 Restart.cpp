/*  Restart.cpp | 'Restarting all this?' */

#include <Twinbeam.h>
#include <pic32rt/mips.hpp>
#include <pic32rt/pic32mz.hpp>
#include <pic32rt/pic32mzda.hpp>

/* Compile with './artᵐⁱᵖˢ.ksh Restart' */

int
main(
  int argc,
  const char * argv[]
)
{
    __builtin_uint_t rcon = 🔎𝑀𝑍𝐷𝐴(RCON);
    if (🐛𝑀𝑍𝐷𝐴(rcon,HVD1V8R)) { print("VDDR1V8 (DDR2) High Voltage Detect\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,BCFGERR)) { print("Primary Configuration Registers Error\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,BCFGFAIL)) { print("Primary/Secondary Configuration Registers Error\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,VBPOR)) { print("VBPOR Mode\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,VBAT)) { print("VBAT Mode\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,DPSLP)) { print("Deep Sleep Mode\n"); }
    if (rcon & PIC32MZDA_RCON_CMR) { print("Configuration Mismatch Reset\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,EXTR)) { print("External Reset (MCLR) Pin\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,SWR)) { print("Software Reset\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,DMTO)) { print("Deadman Timer Time-out\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,WDTO)) { print("Watchdog Timer Time-out\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,SLEEP)) { print("Wake From Sleep\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,IDLE)) { print("Wake From Idle\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,BOR)) { print("Brown-out Reset\n"); }
    if (🐛𝑀𝑍𝐷𝐴(rcon,POR)) { print("Power-on Reset\n"); }
    
    while (1) { ; }
    
    Reset(KEY1,KEY2); /* Perform a software reset. */
    
    return 0;
}


