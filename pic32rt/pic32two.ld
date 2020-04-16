/*                                                                           
                                                                             
    pic32two.ld (for MZ, MZDA and not MM) with live update.                  
                                                                             
    Ensure 'start.S' is the first file when 'prompt> ld.lld start.S …'.      
                                                                             
                                                                             
                              ram      flash     stkheap                     
      Model                 (bytes)   (bytes)    (bytes)                     
    ├─────────────────────┼─────────┼──────────┼─────────┤                   
    ╎ PIC32MZ2064DAB288   ┊ 0x9FFFF ┆ 0x1FFFFF ┆  651264 ╎ 128 MB DDR2 (E.g Micron MT47H64M16NF-25E)
    └─────────────────────┴─────────┴──────────┴─────────┘ (Starting at 0xA8000000|0x88000000)
                                                                             
                                                                             
    See also --<pic32one.ld> for a linker file with a scalar program memory  
    interval suitable for one image following directly after an optional     
    software configuration section containing a (non-used?) `PFSWAP` bit     
    configuration.                                                           
                                                                             
                                                                             
 */

__start = 0xBE005000;
Pagesize = 4096;
StackAndHeap = 159*Pagesize; /* 4096 bytes reserved for .got, .abiflags_app, 
  .reginfo_app, .bss and .data. */
  
MEMORY {
  /* Ram is 640 kB (PIC32MZ2...) or 256 kB (PIC32MZ1...). */
  kseg0_ram : ORIGIN = 0x80000000, LENGTH = 0x9FFFF
/* kseg0_ddr2 : ORIGIN = 0x88000000, LENGTH = 0x2000000  32 MB 
  kseg0_ddr2 : ORIGIN = 0x88000000, LENGTH = 0x10000000 256 MB */
  kseg1_ram : ORIGIN = 0xA0000000, LENGTH = 0x9FFFF
/* kseg1_ddr2 : ORIGIN = 0xA8000000, LENGTH = 0x2000000   32 MB 
  kseg1_ddr2 : ORIGIN = 0xA8000000, LENGTH = 0x10000000  256 MB */
  kseg1_program_flash_previous_aka_lower : ORIGIN = 0xBD000000, LENGTH = 0xFFFFF
  TB1PGMCFG3 : ORIGIN = 0xBE000000, LENGTH = 0x4
  TB1PGMCFG2 : ORIGIN = 0xBE000004, LENGTH = 0x4
  TB1PGMCFG1 : ORIGIN = 0xBE000008, LENGTH = 0x4
  TB1PGMCFG0 : ORIGIN = 0xBE00000C, LENGTH = 0x4
  kseg1_program_flash_current_aka_upper : ORIGIN = 0xBE004000, LENGTH = 0xFBFFF
  kseg3_frames : ORIGIN = 0xF4000000, LENGTH = 0xBFFFFFF
}

SECTIONS
{
  /*  Live update gives one upgrade cycle rollback:
   
   TB1PGMCFG0: TWINBEAM CONFIGURATION WORD 0
   
   TB1PGMCFG0_CPFSWAP ␣00␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|␣␣␣␣|Current PFSWAP
     (10=PFSWAP=0, 01=PFSWAP=1,00=uninited,11=notused)
   
   */
  
  .conf : { LONG(0x5457494e) } > TB1PGMCFG3 /* Based on Twinbeam */
  .conf : { LONG(0x4d555845) } > TB1PGMCFG2 /* Revision 'MUXE' */
  .conf : { LONG(0xFFFFFFFF) } > TB1PGMCFG1 /* Application settings */
  .conf : { LONG(0xBFFFFFFF) } > TB1PGMCFG0 /* To invert memory space by 
    setting PFSWAP=1, set TB1PGMCFG0 to 0xBFFFFFFF. To set PFSWAP=0 set TB1PGMCFG0 
    to 0xDFFFFFFF. (See the bitfield above for details.) */
  
  /* .ddr2 : { *(.ddr2) } > kseg0_ddr2 */
  .text : { * (.text .ctors .dtors) } > kseg1_program_flash_current_aka_upper
  .rodata : { *(.rodata) _etext = .; } > kseg1_program_flash_current_aka_upper
  .data : { _data_begin = .; *(.data) _data_end = .; } > kseg1_ram AT > kseg1_program_flash_current_aka_upper
  
  .bss : { _bss_begin = .; *(.bss) *(COMMON) _bss_end = .; } > kseg1_ram
  .reginfo_app : { *(.reginfo) } > kseg1_ram
  .abiflags_app : { *(.MIPS.abiflags) } > kseg1_ram
  .got ALIGN(4) : { *(.got.plt) *(.got) . = ALIGN(4); } > kseg1_ram
  .ahstk : { PROVIDE(_gp = .); . = . + StackAndHeap; PROVIDE(_sp = .); } > kseg1_ram
  /* .coherent : { *(.coherent) } > kseg1_ram */
}


