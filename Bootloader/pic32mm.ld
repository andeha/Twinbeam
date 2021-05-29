/*  pic32mm.ld - for the PIC32MM0064GPL036 and PIC32MM0064GPL028 bootloader. */

__start = 0xBFC00000;
Pagesize = 4096;
StackAndHeap = 1*Pagesize;

MEMORY {
  kseg1_ram : ORIGIN = 0xA0000000, LENGTH = 0x1FFF
  kseg1_boot_flash_1 : ORIGIN = 0xBFC00000, LENGTH = 0x16FF
  /* ⬷ 8, 16 alt. 32 kB on Pic32mm. */
  FSEC    : ORIGIN = 0xBFC017d8, LENGTH = 0x4
  FOSCSEL : ORIGIN = 0xBFC017d4, LENGTH = 0x4
  FWDT    : ORIGIN = 0xBFC017d0, LENGTH = 0x4
  FPOR    : ORIGIN = 0xBFC017cc, LENGTH = 0x4
  FICD    : ORIGIN = 0xBFC017c8, LENGTH = 0x4
  FDEVOPT : ORIGIN = 0xBFC017c4, LENGTH = 0x4
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
     
   ・ Code-protection disabled.
   ・ Fast-RC osc. with DIV-by-N, Sys-PLL=FRC, secondary 
      oscillator (SOSC) enabled, primary oscillator (POSC) 
      disabled, CLK0/OSC2 is I/O and not SYSCLK, 
      SOSC chrystal and not external pin, clock-switching enabled, 
      fail-safe clock monitoring enabled.
   ・ Watchdog timer enabled, …
   ・ LPBOR enabled, RETVR disabled, LPBOR enabled.
   ・ ICE/ICD #1, JTAG enabled.
   ・ VBUSON@USB, USBID@USB, SDA1/SCL1 on RB8/RB9.
     
  */
  
  .conf : { LONG(0xFFFFFFFF) } > FSEC /* ⬷ code protection disabled. */
  .conf : { LONG(0xFFFFFFFF) } > FOSCSEL /* ⬷ Switching enabled, Crystal SOSC, 
 OSC2/CLKO is IO, POSC disabled, 2-speed startup, SOSC enabled, PLL=FRC, FRC with 
 divide-by-N selected. */
  .conf : { LONG(0xFFFF60E0) } > FWDT /* ⬷ WDT disabled. */
  .conf : { LONG(0xFFFFFFFF) } > FPOR
  .conf : { LONG(0xFFFFFFFD) } > FICD /* ⬷ PGEC1/PGED1, JTAG disabled. */
  .conf : { LONG(0xFFFFFFFF) } > FDEVOPT /* ⬷ SOSC operates in 'Normal Power' mode. */
}

