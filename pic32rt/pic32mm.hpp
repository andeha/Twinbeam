/* pic32mm.hpp | Energy-focused, packaged and early. */

#define PIC32MM_KEY1 0xAA996655
#define PIC32MM_KEY2 0x556699AA
#define PIC32MM_SYSKEY 0xBF800030

PIC32SYMBOL(MM, U1MODE, 0xBF806000)
PIC32SYMBOL(MM, U1MODE, 0xBF806000)

/*
   
   A Curiosity equipped with PIC32MM0256GPM064 in a TQFP-64 (not UQF-28)
   
   S2 - RC10 pin 45. (OCM3F)
   S3 - RC4 pin 36. (OCM1E/INT3)
   S1 - TMS/RP14/RB9 pin 49. (SDA1/INT2/)
   POT - RC8 (AN14/LVDIN/C2INC/)
   OCM3E/RC15 - Blue/RC3 - Green/RD1 - Red
   RD3 Red-led1, RC13 Red-led2
   J6 current measurement. (3V3)
   AN2/C2INB/VMIO/RP13/CN4/RB2: VDDSENSE
   AN3/C2INA/VPIO/CN5/RB3: VPPSENSE
   RP22/PMBE/CN52/RD3 PKMISO
   RP25/PMWR/CN13/RD4 PKMOSI
   Micro B-U7-USB D- and D+ - RB10/RB11 and VBUS/RB6
   
   RTCC/RA15 available on RA15_GPIOXA.
   
   SOT-23 and SC-70.
   
 */

#define 🔎𝑀𝑀(symbol) 🔎(PIC32MM_##symbol)
#define 🔧𝑀𝑀(symbol) 🔧(PIC32MM_##symbol)
#define 🎭𝑀𝑀(sym,msk,...) 🎭((__builtin_uint_t *)(PIC32MM_##sym), PIC32MM_##sym##_##msk __VA_OPT__(,) __VA_ARGS__)
#define 🔧ᵗᵍᵍˡ𝑀𝑀(symbol,msk) 🔧(PIC32MM_##symbol##INV) = PIC32MM_##symbol##_##msk
#define 🔧0𝑀𝑀(symbol,msk) 🔧(PIC32MM_##symbol##CLR) = PIC32MM_##symbol##_##msk
#define 🔧1𝑀𝑀(symbol,msk) 🔧(PIC32MM_##symbol##SET) = PIC32MM_##symbol##_##msk


