//
//  pic32mz.hpp
//  pic32rt
//

#ifndef __PIC32MZ_HPP
#define __PIC32MZ_HPP

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
PIC32SYMBOL(MZ, INTSTAT, 0xBF810020)
PIC32SYMBOL(MZ, RPG9R,   0xBF8016a4)
PIC32SYMBOL(MZ, U2RXR,   0xBF801470)
PIC32SYMBOL(MZ, U6MODE,  0xBF822A00) // UARTx mode
PIC32SYMBOL(MZ, U4MODE,  0xBF822600)
PIC32SYMBOL(MZ, U2MODE,  0xBF822200)
PIC32SYMBOL(MZ, U6STA,   0xBF822A10) // UARTx status and control
PIC32SYMBOL(MZ, U4STA,   0xBF822610)
PIC32SYMBOL(MZ, U2STA,   0xBF822210)
PIC32SYMBOL(MZ, U6TXREG, 0xBF822A20) // Transmit buffer register in which data to be transmitted is stored
PIC32SYMBOL(MZ, U4TXREG, 0xBF822620)
PIC32SYMBOL(MZ, U2TXREG, 0xBF822220)
PIC32SYMBOL(MZ, U2RXREG, 0xBF822230) // Recieve buffer register in which data recieved is stored
PIC32SYMBOL(MZ, U4RXREG, 0xBF822630)
PIC32SYMBOL(MZ, U6RXREG, 0xBF822A30)
PIC32SYMBOL(MZ, U2BRG,   0xBF822240) // Baud rate
PIC32SYMBOL(MZ, U4BRG,   0xBF822640)
PIC32SYMBOL(MZ, U6BRG,   0xBF822a40)
PIC32SYMBOL(MZ, ANSELB,  0xBF860100) // Analog if `1`
PIC32SYMBOL(MZ, TRISB,   0xBF860110) // Input if `1`
PIC32SYMBOL(MZ, PORTB,   0xBF860120) // The port pins
PIC32SYMBOL(MZ, LATB,    0xBF860130) // The latch
PIC32SYMBOL(MZ, TRISH,   0xBF860710)
PIC32SYMBOL(MZ, PORTH,   0xBF860720)
PIC32SYMBOL(MZ, LATH,    0xBF860730)
#pragma clang diagnostic pop –

BITMASK (uint32_t) { // UxMODE
  PIC32MZ_U2MODE_MODE_ON = 0b1 << 15, // UARTx enable bit
  PIC32MZ_U4MODE_MODE_ON = 0b1 << 15,
  PIC32MZ_U6MODE_MODE_ON = 0b1 << 15,
};

BITMASK (uint32_t) { // UxSTA
  PIC32MZ_U6STA_URXEN = 0b1 << 12, // Reciever enable
  PIC32MZ_U4STA_URXEN = 0b1 << 12,
  PIC32MZ_U2STA_URXEN = 0b1 << 12,
  PIC32MZ_U6STA_UTXEN = 0b1 << 10, // Transmit enable
  PIC32MZ_U4STA_UTXEN = 0b1 << 10,
  PIC32MZ_U2STA_UTXEN = 0b1 << 10,
  PIC32MZ_U6STA_UTXBF = 0b1 <<  9, // Transmit buffer full status
  PIC32MZ_U4STA_UTXBF = 0b1 <<  9,
  PIC32MZ_U2STA_UTXBF = 0b1 <<  9,
  PIC32MZ_U6STA_TRMT  = 0b1 <<  8, // Transmit shift register is empty bit
  PIC32MZ_U4STA_TRMT  = 0b1 <<  8,
  PIC32MZ_U2STA_TRMT  = 0b1 <<  8,
  PIC32MZ_U2STA_OERR  = 0b1 <<  1, // Receive buffer overrun error status
  PIC32MZ_U4STA_OERR  = 0b1 <<  1,
  PIC32MZ_U6STA_OERR  = 0b1 <<  1,
  PIC32MZ_U2STA_URXDA = 0b1 <<  0, // Receive buffer data available (read-only)
  PIC32MZ_U4STA_URXDA = 0b1 <<  0,
  PIC32MZ_U6STA_URXDA = 0b1 <<  0,
};

#define 🔎𝑀𝑍(symbol) 🔎(PIC32MZ_##symbol)
#define 🔧𝑀𝑍(symbol) 🔧(PIC32MZ_##symbol)
#define 🔧0𝑀𝑍(symbol,msk) 🔧(PIC32MZ_##symbol##CLR) = PIC32MZ_##symbol##_##msk
#define 🔧1𝑀𝑍(symbol,msk) 🔧(PIC32MZ_##symbol##SET) = PIC32MZ_##symbol##_##msk

#ifdef __MZDAStarterBoard__
enum Interrupt { Coretimer=0, Coresoftware0=1, Coresoftware1=2, ExternalInt0=3,
  Timer1=4, InputCapture1Error=5, InputCapture1=6, OutputCompare1=7, Timer2=9, 
  Timer5=24, Timer6=28, Timer7=32, Timer8=36, Timer9=40, ADCGlobal=44, ADCFIFO=45,
  ADCDigitalComparator1=46, ADCDigitalFilter1=52, ADCFault=58, ADCData0=59, 
  USBSuspendResume=103, Crypto=107, SPI1ReceiveDone=110, SPI1TransferDone=111, 
  InputchangePortB=119, USBGeneral=132, USBDMA=133, DMAChannel0=134, 
  I2C2BusCollision=148, I2C2Slave=149, I2C2Master=150, Realtimeclock=166, 
  Flash=167, Prefetch=168, SQI=169, SDHC=191, GLCD=192, GPU=193, CTMU=195, 
  ADCEndOfScan=196, ADCAnalogCircuitReady=197, ADCUpdateReady=198, ADC0Early=199, 
  ADCGroupEarly=205, ADC0Warm=207, MPLLFault=215 };
#endif

BITMASK (uint32_t) { // INTSTAT
  PIC32MZ_INTSTAT_SIRQ_8̄ = 0b00000111111 // Interrupt vector
};

MACRO Interrupt 🔎IRQ() { return Interrupt(PIC32MZ_INTSTAT_SIRQ_8̄ & 🔎𝑀𝑍(INTSTAT)); }

#endif
