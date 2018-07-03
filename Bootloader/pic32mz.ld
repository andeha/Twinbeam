/*  pic32mz.ld (bootloader). */

__start      = 0xBFC00000;
Pagesize     = 4096;
StackAndHeap = 160*Pagesize;

MEMORY {
  kseg1_boot_flash_1 : ORIGIN = 0xBFC00000, LENGTH = 0xFF00
  kseg1_ram  : ORIGIN = 0xA0000000, LENGTH = 0x9FFFF /* 640 kB (PIC32MZ2...) or 256 kB (PIC32MZ1...). */
  BF1DEVCP0  : ORIGIN = 0xBFC0ffdc, LENGTH = 0x4
  BF1DEVCFG0 : ORIGIN = 0xBFC0ffcc, LENGTH = 0x4
  BF1DEVCFG1 : ORIGIN = 0xBFC0ffc8, LENGTH = 0x4
  BF1DEVCFG2 : ORIGIN = 0xBFC0ffc4, LENGTH = 0x4
  BF1DEVCFG3 : ORIGIN = 0xBFC0ffc0, LENGTH = 0x4
  BF1DEVCFG4 : ORIGIN = 0xBFC0ffbc, LENGTH = 0x4
}

SECTIONS
{
  .data : { *(.data) } > kseg1_ram
  .bss : { _bss_begin = .; *(.bss) *(COMMON) _bss_end = .; } > kseg1_ram
  .reginfo_boot : { *(.reginfo) } > kseg1_ram
  .abiflags_boot : { *(.MIPS.abiflags) } > kseg1_ram
  .got ALIGN(4) : { *(.got.plt) *(.got) . = ALIGN(4); } > kseg1_ram
  .ahstk : { PROVIDE(_gp = .); . = . + StackAndHeap; PROVIDE(_sp = .); } > kseg1_ram
  .conf : { LONG(0xF4FFFFFF) } > BF1DEVCFG4
  .conf : { LONG(0xFFFFFFFF) } > BF1DEVCFG3
  .conf : { LONG(0xDFFFFFFF) } > BF1DEVCFG2
  .conf : { LONG(0xDFF4FFFF) } > BF1DEVCFG1
  .conf : { LONG(0xFFFFFFF7) } > BF1DEVCFG0  /* ICESEL = ICS_PGx2 */
  .conf : { LONG(0xF4FFFFFF) } > BF1DEVCP0
  .text : { bootloader.o (.text) } > kseg1_boot_flash_1
  .rodata : { *(.rodata) } > kseg1_boot_flash_1
}
