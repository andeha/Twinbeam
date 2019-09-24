/*  mips.hpp | pic32rt. */

MACRO __builtin_uint_t 🔎Count() { __builtin_uint_t val; asm 
  volatile("mfc0 %0, $9, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Compare() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $11, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Status() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $12, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎IntCtl() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $12, 1; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎SRSCtl() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $12, 2; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎SRSMap() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $12, 3; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Cause() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $13, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎NestedExc() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $13, 1; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎EPC() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $14, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎NestedEPC() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $14, 1; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎PRID() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $15, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Ebase() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $15, 1; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Config() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $16, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Config3() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $16, 3; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎Debug() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $23, 0; nop" : "=r" (val)); return val; }
MACRO __builtin_uint_t 🔎DEPC() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $23, 0; nop" : "=r" (val)); return val; }

MACRO void 🔧Count(__builtin_uint_t value) { asm
  volatile("mtc0 %0, $9, 0; nop" : : "r" (value)); }
MACRO void 🔧Compare(__builtin_uint_t value) { asm
  volatile("mtc0 %0, $11, 0; nop" : : "r" (value)); }
MACRO void 🔧Status(__builtin_uint_t value) { asm
  volatile("mtc0 %0, $12, 0; nop" : : "r" (value)); }
MACRO void 🔧Cause(__builtin_uint_t value) { asm
  volatile("mtc0 %0, $13, 0; nop" : : "r" (value)); }
MACRO void 🔧Ebase(__builtin_uint_t value) { asm
  volatile("mtc0 %0, $15, 1; nop" : : "r" (value)); }
MACRO void 🔧UserTraceData1(uint32_t value) { asm
  volatile("mtc0 %0, $23, 3; nop" : : "r" (value)); }

MACRO __builtin_uint_t 🔎Desave() { __builtin_uint_t val; asm
  volatile("mfc0 %0, $31, 0; nop" : "=r" (val)); return val; }
MACRO void 🔧Desave(uint32_t value) { asm
  volatile("mtc0 %0, $31, 0; nop" : : "r" (value)); }

BITMASK (uint32_t) { /* MIPS Status. */
  MIPS_Status_IE  = 0b1 << 0, /* Interrupt Enable */
  MIPS_Status_EXL = 0b1 << 1, /* Exception Level */
  MIPS_Status_ERL = 0b1 << 2, /* Error Level */
  MIPS_Status_UM  = 0b1 << 4, /* User Mode */
  MIPS_Status_SR = 0b1 << 20, /* Soft Reset */
  PIC32_Status_TS = 0b1 << 21, // TLB Shutdown Control
  MIPS_Status_BEV = 0b1 << 22, /* Bootstrap Exception Vector Control. (Location of Exception vector: 1 = Bootstrap, 0 = Normal.) */
  OPTMIPS_Status_MX = 0b1 << 24, /* MIPS DSP Resource Enable */
  MIPS_Status_RP  = 0b1 << 27, /* Reduced Power */
};

BITMASK (uint32_t) { // MIPS Cause
  MIPS_Cause_DSPDis = 0x1a // DSP Module State Disabled Exception [see 'MIPS® Architecture for Programmers Volume IV-e: MIPS® DSP Module for MIPS32TM Architecture'.]
};

BITMASK (uint32_t) { // MIPS Debug
  MIPS_Status_DM = 0b1 << 0,
};

#define debug_break(code) asm ("sdbbp " #code)
#define break(code)       asm ("break " #code)
#define wait              asm ("wait")

#define di asm volatile ("di")
#define ei asm volatile ("ei")
#define ehb asm volatile ("ehb")

