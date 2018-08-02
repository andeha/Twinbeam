//
//  mips.cpp
//  pdb
//

#include <Twinbeam.h>
#include <Additions.h>
#include "pdb.h"

/* CP0, register 23, 0 */ BITMASK(uint32_t) { // DEBUG: Debug control, exception status and EJTAG trace control
  DEBUG_DBD        = 0b10000000000000000000000000000000, // Branch ͞ Debug Exception
  DEBUG_DM         = 0b01000000000000000000000000000000, // Debug Mode
  DEBUG_NODCR      = 0b00100000000000000000000000000000, // Debug Control Register
  DEBUG_LSNM       = 0b00010000000000000000000000000000, // Load Store Access Control
  DEBUG_DOZE       = 0b00001000000000000000000000000000, // Low-Power Mode Debug Exception
  DEBUG_HALT       = 0b00000100000000000000000000000000, // System Bus Clock Stop
  DEBUG_COUNTDM    = 0b00000010000000000000000000000000, // Count Register Behavior
  DEBUG_IBUSEP     = 0b00000001000000000000000000000000, // Instruction Fetch Bus Error Exception Pending
  DEBUG_MCHECKP    = 0b00000000100000000000000000000000, // Machine Check Exception Pending
  DEBUG_CACHEEP    = 0b00000000010000000000000000000000, // Cache Error Pending
  DEBUG_DBUSEP     = 0b00000000001000000000000000000000, // Data Access Bus Error Exception Pending
  DEBUG_IEXI       = 0b00000000000100000000000000000000, // Imprecise Error Exception Inhibit Control
  DEBUG_DDBSIMPR   = 0b00000000000010000000000000000000, // Debug Data Break Store Exception
  DEBUG_DDBLIMPR   = 0b00000000000001000000000000000000, // Debug Data Break Load Exception
  DEBUG_VER_3͞      = 0b00000000000000111000000000000000, // EJTAG Version
  DEBUG_DEXCCODE_5͞ = 0b00000000000000000111110000000000, // Latest Exception in Debug Mode
  DEBUG_NOSST      = 0b00000000000000000000001000000000, // Singe-step Feature Control
  DEBUG_SST        = 0b00000000000000000000000100000000, // Debug Single-step Control
  DEBUG_DIBIMPR    = 0b00000000000000000000000001000000, // Imprecise Debug Instruction Break Exception
  DEBUG_DINT       = 0b00000000000000000000000000100000, // Debug Interrupt Exception
  DEBUG_DIB        = 0b00000000000000000000000000010000, // Debug Instruction Break Exception
  DEBUG_DDBS       = 0b00000000000000000000000000001000, // Debug Data Break Exception on Store
  DEBUG_DDBL       = 0b00000000000000000000000000000100, // Debug Data Break Exception on Load
  DEBUG_DBP        = 0b00000000000000000000000000000010, // Debug Software Breakpoint Exception
  DEBUG_DSS        = 0b00000000000000000000000000000001  // Debug Single-step Exception
};

Register Mips_Debug = {
  { "DEBUG_DBD", DEBUG_DBD, U"Branch ͞ Debug Exception" },
  { "DEBUG_DM",  DEBUG_DM,  U"Debug Mode" }
};

AnnotatedRegister AR_Mips_Debug = {
    U"Debug (Mips CP0, register 23, 0: Debug control, exception status and EJTAG trace control.)",
    Mips_Debug, 0x00000000,
    U""
};