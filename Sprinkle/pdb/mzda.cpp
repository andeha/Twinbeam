//
//  mzda.cpp
//  pdb
//

#include <Twinbeam.h>

BITMASK (uint32_t) { // RCON
  PIC32MZ_RCON_HVD1V8R    = 0b1 << 29, // VDDR1V8 (DDR2) High Voltage Detect
  PIC32MZ_RCON_BCFGERR    = 0b1 << 27, // Primary Configuration Registers Error
  PIC32MZ_RCON_BCFGFAIL   = 0b1 << 26, // Primary/Secondary Configuration Registers Error
  PIC32MZ_RCON_VBPOR      = 0b1 << 17, // VBPOR Mode
  PIC32MZ_RCON_VBAT       = 0b1 << 16, // VBAT Mode
  PIC32MZ_RCON_DPSLP      = 0b1 << 10, // Deep Sleep Mode
  PIC32MZ_RCON_CMR        = 0b1 << 9,  // Configuration Mismatch Reset
  PIC32MZ_RCON_EXTR       = 0b1 << 7,  // External Reset (MCLR) Pin
  PIC32MZ_RCON_SWR        = 0b1 << 6,  // Software Reset
  PIC32MZ_RCON_DMTO       = 0b1 << 5,  // Deadman Timer Time-out
  PIC32MZ_RCON_WDTO       = 0b1 << 4,  // Watchdog Timer Time-out
  PIC32MZ_RCON_SLEEP      = 0b1 << 3,  // Wake From Sleep
  PIC32MZ_RCON_IDLE       = 0b1 << 2,  // Wake From Idle
  PIC32MZ_RCON_BOR        = 0b1 << 1,  // Brown-out Reset
  PIC32MZ_RCON_POR        = 0b1 << 0   // Power-on Reset
};

Register Microchip_RCON = {
  { U"RCON_HVD1V8R", PIC32MZ_RCON_HVD1V8R, U"VDDR1V8 (DDR2) High Voltage Detect" },
  { U"RCON_BCFGERR", PIC32MZ_RCON_BCFGERR, U"Primary Configuration Registers Error" },
  { U"RCON_BCFGFAIL", PIC32MZ_RCON_BCFGFAIL, U"Primary/Secondary Configuration Registers Error" },
  { U"RCON_VBPOR", PIC32MZ_RCON_VBPOR, U"VBPOR Mode" },
  { U"RCON_VBAT", PIC32MZ_RCON_VBAT, U"VBAT Mode" },
  { U"RCON_DPSLP", PIC32MZ_RCON_DPSLP, U"Deep Sleep Mode" },
  { U"RCON_CMR", PIC32MZ_RCON_CMR, U"Configuration Mismatch Reset" },
  { U"RCON_EXTR", PIC32MZ_RCON_EXTR, U"External Reset (MCLR) Pin" },
  { U"RCON_SWR", PIC32MZ_RCON_SWR, U"Software Reset" },
  { U"RCON_DMTO", PIC32MZ_RCON_DMTO, U"Deadman Timer Time-out" },
  { U"RCON_WDTO", PIC32MZ_RCON_WDTO, U"Watchdog Timer Time-out" },
  { U"RCON_SLEEP", PIC32MZ_RCON_SLEEP, U"Wake From Sleep" },
  { U"RCON_IDLE", PIC32MZ_RCON_IDLE, U"Wake From Idle" },
  { U"RCON_BOR", PIC32MZ_RCON_BOR, U"Brown-out Reset" },
  { U"RCON_POR", PIC32MZ_RCON_POR, U"Power-on Reset" },
};

AnnotatedRegister AR_Microchip_RCON = {
  U"RCON: RESET CONTROL REGISTER",
  15, Microchip_RCON, 0x00000000,
  U""
};

