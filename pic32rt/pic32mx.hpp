//
//  pic32mx.hpp
//  pic32rt
//

PIC32SYMBOL(MX, U5MODE,  0xBF806a00) /* UARTx mode register. */
PIC32SYMBOL(MX, U5STA,   0xBF806a10) /* UARTx status and control register. */
PIC32SYMBOL(MX, U5TXREG, 0xBF806a20) /* Transmit buffer register in which data to be transmitted is stored. */
PIC32SYMBOL(MX, U5RXREG, 0xBF806a30) /* Recieve buffer register in which data recieved is stored. */

BITMASK (uint32_t) { /* UxMODE */
  PIC32MX_U5MODE_MODE_ON = 0b1<<15, /* UARTx Enable bit. */
};

BITMASK (uint32_t) { /* UxSTA */
  PIC32MX_U5STA_UTXEN = 0b1 << 10, /* Transmit enable. */
  PIC32MX_U5STA_UTXBF = 0b1 <<  9, /* Transmit buffer full status. */
  PIC32MX_U5STA_OERR  = 0b1 <<  1, /* Receive buffer overrun error status. */
  PIC32MX_U5STA_URXDA = 0b1 <<  0, /* Receive buffer data available (read-only). */
};

#define 🔎𝑀𝑋(symbol) 🔎(PIC32MX_##symbol)
#define 🔧𝑀𝑋(symbol) 🔧(PIC32MX_##symbol)
#define 🎭𝑀𝑋(sym,msk,...) (uint32_t)🎭((__builtin_uint_t *)(PIC32MX_##sym), PIC32MX_##sym##_##msk __VA_OPT__(,) __VA_ARGS__)
#define 🔧ᵗᵍᵍˡ𝑀𝑋(symbol,msk) 🔧(PIC32MX_##symbol##INV) = PIC32MX_##symbol##_##msk
#define 🔧0𝑀𝑋(symbol,msk) 🔧(PIC32MX_##symbol##CLR) = PIC32MX_##symbol##_##msk
#define 🔧1𝑀𝑋(symbol,msk) 🔧(PIC32MX_##symbol##SET) = PIC32MX_##symbol##_##msk
#define 🐛𝑀𝑋(symbol,msk) ((i)&PIC32MX_##symbol##_##msk)

#define PIC32MX_SYSKEY 0xBF80F230

