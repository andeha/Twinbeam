/*
    
    pic32.ld
    
    Ensure `start.S` is the first file when `ld.lld start.S ...`.
    
 */

__start      = 0xBD001000;
Pagesize     = 4096;
StackAndHeap = 159*Pagesize; /* 4096 bytes reserved for .got, .abiflags_app, reginfo_app, .bss, .data */

MEMORY {
  kseg1_program_flash : ORIGIN = 0xBD000000, LENGTH = 0x1FFFFF
  kseg1_ram : ORIGIN = 0xA0000000, LENGTH = 0x9FFFF /* 640 kB (PIC32MZ2...) or 256 kB (PIC32MZ1...). */
}

SECTIONS
{
  .text : { * (.text .ctors .dtors) } > kseg1_program_flash
  .rodata : { *(.rodata) _etext = .; } > kseg1_program_flash
  
  .data : { _data_begin = .; *(.data) _data_end = .; } > kseg1_ram AT > kseg1_program_flash
  .bss : { _bss_begin = .; *(.bss) *(COMMON) _bss_end = .; } > kseg1_ram
  .reginfo_app : { *(.reginfo) } > kseg1_ram
  .abiflags_app : { *(.MIPS.abiflags) } > kseg1_ram
  .got ALIGN(4) : { *(.got.plt) *(.got) . = ALIGN(4); } > kseg1_ram
  .ahstk : { PROVIDE(_gp = .); . = . + StackAndHeap; PROVIDE(_sp = .); } > kseg1_ram
}

