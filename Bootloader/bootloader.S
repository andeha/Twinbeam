/*  bootloader.S | 🛸 Entry point when powering on. */

#define gp  $28
#define sp  $29
#define ra  $31
    
    .section .text
    .org 0x0000
    .set noreorder
    .ent __start
__start:
    la    gp, _gp /* Stack begin */
    la    sp, _sp /* Stack end */
    
    di
    
    /* ... */
    
    j 0xBD001000
    nop
__start_end:
    .end __start
    

