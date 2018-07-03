/*
    
    pic32.ld
    
    Ensure `start.S` is the first file when `ld.lld start.S ...`.
    
 */

__start      = 0xBD001000;
Pagesize     = 4096;
StackAndHeap = 160*Pagesize;

MEMORY {
  kseg1_program_flash : ORIGIN = 0xBD000000, LENGTH = 0x1FFFFF
  kseg1_ram : ORIGIN = 0xA0000000, LENGTH = 0x9FFFF /* 640 kB (PIC32MZ2...) or 256 kB (PIC32MZ1...). */
}

SECTIONS
{
  .data : { *(.data) } > kseg1_ram
  .bss : { _bss_begin = .; *(.bss) *(COMMON) _bss_end = .; } > kseg1_ram
  .reginfo_boot : { *(.reginfo) } > kseg1_ram
  .abiflags_boot : { *(.MIPS.abiflags) } > kseg1_ram
  .got ALIGN(4) : { *(.got.plt) *(.got) . = ALIGN(4); } > kseg1_ram
  .ahstk : { PROVIDE(_gp = .); . = . + StackAndHeap; PROVIDE(_sp = .); } > kseg1_ram
  .text : { start.o (.text) } > kseg1_program_flash
  /* .text : { * (.construct) } > kseg1_program_flash */
  .text : { * (.text) } > kseg1_program_flash
  .rodata : { *(.rodata) } > kseg1_program_flash
}

