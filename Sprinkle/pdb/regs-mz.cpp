/*  regs-mz.cpp | Let us keep mzda for a while. */

#include <Twinbeam.h> /* includes --<Source>--<coroutine>. */

/* CP0, register 0 and 0 */ BITMASK (uint32_t) { /* Index. */
  MIPS_Index_P = 0x80000000, /* Probe Failure Detect. */
  MIPS_Index_Index = 0x0000001f /* Index to TLB Entry Affected by the TLBR and TLBW Instruction. */
};

Bitfield Mips_Index[] READONLY = {
  { U"MIPS_Index_P", MIPS_Index_P, U"Probe Failure Detect" },
  { U"MIPS_Index_Index", MIPS_Index_Index, U"Index to TLB Entry Affected by the TLBR and TLBW Instruction" }
};

AnnotatedRegister AR_Mips_Index READONLY = {
  U"INDEX: TLB Index Register (CP0 Register 0, Select 0)",
  2, Mips_Index, 0x00000000,
  U""
};

