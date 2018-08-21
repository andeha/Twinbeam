//
//  mzda.cpp
//  pdb
//

#include <Twinbeam.h>
#include "pdb.h"

#pragma mark - SPECIAL FEATURES

BITMASK (uint32_t) { // DEVID
    PIC32MZDA_DEVID_VER = 0xF0000000, // 0b1111<<28, // Revision Identifier
    PIC32MZDA_DEVID_DEVID = 0xFFFffff // Device Id
};

Register Microchip_DEVID = {
  { U"DEVID_VER", PIC32MZDA_DEVID_VER, U"Revision Identifier" },
  { U"DEVID_DEVID", PIC32MZDA_DEVID_DEVID, U"Device ID" },
};

AnnotatedRegister AR_Microchip_DEVID = {
  U"DEVID: DEVICE AND REVISION ID REGISTER",
  Microchip_DEVID, 0x00000000,
  U""
};