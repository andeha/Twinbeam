/*  pic32mz.ld (…for the bootloader). */

__start = 0xBFC00000;
Pagesize = 4096;
StackAndHeap = 2*Pagesize;

MEMORY {
  /* Ram is 640 kB (PIC32MZ2...) or 256 kB (PIC32MZ1...). */
  kseg0_ram  : ORIGIN = 0x80000000, LENGTH = 0x9FFFF
  kseg1_ram  : ORIGIN = 0xA0000000, LENGTH = 0x9FFFF
  kseg1_boot_flash_1 : ORIGIN = 0xBFC00000, LENGTH = 0xFF00
  BF1DEVCFG4 : ORIGIN = 0xBFC0ffbc, LENGTH = 0x4
  BF1DEVCFG3 : ORIGIN = 0xBFC0ffc0, LENGTH = 0x4
  BF1DEVCFG2 : ORIGIN = 0xBFC0ffc4, LENGTH = 0x4
  BF1DEVCFG1 : ORIGIN = 0xBFC0ffc8, LENGTH = 0x4
  BF1DEVCFG0 : ORIGIN = 0xBFC0ffcc, LENGTH = 0x4
  BF1DEVCP0  : ORIGIN = 0xBFC0ffdc, LENGTH = 0x4
}

SECTIONS
{
  .stkheap : { PROVIDE(_gp = .); . = . + StackAndHeap; PROVIDE(_sp = .); } > kseg1_ram
  .data : { _data_begin = .; *(.data) _data_end = .; } > kseg1_ram
  .bss : { _bss_begin = .; *(.bss) *(COMMON) _bss_end = .; } > kseg1_ram
  .text : { bootloader.o (.text) } > kseg1_boot_flash_1
  .rodata : { *(.rodata) _rodata_end = .; } > kseg1_boot_flash_1
  /DISCARD/ : { *(.reginfo) *(.MIPS.abiflags) *(.got.plt) *(.got) }
  
/*
   
   BF1DEVCFG4=0xBFC4ff3c a․k․a DEVCFG4: DEVICE CONFIGURATION WORD = 0xFFFFFFFF (BF1DEVCFG4=0xBFC4ffbc)
   
     DEVCFG4_SWDTPS ␣␣␣1|1111|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Sleep Mode Watchdog Timer Postscale Select
    
   BF1DEVCFG3=0xBFC4ff40 a․k․a DEVCFG3: DEVICE CONFIGURATION WORD = 0xFFFFFFFF (ABF1DEVCFG3=0xBFC4ffc0)
                                                                           
    DEVCFG3_IOL1WAY ␣␣1␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Peripheral Pin Select Configuration
   DEVCFG3_PMDL1WAY ␣␣␣1|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Peripheral Module Disable Configuration
    DEVCFG3_PGL1WAY ␣␣␣␣|1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Permission Group Lock One Way Configuration
     DEVCFG3_FETHIO ␣␣␣␣|␣␣1␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Ethernet I/O Pin Selection Configuration
      DEVCFG3_FMIEN ␣␣␣␣|␣␣␣1|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Ethernet MII Enable Configuration
     DEVCFG3_USERID ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|1111|1111|1111|1111|User-defined value readable via ICSPTM and JTAG
                                                                           
   BF1DEVCFG2 a․k․a DEVCFG2: DEVICE CONFIGURATION WORD = 0xFFFFFFFF
                                                                           
   DEVCFG2_UPLLFSEL ␣1␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|USB PLL Input Frequency Select
      DEVCFG2_FDSEN ␣␣␣1|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deep Sleep Enable
    DEVCFG2_DSWDTEN ␣␣␣␣|1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deep Sleep Watchdog Timer Enable
   DEVCFG2_DSWDTOSC ␣␣␣␣|␣1␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deep Sleep Watchdog Timer Reference Clock Select
    DEVCFG2_DSWDTPS ␣␣␣␣|␣␣11|111␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deep Sleep Watchdog Timer Postscale Select
    DEVCFG2_DSBOREN ␣␣␣␣|␣␣␣␣|␣␣␣1|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deep Sleep BOR Enable
   DEVCFG2_FPLLODIV ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣111|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Default System PLL Output Divisor
  DEVCFG2_FPLLOMULT ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|System PLL Feedback Divider
   DEVCFG2_FPLLICLK ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|System PLL Input Clock Select
    DEVCFG2_FPLLRNG ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|System PLL Divided Input Clock Frequency Range
   DEVCFG2_FPLLIDIV ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|PLL Input Divider
                                                                           
   BF1DEVCFG1 a․k․a DEVCFG1: DEVICE CONFIGURATION WORD = 0xFFFFFFFF
                                                                           
     DEVCFG1_FDMTEN 1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deadman Timer enable
     DEVCFG1_DMTCNT ␣111|11␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deadman Timer Count Select
  DEVCFG1_FWDTWINSZ ␣␣␣␣|␣␣11|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Watchdog Timer Window Size
     DEVCFG1_FWDTEN ␣␣␣␣|␣␣␣␣|1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Watchdog Timer Enable
     DEVCFG1_WINDIS ␣␣␣␣|␣␣␣␣|␣1␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Watchdog Timer Window Enable
    DEVCFG1_WDTSPGM ␣␣␣␣|␣␣␣␣|␣␣1␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Watchdog Timer Stop During Flash Programming
      DEVCFG1_WDTPS ␣␣␣␣|␣␣␣␣|␣␣␣1|1111|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Watchdog Timer Postscale Select
      DEVCFG1_FCKSM ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|11␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Deadman Timer Count Select
   DEVCFG1_OSCIOFNC ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣1␣␣|␣␣␣␣|␣␣␣␣|CLKO Enable Configuration
    DEVCFG1_POSCMOD ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣11|␣␣␣␣|␣␣␣␣|Primary Oscillator Configuration
       DEVCFG1_IESO ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|1␣␣␣|␣␣␣␣|Internal External Switchover
    DEVCFG1_FSOSCEN ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣1␣␣|␣␣␣␣|Secondary Oscillator Enable
     DEVCFG1_DMTINV ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣11|1␣␣␣|Deadman Timer Count Window Interval
      DEVCFG1_FNOSC ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣111|Oscillator Selection
                                                                           
  BF1DEVCFG0 a․k․a DEVCFG0: DEVICE CONFIGURATION WORD = 0xFFFFFFF7 (When PFSWAP=1, AF1DEVCFG0)
                                                                           
   DEVCFG1_EJTAGBEN ␣1␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|EJTAG Boot Enable
    DEVCFG1_POSCAGC ␣␣␣␣|1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Primary Oscillator Automatic Gain Control
 DEVCFG1_POSCAGCDLY ␣␣␣␣|␣␣11|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Primary Crystal AGC Gain Search Step Settling Time Control
  DEVCFG1_POSCFGAIN ␣␣␣␣|␣␣␣␣|11␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Primary Crystal Oscillator Fine Gain Control
  DEVCFG1_POSCBOOST ␣␣␣␣|␣␣␣␣|␣␣1␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Primary Oscillator Boost
   DEVCFG1_POSCGAIN ␣␣␣␣|␣␣␣␣|␣␣␣1|1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Primary Crystal Oscillator Course Gain Control
  DEVCFG1_SOSCBOOST ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣1␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Secondary Oscillator Kick Start Programmability
   DEVCFG1_SOSCGAIN ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣11|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Secondary Oscillator Gain Control
      DEVCFG1_SMCLR ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|1␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Soft Master Clear Enable
     DEVCFG1_DBGPER ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣111|␣␣␣␣|␣␣␣␣|␣␣␣␣|Debug Mode CPU Access Permission
     DEVCFG1_FSLEEP ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣1␣␣|␣␣␣␣|␣␣␣␣|Flash Sleep Mode
    DEVCFG1_FECCCON ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣11|␣␣␣␣|␣␣␣␣|Dynamic Flash ECC Configuration
    DEVCFG1_BOOTISA ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣1␣␣|␣␣␣␣|Boot ISA Selection
      DEVCFG1_TRCEN ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣1␣|␣␣␣␣|Trace Enable
     DEVCFG1_ICESEL ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣1|1␣␣␣|In-Circuit Emulator/Debugger Communication Channel Select
     DEVCFG1_JTAGEN ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣1␣␣|JTAG Enable
      DEVCFG1_DEBUG ␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣11|Background Debugger Enable
                                                                           
  BF1DEVCP0=0xBFC4ffdc a․k․a DEVCP0: DEVICE CONFIGURATION WORD = 0xFFFFFFFF (When PFSWAP=1, ABF1CP0=0xBFC4ff5c)
                                                                           
          DEVCP0_CP ␣␣␣1|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Code-Protect
                                                                           
                                                                           
   ・ Sleep mode watchdog post scale=1:1048576
   ・ PPS=one conf, perih disable=one conf, Permission group=one conf,
      default ethernet pin, ethernet MII enabled
      EXTDDR=128MB, JTAG-USERID=0xffff
   ・ UPLL input clock is 24 MHz,
      FPLLODIV=PLL output divided by 32, FPLLMULT=Multiply by 128,
      FPLLICLK=FRC is selected as input to the System PLL,
      FPLLIDIV=Divide by 8
   ・ FNOSC=FRC divided by FRCDIV<2:0> bits (FRCDIV)
   ・ ICESEL=PGEC2/PGED2 pair is used = 0b10
   ・ Code-protection disabled
                                                                             
 */
  
  .conf : { LONG(0xFFFFFFFF) } > BF1DEVCFG4
  .conf : { LONG(0xFFFFFFFF) } > BF1DEVCFG3
  .conf : { LONG(0xFFFFFFFF) } > BF1DEVCFG2
  .conf : { LONG(0xFFFFFFFF) } > BF1DEVCFG1
  .conf : { LONG(0xFFFFFFF7) } > BF1DEVCFG0
  .conf : { LONG(0xFFFFFFFF) } > BF1DEVCP0
  
}

