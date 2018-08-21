//
//  mips.cpp
//  pdb
//

#include <Twinbeam.h>
#include "pdb.h"

/* CP0, register 15, 0 */ BITMASK(uint32_t) { // Processor Identification Register (CP0 Register 15, Select 0)
  PRID_COMPANYID   = 0b00100000000000000000000000000000, // Company Identification
  PRID_PROCESSORID = 0b00010000000000000000000000000000, // Processor Identification
  PRID_MAJORREV    = 0b00001000000000000000000000000000, // Processor Major Revision
  PRID_MINORREV    = 0b00000100000000000000000000000000, // Processor Minor Revision
  PRID_PATCHREV    = 0b00000010000000000000000000000000, // Processor Patch Level
};

Register Mips_Prid = {
  { U"PRID_COMPANYID", PRID_COMPANYID, U"Company Identification" },
  { U"PRID_PROCESSORID", PRID_PROCESSORID, U"Processor Identification" },
  { U"PRID_MAJORREV", PRID_MAJORREV, U"Processor Major Revision" },
  { U"PRID_MINORREV", PRID_MINORREV, U"Processor Minor Revision" },
  { U"PRID_PATCHREV", PRID_PATCHREV, U"Processor Patch Level" },
};

AnnotatedRegister AR_Mips_Prid = {
    U"PRID: Processor Identification Register (CP0 Register 15, Select 0)",
    Mips_Prid, 0x00000000,
    U""
};
