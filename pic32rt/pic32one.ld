/*                                                                           
                                                                             
    pic32one.ld (for MX, MZDA and MM) with no live update.                   
                                                                             
    Ensure 'start.S' is the first file when 'prompt> ld.lld start.S …'.      
                                                                             
                              ram      flash     stkheap                     
      Model                 (bytes)   (bytes)    (bytes)                     
    ├─────────────────────┼─────────┼──────────┼─────────┤                   
    ╎ PIC32MM0256GPM064   ┊ 0x7FFF  ┆ 0x3FFFF  ┆   28671 ╎                   
    ╎ PIC32MX775F512(H|L) ┊ 0xFFFF  ┆ 0x7FFFF  ┆  520191 ╎                   
    ╎ PIC32MZ2064DAH169   ┊ 0x9FFFF ┆ 0x1FFFFF ┆  651264 ╎  32 MB DDR2       
    ╎ PIC32MZ2064DAB288   ┊ 0x9FFFF ┆ 0x1FFFFF ┆  651264 ╎ 128 MB DDR2 (E.g Micron MT47H64M16NF-25E)
    └─────────────────────┴─────────┴──────────┴─────────┘ (Starting at 0xA8000000|0x88000000)
                                                                             
    See also --<pic32two.ld> for a linker file with a divided program        
    memory.                                                                  
                                                                             
                                                                             
 */

__start      = 0xBD001000;
Pagesize     = 4096;
StackAndHeap = 159*Pagesize; /* Totally 4096 bytes reserved for .got, 
  .abiflags_app, reginfo_app, .bss, .data. */

MEMORY {
  /* Ram is 640 kB (PIC32MZ2...) or 256 kB (PIC32MZ1...). */
  kseg0_ram : ORIGIN = 0x80000000, LENGTH = 0x9FFFF
  kseg1_ram : ORIGIN = 0xA0000000, LENGTH = 0x9FFFF
  kseg1_program_flash : ORIGIN = 0xBD000000, LENGTH = 0x1FFFFF
  kseg3_frames : ORIGIN = 0xF4000000, LENGTH = 0xBFFFFFF
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


