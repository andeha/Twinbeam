//
//  mips.cpp
//  pdb
//

#include <Twinbeam.h>

#pragma mark - 50.13.22 Cause Register (CP0 Register 13, Select 0)

/* CP0, register 13, 0 */ BITMASK(uint32_t) { // Cause Register (CP0 Register 13, Select 0)
  MIPS_Cause_BD = 0x80000000 /* 0b1<<31 */, /* Branch Delay */
  MIPS_Cause_TI = 0b1<<30, /* Timer Interrupt */
  MIPS_Cause_CE = 0b11<<28, /* Coprocessor Exception */
  MIPS_Cause_DC = 0b1<<27, /* Disable Count Register */
  MIPS_Cause_PCI = 0b1<<26, /* Performance Counter Interrupt */
  MIPS_Cause_IC = 0b1<<25, /* Interrupt Chaining */
  MIPS_Cause_AP = 0b1<<24, /* Interrupt Auto-Prologue Exception */
  MIPS_Cause_IV = 0b1<<23, /* Interrupt Vector */
  MIPS_Cause_WP = 0b1<<22, /* Watch Exception Pending */
  MIPS_Cause_FDCI = 0b1<<21, /* Fast Debug Channel Interrupt */
  MIPS_Cause_RIPL = 0b11111111<<10, /* Requested Interrupt Priority Level */
  MIPS_Cause_IP1 = 0b1<<9, /* Software Interrupt 1 Request Control */
  MIPS_Cause_IP0 = 0b1<<8, /* Software Interrupt 0 Request Control */
  MIPS_Cause_EXCCODE = 0b11111<<2 /* Exception Code */
};

Register Mips_Cause READONLY = {
  { U"MIPS_Cause_EXCCODE", MIPS_Cause_EXCCODE, U"Exception Code" },
  { U"MIPS_Cause_IP0", MIPS_Cause_IP0, U"Software Interrupt 0 Request Control" },
  { U"MIPS_Cause_IP1", MIPS_Cause_IP1, U"Software Interrupt 1 Request Control" },
  { U"MIPS_Cause_RIPL", MIPS_Cause_RIPL, U"Requested Interrupt Priority Level" },
  { U"MIPS_Cause_FDCI", MIPS_Cause_FDCI, U"Fast Debug Channel Interrupt" },
  { U"MIPS_Cause_WP", MIPS_Cause_WP, U"Watch Exception Pending" },
  { U"MIPS_Cause_IV", MIPS_Cause_IV, U"Interrupt Vector" },
  { U"MIPS_Cause_AP", MIPS_Cause_AP, U"Interrupt Auto-Prologue Exception" },
  { U"MIPS_Cause_IC", MIPS_Cause_IC, U"Interrupt Chaining" },
  { U"MIPS_Cause_PCI", MIPS_Cause_PCI, U"Performance Counter Interrupt" },
  { U"MIPS_Cause_DC", MIPS_Cause_DC, U"Disable Count Register" },
  { U"MIPS_Cause_CE", MIPS_Cause_CE, U"Coprocessor Exception" },
  { U"MIPS_Cause_TI", MIPS_Cause_TI, U"Timer Interrupt" },
  { U"MIPS_Cause_BD", MIPS_Cause_BD, U"Branch Delay" }
};

AnnotatedRegister AR_Mips_Cause READONLY = {
    U"Cause Register (CP0 Register 13, Select 0)",
    14, Mips_Cause, 0x00000000,
    U""
};

