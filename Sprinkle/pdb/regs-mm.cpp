/*  regs-mm.cpp | the structure of MM and no double. */

#include <Twinbeam.h> /* includes --<Source>--<coroutine>. */

/* CP0, register 16, 0 */ BITMASK (uint32_t) { /* MIPS Config. */
  MIPS_Config_K23 = 0b111<<28, /* Cacheability kseg2 and kseg3 */
  MIPS_Config_KU = 0b111<<25,  /* Cacheability kuseg and useg */
// MIPS_Config_ISP = 0b1<<24,   /* Instruction scratch pad RAM */
// MIPS_Config_DSP = 0b1<<23,   /* Data scratch pad RAM */
  MIPS_Config_UDI = 0b1<<22,   /* User-defined */
  MIPS_Config_SB = 0b1<<21,    /* Simple BE */
  MIPS_Config_MDU = 0b1<<20,   /* Multiply/divide unit */
// MIPS_Config_MM = 0b11<<17,   /* Merge mode */
  MIPS_Config_DS = 0b1<<16,    /* Dual SRAM Interface */
// MIPS_Config_DSBM = 0b1<<16,  /* Dual SRAM/burst mode */
// MIPS_Config_BM = 0b1<<16,    /* Burst mode */
  MIPS_Config_BE = 0b1<<15,    /* Endian mode */
  MIPS_Config_AT = 0b11<<13,   /* Architecture type */
  MIPS_Config_AR = 0b111<<10,  /* Architecture revision level */
  MIPS_Config_MT = 0b111<<7,   /* MMU Type */
  MIPS_Config_K0 = 0b111<<0    /* Kseg0 Coherency Algorithm */
};

Bitfield MipsMM_Config[] READONLY = {
  { U"MIPS_Config_K23", MIPS_Config_K23, U"Cacheability kseg2 and kseg3" },
  { U"MIPS_Config_KU", MIPS_Config_KU, U"Cacheability kuseg and useg" },
  { U"MIPS_Config_UDI", MIPS_Config_UDI, U"User-defined" },
  { U"MIPS_Config_SB", MIPS_Config_SB, U"Simple BE" },
  { U"MIPS_Config_MDU", MIPS_Config_MDU, U"Multiply/Divide Unit" },
  { U"MIPS_Config_DS", MIPS_Config_DS, U"Dual SRAM Interface" },
  { U"MIPS_Config_BE", MIPS_Config_BE, U"Endian Mode" },
  { U"MIPS_Config_AT", MIPS_Config_AT, U"Architecture Type" },
  { U"MIPS_Config_AR", MIPS_Config_AR, U"Architecture Revision Level" },
  { U"MIPS_Config_MT", MIPS_Config_MT, U"MMU Type" },
  { U"MIPS_Config_K0", MIPS_Config_K0, U"Kseg0 Coherency Algorithm" },
};

AnnotatedRegister AR_MipsMM_Config READONLY = {
  U"CONFIG: Configuration Register (CP0 Register 16, Select 0)",
  11, MipsMM_Config, 0x80000000,
  U""
};

/* CP0, register 23, 0 */ BITMASK(uint32_t) { /* Debug Register */
  MIPS_DEBUG_DBD        = 0b10000000000000000000000000000000, /* Branch ͞ Debug Exception */
  MIPS_DEBUG_DM         = 0b01000000000000000000000000000000, /* Debug Mode */
  MIPS_DEBUG_NODCR      = 0b00100000000000000000000000000000, /* Debug Control Register */
  MIPS_DEBUG_LSNM       = 0b00010000000000000000000000000000, /* Load Store Access Control */
  MIPS_DEBUG_DOZE       = 0b00001000000000000000000000000000, /* Low-Power Mode Debug Exception */
  MIPS_DEBUG_HALT       = 0b00000100000000000000000000000000, /* System Bus Clock Stop */
  MIPS_DEBUG_COUNTDM    = 0b00000010000000000000000000000000, /* Count Register Behavior */
  MIPS_DEBUG_IBUSEP     = 0b00000001000000000000000000000000, /* Instruction Fetch Bus Error Exception Pending */
  MIPS_DEBUG_MCHECKP    = 0b00000000100000000000000000000000, /* Machine Check Exception Pending */
  MIPS_DEBUG_CACHEEP    = 0b00000000010000000000000000000000, /* Cache Error Pending */
  MIPS_DEBUG_DBUSEP     = 0b00000000001000000000000000000000, /* Data Access Bus Error Exception Pending */
  MIPS_DEBUG_IEXI       = 0b00000000000100000000000000000000, /* Imprecise Error Exception Inhibit Control */
  MIPS_DEBUG_DDBSIMPR   = 0b00000000000010000000000000000000, /* Debug Data Break Store Exception */
  MIPS_DEBUG_DDBLIMPR   = 0b00000000000001000000000000000000, /* Debug Data Break Load Exception */
  MIPS_DEBUG_VER_3͞      = 0b00000000000000111000000000000000, /* EJTAG Version */
  MIPS_DEBUG_DEXCCODE_5͞ = 0b00000000000000000111110000000000, /* Latest Exception in Debug Mode */
  MIPS_DEBUG_NOSST      = 0b00000000000000000000001000000000, /* Singe-step Feature Control */
  MIPS_DEBUG_SST        = 0b00000000000000000000000100000000, /* Debug Single-step Control */
  MIPS_DEBUG_DIBIMPR    = 0b00000000000000000000000001000000, /* Imprecise Debug Instruction Break Exception */
  MIPS_DEBUG_DINT       = 0b00000000000000000000000000100000, /* Debug Interrupt Exception */
  MIPS_DEBUG_DIB        = 0b00000000000000000000000000010000, /* Debug Instruction Break Exception */
  MIPS_DEBUG_DDBS       = 0b00000000000000000000000000001000, /* Debug Data Break Exception on Store */
  MIPS_DEBUG_DDBL       = 0b00000000000000000000000000000100, /* Debug Data Break Exception on Load */
  MIPS_DEBUG_DBP        = 0b00000000000000000000000000000010, /* Debug Software Breakpoint Exception */
  MIPS_DEBUG_DSS        = 0b00000000000000000000000000000001  /* Debug Single-step Exception */
};

Register MipsMM_Debug READONLY = {
  { U"MIPS_DEBUG_DBD", MIPS_DEBUG_DBD, U"Branch Delay Debug Exception" },
  { U"MIPS_DEBUG_DM", MIPS_DEBUG_DM, U"Debug Mode" },
  { U"MIPS_DEBUG_NODCR", MIPS_DEBUG_NODCR, U"Debug Control Register" },
  { U"MIPS_DEBUG_LSNM", MIPS_DEBUG_LSNM, U"Load Store Access Control" },
  { U"MIPS_DEBUG_DOZE", MIPS_DEBUG_DOZE, U"Low-Power Mode Debug Exception" },
  { U"MIPS_DEBUG_HALT", MIPS_DEBUG_HALT, U"System Bus Clock Stop" },
  { U"MIPS_DEBUG_COUNTDM", MIPS_DEBUG_COUNTDM, U"Count Register Behavior" },
  { U"MIPS_DEBUG_IBUSEP", MIPS_DEBUG_IBUSEP, U"Instruction Fetch Bus Error Exception Pending" },
  { U"MIPS_DEBUG_MCHECKP", MIPS_DEBUG_MCHECKP, U"Machine Check Exception Pending" },
  { U"MIPS_DEBUG_CACHEEP", MIPS_DEBUG_CACHEEP, U"Cache Error Pending" },
  { U"MIPS_DEBUG_DBUSEP", MIPS_DEBUG_DBUSEP, U"Data Access Bus Error Exception Pending" },
  { U"MIPS_DEBUG_IEXI", MIPS_DEBUG_IEXI, U"Imprecise Error Exception Inhibit Control" },
  { U"MIPS_DEBUG_DDBSIMPR", MIPS_DEBUG_DDBSIMPR, U"Debug Data Break Store Exception" },
  { U"MIPS_DEBUG_DDBLIMPR", MIPS_DEBUG_DDBLIMPR, U"Debug Data Break Load Exception" },
  { U"MIPS_DEBUG_VER_3", MIPS_DEBUG_VER_3͞, U"EJTAG Version" },
  { U"MIPS_DEBUG_DEXCCODE_5", MIPS_DEBUG_DEXCCODE_5͞, U"Latest Exception in Debug Mode" },
  { U"MIPS_DEBUG_NOSST", MIPS_DEBUG_NOSST, U"Single-step Feature Control" },
  { U"MIPS_DEBUG_SST", MIPS_DEBUG_SST, U"Debug Single-step Control" },
  { U"MIPS_DEBUG_DIBIMPR", MIPS_DEBUG_DIBIMPR, U"Imprecise Debug Instruction Break Exception" },
  { U"MIPS_DEBUG_DINT", MIPS_DEBUG_DINT, U"Debug Interrupt Exception" },
  { U"MIPS_DEBUG_DIB", MIPS_DEBUG_DIB, U"Debug Instruction Break Exception" },
  { U"MIPS_DEBUG_DDBS", MIPS_DEBUG_DDBS, U"Debug Data Break Exception on Store" },
  { U"MIPS_DEBUG_DDBL", MIPS_DEBUG_DDBL, U"Debug Data Break Exception on Load" },
  { U"MIPS_DEBUG_DBP", MIPS_DEBUG_DBP, U"Debug Software Breakpoint Exception" },
  { U"MIPS_DEBUG_DSS", MIPS_DEBUG_DSS, U"Debug Single-step Exception" }
};

AnnotatedRegister AR_MipsMM_Debug READONLY = {
  U"Debug Register (CP0 Register 23, Select 0)",
  25, MipsMM_Debug, 0x00000000,
  U""
};

BITMASK (uint32_t) { /* INTCON */
  PIC32MM_INTCON_VS = 0b1111111<<16, /* Vector Spacing */
  PIC32MM_INTCON_MVEC = 0b1<<12, /* Multivector Configuration */
  PIC32MM_INTCON_TPC = 0b111<<8, /* Interrupt Proximity Timer Control */
  PIC32MM_INTCON_INT4EP = 0b1<<4, /* Ext. Irq 4 Edge Polarity Ctrl */
  PIC32MM_INTCON_INT3EP = 0b1<<3, /* Ext. Irq 3 Edge Polarity Ctrl */
  PIC32MM_INTCON_INT2EP = 0b1<<2, /* Ext. Irq 2 Edge Polarity Ctrl */
  PIC32MM_INTCON_INT1EP = 0b1<<1, /* Ext. Irq 1 Edge Polarity Ctrl */
  PIC32MM_INTCON_INT0EP = 0b1<<0 /*  Ext. Irq 0 Edge Polarity Ctrl */
};

Register MicrochipMM_INTCON = {
  { U"PIC32MM_INTCON_VS", PIC32MM_INTCON_VS, U"Vector Spacing" },
  { U"PIC32MM_INTCON_MVEC", PIC32MM_INTCON_MVEC, U"Multi Vector Configuration" },
  { U"PIC32MM_INTCON_TPC", PIC32MM_INTCON_TPC, U"Interrupt Proximity Timer Control" },
  { U"PIC32MM_INTCON_INT4EP", PIC32MM_INTCON_INT4EP, U"Ext. Irq 4 Edge Polarity Ctrl" },
  { U"PIC32MM_INTCON_INT3EP", PIC32MM_INTCON_INT3EP, U"Ext. Irq 3 Edge Polarity Ctrl" },
  { U"PIC32MM_INTCON_INT2EP", PIC32MM_INTCON_INT2EP, U"Ext. Irq 2 Edge Polarity Ctrl" },
  { U"PIC32MM_INTCON_INT1EP", PIC32MM_INTCON_INT1EP, U"Ext. Irq 1 Edge Polarity Ctrl" },
  { U"PIC32MM_INTCON_INT0EP", PIC32MM_INTCON_INT0EP, U"Ext. Irq 0 Edge Polarity Ctrl" }
};

AnnotatedRegister AR_MicrochipMM_INTCON = {
  U"INTCON: INTERRUPT CONTROL REGISTER",
  8, MicrochipMM_INTCON, 0x00000000,
  U""
};

BITMASK (uint32_t) { /* PRISS */
  PIC32MM_PRISS_PRI7SS = 0xf0000000, /* Irq with Prio Level 7 Shadow Set */
  PIC32MM_PRISS_PRI6SS = 0x0f000000, /* Irq with Prio Level 6 Shadow Set */
  PIC32MM_PRISS_PRI5SS = 0x00f00000, /* Irq with Prio Level 5 Shadow Set */
  PIC32MM_PRISS_PRI4SS = 0x000f0000, /* Irq with Prio Level 4 Shadow Set */
  PIC32MM_PRISS_PRI3SS = 0x0000f000, /* Irq with Prio Level 3 Shadow Set */
  PIC32MM_PRISS_PRI2SS = 0x00000f00, /* Irq with Prio Level 2 Shadow Set */
  PIC32MM_PRISS_PRI1SS = 0x000000f0, /* Irq with Prio Level 1 Shadow Set */
  PIC32MM_PRISS_SS0 = 0b1<<0 /* Single Vector Shadow Register Set */
};

Register MicrochipMM_PRISS = {
  { U"PIC32MM_PRISS_PRI7SS", PIC32MM_PRISS_PRI7SS, U"Interrupt with Priority Level 7 Shadow Set" },
  { U"PIC32MM_PRISS_PRI6SS", PIC32MM_PRISS_PRI6SS, U"Interrupt with Priority Level 6 Shadow Set" },
  { U"PIC32MM_PRISS_PRI5SS", PIC32MM_PRISS_PRI5SS, U"Interrupt with Priority Level 5 Shadow Set" },
  { U"PIC32MM_PRISS_PRI4SS", PIC32MM_PRISS_PRI4SS, U"Interrupt with Priority Level 4 Shadow Set" },
  { U"PIC32MM_PRISS_PRI3SS", PIC32MM_PRISS_PRI3SS, U"Interrupt with Priority Level 3 Shadow Set" },
  { U"PIC32MM_PRISS_PRI2SS", PIC32MM_PRISS_PRI2SS, U"Interrupt with Priority Level 2 Shadow Set" },
  { U"PIC32MM_PRISS_PRI1SS", PIC32MM_PRISS_PRI1SS, U"Interrupt with Priority Level 1 Shadow Set" },
  { U"PIC32MM_PRISS_SS0",    PIC32MM_PRISS_SS0, U"Single Vector Shadow Register Set" }
};

AnnotatedRegister AR_MicrochipMM_PRISS = {
  U"PRISS: PRIORITY SHADOW SELECT REGISTER",
  8, MicrochipMM_PRISS, 0x00000000,
  U""
};

BITMASK (uint32_t) { /* INTSTAT */
  PIC32MM_INTSTAT_SRIPL = 0b111<<8, /* Requested Priority Level bits for Single Vector Mode */
  PIC32MM_INTSTAT_SIRQ = 0xff /* Last Interrupt Request Serviced Status */
};

Register MicrochipMM_INTSTAT = {
  { U"PIC32MM_INTSTAT_SRIPL", PIC32MM_INTSTAT_SRIPL, U"Requested Priority Level bits for Single Vector Mode" },
  { U"PIC32MM_INTSTAT_SIRQ",  PIC32MM_INTSTAT_SIRQ, U"Last Interrupt Request Serviced Status" }
};

AnnotatedRegister AR_MicrochipMM_INTSTAT = {
  U"INTSTAT: INTERRUPT STATUS REGISTER",
  2, MicrochipMM_INTSTAT, 0x00000000,
  U""
};

BITMASK (uint32_t) { /* IPTMR */
  PIC32MM_IPTMR_IPTMR = 0xffffffff /* Interrupt Proximity Timer Reload */
};

Register MicrochipMM_IPTMR = {
  { U"PIC32MM_IPTMR_IPTMR", PIC32MM_IPTMR_IPTMR, U"Interrupt Proximity Timer Reload" }
};

AnnotatedRegister AR_MicrochipMM_IPTMR = {
  U"IPTMR: INTERRUPT PROXIMITY TIMER REGISTER",
  1, MicrochipMM_IPTMR, 0x00000000,
  U""
};

BITMASK (uint32_t) { /* IFS0 */
  PIC32MM_IFS0_CCP2IF = 0x80000000, /* Capture/Compare/PWM/Timer P2 Interrupt */
  PIC32MM_IFS0_CCT1IF = 0b1<<30, /* Capture/Compare/PWM/Timer T1 Interrupt */
  PIC32MM_IFS0_CCP1IF = 0b1<<29, /* Capture/Compare/PWM/Timer P1 Interrupt */
  PIC32MM_IFS0_U1EIF = 0b1<<25, /* Uart 1 Generic Interrupt */
  PIC32MM_IFS0_U1TXIF = 0b1<<24, /* Uart 1 Tx Interrupt */
  PIC32MM_IFS0_U1RXIF = 0b1<<23, /* Uart 1 Rx Interrupt */
  PIC32MM_IFS0_SPI1RXIF = 0b1<<22, /* Spi1 Rx Interrupt */
  PIC32MM_IFS0_SPI1TXIF = 0b1<<21, /* Spi1 Tx Interrupt */
  PIC32MM_IFS0_SPI1EIF = 0b1<<20, /* Spi1 Generic Interrupt */
  PIC32MM_IFS0_CLC2IF = 0b1<<19, /* Logic 2 Interrupt */
  PIC32MM_IFS0_CLC1IF = 0b1<<18, /* Logic 1 Interrupt */
  PIC32MM_IFS0_LVDIF = 0b1<<17, /* High/Low-Voltage Detect Interrupt */
  PIC32MM_IFS0_CRCIF = 0b1<<16, /* CRC Interrupt */
  PIC32MM_IFS0_AD1IF = 0b1<<15, /* ADC 1 Interrupt */
  PIC32MM_IFS0_RTCCIF = 0b1<<14, /* RTCC Interrupt */
  PIC32MM_IFS0_CMP2IF = 0b1<<13, /* Comparator 2 Interrupt */
  PIC32MM_IFS0_CMP1IF = 0b1<<12, /* Comparator 1 Interrupt */
  PIC32MM_IFS0_T1IF = 0b1<<11, /* Timer 1 Interrupt */
  PIC32MM_IFS0_CNCIF = 0b1<<10, /* Change Notification C */
  PIC32MM_IFS0_CNBIF = 0b1<<9, /* Change Notification B */
  PIC32MM_IFS0_CNAIF = 0b1<<8, /* Change Notification A */
  PIC32MM_IFS0_INT4IF = 0b1<<7, /* External Interrupt 4 */
  PIC32MM_IFS0_INT3IF = 0b1<<6, /* External Interrupt 3 */
  PIC32MM_IFS0_INT2IF = 0b1<<5, /* External Interrupt 2 */
  PIC32MM_IFS0_INT1IF = 0b1<<4, /* External Interrupt 1 */
  PIC32MM_IFS0_INT0IF = 0b1<<3, /* External Interrupt 0 */
  PIC32MM_IFS0_CS1IF = 0b1<<2, /* Core Software Interrupt 1 */
  PIC32MM_IFS0_CS0IF = 0b1<<1, /* Core Software Interrupt 0 */
  PIC32MM_IFS0_CTIF = 0b1<<0 /* Core Timer Interrupt */
};

Register MicrochipMM_IFS0 = {
  { U"PIC32MM_IFS0_CCP2IF", PIC32MM_IFS0_CCP2IF, U"Capture/Compare/PWM/Timer P2 Interrupt" },
  { U"PIC32MM_IFS0_CCT1IF", PIC32MM_IFS0_CCT1IF, U"Capture/Compare/PWM/Timer T1 Interrupt" },
  { U"PIC32MM_IFS0_CCP1IF", PIC32MM_IFS0_CCP1IF, U"Capture/Compare/PWM/Timer P1 Interrupt" },
  { U"PIC32MM_IFS0_U1EIF", PIC32MM_IFS0_U1EIF, U"Uart 1 Generic Interrupt" },
  { U"PIC32MM_IFS0_U1TXIF", PIC32MM_IFS0_U1TXIF, U"Uart 1 Tx Interrupt" },
  { U"PIC32MM_IFS0_U1RXIF", PIC32MM_IFS0_U1RXIF, U"Uart 1 Rx Interrupt" },
  { U"PIC32MM_IFS0_SPI1RXIF", PIC32MM_IFS0_SPI1RXIF, U"Spi1 Rx Interrupt" },
  { U"PIC32MM_IFS0_SPI1TXIF", PIC32MM_IFS0_SPI1TXIF, U"Spi1 Tx Interrupt" },
  { U"PIC32MM_IFS0_SPI1EIF", PIC32MM_IFS0_SPI1EIF, U"Spi1 Generic Interrupt" },
  { U"PIC32MM_IFS0_CLC2IF", PIC32MM_IFS0_CLC2IF, U"Logic 2 Interrupt" },
  { U"PIC32MM_IFS0_CLC1IF", PIC32MM_IFS0_CLC1IF, U"Logic 1 Interrupt" },
  { U"PIC32MM_IFS0_LVDIF", PIC32MM_IFS0_LVDIF, U"High/Low-Voltage Detect Interrupt" },
  { U"PIC32MM_IFS0_CRCIF", PIC32MM_IFS0_CRCIF, U"CRC Interrupt" },
  { U"PIC32MM_IFS0_AD1IF", PIC32MM_IFS0_AD1IF, U"ADC 1 Interrupt" },
  { U"PIC32MM_IFS0_RTCCIF", PIC32MM_IFS0_RTCCIF, U"RTCC Interrupt" },
  { U"PIC32MM_IFS0_CMP2IF", PIC32MM_IFS0_CMP2IF, U"Comparator 2 Interrupt" },
  { U"PIC32MM_IFS0_CMP1IF", PIC32MM_IFS0_CMP1IF, U"Comparator 1 Interrupt" },
  { U"PIC32MM_IFS0_T1IF", PIC32MM_IFS0_T1IF, U"Timer 1 Interrupt" },
  { U"PIC32MM_IFS0_CNCIF", PIC32MM_IFS0_CNCIF, U"Change Notification C" },
  { U"PIC32MM_IFS0_CNBIF", PIC32MM_IFS0_CNBIF, U"Change Notification B" },
  { U"PIC32MM_IFS0_CNAIF", PIC32MM_IFS0_CNAIF, U"Change Notification A" },
  { U"PIC32MM_IFS0_INT4IF", PIC32MM_IFS0_INT4IF, U"External Interrupt 4" },
  { U"PIC32MM_IFS0_INT3IF", PIC32MM_IFS0_INT3IF, U"External Interrupt 3" },
  { U"PIC32MM_IFS0_INT2IF", PIC32MM_IFS0_INT2IF, U"External Interrupt 2" },
  { U"PIC32MM_IFS0_INT1IF", PIC32MM_IFS0_INT1IF, U"External Interrupt 1" },
  { U"PIC32MM_IFS0_INT0IF", PIC32MM_IFS0_INT0IF, U"External Interrupt 0" },
  { U"PIC32MM_IFS0_CS1IF", PIC32MM_IFS0_CS1IF, U"Core Software Interrupt 1" },
  { U"PIC32MM_IFS0_CS0IF", PIC32MM_IFS0_CS0IF, U"Core Software Interrupt 0" },
  { U"PIC32MM_IFS0_CTIF", PIC32MM_IFS0_CTIF, U"Core Timer Interrupt" }
};

AnnotatedRegister AR_MicrochipMM_IFS0 = {
  U"IFS0: INTERRUPT FLAG REGISTER 0",
  29, MicrochipMM_IFS0, 0x00000000,
  U""
};

BITMASK (uint32_t) { /* IFS1 */
  PIC32MM_IFS1_CPCIF = 0b1<<15, /* */
  PIC32MM_IFS1_NVMIF = 0b1<<14, /* Non-volatile Interrupt */
  PIC32MM_IFS1_U2EIF = 0b1<<10, /* Uart 2 Generic Interrupt */
  PIC32MM_IFS1_U2TXIF = 0b1<<9, /* Uart 2 Tx Interrupt */
  PIC32MM_IFS1_U2RXIF = 0b1<<8, /* Uart 2 Rx Interrupt */
  PIC32MM_IFS1_SPI2RXIF = 0b1<<7, /* Spi2 Rx Interrupt */
  PIC32MM_IFS1_SPI2TXIF = 0b1<<6, /* Spi2 Tx Interrupt */
  PIC32MM_IFS1_SPI2EIF = 0b1<<5, /* Spi2 Generic Interrupt */
  PIC32MM_IFS1_CCT3IF = 0b1<<2, /* Capture/Compare/PWM/Timer T3 Interrupt */
  PIC32MM_IFS1_CCP3IF = 0b1<<1, /* Capture/Compare/PWM/Timer P3 Interrupt */
  PIC32MM_IFS1_CCT2IF = 0b1<<0, /* Capture/Compare/PWM/Timer T2 Interrupt */
};

Register MicrochipMM_IFS1 = {
  { U"PIC32MM_IFS1_CPCIF", PIC32MM_IFS1_CPCIF, U"" },
  { U"PIC32MM_IFS1_NVMIF", PIC32MM_IFS1_NVMIF, U"Non-volatile Interrupt" },
  { U"PIC32MM_IFS1_U2EIF", PIC32MM_IFS1_U2EIF, U"Uart 2 Generic Interrupt" },
  { U"PIC32MM_IFS1_U2TXIF", PIC32MM_IFS1_U2TXIF, U"Uart 2 Tx Interrupt" },
  { U"PIC32MM_IFS1_U2RXIF", PIC32MM_IFS1_U2RXIF, U"Uart 2 Rx Interrupt" },
  { U"PIC32MM_IFS1_SPI2RXIF", PIC32MM_IFS1_SPI2RXIF, U"Spi2 Rx Interrupt" },
  { U"PIC32MM_IFS1_SPI2TXIF", PIC32MM_IFS1_SPI2TXIF, U"Spi2 Tx Interrupt" },
  { U"PIC32MM_IFS1_SPI2EIF", PIC32MM_IFS1_SPI2EIF, U"Spi2 Generic Interrupt" },
  { U"PIC32MM_IFS1_CCT3IF", PIC32MM_IFS1_CCT3IF, U"Capture/Compare/PWM/Timer T3 Interrupt" },
  { U"PIC32MM_IFS1_CCP3IF", PIC32MM_IFS1_CCP3IF, U"Capture/Compare/PWM/Timer P3 Interrupt" },
  { U"PIC32MM_IFS1_CCT2IF", PIC32MM_IFS1_CCT2IF, U"Capture/Compare/PWM/Timer T2 Interrupt" }
};

AnnotatedRegister AR_MicrochipMM_IFS1 = {
  U"IFS1: INTERRUPT FLAG REGISTER 1",
  11, MicrochipMM_IFS0, 0x00000000,
  U""
};
