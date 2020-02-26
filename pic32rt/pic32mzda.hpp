/*  pic32mzda.hpp | Chip actually realized. (pic32rt) */

#define 🔎𝑀𝑍𝐷𝐴(symbol) 🔎(PIC32MZDA_##symbol)
#define 🔧𝑀𝑍𝐷𝐴(symbol) 🔧(PIC32MZDA_##symbol)
#define 🎭𝑀𝑍𝐷𝐴(sym,msk,...) (uint32_t)🎭((__builtin_uint_t *)(PIC32MZDA_##sym), PIC32MZDA_##sym##_##msk __VA_OPT__(,) __VA_ARGS__)
#define 🔧ᵗᵍᵍˡ𝑀𝑍𝐷𝐴(symbol,msk) 🔧(PIC32MZDA_##symbol##INV) = PIC32MZDA_##symbol##_##msk
#define 🔧0𝑀𝑍𝐷𝐴(symbol,msk) 🔧(PIC32MZDA_##symbol##CLR) = PIC32MZDA_##symbol##_##msk
#define 🔧1𝑀𝑍𝐷𝐴(symbol,msk) 🔧(PIC32MZDA_##symbol##SET) = PIC32MZDA_##symbol##_##msk
#define 🐛𝑀𝑍𝐷𝐴(symbol,msk) (🔎(PIC32MZDA_##symbol)&PIC32MZDA_##symbol##_##msk)
MACRO sexdeca 🚫Serialᵖʰʸ() { return *(sexdeca *)0x1FC54020; } /* Physical? */
MACRO sexdeca Serial₀() { return *(sexdeca *)0x9FC54020; } /* Kseg0. (Cacheable) */
MACRO sexdeca Serial₁() { return *(sexdeca *)0xAFC54020; } /* Kseg1. (Not-cacheble) */

#pragma mark - Locking/unlocking

#define PIC32MZDA_KEY1   0xAA996655
#define PIC32MZDA_KEY2   0x556699AA
#define PIC32MZDA_SYSKEY 0xBF800030

#define 🔓𝑀𝑍𝐷𝐴(syskey1,syskey2) 🔒𝑀𝑍𝐷𝐴 🔧𝑀𝑍𝐷𝐴(SYSKEY)=syskey1; 🔧𝑀𝑍𝐷𝐴(SYSKEY)=syskey2;
#define 🔒𝑀𝑍𝐷𝐴 🔧𝑀𝑍𝐷𝐴(SYSKEY)=0x0;

#pragma mark - Flash

BITMASK (uint32_t) { /* NVMCON */
  PIC32MZDA_NVMCON_WR = 0b1<<15, /* Write Control */
  PIC32MZDA_NVMCON_WREN = 0b1<<14, /* Write Enable */
  PIC32MZDA_NVMCON_WRERR = 0b1<<13, /* Write Error */
  PIC32MZDA_NVMCON_LVDERR = 0b1<<12, /* Low-Voltage Detect Error */
  PIC32MZDA_NVMCON_PFSWAP = 0b1<<7, /* Program Flash Bank Swap Control */
  PIC32MZDA_NVMCON_BFSWAP = 0b1<<6, /* Boot Flash Bank Swap Control */
  PIC32MZDA_NVMCON_NVMOP = 0b1111<<0, /* NVM Operation */
};

BITMASK (uint32_t) { /* NVMCON2 */
  PIC32MZDA_NVMCON2_SWAPLOCK = 0b11<<6, /* Program flash memory page write-protect 'Unlock'. */
};

PIC32SYMBOL(MZDA, NVMCON, 0xBF800600)
PIC32SYMBOL(MZDA, NVMCON2, 0xBF8006a0)

/* For non-live update: */

MACRO void boot_EraseProgFlash() { /* 0b0111 */ }
/* MACRO void SwapBoot1And2() { 🔧ᵗᵍᵍˡ𝑀𝑍𝐷𝐴(NVMCON,BFSWAP); } */

/*
 
 In a 'live update' the new code is kept in the upper half (0xBE004000):
 
 Since new code when live update is in upper half, 0xBE000001 may be assumed 
 by boot to contain a persisted PFSWAP take care of by `boot_Reprogram`, and 
 `boot_Rollback`. 
 
 Run only `boot_`-prefixed functions from inside the boot application.
 
 */

MACRO bool boot_IsProgramFlashInverted() { return 🎭𝑀𝑍𝐷𝐴(NVMCON,PFSWAP); }

/* ... */

#pragma mark - ...and 𝒇𝒊𝒏𝒂𝒍𝒍𝒚 the IO-ports

#define IOPORT(serie,letter,start)                                          \
  PIC32SYMBOL(serie, ANSEL##letter,  start) /* Analog if `1`. */            \
  PIC32SYMBOL(serie, TRIS##letter,   start+0x10) /* Input if `1`. */        \
  PIC32SYMBOL(serie, PORT##letter,   start+0x20) /* The port pins. */       \
  PIC32SYMBOL(serie, LAT##letter,    start+0x30) /* The latch. */
// PIC32SYMBOL(serie, ODC##letter,    start+0x40) /* Open-drain control. */ \
// PIC32SYMBOL(serie, CNCON##letter,  start+0x70) /*  */                    \
// PIC32SYMBOL(serie, CNEN##letter,   start+0x80) /* CN enable. */          \
// PIC32SYMBOL(serie, CNSTAT##letter, start+0x90) /*  */                    \

IOPORT(MZDA,A,0xBF860000) IOPORT(MZDA,C,0xBF860200) IOPORT(MZDA,D,0xBF860300)
IOPORT(MZDA,E,0xBF860400) IOPORT(MZDA,F,0xBF860500) IOPORT(MZDA,G,0xBF860600)
IOPORT(MZDA,H,0xBF860700) IOPORT(MZDA,J,0xBF860800) IOPORT(MZDA,K,0xBF860900)

