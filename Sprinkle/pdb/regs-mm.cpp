/*  regs-mm.cpp | the structure of MM and no double. */

#include <Twinbeam.h> /* includes --<Source>--<coroutine>. */

/* CP0, register 16, 0 */ BITMASK (uint32_t) { /* MIPS Config. */
  MIPS_Config_K23 = 0b111<<28, /* Cacheability kseg2 and kseg3 */
  MIPS_Config_KU = 0b111<<25,  /* Cacheability kuseg and useg */
// MIPS_Config_ISP = 0b1<<24,   /* Instruction scratch pad RAM */
// MIPS_Config_DSP = 0b1<<23,   /* Data scratch pad RAM */
  MIPS_Config_UDI = 0b1<<22,   /* User-defined */
  MIPS_Config_SB = 0b1<<21,    /* Simple BE */
  MIPS_Config_MDU = 0b1<<20,   /* Multiply/divide unit */
// MIPS_Config_MM = 0b11<<17,   /* Merge mode */
  MIPS_Config_DS = 0b1<<16,    /* Dual SRAM Interface */
// MIPS_Config_DSBM = 0b1<<16,  /* Dual SRAM/burst mode */
// MIPS_Config_BM = 0b1<<16,    /* Burst mode */
  MIPS_Config_BE = 0b1<<15,    /* Endian mode */
  MIPS_Config_AT = 0b11<<13,   /* Architecture type */
  MIPS_Config_AR = 0b111<<10,  /* Architecture revision level */
  MIPS_Config_MT = 0b111<<7,   /* MMU Type */
  MIPS_Config_K0 = 0b111<<0    /* Kseg0 Coherency Algorithm */
};

Bitfield MipsMM_Config[] READONLY = {
  { U"MIPS_Config_K23", MIPS_Config_K23, U"Cacheability kseg2 and kseg3" },
  { U"MIPS_Config_KU", MIPS_Config_KU, U"Cacheability kuseg and useg" },
  { U"MIPS_Config_UDI", MIPS_Config_UDI, U"User-defined" },
  { U"MIPS_Config_SB", MIPS_Config_SB, U"Simple BE" },
  { U"MIPS_Config_MDU", MIPS_Config_MDU, U"Multiply/Divide Unit" },
  { U"MIPS_Config_DS", MIPS_Config_DS, U"Dual SRAM Interface" },
  { U"MIPS_Config_BE", MIPS_Config_BE, U"Endian Mode" },
  { U"MIPS_Config_AT", MIPS_Config_AT, U"Architecture Type" },
  { U"MIPS_Config_AR", MIPS_Config_AR, U"Architecture Revision Level" },
  { U"MIPS_Config_MT", MIPS_Config_MT, U"MMU Type" },
  { U"MIPS_Config_K0", MIPS_Config_K0, U"Kseg0 Coherency Algorithm" },
};

AnnotatedRegister AR_MipsMM_Config READONLY = {
  U"CONFIG: Configuration Register (CP0 Register 16, Select 0)",
  11, MipsMM_Config, 0x80000000,
  U""
};